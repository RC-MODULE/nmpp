//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM640x Software, 2018                */
//*                                                                         */
//*   Software design:  A.Brodyazhenko                                      */
//*                                                                         */
//*   File:             nmppsConvert_32s32f.asm                             */
//*   Contents:         Convert data array from nm32s to nm32f              */
//*						nm32s -> nm32f								        */
//***************************************************************************/

global _nmppsConvert_32s32f: label;
begin "text"
<_nmppsConvert_32s32f>
	ar5 = ar7 - 2;
	push ar1, gr1;
	push ar0, gr0;

	ar0 = [--ar5]; // input nm32s* x
	ar1 = [--ar5]; // output nm32f* X
	gr0 = [--ar5]; // size N

	gr1 = gr0 >> 6;
	if =0 goto Packing_32s32f_less64;

<Packing_32s32f>
	gr1--;
	if > delayed goto Packing_32s32f;
		fpu rep 32 .packer = [ar0++] with .float <= .fixed_32;
		fpu rep 32 [ar1++] = .packer;

	gr0 = gr0 << 26;				// computing a remainder
	gr0 = gr0 >> 26;				// computing a remainder
	if =0 delayed goto exit_Conv32s32f;

<Packing_32s32f_less64>			    // N < 64
	gr0 = gr0 >> 1;
	gr0--;
	vlen = gr0;
	fpu rep vlen .packer = [ar0++] with .float <= .fixed_32;
	fpu rep vlen [ar1++] = .packer;

<exit_Conv32s32f>
	pop ar0, gr0;
	pop ar1, gr1;
	return;
end "text";
