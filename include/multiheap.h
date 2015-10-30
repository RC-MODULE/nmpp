#ifndef MULTIHEAP_INCLUDED
#define MULTIHEAP_INCLUDED
typedef unsigned size_t32;
typedef unsigned size_t32;



#include "nmplv.h"


#define GUARD_BITS 0x600DB1D5
#define MAX_BUFFER32_SIZE 16*1024*1024/4 
/// класс буфер - заголовок в начале выделяемой данамической памяти 
struct S_BufferInfo{
	int 			guardInfoBits0;
	size_t32		size32Buffer;	///<< размер массива данных в буфере в 32-р словах
	S_BufferInfo*	pPrevBuffer;	///<< указатель на предыдущий буфер в списке 
	S_BufferInfo*	pNextBuffer;	///<< указатель на следующий буфер в списке 
	bool			isLocked;		///<< флаг блокировки буфера, запрещаюий его удаление с помощью Release()
	int				guardInfoBits1;

	
	/// Возвращает указатель на данные в буфере 
	int* DataBegin(){
		return ((int*)this+sizeof(S_BufferInfo)/sizeof(int));
	};

	/// Возвращает указатель на конец данных в буфере (следу)
	int* DataEnd(){
		int *p=((int*)this+sizeof(S_BufferInfo)/sizeof(int)+size32Buffer);
		return p;
	}
	/// Возвращает указатель на конечные защитные поля (2 слова)
	int* EndGuardBits(){
		return DataEnd()-2;
	}
	unsigned CheckGuardBits(){
		if (guardInfoBits0!=GUARD_BITS){
			return 0xBADB00F1;
		}
		if (guardInfoBits1!=GUARD_BITS){
			return 0xBADB00F2;
		}
		if (size32Buffer){
			int* pFinalGuardBits=EndGuardBits();
			if ((*pFinalGuardBits)!=GUARD_BITS){
				return 0xBADB00F3;
			}
			if (*(pFinalGuardBits+1)!=GUARD_BITS){
				return 0xBADB00F4;
			}
			if (size32Buffer<0)
				return 0xBADB00FF;

			if (size32Buffer>MAX_BUFFER32_SIZE)
				return 0xBADB00FE;
		}
		return 0;
	}
};


/// класс - куча
class  C_Heap{
public:
	S_BufferInfo*	pZeroBuffer;		///<< указатель на нулевой буфер в списке (c нулевым размером)
	int*			pHeapEnd;			///<< указатель на слово следуюшее за концом кучи 
	int				size32HeapAvail;	///<< размер общей свободной памяти в куче
	bool			isHeapLocked;		///<< запрещает операции с кучей 
	int				status;
	C_Heap() {
		pZeroBuffer   = 0;
		pHeapEnd      = 0;
		size32HeapAvail=0;
		isHeapLocked=false;
		status =0;
	}
	/// конструктор - создает кучу в указанной памяти
	C_Heap (void* addrHeap, size_t32 size32Heap){
		Create(addrHeap,size32Heap);
	}

	/// создает кучу в указанной памяти
	void Create( void* addrHeap, size_t32 size32Heap){
		
		pZeroBuffer= (S_BufferInfo*)addrHeap;								// начальный адрес кучи
		pZeroBuffer->pPrevBuffer=0;
		pZeroBuffer->pNextBuffer=0;
		pZeroBuffer->size32Buffer=0;
		pZeroBuffer->isLocked=true;
		pZeroBuffer->guardInfoBits0=GUARD_BITS;
		pZeroBuffer->guardInfoBits1=GUARD_BITS;

		pHeapEnd   = (int*)addrHeap+size32Heap;								// конечный адрес кучи (следующий за последним байтом кучи)
		size32HeapAvail=pHeapEnd-(int*)pZeroBuffer->DataEnd();
	}
	
	/// устанавливает принадлежность к куче
	int IsMine(void* addr){
		if ((int*)pZeroBuffer < (int*)addr && (int*)addr < pHeapEnd)
			return 1;
		return 0;
	}

