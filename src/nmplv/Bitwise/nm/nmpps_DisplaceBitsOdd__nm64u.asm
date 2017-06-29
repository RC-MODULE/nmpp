

data ".data_shift"
	PushWoperOdd:long[4]=(0hl,8000000000000000hl,0hl,1hl);
	TmpOdd:long;
end ".data_shift";

macro ShiftBitstreamOdd_tail(N)
	if > delayed goto ar3;
		rep N data = [ar0++],ftw,wtw	with vsum, data,0;
		rep N data = [ar1++]	with vsum, shift data, afifo;
		rep N [ar6++] = afifo;
end ShiftBitstreamOdd_tail;


import from rtmacro.mlb;
import from macros.mlb;

global _nmppsFwdShiftBitstream_Odd:label;
begin ".text_nmplv"
<_nmppsFwdShiftBitstream_Odd>
.branch;
/*	ar5 = sp - 2;	
	push ar0,gr0;
	push ar1,gr1;
	push ar2,gr2;
	push ar3,gr3;
	push ar4,gr4;
	push ar5,gr5;
	push ar6,gr6;
	ar0 = [--ar5];	// pSrcVec
	ar6 = [--ar5];	// pDstVec
	ar2 = [--ar5];	// pnBits
	gr6 = [--ar5];	// nBits
	ar1 = [--ar5];	// nSize
	*/
	ar3,gr3=[ar2];
	[TmpOdd]=ar3,gr3;
	
	ar4 = PushWoperOdd;
	
	
	//	nb1	4000000000000001hl	gr0,gr1
	//	sb	8000000000000000hl  gr3,gr2
	//	wo	0000000000000002hl  gr2,gr1

	gr0 = 40000000h;
	gr1 = 2;
	gr2 = 0;
	gr3 = 80000000h;
	
	gr6--;

	ar4 = PushWoperOdd;
	
	LSHIFT64(gr4,gr5,gr1,gr2,gr6);	//gr1=2
	[ar4++] = gr4;
	[ar4++] = gr5;
	ar4 -= 2;
	RSHIFT64(gr4,gr5,gr2,gr3,gr6);
	sbl = gr4;
	sbh = gr5		with gr1--;		//gr1=1;
	LSHIFT64(gr4,gr5,gr1,gr2,gr6);
	gr5 = gr5 or gr0;
	nb1l=gr4;
	nb1h=gr5;
	
	
	
//	nb1h = 40000000h;
//	nb1l = 1;
//	sbl  = 0;
//	sbh  = 80000000h;
	
	
	gr4=ar4;
	gr5=ar1;
	gr7 = gr5>>5;
	
	push ar6,gr6;
	if =0 delayed goto Tail;
		ar1=ar0-2	with	gr7--;
<Next32>
	ar4 = gr4;
	rep 4 wfifo = [ar4++],ftw,wtw;
	rep 32 data = [ar0++],ftw,wtw	with vsum, data,0;
	if > delayed goto Next32 with gr7--;
		rep 32 data = [ar1++]	with vsum, shift data, afifo;
		rep 32 [ar6++] = afifo;
	
	Tail_start: label;
	Tail_end: label;
<Tail>
	gr7 = gr5>>5;
	gr7<<=5;
	ar3 = Tail_start	with  gr3 = gr5-gr7;
	ar4 = gr4	with gr3<<=2;
	ar3+=gr3;
	delayed goto ar3; 
		rep 4 wfifo = [ar4++],ftw,wtw;
		ar3 = Tail_end;
<Tail_start>
	delayed goto Tail_end;
		ftw;
		wtw;
	ShiftBitstreamOdd_tail(1);
	ShiftBitstreamOdd_tail(2);
	ShiftBitstreamOdd_tail(3);
	ShiftBitstreamOdd_tail(4);
	ShiftBitstreamOdd_tail(5);
	ShiftBitstreamOdd_tail(6);
	ShiftBitstreamOdd_tail(7);
	ShiftBitstreamOdd_tail(8);
	ShiftBitstreamOdd_tail(9);
	ShiftBitstreamOdd_tail(10);
	ShiftBitstreamOdd_tail(11);
	ShiftBitstreamOdd_tail(12);
	ShiftBitstreamOdd_tail(13);
	ShiftBitstreamOdd_tail(14);
	ShiftBitstreamOdd_tail(15);
	ShiftBitstreamOdd_tail(16);
	ShiftBitstreamOdd_tail(17);
	ShiftBitstreamOdd_tail(18);
	ShiftBitstreamOdd_tail(19);
	ShiftBitstreamOdd_tail(20);
	ShiftBitstreamOdd_tail(21);
	ShiftBitstreamOdd_tail(22);
	ShiftBitstreamOdd_tail(23);
	ShiftBitstreamOdd_tail(24);
	ShiftBitstreamOdd_tail(25);
	ShiftBitstreamOdd_tail(26);
	ShiftBitstreamOdd_tail(27);
	ShiftBitstreamOdd_tail(28);
	ShiftBitstreamOdd_tail(29);
	ShiftBitstreamOdd_tail(30);
	ShiftBitstreamOdd_tail(31);
<Tail_end>
	ar3 = TmpOdd;
	pop ar6,gr6;
	rep 1 data = [ar3] with vsum,data,0;
	rep 1 data = [ar6] with afifo+data;
	rep 1 [ar6] = afifo;
	
	
	pop ar6,gr6;
	pop ar5,gr5;
	pop ar4,gr4;
	pop ar3,gr3;
	pop ar2,gr2;
	pop ar1,gr1;
	pop ar0,gr0;
	return;
.wait;
end ".text_nmplv"; 
