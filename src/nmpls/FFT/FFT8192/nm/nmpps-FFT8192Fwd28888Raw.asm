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
extern _clock:label;
macro START_TIMER()
	call _clock;
	[t]=gr7;
end  START_TIMER;

macro STOP_TIMER()
	call _clock; 
	gr0 =[t]; 	
	gr7-=gr0; 
end STOP_TIMER;

macro CRC32(adr)
//	ar0 = [adr];
//	gr5 = 8192*2;
//	call vec_crc32;
end CRC32;


extern vec_RShift32s:label;
extern vec_crc32:label;
data ".data_fft_L"
	t:word;
	GAddCmplxMask:long[2]=(
		0000000100000000hl,
		00000000FFFFFFFFhl);
		
	cosTblHold:word;
	sinTblHold:word;
	cosTblHold2:word;
	sinTblHold2:word;
	pX:word;
	pN:word;
	pTmpRe:word;
	pTmpIm:word;
	pHRe :word;
	pHIm :word;
	pHRaw:word;
	pH   :word;
	pGRe :word;
	pGIm :word;
	pGRaw:word;
	pG   :word;
	
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
	shift4:word;
end ".data_fft_L";




begin ".text_nmplv"

		
//////////////////////////////////////////////////////////////////////////////
//                                                                          //
//  Main Forward FFT-8192 procedure                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////
//
// total  instructions = 425 ticks
// scalar instructions = 192 ticks
// vector instructions = 425-192 = 233 ticks
// vector stages       = 12
// average vector stage= 233/12= 19.41 ticks at 16 theoretical



global nmppsFFT8192Fwd28888Core	:label;
      <nmppsFFT8192Fwd28888Core>
