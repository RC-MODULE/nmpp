//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM640x Software, 2018                */
//*                                                                         */
//*   Software design:  A.Brodyazhenko                                      */
//*                                                                         */
//*   File:             nmppsConvert_32f32fcr.asm                           */
//*   Contents:         Convert data array from nm32s to nm32fcr            */
//*						nm32f    -> nm32fcr(re)								*/
//*						0	     -> nm32fcr(im)            				    */
//***************************************************************************/

global _nmppsConvert_32f32fcr: label;
begin "text"
<_nmppsConvert_32f32fcr>
	ar5 = ar7 - 2;
	push ar4, gr4;
	push ar3, gr3;
	push ar2, gr2;
	push ar1, gr1;
	push ar0, gr0;

	ar0 = [--ar5]; // input nm32s *x
	ar1 = [--ar5]; // output nm32fcr *X
	gr0 = [--ar5]; // size N

	gr0 - 1;
	if =0 delayed goto Packing_32f32fcr_1elem;
		gr1 = 4;
	
	ar2 = ar1 + 2;
	
	gr3 = gr0 >> 6;	// count of the iterations
	if =0 delayed goto Packing_32f32fcr_less64;
		gr2 = gr1;
		gr4 = gr0;

<Packing_32f32fcr>					// N > 64
	fpu 0 rep 32 vreg0 = [ar0++];
	fpu 0 .packer = vreg0 with .float .in_high <= .float .in_low;
	fpu rep 32 [ar1++gr1] = .packer;
	gr3--;
	if > delayed goto Packing_32f32fcr;
		fpu 0 .packer = vreg0 with .float .in_high <= .float .in_high;
		fpu rep 32 [ar2++gr2] = .packer;
	gr4 = gr4 << 26;				// computing a reminder
	gr4 = gr4 >> 26;				// computing a reminder
	if =0 goto exit_Conv32f32fcr;

<Packing_32f32fcr_less64>			// N < 64
	gr4 = gr4 >> 1;
	gr4--;
	vlen = gr4;
	fpu 0 rep vlen vreg0 = [ar0++];
	fpu 0 .packer = vreg0 with .float .in_high <= .float .in_low;
	fpu rep vlen [ar1++gr1] = .packer;

	gr0 = gr0 << 31;
	if =0 delayed goto exit_Conv32f32fcr; // if N is even then go to exit
		fpu 0 .packer = vreg0 with .float .in_high <= .float .in_high;
		fpu rep vlen [ar2++gr2] = .packer;

<Packing_32f32fcr_1elem>				  // if N is odd 
	fpu 0 rep 1 vreg0 = [ar0++];
	fpu 0 .packer = vreg0 with .float .in_high <= .float .in_low;
	fpu rep 1 [ar1++] = .packer;

<exit_Conv32f32fcr>
	pop ar0, gr0;
	pop ar1, gr1;
	pop ar2, gr2;
	pop ar3, gr3;
	pop ar4, gr4;
	return;
end "text";