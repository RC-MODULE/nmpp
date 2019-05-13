//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM640x Software, 2018                */
//*                                                                         */
//*   Software design:  A.Brodyazhenko                                      */
//*                                                                         */
//*   File:             nmppsConvert_64f32f.asm                             */
//*   Contents:         Convert data array from nm64f to nm32f              */
//*						nm64f -> nm32f								        */
//***************************************************************************/

global _nmppsConvert_64f32f: label;
begin "text"
<_nmppsConvert_64f32f>
	ar5 = ar7 - 2;
	push ar1, gr1;
	push ar0, gr0;

	ar0 = [--ar5]; // input nm64f* x
	ar1 = [--ar5]; // output nm32f* X
	gr0 = [--ar5]; // size N

	gr1 = gr0 >> 5;
	if =0 goto Packing_64f32f_less32;

<Packing_64f32f>
	gr1--;
	if > delayed goto Packing_64f32f;
		fpu rep 32 .packer = [ar0++] with .float <= .double;
		fpu rep 16 [ar1++] = .packer;

	gr0 = gr0 << 27;				// computing a remainder
	gr0 = gr0 >> 27;				// computing a remainder
	if =0 delayed goto exit_Conv64f32f;

<Packing_64f32f_less32>
    gr1 = gr0 >> 1;
    gr0--;
	vlen = gr0;
	fpu rep vlen .packer = [ar0++] with .float <= .double;
    gr1--;
	vlen = gr1;
	fpu rep vlen [ar1++] = .packer;

<exit_Conv64f32f>
	pop ar0, gr0;
	pop ar1, gr1;
	return;
end "text";
