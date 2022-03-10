extern vec_Add:label;
import from macros.mlb;
begin ".text_nmplv"
//------------------------------------------------------------------------------------------------
//! \fn void _nmppsAdd_64sc(nm64sc *pSrcVec1, nm64sc *pSrcVec2, nm64sc *pDstVec, int nSize);
//! 
//! \perfinclude _nmppsAdd_64sc.html 
//------------------------------------------------------------------------------------------------


global _nmppsAdd_64sc :label;
<_nmppsAdd_64sc>


.branch;
	ar5 = sp - 2;
	push ar0,gr0 with gr0=false;
	push ar1,gr1 with gr0++;
	push ar5,gr5 with gr0++;		// gr0=2 
	push ar6,gr6 with gr1=gr0;
	ar0 = [--ar5];	// pSrcVec1
	ar1 = [--ar5];	// pSrcVec2
	ar6 = [--ar5];	// pDstVec
	gr5 = [--ar5];	// nSize in 64-bit elements
	
	nb1 = 0 with gr5<<=1;		
	delayed call vec_Add with gr1=gr0;
		wtw;						
		gr6=gr0;					// gr6=2
	pop ar6,gr6;
	pop ar5,gr5;
	pop ar1,gr1;
	pop ar0,gr0;
return with gr7=false;
.wait;
end ".text_nmplv";
