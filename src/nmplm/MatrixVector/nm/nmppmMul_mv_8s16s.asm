//------------------------------------------------------------------------
//
//  $Workfile:: mtrMulMV8_ss.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2005/01/12 14:05:15 $
//
//! \if file_doc
//!
//! \file   mtrMulMV8_ss.asm
//! \author Сергей Мушкаев
//! \brief  Умножение матрицы на вектор.
//!
//! \endif
//!
//------------------------------------------------------------------------
//#include "vArithm.h"
extern mtr_Acc8MulMV4:label;

extern	vec_ar0gr0:long;
extern	vec_ar1gr1:long;
extern	vec_ar2gr2:long;
extern	vec_ar3gr3:long;
extern	vec_ar4gr4:long;
extern	vec_ar5gr5:long;
extern	vec_ar6gr6:long;
extern	vec_ar7gr7:long;
extern  _nmppsTmpBuffer64_G_:long[64];
extern  _nmppsTmpBuffer64_L_:long[64];

data ".data_nmplm_G"
	WSum4CharBuffersIn1:long[32]=(
				0000000000000001hl,
				0000000000000001hl,
				0000000000000001hl,
				0000000000000001hl,
				0000000000000001hl,
				0000000000000001hl,
				0000000000000001hl,
				0000000000000001hl,
				0000000000010000hl,
				0000000000010000hl,
				0000000000010000hl,
				0000000000010000hl,
				0000000000010000hl,
				0000000000010000hl,
				0000000000010000hl,
				0000000000010000hl,
				0000000100000000hl,
				0000000100000000hl,
				0000000100000000hl,
				0000000100000000hl,
				0000000100000000hl,
				0000000100000000hl,
				0000000100000000hl,
				0000000100000000hl,
				0001000000000000hl,
				0001000000000000hl,
				0001000000000000hl,
				0001000000000000hl,
				0001000000000000hl,
				0001000000000000hl,
				0001000000000000hl,
				0001000000000000hl
					  );


end ".data_nmplm_G";



begin ".text_nmplm"



/////////////////////////////////////////////////////////////////////////////////////////


//------------------------------------------------------------------------
//! \fn void nmppmMul_mv_ ( v8nm16s *pSrcMtr,  v8nm16s *pSrcVec8, nm16s *pDstVec, int nHeight);
//!
//! \perfinclude _nmppmMul_mv___F7v8nm16sP7v8nm16sPPSsi.html
//------------------------------------------------------------------------

