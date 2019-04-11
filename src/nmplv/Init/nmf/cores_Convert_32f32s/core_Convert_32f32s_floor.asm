//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM640x Software, 2018                */
//*                                                                         */
//*   Software design:  A.Brodyazhenko                                      */
//*                                                                         */
//*   File:             core_nmppsConvert_32f32s_floor.asm                  */
//*   Contents:         Convert a data array from nm32f to nm32s            */
//*						floor(nm32f) -> nm32s							    */
//*	  This function has a register interface.								*/
//*	  Prototype: void core_nmppsConvert_32f32s_floor(ar0, ar1, gr0);	    */
//*   ar0 - address of input  array nm32f	                                */
//*   ar1 - address of output array nm32s	                                */
//*   gr0 - input and output arrays size	                                */
//***************************************************************************/

data "data"
.align;
	half_one: word[2] = (float(0.5), float(0.5));
end "data";

nobits "data1"
	scale_factor: word[2];
end "data1";

global core_nmppsConvert_32f32s_floor: label;

begin "text"
<core_nmppsConvert_32f32s_floor>
	ar2 = ar2 + 127;
	gr2 = ar2;
	gr2 <<= 23;
	ar2 = scale_factor;
	[ar2++] = gr2;
	[ar2++] = gr2;
	ar2 = ar2 - 2;
	fpu 0 rep 1 vreg1 = [ar2];

	ar2 = half_one;

	fpu 0 rep 32 vreg0 = [ar2];

	gr1 = gr0 >> 6;
	if =0 goto Packing_32f32s_less64_floor;

<Packing_32f32s_floor>
	fpu 0 rep 32 vreg2 = [ar0++];
	fpu 0 .float vreg2 = vreg2 * .retrive(vreg1) - vreg0;
	gr1--;
	if > delayed goto Packing_32f32s_floor;
		fpu 0 .packer = vreg2 with .fixed_32 <= .float;
		fpu rep 32 [ar1++] = .packer;

	gr0 = gr0 << 26;				// computing a remainder
	gr0 = gr0 >> 26;				// computing a remainder
	if =0 delayed goto exit_Conv32f32s_floor;

<Packing_32f32s_less64_floor>			    // N < 64
	gr0 = gr0 >> 1;
	gr0--;
	vlen = gr0;
	fpu 0 rep vlen vreg0 = [ar2];
	fpu 0 rep vlen vreg2 = [ar0++];
	fpu 0 .float vreg2 = vreg2 * .retrive(vreg1) - vreg0;
	fpu 0 .packer = vreg2 with .fixed_32 <= .float;
	fpu rep vlen [ar1++] = .packer;

<exit_Conv32f32s_floor>
	return;
end "text";
