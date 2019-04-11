
#include "math.h"
#include "nmtype.h"
#include "macros_fpu.h"


extern "C" __attribute__ ((section(".text_int")))
void nmppsLn_32f (const nm32f *pSrcVec, nm32f *pDstVec, int nSize)
{
	if (nSize<8){
		static float b4[8]={1,1,1,1,1,1,1,1};
		float o4[8];
		int i;
		for (i=0;i<nSize;i++)
			b4[i]=pSrcVec[i];
		nmppsLn_32f( b4, o4, 8 );//	��������!
		for (i=0;i<nSize;i++)
			pDstVec[i]=o4[i];
		return;
	}

	static const float coeffs[112]= { DUP(float( 0.7)), DUP(pow(2.0, 126)),  DUP(float( -126.0)),
           //  ��������� ���
           //
           //    for (i=11;i>=0;i--){
           //        int pw=1<<i;
           //        float tr_h= pow( 2.0, pw );
           //        if ( x>tr_h ){            ��������� 1 - tr_h
           //            x /= tr_h;            ��������� 2 - 1/tr_h
           //            res += pw;            ��������� 3 - pw
           //        }
           //    }
			DUP(pow(2.0, 64 )), DUP(pow(2.0, -64 )), DUP(float( 64.0 )), //     2^6 = 64
			DUP(pow(2.0, 32 )), DUP(pow(2.0, -32 )), DUP(float( 32.0 )), //     2^5 = 32
			DUP(pow(2.0, 16 )), DUP(pow(2.0, -16 )), DUP(float( 16.0 )), //     2^4 = 16
			DUP(pow(2.0, 8  )), DUP(pow(2.0, -8  )), DUP(float( 8.0  )), //     2^3 = 8
			DUP(pow(2.0, 4  )), DUP(pow(2.0, -4  )), DUP(float( 4.0  )), //     2^2 = 4
			DUP(pow(2.0, 2  )), DUP(pow(2.0, -2  )), DUP(float( 2.0  )), //     2^1 = 2
			DUP(pow(2.0, 1  )), DUP(pow(2.0, -1  )), DUP(float( 1.0  )), //     2^0 = 1
            //     2^1/2 = sqrt(2.0))
            DUP(float( 1.414213562373095049)), // 2^(1/2)) =sqrt(2.0)
            DUP(float( 0.707106781186547524)), // 2^-(1/2)
            DUP(float( 0.5)),                  //    1/2
            //     2^1/4
            DUP(float( 1.189207115002721067)), // 2^ (1/4)
            DUP(float( 0.840896415253714543)), // 2^-(1/4)
            DUP(float( 0.25)),                  //   1/4
            //     2^1/8
            DUP(float( 1.090507732665257659)), // 2^ (1/8)
            DUP(float( 0.917004043204671232)), // 2^-(1/8)
			//	vreg6
            DUP(nanf("")),               // NaN
            DUP(float( 0.125)),                //   1/8
            //     2^-1/4
            DUP(float( 0.840896415253714543)), // 2^-(1/4)
            DUP(float( 1.189207115002721067)), // 2^ (1/4)
            DUP(float(-0.25)),                  //   1/4

            //     ln(2)
            DUP(float( 0.693147180559945309)),
            DUP(float( 1.0)),

            DUP(float( 0.142857142857142857)),                 //  1/7
            DUP(float(-0.166666666666666667)),                 // -1/6
            DUP(float( 0.2)),                                  //  1/5
            DUP(float(-0.25)),                                 // -1/4
            DUP(float( 0.333333333333333333)),                 //  1/3
            DUP(float(-0.5)),                                  // -1/2

            DUP(float( 1e100 ))               // err
	};
	const float* cfs= coeffs;
	//	0.0, 1.0
	asm( "fpu 0  rep 32 vreg5= [%0++];  \n\t"
		 "fpu 1  vreg5= fpu 0  vreg5;  \n\t"
		 "fpu 2  vreg5= fpu 1  vreg5;  \n\t"
		 "fpu 3  vreg5= fpu 2  vreg5;  \n\t"
		 "fpu 0  rep 13 vreg6= [%0++];  \n\t"
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

		//	����� ������ ��� ����, ��. log_vdc.cpp, ��� �������� ����
		//	���������� ���� �� ��������� ��� ������������ �����

		//	READ
		asm ( 	"vlen = %2;  							\n\t"
//	slow !!!    ".int 0x7fa00000						\n\t"
//	slow !!!	".int 0xf7990000						\n\t"
				"fpu 0 rep vlen vreg1= [%0++]; 			\n\t"
				"fpu 1 rep vlen vreg1= [%0++]; 			\n\t"
				"fpu 2 rep vlen vreg1= [%0++]; 			\n\t"
				"vlen = %3;                    			\n\t"
				"fpu 3 rep vlen vreg1= [%0++]; 			\n\t"
		//   vreg7= [0,0,0,...]
				ALL_FPU (".float vreg7= vreg1 - vreg1;")
					: "+a" (pSrcVec),   "+a" (cfs)
					: "g"(len0), "g"(len1)
					  , "m"(*pSrcVec) );

		//	NaN
		asm ( 	ALL_FPU (".float vreg1 + vreg1, set mask if >;")
				ALL_FPU_ANTI_MASK
				ALL_FPU (".float vreg7= not mask ?  vreg1 * .retrive(vreg6) : vreg7;")
					: "+a" (cfs) );	//	����������� ���������� �������������

		//	���� �������� ��� (0.7 > �), ��������� �� 2^126
		asm ( 	ALL_FPU (".float vreg1 - .retrive(vreg5), set mask if <;")
				ALL_FPU_ANTI_MASK
				ALL_FPU (".float vreg1= mask ?   vreg1 * .retrive(vreg5) : vreg1;")
				ALL_FPU (".float vreg7= mask ?   vreg7 + .retrive(vreg5) : vreg7;")
					: "+a" (cfs) );	//	����������� ���������� �������������
		int i;
		//	������� �������� � ������� (������)
		//	���� �� ���������� (i=0; i<13; i++), �� � vreg5 �� ������� �����
		for (i=0; i<9; i++){
			asm ( 	ALL_FPU (".float vreg1 - .retrive(vreg5), set mask if >;")
					ALL_FPU_ANTI_MASK
					ALL_FPU (".float vreg1= mask ?   vreg1 * .retrive(vreg5) : vreg1;")
					ALL_FPU (".float vreg7= mask ?   vreg7 + .retrive(vreg5) : vreg7;")
						: "+a" (cfs) );	//	����������� ���������� �������������
		}
		asm ( 	ALL_FPU (".float vreg1 - .retrive(vreg5), set mask if >;")
				ALL_FPU_ANTI_MASK
				ALL_FPU (".float vreg1= mask ?   vreg1 * .retrive(vreg5) : vreg1;")
				ALL_FPU (".float vreg7= mask ?   vreg7 + .retrive(vreg6) : vreg7;")
					: "+a" (cfs) );	//	����������� ���������� �������������

		//	������� �������� � �������, ������ ����� (��� 0.7 < � < 1)
		for (i=0; i<1; i++){
			asm ( 	ALL_FPU (".float vreg1 - .retrive(vreg6), set mask if <;")
					ALL_FPU_ANTI_MASK
					ALL_FPU (".float vreg1= mask ?   vreg1 * .retrive(vreg6) : vreg1;")
					ALL_FPU (".float vreg7= mask ?   vreg7 + .retrive(vreg6) : vreg7;")
						: "+a" (cfs) );	//	����������� ���������� �������������
		}

		asm ( 	ALL_FPU (".float vreg7= vreg7 * .retrive(vreg6);")//  res * log(2)
				ALL_FPU (".float vreg1= vreg1 - .retrive(vreg6);")//  x = x-1;
			    //  Taylor
			    //  x^2 x^3 � �.�. �� ���������� �����, � ������������,
			    //  ����� ���������� �� ������� � �������,- ��� ������ ��������
				ALL_FPU (".float vreg2= vreg1 * vreg1;")    // 2
			    ALL_FPU (".float vreg3= vreg2 * vreg1;")    // 3
			    ALL_FPU (".float vreg4= vreg2 * vreg2;")    // 4
			    ALL_FPU (".float vreg0= vreg4 * vreg3;")    // 7
			    ALL_FPU (".float vreg7= vreg0 * .retrive(vreg6) + vreg7;")
			    ALL_FPU (".float vreg0= vreg3 * vreg3;")    // 6
			    ALL_FPU (".float vreg7= vreg0 * .retrive(vreg6) + vreg7;")
			    ALL_FPU (".float vreg0= vreg3 * vreg2;")    // 5
			    ALL_FPU (".float vreg7= vreg0 * .retrive(vreg6) + vreg7;")
			    ALL_FPU (".float vreg7= vreg4 * .retrive(vreg6) + vreg7;")
			    ALL_FPU (".float vreg7= vreg3 * .retrive(vreg6) + vreg7;")
			    ALL_FPU (".float vreg7= vreg2 * .retrive(vreg6) + vreg7;")
			    ALL_FPU (".float vreg7= vreg1 + vreg7;")
					: "+a" (cfs) );	//	����������� ���������� �������������
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