	/// Возвращает объем свободной памяти в пуле в 32р. словах
	//int HeapAvail(){
	//	return (size32FreeMem-sizeof(S_BufferInfo)/sizeof(int));
	//}

	//size_t32 TotalAvail(){
	//	return size32HeapAvail;
	//}
	
	/// Возвращает максимальный размер буфера  в 32р. словах, который можно выделить в куче
	size_t32 AllocateMaxAvail(){
		int size32Max=0;
		S_BufferInfo* pBuffer=pZeroBuffer;
		for ( ; pBuffer->pNextBuffer!=0; pBuffer=pBuffer->pNextBuffer) {
			int size32Between=(int*)pBuffer->pNextBuffer - pBuffer->DataEnd();
			if (size32Between>size32Max) 
				size32Max=size32Between;
		} 
		// находимся на последнем буфере
		int size32Between=(int*)pHeapEnd - pBuffer->DataEnd();
		if (size32Between>size32Max) 
			size32Max=size32Between;
		size32Max-=sizeof(S_BufferInfo)/sizeof(int);
		return size32Max;
	}

	/// Выделяет буфер в куче
	int* Allocate(size_t32 size32Buffer){
		if (isHeapLocked) 
			return 0;
		if (size32Buffer==0)
			return 0;
		size32Buffer+=(size32Buffer&1);	// округляем вверх до четного размера
		size32Buffer+=2;					// добавляем 2 слова для защитного поля
		S_BufferInfo* pBuffer=pZeroBuffer;
		int size32Between=0;
		for(; pBuffer->pNextBuffer!=0; pBuffer=pBuffer->pNextBuffer){
			// проверяем влезает ли массив в промежуток между буферами
			size32Between=(int*)pBuffer->pNextBuffer - pBuffer->DataEnd();
			if (size32Between>=size32Buffer+sizeof(S_BufferInfo)/sizeof(int)){
				// создаем новый буфер
				S_BufferInfo* pAllocateBuffer=(S_BufferInfo*)pBuffer->DataEnd();
				// устанавливаем связи в следующем буфере
				pBuffer->pNextBuffer->pPrevBuffer=pAllocateBuffer;
				// устнавливаем связи в новом буфере
				pAllocateBuffer->pPrevBuffer=pBuffer;
				pAllocateBuffer->pNextBuffer=pBuffer->pNextBuffer;
				pAllocateBuffer->size32Buffer=size32Buffer;
				pAllocateBuffer->isLocked=false;
				// устанавливаем защитные биты
				pAllocateBuffer->guardInfoBits0=GUARD_BITS;
				pAllocateBuffer->guardInfoBits1=GUARD_BITS;
				int* guardEndBits=pAllocateBuffer->EndGuardBits();
				*guardEndBits    =GUARD_BITS;
				*(guardEndBits+1)=GUARD_BITS;			
				// устанавливаем связи в предыдущем буфере
				pBuffer->pNextBuffer=pAllocateBuffer;
				// уменьшаем сободный размер				
				size32HeapAvail-=(size32Buffer+sizeof(S_BufferInfo)/sizeof(int));

				return pAllocateBuffer->DataBegin();
			} 
		}
		// дошли до последнего буфера (у которого ->pNextBuffer=0)
		size32Between=(int*)pHeapEnd - pBuffer->DataEnd();
		if (size32Between>=size32Buffer+sizeof(S_BufferInfo)/sizeof(int)){
			// создаем новый буфер
			S_BufferInfo* pAllocateBuffer=(S_BufferInfo*)pBuffer->DataEnd();
			// устнавливаем связи в новом буфере
			pAllocateBuffer->pPrevBuffer=pBuffer;
			pAllocateBuffer->pNextBuffer=0;
			pAllocateBuffer->size32Buffer=size32Buffer;
			pAllocateBuffer->isLocked=false;
			// устанавливаем защитные биты
			pAllocateBuffer->guardInfoBits0=GUARD_BITS;
			pAllocateBuffer->guardInfoBits1=GUARD_BITS;
			int* guardEndBits=pAllocateBuffer->EndGuardBits();
			*guardEndBits    =GUARD_BITS;
			*(guardEndBits+1)=GUARD_BITS;
			// устанавливаем связи в предыдущем буфере
			pBuffer->pNextBuffer=pAllocateBuffer;
			size32HeapAvail-=(size32Buffer+sizeof(S_BufferInfo)/sizeof(int));
			// уменьшаем сободный размер				
			return pAllocateBuffer->DataBegin();
		} 
		return 0;
	}
	
