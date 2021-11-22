
#include <math.h>
#include "nmtype.h"
#include "macros_fpu.h"

static const float coeffs[68]= {
           //  константы для
           //
           //    for (i=11;i>=0;i--){
           //        int pw=1<<i;
           //        float tr_h= pow( 2.0, pw );
           //        if ( x>tr_h ){            константа 1 - tr_h
           //            x /= tr_h;            константа 2 - 1/tr_h
           //            res += pw;            константа 3 - pw
           //        }
           //    }
			DUP( 0.0f ),
			DUP(float( 1.0)), DUP(pow(2.0, 126)),  DUP(pow(2.0, 126)),
			DUP(pow(2.0, 64 )), DUP(pow(2.0, -64 )), DUP(pow(2.0, -64 )), //     2^6 = 64
			DUP(pow(2.0, 32 )), DUP(pow(2.0, -32 )), DUP(pow(2.0, -32 )), //     2^5 = 32
			DUP(pow(2.0, 16 )), DUP(pow(2.0, -16 )), DUP(pow(2.0, -16 )), //     2^4 = 16
			DUP(pow(2.0, 8  )), DUP(pow(2.0, -8  )), DUP(pow(2.0, -8  )), //     2^3 = 8
			DUP(pow(2.0, 4  )), DUP(pow(2.0, -4  )), DUP(pow(2.0, -4  )), //     2^2 = 4
			DUP(pow(2.0, 2  )), DUP(pow(2.0, -2  )), DUP(pow(2.0, -2  )), //     2^1 = 2
			DUP(pow(2.0, 1  )), DUP(pow(2.0, -1  )), DUP(pow(2.0, -1  )), //     2^0 = 1
            //     2^1/2 = sqrt(2.0))
//            DUP(float( 1.414213562373095049)), // 2^(1/2)) =sqrt(2.0)
//            DUP(float( 0.707106781186547524)), // 2^-(1/2)
//            DUP(float( 0.707106781186547524)),                  //
			DUP( 0.8f ),
			//	vreg6
			DUP( 1.0f ),
            DUP(float( 2.0)),

            DUP(float( 2.0)),
            DUP(float( 2.0)),
            DUP(float( 2.0)),
            DUP(float( 2.0)),

            DUP(nanf("")),               // NaN

            DUP(float( 1e100 ))               // err
	};

