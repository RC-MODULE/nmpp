begin ".text_nmplm"

//=================================================
// Вычисляет произведение матрицы на вектор, оба комплексные, оба nm64s.
//
// В векторе nQuantity ненулевых элементов,
// начиная с номера nStart.
// Тип результатa nm64s.
// time=W*H*16 тактов

//------------------------------------------------------------------------------------------------
//! \fn void MTR_ProdV_Zero( nm64sc *pSrcMtr,  nm64sc *pSrcVec, nm64sc *pDstVec, int nStart, int nQuantity, int nHeight, int nWidth, void*tmp)
//! 
//! \perfinclude _MTR_ProdV_Zero__F6nm64scPC6nm64scPC6nm64scPiiiiPv.html 
//------------------------------------------------------------------------------------------------

global _MTR_ProdV_Zero__F6nm64scPC6nm64scPC6nm64scPiiiiPv:label;
global _void._.8.8MTR_ProdV_Zero.1class._nm64sc._const._.0.9._class._nm64sc._const._.0.9._class._nm64sc._.0.9._int.9._int.9._int.9._int.9._void._.0.2 :label;
<_MTR_ProdV_Zero__F6nm64scPC6nm64scPC6nm64scPiiiiPv>
<_void._.8.8MTR_ProdV_Zero.1class._nm64sc._const._.0.9._class._nm64sc._const._.0.9._class._nm64sc._.0.9._int.9._int.9._int.9._int.9._void._.0.2>
    ar5=ar7-2 with gr7=false; // gr7 for nb1
    push ar0,gr0;
	push ar1,gr1;
	push ar2,gr2;
	push ar3,gr3;
	push ar4,gr4;
	push ar5,gr5;
	push ar6,gr6;

    gr2=[--ar5];  // MTR complex
    ar0=[--ar5];  // Vector complex
    ar6=[--ar5];  // dst complex
    gr0=[--ar5];  // nStart
    gr1=[--ar5];  // nQuantity
    gr4=[--ar5]with gr0<<=2;   // gr4=H, gr2=&MTR[nStart]
    gr3=[--ar5]with gr2+=gr0;  // gr3=Wstride, gr0=4*nStart
    ar4=[--ar5];  // tmp
    ar3=gr1;      // Width for loops
// Если не от начала вектора то сдвинем ar0
//!!    ar0=ar0+gr0;  // ar0=&Vector[nStart]
extern ProdVjobStart:label;
skip ProdVjobStart;
end ".text_nmplm";