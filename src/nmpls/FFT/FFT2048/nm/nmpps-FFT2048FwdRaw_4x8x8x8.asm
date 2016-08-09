//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM640X Software                      */
//*                                                                         */
//*   Fast Fourie Transform Library                                         */
//*   (C-callable functions)                                                */
//*                                                                         */
//*   File:             FFT3.asm                                            */
//*   Contents:         Routine for forward FFT 32 of complex array         */
//*                     with 32 bit elements                                */
//*                                                                         */
//*   Software design:  S.Mushkaev                                          */
//*                                                                         */
//*                                                                         */
//***************************************************************************/

    //==================================
    //! \fn int nmppsFFT32FwdRaw(nm32sc*	src, nm32sc*	dst, NmppsFFTSpec*	spec)
	//!
	//! \perfinclude nmppsFFT32FwdRaw.html
    //==================================

// TIME=35590 clocks . 17.377 clocks

extern vec_RShift32s:label;
extern vec_crc32:label;
data ".data_fft_L"

	GAddCmplxMask:long[2]=(
		0000000100000000hl,
		00000000FFFFFFFFhl);
		
	cosTblHold:word;
	sinTblHold:word;
	pX:word;
	pTmpRe:word;
	pTmpIm:word;
	pHRe:word;
	pHIm:word;
	pH:word;
	pJRe:word;
	pJIm:word;
	pJRaw:word;
	pI:word;
	pIRe:word;
	pIIm:word;
	pIRaw:word;
	pJ:word;
	pYRe:word;
	pYIm:word;
	pYRaw:word;
	pY:word;
	shift1:word;
	shift2:word;
	shift3:word;
end ".data_fft_L";




begin ".text_nmplv"
	
global   nmppsFinalizeCmplxMul:label;
		<nmppsFinalizeCmplxMul>


		
	return;
		
//////////////////////////////////////////////////////////////////////////////
//                                                                          //
//  Main Forward FFT-2048 procedure                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////
//
// total  instructions = 425 ticks
// scalar instructions = 192 ticks
// vector instructions = 425-192 = 233 ticks
// vector stages       = 12
// average vector stage= 233/12= 19.41 ticks at 16 theoretical
//
// Data-flow scheme (ar1<->ar6)
//[ar0:lo]+[ar0:hi] -> [ar1:lo]
//[ar0:lo]-[ar0:hi] -> [ar2:lo]
//                     [ar1:lo]*[ar4:re]->[ar2:hi]
//                     [ar1:lo]*[ar4:im]->[ar1:hi]
//                     [ar2:lo]*[ar4:re]->[ar1:lo]
//                     [ar2:lo]*[ar4:im]->[ar2:lo]					              
//                                        [ar1:lo]|[ar2:lo]->[ar6:odd ]
//                                        [ar1:hi]|[ar2:hi]->[ar6:even]
//                                                           [ar6     ] >>7 [ar1]
extern _clock:label;
global nmppsFFT2048Fwd4x8x8x8PreRaw	:label;
      <nmppsFFT2048Fwd4x8x8x8PreRaw>
.branch;	  
/*	
	// 	int ii,k,kk,j,i,n,h;	
	//spec->buffer[0]  =nmppsMalloc_64s(2048);
	//spec->buffer[1]  =nmppsMalloc_64s(2048);
	cosTbl=(nm8s*)spec->fftTable[0];
	sinTbl=(nm8s*)spec->fftTable[1];
	ii=0;	
	

//================= 0 =================
	pHRe=(nm32sc*)spec->buffer[0];
	pHIm=(nm32sc*)spec->buffer[1];
	pX  =(nm32sc*)src;
	pH  =(nm32sc*)dst;
	cosTblHold=cosTbl;
	sinTblHold=sinTbl;
	for( i=511; i>=0; i--){
		load_wfifo(pX+i,512,4);
		cosTbl=cosTblHold;
		sinTbl=sinTblHold;
		for( kk=0; kk<4; kk++){
			vsum_data (cosTbl,pHRe+512*kk+i);	cosTbl+=4;
			vsum_data (sinTbl,pHIm+512*kk+i);	sinTbl+=4;
		}
	}
*/
	
	nb1 = 080000000h 	with gr7=false;
	sb  = 000020002h 	with gr7++;
	ar0 = [cosTblHold]	with gr7<<=9;		// gr7 =512 (i)
	ar1 = [sinTblHold];	
	ar4 = [pX] 			with gr4 = gr7<<1;	//512*2;
	rep 4 wfifo = [ar4++gr4],ftw,wtw;
	rep 4 ram =[ar0++];
	ar5 = [pHRe] 		with gr5=gr4; 		//512*2;
	ar6 = [pHIm] 		with gr6=gr4;		//512*2;
	ar4 -= 512*2*4-2;
	gr1 = -8;
	<Next0_i>
		rep 4 wfifo = [ar4++gr4],ftw with vsum ,ram,0; 
		rep 4 [ar5++gr5] = afifo ; 
		rep 4 data=[ar1++] 	with vsum ,data,0; 
		ar1 = ar1+gr1 		with gr7--;
		rep 4 [ar6++gr6] = afifo,wtw  ; 
		ar4-= 512*2*4-2;
		ar5-= 512*2*4-2 ;
	if <>0 delayed goto Next0_i ;
		ar6-= 512*2*4-2 ;
	
	//ar0+=4*2;
	ar1+=4*2;
	[cosTblHold]=ar0;	
	[sinTblHold]=ar1;	

	//pop ar2,gr2;
	
	//gr7 -= gr2;
	//gr7 = ar6;
	//return ;
	
	//14853
	
