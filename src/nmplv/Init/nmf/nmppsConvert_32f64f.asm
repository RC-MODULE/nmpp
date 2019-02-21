//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM640x Software, 2018                */
//*                                                                         */
//*   Software design:  A.Brodyazhenko                                      */
//*                                                                         */
//*   File:             nmppsConvert_32f64f.asm                             */
//*   Contents:         Convert data array from nm32f to nm64f              */
//*						nm32f -> nm64f								        */
//***************************************************************************/

global _nmppsConvert_32f64f: label;
begin "text"
<_nmppsConvert_32f64f>
	ar5 = ar7 - 2;
	push ar2, gr2;
	push ar1, gr1;
	push ar0, gr0;

	ar0 = [--ar5]; // input nm32f* x
	ar1 = [--ar5]; // output nm64f* X
	gr0 = [--ar5]; // size N

	ar2 = ar1 + 2;

	gr1 = gr0 >> 5;
	if =0 goto Packing_32f64f_less64;

<Packing_32f64f>
	gr1--;
	if > delayed goto Packing_32f64f;
		fpu rep 32 .packer = [ar0++] with .double <= .float;
		fpu rep 32 (vreg0, vreg1) = .packer;
		fpu rep 32 [ar1++] = vreg0;
		fpu rep 32 [ar2++] = vreg1;

	gr0 = gr0 << 27;				// computing a remainder
	gr0 = gr0 >> 27;				// computing a remainder
	if =0 delayed goto exit_Conv32f64f;

<Packing_32f64f_less64>			    // N < 64
	gr0--;
	vlen = gr0;
	fpu rep vlen .packer = [ar0++] with .double <= .float;
	fpu rep 32 (vreg0, vreg1) = .packer;
	fpu rep vlen [ar1++] = vreg0;
	fpu rep vlen [ar2++] = vreg1;

<exit_Conv32f64f>
	pop ar0, gr0;
	pop ar1, gr1;
	pop ar2, gr2;
	return;
end "text";
