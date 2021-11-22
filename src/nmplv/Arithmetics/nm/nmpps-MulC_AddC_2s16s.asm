// Умножение на 16р константу массива из N2s 2х разрядных чисел
// N2s должно быть кратно 32 т.к. лишнее умножаться не будет.
// int  MulC_2s16s ( short *psrc, short C, short *pdst, int N, int VC);
// 16р константа VC прибавляется ко всем произведениям.Тоже short.
// Функция с указанным выше интерфейсом может вызываться из cpp.
// 100 тактов времени-вот во что обошлась папаше Дорсету кратность 32.
data ".data_nmplv_G"


matr1: long [7]=(0l,
               111hl,
          222_0000hl,
     333_0000_0000hl,
444_0000_0000_0000hl,
0l,0l);

sb_0: long=2a8hl; // 2,2,2,2,56 ширины от младших к старшим
sb_1: long=2aa00hl; // 8,2,2,2,2,48
sb_2: long=2aa0000hl; // 16,2,2,2,2,40
sb_3: long=2aa000000hl; // 24,2,2,2,2,32
sb_4: long=2aa00000000hl; // 32,2,2,2,2,40
sb_5: long=2aa0000000000hl; // 40,2,2,2,2,16
sb_6: long=2aa000000000000hl; // 48,2,2,2,2,8
sb_7: long=0aa00000000000000hl; // 56,2,2,2,2
VC: long;
end ".data_nmplv_G";
begin ".text_nmplv"
//  i=MulC_2s16s ( (short*)&psrc, C, (short*)&pdst, N2s, VC);
extern vec_vsum_data_vr: label;
global _nmppsMulC_AddC_2s16s: label;
<_nmppsMulC_AddC_2s16s>
// аргументы пушнуты в обратном порядке
   push ar6, gr6;
   ar6 = ar7;
   push ar0,gr0;
   push ar1,gr1;
   push ar2,gr2;
   push ar3,gr3 with gr2=false;
   push ar4,gr4 with gr2++;
   push ar5,gr5;
   ar1 = [ar6+-5]with gr2++; // psrc,  gr2=2
   gr1 = [ar6+-6]; // C
   gr0=gr1<<16;// формирование matr1
   ar5=matr1+2 with gr5=gr2;   // gr5=2;
   [ar5++gr5]=gr1;[ar5++gr5]=gr0;
   ar5++;[ar5++gr5]=gr1;[ar5]=gr0; /**/
   gr3=[ar6+-8]; // pdst
   gr5 = [ar6+-9]; // N2s к-во элементов 2s

   gr0 = [ar6+-7]; // vr
   gr7=gr0<<16;
   gr0=gr0 or gr7;
   vrh=gr0;
   vrl=gr0;

//===========================================
   nb1=80008000h; // 4 по 16 в матрице
   ar2=sb_0;
//-----------------------------------------------------0:
     sb=[ar2++];     // поля на входе X: 2,2,2,2,56
     ar3=matr1+2;
     rep 5 wfifo = [ar3++], ftw, wtw;

     ar0=ar1; gr0=2;
     ar6=gr3 with gr3=gr3+gr0;
     gr6=16;
     gr5=gr5>>5;
     call vec_vsum_data_vr;
//-----------------------------------------------------1:
     sb=[ar2++];     // поля на входе X: 8,2,2,2,2,48
     gr2=7;
     ar3=matr1;
<L0> rep 6 wfifo = [ar3++], ftw, wtw;
     ar0=ar1;
     ar6=gr3 with gr3=gr3+gr0;
     call vec_vsum_data_vr;
//-----------------------------------------------------2:
     sb=[ar2++];     // поля на входе X: 8,2,2,2,2,48
     ar3=matr1;
     rep 6 wfifo = [ar3++], ftw, wtw;
     ar0=ar1;
     ar6=gr3 with gr3=gr3+gr0;
     call vec_vsum_data_vr;
//-----------------------------------------------------3:
     sb=[ar2++];     // поля на входе X: 8,2,2,2,2,48
     ar3=matr1;
     rep 6 wfifo = [ar3++], ftw, wtw;
     ar0=ar1;
     ar6=gr3 with gr3=gr3+gr0;
     call vec_vsum_data_vr;
//-----------------------------------------------------4:
     sb=[ar2++];     // поля на входе X: 8,2,2,2,2,48
     ar3=matr1;
     rep 6 wfifo = [ar3++], ftw, wtw;
     ar0=ar1;
     ar6=gr3 with gr3=gr3+gr0;
     call vec_vsum_data_vr;
//-----------------------------------------------------5:
     sb=[ar2++];     // поля на входе X: 8,2,2,2,2,48
     ar3=matr1;
     rep 6 wfifo = [ar3++], ftw, wtw;
     ar0=ar1;
     ar6=gr3 with gr3=gr3+gr0;
     call vec_vsum_data_vr;
//-----------------------------------------------------6:
     sb=[ar2++];     // поля на входе X: 8,2,2,2,2,48
     ar3=matr1;
     rep 6 wfifo = [ar3++], ftw, wtw;
     ar0=ar1;
     ar6=gr3 with gr3=gr3+gr0;
     call vec_vsum_data_vr;
//-----------------------------------------------------7:
     sb=[ar2++];     // поля на входе X: 8,2,2,2,2,48
     ar3=matr1;
     rep 5 wfifo = [ar3++], ftw, wtw;
     ar0=ar1;
     ar6=gr3 with gr3=gr3+gr0;
     call vec_vsum_data_vr;
//time  673  для  N2s= 1024= 400h
//time  970  для  N2s= 2048= 8q0h
//time 1514  для  N2s= 4096=1000h
//time 2603  для  N2s= 8192=2000h
//time 4753  для  N2s=16384=4000h
//so time=336+0.358*N
// а так было в /dev2
//time 9169  для ar2=16 N2s=16384= 4000h
//time 18129 для ar2=32 N2s=32768= 8000h
//time 36048 для ar2=64 N2s=65536=10000h
//so time=7109+0.43*N2s
//==========================================
<fin>
   pop ar5,gr5;
   pop ar4,gr4;
   pop ar3,gr3;
   pop ar2,gr2;
   pop ar1,gr1;
   pop ar0,gr0;
   pop ar6,gr6;
   return;
end ".text_nmplv";

