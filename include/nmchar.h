#ifndef NMCHAR
#define NMCHAR

#include <stdlib.h>
#include <string.h>
//extern unsigned int crc;
#define __INLINE__ inline

class uint8ptr;
#define nmcharptr uint8ptr
class nmchar{
public:
	unsigned int *adr;
	int idx;
	__INLINE__ nmchar(){
		//adr=0;
		//idx=0;
	}
	__INLINE__ nmchar(nmchar& ch){
		adr=ch.adr;
		idx=ch.idx;
//		crc^=ch;
	}
	__INLINE__ nmchar& operator = (nmchar ch){
		unsigned char val=(ch);
		(*adr) &= ~(0xFF<<(idx*8));
		(*adr) |= (val) <<(idx*8);
//		crc^=ch;
		//adr=ch.adr;
		//idx=ch.idx;
		return *this;
	}
	__INLINE__ unsigned int operator + (nmchar& ch){
		unsigned int a=(ch);
		unsigned int b=(*this);
		a+=b;
//		crc^=a;
		return a;
	}

	__INLINE__ nmchar& operator = (unsigned int val){
		(*adr) &= ~(0xFF<<(idx*8));
		(*adr) |= (val&0xFF) <<(idx*8);
//		crc^=val;
		return *this;
	}
	__INLINE__ operator unsigned char(){
		unsigned char ret=((*adr)>>(idx*8));
		ret&=0xFF;
//		crc^=ret;
		return ret;
	}
	
	__INLINE__ uint8ptr operator &();

};



class uint8ptr {
public:
	unsigned int *addr;
	int indx;
	nmchar arref;
	__INLINE__ uint8ptr (){
		addr=0;
		indx=0;
	}
	//uint8ptr(uint8ptr& p){
	//	indx=p.indx;
	//	addr=p.addr;
	//}

	//uint8ptr(uint8ptr& p){
	//	indx=p.indx;
	//	addr=p.addr;
	//}
	
	__INLINE__ unsigned char* x86addr(){
		return ((unsigned char*)addr)+indx;
	}
	__INLINE__ uint8ptr (void* p){
		addr=(unsigned int*)p;
		indx=0;
	}
	__INLINE__ uint8ptr (unsigned char* p){
		addr=(unsigned int*)p;
		indx=0;
	}
	__INLINE__ uint8ptr (const unsigned char* p){
		addr=(unsigned int*)p;
		indx=0;
	}
	__INLINE__ uint8ptr (char* p){
		addr=(unsigned int*)p;
		indx=0;
	}

	__INLINE__ uint8ptr(const uint8ptr& p){
		indx=p.indx;
		addr=p.addr;
	}
	//uint8ptr(int* p){
	//	addr=(unsigned*)p;
	//	indx=0;
	//}
	__INLINE__ uint8ptr(unsigned int*p){
		addr=p;
		indx=0;
	}
	__INLINE__ uint8ptr(unsigned int*p,int offset){
		addr=p+(offset>>2);
		indx=offset&3;
	}

	//operator int(){
	//	return int(addr);
	//}

	__INLINE__ nmchar& operator [](int idx){
		
		arref.adr=addr+(indx+idx)/4;
		arref.idx=(indx+idx)%4;
		return arref;
	}
	
	//uint8ptr& operator = (unsigned ptr){
	//	addr=(unsigned*)ptr;
	//	indx=0;
	//	return (*this);
	//}


	__INLINE__ uint8ptr& operator = (unsigned int* ptr){
		addr=(unsigned*)ptr;
		indx=0;
		return (*this);
	}
	
	__INLINE__ bool operator < (uint8ptr ptr){
		if (addr<ptr.addr)
			return 1;
		if (addr==ptr.addr)
			if (indx<ptr.indx)
				return 1;
		return 0;
	}
	__INLINE__ bool operator > (uint8ptr ptr){
		if (addr>ptr.addr)
			return true;
		if (addr==ptr.addr)
			if (indx>ptr.indx)
				return false;
		return 0;
	}
	
	__INLINE__ bool operator >= (uint8ptr ptr){
		if (addr>ptr.addr)
			return 1;
		if (addr==ptr.addr)
			if (indx>=ptr.indx)
				return 1;
		return 0;
	}
	

	__INLINE__ int operator - (uint8ptr ptr){
	  
		

#ifdef __NM__
		int a=(int)addr;
		int b=(int)ptr.addr;
		//a&=0x0FFFFFFF;
		//b&=0x0FFFFFFF;
		a<<=2;
		b<<=2;
		a+=indx;
		b+=ptr.indx;
		return a-b;
#else
		//a+=indx;
		//b+=ptr.indx;
		return addr-ptr.addr+indx-ptr.indx;
#endif		
	}

	
//	uint8ptr& operator = (unsigned char* ptr){
//		addr=(unsigned int*)ptr;
//		indx=0;
//		return (*this);
//	}
	
	
	
	__INLINE__ uint8ptr& operator = (const uint8ptr& p){
		addr=p.addr;
		indx=p.indx;
		return (*this);
	}

