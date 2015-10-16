#include "nmplv.h"
#define IMG_AT_BUFFER 1
#define WARP_AT_BUFFER 2
template<class T> class C_WarpImg
{
	bool isAllocated;
	void (*pfFree32)(void*);
public: 
	unsigned 	nWidth;
	unsigned 	nHeight;
	unsigned	warpHeight;
	T* 			pWarp;
	unsigned	nWarpSize;
	T*  		pImg;
	unsigned 	nImgSize;
	
	C_WarpImg(unsigned width, unsigned height, unsigned border, void* (*malloc32)(unsigned ), void (*free32)(void*)){
		nWidth=width;
		nHeight=height;
		nImgSize =width*height;
		warpHeight=height+2*border;
		nWarpSize=width*warpHeight;
		pImg=0;
		isAllocated=false;
		pWarp=(T*)malloc32(VEC_Size32(pWarp,nWarpSize));
		pfFree32=free32;
		if (pWarp){
			pImg=VEC_Addr(pWarp,border*width);
			isAllocated=true;
		}
	}
	
	C_WarpImg(unsigned width, unsigned height, unsigned border, void* buffer, int mode=IMG_AT_BUFFER){
		nWidth=width;
		nHeight=height;
		nImgSize =width*height;
		warpHeight=height+2*border;
		nWarpSize=width*warpHeight;

		isAllocated=false;
		if (mode==WARP_AT_BUFFER){
			pWarp=(T*)buffer;
			pImg=VEC_Addr(pWarp,border*width);
		}
		if (mode==IMG_AT_BUFFER){
			pImg =(T*)buffer;
			pWarp=(T*)VEC_Addr(pImg,-border*width);
		}
	}
	
	T* addr(int x, int y){
		return VEC_Addr(pImg,y*nWidth+x);
	}
	T* end(){
		return VEC_Addr(pWarp,nWarpSize);
	}

	~C_WarpImg(){
		if (isAllocated){
			pfFree32(pWarp);
	}
}
	

};