.branch;	  
	

	//-------- 0.0 -------------------
	//for(int kk=0; kk<4096; kk++){
	//	pN[kk].re=pX[kk].re+pX[4096+kk].re;
	//	pN[kk].im=pX[kk].im+pX[4096+kk].im;
	//}
	//for(int kk=0; kk<4096; kk++){
	//	pN[4096+kk].re=pX[kk].re-pX[4096+kk].re;
	//	pN[4096+kk].im=pX[kk].im-pX[4096+kk].im;
	//}

	START_TIMER();
	nb1 = 080000000h; wtw;
	ar0 = [pX];
	ar1 = ar0;
	ar1+= 4096*2;
	ar2 = ar1;
	ar5 = [pN];
	ar6 = ar5;
	gr7 = 4096/32;
	ar6+= 4096*2 with gr7--;
	<Next0_kk>
		rep 32 ram = [ar0++];
		rep 32 data= [ar1++] with ram+data;
		rep 32 [ar5++]=afifo; // with vsum ,ram,afifo;
	if <>0 delayed goto Next0_kk with gr7--;
		rep 32 data= [ar2++] with ram-data;
		rep 32 [ar6++]=afifo;
	
	//STOP_TIMER(); // Best time=12321, 12321/8192 = 1,504028320312 
	//return;
	

	//---------------------------------- 1.0 -----------------------------------------	
	//for(int kk=0; kk<512; kk++){
	//	cosTbl=cosTblHold;
	//	sinTbl=sinTblHold;
	//	for(int k2=0; k2<2; k2++){
	//		load_wfifo(pN+4096*k2+kk,512,8);
	//		for(int k1=0; k1<8; k1++){	
	//			vsum_data(cosTbl,pGRe+1024*k1+512*k2+kk,spec->round[1]);cosTbl+=8;
	//			vsum_data(sinTbl,pGIm+1024*k1+512*k2+kk,0);				sinTbl+=8;
	//		}
	//	}
	//}
	//cosTblHold=cosTbl;
	//sinTblHold=sinTbl;
	
	//START_TIMER();
	
	gr0 = [pGRe]		with gr4=false;		//
	gr1 = [pGIm]		with gr4++;			//
	gr2 = [pN]			with gr3=gr4<<9;	// gr3=512 		gr3:for(int kk=0; kk<512; kk++)
	sb  = 002020202h 	with gr4=gr3<<1;	// gr4=512*2 	gr4:load_wfifo(pN+4096*k2+kk,512,8);
	vr  = 000040h		with gr5=gr4<<1;	// gr5=1024*2	gr5:vsum_data(cosTbl,pGRe+1024*k1+512*k2+kk,vr);
	ar2 = [cosTblHold] 	with gr6=gr5;		// gr6=1024*2	gr6:vsum_data(sinTbl,pGIm+1024*k1+512*k2+kk,0);
	ar3 = [sinTblHold];	
	ar4 = gr2; 
	rep 8 wfifo = [ar4++gr4],ftw,wtw; 		// load_wfifo(pN+4096*k2+kk,512,8); 
	gr7 = 2;	
	<Next1_kk>								// for(int kk=0; kk<512; kk++){
		ar4 -= 512*2*8-4096*2; 
		ar0 = ar2; 
		rep 8 data  = [ar0++] with vsum ,data,vr;	// vsum_data(cosTbl,pGRe+512*k+kk,spec->round[1]) 
		rep 8 wfifo = [ar4++gr4],ftw; 				// load_wfifo(pN+4096*k2+kk,512,8);  
		ar1 = ar3 with gr2+=gr7;
		//rep 8 wfifo = [ar4++gr4],ftw; 				// load_wfifo(pN+4096*k2+kk,512,8);  
		ar5 = gr0 with gr0+=gr7;
		//rep 8 wfifo = [ar4++gr4],ftw; 				// load_wfifo(pN+4096*k2+kk,512,8);  
		ar6 = gr1 with gr1+=gr7; 
		//rep 8 wfifo = [ar4++gr4],ftw; 				// load_wfifo(pN+4096*k2+kk,512,8);  
		rep 8 [ar5++gr5] = afifo;
		//-rep 8 wfifo = [ar4++gr4],ftw; 				// load_wfifo(pN+4096*k2+kk,512,8);  
		//gr7 = 2-1;
		//<Next1_k2>							// for(int k2=0; k2<2; k2++){
		
		
		//	with gr7--; 								// kk--;			
		
		rep 8 data = [ar1++],wtw with vsum ,data,0;	// vsum_data(sinTbl,pGIm+1024*k1+512*k2+kk,0);
		//rep 8 wfifo = [ar4++gr4],ftw,wtw; 				// load_wfifo(pN+4096*k2+kk,512,8);  
		rep 8 [ar6++gr6] = afifo ;
		rep 8 data  = [ar0++] with vsum ,data,vr;		// vsum_data(cosTbl,pJRe+64*(k*4+kk)+i);		
		//ar4 -= 512*2*8-4096*2;						// load_wfifo(pN+4096*k2+kk,512,8); 
		ar5 -= 1024*2*8-512*2;						// vsum_data(cosTbl,pGRe+1024*k1+512*k2+kk,
		//if <>0 delayed goto Next1_k2;
		ar6 -= 1024*2*8-512*2;						// vsum_data(sinTbl,pGIm+1024*k1+512*k2+kk,0);	
		// final cycle
		
		
		ar4 = gr2 with gr3--;
		rep 8 wfifo = [ar4++gr4],ftw; 					// load_wfifo(pH+512*kk+i,64,8);	
		rep 8 [ar5++gr5] = afifo;
	if <>0 delayed goto Next1_kk;
		rep 8 data = [ar1++],wtw with vsum ,data,0;		// vsum_data(sinTbl,pJIm+64*(k*4+kk)+i);	sinTbl+=8;
		rep 8 [ar6++gr6] = afifo ;
		
	[cosTblHold]=ar0;	
	[sinTblHold]=ar1;	
	
	//STOP_TIMER();	// Best time=16434; 16434/8192/2 = 1,003356933594 ; 
	//return;  		// 28736 from  12321+16434 = 28755
	// best time when code and sinTbl in the same bank

