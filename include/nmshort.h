#ifndef NMSHORT_DEFINED
#define NMSHORT_DEFINED

#include <stdlib.h>
#include <string.h>
//extern unsigned int crc;
class uint16ptr;
class nmshort{
public:
	unsigned int *adr;
	int idx;
	inline nmshort(){
		//adr=0;
		//idx=0;
	}
	inline nmshort(nmshort& ch){
		adr=ch.adr;
		idx=ch.idx;
//		crc^=ch;
	}
	inline nmshort& operator = (nmshort ch){
		unsigned char val=(ch);
		(*adr) &= ~(0xFFFF<<(idx*16));
		(*adr) |= (val) <<(idx*16);
//		crc^=ch;
		//adr=ch.adr;
		//idx=ch.idx;
		return *this;
	}
	inline unsigned int operator + (nmshort& ch){
		unsigned int a=(ch);
		unsigned int b=(*this);
		a+=b;
//		crc^=a;
		return a;
	}

	inline nmshort& operator = (unsigned int val){
		(*adr) &= ~(0xFFFF<<(idx*16));
		(*adr) |= (val&0xFFFF) <<(idx*16);
//		crc^=val;
		return *this;
	}
	inline operator unsigned char(){
		unsigned char ret=((*adr)>>(idx*4));
		ret&=0xFF;
//		crc^=ret;
		return ret;
	}
	
	inline uint16ptr operator &();

};



class uint16ptr {
public:
	unsigned int *addr;
	int indx;
	nmshort arref;
	inline uint16ptr (){
		addr=0;
		indx=0;
	}
	//uint16ptr(uint16ptr& p){
	//	indx=p.indx;
	//	addr=p.addr;
	//}

	//uint16ptr(uint16ptr& p){
	//	indx=p.indx;
	//	addr=p.addr;
	//}
	
	inline unsigned char* x86addr(){
		return ((unsigned char*)addr)+indx;
	}
	inline uint16ptr (void* p){
		addr=(unsigned int*)p;
		indx=0;
	}
	inline uint16ptr (unsigned short* p){
		addr=(unsigned int*)p;
		indx=0;
	}
	inline uint16ptr (short* p){
		addr=(unsigned int*)p;
		indx=0;
	}

	inline uint16ptr(const uint16ptr& p){
		indx=p.indx;
		addr=p.addr;
	}
	//uint16ptr(int* p){
	//	addr=(unsigned*)p;
	//	indx=0;
	//}
	inline uint16ptr(unsigned int*p){
		addr=p;
		indx=0;
	}
	inline uint16ptr(unsigned int*p,int offset){
		addr=p+(offset>>1);
		indx=offset&1;
	}

	//operator int(){
	//	return int(addr);
	//}

	inline nmshort& operator [](int idx){
		
		arref.adr=addr+(indx+idx)/2;
		arref.idx=(indx+idx)%2;
		return arref;
	}
	
	//uint16ptr& operator = (unsigned ptr){
	//	addr=(unsigned*)ptr;
	//	indx=0;
	//	return (*this);
	//}


	inline uint16ptr& operator = (unsigned int* ptr){
		addr=(unsigned*)ptr;
		indx=0;
		return (*this);
	}
	
	inline bool operator < (uint16ptr ptr){
		if (addr<ptr.addr)
			return 1;
		if (addr==ptr.addr)
			if (indx<ptr.indx)
				return 1;
		return 0;
	}
	
	inline bool operator >= (uint16ptr ptr){
		if (addr>ptr.addr)
			return 1;
		if (addr==ptr.addr)
			if (indx>=ptr.indx)
				return 1;
		return 0;
	}
	

	inline int operator - (uint16ptr ptr){
		int a=(int)addr;
		int b=(int)ptr.addr;

#ifdef __NM__
		//a&=0x0FFFFFFF;
		//b&=0x0FFFFFFF;
		a<<=1;
		b<<=1;
#endif
		a+=indx;
		b+=ptr.indx;
		return a-b;
	}

	
//	uint16ptr& operator = (unsigned char* ptr){
//		addr=(unsigned int*)ptr;
//		indx=0;
//		return (*this);
//	}
	
	
	
	inline uint16ptr& operator = (const uint16ptr& p){
		addr=p.addr;
		indx=p.indx;
		return (*this);
	}

