//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM640x Software, 2018                */
//*                                                                         */
//*   Software design:  A.Brodyazhenko                                      */
//*                                                                         */
//*   File:             nmppsConvert_32f32s.asm                             */
//*   Contents:         Convert data array from nm32f to nm32s              */
//*						nm32f -> nm32s								        */
//***************************************************************************/

global _nmppsConvert_32f32s: label;
begin "text"
<_nmppsConvert_32f32s>
	ar5 = ar7 - 2;
	push ar1, gr1;
	push ar0, gr0;

	ar0 = [--ar5]; // input nm32f* x
	ar1 = [--ar5]; // output nm32s* X
	gr0 = [--ar5]; // size N

	gr1 = gr0 >> 6;
	if =0 goto Packing_32f32s_less64;

<Packing_32f32s>
	gr1--;
	if > delayed goto Packing_32f32s;
		fpu rep 32 .packer = [ar0++] with .fixed_32 <= .float;
		fpu rep 32 [ar1++] = .packer;

	gr0 = gr0 << 26;				// computing a remainder
	gr0 = gr0 >> 26;				// computing a remainder
	if =0 delayed goto exit_Conv32f32s;

<Packing_32f32s_less64>			    // N < 64
	gr0 = gr0 >> 1;
	gr0--;
	vlen = gr0;
	fpu rep vlen .packer = [ar0++] with .fixed_32 <= .float;
	fpu rep vlen [ar1++] = .packer;

<exit_Conv32f32s>
	pop ar0, gr0;
	pop ar1, gr1;
	return;
end "text";