//----------------- 0.1 -----------------				
/*	
	for( i=0; i<2048; i++){
		pH[i].re=pHRe[i].re-pHIm[i].im;
		pH[i].im=pHRe[i].im+pHIm[i].re;
	}
*/
	sb  = 000000002h;
	ar4 = GAddCmplxMask;
	rep 2 wfifo = [ar4++],ftw,wtw;
	gr7 = 2048/32;
	ar2 = [pHRe];
	ar3 = [pHIm];
	ar6 = [pH];
	gr6 = -2 with gr7--;
	if <>0 delayed skip gr6 with gr7--;
		rep 32 ram  = [ar2++];
		rep 32 data = [ar3++] with vsum ,data, ram;
		rep 32 [ar6++] = afifo;
	
	
	
/*
//================= 1 =================
	cosTblHold=cosTbl;
	sinTblHold=sinTbl;
	pJRe = (nm32sc*)spec->buffer[0];
	pJIm = (nm32sc*)spec->buffer[1];
	pJ   = src;
	pJRaw= dst;
	for(int i=63; i>=0; i--){
		cosTbl=cosTblHold;
		sinTbl=sinTblHold;
		for(int kk=3; kk>=0; kk--){
			load_wfifo(pH+512*kk+i,64,8);	
			for(int k=0; k<8; k++,ii++){	
				vsum_data(cosTbl,pJRe+256*k+64*kk+i,round[1]);	cosTbl+=8;
				vsum_data(sinTbl,pJIm+256*k+64*kk+i,0);			sinTbl+=8;
			}
		}
	}
*/
	
	gr0 = [pJRe]		with gr4=false;		//
	gr1 = [pJIm]		with gr4++;			//
	gr2 = [pH]			with gr3=gr4<<6;	// gr3=64	
	sb  = 002020202h 	with gr4=gr3<<1;	// gr4=64*2 (i)
	vr  = 000040h		with gr5=gr4<<2 ;	// gr5=256*2
	ar2 = [cosTblHold] 	with gr6=gr5;		// gr6=256*2
	ar3 = [sinTblHold];	
	ar4 = gr2; 
	rep 8 wfifo = [ar4++gr4],ftw,wtw; 		// load_wfifo(pH+512*kk+i,64,8);	
	
	<Next1_i>
		gr7 = 2;
		ar0 = ar2; 
		ar1 = ar3 with gr2+=gr7;
		ar5 = gr0 with gr0+=gr7;
		ar6 = gr1 with gr1+=gr7; 
		ar4 -= 64*2*8-512*2 with gr7++;  // gr7=3 and aftercycle; // (kk=0..3) 
		<Next1_kk>
			rep 8 data  = [ar0++] with vsum ,data,vr;	// vsum_data(cosTbl,pJRe+64*(k*4+kk)+i);
			rep 8 wfifo = [ar4++gr4],ftw; 				// load_wfifo(pH+512*kk+i,64,8);	
			with gr7--; 								// kk--;
			rep 8 [ar5++gr5] = afifo;
			rep 8 data = [ar1++],wtw with vsum ,data,0;	// vsum_data(sinTbl,pJIm+64*(k*4+kk)+i);	sinTbl+=8;
			rep 8 [ar6++gr6] = afifo ;
			ar4 -= 64*2*8-512*2;
			ar5 -= 256*2*8-64*2;
		if <>0 delayed goto Next1_kk;
			ar6 -= 256*2*8-64*2;
		// final cycle
		ar4 = gr2 with gr3--;
		rep 8 data  = [ar0++] with vsum ,data,vr;		// vsum_data(cosTbl,pJRe+64*(k*4+kk)+i);
		rep 8 wfifo = [ar4++gr4],ftw; 					// load_wfifo(pH+512*kk+i,64,8);	
		rep 8 [ar5++gr5] = afifo;
	if <>0 delayed goto Next1_i;
		rep 8 data = [ar1++],wtw with vsum ,data,0;		// vsum_data(sinTbl,pJIm+64*(k*4+kk)+i);	sinTbl+=8;
		rep 8 [ar6++gr6] = afifo ;
		
	[cosTblHold]=ar0;	
	[sinTblHold]=ar1;	
	
	// 5622/5244/4598 ticks /  4598/2048/2 = 1,077928363988
	
