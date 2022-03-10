//*******************************************************************************************//
//* Prototype: void nmppsCopyOddToEven_32f(const float* pSrcVec, float* pDstVec, int size); *//
//* Contents: A Copying of a floating point array from odd src address to even dst address  *//
//* src - odd address only                                                                  *//
//* dst - even address only                                                                 *//
//* size - all sizes except zero (1, 2, 3, 4, ...)                                          *//
//*******************************************************************************************//

global _nmppsCopyOddToEven_32f: label;

extern vec_CopyOddToEven_32f: label;

begin ".text_nmplv"
<_nmppsCopyOddToEven_32f>
	ar5 = ar7 - 2;
	push ar6, gr6;
	push ar5, gr5;
	push ar0, gr0;

	ar0 = [--ar5];    	// input nm32f* pSrcVec
	ar6 = [--ar5];    	// output nm32f* pDstVec
	gr5 = [--ar5];    	// nSize

	call vec_CopyOddToEven_32f;

	pop ar0, gr0;
	pop ar5, gr5;
	pop ar6, gr6;
	return;
end ".text_nmplv";
