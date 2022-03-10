global _nmppsConvert_4s2s: label;// объ¤вление глобальной метки
data ".data_matr_4s2s"
	local matr1: long[32]=(0000000100000000hl,0000000400000000hl,
						   0000001000000000hl,0000004000000000hl,
						   0000010000000000hl,0000040000000000hl,
						   0000100000000000hl,0000400000000000hl,
						   0001000000000000hl,0004000000000000hl,
						   0010000000000000hl,0040000000000000hl,
						   0100000000000000hl,0400000000000000hl,
						   1000000000000000hl,4000000000000000hl,
						   0000000000000001hl,0000000000000004hl,
						   0000000000000010hl,0000000000000040hl,
						   0000000000000100hl,0000000000000400hl,
						   0000000000001000hl,0000000000004000hl,
						   0000000000010000hl,0000000000040000hl,
						   0000000000100000hl,0000000000400000hl,
						   0000000001000000hl,0000000004000000hl,
						   0000000010000000hl,0000000040000000hl);
end ".data_matr_4s2s";


macro convert_4s2s_tail (N)
	delayed goto ar2;
		rep N data = [ar1++gr1],wtw 		 with vsum, data, 0;
		rep N data = [ar0++gr0]				 with vsum, data, afifo;
		rep N [ar6++gr6]=afifo;
end convert_4s2s_tail;

begin ".text_nmplv"
<_nmppsConvert_4s2s>
.branch;
	ar5 = ar7 -2;
	push ar0,gr0;	
	push ar1,gr1			with gr0 = false;	
	push ar2,gr2			with gr0++;	
	push ar3,gr3			with gr0++;	
	push ar4,gr4			with gr0++;
	push ar5,gr5			with gr0++;			//gr0=4
	push ar6,gr6;
	ar0 = [--ar5];			// pSrcVec
	ar6 = [--ar5];			// pDstVec
	gr5 = [--ar5];			// nSize
	nb1 = 0AAAAAAAAh		with gr6 = false;
	sb = 22222222h			with gr6++;
	ar1 = ar0;				with gr6++;			//gr6=2
	ar1+=2;
	
	
	Cnv_tail_4s2s:label;
	Tail_4s2s:label;
	end_convert_4s2s:label;
	
	gr1 = gr0; 		 with 	gr5 >>=5;
	ar4 = matr1		 with	gr7 = gr5>>5;
	rep 32 wfifo = [ar4++],ftw,wtw;
	ftw;
	if =0 delayed goto Cnv_tail_4s2s;
		gr4 = matr1 with gr3=gr7;
		gr7--;
<Loop>
	rep 32 data = [ar1++gr1],wtw 		 with vsum, data, 0;
	ar4 = gr4;
	rep 32 wfifo = [ar4++],ftw;
	rep 32 data = [ar0++gr0],wtw		 with vsum, data, afifo;
	if > delayed goto Loop with gr7--;
		rep 32 [ar6++gr6]=afifo,ftw;
		nul;

<Cnv_tail_4s2s>	
	gr7=gr3;
	ar2 = end_convert_4s2s	with gr7 <<=5;
	ar5 = Tail_4s2s 		with gr5 = gr5- gr7;		// tail
	gr5<<=2;
	ar5+=gr5;
	delayed goto ar5;
		nul;
		nul;
<Tail_4s2s>
	delayed goto end_convert_4s2s;
		wtw;
		nul;
	convert_4s2s_tail (1);
	convert_4s2s_tail (2);
	convert_4s2s_tail (3);
	convert_4s2s_tail (4);
	convert_4s2s_tail (5);
	convert_4s2s_tail (6);
	convert_4s2s_tail (7);
	convert_4s2s_tail (8);
	convert_4s2s_tail (9);
	convert_4s2s_tail (10);
	convert_4s2s_tail (11);
	convert_4s2s_tail (12);
	convert_4s2s_tail (13);
	convert_4s2s_tail (14);
	convert_4s2s_tail (15);
	convert_4s2s_tail (16);
	convert_4s2s_tail (17);
	convert_4s2s_tail (18);
	convert_4s2s_tail (19);
	convert_4s2s_tail (20);
	convert_4s2s_tail (21);
	convert_4s2s_tail (22);
	convert_4s2s_tail (23);
	convert_4s2s_tail (24);
	convert_4s2s_tail (25);
	convert_4s2s_tail (26);
	convert_4s2s_tail (27);
	convert_4s2s_tail (28);
	convert_4s2s_tail (29);
	convert_4s2s_tail (30);
	convert_4s2s_tail (31);
<end_convert_4s2s>
	pop ar6,gr6;
	pop ar5,gr5;
	pop ar4,gr4;
	pop ar3,gr3;
	pop ar2,gr2;
	pop ar1,gr1;
	pop ar0,gr0;
.wait;
	return;
end ".text_nmplv";   