//	ar0 = [pJRe];
//	gr5 = 2048*2;
//	call vec_crc32;
//
//	ar0 = [pJIm];
//	gr5 = 2048*2;
//	call vec_crc32;
//	return;
	
//----------------- 1.1 -----------------	
/*	for(int i=0;i<2048; i++){
		pJRaw[i].re=pJRe[i].re-pJIm[i].im+round[1];
		pJRaw[i].im=pJRe[i].im+pJIm[i].re+round[1];
	}
*/	
	
	sb  = 000000002h;
	ar4 = GAddCmplxMask;
	gr6 = -2;
	rep 2 wfifo = [ar4++],ftw,wtw;
	gr7 = 2048/32;
	ar2 = [pJRe];
	ar3 = [pJIm];
	ar6 = [pJRaw] with gr7--;
	if <>0 delayed skip gr6 with gr7--;
		rep 32 ram  = [ar2++];
		rep 32 data = [ar3++] with vsum, data, ram;
		rep 32 [ar6++] = afifo;

//----------------- 1.2 -----------------			
/*	for(int i=0; i<2048; i++){
		pJ[i].re=pJRaw[i].re>>spec->shift[1];
		pJ[i].im=pJRaw[i].im>>spec->shift[1];
	}
*/	
	ar0 = [pJRaw]	with gr6=-gr6;	// gr6=2
	ar6 = [pJ]		with gr0=gr6;	// gr0=2
	delayed call vec_RShift32s;
		gr4 = [shift1] with gr5=gr0<<11; //	gr5 = 2048*2; /

	
//================= 2 =================-------
/*
	cosTblHold=cosTbl;
	sinTblHold=sinTbl;
	pIRe=(nm32sc*)spec->buffer[0];
	pIIm=(nm32sc*)spec->buffer[1];
	pIRaw=src;
	pI=dst;

	for(int i=7; i>=0; i--){
		cosTbl=cosTblHold;
		sinTbl=sinTblHold;
		for(int kk=31; kk>=0; kk--){
			load_wfifo(pJ+64*kk+i,8,8);			
			for(int k=0; k<8; k++){		
				vsum_data(cosTbl,pIRe+256*k+8*kk+i);	cosTbl+=8;
				vsum_data(sinTbl,pIIm+256*k+8*kk+i);	sinTbl+=8;
			}
		}
	}
*/
	// 1.2 ===> gr6=2; 	
	nb1 = 080000000h;	
	sb  = 002020202h	with gr3 = gr6<<2;	// gr3 = 8 (i)
	gr0 = [pIRe]		with gr4 = gr6<<3;	// gr4 = 8*2;	
	gr1 = [pIIm]		with gr5 = gr6<<8;	// gr5 = 256*2;	
	gr2 = [pJ]			with gr6 = gr6<<8;	// gr6 = 256*2;
	ar2 = [cosTblHold];	
	ar3 = [sinTblHold];	
	ar4 = gr2; 
	rep 8 wfifo = [ar4++gr4],ftw,wtw; 	
	
	<Next2_i>
		gr7 = 2;
		ar0 = ar2;					//[cosTblHold];	
		ar1 = ar3	with gr2+=gr7;	//[sinTblHold];	
		ar5 = gr0	with gr0+=gr7;
		ar6 = gr1	with gr1+=gr7; 
		gr7 = 31;	
		<Next2_kk>
			rep 8 data=[ar0++] with vsum ,data,vr;		// vsum_data(cosTbl,pIRe+256*k+8*kk+i);
			rep 8 wfifo = [ar4++gr4],ftw; 				// load_wfifo(pJ+64*kk+i,8,8);	
			with gr7--;									// kk--
			rep 8 [ar5++gr5] = afifo;
			rep 8 data=[ar1++],wtw with vsum ,data,0;	// vsum_data(sinTbl,pIIm+256*k+8*kk+i);
			rep 8 [ar6++gr6] = afifo ;
			ar5-= 256*2*8-8*2;
		if <>0 delayed goto Next2_kk ;
			ar6-= 256*2*8-8*2;
		
		// final cycle
		ar4 = gr2 with gr3--;
		rep 8 data=[ar0++] with vsum ,data,vr;			// vsum_data(cosTbl,pIRe+256*k+8*kk+i);
		rep 8 wfifo = [ar4++gr4],ftw; 					// load_wfifo(pJ+64*kk+i,8,8);	
		rep 8 [ar5++gr5] = afifo;
	if <>0 delayed goto Next2_i with gr7=false;
		rep 8 data=[ar1++],wtw with vsum ,data,0;		// vsum_data(sinTbl,pIIm+256*k+8*kk+i);
		rep 8 [ar6++gr6] = afifo ;
	
	//!!! WARING reading ar4++gr4 out of memory is possible 
	[cosTblHold]=ar0;	
	[sinTblHold]=ar1;	
	