	/// удаляет структуру буфера из списка 
	int ReleaseBuffer(S_BufferInfo* pDelBuffer){
		if (isHeapLocked) 
			return 0;
		if (pDelBuffer->isLocked) 
			return 0;
		if (pDelBuffer->size32Buffer==0)
			return 0;
		
		pDelBuffer->pPrevBuffer->pNextBuffer=pDelBuffer->pNextBuffer;		// связываем ссылку предыдущего буфера на следующий 
		if (pDelBuffer->pNextBuffer)										// если есть следующий
			pDelBuffer->pNextBuffer->pPrevBuffer=pDelBuffer->pPrevBuffer;	// связываем ссылку следующего буфера на предыдущий 
		size32HeapAvail+=(pDelBuffer->size32Buffer+sizeof(S_BufferInfo)/sizeof(int));
		pDelBuffer->size32Buffer=0;
		return 1;
	}
	
	/// осообождат память по адресу
	int Release(void* p){
		if (isHeapLocked) 
			return 0;
		S_BufferInfo* pDelBuffer=(S_BufferInfo*)p-1;
		return ReleaseBuffer(pDelBuffer);
	}
	
	/// блокирует указатель от удаления через Release
	void Lock(void* p){
		S_BufferInfo* pBuffer=(S_BufferInfo*)p-1;
		pBuffer->isLocked=true;
	}

	/// блокирует все указатели от удаления через Release
	void LockAll(){
		S_BufferInfo* pBuffer=pZeroBuffer->pNextBuffer;
		while (pBuffer) {
			pBuffer->isLocked=true;
			pBuffer=pBuffer->pNextBuffer;
		}
	}
	/// разблокирует все указатели для удаления через Release
	void UnlockAll(){
		S_BufferInfo* pBuffer=pZeroBuffer->pNextBuffer;
		while (pBuffer) {
			pBuffer->isLocked=false;
			pBuffer=pBuffer->pNextBuffer;
		}
	}

	/// разблокирует все указатели для удаления через Release
	void Unlock(void* p){
		S_BufferInfo* pBuffer=(S_BufferInfo*)p-1;
		pBuffer->isLocked=false;
		//numHeapLocked--;
	}

	/// удаляет все указатели из кучи
	void ReleaseAll(){
		S_BufferInfo* pBuffer=pZeroBuffer->pNextBuffer;
		if (isHeapLocked) 
			return ;
		while (pBuffer) {
			if (!pBuffer->isLocked){
				ReleaseBuffer(pBuffer);
			}
			pBuffer=pBuffer->pNextBuffer;
		}
	}
	/// Запрещает операции с кучей
	void LockHeap(){
		isHeapLocked=true;
	}
	/// Разрещает операции с кучей
	void UnlockHeap(){
		isHeapLocked=false;
	}
	int Check(){
		if (status)
			return status;

		if (pZeroBuffer->pPrevBuffer){
			status=0xBADB00F0; 
			return status;
		}
		if (pZeroBuffer->size32Buffer){
			status=0xBADB00FF; 
			return status;
		}
	//	if (status=pZeroBuffer->CheckGuardBits()){
	//		return status;
	//	}
		
		S_BufferInfo* pBuffer=pZeroBuffer->pNextBuffer;

		int AllocatedMemory=0;
		int MaxHeapSize=(int*)pHeapEnd-(int*)pZeroBuffer;
		
		for(int i=0;i<100;i++){
			if (pBuffer==0)
				break;

			
			if (!IsMine(pBuffer)){
				status =0xBADB00FA; 
				return status;
			}

			if (status=pBuffer->CheckGuardBits()){
				return status;
			}

			if (pBuffer->pPrevBuffer->pNextBuffer!=pBuffer){
				status =0xBADB00FB; 
				return status;
			}

			AllocatedMemory+=sizeof(S_BufferInfo)/sizeof(int);
			AllocatedMemory+=pBuffer->size32Buffer;
			if (AllocatedMemory>MaxHeapSize){
				status=0xBADB00FD;
				return status;
			}
			if ((int)pBuffer&1){
				status=0xBADB00FC;
				return status;
			}
			pBuffer=pBuffer->pNextBuffer;
		}
		return 0;
	}
};


