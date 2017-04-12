global _nmppsConvert_1u4u: label;// объ¤вление глобальной метки

data ".data_cnv_matr_1u4u"
	local matr1: long[256]=	(100000000hl,10000000000hl,1000000000000hl,100000000000000hl,
							1hl,100hl,10000hl,1000000hl,
							0hl dup 24,
							1000000000hl,100000000000hl,10000000000000hl,1000000000000000hl,
							10hl,1000hl,100000hl,10000000hl,
							0hl dup 24,
							
							0hl dup 8,
								100000000hl,10000000000hl,1000000000000hl,100000000000000hl,
								1hl,100hl,10000hl,1000000hl, 
							0hl dup 16,							
							0hl dup 8,
								1000000000hl,100000000000hl,10000000000000hl,1000000000000000hl,
								10hl,1000hl,100000hl,10000000hl,
							0hl dup 16,
							
							0hl dup 16,
								100000000hl,10000000000hl,1000000000000hl,100000000000000hl,
								1hl,100hl,10000hl,1000000hl,
							0hl dup 8,							
							0hl dup 16,
								1000000000hl,100000000000hl,10000000000000hl,1000000000000000hl,
								10hl,1000hl,100000hl,10000000hl,
							0hl dup 8,
							
							0hl dup 24,
								100000000hl,10000000000hl,1000000000000hl,100000000000000hl,
								1hl,100hl,10000hl,1000000hl,
							0hl dup 24,
								1000000000hl,100000000000hl,10000000000000hl,1000000000000000hl,
								10hl,1000hl,100000hl,10000000hl);
end ".data_cnv_matr_1u4u";



macro convert_1u4u_tail_step(N)
	own Loop:label;
<Loop>
	ar0=gr1;
	ar6=gr2 with gr4--;
	rep 32 wfifo = [ar4++],ftw;
	rep N data,ram = [ar0++gr0],wtw with vsum,data,0;	
	rep 32 wfifo = [ar4++],ftw;	
	if > delayed goto Loop with gr2 += gr0;			//gr4=gr4+2
		rep N with vsum,shift ram,afifo;
		rep N [ar6++gr6]=afifo,wtw;
		
	delayed goto end_convert_1u4u;
		nul;
		nul;
	nul;
	nul;	
end convert_1u4u_tail_step;

begin ".textAAA"

<_nmppsConvert_1u4u>
.branch;
	ar5 = ar7 -2;
	push ar0,gr0;	
	push ar1,gr1	with gr0=false;	
	push ar2,gr2	with gr0++;	
	push ar3,gr3	with gr0++;		//gr0=2	
	push ar4,gr4;
	push ar5,gr5;
	push ar6,gr6;
	ar0 = [--ar5];			// pSrcVec
	ar6 = [--ar5];			// pDstVec
	gr5 = [--ar5];			// nSize
	nb1 = 0FFFFFFFFh;
	sb = 0FFFFFFFFh;
	gr5 >>=6;
	gr6 = 8;
	gr2 = ar6;
	gr1 = ar0;
	
	Cnv_tail_1u4u: label;
	Tail_1u4u: label;
	end_convert_1u4u: label;
	
	ar4 = matr1;
	gr7 = gr5 >> 5;
	gr3 = gr7;
	if =0 delayed goto Cnv_tail_1u4u;
		gr4 = ar4;
		rep 32 wfifo = [ar4++],ftw,wtw; 							//1
	gr7--;
	
<Convert_1u4u_first_step>
	rep 32 wfifo = [ar4++],ftw;										//2
	rep 32 data,ram = [ar0++gr0],wtw with vsum,data,0;
	ar4 = gr4;
	if > delayed goto Convert_1u4u_first_step with gr7--;
		rep 32 wfifo = [ar4++],ftw with vsum,shift ram,afifo;		//1
		rep 32 [ar6++gr6]=afifo,wtw;
		
	ar0 = gr1;
	ar6 = gr2;
	ar6+=2;
	gr7=gr3;
	ar4 = matr1;
	ar4+=128;
	gr4 = ar4		with 	gr7--;
	rep 32 wfifo = [ar4++],ftw,wtw;
	
