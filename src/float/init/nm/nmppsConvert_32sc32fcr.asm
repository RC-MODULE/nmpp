//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM640x Software, 2017                */
//*                                                                         */
//*   Software design:  A.Brodyazhenko                                      */
//*                                                                         */
//*   File:             nmppsConvert_32sc32fcr.asm                          */
//*   Contents:         Convert data array from nm32sc to nm32fcr           */
//*						nm32sc(re) -> nm32fcr(re)							*/
//*						nm32sc(im) -> nm32fcr(im)            				*/
//***************************************************************************/

global _nmppsConvert_32sc32fcr: label;

data "data"
	swapping_matr: word[4] = (float(0), float(1), float(1), float(0));
end "data";

begin ".text_nmplv"
<_nmppsConvert_32sc32fcr>
	ar5 = ar7 - 2;
	push ar2, gr2;
	push ar1, gr1;
	push ar0, gr0;
	
	ar0 = [--ar5]; // input
	ar1 = [--ar5]; // output
	gr0 = [--ar5]; // size N

	ar2 = swapping_matr with gr2 = gr0 >> 5;	// count of the iterations
	//gr2;
	if =0 delayed goto Packing_32sc32fcr_less32;
		fpu 0 rep 1 vreg0 = [ar2++];
		fpu 0 rep 1 vreg1 = [ar2++];

<Packing_32sc32fcr>
	fpu rep 32 .packer = [ar0++] with .float <= .fixed_32;
	fpu 0 rep 32 vreg2 = .packer;
	gr2--;
	if > delayed goto Packing_32sc32fcr;
		fpu 0 .matrix vreg3 = vreg2 * .retrive(vreg0, vreg1);
		fpu 0 rep 32 [ar1++] = vreg3;

	gr0 = gr0 << 27;
	gr0 = gr0 >> 27;	// reminder
	if =0 delayed goto exit_Conv32sc32fcr;
<Packing_32sc32fcr_less32>
	gr0--;
	vlen = gr0;
	fpu rep vlen .packer = [ar0++] with .float <= .fixed_32;
	fpu 0 rep vlen vreg2 = .packer;
	fpu 0 .matrix vreg3 = vreg2 * .retrive(vreg0, vreg1);
	fpu 0 rep vlen [ar1++] = vreg3;

<exit_Conv32sc32fcr>
	pop ar0, gr0;
	pop ar1, gr1;
	pop ar2, gr2;
	return;
end ".text_nmplv";