// -in 
//|.-out-(pN)
//||.-tmp[0] (pGRe)
//|||.-tmp[1] (pGIm)
//||||.-fftTbl[0]
//|||||.-fftTbl[1]
//||||||.-fftTbl[2]
//|||||||.-fftTbl[3]
// |||| | 
//00112020        16442
//00112030        16442
//00113020        16442
//00113030        16442
//00123030        16445
//00132020        16439
//00213030        16442
//00221010        16442
//00221030        16442
//00223010        16442
//00223030        16439
//00231010        16442
//00312020        16442
//00321010        16442
//00331010        16442
//00331020        16439
//00332010        16442
//00332020        16442
//01213030        16434
//01221030        16435
//01223030        16434
//01312020        16434
//01331020        16434
//01332020        16435
//02112030        16434
//02113030        16434
//02123030        16435
//02321010        16434
//02331010        16434
//02332010        16434
//03112020        16434
//03113020        16435
//03132020        16434
//03221010        16434
//03223010        16434
//03231010        16435
	
	
	//ar0 = [pGRe];
	//gr5 = 8192*2;
	//call vec_crc32;
	
	//ar0 = [pGIm];
	//gr5 = 8192*2;
	//call vec_crc32;
	//return;

	//----------------- 1.1 -----------------	
	//for(int i=0;i<8192; i++){
	//	pGRaw[i].re=pGRe[i].re-pGIm[i].im;
	//	pGRaw[i].im=pGRe[i].im+pGIm[i].re;
	//}

	//START_TIMER();
	
	sb  = 000000002h;
	ar4 = GAddCmplxMask;
	gr6 = -2;
	rep 2 wfifo = [ar4++],ftw,wtw;
	gr7 = 8192/32;
	ar2 = [pGRe];
	ar3 = [pGIm];
	ar6 = [pGRaw] with gr7--;
	
	if <>0 delayed skip gr6 with gr7--;
		rep 32 ram  = [ar2++];
		rep 32 data = [ar3++] with vsum, data, ram;
		rep 32 [ar6++] = afifo;

	//STOP_TIMER();	// Best time   8225/8192 = 1,004028320313
	//return ;  //  37953 from max 12321+16434+8225 = 36980

// -in 
//|.-out-(pGRaw)
//||.-tmp[0] (pGRe)
//|||.-tmp[1] (pGIm)
// |||   	
//01230000        8226
//01230010        8225
//01230030        8225
//01231010        8225
//01231020        8225
//01232020        8225
//01232030        8225
//01233010        8225
//01233020        8225
//01320000        8225
//01320010        8225
//01320030        8225
//01321000        8225
//01321010        8225
//01322000        8225
//01322010        8225
//01322030        8225
//01323000        8225
//01323010        8225
//02130000        8225
//02130020        8225
//02130030        8225
//02131010        8225
//02131020        8225
//02131030        8225
//02132000        8225
//02132010        8225
//02132020        8225
//02133000        8225
//02133010        8225
//02133020        8225
//02133030        8224
//02313020        8224
	
	//----------------- 1.2 -----------------			
	//for(int i=0; i<8192; i++){
	//	pG[i].re=pGRaw[i].re>>spec->shift[1];
	//	pG[i].im=pGRaw[i].im>>spec->shift[1];
	//}
	
	//START_TIMER();
	ar0 = [pGRaw]	with gr6=-gr6;	// gr6=2
	ar6 = [pG]		with gr0=gr6;	// gr0=2
	delayed call vec_RShift32s;
		gr4 = [shift1] with gr5=gr0<<13; //	gr5 = 8192*2; /

	//STOP_TIMER();	// Best time=8262; 8262/8192/2=0.504272 ; Best route = 0005ef0
	//return ; //  46195 from max from 12321+16434+8225+8262 = 45242
	CRC32(pG);
	
	// ---------------- 2.0 --------------------
	//for(int kk=0; kk<64; kk++){
	//	cosTbl=cosTblHold;
	//	sinTbl=sinTblHold;
	//	for (int k2=0; k2<16;k2++){
	//		load_wfifo(pG+512*k2+kk,64,8);
	//		for (int k1=0; k1<8;k1++){
	//			int k=16*k1+k2;//for(int k=0; k<128; k++)
	//			vsum_data(cosTbl,pHRe+1024*k1+64*k2+kk,spec->round[2]);	cosTbl+=8;
	//			vsum_data(sinTbl,pHIm+1024*k1+64*k2+kk,0);				sinTbl+=8;
	//		}
	//	}
	//}
	//cosTblHold=cosTbl;
	//sinTblHold=sinTbl;

	
	// 1.2 ===> gr6=2; 	
	//START_TIMER();

	gr0 = [pHRe]		with gr4=false;		//
	gr1 = [pHIm]		with gr4++;			//
	gr2 = [pG]			with gr3=gr4<<6;	// gr3=64 		gr3:for(int kk=0; kk<64; kk++){
	nb1 = 080000000h; 
	sb  = 002020202h 	with gr4=gr3<<1;	// gr4=64*2 	gr4:load_wfifo(pG+512*k2+kk,64,8);
	vr  = 000040h		with gr5=gr4<<4;	// gr5=1024*2	gr5:vsum_data(cosTbl,pHRe+1024*k1+64*k2+kk,spec->round[2])
	ar2 = [cosTblHold] 	with gr6=gr5;		// gr6=1024*2	gr6:vsum_data(sinTbl,pHIm+1024*k1+64*k2+kk,0);
	ar3 = [sinTblHold];	
	ar4 = gr2; 
	rep 8 wfifo = [ar4++gr4],ftw,wtw; 		// load_wfifo(pG+512*k2+kk,64,8);
	
	<Next2_kk>								// for(int kk=0; kk<64; kk++){
		gr7 = 2;
		ar0 = ar2; 
		ar1 = ar3 with gr2+=gr7;
		ar5 = gr0 with gr0+=gr7;
		ar6 = gr1 with gr1+=gr7; 
		ar4 -= 512*2*8-4096*2; 		
		gr7 = 16-1;
		<Next2_k2>							// for (int k2=0; k2<16;k2++){
			rep 8 data  = [ar0++] with vsum ,data,vr;	// vsum_data(cosTbl,pHRe+1024*k1+64*k2+kk
			rep 8 wfifo = [ar4++gr4],ftw; 				// load_wfifo(pN+4096*k2+kk,512,8);  load_wfifo(pH+512*kk+i,64,8);	
			with gr7--; 								// kk--;S	
			rep 8 [ar5++gr5] = afifo;
			rep 8 data = [ar1++],wtw with vsum ,data,0;	// vsum_data(sinTbl,pHIm+1024*k1+64*k2+kk,0);
			rep 8 [ar6++gr6] = afifo ;
			ar4 -= 512*2*8-4096*2;						// load_wfifo(pN+4096*k2+kk,512,8); 
			ar5 -= 1024*2*8-64*2;						// vsum_data(cosTbl,pHRe+1024*k1+64*k2+kk
		if <>0 delayed goto Next2_k2;
			ar6 -= 1024*2*8-64*2;						// vsum_data(sinTbl,pHIm+1024*k1+64*k2+kk,0);
		// final cycle
		rep 8 data  = [ar0++] with vsum ,data,vr;		// vsum_data(cosTbl,pHRe+1024*k1+64*k2+kk
		ar4 = gr2 with gr3--;
		rep 8 wfifo = [ar4++gr4],ftw; 					// load_wfifo(pG+512*k2+kk,64,8);
		rep 8 [ar5++gr5] = afifo;
	if <>0 delayed goto Next2_kk;
		rep 8 data = [ar1++],wtw with vsum ,data,0;		// vsum_data(sinTbl,pHIm+1024*k1+64*k2+kk,0);
		rep 8 [ar6++gr6] = afifo ;
		
	[cosTblHold]=ar0;	
	[sinTblHold]=ar1;	
	
	
	//STOP_TIMER(); // Best time=16752; 16752/8192/2 = 1,0224609375
	//return;    	// 63868 of 12321+16434+8734+8262+16752 = 62503
	
	CRC32(pHRe);
	CRC32(pHIm);

