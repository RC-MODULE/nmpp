import from macros.mlb;
begin ".text_nmplm"

//============================================================
// 5,6
//	Вычисляет произведение вектор-столбца на сопряженный к 
//    нему-же (получается квадратная матрица).
// 25 тактов на комплексное число результата
// при размере вектора >8, 41 такт при размере 4 и
// 68 при размере 2.

//------------------------------------------------------------------------------------------------
//! \fn void MTR_ProdSelfV( nm64sc *pSrcVec, nm64sc *pDstMtr, int nSize, void* pTmp);
//! 
//! \perfinclude _MTR_ProdSelfV__F6nm64scP6nm64scPiPv.html 
//------------------------------------------------------------------------------------------------

//global _MTR_ProdSelfV__F6nm64scPC6nm64scPi:label;
//      <_MTR_ProdSelfV__F6nm64scPC6nm64scPi>
global _void._.8.8MTR_ProdSelfV.1class._nm64sc._.0.9._class._nm64sc._.0.9._int.9._void._.0.2 :label;
extern _nmppsTmpBuffer256_G_: long; 
<_void._.8.8MTR_ProdSelfV.1class._nm64sc._.0.9._class._nm64sc._.0.9._int.9._void._.0.2>

    ar5=ar7-2 with gr7=false; // gr7 for nb1
    push ar0,gr0;
	push ar1,gr1;
	push ar2,gr2;
	push ar3,gr3;
	push ar4,gr4;
	push ar5,gr5;
	push ar6,gr6;

    gr6=[--ar5];  // Vector complex
    ar6=[--ar5];  // dst = MTR complex
    gr5=[--ar5];  // L=Length
ar4=[--ar5]; // pTmp
[_nmppsTmpBuffer256_G_]=ar4;
//=====================================================
   nb1=gr7 with gr4=gr3<<1;  // gr4=2*L кол-во 64р чисел 
   sb=gr7 with  gr0=gr7-1;   // gr0=-1;
   ar4=[_nmppsTmpBuffer256_G_] with gr0--;  // gr0=-2  
.branch;
// Почленное умножение эл-тов вектора:
// На i-й эл-т вектора множатся все эл-ты .
   ar0=gr6 with gr2=gr5;  // ar0=Vector,  gr2=saved L
//----- Начинальник -----
   ar1=ar0;
   rep 1 wfifo=[ar0++],ftw;  // x0
   nul;
//--------------------------------
   ar2=ar1;
.wait;nb1=gr7;wtw;.branch;   // matr=x0
   rep 1 wfifo=[ar0++],ftw;  // y0
   gr3=gr5-1;
<Vv1> if > delayed skip Vv1 with gr3--;
   rep 2 data=[ar1++]with vsum,data,0;
   rep 2 [ar4++]=afifo;
.wait;nb1=gr7;wtw;.branch;   // matr=y0
<Vv0>
//--------------------------------
   rep 1 wfifo=[ar0++],ftw;  // x1
   gr3=gr5-1;
<Vv2> if > delayed skip Vv2 with gr3--;
   rep 2 data=[ar2++]with vsum,data,0;
   rep 2 [ar4++]=afifo;
   ar1=ar0+gr0;ar2=ar1 with gr5--;
.wait;nb1=gr7;wtw;.branch;   // matr=x1
   rep 1 wfifo=[ar0++],ftw;  // y1
   gr3=gr5-1;
<Vv3> if > delayed skip Vv3 with gr3--;
   rep 2 data=[ar1++]with vsum,data,0;
   rep 2 [ar4++]=afifo;
.wait;nb1=gr7 with gr5-1;
   if > delayed skip Vv0;
   wtw;
   nul;
.branch;   // matr=y1
// ---- Завершальник : ----
   rep 2 data=[ar2++]with vsum,data,0;
   rep 2 [ar4++]=afifo;
//------------------------------
// Сборка "бабочки"
   gr1=4;   
   ar0=[_nmppsTmpBuffer256_G_] with gr0=gr2+1;//ar0=Буфер почленных продуктов,gr0=L+1
   with gr0<<=2; // gr0=4(L+1)
   ar1=ar0+gr0 with gr6=gr2<<2; //gr6=4L, ar1=ar0+4(L+1) вторая половина строки
   ar4=ar6+gr6 with gr4=gr6-1;
   gr0=gr6 with gr4--;
   ar3=ar6 with gr3=gr6+gr1; 
   gr2--; // L-1
ar5=ar6+80;
<Vvs0> // Цикл вдоль столбца:
// -------  Диагональный эл-т строки: -------
   gr5=gr2; // gr5=L-1, параметр цикла по строке
   rep 1 data=[ar0++]with data;       // xa
   rep 1 data=[--ar1]with data+afifo; // yb
   rep 1 [ar6++]=afifo;  // Real=xa+yb
   rep 1 data=[ar0++]with data;       // xb
   rep 1 data=[--ar1]with data-afifo; // ya
   rep 1 [ar6++]=afifo; // Imagine= ya-xb  
// -------цикл вдоль строки: -------
<Vvs1>   ar1=ar1+8;
   rep 1 data=[ar0++]with data;       // xa
   rep 1 data=[--ar1]with data+afifo; // yb
   rep 1 [ar6++]=afifo with afifo;  // Real=xa+yb
   rep 1 [ar4++]=afifo;
   rep 1 data=[ar0++]with data;       // xb
   rep 1 data=[--ar1]with data-afifo; // ya
   rep 1 [ar6++]=afifo with 0-afifo; // Imagine= ya-xb  
   rep 1 [ar4++gr4]=afifo;
   gr5--;
   if > skip Vvs1;
//---------- конец цикла вдоль строки,
   ar0=ar1+gr1;
   ar1=ar0+gr0 with gr0-=gr1;
   ar3=ar3+gr3;ar6=ar3;
   ar4=ar6+gr6;
   gr2--;
   if > skip Vvs0;

//--финиш: diagonal only
   rep 1 data=[ar0++]with data;       // xa
   rep 1 data=[--ar1]with data+afifo;   // yb
   rep 1 [ar3++]=afifo with 0;  // Real=xa+yb
   rep 1 [ar3++]=afifo; // Imagine= ya-xb    
.wait; 

 pop ar6,gr6;
	pop ar5,gr5;
	pop ar4,gr4;
	pop ar3,gr3;
	pop ar2,gr2;
	pop ar1,gr1;
	pop ar0,gr0;
 
 delayed return;
// gr7=[_nmppsTmpBuffer256_G_+2];
 nul;
end ".text_nmplm";