//----------------- 2.1 -----------------			
/* 	for(int i=0; i<2048; i++){
		pIRaw[i].re=pIRe[i].re-pIIm[i].im+round[2];
		pIRaw[i].im=pIRe[i].im+pIIm[i].re+round[2];
	} */
	
	sb  = 000000002h;
	ar4 = GAddCmplxMask;
	gr6 = -2;
	rep 2 wfifo = [ar4++],ftw,wtw;
	gr7 = 2048/32;
	ar6 = [pIRaw] with gr7--;
	ar2 = [pIRe];
	ar3 = [pIIm];
	if <>0 delayed skip gr6 with gr7--;
		rep 32 ram  = [ar2++];
		rep 32 data = [ar3++] with vsum,data, ram;
		rep 32 [ar6++] = afifo;
		
//----------------- 2.2 -----------------					
/*	for(int i=0; i<2048; i++){
		pI[i].re=pIRaw[i].re>>spec->shift[2];
		pI[i].im=pIRaw[i].im>>spec->shift[2];
	} */
	// 2.1 ===> gr6=-2
	ar0 = [pIRaw]	with gr6 = -gr6; 				// gr6 = 2;
	ar6 = [pI]		with gr0 = gr6;					// gr0 = 2;
	delayed call vec_RShift32s with gr5 = gr0<<11;	// gr5 = 2048*2;
		gr4 = [shift2];
	
//================= 3 =================-------
/*
	pYRe=(nm32sc*)spec->buffer[0];
	pYIm=(nm32sc*)spec->buffer[1];
	pYRaw=src;
	pY =dst;


	for(int kk=0; kk<256; kk++){
		load_wfifo(pI+8*kk,1,8);								
		for(int k=0; k<8; k++){
			vsum_data(cosTbl,pYRe+256*k+kk);	cosTbl+=8;						
			vsum_data(sinTbl,pYIm+256*k+kk);	sinTbl+=8;						
		}
	}
*/
			
			
	sb  = 002020202h	with gr7 = gr6<<7;	// gr7 = 256
	nb1 = 080000000h	with gr5 = gr7<<1;	// gr5 = 256*2
	ar4 = [pI] 			with gr6 = gr7<<1;	// gr6 = 256*2;	
	rep 8 wfifo = [ar4++],ftw,wtw; 			// load_wfifo(pI+8*kk,1,8);								
	ar0 = [cosTblHold]	with gr7--;			// gr7 = 255 (kk);
	ar1 = [sinTblHold];
	ar5 = [pYRe];	
	ar6 = [pYIm];