global _nmppmMul_mv___F7v8nm16sP7v8nm16sPPSsi:label;
global _void._.8.8nmppmMul_mv_.1class._v8nm16s._.0.9._class._v8nm16s._.0.9._short._.0.9._int.2 :label;
<_nmppmMul_mv___F7v8nm16sP7v8nm16sPPSsi>
<_void._.8.8nmppmMul_mv_.1class._v8nm16s._.0.9._class._v8nm16s._.0.9._short._.0.9._int.2>
.branch;
	ar5 = sp - 2;

	
	push ar0,gr0;
	push ar1,gr1;
	push ar2,gr2;
	push ar3,gr3;
	push ar4,gr4;
	push ar5,gr5;
	push ar6,gr6;

	ar0 = [--ar5];	//		nm16s*		SrcMtr,			// input  matrix					:long Global [8*Height/
	ar1 = [--ar5];	//		nm16s*		SrcVec8,		// input  vector of 8 16-bit words	:long Local  [2]
	ar6 = [--ar5];	//			nm16s*		pDstVec,			// output vector					:long Global [Height/4]
	gr5 = [--ar5];	//			int			nHeight			// Matrix height					:=[0,1,2,...]

	gr7 = ar0;
	with gr7;
	if < delayed skip 4;
		ar3 = _nmppsTmpBuffer64_L_;
	ar3 = _nmppsTmpBuffer64_G_;
	ar5 = ar3;	
	gr0 = [ar1++] with gr6 = true;
	gr1 = [ar1++] with gr6>>=16;		// gr6= 0x0000FFFF
	gr2 = [ar1++] with gr7=gr6<<16;		// gr7= 0xFFFF0000
	gr3 = [ar1++] with gr4 = false;	
	
	
	ar4 = gr4	  with gr4 = gr0 and gr6;
	[ar3++] = gr4;	
	[ar3++] = ar4 with gr4 = gr0 >>16;
	[ar3++] = gr4;
	[ar3++] = ar4 with gr4 = gr1 and gr6;
	[ar3++] = gr4;
	[ar3++] = ar4 with gr4 = gr1 >>16; 
	[ar3++] = gr4;	
	[ar3++] = ar4 with gr4 = gr2 and gr6;
	[ar3++] = gr4;
	[ar3++] = ar4 with gr4 = gr2 >>16;
	[ar3++] = gr4 ;
	[ar3++] = ar4 with gr4 = gr3 and gr6;
	[ar3++] = gr4;
	[ar3++] = ar4 with gr4 = gr3 >>16;
	[ar3++] = gr4;
	[ar3++] = ar4
	
				  with gr4 = gr0 <<16;
	[ar3++] = gr4 ;	
	[ar3++] = ar4 with gr4 = gr0 and gr7;
	[ar3++] = gr4 ;
	[ar3++] = ar4 with gr4 = gr1 <<16;
	[ar3++] = gr4 ;
	[ar3++] = ar4 with gr4 = gr1 and gr7; 
	[ar3++] = gr4 ;	
	[ar3++] = ar4 with gr4 = gr2 <<16;
	[ar3++] = gr4 ;
	[ar3++] = ar4 with gr4 = gr2 and gr7;
	[ar3++] = gr4 ;
	[ar3++] = ar4 with gr4 = gr3 <<16;
	[ar3++] = gr4 ;
	[ar3++] = ar4 with gr4 = gr3 and gr7;
	[ar3++] = gr4;
	[ar3++] = ar4


						with gr4 = gr0 and gr6;
	[ar3++] = ar4,gr4	with gr4 = gr0 >>16;
	[ar3++] = ar4,gr4	with gr4 = gr1 and gr6;
	[ar3++] = ar4,gr4	with gr4 = gr1 >>16;
	[ar3++] = ar4,gr4	with gr4 = gr2 and gr6;
	[ar3++] = ar4,gr4	with gr4 = gr2 >>16;
	[ar3++] = ar4,gr4	with gr4 = gr3 and gr6;
	[ar3++] = ar4,gr4	with gr4 = gr3 >>16;
	[ar3++] = ar4,gr4
						
						with gr4 = gr0 <<16;
	[ar3++] = ar4,gr4	with gr4 = gr0 and gr7;
	[ar3++] = ar4,gr4	with gr4 = gr1 <<16;
	[ar3++] = ar4,gr4	with gr4 = gr1 and gr7;
	[ar3++] = ar4,gr4	with gr4 = gr2 <<16;
	[ar3++] = ar4,gr4	with gr4 = gr2 and gr7;
	[ar3++] = ar4,gr4	with gr4 = gr3 <<16;
	[ar3++] = ar4,gr4	with gr4 = gr3 and gr7;
	[ar3++] = ar4,gr4	with gr7=false;

	ar4 = ar5			with gr7++;
	gr4 = 80008000h		with gr6=gr7+1;		// gr6=2		
	sb  = 00020002h		with gr0=gr6<<3;	// gr0=16
	ar1 = ar0+2			with gr1=gr0;		// gr1=16
	ar2 = ar0+4			with gr2=gr0;		// gr2=16	
	ar3 = ar0+6			with gr3=gr0;		// gr3=16

	[vec_ar0gr0] = ar0,gr0;
	[vec_ar1gr1] = ar1,gr1;
	[vec_ar2gr2] = ar2,gr2;
	[vec_ar3gr3] = ar3,gr3;
	ar0 = ar0+8 ; 
	ar1 = ar0+2;
	ar2 = ar0+4;
	ar3 = ar0+6;
	[vec_ar4gr4] = ar0,gr0;
	[vec_ar5gr5] = ar1,gr1;
	[vec_ar6gr6] = ar2,gr2;
	[vec_ar7gr7] = ar3,gr3;
	delayed call mtr_Acc8MulMV4 with gr5>>=2;
		nul;
		nul;
	
	pop ar6,gr6;
	pop ar5,gr5;
	pop ar4,gr4;
	pop ar3,gr3;
	pop ar2,gr2;
	pop ar1,gr1;
	pop ar0,gr0;

	return with gr7=false;
.wait;
end ".text_nmplm";
 