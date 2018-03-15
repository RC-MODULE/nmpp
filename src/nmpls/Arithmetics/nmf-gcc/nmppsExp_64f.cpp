
#include "math.h"
#include "nmtype.h"

#define ALL_FPU( instr ) 	"fpu 0 " instr "\n\t" \
							"fpu 1 " instr "\n\t" \
							"fpu 2 " instr "\n\t" \
							"fpu 3 " instr "\n\t"

extern "C" __attribute__ ((section(".text_int")))
void nmppsExp_64f(const nm64f *pSrcVec, nm64f *pDstVec, int nSize)
{
	if ( nSize <4 ){
		static double b4[4]={1,1,1,1};
		double o4[4];
		int i;
		for (i=0;i<nSize;i++)
			b4[i]=pSrcVec[i];
		nmppsExp_64f( o4, b4, 4 );//	рекурсия!
		for (i=0;i<nSize;i++)
			pDstVec[i]=o4[i];
		return;
	}

	static const double coeffs[61]= {
			//	vreg5
			0.0, 1.442695040888963407, //	1/ln(2)
			double( 512.0), double( 512.0), pow(2.0, 512), pow(2.0, -512), //     2^9 = 512
			double( 256.0), double( 256.0), pow(2.0, 256), pow(2.0, -256), //     2^8 = 256
			double( 128.0), double( 128.0), pow(2.0, 128), pow(2.0, -128), //     2^7 = 128
			0.0, log(2.0), 1.0,
			0.5,									//	1/ 2!
			0.16666666666666666666666666666667,		//	1/ 3!
			0.04166666666666666666666666666667,		//	1/ 4!
			0.00833333333333333333333333333333,		//	1/ 5!
			0.00138888888888888888888888888889,		//	1/ 6!
			1.984126984126984126984126984127e-4,	//	1/ 7!
			2.4801587301587301587301587301587e-5,	//	1/ 8!
			2.7557319223985890652557319223986e-6,	//	1/ 9!
			2.7557319223985890652557319223986e-7,	//	1/10!
			2.5052108385441718775052108385442e-8,	//	1/11!
			2.0876756987868098979210090321201e-9,	//	1/12!
			1.6059043836821614599392377170155e-10,	//	1/13!
			1.1470745597729724713851697978682e-11,	//	1/14!
			7.6471637318198164759011319857881e-13,	//	1/15!
			//	vreg6
			1.0,
			double( 64.0 ), double( 64.0 ), pow(2.0, 64 ), pow(2.0, -64 ), //     2^6 = 64
			double( 32.0 ), double( 32.0 ), pow(2.0, 32 ), pow(2.0, -32 ), //     2^5 = 32
			double( 16.0 ), double( 16.0 ), pow(2.0, 16 ), pow(2.0, -16 ), //     2^4 = 16
			double( 8.0  ), double( 8.0  ), pow(2.0, 8  ), pow(2.0, -8  ), //     2^3 = 8
			double( 4.0  ), double( 4.0  ), pow(2.0, 4  ), pow(2.0, -4  ), //     2^2 = 4
			double( 2.0  ), double( 2.0  ), pow(2.0, 2  ), pow(2.0, -2  ), //     2^1 = 2
			double( 1.0  ), double( 1.0  ), pow(2.0, 1  ), pow(2.0, -1  ), //     2^0 = 1
            double( 1e100 )               // err
	};
	const double* cfs= coeffs;
	asm( "fpu 0  rep 31 vreg5= [%0++];  \n\t"
		 "fpu 1  vreg5= fpu 0  vreg5;  \n\t"
		 "fpu 2  vreg5= fpu 1  vreg5;  \n\t"
		 "fpu 3  vreg5= fpu 2  vreg5;  \n\t"
		 "fpu 0  rep 29 vreg6= [%0++];  \n\t"
		 "fpu 1  vreg6= fpu 0  vreg6;  \n\t"
		 "fpu 2  vreg6= fpu 1  vreg6;  \n\t"
		 "fpu 3  vreg6= fpu 2  vreg6;"
			: "+a" (cfs) : "m"(*coeffs) );

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
				//		double x= arg[n];
		asm ( 	"vlen = %1;  							\n\t"
				"fpu 0 rep vlen vreg1= [%0++]; 			\n\t"
				"fpu 1 rep vlen vreg1= [%0++]; 			\n\t"
				"fpu 2 rep vlen vreg1= [%0++]; 			\n\t"
				"vlen = %2;                    			\n\t"
				"fpu 3 rep vlen vreg1= [%0++]; 			\n\t"
				//		double res= 1;
				//		double res2= 1;
				//		double taylor= 1;
				//		double mac= 1;
				//		x /= log(2);
				//		double xx=fabs(x);
					//  	res: X*0 + 1 ->  [1,1,1,...]
				ALL_FPU (".double vreg0= vreg1 * .retrive(vreg5) + .retrive(vreg6);")
				ALL_FPU ("vreg4= vreg0;")                           //  res2
				ALL_FPU (".double vreg2= vreg1 * .retrive(vreg5);") //	1/ln(2)
				ALL_FPU (".double vreg2= /vreg2/;")
					: "+a" (pSrcVec)
					: "g"(len0), "g"(len1)
					  , "m"(*pSrcVec) );

		//		for (i=10;i>=0;i--){
		//			int pw=1<<i;
		//			double pp = pow(2.0,pw);
		//			double pm = pow(0.5,pw);
		//			double tr_h= pw;
		//			double m= xx -tr_h;
		//			if ( m>0 ){
		//			 	xx = m;
		//				res *= pp;
		//				res2 *= pm;
		//			}
		//		}
		int i;
		for (i=0; i<3; i++){	//	брать константы из vreg5
			asm ( 	ALL_FPU (".double vreg2 - .retrive(vreg5), set mask if >;")
					ALL_FPU (".double vreg2= mask ?   vreg2 - .retrive(vreg5) : vreg2;")
					ALL_FPU (".double vreg0= mask ?   vreg0 * .retrive(vreg5) : vreg0;")
					ALL_FPU (".double vreg4= mask ?   vreg4 * .retrive(vreg5) : vreg4;")
						: "+a" (cfs) );	//	провязываем инструкции зависимостями
		}
		for (i=0; i<7; i++){	//	брать константы из vreg6
			asm ( 	ALL_FPU (".double vreg2 - .retrive(vreg6), set mask if >;")
					ALL_FPU (".double vreg2= mask ?   vreg2 - .retrive(vreg6) : vreg2;")
					ALL_FPU (".double vreg0= mask ?   vreg0 * .retrive(vreg6) : vreg0;")
					ALL_FPU (".double vreg4= mask ?   vreg4 * .retrive(vreg6) : vreg4;")
						: "+a" (cfs) );	//	провязываем инструкции зависимостями
		}
		//		if (x<0){
		//			x= -xx;
		//			res = res2;
		//		}
		//		else
		//			x= xx;
		//		x *= log(2);
		//		double mac= x*x;
		//		double taylor= x +1;
		asm ( 	ALL_FPU (".double vreg1 - .retrive(vreg5), set mask if <;")
				ALL_FPU (".double vreg2= mask ?   -vreg2 : vreg2;")
				ALL_FPU (".double vreg0= mask ?   vreg4 : vreg0;")
				ALL_FPU (".double vreg2= vreg2 * .retrive(vreg5);") //	ln(2)
				ALL_FPU (".double vreg4= vreg2 * vreg2;") 			//	mac= x*x;
				ALL_FPU (".double vreg7= vreg2 + .retrive(vreg5);")	//	taylor= x +1;
					: "+a" (cfs) );
		//		for (i=2; i<16; i++){
		//			taylor += mac / factorial(i);
		//			mac *= x;
		//		}
		for (i=2; i<15; i++){
			asm ( 	ALL_FPU (".double vreg7= vreg4 * .retrive(vreg5) + vreg7;")
					ALL_FPU (".double vreg4= vreg4 * vreg2;")
						: "+a" (cfs) );
		}
		asm ( 	ALL_FPU (".double vreg7= vreg4 * .retrive(vreg5) + vreg7;")
				ALL_FPU (".double vreg7= vreg7 * vreg0;")
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

