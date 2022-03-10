
#include "math.h"
#include "nmtype.h"

#define ALL_FPU( instr ) 	"fpu 0 " instr "\n\t" \
							"fpu 1 " instr "\n\t" \
							"fpu 2 " instr "\n\t" \
							"fpu 3 " instr "\n\t"

extern "C" __attribute__ ((section(".text_int")))
void nmppsLn_64f(const nm64f *pSrcVec, nm64f *pDstVec, int nSize)
{
	if (nSize<4){
		static double b4[4]={1,1,1,1};
		double o4[4];
		int i;
		for (i=0;i<nSize;i++)
			b4[i]=pSrcVec[i];
		nmppsLn_64f( o4, b4, 4 );//	рекурсия!
		for (i=0;i<nSize;i++)
			pDstVec[i]=o4[i];
		return;
	}

	static const double coeffs[65]= { double( 0.7), pow(2.0, 1022),  double( -1022.0),
           //  константы для
           //
           //    for (i=11;i>=0;i--){
           //        int pw=1<<i;
           //        double tr_h= pow( 2.0, pw );
           //        if ( x>tr_h ){            константа 1 - tr_h
           //            x /= tr_h;            константа 2 - 1/tr_h
           //            res += pw;            константа 3 - pw
           //        }
           //    }
			pow(2.0, 512), pow(2.0, -512), double( 512.0), //     2^9 = 512
			pow(2.0, 256), pow(2.0, -256), double( 256.0), //     2^8 = 256
			pow(2.0, 128), pow(2.0, -128), double( 128.0), //     2^7 = 128
			pow(2.0, 64 ), pow(2.0, -64 ), double( 64.0 ), //     2^6 = 64
			pow(2.0, 32 ), pow(2.0, -32 ), double( 32.0 ), //     2^5 = 32
			pow(2.0, 16 ), pow(2.0, -16 ), double( 16.0 ), //     2^4 = 16
			pow(2.0, 8  ), pow(2.0, -8  ), double( 8.0  ), //     2^3 = 8
			pow(2.0, 4  ), pow(2.0, -4  ), double( 4.0  ), //     2^2 = 4
			pow(2.0, 2  ), pow(2.0, -2  ), double( 2.0  ), //     2^1 = 2
			pow(2.0, 1  ), pow(2.0, -1  ), double( 1.0  ), //     2^0 = 1
            //     2^1/2 = sqrt(2.0)
            double( 1.414213562373095049), // 2^(1/2) =sqrt(2.0)
            double( 0.707106781186547524), // 2^-(1/2)
            double( nan("") ), // 2^-(1/2)
            double( 0.5),                  //    1/2
            //     2^1/4
            double( 1.189207115002721067), // 2^ (1/4)
            double( 0.840896415253714543), // 2^-(1/4)
            double( 0.25),                  //   1/4
            //     2^1/8
            double( 1.090507732665257659), // 2^ (1/8)
            double( 0.917004043204671232), // 2^-(1/8)
            double( 0.125),                //   1/8
            //     2^-1/4
            double( 0.840896415253714543), // 2^-(1/4)
            double( 1.189207115002721067), // 2^ (1/4)
            double(-0.25),                  //   1/4
            //     2^-1/8
            double( 0.917004043204671232), // 2^-(1/8)
            double( 1.090507732665257659), // 2^ (1/8)
            double(-0.125),                //   1/8

            //     ln(2)
            double( 0.693147180559945309),
            double( 1.0),

            double(-0.125),                                // -1/8
            double( 0.111111111111111111),                 //  1/9
            double(-0.1),                                  // -1/10
            double( 0.09090909090909090909),               //  1/11
            double(-0.08333333333333333333),               // -1/12
            double( 0.07692307692307692308),               //  1/13
            double(-0.07142857142857142857),               // -1/14
            double( 0.142857142857142857),                 //  1/7
            double(-0.166666666666666667),                 // -1/6
            double( 0.2),                                  //  1/5
            double(-0.25),                                 // -1/4
            double( 0.333333333333333333),                 //  1/3
            double(-0.5),                                  // -1/2

            double( 1e100 )               // err
	};
	const double* cfs= coeffs;
	//	0.0, 1.0
	asm( "fpu 0  rep 32 vreg5= [%0++];  \n\t"
		 "fpu 1  vreg5= fpu 0  vreg5;  \n\t"
		 "fpu 2  vreg5= fpu 1  vreg5;  \n\t"
		 "fpu 3  vreg5= fpu 2  vreg5;  \n\t"
		 "fpu 0  rep 32 vreg6= [%0++];  \n\t"
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

		//	Чтобы понять, что происходит, см. test.cpp, там реализация того же алгоритма
		//	на чистом С
		//	READ
		asm ( 	"vlen = %1;  							\n\t"
				"fpu 0 rep vlen vreg1= [%0++]; 			\n\t"
				"fpu 1 rep vlen vreg1= [%0++]; 			\n\t"
				"fpu 2 rep vlen vreg1= [%0++]; 			\n\t"
				"vlen = %2;                    			\n\t"
				"fpu 3 rep vlen vreg1= [%0++]; 			\n\t"
		//   vreg7= [0,0,0,...]
				ALL_FPU (".double vreg7= vreg1 - vreg1;")
					: "+a" (pSrcVec)
					: "g"(len0), "g"(len1)
					  , "m"(*pSrcVec) );

		//	NaN
		asm ( 	ALL_FPU (".float vreg1 + vreg1, set mask if >;")
				ALL_FPU (".float vreg7= not mask ?  vreg1 * .retrive(vreg6) : vreg7;")
					: "+a" (cfs) );	//	провязываем инструкции зависимостями

		//	Если аргумент мал (0.7 > х), домножаем на 2^1022
		asm ( 	ALL_FPU (".double vreg1 - .retrive(vreg5), set mask if <;")
				ALL_FPU (".double vreg1= mask ?   vreg1 * .retrive(vreg5) : vreg1;")
				ALL_FPU (".double vreg7= mask ?   vreg7 + .retrive(vreg5) : vreg7;")
					: "+a" (cfs) );	//	провязываем инструкции зависимостями
		int i;
		//	Двигаем аргумент к единице (сверху)
		//	Было бы достаточно (i=0; i<13; i++), но в vreg5 не хватает места
		for (i=0; i<9; i++){
			asm ( 	ALL_FPU (".double vreg1 - .retrive(vreg5), set mask if >;")
					ALL_FPU (".double vreg1= mask ?   vreg1 * .retrive(vreg5) : vreg1;")
					ALL_FPU (".double vreg7= mask ?   vreg7 + .retrive(vreg5) : vreg7;")
						: "+a" (cfs) );	//	провязываем инструкции зависимостями
		}
		asm ( 	ALL_FPU (".double vreg1 - .retrive(vreg5), set mask if >;")
				ALL_FPU (".double vreg1= mask ?   vreg1 * .retrive(vreg5) : vreg1;")
				ALL_FPU (".double vreg7= mask ?   vreg7 + .retrive(vreg6) : vreg7;")
					: "+a" (cfs) );	//	провязываем инструкции зависимостями
		for (i=0; i<3; i++){
			asm ( 	ALL_FPU (".double vreg1 - .retrive(vreg6), set mask if >;")
					ALL_FPU (".double vreg1= mask ?   vreg1 * .retrive(vreg6) : vreg1;")
					ALL_FPU (".double vreg7= mask ?   vreg7 + .retrive(vreg6) : vreg7;")
						: "+a" (cfs) );	//	провязываем инструкции зависимостями
		}
		//	Двигаем аргумент к единице, теперь снизу (для 0.7 < х < 1)
		for (i=0; i<2; i++){
			asm ( 	ALL_FPU (".double vreg1 - .retrive(vreg6), set mask if <;")
					ALL_FPU (".double vreg1= mask ?   vreg1 * .retrive(vreg6) : vreg1;")
					ALL_FPU (".double vreg7= mask ?   vreg7 + .retrive(vreg6) : vreg7;")
						: "+a" (cfs) );	//	провязываем инструкции зависимостями
		}

		asm ( 	ALL_FPU (".double vreg7= vreg7 * .retrive(vreg6);")//  res * log(2)
				ALL_FPU (".double vreg1= vreg1 - .retrive(vreg6);")//  x = x-1;
			    //  Taylor
			    //  x^2 x^3 и т.д. не прибавляем сразу, а придерживаем,
			    //  чтобы складывать от меньших к большим,- для лучшей точности
				ALL_FPU (".double vreg2= vreg1 * vreg1;")    // 2
			    ALL_FPU (".double vreg3= vreg2 * vreg1;")    // 3
			    ALL_FPU (".double vreg4= vreg2 * vreg2;")    // 4
			    ALL_FPU (".double vreg0= vreg4 * vreg4;")    // 8
			    ALL_FPU (".double vreg7= vreg0 * .retrive(vreg6) + vreg7;")
			    ALL_FPU (".double vreg0= vreg0 * vreg1;")    // 9
			    ALL_FPU (".double vreg7= vreg0 * .retrive(vreg6) + vreg7;")
			    ALL_FPU (".double vreg0= vreg0 * vreg1;")    // 10
			    ALL_FPU (".double vreg7= vreg0 * .retrive(vreg6) + vreg7;")
			    ALL_FPU (".double vreg0= vreg0 * vreg1;")    // 11
			    ALL_FPU (".double vreg7= vreg0 * .retrive(vreg6) + vreg7;")
			    ALL_FPU (".double vreg0= vreg0 * vreg1;")    // 12
			    ALL_FPU (".double vreg7= vreg0 * .retrive(vreg6) + vreg7;")
			    ALL_FPU (".double vreg0= vreg0 * vreg1;")    // 13
			    ALL_FPU (".double vreg7= vreg0 * .retrive(vreg6) + vreg7;")
			    ALL_FPU (".double vreg0= vreg0 * vreg1;")    // 14
			    ALL_FPU (".double vreg7= vreg0 * .retrive(vreg6) + vreg7;")
			    ALL_FPU (".double vreg0= vreg4 * vreg3;")    // 7
			    ALL_FPU (".double vreg7= vreg0 * .retrive(vreg6) + vreg7;")
			    ALL_FPU (".double vreg0= vreg3 * vreg3;")    // 6
			    ALL_FPU (".double vreg7= vreg0 * .retrive(vreg6) + vreg7;")
			    ALL_FPU (".double vreg0= vreg3 * vreg2;")    // 5
			    ALL_FPU (".double vreg7= vreg0 * .retrive(vreg6) + vreg7;")
			    ALL_FPU (".double vreg7= vreg4 * .retrive(vreg6) + vreg7;")
			    ALL_FPU (".double vreg7= vreg3 * .retrive(vreg6) + vreg7;")
			    ALL_FPU (".double vreg7= vreg2 * .retrive(vreg6) + vreg7;")
			    ALL_FPU (".double vreg7= vreg1 + vreg7;")
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
					  , "a"(pSrcVec), "a" (cfs) );
	}
	return;
}

