import from macros.mlb;
extern vec_Sub:label;
begin ".text_nmplv"
//------------------------------------------------------------------------------------------------
//! \fn void nmppsSub(nm64sc *pSrcVec1, nm64sc *pSrcVec2, nm64sc *pDstVec, int nSize);
//! 
//! \perfinclude _nmppsSub__F6nm64scP6nm64scP6nm64scPi.html 
//------------------------------------------------------------------------------------------------

global _void._.8.8nmppsSub.1class._nm64sc._.0.9._class._nm64sc._.0.9._class._nm64sc._.0.9._int.2 :label;
<_void._.8.8nmppsSub.1class._nm64sc._.0.9._class._nm64sc._.0.9._class._nm64sc._.0.9._int.2>
.branch;
	ar5 = sp - 2 with gr7=false;
	nb1 = gr7;			
	push ar0,gr0 with gr7++;
	push ar1,gr1 with gr0=gr7+1;	// gr0=2
	push ar5,gr5 with gr1=gr0;		// gr1=2 
	push ar6,gr6 with gr6=gr0;		// gr6=2

	ar0 = [--ar5];	// pSrcVec1
	ar1 = [--ar5];	// pSrcVec2
	ar6 = [--ar5];	// pDstVec
	gr5 = [--ar5];	// nSize in 64-bit elements
	
	delayed call vec_Sub with gr5<<=1;
		nul;
		wtw;

	pop ar6,gr6;
	pop ar5,gr5;
	pop ar1,gr1;
	pop ar0,gr0;
	return;
.wait;
end ".text_nmplv";
