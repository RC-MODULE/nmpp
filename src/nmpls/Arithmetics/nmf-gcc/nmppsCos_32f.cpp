
#include "math.h"
#include "nmtype.h"
#include "macros_fpu.h"

static const float coeffs_cos[38]= {
		//	vreg5
			DUP(1.0/(2*atan(1)*4)),	//	1/(2*pi)
			DUP(pow(2.0, 23)),
			DUP(2*atan(1)*4),		//	2*pi
			DUP(  atan(1)*4),     // Pi
			DUP(2*atan(1)*4 ),     // Pi*2
			DUP(  atan(1)*2),     // Pi/2
			DUP(  atan(1)*4),     // Pi
			DUP(-0.5),
			DUP(0.041666666666666666667),               // 1/4!
			DUP(-0.001388888888888888888889),           // 1/6!
			DUP(2.4801587301587301587301587301587e-5),  // 1/8!
			DUP(-2.755731922398589065255731922399e-7),  // 1/10!
			DUP(2.0876756987868098979210090321201e-9),  // 1/12!
//			DUP(-1.147074559772972471385169797868e-11), // 1/14!
//			DUP(4.7794773323873852974382074911175e-14), // 1/16!
//			DUP(-1.5619206968586226462216364350057e-16), // 1/18!
			//DUP(4.1103176233121648584779906184361e-19), // 1/20!
			//	vreg6
			DUP(pow(2.0, 23)),
			DUP(1.0),
            DUP(float( 1e100 ))               // err
	};

extern "C" int set_fp_ccr( int val );

extern "C" __attribute__ ((section(".text_int")))

void nmppsCos_32f(const nm32f* pSrcVec, nm32f* pDstVec, int nSize)
{
	if (nSize<8){
		static float b4[8]={1,1,1,1,1,1,1,1};
		float o4[8];
		int i;
		for (i=0;i<nSize;i++)
			b4[i]=pSrcVec[i];
		nmppsCos_32f( o4, b4, 8 );//	ðåêóðñèÿ!
		for (i=0;i<nSize;i++)
			pDstVec[i]=o4[i];
		return;
	}

	const float* cfs= coeffs_cos;
	asm( 	 	 "fpu 0  rep 13 vreg5= [%0++];  \n\t"
				 "fpu 1  vreg5= fpu 0  vreg5;  \n\t"
				 "fpu 2  vreg5= fpu 1  vreg5;  \n\t"
				 "fpu 3  vreg5= fpu 2  vreg5;  \n\t"
				 "fpu 0  rep 2 vreg6= [%0++];  \n\t"
				 "fpu 1  vreg6= fpu 0  vreg6;  \n\t"
				 "fpu 2  vreg6= fpu 1  vreg6;  \n\t"
				 "fpu 3  vreg6= fpu 2  vreg6;  \n\t"
										: "+a" (cfs)/*, "=g"(rMode)*/ : "m"(*coeffs_cos) );

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
		int rMode= set_fp_ccr(7);

		//	READ
		asm ( 	"vlen = %1;  							\n\t"
				"fpu 0 rep vlen vreg0= [%0++]; 			\n\t"
				"fpu 1 rep vlen vreg0= [%0++]; 			\n\t"
				"fpu 2 rep vlen vreg0= [%0++]; 			\n\t"
				"vlen = %2;                    			\n\t"
				"fpu 3 rep vlen vreg0= [%0++]; 			\n\t"
					: "+a" (pSrcVec)
					: "g"(len0), "g"(len1)
					  , "m"(*pSrcVec), "g"(rMode) );

		asm ( 	ALL_FPU (".float vreg2 = /vreg0/;")
				//	ïðèâîäèì ê 0 < X < 2*pi
				ALL_FPU (".float vreg1 = vreg2 * .retrive(vreg5)  + .retrive(vreg6);")
				ALL_FPU (".float vreg3 = vreg1  - .retrive(vreg5);")
				ALL_FPU (".float vreg1 = - vreg3 * .retrive(vreg5) + vreg2;")
				: "+a" (cfs) : "r"(pSrcVec) );	//	ïðîâÿçûâàåì èíñòðóêöèè çàâèñèìîñòÿìè

		//	actually, we presume rMode == 1 for best results,
		//	but we are preserve user's current mode
		set_fp_ccr(rMode);

		asm ( 	ALL_FPU (".float vreg1 - .retrive(vreg5), set mask if >;")          //  x > Pi
				ALL_FPU_ANTI_MASK
				ALL_FPU (".float vreg1= mask ? - vreg1 + .retrive(vreg5) : vreg1;") //  x= 2*Pi-x

				ALL_FPU (".float vreg1 - .retrive(vreg5), set mask if >;")          //  x > Pi/2   (=!=) - èñïîëüçóåòñÿ íèæå
				ALL_FPU_ANTI_MASK
				ALL_FPU (".float vreg1= mask ? - vreg1 + .retrive(vreg5) : vreg1;") //  x= Pi-x

				//	ðÿä Òåéëîðà
			    ALL_FPU (".float vreg2= vreg1 * vreg1;")
			    ALL_FPU (".float vreg1= vreg2 * .retrive(vreg5) + .retrive(vreg6);")                  //  - 1/2 x*x
			    ALL_FPU (".float vreg3= vreg2 * vreg2;")
			    ALL_FPU (".float vreg1= vreg3 * .retrive(vreg5) +vreg1;")
				: "+a" (cfs): "g"(rMode));

		//	ïðîäîëæåíèå ðÿäà Òåéëîðà
		int i;
		for( i=0; i<4; i++){
			asm ( 	ALL_FPU (".float vreg3= vreg2 * vreg3;")
					ALL_FPU (".float vreg1= vreg3 * .retrive(vreg5) +vreg1;")
					: "+a" (cfs));
		}

		asm (	ALL_FPU (".float vreg1= mask ? - vreg1 : vreg1;") //  x *= sign,  ñìîòðè âûøå - (=!=)
					: "+a" (cfs));

		//	WRITE
		asm ( 	"vlen = %2;  \n\t"
				"fpu 0 rep vlen [%0++] = vreg1; 	\n\t"
				"fpu 1 rep vlen [%0++] = vreg1; 	\n\t"
				"fpu 2 rep vlen [%0++] = vreg1; 	\n\t"
				"vlen = %3;                     	\n\t"
				"fpu 3 rep vlen [%0++] = vreg1; 	\n\t"
					: "+a" (pDstVec)
					  , "=m"(*pDstVec)
					: "g"(len0), "g"(len1)
					  , "a" (cfs) );
	}
	return;
}