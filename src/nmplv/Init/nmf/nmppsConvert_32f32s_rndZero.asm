//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM640x Software, 2018                */
//*                                                                         */
//*   Software design:  A.Brodyazhenko                                      */
//*                                                                         */
//*   File:             nmppsConvert_32f32s_rndZero.asm                     */
//*   Contents:         Convert data array from nm32f to nm32s              */
//*						nm32f -> nm32s								        */
//***************************************************************************/

data "data"
.align;
	half_one: word[2] = (float(0.5), float(0.5));
	zeros: word[2] = (float(0.0), float(0.0));
end "data";

global _nmppsConvert_32f32s_rndZero: label;

begin "text"
<_nmppsConvert_32f32s_rndZero>
	ar5 = ar7 - 2;
	push ar2, gr2;
	push ar1, gr1;
	push ar0, gr0;

	ar0 = [--ar5]; // input nm32f* x
	ar1 = [--ar5]; // output nm32s* X
	// gr7 = [--ar5]; // round mode
	// gr2 = [--ar5]; // scale factor
	gr0 = [--ar5]; // size N

	ar2 = half_one;

	fpu 0 rep 32 vreg0 = [ar2];

	ar2 = zeros;

	fpu 0 rep 1 vreg1 = [ar2];

	gr1 = gr0 >> 6;
	if =0 goto Packing_32f32s_less64_Sfs;

<Packing_32f32s_Sfs>
	fpu 0 .float vreg0 = /vreg0/;
	fpu 0 rep 32 vreg2 = [ar0++];
	fpu 0 .float vreg2 - .retrive(vreg1), set mask if <;
	fpu 0 .float vreg0 = mask ? -vreg0 : vreg0;
	fpu 0 .float vreg2 = vreg2 - vreg0;
	gr1--;
	if > delayed goto Packing_32f32s_Sfs;
		fpu 0 .packer = vreg2 with .fixed_32 <= .float;
		fpu rep 32 [ar1++] = .packer;

	gr0 = gr0 << 26;				// computing a remainder
	gr0 = gr0 >> 26;				// computing a remainder
	if =0 delayed goto exit_Conv32f32s_Sfs;

<Packing_32f32s_less64_Sfs>			    // N < 64
	gr0 = gr0 >> 1;
	gr0--;
	vlen = gr0;
	fpu 0 rep vlen vreg2 = [ar0++];
	fpu 0 .float vreg2 - .retrive(vreg1), set mask if <;
	fpu 0 .float vreg0 = mask ? -vreg0 : vreg0;
	fpu 0 .float vreg2 = vreg2 - vreg0;
	fpu 0 .packer = vreg2 with .fixed_32 <= .float;
	fpu rep vlen [ar1++] = .packer;

<exit_Conv32f32s_Sfs>
	pop ar0, gr0;
	pop ar1, gr1;
	pop ar2, gr2;
	return;
end "text";
