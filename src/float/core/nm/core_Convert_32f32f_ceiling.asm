//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM640x Software, 2021                */
//*                                                                         */
//*   Software design:  S.Mushkaev                                          */
//*                                                                         */
//*   File:             core_nmppsConvert_32f32f_ceiling.asm                */
//*   Contents:         Convert a data array from nm32f to nm32s            */
//*						ceil(nm32f) -> nm32f							    */
//*	  This function has a register interface.								*/
//*	  Prototype: void core_nmppsConvert_32f32s_ceiling(ar0, ar1, gr0);	    */
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

global core_nmppsConvert_32f32f_ceiling: label;

begin ".text_nmplv"
<core_nmppsConvert_32f32f_ceiling>

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
	if =0 goto Packing_32f32f_less64_ceiling;

<Packing_32f32f_ceiling>
	fpu 0 rep 32 vreg2 = [ar0++];
	fpu 0 .float vreg2 = -vreg2 * .retrive(vreg1) - vreg0;
	gr1--;
	fpu 0 .packer = vreg2 with .fixed_32 <= .float;
	fpu 0 rep 32 vreg2 = .packer;
	fpu 0 .packer = vreg2 with .float <= .fixed_32;
	fpu 0 rep 32 vreg2 = .packer;
	if > delayed goto Packing_32f32f_ceiling;
		fpu 0 .float vreg2 = -vreg2;
		fpu 0 rep 32 [ar1++] = vreg2;

	gr0 = gr0 << 26;				            // computing a remainder
	gr0 = gr0 >> 26;				            // computing a remainder
	if =0 goto exit_Conv32f32f_ceiling;

<Packing_32f32f_less64_ceiling>			        // N < 64
	
	gr0 = gr0 >> 1;
	gr0--;
	vlen = gr0;
	fpu 0 rep vlen vreg0 = [ar2];
	fpu 0 rep vlen vreg2 = [ar0++];
	fpu 0 .float vreg2 = -vreg2 * .retrive(vreg1) - vreg0;
	fpu 0 .packer = vreg2 with .fixed_32 <= .float;
	fpu 0 rep vlen vreg2 = .packer;
	fpu 0 .packer = vreg2 with .float <= .fixed_32;
	fpu 0 rep vlen vreg2 = .packer;
	fpu 0 .float vreg2 = -vreg2;
	fpu 0 rep vlen [ar1++] = vreg2;



<exit_Conv32f32f_ceiling>
	return;
end ".text_nmplv";