// -in 
//|.-out-(pG)
//||.-tmp[0] (pHRe)
//|||.-tmp[1] (pHIm)
//||||.-fftTbl[0]
//|||||.-fftTbl[1]
//||||||.-fftTbl[2]
//|||||||.-fftTbl[3]
// |||| | 
//00112020        16758
//00112030        16756
//00113020        16756
//00221010        16755
//00221030        16755
//00223030        16755
//00331010        16755
//01213030        16752
//01221030        16752
//01223030        16752
//01312020        16752
//01331020        16752
//01332020        16752
//02123030        16752
//03113020        16752
//03132020        16752
//03221010        16752
//03231010        16752
	
	//---------------------------------- 2.1 -----------------------------------------	
	//for(int i=0;i<8192; i++){
	//	pHRaw[i].re=pHRe[i].re-pHIm[i].im;
	//	pHRaw[i].im=pHRe[i].im+pHIm[i].re;
	//}
	//START_TIMER();

	
	sb  = 000000002h;
	ar4 = GAddCmplxMask;
	gr6 = -2;
	rep 2 wfifo = [ar4++],ftw,wtw;
	gr7 = 8192/32;
	ar6 = [pHRaw] with gr7--;
	ar2 = [pHRe];
	ar3 = [pHIm];
	if <>0 delayed skip gr6 with gr7--;
		rep 32 ram  = [ar2++];
		rep 32 data = [ar3++] with vsum,data, ram;
		rep 32 [ar6++] = afifo;
		
	//STOP_TIMER();	 // Best time=8222; 8732/8192/2=0.532958 ; Best route = 0005ef0
	//return;	  // 72064 from 12321+16434+8225+8262+16752+8222 = 70216
	
	//----------------- 2.2 -----------------					
	//for(int i=0; i<8192; i++){
	//	pH[i].re=pHRaw[i].re>>spec->shift[2];
	//	pH[i].im=pHRaw[i].im>>spec->shift[2];
	//}
	// 2.1 ===> gr6=-2
	//START_TIMER();
	ar0 = [pHRaw]	with gr6 = -gr6; 				// gr6 = 2;
	ar6 = [pH]		with gr0 = gr6;					// gr0 = 2;
	delayed call vec_RShift32s with gr5 = gr0<<13;	// gr5 = 8192*2;
		gr4 = [shift2];
	
	//STOP_TIMER(); // Best time=8262; 8262/8192/2=0.504272 ; Best route = 0000007
	//return;	 // 80300 of 12321+16434+8225+8262+16752+8222+8262 = 78478
	CRC32(pH);
	
	//---------------------------------- 3.0 -----------------------------------------	
	//for(int i=0; i<8; i++){
	//	cosTbl=cosTblHold;
	//	sinTbl=sinTblHold;
	//	for (int k2=0; k2<128;k2++){
	//		load_wfifo(pH+64*k2+i,8,8);
	//		for (int k1=0; k1<8;k1++){
	//			vsum_data(cosTbl,pJRe+1024*k1+8*k2+i,spec->round[3]);	cosTbl+=8;
	//			vsum_data(sinTbl,pJIm+1024*k1+8*k2+i,0);				sinTbl+=8;
	//		}
	//	}
	//}

	//START_TIMER();	
		
	
	gr0 = [pJRe]		with gr4=false;		//
	gr1 = [pJIm]		with gr4++;			//
	gr2 = [pH]			with gr3=gr4<<3;	// gr3=8 		gr3:for(int i=0; i<8; i++){
	nb1 = 080000000h; 
	sb  = 002020202h 	with gr4=gr3<<1;	// gr4=8*2 		gr4:load_wfifo(pH+64*k2+i,8,8);
	vr  = 000040h		with gr5=gr4<<7;	// gr5=1024*2	gr5:vsum_data(cosTbl,pJRe+1024*k1+8*k2+i,spec->round[3]);
	ar2 = [cosTblHold] 	with gr6=gr5;		// gr6=1024*2	gr6:vsum_data(sinTbl,pJIm+1024*k1+8*k2+i,0);
	ar3 = [sinTblHold];	
	ar4 = gr2; 
	rep 8 wfifo = [ar4++gr4],ftw,wtw; 		// load_wfifo(pH+64*k2+i,8,8);
	
	<Next3_kk>								// for(int i=0; i<8; i++){
		gr7 = 2;
		ar0 = ar2; 
		ar1 = ar3 with gr2+=gr7;
		ar5 = gr0 with gr0+=gr7;
		ar6 = gr1 with gr1+=gr7; 
		ar4 -= 8*2*8-64*2; 
		gr7 = 128-1;
		<Next3_k2>							// for (int k2=0; k2<128;k2++){
			rep 8 data  = [ar0++] with vsum ,data,vr;	// vsum_data(cosTbl,pJRe+1024*k1+8*k2+i,spec->round[3]);
			rep 8 wfifo = [ar4++gr4],ftw; 				// load_wfifo(pH+64*k2+i,8,8);
			with gr7--; 								// kk--;
			rep 8 [ar5++gr5] = afifo;
			rep 8 data = [ar1++],wtw with vsum ,data,0;	// vsum_data(sinTbl,pJIm+1024*k1+8*k2+i,0);
			rep 8 [ar6++gr6] = afifo ;
			ar4 -= 8*2*8-64*2;						// load_wfifo(pH+64*k2+i,8,8); 
			ar5 -= 1024*2*8-8*2;						// vsum_data(cosTbl,pJRe+1024*k1+8*k2+i,spec->round[3]);
		if <>0 delayed goto Next3_k2;
			ar6 -= 1024*2*8-8*2;						// vsum_data(sinTbl,pJIm+1024*k1+8*k2+i,0);
		// final cycle
		ar4 = gr2 with gr3--;
		rep 8 data  = [ar0++] with vsum ,data,vr;		// vsum_data(cosTbl,pJRe+1024*k1+8*k2+i,spec->round[3]);
		rep 8 wfifo = [ar4++gr4],ftw; 					// load_wfifo(pH+64*k2+i,8,8);
		rep 8 [ar5++gr5] = afifo;
	if <>0 delayed goto Next3_kk;
		rep 8 data = [ar1++],wtw with vsum ,data,0;		// vsum_data(sinTbl,pJIm+1024*k1+8*k2+i,0);
		rep 8 [ar6++gr6] = afifo ;
		
	[cosTblHold]=ar0;	
	[sinTblHold]=ar1;
	
		
	
	CRC32(pJRe);
	CRC32(pJIm);
	
	//STOP_TIMER();		// Best time=16480; 16480/8192/2=1.005859 ; Best route = 0000007
	//return ;  			// 97324 from 12321+16434+8225+8262+16752+8222+8262+16480 = 94958
	
	//---------------------------------- 3.1 -----------------------------------------	
	//for(int i=0;i<8192; i++){
	//	pJRaw[i].re=pJRe[i].re-pJIm[i].im;
	//	pJRaw[i].im=pJRe[i].im+pJIm[i].re;
	//}
	
	//START_TIMER();

	
	sb  = 000000002h;
	ar4 = GAddCmplxMask;
	gr6 = -2;
	rep 2 wfifo = [ar4++],ftw,wtw;
	gr7 = 8192/32;
	ar6 = [pJRaw] with gr7--;
	ar2 = [pJRe];
	ar3 = [pJIm];
	if <>0 delayed skip gr6 with gr7--;
		rep 32 ram  = [ar2++];
		rep 32 data = [ar3++] with vsum,data, ram;
		rep 32 [ar6++] = afifo;
		
	//STOP_TIMER();	 // Best time=8222; 
	//return;		
	

	//----------------- 3.2 -----------------					
	//for(int i=0; i<8192; i++){
	//	pJ[i].re=pJRaw[i].re>>spec->shift[3];
	//	pJ[i].im=pJRaw[i].im>>spec->shift[3];
	//}
	// 2.1 ===> gr6=-2
	//START_TIMER();
	ar0 = [pJRaw]	with gr6 = -gr6; 				// gr6 = 2;
	ar6 = [pJ]		with gr0 = gr6;					// gr0 = 2;
	delayed call vec_RShift32s with gr5 = gr0<<13;	// gr5 = 8192*2;
		gr4 = [shift2];
	
	//STOP_TIMER(); // Best time=8262; 8262/8192/2=0.504272 ; Best route = 0000007
	//return ;  // 113760 from max 12321+16434+8225+8262+16752+8222+8262+16480+8222+8262 = 111442
	
	CRC32(pJ);
	
	//---------------------------------- 4.0 -----------------------------------------
	//for (int k2=0; k2<1024; k2++){
	//	load_wfifo(pJ+8*k2,1,8);
	//	for (int k1=0; k1<8; k1++){
	//		vsum_data(cosTbl,pYRe+1024*k1+k2,spec->round[4]);	cosTbl+=8;
	//		vsum_data(sinTbl,pYIm+1024*k1+k2,0);				sinTbl+=8;
	//	}
	//}
	//START_TIMER();
	sb  = 002020202h	with gr7 = gr6<<9;	// gr7 = 1024		gr7: for (int k2=0; k2<1024; k2++){
	nb1 = 080000000h	with gr5 = gr7<<1;	// gr5 = 1024*2		vsum_data(cosTbl,pYRe+1024*k1+k2,spec->round[4]);
	ar4 = [pJ] 			with gr6 = gr5;		// gr6 = 1024*2;		vsum_data(sinTbl,pYIm+1024*k1+k2,0);
	rep 8 wfifo = [ar4++],ftw,wtw; 			// load_wfifo(pJ+8*k2,1,8);
	ar0 = [cosTblHold2]	with gr7--;			// 
	ar1 = [sinTblHold2];
	ar5 = [pYRe];	
	ar6 = [pYIm];
	<Next4_k2>								// for (int k2=0; k2<1024; k2++){
		rep 8 data=[ar0++] with vsum ,data,vr;		// vsum_data(cosTbl,pYRe+1024*k1+k2,spec->round[4]);
		rep 8 wfifo = [ar4++],ftw; 					// load_wfifo(pJ+8*k2,1,8);
		rep 8 [ar5++gr5] = afifo;
		with gr7--;									// k2--	
		rep 8 data=[ar1++],wtw with vsum ,data,0;	// vsum_data(sinTbl,pYIm+1024*k1+k2,0);
		rep 8 [ar6++gr6] = afifo ;
		ar5-= 1024*2*8-2;
	if <>0 delayed goto Next4_k2;		
		ar6-= 1024*2*8-2;
	
	// final cycle
	rep 8 data=[ar0++] with vsum ,data,vr;	// vsum_data(cosTbl,pYRe+1024*k1+k2,spec->round[4]);
	rep 8 [ar5++gr5] = afifo;
	rep 8 data=[ar1++] with vsum ,data,0;	// vsum_data(sinTbl,pYIm+1024*k1+k2,0);
	rep 8 [ar6++gr6] = afifo ;
	
	//STOP_TIMER(); // Best time=17446; 17446/8192/2=1.064819 ; Best route = 0000007
	//return; //  131174 from 12321+16434+8225+8262+16752+8222+8262+16480+8222+8262+17446 = 128888
	
	
	
	CRC32(pYRe);
	CRC32(pYIm);
	
	
	
	//---------------------------------- 4.1 -----------------------------------------	
	//for(int i=0;i<8192; i++){
	//	pYRaw[i].re=pYRe[i].re-pYIm[i].im;
	//	pYRaw[i].im=pYRe[i].im+pYIm[i].re;
	//}
	//START_TIMER();
	sb  = 000000002h;
	ar4 = GAddCmplxMask;
	gr6 = -2;
	rep 2 wfifo = [ar4++],ftw,wtw;
	gr7 = 8192/32;
	ar6 = [pYRaw] with gr7--;
	ar2 = [pYRe];
	ar3 = [pYIm];
	if <>0 delayed skip gr6 with gr7--;
		rep 32 ram  = [ar2++];
		rep 32 data = [ar3++] with vsum,data, ram;
		rep 32 [ar6++] = afifo;
	//STOP_TIMER(); 	// Best time=8222
	//return; 		//  139370 from 12321+16434+8225+8262+16752+8222+8262+16480+8222+8262+17446+8222 = 137110
	// 137110-139370 = -2260 wast
	CRC32(pYRaw);
	

