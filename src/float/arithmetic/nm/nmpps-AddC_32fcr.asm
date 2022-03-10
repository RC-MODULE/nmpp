//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM640x Software                      */
//*                                                                         */
//*   Software design:  A.Brodyazhenko                                      */
//*                                                                         */
//*   File:             nmpps-AddC_32fcr.asm                                */
//*   Contents:         The function adds the float const to 		        */
//*						the every element real part of input complex vector */
//***************************************************************************/

// void nmppsAddC_32fcr(const nm32fcr *pSrcVec, nm32fcr *pDstVec, float C, int nSize);

global _nmppsAddC_32fcr: label;
begin ".text_nmplv"
<_nmppsAddC_32fcr>
	ar5 = ar7 - 2;
	push ar3, gr3;
	push ar2, gr2;
	push ar1, gr1;
	push ar0, gr0;

	ar0 = [--ar5]; 					// input x
	ar1 = [--ar5]; 					// input x
	fpu 0 rep 1 vreg1 = [--ar5];	// const
	gr0 = [ar5];					// size N

	gr1 = gr0 >> 5; 				// count of the iterations

	if =0 delayed goto Add_C_32fcr_less32;
		fpu 0 .packer = vreg1 with .float .in_high <= .float .in_high;
		fpu 0 rep 1 vreg1 = .packer;
<Loop_Add_C32fcr>
	fpu 0 rep 32 vreg0 = [ar0++];
	gr1--;
	if > delayed goto Loop_Add_C32fcr;
		fpu 0 .float vreg2 = vreg0 + .retrive(vreg1);
		fpu 0 rep 32 [ar1++] = vreg2;
	gr0 = gr0 << 27;
	gr0 = gr0 >> 27;				// reminder
	if =0 delayed goto exit_Add_C_32fcr;
<Add_C_32fcr_less32>
	gr0--;
	vlen = gr0;
	fpu 0 rep vlen vreg0 = [ar0++];
	fpu 0 .float vreg2 = vreg0 + .retrive(vreg1);
	fpu 0 rep vlen [ar1++] = vreg2;

<exit_Add_C_32fcr>
	pop ar0, gr0;
	pop ar1, gr1;
	pop ar2, gr2;
	pop ar3, gr3;
	return;
end ".text_nmplv";