#define ALLOCATE_FORWARD 1
#define ALLOCATE_BACKWARD 2
#define ALLOCATE_RANDOM 4
#define ALLOCATE_CUSTOM 8
#define MAX_NUM_BANKS 6
class C_Allocator32 {
	public: 
	void* Allocate();
	int Release();
};

class C_MultiHeap: public C_Allocator32 {
	unsigned m_z;							///< переменная для генератора случайных чисел
	unsigned m_w;							///< переменная для генератора случайных чисел
public:
	C_Heap pHeap[MAX_NUM_BANKS];			///< массив куч
	unsigned numHeaps;						///< число проининицализированных куч 
	unsigned numAllocateFails;					///< число ошибок выделения куч
	unsigned AllocateMode ;						///< порядок обхода куч при поиске свободного места
	void**  pAllocateLegend;					///< история номеров куч использованных в последних 8 Allocate 
	unsigned idxAllocateLegend;
	long long allocateHistory;
	C_MultiHeap(int Mode=ALLOCATE_FORWARD) {
		allocateHistory=0;
		numHeaps=0;
		numAllocateFails=0;
		m_z=3141516;
		m_w=3141516;
		AllocateMode=Mode;
		pAllocateLegend=0;
	}
		
	int Error(){
		return numAllocateFails;
	}
	void Mode(int mode, void** legend=0){
		
		idxAllocateLegend=0;
		pAllocateLegend=legend;
		AllocateMode=mode;
	}

	/// Генератор случайных чисел
	unsigned Rand()
	{
		m_z = 36969 * (m_z & 0xFFFF) + (m_z >> 16);
		m_w = 18000 * (m_w & 0xFFFF) + (m_w >> 16);
		return (m_z << 16) + m_w;
	}
	unsigned Rand(unsigned min, unsigned max){
		unsigned r=Rand();
		r=(r-min)%(max-min+1)+min;
		return r;

	}
	
	C_Heap& operator [](int idxHeap){
		return pHeap[idxHeap];
	}

	/// создает кучу по адресууказанного размера (полный размер со служебными данными)
	int CreateHeap(void* addrHeap, size_t32 size32Heap){
		if (numHeaps>MAX_NUM_BANKS)
			return 0;
		
		pHeap[numHeaps].Create(addrHeap,size32Heap);
		if (pHeap[numHeaps].size32HeapAvail)
			numHeaps++;
		return 1;
	}
	
