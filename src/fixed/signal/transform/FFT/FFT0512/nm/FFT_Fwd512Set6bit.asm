//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM6403 Software                      */
//*                                                                         */
//*   Fast Fourie Transform Library                                         */
//*   (C-callable functions)                                                */
//*                                                                         */
//*   File:             FFT512.asm                                          */
//*   Contents:         Routine for forward FFT 512 of complex array        */
//*                     with 32 bit elements                                */
//*                                                                         */
//*   Software design:  S.Mushkaev                                          */
//*                                                                         */
//*   Version           1.2                                                 */
//*   Start date:       03.07.2000                                          */
//*   Release   $Date: 2005/02/10 11:47:59 $*/
//*                                                                         */
//*                                                                         */
//***************************************************************************/

extern W1_512_7bit	:long;
extern W2_512_7bit	:long;
extern W1_512_6bit	:long;
extern W2_512_6bit	:long;

extern W1_512:word;
extern W2_512:word;
extern DefaultShiftR_512:word;		

begin ".text_fft"

    //--------------------------------------------------------------------
    //! \fn void FFT_Fwd512Set6bit()
	//!
	//! \n
    //--------------------------------------------------------------------
global _FFT_Fwd512Set6bit:label;
<_FFT_Fwd512Set6bit>
.branch;
			   gr7 = W1_512_6bit;
	[W1_512] = gr7;
			   gr7 = W2_512_6bit;
	[W2_512] = gr7;
			   gr7 = 12;			
	delayed return;
		[DefaultShiftR_512] = gr7;		
		nul;
.wait;



end ".text_fft";