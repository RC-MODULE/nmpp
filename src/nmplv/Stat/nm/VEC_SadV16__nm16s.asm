//-----------------------------------------------------------------------------
//
// $Workfile:: SadV16.asm                             $
//
// Vector processing library
//
// $Revision: 1.1 $        $Date: 2004/11/22 13:50:11 $
//
//! \if file_doc
//!
//! \file   SadV16.asm
//! \author Sergey Mushkaev
//! \breif  Sum of Absolute difference 
//! 
//! \endif 
//!
//----------------------------------------------------------------------------

//import from macros.mlb;

extern	_nmppsTmpBuffer64_G_:long;
extern _VEC_TBL_One_G:long;

begin ".text_nmplv"


//--------------------------------------------------------------------
//! \fn int nmppsSadV16_16s(nm16s* pSrc1,nm16s* pSrc2);
//!
//! \perfinclude _nmppsSadV16_16s.html
//--------------------------------------------------------------------

global _nmppsSadV16_16s:label;
<_nmppsSadV16_16s>
.branch;
	ar5 = _VEC_TBL_One_G;
	rep 4 wfifo=[ar5];

	ar5=ar7-2;
	push ar0,gr0 with gr7=true;
	push ar1,gr1;
	push ar6,gr6 with gr6=gr7+gr7;
	
	ar0=[--ar5];	// Signature 1
	ar1=[--ar5];	// Signature 2
	nb1 = 080008000h;
	sb  = 000020002h; 
	f1cr= 080008000h;
	ar5 = _nmppsTmpBuffer64_G_;
	wtw;
	ar6 = ar5 with gr7=false;
	rep 4 data =[ar0++]		with data;
	rep 4 data =[ar1++]		with data-afifo;
	rep 4 [ar5++]=afifo		with 0-afifo;
	nb1 = gr7;
	rep 4 [ar5],ram=afifo, ftw	with activate afifo;
	rep 4 data=[ar6++]		with mask afifo,data,ram;
	//WTW_REG_DEPRICATED(gr7);
	wtw;
	rep 4					with vsum ,afifo,0;
	rep 4 [ar6++]=afifo;
	
	gr0=[ar6+=gr6];
	gr0=[ar6+=gr6] with gr7 =gr0;
	gr0=[ar6+=gr6] with gr7+=gr0;
	gr0=[ar6+=gr6] with gr7+=gr0;
	pop ar6,gr6    with gr7+=gr0;
	pop ar1,gr1;
	pop ar0,gr0;

	return;
.wait;

end ".text_nmplv";

