//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM640x Software                      */
//*                                                                         */
//*   Software design:  A.Brodyazhenko                                      */
//*                                                                         */
//*   File:             nmppsConvertRisc_8u32u.asm                          */
//*   Contents:         it converts byte array to int array (on RISC)		*/
//***************************************************************************/

global _nmppsConvertRisc_8u32u: label;
begin "text"
<_nmppsConvertRisc_8u32u>
	ar5 = ar7 - 2;
	push ar6, gr6;
	push ar5, gr5;
	push ar4, gr4;
	push ar3, gr3;
	push ar2, gr2;
	push ar1, gr1;
	push ar0, gr0;
	
	ar0 = [--ar5]; // input x
	ar1 = [--ar5]; // output X
	gr7 = [--ar5]; // size N bytes

	gr3 = 0FFh;	   // Const for a first byte
	ar3 = gr3 with gr7 = gr7 >> 3;

<Convert8u32u>
	ar2, gr2 = [ar0++];	// loading 
	
	gr0 = ar2 with gr1 = gr2 and gr3;   // a fifth byte 5
	
	gr3 = gr0 and gr3;				    // a first byte 1

	[ar1++] = gr3 with gr5 = gr0 << 16;
	gr5 = gr5 >> 24;				    // a second byte 2

	[ar1++] = gr5 with gr6 = gr0 << 8;
	gr3 = ar3 with gr6 = gr6 >> 24;     // gr3 = 0FFh and a third byte 3

	[ar1++] = gr6 with gr0 = gr0 >> 24; // a fourth byte 4

	[ar1++] = gr0 with gr4 = gr2 << 16;
	[ar1++] = gr1 with gr4 = gr4 >> 24; // a sixth byte 6

	[ar1++] = gr4 with gr5 = gr2 << 8;
	gr5 = gr5 >> 24;					// a seventh byte 7

	gr6 = gr2 >> 24;					// a eighth byte 8

	gr7--;
	if > delayed goto Convert8u32u;
	[ar1++] = gr5;
	[ar1++] = gr6;

<exit_Conv8u32u>
	pop ar0, gr0;
	pop ar1, gr1;
	pop ar2, gr2;
	pop ar3, gr3;
	pop ar4, gr4;
	pop ar5, gr5;
	pop ar6, gr6;
	return;
end "text";