<Next3_kk>
		rep 8 data=[ar0++] with vsum ,data,vr;		// vsum_data(cosTbl,pYRe+256*k+kk);
		rep 8 wfifo = [ar4++],ftw; 					// load_wfifo(pI+8*kk,1,8);								
		rep 8 [ar5++gr5] = afifo;
		with gr7--;									// kk--	
		rep 8 data=[ar1++],wtw with vsum ,data,0;	// vsum_data(sinTbl,pYIm+256*k+kk);
		rep 8 [ar6++gr6] = afifo ;
		ar5-= 256*2*8-2;
	if <>0 delayed goto Next3_kk;		
		ar6-= 256*2*8-2;
	
	// final cycle
	rep 8 data=[ar0++] with vsum ,data,vr;	// vsum_data(cosTbl,pYRe+256*k+kk);
	rep 8 [ar5++gr5] = afifo;
	rep 8 data=[ar1++] with vsum ,data,0;	// vsum_data(sinTbl,pYIm+256*k+kk);
	rep 8 [ar6++gr6] = afifo ;
		
	
/* 	for(int i=0; i<2048; i++){
		pYRaw[i].re=pYRe[i].re-pYIm[i].im+round[3];	
		pYRaw[i].im=pYRe[i].im+pYIm[i].re+round[3];
	}*/
	
	sb  = 000000002h;						// 
	ar4 = GAddCmplxMask;
	gr6 = -2;
	rep 2 wfifo = [ar4++],ftw,wtw;
	gr7 = 2048/32;
	ar6 = [pYRaw] with gr7--;
	ar2 = [pYRe];
	ar3 = [pYIm];
	if <>0 delayed skip gr6 with gr7--;
		rep 32 ram  = [ar2++];
		rep 32 data = [ar3++] with vsum ,data, ram;
		rep 32 [ar6++] = afifo;

.wait;
return ;		
	
	
	
	
	  
global _nmppsFFT2048Fwd4x8x8x8Raw	:label;
      <_nmppsFFT2048Fwd4x8x8x8Raw>

	ar5=sp-2	 with gr7=false;
	push ar0,gr0 with gr7++;			
	push ar1,gr1 with gr7++;		
	push ar2,gr2;
	push ar3,gr3;
	push ar4,gr4;
	push ar5,gr5;	
	push ar6,gr6 with gr6=gr7;			// gr6=2
	
	ar0 = [--ar5];						// src[32*2]
	ar6 = [--ar5];						// dst[32*2]
	ar5 = [--ar5];						// spec
	gr1 = [ar5++];						// tmp[32*2]
	gr2 = [ar5++];						// tmp[32*2]
	gr3 = [ar5++];						// weights[16*2*2]
	ar4 = [ar5++];						// weights[16*2*2]
	[pHRe] = gr1;
	[pHIm] = gr2;
	[cosTblHold] = gr3;
	[sinTblHold] = gr4;
	[pX]= ar0;
	[pY]= ar6;
	[pH]= ar0;
	
	[pJRe]= gr1;
	[pJIm]= gr2;
	[pJRaw]=ar6;
	[pJ]=ar0;
	
	
	[pIRe]=gr1;
	[pIIm]=gr2;
	[pIRaw]=ar6;
	[pI]=ar0;
	
	[pYRe]=gr1;
	[pYIm]=gr2;
	[pYRaw]=ar6;
	
	gr0 = [ar5++];
	gr1 = [ar5++];
	gr2 = [ar5++];
	gr3 = [ar5++];
	[shift1]=gr1;
	[shift2]=gr2;
	[shift2]=gr3;
		
	call nmppsFFT2048Fwd4x8x8x8PreRaw;
	
	
	pop ar6,gr6;
	pop ar5,gr5;
	pop ar4,gr4;
	pop ar3,gr3;
	pop ar2,gr2;
	pop ar1,gr1;
	pop ar0,gr0;


return;

	

global _nmppsFFT2048Fwd4x8x8x8	:label;
      <_nmppsFFT2048Fwd4x8x8x8>
