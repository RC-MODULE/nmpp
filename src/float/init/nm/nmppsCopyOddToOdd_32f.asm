
//*********************************************************************************************//
//* Prototype: void nmppsCopyOddToOdd_32f(const float* pSrcVec, float* pDstVec, int size);    *//
//* Contents: A Copying of a floating point array from odd src address to odd dst address     *//
//* src - odd address only                                                                    *//
//* dst - odd address only                                                                    *//
//* size - all size execpt zero (1, 2, 3, 4, ... )                                            *//
//*********************************************************************************************//

global _nmppsCopyOddToOdd_32f: label;

extern vec_CopyEvenToEven_32f: label;

begin ".text_nmplv"
<_nmppsCopyOddToOdd_32f>
	ar5 = ar7 - 2;
	push ar6, gr6;
	push ar5, gr5;
	push ar0, gr0;

	ar0 = [--ar5];    	// input nm32f* pSrcVec
	ar6 = [--ar5];    	// output nm32f* pDstVec
	gr5 = [--ar5];    	// nSize

	gr5--;
	if =0 delayed goto exit_nmppsCopyOddToOdd_32f;
	    gr0 = [ar0++];
	    [ar6++] = gr0;
	call vec_CopyEvenToEven_32f;

<exit_nmppsCopyOddToOdd_32f>
	pop ar0, gr0;
	pop ar5, gr5;
	pop ar6, gr6;
	return;
end ".text_nmplv";