	__INLINE__ unsigned int* ptr(){
		if (indx==0)
			return addr;
		//}
		else {
			int g=1;
			return (unsigned int*)-1;
		}
	}
	__INLINE__ nmchar& operator *(){

		return (nmchar&)(*this);
	}

/*
uint8ptr operator + (int idx){
uint8ptr tmp(*this);
tmp.addr=addr+(indx+idx)/4;
tmp.indx=(indx+idx)&0x3;
return tmp;
}

uint8ptr operator- (int idx){
uint8ptr tmp(*this);
tmp.addr=addr+(indx-idx)/4;
tmp.indx=(indx-idx)&0x3;
return tmp;
}

uint8ptr& operator+= (int idx){
addr=addr+(indx+idx)/4;
indx=(indx+idx)&0x3;
return *this;
}

uint8ptr& operator-= (int idx){
addr=addr+(indx-idx)/4;
indx=(indx-idx)&0x3;
return *this;
}
*/
	__INLINE__ uint8ptr operator + (int idx){
		uint8ptr tmp(*this);
		tmp.addr=addr+((indx+idx)>>2);
		tmp.indx=(indx+idx)&0x3;
		return tmp;
	}

	__INLINE__ uint8ptr operator- (int idx){
		uint8ptr tmp(*this);
		tmp.addr=addr+((indx-idx)>>2);
		tmp.indx=(indx-idx)&0x3;
		return tmp;
	}


	__INLINE__ uint8ptr& operator+= (int idx){
		addr=addr+((indx+idx)>>2);
		indx=(indx+idx)&0x3;
		return *this;
	}

	__INLINE__ uint8ptr& operator-= (int idx){
		addr=addr+((indx-idx)>>2);
		indx=(indx-idx)&0x3;
		return *this;
	}

	__INLINE__ uint8ptr operator++ (int){
		uint8ptr tmp(*this);
		if (indx==3){
			indx=0;
			addr++;
		} 
		else {
			indx++;
		}
		return tmp;
	}

	__INLINE__ uint8ptr& operator++ (){
		if (indx==3){
			indx=0;
			addr++;
		} 
		else {
			indx++;
		}
		return *this;
	}

	//__INLINE__ unsigned int operator== (unsigned int N){
	//	return (((unsigned int)addr)==N);
	//}
	
	__INLINE__ bool operator == (uint8ptr ptr){
		if (addr==ptr.addr && indx==ptr.indx)
			return 1;
		return 0;
	}

};

__INLINE__ uint8ptr nmchar::operator &(){
	uint8ptr p;
	p.addr=adr;
	p.indx=idx;
	return p;
}

template <int Y,int X> class nmchar2D {
public:
	uint8ptr arr;
	unsigned int data[Y*X/4];

	nmchar2D(){
	}

	uint8ptr& operator [](int idx){
		arr.addr=data+X*idx/4;
		arr.indx=0;
		return arr;
	}
	unsigned int* ptr(){
		return data;
	}
};

template<int N> class nmchar1D {
public:
	nmchar deref;
	unsigned int data[(N+3)/4];

	nmchar1D(){
	}

	__INLINE__ nmchar& operator [](int idx){
		deref.adr=data+idx/4;
		deref.idx=idx%4;
		
		return deref;
	}

	__INLINE__ operator uint8ptr(){
		uint8ptr p;
		p.addr=data;
		p.indx=0;
		return p;
	}
	__INLINE__ unsigned int* ptr(){
		return data;
	}

	
};

void free(uint8ptr& p);
//{
//	free(p.addr);
//}

void nmchar_memcpy (uint8ptr dst, uint8ptr src, unsigned int  len);
//{
//	
//	
//	#ifdef __NM__
//		memcpy((void*)dst.x86addr(), (void*)src.x86addr(),len);
//	#else
//		if (dst.indx==src.indx){
//			// copy n bytes to align pointers
//			if (dst.indx){
//				int n=4-dst.indx;
//				if (len<n)
//					n=len;
//				for(int i=0; i<n; i++){
//					*dst=*src;
//					dst++;
//					src++;
//				}
//				len-=n;
//			}
//			int words=len>>2;
//			memcpy(dst.addr, src.addr, words);
//			dst.addr+=words;
//			src.addr+=words;
//			len%=4;
//			// copy rest bytes
//			for(int i=0;i<len;i++){
//				*dst=*src;
//				dst++;
//				src++;
//			}
//		}
//		else {
//			for(int i=0; i<len; i++){
//				*dst=*src;
//				src++;
//				dst++;
//			}
//		}
//	
//	#endif
//}
//
void nmchar_memset (uint8ptr dst, int setvalue, unsigned int  len);
//{
//	
//	
//	#ifdef __NM__
//		memset((void*)dst.x86addr(), setvalue,len);
//	#else
//
//		// copy n bytes to align pointers
//		if (dst.indx){
//			int n=4-dst.indx;
//			if (len<n)
//				n=len;
//			for(int i=0; i<n; i++){
//				*dst=setvalue;
//				dst++;
//			}
//			len-=n;
//		}
//		int words=len>>2;
//		
//		setvalue&=0xFF;
//		setvalue|=(setvalue<<8);
//		setvalue|=(setvalue<<16);
//		memset(dst.addr, setvalue, words);
//		dst.addr+=words;
//		len%=4;
//		// copy rest bytes
//		setvalue&=0xFF;
//		for(int i=0;i<len;i++){
//			*dst=setvalue;
//			dst++;
//		}
//		
//	
//	#endif
//}
//

#undef __INLINE__
#endif 
