//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM640x Software                      */
//*                                                                         */
//*   Software design:  A.Brodyazhenko                                      */
//*                                                                         */
//*   File:             nmpps-ConjMul_32fcr.asm                             */
//*   Contents:         The function multiplies the elements of two vectors */
//*                     Vector1 * Conjugate(Vector2)                        */
//***************************************************************************/

// void nmppsConjMul_32fcr(const nm32fcr *pSrcVec1, nm32fcr *pSrcVec2, nm32fcr *pDstVec, int nSize);

global _nmppsConjMul_32fcr: label;
begin ".text_nmplv"
<_nmppsConjMul_32fcr>
	ar5 = ar7 - 2;
	push ar3, gr3;
	push ar2, gr2;
	push ar1, gr1;
	push ar0, gr0;
	ar0 = [--ar5]; 			// the addres of pSrcVec1
	ar1 = [--ar5]; 			// the addres of pSrcVec2
	ar2 = [--ar5]; 			// the addres of pDstVec
	gr0 = [--ar5]; 			// nSize

	gr1 = gr0 >> 5; 		// count of the iterations
	if =0 goto less32_ConjMul_32fcr;
	
<ConjMul_32fcr>
	fpu 0 rep 32 vreg0 = [ar0++];
	fpu 0 rep 32 vreg1 = [ar1++];
	fpu 0 .packer = vreg1 with .float .in_low <= .float .in_low;
	fpu 0 rep 32 vreg3 = .packer;
	fpu 0 .float vreg1 = vreg1 - vreg3;
	fpu 0 .float vreg1 = vreg1 - vreg3;
	gr1--;
	if > delayed goto ConjMul_32fcr;
		fpu 0 .complex vreg2 = vreg0 * vreg1;
		fpu 0 rep 32 [ar2++] = vreg2;

	gr0 = gr0 << 27;
	gr0 = gr0 >> 27;		// reminder
	if =0 delayed goto exit_ConjMul_32fcr;
<less32_ConjMul_32fcr>
	gr0--;
	vlen = gr0;
	fpu 0 rep vlen vreg0 = [ar0++];
	fpu 0 rep vlen vreg1 = [ar1++];
	fpu 0 .packer = vreg1 with .float .in_low <= .float .in_low;
	fpu 0 rep vlen vreg3 = .packer;
	fpu 0 .float vreg1 = vreg1 - vreg3;
	fpu 0 .float vreg1 = vreg1 - vreg3;
	fpu 0 .complex vreg2 = vreg0 * vreg1;
	fpu 0 rep vlen [ar2++] = vreg2;

<exit_ConjMul_32fcr>
	pop ar0, gr0;
	pop ar1, gr1;
	pop ar2, gr2;
	pop ar3, gr3;
	return;
end ".text_nmplv";