
#include "math.h"
#include "nmtype.h"
#include "macros_fpu.h"

extern "C" __attribute__ ((section(".text_int")))
void nmppsExp_32f(const nm32f *pSrcVec, nm32f *pDstVec, int nSize)
{
	if (nSize<16){
		static float b4[16]={1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
		float o4[16];
		int i;
		for (i=0;i<nSize;i++)
			b4[i]=pSrcVec[i];
		nmppsExp_32f( b4, o4, 16 );//	рекурсия!
		for (i=0;i<nSize;i++)
			pDstVec[i]=o4[i];
		return;
	}

	static const float coeffs[122]= {
			//	vreg5
			DUP(0.0), DUP(1.442695040888963407), //	1/ln(2)
			DUP(0.0), DUP(log(2.0)),
			DUP(0.5),									//	1/ 2!
			DUP(0.16666666666666666666666666666667),		//	1/ 3!
			DUP(0.04166666666666666666666666666667),		//	1/ 4!
			DUP(0.00833333333333333333333333333333),		//	1/ 5!
			DUP(0.00138888888888888888888888888889),		//	1/ 6!
			DUP(1.984126984126984126984126984127e-4),	//	1/ 7!
			DUP(2.4801587301587301587301587301587e-5),	//	1/ 8!
			DUP(2.7557319223985890652557319223986e-6),	//	1/ 9!
			DUP(1.0),
			//	vreg6
			DUP(1.0),
			DUP(float( 64.0 )), DUP(float( 64.0 )), DUP(pow(2.0, 64 )), DUP(pow(2.0, -64 )), //     2^6 = 64
			DUP(float( 32.0 )), DUP(float( 32.0 )), DUP(pow(2.0, 32 )), DUP(pow(2.0, -32 )), //     2^5 = 32
			DUP(float( 16.0 )), DUP(float( 16.0 )), DUP(pow(2.0, 16 )), DUP(pow(2.0, -16 )), //     2^4 = 16
			DUP(float( 8.0  )), DUP(float( 8.0  )), DUP(pow(2.0, 8  )), DUP(pow(2.0, -8  )), //     2^3 = 8
			DUP(float( 4.0  )), DUP(float( 4.0  )), DUP(pow(2.0, 4  )), DUP(pow(2.0, -4  )), //     2^2 = 4
			DUP(float( 2.0  )), DUP(float( 2.0  )), DUP(pow(2.0, 2  )), DUP(pow(2.0, -2  )), //     2^1 = 2
			DUP(float( 1.0  )), DUP(float( 1.0  )), DUP(pow(2.0, 1  )), DUP(pow(2.0, -1  )), //     2^0 = 1
            DUP(float( 1e100 ))               // err
	};
	const float* cfs= coeffs;
	asm( "fpu 0  rep 13 vreg5= [%0++];  \n\t"
		 "fpu 1  vreg5= fpu 0  vreg5;  \n\t"
		 "fpu 2  vreg5= fpu 1  vreg5;  \n\t"
		 "fpu 3  vreg5= fpu 2  vreg5;  \n\t"
		 "fpu 0  rep 29 vreg6= [%0++];  \n\t"
		 "fpu 1  vreg6= fpu 0  vreg6;  \n\t"
		 "fpu 2  vreg6= fpu 1  vreg6;  \n\t"
		 "fpu 3  vreg6= fpu 2  vreg6;"
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

		//	READ
				//		float x= arg[n];
		asm ( 	"vlen = %2;  							\n\t"
				"fpu 0 rep vlen vreg1= [%0++]; 			\n\t"
				"fpu 1 rep vlen vreg1= [%0++]; 			\n\t"
				"fpu 2 rep vlen vreg1= [%0++]; 			\n\t"
				"vlen = %3;                    			\n\t"
				"fpu 3 rep vlen vreg1= [%0++]; 			\n\t"
				//		float res= 1;
				//		float res2= 1;
				//		float taylor= 1;
				//		float mac= 1;
				//		x /= log(2);
				//		float xx=fabs(x);
					//  	res: X*0 + 1 ->  [1,1,1,...]
				ALL_FPU (".float vreg0= vreg1 * .retrive(vreg5) + .retrive(vreg6);")
				ALL_FPU (".float vreg4= vreg0;")                           //  res2
				ALL_FPU (".float vreg2= vreg1 * .retrive(vreg5);") //	1/ln(2)
				ALL_FPU (".float vreg2= /vreg2/;")
					: "+a" (pSrcVec),  "+a" (cfs)
					: "g"(len0), "g"(len1)
					  , "m"(*pSrcVec) );

		//		for (i=10;i>=0;i--){
		//			int pw=1<<i;
		//			float pp = pow(2.0,pw);
		//			float pm = pow(0.5,pw);
		//			float tr_h= pw;
		//			float m= xx -tr_h;
		//			if ( m>0 ){
		//			 	xx = m;
		//				res *= pp;
		//				res2 *= pm;
		//			}
		//		}
		int i;
		for (i=0; i<7; i++){	//	брать константы из vreg6
			asm ( 	ALL_FPU (".float vreg2 - .retrive(vreg6), set mask if >;")
					ALL_FPU_ANTI_MASK
					ALL_FPU (".float vreg2= mask ?   vreg2 - .retrive(vreg6) : vreg2;")
					ALL_FPU (".float vreg0= mask ?   vreg0 * .retrive(vreg6) : vreg0;")
					ALL_FPU (".float vreg4= mask ?   vreg4 * .retrive(vreg6) : vreg4;")
						: "+a" (cfs) );	//	провязываем инструкции зависимостями
		}
		//		if (x<0){
		//			x= -xx;
		//			res = res2;
		//		}
		//		else
		//			x= xx;
		//		x *= log(2);
		//		float mac= x*x;
		//		float taylor= x +1;
		asm ( 	ALL_FPU (".float vreg1 - .retrive(vreg5), set mask if <;")
				ALL_FPU_ANTI_MASK
				ALL_FPU (".float vreg2= mask ?   -vreg2 : vreg2;")
				ALL_FPU (".float vreg0= mask ?   vreg4 : vreg0;")
				ALL_FPU (".float vreg2= vreg2 * .retrive(vreg5);") //	ln(2)
				ALL_FPU (".float vreg4= vreg2 * vreg2;") 			//	mac= x*x;
					: "+a" (cfs) );
		//		for (i=2; i<16; i++){
		//			taylor += mac / factorial(i);
		//			mac *= x;
		//		}
		asm ( 	ALL_FPU (".float vreg7= vreg4 * .retrive(vreg5);")
				ALL_FPU (".float vreg4= vreg4 * vreg2;")
					: "+a" (cfs) );
		for (i=3; i<9; i++){
			asm ( 	ALL_FPU (".float vreg7= vreg4 * .retrive(vreg5) + vreg7;")
					ALL_FPU (".float vreg4= vreg4 * vreg2;")
						: "+a" (cfs) );
		}
		asm ( 	ALL_FPU (".float vreg7= vreg4 * .retrive(vreg5) + vreg7;")
				ALL_FPU (".float vreg7= vreg7 + vreg2;")	//	taylor+ x;
				ALL_FPU (".float vreg7= vreg7 + .retrive(vreg5);")	//	taylor +1;
				ALL_FPU (".float vreg7= vreg7 * vreg0;")
					: "+a" (cfs) );

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
					  , "a"(pSrcVec), "a" (cfs) );
	}
	return;
}

