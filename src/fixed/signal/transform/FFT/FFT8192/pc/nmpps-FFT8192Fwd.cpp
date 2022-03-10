//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM640x Software                      */
//*                                                                         */
//*   Software design:  S.Mushkaev                                          */
//*                                                                         */
//*                                                                         */
//***************************************************************************/

#include "fft.h"
#include "nmpp.h"
#include "nmtl.h"
#include "fftexp.h"
extern "C"{

int nmppsFFT8192Fwd28888RawRef(const nm32sc* src, nm32sc* dst, const NmppsFFTSpec* spec)
{
	int round[5];
	round[0]=1<<(spec->shift[0]-1);
	round[1]=1<<(spec->shift[1]-1);
	round[2]=1<<(spec->shift[2]-1);
	round[3]=1<<(spec->shift[3]-1);
	round[4]=1<<(spec->shift[3]-1);


	vec<cmplx<int> > X((cmplx<int>*)src,8192);
	vec<cmplx<int> > Y((cmplx<int>*)dst,8192);
	vec<cmplx<int> > N(8192);
	vec<cmplx<int> > G(8192);
	vec<cmplx<int> > H(8192);
	vec<cmplx<int> > J(8192);
	cmplx<int> z;
	//-------- 0 -------------------
	for(int kk=0; kk<4096; kk++){
		N[kk]=X[kk]+X[4096+kk];
	}
	for(int kk=0; kk<4096; kk++){
		N[4096+kk]=X[kk]-X[4096+kk];
	}
	
	//-------- 1 -------------------
	for(int k=0; k<16; k++){
		for(int kk=0; kk<512; kk++){
			for(int g=0; g<8; g++){
				G[512*(k%16)+kk]+= N[4096*(k%2)+512*g+kk]*	expFFT127<8192>(512*g*k,spec->amp[1]);
			}
		}
	}
	z.re= round[1];
	z.im= round[1];
	G+=z;
	G>>=spec->shift[1];


	for(int k=0; k<128; k++){
		for(int kk=0; kk<64; kk++){
			for(int h=0; h<8; h++){
				H[64*(k%128)+kk]+=G[512*(k%16)+64*h+kk]*	expFFT127<8192>(64*h*k,spec->amp[2]);
			}
		}
	}
	z.re= round[2];
	z.im= round[2];
	H+=z;
	H>>=spec->shift[2];

	for(int k=0; k<1024; k++){
		for(int i=0; i<8; i++){
			for(int j=0; j<8; j++){
				J[8*(k%1024)+i]+=H[64*(k%128)+8*j+i]*		expFFT127<8192>(8*j*k,spec->amp[3]);
			}
		}
	}
	z.re= round[3];
	z.im= round[3];
	J+=z;
	J>>=spec->shift[3];

	Y.reset();
	for(int k=0; k<8192; k++){
		for(int i=0; i<8; i++){
			Y[k]+=J[8*(k%1024)+i]*							expFFT127<8192>(i*k,spec->amp[4]);
		}
	}

	z.re= round[4];
	z.im= round[4];
	Y+=z;

	return 0;
}


int nmppsFFT8192Fwd28888Raw(const nm32sc* src, nm32sc* dst, const NmppsFFTSpec* spec)
{
	int round[5];
	round[0]=1<<(spec->shift[0]-1);
	round[1]=1<<(spec->shift[1]-1);
	round[2]=1<<(spec->shift[2]-1);
	round[3]=1<<(spec->shift[3]-1);
	round[4]=1<<(spec->shift[4]-1);


	nm8s*   cosTbl;
	nm8s*   sinTbl;
	nm8s*   cosTblHold=(nm8s*)spec->fftTable[0];
	nm8s*   sinTblHold=(nm8s*)spec->fftTable[2];

	nm32sc* pX   =(nm32sc*)src;
	nm32sc* pN   =(nm32sc*)spec->buffer[0];
	
	nm32sc* pGRe =(nm32sc*)dst;
	nm32sc* pGIm =(nm32sc*)spec->buffer[1];
	nm32sc* pGRaw=(nm32sc*)spec->buffer[0];
	nm32sc* pG   =(nm32sc*)dst;


	nm32sc* pHRe =(nm32sc*)spec->buffer[0];
	nm32sc* pHIm =(nm32sc*)spec->buffer[1];
	nm32sc* pHRaw=(nm32sc*)dst;
	nm32sc* pH   =(nm32sc*)spec->buffer[0];

	nm32sc* pJRe =(nm32sc*)spec->buffer[1];
	nm32sc* pJIm =(nm32sc*)dst;
	nm32sc* pJRaw=(nm32sc*)spec->buffer[0];
	nm32sc* pJ   =(nm32sc*)dst;

	
	nm32sc* pYRe =(nm32sc*)spec->buffer[1];
	nm32sc* pYIm =(nm32sc*)spec->buffer[0];
	nm32sc* pYRaw=(nm32sc*)dst;

	//vec<cmplx<int> > X((cmplx<int>*)src,8192);
	//vec<cmplx<int> > Y((cmplx<int>*)dst,8192);
	//vec<cmplx<int> > N((cmplx<int>*)pN,8192);
	//vec<cmplx<int> > G((cmplx<int>*)pG,8192);
	//vec<cmplx<int> > H((cmplx<int>*)pH,8192);
	//vec<cmplx<int> > J((cmplx<int>*)pJ,8192);
	//cmplx<int> z;

	//-------- 0 -------------------
	//for(int kk=0; kk<4096; kk++){
	//	N[kk]+=X[kk]+X[4096+kk];
	//}
	//for(int kk=0; kk<4096; kk++){
	//	N[4096+kk]+=X[kk]-X[4096+kk];
	//}
	//-------- 0.0 -------------------
	for(int kk=0; kk<4096; kk++){
		pN[kk].re=pX[kk].re+pX[4096+kk].re;
		pN[kk].im=pX[kk].im+pX[4096+kk].im;
	}
	for(int kk=0; kk<4096; kk++){
		pN[4096+kk].re=pX[kk].re-pX[4096+kk].re;
		pN[4096+kk].im=pX[kk].im-pX[4096+kk].im;
	}
//unsigned crc;
//crc=nmppsCrc_32s((nm32s*)pX,8192*2);
//crc=nmppsCrc_32s((nm32s*)pN,8192*2);
	//-------- 1 -------------------
	//for(int kk=0; kk<512; kk++){
	//	for(int k2=0; k2<2; k2++){ 		
	//		for(int k1=0; k1<8; k1++){	// rep 8
	//			int k=k1*2+k2;			// for(int k=0; k<16; k++)
	//			for(int g=0; g<8; g++){	// vsum
	//				G[1024*k1+512*k2+kk]+= N[4096*k2+512*g+kk]*	expFFT<8192>(512*g*k);
	//			}
	//		}
	//	}
	//}
	//z.re= spec->round[1];
	//z.im= spec->round[1];
	//G+=z;
	//G>>=spec->shift[1];
	//---------------------------------- 1.0 -----------------------------------------	
	for(int kk=0; kk<512; kk++){
		cosTbl=cosTblHold;
		sinTbl=sinTblHold;
		for(int k2=0; k2<2; k2++){
			load_wfifo(pN+4096*k2+kk,512,8);
			for(int k1=0; k1<8; k1++){	
				vsum_data(cosTbl,pGRe+1024*k1+512*k2+kk,round[1]);cosTbl+=8;
				vsum_data(sinTbl,pGIm+1024*k1+512*k2+kk,0);				sinTbl+=8;
			}
		}
	}
	cosTblHold=cosTbl;
	sinTblHold=sinTbl;
//crc=nmppsCrc_32s((nm32s*)pGRe,8192*2);
//crc=nmppsCrc_32s((nm32s*)pGIm,8192*2);

	//---------------------------------- 1.1 -----------------------------------------	
	for(int i=0;i<8192; i++){
		pGRaw[i].re=pGRe[i].re-pGIm[i].im;
		pGRaw[i].im=pGRe[i].im+pGIm[i].re;
	}
	//---------------------------------- 1.2 -----------------------------------------
	for(int i=0; i<8192; i++){
		pG[i].re=pGRaw[i].re>>spec->shift[1];
		pG[i].im=pGRaw[i].im>>spec->shift[1];
	}

//crc=nmppsCrc_32s((nm32s*)pG,8192*2);

	//---------------------------------- 2.0 -----------------------------------------
	//for(int kk=0; kk<64; kk++){
	//	for(int k2=0; k2<16; k2++){ 		
	//		for(int k1=0; k1<8; k1++){	// rep 8
	//			int k=k1*16+k2;			// for(int k=0; k<128; k++){
	//			for(int h=0; h<8; h++){	// vsum
	//				H[1024*k1+64*k2+kk]+=G[512*k2+64*h+kk]*	expFFT<8192>(64*h*k);
	//			}
	//		}
	//	}
	//z.re= spec->round[2];
	//z.im= spec->round[2];
	//H+=z;
	//H>>=spec->shift[2];
	// ---------------- 2.0 --------------------
	for(int kk=0; kk<64; kk++){
		cosTbl=cosTblHold;
		sinTbl=sinTblHold;
		for (int k2=0; k2<16;k2++){
			load_wfifo(pG+512*k2+kk,64,8);
			for (int k1=0; k1<8;k1++){
				int k=16*k1+k2;//for(int k=0; k<128; k++)
				vsum_data(cosTbl,pHRe+1024*k1+64*k2+kk,round[2]);cosTbl+=8;
				vsum_data(sinTbl,pHIm+1024*k1+64*k2+kk,0);				sinTbl+=8;
			}
		}
	}
	cosTblHold=cosTbl;
	sinTblHold=sinTbl;
//crc=nmppsCrc_32s((nm32s*)pHRe,8192*2);
//crc=nmppsCrc_32s((nm32s*)pHIm,8192*2);
	//---------------------------------- 2.1 -----------------------------------------	
	for(int i=0;i<8192; i++){
		pHRaw[i].re=pHRe[i].re-pHIm[i].im;
		pHRaw[i].im=pHRe[i].im+pHIm[i].re;
	}
	//---------------------------------- 2.2 -----------------------------------------
	for(int i=0; i<8192; i++){
		pH[i].re=pHRaw[i].re>>spec->shift[2];
		pH[i].im=pHRaw[i].im>>spec->shift[2];
	}
//crc=nmppsCrc_32s((nm32s*)pH,8192*2);


	//---------------------------------- 3.0 -----------------------------------------
	//for(int k2=0; k2<128; k2++){ 		
	//	for(int k1=0; k1<8; k1++){
	//		for(int i=0; i<8; i++){		// rep 8
	//			int k=k1*128+k2;		// for(int k=0; k<1024; k++){
	//			for(int j=0; j<8; j++){	// vsum
	//				J[1024*k1+8*k2+i]+=H[64*k2+8*j+i]*expFFT<8192>(8*j*k);
	//			}
	//		}
	//	}
	//}	
	//z.re= spec->round[3];
	//z.im= spec->round[3];
	//J+=z;
	//J>>=spec->shift[3];

	for(int i=0; i<8; i++){
		cosTbl=cosTblHold;
		sinTbl=sinTblHold;
		for (int k2=0; k2<128;k2++){
			load_wfifo(pH+64*k2+i,8,8);
			for (int k1=0; k1<8;k1++){
				vsum_data(cosTbl,pJRe+1024*k1+8*k2+i,round[3]);		cosTbl+=8;
				vsum_data(sinTbl,pJIm+1024*k1+8*k2+i,0);				sinTbl+=8;
			}
		}
	}
//crc=nmppsCrc_32s((nm32s*)pJRe,8192*2);
//crc=nmppsCrc_32s((nm32s*)pJIm,8192*2);

	//---------------------------------- 3.1 -----------------------------------------	
	for(int i=0;i<8192; i++){
		pJRaw[i].re=pJRe[i].re-pJIm[i].im;
		pJRaw[i].im=pJRe[i].im+pJIm[i].re;
	}
	//---------------------------------- 3.2 -----------------------------------------
	for(int i=0; i<8192; i++){
		pJ[i].re=pJRaw[i].re>>spec->shift[3];
		pJ[i].im=pJRaw[i].im>>spec->shift[3];
	}

//crc=nmppsCrc_32s((nm32s*)pJ,8192*2);

	//---------------------------------- 4.0 -----------------------------------------
	//for(int k2=0; k2<1024; k2++){ 		
	//	for(int k1=0; k1<8; k1++){		// rep 8
	//		int k=1024*k1+k2;			// for(int k=0; k<8192; k++){ 
	//		for(int i=0; i<8; i++){		// vsum
	//			Y[1024*k1+k2]+=J[8*k2+i]*expFFT<8192>(i*k);
	//		}
	//	}
	//}
	//z.re= spec->round[4];
	//z.im= spec->round[4];
	//Y+=z;
	cosTbl=(nm8s*)spec->fftTable[1];
	sinTbl=(nm8s*)spec->fftTable[3];

	for (int k2=0; k2<1024; k2++){
		load_wfifo(pJ+8*k2,1,8);
		for (int k1=0; k1<8; k1++){
			vsum_data(cosTbl,pYRe+1024*k1+k2,round[4]);			cosTbl+=8;
			vsum_data(sinTbl,pYIm+1024*k1+k2,0);				sinTbl+=8;
		}
	}
//crc=nmppsCrc_32s((nm32s*)pYRe,8192*2);
//crc=nmppsCrc_32s((nm32s*)pYIm,8192*2);
	//---------------------------------- 4.1 -----------------------------------------	
	for(int i=0;i<8192; i++){
		pYRaw[i].re=pYRe[i].re-pYIm[i].im;
		pYRaw[i].im=pYRe[i].im+pYIm[i].re;
	}
//crc=nmppsCrc_32s((nm32s*)pYRaw,8192*2);
	return 0;
}




int nmppsFFT8192Fwd28888(const nm32sc* src, nm32sc* dst, const NmppsFFTSpec* spec)
{
	nmppsFFT8192Fwd28888Raw(src, dst, spec);

	//---------------------------------- 3.2 -----------------------------------------
	for(int i=0; i<8192; i++){
		dst[i].re=dst[i].re>>spec->shift[4];
		dst[i].im=dst[i].im>>spec->shift[4];
	}
	return 0;
}

};