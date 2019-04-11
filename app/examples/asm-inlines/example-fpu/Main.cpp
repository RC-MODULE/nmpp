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
	
	
int main()
{
	
	int *pA=srcA;
	int *pB=srcB;
	int *pC=dst;

		asm(
		"\n\t"	
		"sir=080000000h; \n\t"
		"nb1=sir; \n\t"
		"rep 1 data=[%0++] with data; \n\t"
		"rep 1 data=[%1++] with afifo+data; \n\t"
		"rep 1 [%2++]=afifo ; \n\t"
		
		: "+a"(pA),"+a"(pB),"+a"(pC),"=m"(*pC) 
		: "m"(*pA), "m"(*pB)
	);

	
	
	return dst[0];

					  
	
	
	
}
