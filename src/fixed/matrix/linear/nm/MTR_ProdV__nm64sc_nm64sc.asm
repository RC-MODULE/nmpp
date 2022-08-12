import from macros.mlb;
begin ".text_nmplm"

//-----------------------------------------------------------------
// Умножение матрицы на вектор, оба комплексные, оба nm64s
// как и результат.
// time=W*H*16 тактов

//------------------------------------------------------------------------------------------------
//! \fn void  nmppmMul_mv_64sc ( nm64sc *pSrcMtr,  nm64sc *pSrcVec, nm64sc *pDstVec, int nHeight, int nWidth, void * tmp) 
//! 
//! \perfinclude _nmppmMul_mv___F6nm64scPC6nm64scPC6nm64scPiiPv.html 
//------------------------------------------------------------------------------------------------

global _nmppmMul_mv___F6nm64scPC6nm64scPC6nm64scPiiPv:label;
global _void._.8.8nmppmMul_mv_.1class._nm64sc._.0.9._class._nm64sc._.0.9._class._nm64sc._.0.9._int.9._int.9._void._.0.2 :label;

MTRtmpArray: long; 

macro Wtw7()
  .wait;
  nb1=gr7;
  wtw;
  .branch;
end Wtw7;
macro VsumAfifo(N)
  rep N data = [ar1++gr1] with vsum,data,afifo;
  rep N [ar4++] = afifo;
end   VsumAfifo;

macro Load_Vector_Item(AR)
  rep 1 wfifo = [AR++],ftw;
   nul; // for even full number of instructions
  .wait; nb1=gr7; wtw;
  .branch;
end   Load_Vector_Item;

macro Vsum0(N)
  rep N data = [ar1++gr1] with vsum,data,0;
  rep N [ar4++] = afifo;
end   Vsum0;


Ls0:      label;
Ls2:      label;
Ls3:      label;
Ls4:      label;
Ls5:      label;
smplVsum0:label;  
LsRet0:   label;
LsTbl: word[18]=(// таблица модифицируемых кодов:
  Ls0,  944fe018h, //rep data=[ar1++gr1]with vsum,data,0;
  Ls2,  9c4ff518h, //rep data=[ar1++]with data
  Ls2+1,9c8ff816h, //rep data=[ar2++]with afifo-data
  Ls3,  9c4ffb16h, //rep data=[ar1++]with afifo+data
  Ls3+1,9c8ff816h, //rep data=[ar2++]with afifo-data
  Ls4,  9c4ff518h, //rep data=[ar1++]with data
  Ls4+1,9c8ffb16h, //rep data=[ar2++]with afifo+data
  Ls5,  9c4ffb16h, //rep data=[ar1++]with afifo+data
  Ls5+1,9c8ffb16h  //rep data=[ar2++]with afifo+data
   );
<_nmppmMul_mv___F6nm64scPC6nm64scPC6nm64scPiiPv>
<_void._.8.8nmppmMul_mv_.1class._nm64sc._.0.9._class._nm64sc._.0.9._class._nm64sc._.0.9._int.9._int.9._void._.0.2>
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
    gr4=[--ar5];  // H
    ar3=[--ar5];  // Width
    ar4=[--ar5];  // tmp
    gr3=ar3;      // Width for stride
//=====================================================
global ProdVjobStart:label;
<ProdVjobStart>
    [MTRtmpArray]=ar4;
    nb1=gr7 with gr1=gr3<<2;  // gr1=4*Wstride
    gr3=ar3;                  // Width for loop
    ar5=smplVsum0;
// gr0=((H-1)and 31)+1; gr4=H-gr0; ar2=H; ar3=W;
   ar2=gr4 with gr0=gr4-1;
   gr0<<=27;
   gr0>>=27;gr0++;
   gr5=9 with gr4-=gr0;//if gr4=0 работает только модиф. код,который работает всегда
   if <>0 delayed skip CodeModify;//Там будем в любом случае
   ar4=LsTbl with gr0<<=13; //  << Cnt 13
   ar5=LsRet0; // skip main loop at smplVsum0
//====== modify 9 word of code ===========

<CodeModify>

    push ar1,gr1;
    ar1,gr1=[ar4++] with gr5--;
<modify>
    if > delayed skip modify with gr1+=gr0;
    [ar1]=gr1;
    ar1,gr1=[ar4++] with gr5--;
    pop ar1,gr1;

//=========== code done ===============

    sb=gr7 with gr0=gr7+1; // gr0=1;
    
//==вектор X=iY, матр. A+iB
    ar4=[MTRtmpArray] with gr0++;  // gr0=2;    
.branch;
// Почленное умножение матрицы на эл-ты вектора:
// На i-й эл-т вектора множатся все эл-ты i-го столбца.
// Складывать будем после, на след. итерации (V2).

<V1>
      Load_Vector_Item(ar0);                    //      X
  delayed call ar5 with gr5=gr4>>5;
      ar1=gr2 with gr2+=gr0;gr5--;    //  A*X
      nul;nul;
  delayed call ar5 with gr5=gr4>>5;
      ar1=gr2 with gr2-=gr0;gr5--;    //  B*X
      nul;nul;
      Load_Vector_Item(ar0);                    //      Y

  delayed call ar5 with gr5=gr4>>5;
      ar1=gr2 with gr2+=gr0;gr5--;    //  A*Y
      nul;nul;
  delayed call ar5 with gr5=gr4>>5;
      ar1=gr2 with gr2+=gr0;gr5--;    //  B*Y
      nul;nul;
   gr3--; // цикл по строке
   if > skip V1;