.wait;
return ;		
	
	
global _nmppsFFT8192Fwd28888Raw	:label;
      <_nmppsFFT8192Fwd28888Raw>

	ar5=sp-2	;
	push ar0,gr0;			
	push ar1,gr1;		
	push ar2,gr2;
	push ar3,gr3;
	push ar4,gr4;
	push ar5,gr5;	
	push ar6,gr6;
	
	ar0 = [--ar5];						// src[8192*2]
	ar6 = [--ar5];						// dst[8192*2]
	ar5 = [--ar5];						// spec
	gr1 = [ar5++];						// tmp0[8192*2]
	gr2 = [ar5++];						// tmp1[8192*2]
	gr3 = [ar5++];						// weights[]
	gr4 = [ar5++];						// weights[]
	[cosTblHold] = gr3;
	[sinTblHold] = gr4;
	[pX]   = ar0;
	[pHRe] = gr1;
	[pHIm] = gr2;
	[pH]   = ar6;
	[pJRe] = gr1;
	[pJIm] = gr2;
	[pJRaw]= ar6;
	[pJ]   = gr2;
	[pIRe] = gr1;
	[pIIm] = ar6;
	[pIRaw]= gr2;
	[pI]   = ar6;
	[pYRe] = gr1;
	[pYIm] = gr2;
	[pYRaw]= ar6;
	gr0 = [ar5++];
	gr1 = [ar5++];
	gr2 = [ar5++];
	[shift1]=gr1;
	delayed call nmppsFFT8192Fwd28888Core;
		[shift2]=gr2;	
		
	pop ar6,gr6;
	pop ar5,gr5;
	pop ar4,gr4;
	pop ar3,gr3;
	pop ar2,gr2;
	pop ar1,gr1;
	pop ar0,gr0;