	inline unsigned int* ptr(){
		if (indx==0)
			return addr;
		//}
		else {
			int g=1;
			return (unsigned int*)-1;
		}
	}
	inline nmshort& operator *(){

		return (nmshort&)(*this);
	}

/*
uint16ptr operator + (int idx){
uint16ptr tmp(*this);
tmp.addr=addr+(indx+idx)/2;
tmp.indx=(indx+idx)&0x1;
return tmp;
}

uint16ptr operator- (int idx){
uint16ptr tmp(*this);
tmp.addr=addr+(indx-idx)/2;
tmp.indx=(indx-idx)&0x1;
return tmp;
}

uint16ptr& operator+= (int idx){
addr=addr+(indx+idx)/2;
indx=(indx+idx)&0x1;
return *this;
}

uint16ptr& operator-= (int idx){
addr=addr+(indx-idx)/2;
indx=(indx-idx)&0x1;
return *this;
}
*/
	inline uint16ptr operator + (int idx){
		uint16ptr tmp(*this);
		tmp.addr=addr+((indx+idx)>>1);
		tmp.indx=(indx+idx)&0x1;
		return tmp;
	}

	inline uint16ptr operator- (int idx){
		uint16ptr tmp(*this);
		tmp.addr=addr+((indx-idx)>>1);
		tmp.indx=(indx-idx)&0x1;
		return tmp;
	}


	inline uint16ptr& operator+= (int idx){
		addr=addr+((indx+idx)>>1);
		indx=(indx+idx)&0x1;
		return *this;
	}

	inline uint16ptr& operator-= (int idx){
		addr=addr+((indx-idx)>>1);
		indx=(indx-idx)&0x1;
		return *this;
	}

	inline uint16ptr operator++ (int){
		uint16ptr tmp(*this);
		if (indx==1){
			indx=0;
			addr++;
		} 
		else {
			indx++;
		}
		return tmp;
	}

	inline uint16ptr& operator++ (){
		if (indx==1){
			indx=0;
			addr++;
		} 
		else {
			indx++;
		}
		return *this;
	}

	inline unsigned int operator== (unsigned int N){
		return (((unsigned int)addr)==N);
	}
	
	inline bool operator == (uint16ptr ptr){
		if (addr==ptr.addr && indx==ptr.indx)
			return 1;
		return 0;
	}

};

inline uint16ptr nmshort::operator &(){
	uint16ptr p;
	p.addr=adr;
	p.indx=idx;
	return p;
}

template <int Y,int X> class nmshort2D {
public:
	uint16ptr arr;
	unsigned int data[Y*X/2];

	nmshort2D(){
	}

	uint16ptr& operator [](int idx){
		arr.addr=data+X*idx/2;
		arr.indx=0;
		return arr;
	}
	unsigned int* ptr(){
		return data;
	}
};
/*
template<int N> class nmshort1D {
public:
	nmshort deref;
	unsigned int data[(N+3)/4];

	nmshort1D(){
	}

	inline nmshort& operator [](int idx){
		addr=data+idx/4;
		indx=idx%4;
		return deref;
	}

	inline operator uint16ptr(){
		uint16ptr p;
		p.addr=data;
		p.indx=0;
		return p;
	}
	inline unsigned int* ptr(){
		return data;
	}

	
};
*/
inline void free(uint16ptr& p){
	free(p.addr);
}

inline void nmshort_memcpy (uint16ptr dst, uint16ptr src, unsigned int  len){
	
	
	#ifdef __NM__
		memcpy((void*)dst.x86addr(), (void*)src.x86addr(),len);
	#else
		if (dst.indx==src.indx){
			// copy n bytes to align pointers
			if (dst.indx){
				int n=4-dst.indx;
				if (len<n)
					n=len;
				for(int i=0; i<n; i++){
					*dst=*src;
					dst++;
					src++;
				}
				len-=n;
			}
			int words=len>>2;
			memcpy(dst.addr, src.addr, words);
			dst.addr+=words;
			src.addr+=words;
			len%=4;
			// copy rest bytes
			for(int i=0;i<len;i++){
				*dst=*src;
				dst++;
				src++;
			}
		}
		else {
			for(int i=0; i<len; i++){
				*dst=*src;
				src++;
				dst++;
			}
		}
	
	#endif
}

inline void nmshort_memset (uint16ptr dst, int setvalue, unsigned int  len){
	
	
	#ifdef __NM__
		memset((void*)dst.x86addr(), setvalue,len);
	#else

		// copy n bytes to align pointers
		if (dst.indx){
			int n=4-dst.indx;
			if (len<n)
				n=len;
			for(int i=0; i<n; i++){
				*dst=setvalue;
				dst++;
			}
			len-=n;
		}
		int words=len>>2;
		
		setvalue&=0xFF;
		setvalue|=(setvalue<<8);
		setvalue|=(setvalue<<16);
		memset(dst.addr, setvalue, words);
		dst.addr+=words;
		len%=4;
		// copy rest bytes
		setvalue&=0xFF;
		for(int i=0;i<len;i++){
			*dst=setvalue;
			dst++;
		}
		
	
	#endif
}

#endif 
