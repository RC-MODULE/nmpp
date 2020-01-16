
//*******************************************************************************************//
//* A.Brodyazhenko, 2019                                                                    *//
//* Prototype: void nmppsCopyEvenToEven_32f(const float* pSrcVec, float* pDstVec, int size);*//
//* Contents: A Copying of a floating point array from even src address to even dst address *//
//* src - even address only                                                                 *//
//* dst - even address only                                                                 *//
//* size - all sizes (0, 1, 2, 3, 4, ... )                                                  *//
//*******************************************************************************************//

global _nmppsCopyEvenToEven_32f: label;

extern vec_CopyEvenToEven_32f: label;

begin ".text_nmplv"
<_nmppsCopyEvenToEven_32f>
	ar5 = ar7 - 2;
	push ar6, gr6;
	push ar5, gr5;
	push ar0, gr0;

	ar0 = [--ar5];    	// input float* pSrcVec
	ar6 = [--ar5];    	// output float* pDstVec
	gr5 = [--ar5];    	// nSize

	call vec_CopyEvenToEven_32f;

	pop ar0, gr0;
	pop ar5, gr5;
	pop ar6, gr6;
	return;
end ".text_nmplv";