.branch;
	ar5=sp-2	 with gr7=false;
	push ar0,gr0 with gr7++;			
	push ar1,gr1 with gr7++;		
	push ar2,gr2;
	push ar3,gr3;
	push ar4,gr4;
	push ar5,gr5;	
	push ar6,gr6 with gr6=gr7;			// gr6=2
	
	ar0 = [--ar5];						// src[32*2]
	ar6 = [--ar5];						// dst[32*2]
	ar5 = [--ar5];						// spec
	gr1 = [ar5++];						// tmp[32*2]
	gr2 = [ar5++];						// tmp[32*2]
	gr3 = [ar5++];						// weights[16*2*2]
	gr4 = [ar5++];						// weights[16*2*2]
	[pTmpRe]=gr1;
	[pTmpIm]=gr2;
	
	[pHRe] = gr1;
	[pHIm] = gr2;
	[cosTblHold] = gr3;
	[sinTblHold] = gr4;
	[pX]= ar0;
	[pH]= ar0;
	
	[pJRe]= gr1;
	[pJIm]= gr2;
	[pJRaw]=ar6;
	[pJ]=ar0;
	
	
	[pIRe]=gr1;
	[pIIm]=gr2;
	[pIRaw]=ar6;
	[pI]=ar0;
	
	[pYRe]=gr1;
	[pYIm]=gr2;
	[pYRaw]=ar0;
	[pY]=ar6;
	
	gr0 = [ar5++];
	gr1 = [ar5++];
	gr2 = [ar5++];
	gr3 = [ar5++];
	[shift1]=gr1;
	[shift2]=gr2;
	[shift3]=gr3;
	
	call nmppsFFT2048Fwd4x8x8x8PreRaw;
	
	//{	for(int i=0; i<2048; i++){
	//	pY[i].re=pYRaw[i].re>>spec->shift[3];
	//	pY[i].im=pYRaw[i].im>>spec->shift[3];}	

	
	ar0 = [pYRaw];
	ar6 = [pY];
	gr0 = 2;
	gr6 = 2;
	gr5 = 2048*2 with gr1=gr7;
	
	delayed call vec_RShift32s;
		gr4 = [shift3];
		
	pop ar6,gr6 with gr7=gr1;
	pop ar5,gr5;
	pop ar4,gr4;
	pop ar3,gr3;
	pop ar2,gr2;
	pop ar1,gr1;
	pop ar0,gr0;
return ;
.wait;

/*
global _nmppsFFT2048Fwd4x8x8x8	:label;
      <_nmppsFFT2048Fwd4x8x8x8>
.branch;
	ar5=sp-2	 with gr7=false;
	push ar0,gr0 with gr7++;			
	push ar1,gr1 with gr7++;		
	push ar2,gr2;
	push ar3,gr3;
	push ar4,gr4;
	push ar5,gr5;	
	push ar6,gr6 with gr6=gr7;			// gr6=2
	
	ar0 = [--ar5];						// src[32*2]
	ar6 = [--ar5];						// dst[32*2]
	ar5 = [--ar5];						// spec
	gr1 = [ar5++];						// tmp[32*2]
	gr2 = [ar5++];						// tmp[32*2]
	gr3 = [ar5++];						// weights[16*2*2]
	gr4 = [ar5++];						// weights[16*2*2]
	//[pTmpRe]=gr1;
	//[pTmpIm]=gr2;
	
	[pHRe] = gr1;
	[pHIm] = gr2;
	[cosTblHold] = gr3;
	[sinTblHold] = gr4;
	[pX]   = ar0;
	[pH]   = ar6;
	
	[pJRe] = gr1;
	[pJIm] = gr2;
	[pJRaw]= ar6;
	[pJ]   = gr1;//ar0;
	
	
	[pIRe] = gr2;//gr1;
	[pIIm] = ar6;//gr2;
	[pIRaw]= gr1;//ar6;
	[pI]   = gr2;//ar0;
	
	[pYRe] = ar6;
	[pYIm] = gr1;
	[pYRaw]= gr2;
	
	[pY]   = ar6;
	
	gr0 = [ar5++];
	gr1 = [ar5++];
	gr2 = [ar5++];
	gr3 = [ar5++];
	[shift1]=gr1;
	[shift2]=gr2;
	[shift3]=gr3;
	
	call nmppsFFT2048Fwd4x8x8x8PreRaw;
	
	//	for(int i=0; i<2048; i++){
	//	pY[i].re=pYRaw[i].re>>spec->shift[3];
	//	pY[i].im=pYRaw[i].im>>spec->shift[3];}

	with gr1=gr7;
	ar0 = [pYRaw] ;//	with gr0=false;
	ar6 = [pY]		;//with gr0++;
	gr0 =2;
	gr6 =2;
	gr5 = 2048*2 	;//with gr0++;					// gr0=2
	delayed call vec_RShift32s;	// gr6=2
		gr4 = [shift3];
		
	pop ar6,gr6 with gr7=gr1;
	pop ar5,gr5;
	pop ar4,gr4;
	pop ar3,gr3;
	pop ar2,gr2;
	pop ar1,gr1;
	pop ar0,gr0;
return ;
.wait;
*/
	
end ".text_nmplv";