extern "C" __attribute__ ((section(".text_int")))
void nmppsDiv_32f(const nm32f *pSrcVec1, const nm32f *pSrcVec2, nm32f *pDstVec, int nSize)
{
	if (nSize<8){
		static float bx4[8]={1,1,1,1,1,1,1,1};
		static float by4[8]={1,1,1,1,1,1,1,1};
		float o4[8];
		int i;
		for (i=0;i<nSize;i++){
			bx4[i]=pSrcVec1[i];
			by4[i]=pSrcVec2[i];
		}
		nmppsDiv_32f( bx4, by4, o4, 8 );//	рекурсия!
		for (i=0;i<nSize;i++)
			pDstVec[i]=o4[i];
		return;
	}

	//	0.0, 1.0
	const float* cfs= coeffs;
	asm( 	 "fpu 0  rep 26 vreg5= [%0++];  \n\t"
			 "fpu 1  vreg5= fpu 0  vreg5;  \n\t"
			 "fpu 2  vreg5= fpu 1  vreg5;  \n\t"
			 "fpu 3  vreg5= fpu 2  vreg5;  \n\t"
			 "fpu 0  rep 7 vreg6= [%0++];  \n\t"	//	2.0
			 "fpu 1  vreg6= fpu 0  vreg6;  \n\t"
			 "fpu 2  vreg6= fpu 1  vreg6;  \n\t"
			 "fpu 3  vreg6= fpu 2  vreg6;  "
							: "+a" (cfs) : "m"(*coeffs) );

	nSize /=2;
	while (nSize>0){
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
            nSize = 0;
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

		//	READ Y
		asm ( 	"vlen = %1;  							\n\t"
				"fpu 0 rep vlen vreg0= [%0++]; 			\n\t"
				"fpu 1 rep vlen vreg0= [%0++]; 			\n\t"
				"fpu 2 rep vlen vreg0= [%0++]; 			\n\t"
				"vlen = %2;                    			\n\t"
				"fpu 3 rep vlen vreg0= [%0++]; 			\n\t"
		//   vreg7= [0,0,0,...]
					: "+a" (pSrcVec2)
					: "g"(len0), "g"(len1)
					  , "m"(*pSrcVec2) );

		asm ( 	ALL_FPU (".float vreg1 = /vreg0/;")		//	|y|
				//  	res: X*0 + 1 ->  [1,1,1,...]
				ALL_FPU (".float vreg4= vreg1 * .retrive(vreg5) + .retrive(vreg6);")
				//	Если аргумент мал (1 > y), домножаем на 2^126
				ALL_FPU (".float vreg1 - .retrive(vreg5), set mask if <;")
				ALL_FPU_ANTI_MASK
				ALL_FPU (".float vreg1= mask ?   vreg1 * .retrive(vreg5) : vreg1;")
				ALL_FPU (".float vreg4= mask ?   vreg4 * .retrive(vreg5) : vreg4;")
					: "+a" (cfs) : "r"(pSrcVec2), "r"(pSrcVec1) );	//	провязываем инструкции зависимостями

		//	READ X
		asm ( 	"vlen = %1;  							\n\t"
				"fpu 0 rep vlen vreg2= [%0++]; 			\n\t"
				"fpu 1 rep vlen vreg2= [%0++]; 			\n\t"
				"fpu 2 rep vlen vreg2= [%0++]; 			\n\t"
				"vlen = %2;                    			\n\t"
				"fpu 3 rep vlen vreg2= [%0++]; 			\n\t"
					: "+a" (pSrcVec1)
					: "g"(len0), "g"(len1)
					  , "m"(*pSrcVec1), "a" (cfs) );

		int i;
		//	Двигаем аргумент к единице (сверху)
		//  if  y > 2^i
		//      y = y/2^i
		//      d = d*2^i
		for (i=0; i<7; i++){
			asm ( 	ALL_FPU (".float vreg1 - .retrive(vreg5), set mask if >;")
					ALL_FPU_ANTI_MASK
					ALL_FPU (".float vreg1= mask ?   vreg1 * .retrive(vreg5) : vreg1;")
					ALL_FPU (".float vreg4= mask ?   vreg4 * .retrive(vreg5) : vreg4;")
						: "+a" (cfs) );	//	провязываем инструкции зависимостями
		}

		//	Ньютон
		//	(1/Y)0 = 1
		asm ( 	ALL_FPU (".float vreg7= - vreg1*.retrive(vreg5) +  .retrive(vreg6);")
				//ALL_FPU (".float vreg7= vreg3 * vreg1;")
					: "+a" (cfs) );	//	провязываем инструкции зависимостями
		//	(1/Y) vreg7
		//	2     vreg6
		//	Y0    vreg1
		//	(1/Y)[i+1] = (1/Y)i ( 2 - Y0*(1/Y)i)
		for (i=0; i<4; i++){
			asm ( 	ALL_FPU (".float vreg3= - vreg1*vreg7 +  .retrive(vreg6);")
					ALL_FPU (".float vreg7= vreg3 * vreg7;")
						: "+a" (cfs) );	//	провязываем инструкции зависимостями
		}

		//	Знак Y -> (X/Y)
		asm ( 	ALL_FPU (".float vreg0 + vreg0, set mask if <;") //	Знак Y
				ALL_FPU (".float vreg7= vreg7 * vreg2;")		// * X
				ALL_FPU (".float vreg7= vreg7 * vreg4;")		// / exp(Y)
				ALL_FPU (".float vreg7= mask ?   - vreg7 : vreg7;") //	Знак Y
					: "+a" (cfs) );	//	провязываем инструкции зависимостями

		//	NaN
		asm ( 	ALL_FPU (".float vreg0 + vreg0, set mask if <>0;")
				ALL_FPU_ANTI_MASK
				ALL_FPU (".float vreg7= not mask ?  vreg0 * .retrive(vreg6) : vreg7;")
					: "+a" (cfs) );	//	провязываем инструкции зависимостями

		//	WRITE
		asm ( 	"vlen = %2;  \n\t"
				"fpu 0 rep vlen [%0++] = vreg7; 	\n\t"
				"fpu 1 rep vlen [%0++] = vreg7; 	\n\t"
				"fpu 2 rep vlen [%0++] = vreg7; 	\n\t"
				"vlen = %3;                     	\n\t"
				"fpu 3 rep vlen [%0++] = vreg7; 	\n\t"
					: "+a" (pDstVec)
					  , "=m"(*pDstVec)
					: "g"(len0), "g"(len1)
					  , "a"(pSrcVec2), "a" (cfs) );
	}
	return;
}

