//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM640x Software                      */
//*                                                                         */
//*   Software design:  A.Brodyazhenko                                      */
//*                                                                         */
//*   File:             nmpps-Mul_ConjMul_Add_32fcr.asm                     */
//*   Contents:         The function computes f = x1 * y1 + x2 * Conj(y2) 	*/
//***************************************************************************/

// void nmppsMul_ConjMul_Add_32fcr(const nm32fcr *pSrcVec1, const nm32fcr *pSrcVec2, nm32fcr *pSrcVec3, nm32fcr *pSrcVec4, nm32fcr *pDstVec, int nSize)
// x1 - pSrcVec1
// y1 - pSrcVec2
// x2 - pSrcVec3
// y2 - pSrcVec4
// f  - pDstVec

data ".data_nmplv"
	ForConj: word[2] = (float(-1), float(1));
end ".data_nmplv";

global _nmppsMul_ConjMul_Add_32fcr: label;
begin ".text_nmplv"
<_nmppsMul_ConjMul_Add_32fcr>
	ar5 = ar7 - 2;
	push ar4, gr4;
	push ar3, gr3;
	push ar2, gr2;
	push ar1, gr1;
	push ar0, gr0;

	ar0 = [--ar5]; 					// the address of pSrcVec1
	ar1 = [--ar5]; 					// the address of pSrcVec2
	ar2 = [--ar5]; 					// the address of pSrcVec3
	ar3 = [--ar5]; 					// the address of pSrcVec4
	ar4 = [--ar5]; 					// the address of pDstVec
	gr0 = [--ar5]; 					// nSize

	gr1 = gr0 >> 5; 				// count of the iterations
	if =0 delayed goto less32_MulConjMulAdd_32fcr;
		ar5 = ForConj;
	
	fpu 1 rep 1 vreg1 = [ar5]; 						// -1, 1

<MulConjMulAdd_32fcr>
	fpu 0 rep 32 vreg0 = [ar0++];					// read pSrcVec1
	fpu 0 rep 32 vreg1 = [ar1++];					// read pSrcVec2
	fpu 0 .complex vreg2 = vreg0 * vreg1;			// pSrcVec1 * pSrcVec2
	fpu 3 vreg0 = fpu 0 vreg2;

	fpu 1 rep 32 vreg0 = [ar3++];					// read pSrcVec4
	
	fpu 1 .float vreg0 = vreg0 * .retrive(vreg1);	// Conj(pSrcVec4)
	fpu 2 vreg0 = fpu 1 vreg0;

	fpu 2 rep 32 vreg1 = [ar2++];					// read pSrcVec3
	fpu 2 .complex vreg2 = vreg0 * vreg1;			// pSrcVec3 * Conj(pSrcVec4)
	fpu 3 vreg1 = fpu 2 vreg2;

	gr1--;
	if > delayed goto MulConjMulAdd_32fcr;
		fpu 3 .float vreg2 = vreg0 + vreg1;			// pSrcVec1 * pSrcVec2 + pSrcVec3 * Conj(pSrcVec4)
		fpu 3 rep 32 [ar4++] = vreg2;

	gr0 = gr0 << 27;
	gr0 = gr0 >> 27;								// remainder
	if =0 delayed goto exit_MulConjMulAdd_32fcr;
<less32_MulConjMulAdd_32fcr>
	gr0--;
	vlen = gr0;

	fpu 0 rep vlen vreg0 = [ar0++];
	fpu 0 rep vlen vreg1 = [ar1++];

	fpu 0 .complex vreg2 = vreg0 * vreg1;
	fpu 3 vreg0 = fpu 0 vreg2;

	fpu 1 rep vlen vreg0 = [ar2++];
	fpu 1 rep 1 vreg1 = [ar5]; 						// -1, 1
	fpu 1 .float vreg0 = vreg0 * .retrive(vreg1);
	fpu 2 vreg0 = fpu 1 vreg0;
	
	fpu 2 rep vlen vreg1 = [ar3++];
	fpu 2 .complex vreg2 = vreg0 * vreg1;
	fpu 3 vreg1 = fpu 2 vreg2;
	
	fpu 3 .float vreg2 = vreg0 + vreg1;
	fpu 3 rep vlen [ar4++] = vreg2;

<exit_MulConjMulAdd_32fcr>
	pop ar0, gr0;
	pop ar1, gr1;
	pop ar2, gr2;
	pop ar3, gr3;
	pop ar4, gr4;
	return;
end ".text_nmplv";