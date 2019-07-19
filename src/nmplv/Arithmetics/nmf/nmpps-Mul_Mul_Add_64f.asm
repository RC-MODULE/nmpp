//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM640x Software                      */
//*                                                                         */
//*   Software design:  A.Brodyazhenko                                      */
//*                                                                         */
//*   File:             nmpps-Mul_Mul_Add_64f.asm                           */
//*   Contents:         The function computes f = x1 * y1 + x2 * y2 		*/
//***************************************************************************/

// void nmppsMul_Mul_Add_64f(const nm64f *pSrcVec1, const nm64f *pSrcVec2, nm64f *pSrcVec3, nm64f *pSrcVec4, nm64f *pDstVec, int nSize)
// x1 - pSrcVec1
// y1 - pSrcVec2
// x2 - pSrcVec3
// y2 - pSrcVec4
// f - pDstVec3

global _nmppsMul_Mul_Add_64f: label;
begin ".text_nmplv"
<_nmppsMul_Mul_Add_64f>
	ar5 = ar7 - 2;
	push ar4, gr4;
	push ar3, gr3;
	push ar2, gr2;
	push ar1, gr1;
	push ar0, gr0;

	ar0 = [--ar5]; 			// the address of pSrcVec1
	ar1 = [--ar5]; 			// the address of pSrcVec2
	ar2 = [--ar5]; 			// the address of pSrcVec3
	ar3 = [--ar5]; 			// the address of pSrcVec4
	ar4 = [--ar5]; 			// the address of pDstVec
	gr0 = [--ar5]; 			// nSize

	gr1 = gr0 >> 5; 		// count of the iterations
	if =0 goto less32_MulMulAdd_64f;

<MulMulAdd_64f>
	fpu 0 rep 32 vreg0 = [ar0++];
	fpu 0 rep 32 vreg1 = [ar1++];
	fpu 0 .double vreg2 = vreg0 * vreg1;
	fpu 2 vreg0 = fpu 0 vreg2;

	fpu 1 rep 32 vreg0 = [ar2++];
	fpu 1 rep 32 vreg1 = [ar3++];
	fpu 1 .double vreg2 = vreg0 * vreg1;
	fpu 2 vreg1 = fpu 1 vreg2;
	gr1--;
	if > delayed goto MulMulAdd_64f;
		fpu 2 .double vreg2 = vreg0 + vreg1;
		fpu 2 rep 32 [ar4++] = vreg2;

	gr0 = gr0 << 27;
	gr0 = gr0 >> 27;		// remainder
	if =0 delayed goto exit_MulMulAdd_64f;
<less32_MulMulAdd_64f>
	gr0--;
	vlen = gr0;
	fpu 0 rep vlen vreg0 = [ar0++];
	fpu 0 rep vlen vreg1 = [ar1++];
	fpu 1 rep vlen vreg0 = [ar2++];
	fpu 1 rep vlen vreg1 = [ar3++];

	fpu 0 .double vreg2 = vreg0 * vreg1;
	fpu 1 .double vreg2 = vreg0 * vreg1;

	fpu 2 vreg0 = fpu 0 vreg2;
	fpu 2 vreg1 = fpu 1 vreg2;

	fpu 2 .double vreg2 = vreg0 + vreg1;

	fpu 2 rep vlen [ar4++] = vreg2;

<exit_MulMulAdd_64f>
	pop ar0, gr0;
	pop ar1, gr1;
	pop ar2, gr2;
	pop ar3, gr3;
	pop ar4, gr4;
	return;
end ".text_nmplv";
