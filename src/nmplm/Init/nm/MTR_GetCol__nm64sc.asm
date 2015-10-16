import from macros.mlb;
begin ".text_nmplm"
//------------------------------------------------------------------------------
//
//	Вынимает из матрицы один столбец.
// .
//------------------------------------------------------------------------------------------------
//! \fn void MTR_GetCol( nm64sc *pSrcMtr, nm64sc *pDstVec, int nCol, int nHeight, int nWidth);
//! 
//! \perfinclude _MTR_GetCol__F6nm64scP6nm64scPiii.html
//------------------------------------------------------------------------------------------------

//global _MTR_GetCol__F6nm64scPC6nm64scPiii:label;
global _void._.8.8MTR_GetCol.1class._nm64sc._.0.9._class._nm64sc._.0.9._int.9._int.9._int.2 :label;
//<_MTR_GetCol__F6nm64scPC6nm64scPiii>
<_void._.8.8MTR_GetCol.1class._nm64sc._.0.9._class._nm64sc._.0.9._int.9._int.9._int.2>
    ar5=ar7-2 with gr7=false; // gr7 for nb1
    push ar2,gr2;
    push ar6,gr6;
    ar2=[--ar5];  // MTR complex
    ar6=[--ar5];  // Result vector
    gr2=[--ar5];  // nColomn
.wait;
nb1=gr7 with gr2<<=2;//gr2=4*Colomn
wtw;.branch;
    gr6=[--ar5];   // gr6=H, gr7=4*W
    gr7=[--ar5];   // gr7=W,  
    gr7--;
    ar2=ar2+gr2 with gr2=gr7<<2;// ar2=MTR+4*nColomn
    
Extr0:label;gr7=Extr0 with gr6--;
<Extr0> if > delayed goto gr7 with gr6--;
   rep 2 data=[ar2++]with data;  // 1компл. число
   rep 2 [ar6++]=afifo;
   ar2=ar2+gr2;
   pop ar6,gr6;
   pop ar2,gr2;    
    return;
//=========================
end ".text_nmplm";

