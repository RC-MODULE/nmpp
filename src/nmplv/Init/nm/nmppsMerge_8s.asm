//  i=Merge_8s (int*pdst, int* psrc0, int* psrc1, int size);
//  psrc0 и psrc1 байтовые массивы размером size/2 байтов.
//  pdst массив байтов размером size байтов. Байты из psrc0 пакуются в чётные
//  номера байтов pdst,а байты из psrc1 пакуются в нечётные номера байтов pdst
// Пример: psrc0=8060402h, psrc1=9070503h, pdst=0908070605040302hl.
// Байтами считаем восьмибитные числа. size должно быть кратно ?.
data ".data_nmplv_L"
matr1: word [40]=(
 0,0,0,0,0,0,0,0,
 1,0,10000h,0, 0,1, 0,10000h,
 0,0,0,0,0,0,0,0,
 100h,0, 1000000h,0, 0,100h, 0,1000000h,
 0,0,0,0,0,0,0,0
);
end ".data_nmplv_L";
begin ".text_nmplv"
//  i=Merge_8s (int*psrc, int* pdst0, int* pdst1, int size);
.branch;
extern vec_Mul2D2W8_AddVr: label;
global _nmppsMerge_8s : label;
      <_nmppsMerge_8s>
	nb1=80808080h;  // 8 по 8 на выходе
	sb =02020202h;   // 8 по 8 на входе X
	ar5=ar7-2;
	push ar6,gr6;
	push ar0,gr0;
	push ar1,gr1;
	push ar3,gr3 with gr1=false;
	push ar4,gr4 with gr1++; // gr1=1
	//===========================================
	ar0= [--ar5] with gr6=gr1<<2;// psrc0 gr6=4
	ar1= [--ar5] with gr0=gr1<<1;// psrc1 gr0=2
	ar6= [--ar5] with gr1=gr0;   // pdst  gr1=2

//MS	ar6= [--ar5] with gr6=gr1<<2;// pdst gr6=4
//MS	ar0= [--ar5] with gr0=gr1<<1;// psrc0 gr0=2
//MS	ar1= [--ar5] with gr1=gr0;   // psrc1 gr1=2
	gr5= [--ar5]; // src size (bytes)
	ar3=ar0; 
	gr3=ar1;
	//=========================================== even dbl
	ar4=matr1+8 with gr5>>=3;
//MS	ar4=matr1+8 with gr5>>=4;
	ar5=ar6+2 with gr4=gr5;
	delayed call vec_Mul2D2W8_AddVr with gr3=gr3+gr0;
		ar4=matr1+8;
	//=========================================== odd dbl
	ar0=ar3;ar1=gr3;ar6=ar5 with gr5=gr4;
	delayed call vec_Mul2D2W8_AddVr;
		ar4=matr1;

<fin>// 1799
   pop ar4,gr4;
   pop ar3,gr3;
   pop ar1,gr1;
   pop ar0,gr0;
   pop ar6,gr6;
   return;
.wait;   
end ".text_nmplv";
/*size  time  ticks per int для pdst=4000h, psrc0,1=80000000h,80001000h
*/
