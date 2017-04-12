global _nmppsConvert_2u4u: label;
extern vec_vsum_data_0:label;
data ".MyData"
	local matr1: long[64]=(0000000000000001hl,
						   0000000000000010hl,
						   0000000000000100hl,
						   0000000000001000hl,
						   0000000000010000hl,
						   0000000000100000hl,
						   0000000001000000hl,
						   0000000010000000hl,
						   0000000100000000hl,
						   0000001000000000hl,
						   0000010000000000hl,
						   0000100000000000hl,
						   0001000000000000hl,
						   0010000000000000hl,
						   0100000000000000hl,
						   1000000000000000hl,
						   0hl dup 32,
						   0000000000000001hl,
						   0000000000000010hl,
						   0000000000000100hl,
						   0000000000001000hl,
						   0000000000010000hl,
						   0000000000100000hl,
						   0000000001000000hl,
						   0000000010000000hl,
						   0000000100000000hl,
						   0000001000000000hl,
						   0000010000000000hl,
						   0000100000000000hl,
						   0001000000000000hl,
						   0010000000000000hl,
						   0100000000000000hl,
						   1000000000000000hl);
end ".MyData";

begin ".textAAA"
<_nmppsConvert_2u4u>
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
	nb1 = 0AAAAAAAAh;
	sb = 0AAAAAAAAh;
	gr5 >>=5;
	gr0 = 2;
	gr6 = 4;
	gr3 = gr5;
	ar4 = matr1;
	rep 32 wfifo = [ar4++],ftw;
	gr2 = ar0;
	gr4 = ar6;
	delayed call vec_vsum_data_0;
		wtw;
		nul;
	rep 32 wfifo = [ar4++],ftw;	
	gr5 = gr3;
	ar0 = gr2;
	ar6 = gr4;
	ar6+=2;
	delayed call vec_vsum_data_0;
		wtw;
		nul;
		
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