return;

	

	
global _nmppsFFT8192Fwd28888	:label;
      <_nmppsFFT8192Fwd28888>
.branch;
	ar5=sp-2	;
	push ar0,gr0;			
	push ar1,gr1;		
	push ar2,gr2;
	push ar3,gr3;
	push ar4,gr4;
	push ar5,gr5;	
	push ar6,gr6;
	
	ar0 = [--ar5];						// src[8192*2]
	ar6 = [--ar5];						// dst[8192*2]
	ar5 = [--ar5];						// spec
	gr1 = [ar5++];						// tmp0[8192*2]
	gr2 = [ar5++];						// tmp1[8192*2]
	ar3 = [ar5++];						// weights[]
	gr3 = [ar5++];						// weights[]
	ar4 = [ar5++];						// weights[]
	gr4 = [ar5++];						// weights[]
	[cosTblHold] = ar3;
	[sinTblHold] = ar4;
	[cosTblHold2]= gr3;
	[sinTblHold2]= gr4;
	[pX]   = ar0;
	[pN]   = gr1;
	
	[pGRe] = ar6; 
	[pGIm] = gr2;
	
	[pGRaw]= gr1;
	[pG]   = ar6;
	
	[pHRe] = gr1;
	[pHIm] = gr2;
	
	[pHRaw]= ar6;
	[pH]   = gr1;	
	
	[pJRe] = gr2;
	[pJIm] = ar6;
	[pJRaw]= gr1;
	[pJ]   = gr2; 
	
	[pYRe] = ar6;
	[pYIm] = gr1;
	[pYRaw]= gr2;
	[pY]   = ar6;
	
	gr0 = [ar5++];
	gr1 = [ar5++];
	gr2 = [ar5++];
	gr3 = [ar5++];
	gr4 = [ar5++];
	[shift1]=gr1;
	[shift2]=gr2;
	[shift3]=gr3;
	delayed call nmppsFFT8192Fwd28888Core;
		[shift4]=gr4;
	
	
	//----------------- 3.2 -----------------				
	//	for(int i=0; i<8192; i++){
	//		pY[i].re=pYRaw[i].re>>spec->shift[3];
	//		pY[i].im=pYRaw[i].im>>spec->shift[3]; 
	//}
	
	ar0 = [pYRaw] 	with gr0=false;
	ar6 = [pY]		with gr0++;
	gr5 = 8192*2 	with gr0++;	// gr0=2
	//START_TIMER();
	delayed call vec_RShift32s with gr6=gr0;
		gr4 = [shift4] with gr1=gr7;
	
	
	//STOP_TIMER(); // Best time=8259; 8259/8192/2=0.504089 ; Best route = 80000000
	pop ar6,gr6 with gr7=gr1;
	pop ar5,gr5;
	pop ar4,gr4;
	pop ar3,gr3;
	pop ar2,gr2;
	pop ar1,gr1;
	pop ar0,gr0;
