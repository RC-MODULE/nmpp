

template <int K> void* nmppsMalloc(int size);
template<> void* nmppsMalloc<8>(int size) { return nmppsMalloc_8s(size); }
template<> void* nmppsMalloc<16>(int size){ return nmppsMalloc_16s(size); }
template<> void* nmppsMalloc<32>(int size){ return nmppsMalloc_32s(size); }
template<> void* nmppsMalloc<64>(int size){ return nmppsMalloc_64s(size);}

#define XNM_TYPE(x) nm##x##s
#define NM_TYPE(x) XNM_TYPE(x)

#define xnmppsMalloc(bits,size) nmppsMalloc_##bits##s(size)
#define  nmppsMalloc(bits,size) xnmppsMalloc(bits,size)

#define xnmppsSet(bits,buf,val,size)  nmppsSet_##bits##s(buf,val,size)
#define  nmppsSet(bits,buf,val,size) xnmppsSet(bits,buf,val,size)

#define xnmppsCrcAcc(bits,src,size,crc)  nmppsCrcAcc_##bits##s(src,size, crc)
#define  nmppsCrcAcc(bits,src,size,crc) xnmppsCrcAcc(bits,src,size,crc)

#define xnmppsRandUniform(bits,buf,size)  nmppsRandUniform_##bits##s(buf,size)
#define  nmppsRandUniform(bits,buf,size) xnmppsRandUniform(bits,buf,size)


inline int SIZE32(int bits, int size) {
	switch (bits){
		case(64):
			return size << 1;
		case(32):
			return size ;
		case(16):
			return size >>1;
		case(8):
			return size >>2;
		case(4):
			return size >>3;
	}
	return 0;
}

inline int DIM(int bits) {
	switch (bits) {
	case(64):
		return 1;
	case(32):
		return 2;
	case(16):
		return 4;
	case(8):
		return 8;
	case(4):
		return 16;
	case(2):
		return 32;
	case(1):
		return 64;
	}
	return 0;
}

#include "stdio.h"
inline void dump(int bits,void* buf, int height, int width){
	unsigned *p=(unsigned*)buf;
	switch(bits){
		case(64):
			for(int y=0,i=0; y<height; y++){
				for(int x=0; x<width; x++){
					unsigned lo=nmppsGet_32u(p,i++);
					unsigned hi=nmppsGet_32u(p,i++);
					printf("%08X%08X", hi,lo);
				}
				printf("\n");
			}
			break;
		
		case(32):
			for(int y=0,i=0; y<height; y++){
				for(int x=0; x<width; x++){
					unsigned val=nmppsGet_32u(p,i++);
					printf("%08X ", val);
				}
				printf("\n");
			}
			break;
			
		case(16):
			for(int y=0, i=0; y<height; y++){
				for(int x=0; x<width; x++,i++){
					unsigned val=nmppsGet_16u((nm16u*)buf,i);
					printf("%04X ", val);
				}
				printf("\n");
			}
			break;
		case(8):
			for(int y=0, i=0; y<height; y++){
				for(int x=0; x<width; x++,i++){
					unsigned val=nmppsGet_8u((nm8u*)buf,i);
					printf("%02X ", val);
				}
				printf("\n");
			}
			break;
	}
}