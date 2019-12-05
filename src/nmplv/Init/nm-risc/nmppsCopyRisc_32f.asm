//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM640x Software                      */
//*                                                                         */
//*   Software design:  A.Brodyazhenko                                      */
//*                                                                         */
//*   File:             nmppsCopyRisc_32f.asm                               */
//*   Contents:         It copies a float nums array (on RISC)              */
//***************************************************************************/

global _nmppsCopyRisc_32f: label;
begin ".text_nmplv"
<nmppsCopyRisc_32f>
	ar5 = ar7 - 2;
	push ar1, gr1;
	push ar0, gr0;
	
	ar0 = [--ar5]; // input x
	ar1 = [--ar5]; // output X
	gr7 = [--ar5]; // size N bytes

<CopyRisc_32f>
	gr0 = [ar0++];	// loading
    [ar1++] = gr0 with gr7--;
	if > delayed goto CopyRisc_32f;

<exit_CopyRisc_32f>
	pop ar0, gr0;
	pop ar1, gr1;
	return;
end ".text_nmplv";