<Convert_1u4u_second_step>	
	rep 32 wfifo = [ar4++],ftw;
	rep 32 data,ram = [ar0++gr0],wtw with vsum,data,0;
	ar4 = gr4;
	if > delayed goto Convert_1u4u_second_step with gr7--;
		rep 32 wfifo = [ar4++],ftw with vsum,shift ram,afifo;
		rep 32 [ar6++gr6]=afifo,wtw;
		
	ar0 = gr1;
	ar6 = gr2;
	ar6+=4;
	gr7=gr3;
	ar4 = matr1;
	ar4+=256;
	gr4 = ar4		with 	gr7--;
	rep 32 wfifo = [ar4++],ftw,wtw;
	
<Convert_1u4u_third_step>	
	rep 32 wfifo = [ar4++],ftw;
	rep 32 data,ram = [ar0++gr0],wtw with vsum,data,0;
	ar4 = gr4;
	if > delayed goto Convert_1u4u_third_step with gr7--;
		rep 32 wfifo = [ar4++],ftw with vsum,shift ram,afifo;
		rep 32 [ar6++gr6]=afifo,wtw;
		
	ar0 = gr1;
	ar6 = gr2;
	ar6+=6;
	gr7=gr3;
	ar4 = matr1;
	ar4+=384;
	gr4 = ar4		with 	gr7--;
	rep 32 wfifo = [ar4++],ftw,wtw;
	
<Convert_1u4u_fourth_step>
	rep 32 wfifo = [ar4++],ftw;
	rep 32 data,ram = [ar0++gr0],wtw with vsum,data,0;
	ar4 = gr4;
	if > delayed goto Convert_1u4u_fourth_step with gr7--;
		rep 32 wfifo = [ar4++],ftw with vsum,shift ram,afifo;
		rep 32 [ar6++gr6]=afifo,wtw;
	
	ar6-=6;
<Cnv_tail_1u4u>		
	gr7 = gr3;
	ar5 = Tail_1u4u with gr7 <<=5;
	gr5 = gr5 - gr7;
	
	gr5 =gr5 << 4;
	ar5+=gr5;
	
	gr4 = 4;
	delayed goto ar5;
		gr2=ar6;
		gr1=ar0;
<Tail_1u4u>
	delayed goto end_convert_1u4u;
		nul;
		nul;
	delayed goto end_convert_1u4u;
		nul;
		nul;
	delayed goto end_convert_1u4u;
		nul;
		nul;
	delayed goto end_convert_1u4u;
		nul;
		nul;
	convert_1u4u_tail_step(1);
	convert_1u4u_tail_step(2);
	convert_1u4u_tail_step(3);
	convert_1u4u_tail_step(4);
	convert_1u4u_tail_step(5);
	convert_1u4u_tail_step(6);
	convert_1u4u_tail_step(7);
	convert_1u4u_tail_step(8);
	convert_1u4u_tail_step(9);
	convert_1u4u_tail_step(10);
	convert_1u4u_tail_step(11);
	convert_1u4u_tail_step(12);
	convert_1u4u_tail_step(13);
	convert_1u4u_tail_step(14);
	convert_1u4u_tail_step(15);
	convert_1u4u_tail_step(16);
	convert_1u4u_tail_step(17);
	convert_1u4u_tail_step(18);
	convert_1u4u_tail_step(19);
	convert_1u4u_tail_step(20);
	convert_1u4u_tail_step(21);
	convert_1u4u_tail_step(22);
	convert_1u4u_tail_step(23);
	convert_1u4u_tail_step(24);
	convert_1u4u_tail_step(25);
	convert_1u4u_tail_step(26);
	convert_1u4u_tail_step(27);
	convert_1u4u_tail_step(28);
	convert_1u4u_tail_step(29);
	convert_1u4u_tail_step(30);
	convert_1u4u_tail_step(31);

<end_convert_1u4u>
	
	pop ar6,gr6;
	pop ar5,gr5;
	pop ar4,gr4;
	pop ar3,gr3;
	pop ar2,gr2;
	pop ar1,gr1;
	pop ar0,gr0;
.wait;
	return;
end ".textAAA";   