	/// обходит кучи в заднном в AllocateMode порядке и выделяет память заданного размера
	void* Allocate(size_t32 size32Buffer){
		
		void *p;
		unsigned i;
		
		switch (AllocateMode){
			case ALLOCATE_FORWARD: 
				for(i=0; i<numHeaps; i++){
					p=pHeap[i].Allocate(size32Buffer);
					if (p){
						allocateHistory<<=4;
						allocateHistory|=i;
						if (pAllocateLegend){
							//pAllocateLegend[idxAllocateLegend>>3]&=~(0xFF<<((idxAllocateLegend&7)<<4));
							//pAllocateLegend[idxAllocateLegend>>3]|=~(   i<<((idxAllocateLegend&7)<<4));
							pAllocateLegend[idxAllocateLegend]=p;
							idxAllocateLegend++;
						}
						return p;
					}
				}
				numAllocateFails++;
				break;
						  
			case ALLOCATE_BACKWARD: 
				for(i=numHeaps-1; i>=0; i--){
					p=pHeap[i].Allocate(size32Buffer);
					if (p){
						allocateHistory<<=4;
						allocateHistory|=i;
						if (pAllocateLegend){
							//pAllocateLegend[idxAllocateLegend>>3]&=~(0xFF<<((idxAllocateLegend&7)<<4));
							//pAllocateLegend[idxAllocateLegend>>3]|=~(   i<<((idxAllocateLegend&7)<<4));
							pAllocateLegend[idxAllocateLegend]=p;
							idxAllocateLegend++;
						}
						return p;
					}
					
				}
				numAllocateFails++;
				break;

			case ALLOCATE_RANDOM:{
				unsigned mapAllocateFails=0;
				unsigned mapNoMemory=0xFFFFFFFF>>(32-numHeaps);
				while(mapAllocateFails!=mapNoMemory){
					i=Rand()%numHeaps;
					mapAllocateFails|=(1<<i);
					p=pHeap[i].Allocate(size32Buffer);
					if (p){
						allocateHistory<<=4;
						allocateHistory|=i;
						if (pAllocateLegend){
							//pAllocateLegend[idxAllocateLegend>>3]&=~(0xFF<<((idxAllocateLegend&7)<<4));
							//pAllocateLegend[idxAllocateLegend>>3]|=~(   i<<((idxAllocateLegend&7)<<4));
							pAllocateLegend[idxAllocateLegend]=p;
							idxAllocateLegend++;
						}
						return p;
					}
				}
				numAllocateFails++;
				break;
			}
			case ALLOCATE_CUSTOM:{
				//unsigned mapAllocateFails=0;
				//unsigned mapNoMemory=0xFFFFFFFF>>(32-numHeaps);
				//i=pAllocateLegend[idxAllocateLegend];
				//idxAllocateLegend++;
				//p=pHeap[i].Allocate(size32Buffer);
				//if (p){
				//	return p;
				//}
				//numAllocateFails++;
				return pAllocateLegend[idxAllocateLegend++];
			 }
		}		
		return 0;
	} 

	/// обходит кучи в заднном порядке и выделяет память заданного размера
	void* Allocate(size_t32 size32Buffer, int nPriorHeap0, int nPriorHeap1=-1,int nPriorHeap2=-1,int nPriorHeap3=-1,int nPriorHeap4=-1,int nPriorHeap5=-1){
		
		int* p;
		p=pHeap[nPriorHeap0].Allocate(size32Buffer);
		if (p) {
			if (pAllocateLegend){
				pAllocateLegend[idxAllocateLegend]=p;
				idxAllocateLegend++;
			}
			return p;
		}
		
		if (nPriorHeap1!=-1){
			p=pHeap[nPriorHeap1].Allocate(size32Buffer);
			if (p) {
				if (pAllocateLegend){
					pAllocateLegend[idxAllocateLegend]=p;
					idxAllocateLegend++;
				}
				return p;
			}
		}
		if (nPriorHeap2!=-1){
			p=pHeap[nPriorHeap2].Allocate(size32Buffer);
			if (p) {
				if (pAllocateLegend){
					pAllocateLegend[idxAllocateLegend]=p;
					idxAllocateLegend++;
				}
				return p;
			}

		}
		if (nPriorHeap3!=-1){
			p=pHeap[nPriorHeap3].Allocate(size32Buffer);
			if (p) {
				if (pAllocateLegend){
					pAllocateLegend[idxAllocateLegend]=p;
					idxAllocateLegend++;
				}
				return p;
			}
		}
		if (nPriorHeap4!=-1){
			p=pHeap[nPriorHeap4].Allocate(size32Buffer);
			if (p) {
				if (pAllocateLegend){
					pAllocateLegend[idxAllocateLegend]=p;
					idxAllocateLegend++;
				}
				return p;
			}

		}
		if (nPriorHeap5!=-1){
			p=pHeap[nPriorHeap5].Allocate(size32Buffer);
			if (p) {
				if (pAllocateLegend){
					pAllocateLegend[idxAllocateLegend]=p;
					idxAllocateLegend++;
				}
				return p;
			}

		}
		numAllocateFails++;
		return 0;
	} 
	/// выделяет массив в той же куче где и указатель
	void* AllocateWith(size_t32 size32Buffer, void* addrInTheSameHeap){
		for(int i=0; i<numHeaps; i++){
			if (pHeap[i].IsMine(addrInTheSameHeap)){
				void *p=pHeap[i].Allocate(size32Buffer);
				if (p) {
					if (pAllocateLegend){
						pAllocateLegend[idxAllocateLegend]=p;
						idxAllocateLegend++;
					}
					return p;
				}
			}
		}
		return 0;
	}

