#include "stdio.h"
#include "nmpls.h"
#include "nmpp.h"
#include <time.h>

void* malloc32_0(unsigned sizeInt32 ){
#ifdef __NM__
	return malloc(sizeInt32);
#else
	return malloc(sizeInt32*4);
#endif
}
void* malloc32_1(unsigned sizeInt32 ){
#ifdef __NM__
	return malloc1(sizeInt32);
#else
	return malloc(sizeInt32*4);
#endif
}
void* malloc32_2(unsigned sizeInt32 ){
#ifdef __NM__
	return malloc2(sizeInt32);
#else
	return malloc(sizeInt32*4);
#endif
}
void* malloc32_3(unsigned sizeInt32 ){
#ifdef __NM__
	return malloc3(sizeInt32);
#else
	return malloc(sizeInt32*4);
#endif
}

void free32(void* p){
	return free(p);
}

//extern "C" int printf_( const char* format,...);



	int srcA[4]={1,2,3,4};
	int srcB[4]={2,3,4,5};
	int dst[4]={-1,-1,1,1};
	
extern "C"	{
 inline void vec_add(int* pA, int* pB, int* pC, int rep){
	asm(
		"\n\t"	
		"sir=080000000h; \n\t"
		"nb1=sir; \n\t"
		
		"rep %7 data=[ar0++gr0] with data; \n\t"
		"rep %7 data=[%1++] with afifo+data; \n\t"
		"rep %7 [%2++]=afifo ; \n\t"
		
		: "+RA0"(pA),"+a"(pB),"+a"(pC),"=m"(*pC) 
		: "m"(*pA), "m"(*pB), "RG0"(2), "i"(rep)
	);
}
};
int main()
{
	
	for(int i=0; i<10; i++){
	int *pA=srcA;
	int *pB=srcB;
	int *pC=dst;

	//	asm(
	//	"\n\t"	
	//	"sir=080000000h; \n\t"
	//	"nb1=sir; \n\t"
	//	
	//	"rep %7 data=[ar0++gr0] with data; \n\t"
	//	"rep %7 data=[%1++] with afifo+data; \n\t"
	//	"rep %7 [%2++]=afifo ; \n\t"
	//	
	//	: "+RA0"(pA),"+a"(pB),"+a"(pC),"=m"(*pC) 
	//	: "m"(*pA), "m"(*pB), "RG0"(2), "i"(2)
	//);
	
		vec_add(pA,pB,pC,10);
	}
	
	
	return dst[0];

					  
	
	
	
}
