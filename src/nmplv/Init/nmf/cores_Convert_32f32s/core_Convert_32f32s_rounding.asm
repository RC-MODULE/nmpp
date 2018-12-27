//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM640x Software, 2018                */
//*                                                                         */
//*   Software design:  A.Brodyazhenko                                      */
//*                                                                         */
//*   File:             core_nmppsConvert_32f32s_rounding.asm               */
//*   Contents:         Convert a data array from nm32f to nm32s            */
//*						round(nm32f) -> nm32s								*/
//*	  This function has a register interface.								*/
//*	  Prototype: void core_nmppsConvert_32f32s_rounding(ar0, ar1, gr0);	    */
//*   ar0 - address of input  array nm32f	                                */
//*   ar1 - address of output array nm32s	                                */
//*   gr0 - input and output arrays size	                                */
//***************************************************************************/

global core_nmppsConvert_32f32s_rounding: label;
begin "text"
<core_nmppsConvert_32f32s_rounding>
	gr1 = gr0 >> 6;
	if =0 goto less64_Packing_32f32s_rounding;

<Packing_32f32s_rounding>
	gr1--;
	if > delayed goto Packing_32f32s_rounding;
		fpu rep 32 .packer = [ar0++] with .fixed_32 <= .float;
		fpu rep 32 [ar1++] = .packer;

	gr0 = gr0 << 26;				              // computing a remainder
	gr0 = gr0 >> 26;				              // computing a remainder
	if =0 delayed goto exit_Conv32f32s_rounding;

<less64_Packing_32f32s_rounding>			              // N < 64
	gr0 = gr0 >> 1;
	gr0--;
	vlen = gr0;
	fpu rep vlen .packer = [ar0++] with .fixed_32 <= .float;
	fpu rep vlen [ar1++] = .packer;

<exit_Conv32f32s_rounding>
	return;
end "text";