	/// Возвращает номер кучи к которой принадлежит адрес 
	int Which(void *addr){
		for(int i=0; i<numHeaps; i++){
			if (pHeap[i].IsMine(addr))
				return i;
		}
		return -1;
	}
	
	void Lock(void* addr){
		S_BufferInfo* pBuffer=(S_BufferInfo*)addr-1;
		pBuffer->isLocked=true;
	}
	
	int Unlock(void* addr){
		S_BufferInfo* pBuffer=(S_BufferInfo*)addr-1;
		pBuffer->isLocked=false;
		return 0;
	}

	int LockAll(){
		for(int i=0; i<numHeaps; i++){
			pHeap[i].LockAll();
		}
		return 0;
	}
	int UnlockAll(){
		for(int i=0; i<numHeaps; i++){
			pHeap[i].UnlockAll();
		}
		return 0;
	}
	int Release(void* addr){
		if (AllocateMode==ALLOCATE_CUSTOM)
			return 0;
		if (addr)
			for(int i=0; i<numHeaps; i++){
				if (pHeap[i].IsMine(addr)){
					return pHeap[i].Release(addr);
				}
			}
		return 0;
	}

	/// Удваляет все назаблокированные указатели из куч
	void ReleaseAll(){
		for(int i=0; i<numHeaps; i++){
			pHeap[i].ReleaseAll();
		}
	}

	/// Запрещает операции Allocate и Release с кучей
	void LockHeap(int idxHeap){
		pHeap[idxHeap].LockHeap();
	}
	/// Разрещает операции Allocate и Release с кучей 
	void UnlockHeap(int idxHeap){
		pHeap[idxHeap].UnlockHeap();
	}
	int Check(){
		for(int i=0; i<numHeaps; i++){
			if (pHeap[i].Check())
				return pHeap[i].status;
		}
		return 0;

	}
};
	
	
template<class T> class C_BoxVec
{
public:
	int		sizeData;
	int		sizeBox;
	int		nBorder;
	T*		pBox;
	T*		pData;
	C_MultiHeap* pHeap;

	C_BoxVec(){
		sizeBox=0;
		sizeData=0;
		nBorder=0;
		pBox=0;
		pData=0;
		pHeap=0;
	}

	C_BoxVec(T*	Data, int SizeData, int SizeBorder=0){
		pHeap=0;
		Assign(Data, SizeData, SizeBorder);
	}
	
	C_BoxVec(C_MultiHeap& MultiHeap, int SizeData, int Border=0){
		sizeData=SizeData;
		nBorder =Border;
		Allocate(MultiHeap);
	}
		
	
	T* Addr(int idx){
		return nmppsAddr_(pData,idx);
	}

	int Assign (T*	Data, int SizeData, int SizeBorder=0){
		pData	=Data;
		pBox  	=nmppsAddr_(pData,-SizeBorder);
		sizeData=SizeData;
		sizeBox =SizeData+2*SizeBorder;
	}
	T* Allocate(C_MultiHeap& MultiHeap, int SizeData, int Border=0){
		sizeData=SizeData;
		nBorder =Border;
		Allocate(MultiHeap);
	}

	T* Allocate(C_MultiHeap& MultiHeap){
		pHeap=&MultiHeap;
		pData=0;
		sizeBox =sizeData+2*nBorder;
		int sizeBox32=(int)nmppsAddr_((T*)0,sizeBox)/sizeof(int);
		pBox =(T*)MultiHeap.Allocate(sizeBox32);
		if (pBox){
			pData=nmppsAddr_(pBox,(sizeBox-sizeData)/2);
		}
		return pData;
	}

	int Release(){
		if (pBox)
			if (pHeap){
				pHeap->Release(pBox);
				pBox=0;
			}
		return 0;
	}

	~C_BoxVec() {
		if (pHeap)
			if (pBox)
				pHeap->Release(pBox);
	}
	//inline T& operator [] (int idx){
	//	return *nmppsAddr_(pData,idx);
	//}
};

