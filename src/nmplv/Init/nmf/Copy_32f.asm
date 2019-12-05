
global _Copy_32f: label;

extern core_Copy_32f: label;

begin ".text_nmplv"
<_Copy_32f>
	ar5 = ar7 - 2;
	push ar6, gr6;
	push ar5, gr5;
	push ar0, gr0;

	ar0 = [--ar5];    	// input nm32f* pSrcVec
	ar6 = [--ar5];    	// output nm32f* pDstVec
	gr5 = [--ar5];    	// nSize

	call core_Copy_32f;

	pop ar0, gr0;
	pop ar5, gr5;
	pop ar6, gr6;
	return;
end ".text_nmplv";
