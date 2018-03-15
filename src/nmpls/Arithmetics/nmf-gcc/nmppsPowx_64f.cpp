#include "nmtype.h"

extern "C" __attribute__ ((section(".text_int")))
void nmppsPowx_64f(const nm64f *pSrcVec, nm64f *pDstVec, nm32u Deg, int nSize)
{

	if (nSize<4){
		static double b4[4]={1,1,1,1};
		double o4[4];
		int i;
		for (i=0;i<nSize;i++)
			b4[i]=pSrcVec[i];
		nmppsPowx_64f( o4, b4, Deg, 4 );//	рекурси€!
		for (i=0;i<nSize;i++)
			pDstVec[i]=o4[i];
		return;
	}

	double coeffs[2]={ 0.0, 1.0 };
	double* cfs= coeffs;
	//	0.0, 1.0
	asm( "fpu 0  rep 1 vreg5= [%0++];  \n\t"
		 "fpu 0  rep 1 vreg6= [%0++];  \n\t"
		 "fpu 1  vreg5= fpu 0  vreg5;  \n\t"
		 "fpu 2  vreg5= fpu 1  vreg5;  \n\t"
		 "fpu 3  vreg5= fpu 2  vreg5;  \n\t"
		 "fpu 1  vreg6= fpu 0  vreg6;  \n\t"
		 "fpu 2  vreg6= fpu 1  vreg6;  \n\t"
		 "fpu 3  vreg6= fpu 2  vreg6;"
			: "+a" (cfs) : "m"(*coeffs) );

	while (nSize>0){
		int pp=Deg;
		int len;
		int len0;
		int len1;

		if ( nSize>48*4 ){
			len = 32;
			len0 = len-1;
			len1 = len0;
		}
		else if ( nSize<=32 ){
			len = (nSize+1)/4;
			len0 = len-1;
			len1 = nSize - len*3 -1;
		}
		else if ( nSize<=32*4 ){
			len = (nSize+3)/4;
			len0 = len-1;
			len1 = nSize - len*3 -1;
		}
		else{
			len = 16;
			len0 = len-1;
			len1 = len0;
		}

		nSize -= len*4;

		//	READ
		asm ( 	"vlen = %1;  						\n\t"
				"fpu 0 rep vlen vreg1= [%0++]; 		\n\t"
				"fpu 1 rep vlen vreg1= [%0++]; 		\n\t"
				"fpu 2 rep vlen vreg1= [%0++]; 		\n\t"
				"vlen = %2;                    		\n\t"
				"fpu 3 rep vlen vreg1= [%0++]; 		\n\t"
					: "+a" (pSrcVec)
					: "g"(len0), "g"(len1)
					  , "m"(*pSrcVec) );

		//  X*0 + 1 ->  [1,1,1,...]
		asm ( 	"fpu 0  .double vreg0= vreg1 * .retrive(vreg5) + .retrive(vreg6);\n\t"
				"fpu 1  .double vreg0= vreg1 * .retrive(vreg5) + .retrive(vreg6);\n\t"
				"fpu 2  .double vreg0= vreg1 * .retrive(vreg5) + .retrive(vreg6);\n\t"
				"fpu 3  .double vreg0= vreg1 * .retrive(vreg5) + .retrive(vreg6);\n\t"
					: "+a" (cfs) );	//	пров€зываем инструкции зависимост€ми

		while ( pp!=0 ){
			if ( pp&1 ){
				//	x^(2*i+1) = x * (x^2)^i
				asm ( 	"fpu 0  .double vreg0= vreg0 * vreg1;\n\t"
						"fpu 1  .double vreg0= vreg0 * vreg1;\n\t"
						"fpu 2  .double vreg0= vreg0 * vreg1;\n\t"
						"fpu 3  .double vreg0= vreg0 * vreg1;\n\t"
							: "+a" (cfs) );	//	пров€зываем инструкции зависимост€ми
			}
			//  x^2, x^4, x^8,...
			pp /=2;
			if (pp==0)
				break;
			asm ( 	"fpu 0  .double vreg1= vreg1 * vreg1;\n\t"
					"fpu 1  .double vreg1= vreg1 * vreg1;\n\t"
					"fpu 2  .double vreg1= vreg1 * vreg1;\n\t"
					"fpu 3  .double vreg1= vreg1 * vreg1;\n\t"
						: "+a" (cfs) );	//	пров€зываем инструкции зависимост€ми
		}


		//	WRITE
		asm ( 	"vlen = %2;  \n\t"
				"fpu 0 rep vlen [%0++] = vreg0; 	\n\t"
				"fpu 1 rep vlen [%0++] = vreg0; 	\n\t"
				"fpu 2 rep vlen [%0++] = vreg0; 	\n\t"
				"vlen = %3;                     	\n\t"
				"fpu 3 rep vlen [%0++] = vreg0; 	\n\t"
					: "+a" (pDstVec)
					  , "=m"(*pDstVec)
					: "g"(len0), "g"(len1)
					  , "a"(pSrcVec), "a" (cfs) );
	}
	return;
}