#define BOX_IMG_FILL_NONE	0xF111DEAD
#define BOX_IMG_FILL_RAND	0xF1110123
#define BOX_IMG_FILL_00		0
#define BOX_IMG_FILL_01		1
#define BOX_IMG_FILL_FF		-1
template<class T> class C_BoxImg
{

public:
	int		nWidth;
	int		nHeight;
	int		sizeBox;
	int 	sizeData;
	int		nBorder;
	T*		pBox;
	T*		pData;
	C_MultiHeap* pHeap;

	C_BoxImg(){
		nWidth=0;
		nHeight=0;
		sizeBox=0;
		sizeData=0;
		nBorder=0;
		pBox=0;
		pData=0;
		pHeap=0;
	}


	C_BoxImg(C_MultiHeap& MultiHeap, int Width, int Height, int BorderHeight=0, int FillMode=BOX_IMG_FILL_FF){
		nWidth=Width;
		nHeight=Height;
		nBorder=BorderHeight;
		pBox =(T*)0;
		pData=(T*)0xcbcbcbcb;
		pHeap=0;
		if (Allocate(MultiHeap))
			Fill(FillMode);
	}
	void Lock(){
		S_BufferInfo* Info=((S_BufferInfo*)pBox)-1;
		Info->isLocked=true;
	}
	void Unlock(){
		S_BufferInfo* Info=((S_BufferInfo*)pBox)-1;
		Info->isLocked=false;
	}
	void Fill(int FillMode){
		if (FillMode==BOX_IMG_FILL_NONE)
			return;
		if (FillMode==BOX_IMG_FILL_RAND){
			nmppsRand_(pBox,sizeBox);
			return;
		}
		nmppsSet_(pBox,FillMode,sizeBox);
	}

	C_BoxImg(T*	Data, int Width, int Height, int BorderHeight=0){
		pHeap   =0;
		pData   =Data;
		nWidth  =Width;
		nHeight =Height;
		nBorder =BorderHeight;
		pBox    =nmppsAddr_(pData,-nBorder*nWidth);
		sizeData=nWidth*nHeight;
		sizeBox =sizeData+2*nBorder*nWidth;
	}
	void Init(T*	Data, int Width, int Height, int BorderHeight=0){
		pHeap   =0;
		pData   =Data;
		nWidth  =Width;
		nHeight =Height;
		nBorder =BorderHeight;
		pBox    =nmppsAddr_(pData,-nBorder*nWidth);
		sizeData=nWidth*nHeight;
		sizeBox =sizeData+2*nBorder*nWidth;
	}
	T* Addr(int y, int x){
		return nmppsAddr_(pData,y*nWidth+x);
	}

	T* Allocate(C_MultiHeap& MultiHeap, int Width, int Height, int BorderHeight=0){
		nWidth=Width;
		nHeight=Height;
		nBorder=BorderHeight;
		return Allocate(MultiHeap);
		
	}

	T* Allocate(C_MultiHeap& MultiHeap){
		if (MultiHeap.Check())
			return 0;
		pHeap   =&MultiHeap;
		pData   =0;
		sizeData=nWidth*nHeight;
		sizeBox =sizeData+2*nBorder*nWidth;
		int sizeBox32=(int)nmppsAddr_((T*)0,sizeBox)/sizeof(int);
		pBox=(T*)MultiHeap.Allocate(sizeBox32);
		if (pBox)
			pData=nmppsAddr_(pBox,(sizeBox-sizeData)/2);
		return pData;
	}
	int Release(){
		if (pHeap)
			if (pBox){
				pHeap->Release(pBox);
				pHeap=0;
				//pBox=0;
				//pData=0;

			}
		return 1;
	}
	inline T* operator [] (int idx){
		return nmppsAddr_(pData,idx);
	}
	~C_BoxImg() {
		if (pHeap)
			if (pBox)
				pHeap->Release(pBox);
	}

};
	
#endif