//===========================================
   gr2=ar2 with gr6=gr0<<1; // gr2=H, gr6=4
   gr0=[MTRtmpArray] with gr1=gr2<<1;  // gr1=2H
   gr3=ar3 with gr5=gr1<<1;       // gr5=4*H 
   [MTRtmpArray+1]=ar6 with gr1+=gr5;    // gr1=6*H
   gr2=gr5<<1;  // gr2=8*H
   gr7=gr4>>5;  // параметр цикла <V2>
   if =0 skip _Ls2 with gr5=gr0; // хвост only
//=================================================
// Begin butterfly and addition 
// REAL PART OF THE RESULT:
// цикл делает по 32 эл-та результата за проход
// gr4>>5 раз,где gr4 остаток H без хвоста N=((H-1)&31)+1
<V2>   ar1=gr0 with gr0+=gr2;  // gr0 for next addition
       ar2=ar1+gr1 with gr3--; // ar2=addr of B*Y, gr3=W-1   
       rep 32 data=[ar1++]with data;
       rep 32 data=[ar2++]with afifo-data;
       gr5=ar1;
<R1loop>
       ar1=gr0 with gr0+=gr2;   // gr0+=8*H
       ar2=ar1+gr1 with gr3--;  // original gr3=W
       if > delayed skip R1loop;// repeat W-1 times
       rep 32 data=[ar1++]with afifo+data;
       rep 32 data=[ar2++]with afifo-data;
       rep 32 [ar6++gr6]=afifo;
//повтор для след. группы из 32:
      gr3=ar3 with gr7--;  // W
      if > delayed skip V2;
      gr0=gr5;
<_Ls2> 
// цикл делает N эл-тов результата за проход:N=((H-1)&31)+1
      ar1=gr0 with gr0+=gr2;   // gr0+=8*H
      ar2=ar1+gr1 with gr3--;  // original gr3=W

// модифицированный код: 
<Ls2> rep 4 data=[ar1++]with data;
      rep 4 data=[ar2++]with afifo-data;

<R2loop>
      ar1=gr0 with gr0+=gr2;   // gr0+=8*H
      ar2=ar1+gr1 with gr3--;
      if > delayed skip R2loop;// repeat W-1 times
<Ls3> rep 4 data=[ar1++]with afifo+data;
      rep 4 data=[ar2++]with afifo-data;
      rep 4 [ar6++gr6]=afifo;
//=================================
// IMAGINE PART OF THE RESULT:
   gr0=[MTRtmpArray] with gr1=gr2>>2;  // gr1=2H
   gr3=ar3 with gr0+=gr1; // gr3=W; gr0=addr of A*Y
   ar6=[MTRtmpArray+1] with gr7=gr4>>5;  // параметр цикла <V3> 
   if =0 delayed skip _Ls4; // хвост only
   ar6=ar6+2;
//===========================================
// цикл делает по 32 эл-та результата за проход
// gr4>>5 раз,где gr4 остаток H без хвоста N=((H-1)&31)+1
<V3>   ar1=gr0 with gr0+=gr2;  // gr0 for next addition
       ar2=ar1+gr1 with gr3--; // ar2=addr of B*X, gr3=W-1   
       rep 32 data=[ar1++]with data;
       rep 32 data=[ar2++]with afifo+data;
       gr5=ar1;
<I1loop>
       ar1=gr0 with gr0+=gr2;   // gr0+=8*H
       ar2=ar1+gr1 with gr3--;  // original gr3=W
       if > delayed skip I1loop;// repeat W-1 times
       rep 32 data=[ar1++]with afifo+data;
       rep 32 data=[ar2++]with afifo+data;
       rep 32 [ar6++gr6]=afifo;
//повтор для след. группы из 32:
      gr3=ar3 with gr7--;  // W
      if > delayed skip V3;
      gr0=gr5;
<_Ls4> 
// цикл делает N эл-тов результата за проход:N=((H-1)&31)+1
      ar1=gr0 with gr0+=gr2;   // gr0+=8*H
      ar2=ar1+gr1 with gr3--;  // original gr3=W

// модифицированный код: 
<Ls4> rep 4 data=[ar1++]with data;
      rep 4 data=[ar2++]with afifo+data;
<I2loop>
      ar1=gr0 with gr0+=gr2;
      ar2=ar1+gr1 with gr3--;
      if > delayed skip I2loop;// repeat W-1 times
<Ls5> rep 4 data=[ar1++]with afifo+data;
      rep 4 data=[ar2++]with afifo+data;
      rep 4 [ar6++gr6]=afifo;

<fin> pop ar6,gr6;
	pop ar5,gr5;
	pop ar4,gr4;
	pop ar3,gr3;
	pop ar2,gr2;
	pop ar1,gr1;
	pop ar0,gr0;
 
      return;
// Предполагается, что одна инструкция gr5-- уже сделана 
// последней из отложенных команд call smplVsum0
<smplVsum0>// Цикл по столбу (почленного mul)
<loop0>if > delayed skip loop0 with gr5--;
      Vsum0(32);
<LsRet0> delayed return;
<Ls0> Vsum0(4); // modified command;
      nul;
//======= fin of nmppmMul_mv_ ===================

end ".text_nmplm";