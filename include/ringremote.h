#ifndef RINGREMOTE_INCLUDED
#define RINGREMOTE_INCLUDED
#include <string.h>
#include <time.h>

#define MIN(a,b) ((a) > (b) ? (b) : (a))

#define RING_BUFFER_DECLARED	0xDEC1A8ED
#define RING_BUFFER_ALLOCATED	0xA10CA7ED
#define RING_BUFFER_MEM_ERROR	0xDEADF00D
#define RING_BUFFER_ERROR		0xBEDABEDA
#define RING_BUFFER_OK			0x0

#define EXIT_ON_TIMEOUT       1
#define EXIT_ON_COMPLETED     0
#define EXIT_ON_FULL_BUFFER   2
#define EXIT_ON_EMPTY_BUFFER  2

//void Sleep(int msec);

typedef  void *(*t_memcpy)(void *to, int toIndex, const void *from, int fromIndex, size_t size) ;
typedef  void *(*t_bytecpy)(void *to, int toIndex, void const *from, int fromIndex, size_t size) ;

#ifdef __NM__
	#define bytesizeof(T) (sizeof(T)<<2)
#else
	#define bytesizeof(T) sizeof(T)
#endif 

#if defined(_WIN32) && !defined(__GNUC__)
	#include "crtdbg.h"
#else 
	#define _ASSERTE(val)
#endif