return ;
.wait;

//0:12321
//1:16434+8225+8262
//2:16752+8222+8262
//3:16480+8222+8262
//4:17446+8222+8259
//summary:12321+16434+8225+8262+16752+8222+8262+16480+8222+8262+17446+8222+8259 = 145369 (hypotetical maximum)
//real:147897



// FFTFwd8192:        
// .-in 
// |.-out
// ||.-tmp[0] 
// |||.-tmp[1] 
// ||||.-fftTbl[0]
// |||||.-fftTbl[1]
// ||||||.-fftTbl[2]
// |||||||.-fftTbl[3]
// ||||||||        clocks
// 01232013        154534
// 01232103        147897 *
// 01232301        154038
// 01323012        154534
// 01323102        147898 *
// 01323201        154038
// 02131023        154535
// 02131203        147898 *
// 02131302        154038
// 02313021        154534
// 02313102        154032
// 02313201        147897 *
// 03121032        154528
// 03121203        154039
// 03121302        147897 *
// 03212031        154534
// 03212103        154032
// 03212301        147897 *
// 11232003        147901 *
// 11232300        151984
// 11323002        147901 *
// 11323200        151978
// 12132003        154567
// 12313002        154039
// 12313200        151984
// 13123002        154566
// 13212003        154039
// 13212300        152028
// 21231003        154592
// 21323001        154039
// 21323100        151984
// 22131003        147901 *
// 22131300        151984
// 22313001        147901 *
// 22313100        151984
// 23121003        154089
// 23121300        151984
// 23213001        154567
// 31232001        154039
// 31232100        151984
// 31321002        154566
// 32131002        154038
// 32131200        151984
// 32312001        154566
// 33121002        147901 *
// 33121200        152036
// 33212001        147900 *
// 33212100        151984 
//

// if in-place src=dst
// 1-232003        147901
// 1-232103        147898
// 1-323002        147900
// 1-323102        147948
// 2-131003        147900
// 2-131203        147898
// 2-313001        147901
// 2-313201        147898
// 3-121002        147901
// 3-121302        147898
// 3-212001        147901
// 3-212301        147898

// 147897/8192 = 18,05383300781
end ".text_nmplv";