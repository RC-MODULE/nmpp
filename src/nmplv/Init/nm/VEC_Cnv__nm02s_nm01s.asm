global _nmppsConvert_2s1s: label;// объ¤вление глобальной метки
data ".data_cnv_matr_2s1s"
	local matr1: long[64]=(0000000000000001hl,0000000000000002hl,0000000000000004hl,0000000000000008hl,
						   0000000000000010hl,0000000000000020hl,0000000000000040hl,0000000000000080hl,
						   0000000000000100hl,0000000000000200hl,0000000000000400hl,0000000000000800hl,
						   0000000000001000hl,0000000000002000hl,0000000000004000hl,0000000000008000hl,
						   0000000000010000hl,0000000000020000hl,0000000000040000hl,0000000000080000hl,
						   0000000000100000hl,0000000000200000hl,0000000000400000hl,0000000000800000hl,
						   0000000001000000hl,0000000002000000hl,0000000004000000hl,0000000008000000hl,
						   0000000010000000hl,0000000020000000hl,0000000040000000hl,0000000080000000hl,
						   0000000100000000hl,0000000200000000hl,0000000400000000hl,0000000800000000hl,
						   0000001000000000hl,0000002000000000hl,0000004000000000hl,0000008000000000hl,
						   0000010000000000hl,0000020000000000hl,0000040000000000hl,0000080000000000hl,
						   0000100000000000hl,0000200000000000hl,0000400000000000hl,0000800000000000hl,
						   0001000000000000hl,0002000000000000hl,0004000000000000hl,0008000000000000hl,
						   0010000000000000hl,0020000000000000hl,0040000000000000hl,0080000000000000hl,
						   0100000000000000hl,0200000000000000hl,0400000000000000hl,0800000000000000hl,
						   1000000000000000hl,2000000000000000hl,4000000000000000hl,8000000000000000hl);
end ".data_cnv_matr_2s1s";

macro convert_2s1s_tail (N)
	rep 32 wfifo = [ar4++],ftw;	//2
	rep 32 data =[ar0++gr0],wtw	 with vsum, data,0;
	delayed goto end_convert_2s1s;
		rep 32 data =[ar1++gr1]		 with vsum, data,afifo;	
		rep 32 [ar6++gr6]=afifo;
	nul;
	nul;
end convert_2s1s_tail;

begin ".textAAA"
<_nmppsConvert_2s1s>
.branch;
	ar5 = ar7 -2;
	push ar0,gr0;	
	push ar1,gr1;	
	push ar2,gr2;	
	push ar3,gr3;	
	push ar4,gr4;
	push ar5,gr5;
	push ar6,gr6;
	ar0 = [--ar5];			// pSrcVec
	ar6 = [--ar5];			// pDstVec
	gr5 = [--ar5];			// nSize
	nb1 = 0FFFFFFFFh;
	sb = 0AAAAAAAAh;
	gr5 >>=6;
	gr3 = gr7			with gr6=false;
	ar2 = ar6			with gr6++;
	gr2 = ar0			with gr6++;		//gr6=2;
	gr0 = 4;
	Cnv_tail_2s1s: label;
	Tail_2s1s: label;
	end_convert_2s1s: label;
	
	ar1=ar0;
	ar0+=2;
	gr1=gr0;
	ar4 = matr1;
	gr4 = ar4;
	ar4+=64;
	gr7 = gr5 >> 5;
	gr3=gr7;
	if =0 delayed goto Cnv_tail_2s1s;
		rep 32 wfifo = [ar4++],ftw,wtw; //2
		ar4 = gr4;
	
	gr7--;
	
<Loop1>	
	rep 32 wfifo = [ar4++],ftw;	//1
	rep 32 data =[ar0++gr0],wtw	 with vsum, data,0;
	rep 32 data =[ar1++gr1]		 with vsum, data,afifo;	
	rep 32 wfifo = [ar4++],ftw,wtw; //2
	if > delayed goto Loop1 with gr7--;
		ar4 = gr4;	
		rep 32 [ar6++gr6]=afifo;
		
<Cnv_tail_2s1s>	
	gr7=gr3;
	ar5 = Tail_2s1s with gr7 <<=5;
	gr5 = gr5 - gr7;
	gr5 <<= 3;
	ar5+=gr5;
	delayed goto ar5;
		nul;
		nul;
<Tail_2s1s>
	delayed goto end_convert_2s1s;
		nul;
		nul;
	nul;
	nul;
	nul;
	nul;
	convert_2s1s_tail (1);
	convert_2s1s_tail (2);
	convert_2s1s_tail (3);
	convert_2s1s_tail (4);
	convert_2s1s_tail (5);
	convert_2s1s_tail (6);
	convert_2s1s_tail (7);
	convert_2s1s_tail (8);
	convert_2s1s_tail (9);
	convert_2s1s_tail (10);
	convert_2s1s_tail (11);
	convert_2s1s_tail (12);
	convert_2s1s_tail (13);
	convert_2s1s_tail (14);
	convert_2s1s_tail (15);
	convert_2s1s_tail (16);
	convert_2s1s_tail (17);
	convert_2s1s_tail (18);
	convert_2s1s_tail (19);
	convert_2s1s_tail (20);
	convert_2s1s_tail (21);
	convert_2s1s_tail (22);
	convert_2s1s_tail (23);
	convert_2s1s_tail (24);
	convert_2s1s_tail (25);
	convert_2s1s_tail (26);
	convert_2s1s_tail (27);
	convert_2s1s_tail (28);
	convert_2s1s_tail (29);
	convert_2s1s_tail (30);
	convert_2s1s_tail (31);
<end_convert_2s1s>	
		
		
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