template <class T> class C_RingBufferRemote{
private:
	
public:	
	//size_t  sizeof_size_t;
	//size_t  sizeof_T;
	size_t	data_addr;		///<  физический адрес кольцевого буфера входных данных 
	size_t  head_addr;		///<  сколько элементов ОТ НАЧАЛА ПОТОКА код MASTER уже записал в	буфер входных данных [заполняется MASTER]
	size_t  tail_addr;		///<  сколько элементов ОТ НАЧАЛА ПОТОКА код SLAVE  уже прочитал (обработал) 			 [заполняется SLAVE]
	
	size_t 	size;			///<  размер кольцевого буфера входных данных (в элементах; гарантируется что это степень двойки)
	size_t 	head;			///<  сколько элементов ОТ НАЧАЛА ПОТОКА код MASTER уже записал в	буфер входных данных [заполняется MASTER]
	size_t 	tail;			///<  сколько элементов ОТ НАЧАЛА ПОТОКА код SLAVE  уже прочитал (обработал) 			 [заполняется SLAVE]
	size_t 	id;				///<  сколько элементов ОТ НАЧАЛА ПОТОКА код SLAVE  уже прочитал (обработал) 			 [заполняется SLAVE]
	bool	isConnected;
	
	
	t_bytecpy push_memcpy;
	t_bytecpy pop_memcpy;
	
	// ------------- dma --------------
	t_memcpy dma_init;
	size_t(*dma_check)();
	T*     dma_ptr;
	size_t dma_left;
	size_t dma_size;
	//----------------------------------
	unsigned timeout;
	unsigned time2sleep;
	int 	pad[16-3-5*sizeof(t_bytecpy)/sizeof(int)];	///<  резервные поля
	
	
	
	C_RingBufferRemote(){
		isConnected=false;
	}

	C_RingBufferRemote(size_t ringbuffer_addr, t_bytecpy push_memcopy,  t_bytecpy pop_memcopy){
		Init( ringbuffer_addr,  push_memcopy,   pop_memcopy);
	}

	size_t GetHead(){
		pop_memcpy(&head,0,(const void*)head_addr,0,bytesizeof(size_t));
		return head;
	}
	size_t GetTail(){
		pop_memcpy(&tail,0,(const void*)tail_addr,0,bytesizeof(size_t));
		return tail;
	}
	void SetHead(){
		push_memcpy((void*)head_addr,0,&head,0, bytesizeof(size_t));
	}
	void SetTail(){
		push_memcpy((void*)tail_addr,0,&tail,0,bytesizeof(size_t));
	}

	bool Init(size_t ringbuffer_addr, t_bytecpy push_memcopy,  t_bytecpy pop_memcopy){
		//sizeof_size_t=0;
		//sizeof_T=0;
		data_addr=0xCCCCCCCC;			
		head_addr=0xCCCCCCCC;
		tail_addr=0xCCCCCCCC;
		size=0xCCCCCCCC;			
		head=0xCCCCCCCC;			
		tail=0xCCCCCCCC;	
		isConnected=false;

		dma_init=0;
		dma_check=0;
		dma_ptr =0;
		dma_left=0;
		dma_size=0;
		time2sleep=10;
		timeout=100;

		
		push_memcpy=push_memcopy;
		pop_memcpy =pop_memcopy;

		pop_memcpy(&data_addr,0,(void*)ringbuffer_addr,+0*bytesizeof(size_t),bytesizeof(size_t));
		pop_memcpy(&size,     0,(void*)ringbuffer_addr,+1*bytesizeof(size_t),bytesizeof(size_t));
		pop_memcpy(&head_addr,0,(void*)ringbuffer_addr,+4*bytesizeof(size_t),bytesizeof(size_t));
		pop_memcpy(&tail_addr,0,(void*)ringbuffer_addr,+5*bytesizeof(size_t),bytesizeof(size_t));
		pop_memcpy(&id,		  0,(void*)ringbuffer_addr,+6*bytesizeof(size_t),bytesizeof(size_t));
		
		if ((size&(size-1))!=0)		// check that size is power of two
			return false;
		

		if (id!=0x600DB00F)
			return false;

		id = 0xB00F600D;
		push_memcpy((void*)ringbuffer_addr,+6*bytesizeof(size_t),&id,0,bytesizeof(size_t));
		id =0;
		pop_memcpy(&id, 0,(void*)ringbuffer_addr,+6*bytesizeof(size_t),bytesizeof(size_t));
		if (id!=0xB00F600D)		// no access to remote rinbuffer.id
			return false;


		GetHead();
		GetTail();
		if (head==0xCCCCCCCC || tail==0xCCCCCCCC)
			return false;

		
		isConnected = true;
		return true;
	}

	__INLINE__ bool IsFull(){
		GetHead();
		GetTail();
		return (head-tail==size);
	}
	__INLINE__ bool IsEmpty(){
		GetHead();
		GetTail();
		return (head==tail);
	}
	__INLINE__ size_t GetWriteAvail(){
		GetHead();
		GetTail();
		return (size-(head-tail));
	}
	__INLINE__ size_t GetReadAvail(){
		GetHead();
		GetTail();
		return (head-tail);
	}
	
	/*
	T* Head(){
		if (GetWriteAvail()==0)
			return 0;
		size_t headPointer=head&(size-1);
		T* pElement=(T*)(data_addr+headPointer*bytesizeof(T));
		return pElement;
	}
	T* Tail(){
		if (GetReadAvail()==0)
			return 0;
		size_t tailPointer=tail&(size-1);
		T* pElement=(T*)(data_addr+tailPointer*sizeof_T);
		return pElement;
	}*/
	
	bool Push(int numElements){
		GetHead();
		GetTail();
		size_t h=head+numElements;
		if (h>tail+size)
			return RING_BUFFER_ERROR;
		head=h;
		return RING_BUFFER_OK;
	}

	bool Pop(int numElements){
		GetHead();
		GetTail();
		size_t t=tail+numElements;
		if (t>head)
			return RING_BUFFER_ERROR;
		tail=t;
		return RING_BUFFER_OK;
	}
	

	size_t Push(T* pSrcElements, size_t numElements, int ExitMode= EXIT_ON_COMPLETED)
	{
		GetHead();
		size_t initHead=head;
		size_t count;
		size_t diff;
		clock_t t0=clock();
		size_t posSrc=0;
		while (numElements){
			GetHead();
			GetTail();
			_ASSERTE(head>=tail);
			size_t posHead=head&(size-1);
			size_t posTail=tail&(size-1);
			if (posTail<posHead || head==tail)
				diff=size-posHead; 
			else if (posHead<posTail)
				diff=posTail-posHead; 
			else if (ExitMode&EXIT_ON_FULL_BUFFER) // buffer is full
				return (head-initHead);
			else if (ExitMode&EXIT_ON_TIMEOUT){
				if ((clock()-t0)>timeout*(CLOCKS_PER_SEC/1000))
					return (head-initHead);	
				Sleep(time2sleep);
				continue;
			} else {
				Sleep(time2sleep);
				continue;
			}
			
			count=MIN(numElements,diff);
			if (push_memcpy((void*)data_addr,posHead*bytesizeof(T),pSrcElements,posSrc*bytesizeof(T),count*bytesizeof(T))){
				head+=count;
				posSrc+=count;
				numElements -=count;
				SetHead();
				GetHead();
			}
			
		}
		return (head-initHead);
	}
	
	
	/*
	void PushRequest(T* pSrcElements, size_t numElements)
	{
		GetHead();
		GetTail();
		size_t posHead;
		size_t posTail;
		size_t diff=0;
		while(diff==0){
			posHead=head&(size-1);
			posTail=tail&(size-1);
			if (posTail<posHead || head==tail)
				diff=size-posHead; 
			else if (posHead<posTail)
				diff=posTail-posHead; 
			else { // buffer is full
				Sleep(time2sleep);
				continue;
			} 
		}
		dma_ptr =pSrcElements;
		dma_left =numElements;
		dma_size =MIN(dma_left,diff);
		dma_init(data_addr+posHead*sizeof_T,pSrcElements,dma_size*sizeof_T);
	}

	bool isPushCompleted()
	{
		SetHead();
		if (dma_left==0)
			return true;
		if (dma_check())
			return false;
		
		head     +=dma_size;
		dma_ptr  +=dma_size;
		dma_left -=dma_size;
		SetHead();
		if (dma_left){
			PushRequest(dma_ptr,dma_left);
			return false;
		}
		return true;
			
	}
	
	*/
		
	
	
	
	size_t Pop(T* pDstElements, size_t numElements, int ExitMode= EXIT_ON_COMPLETED)
	{
		GetTail();
		size_t initTail=tail;
		size_t count;
		size_t diff;
		clock_t t0=clock();
		size_t posDst=0;
		while (numElements){
			//GetTail();
			GetHead();
			size_t posHead=head&(size-1);
			size_t posTail=tail&(size-1);
			if (posTail<posHead )
				diff=posHead-posTail; 
			else if (posHead<=posTail && head!=tail)
				diff=size-posTail; 
			else if (ExitMode&EXIT_ON_EMPTY_BUFFER) // buffer is empty
				return (tail-initTail);	
			else if (ExitMode&EXIT_ON_TIMEOUT){
				if ((clock()-t0)>timeout)
					return (tail-initTail);	
				Sleep(time2sleep);
				continue;
			} else {
				Sleep(time2sleep);
				continue;
			}
			
			count=MIN(numElements,diff);
			pop_memcpy(pDstElements,posDst*bytesizeof(T),(const void*)(data_addr),posTail*bytesizeof(T),count*bytesizeof(T));
			tail+=count;
			posDst+=count;
			numElements -=count;
			SetTail();
		}
		return (tail-initTail);
	}
	
	size_t View(T* pDstElements, size_t numElements, int ExitMode= EXIT_ON_COMPLETED)
	{
		GetTail();
		size_t initTail=tail;
		size_t count;
		size_t diff;
		clock_t t0=clock();
		size_t posDst=0;
		while (numElements){
			//GetTail();
			GetHead();
			size_t posHead=head&(size-1);
			size_t posTail=tail&(size-1);
			if (posTail<posHead )
				diff=posHead-posTail; 
			else if (posHead<=posTail && head!=tail)
				diff=size-posTail; 
			else if (ExitMode&EXIT_ON_EMPTY_BUFFER){ // buffer is empty
				size_t ret=tail-initTail;
				tail=initTail;
				return ret;	
			}
			else if (ExitMode&EXIT_ON_TIMEOUT){
				if ((clock()-t0)>timeout){
					size_t ret=tail-initTail;
					tail=initTail;
					return ret;	
				}
				Sleep(time2sleep);
				continue;
			} else {
				Sleep(time2sleep);
				continue;
			}

			count=MIN(numElements,diff);
			pop_memcpy(pDstElements,posDst*bytesizeof(T),(const void*)data_addr,posTail*bytesizeof(T),count*bytesizeof(T));
			tail+=count;
			posDst+=count;
			numElements -=count;
			//SetTail();
		}
		size_t ret=tail-initTail;
		tail=initTail;
		return ret;	
	}

	

};


#endif
