//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM6403 Software                      */
//*                                                                         */
//*   Fast Fourie Transform Library                                         */
//*   (C-callable functions)                                                */
//*                                                                         */
//*   File:             FFT1024.asm                                         */
//*   Contents:         Routine for forward FFT 1024 of complex array       */
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
extern W1_1024_7bit	:long;
extern W2_1024_7bit	:long;
extern W1_1024_6bit	:long;
extern W2_1024_6bit	:long;

extern W1_1024:word;
extern W2_1024:word;
extern DefaultShiftR_1024:word;		

begin ".text_fft"

    //--------------------------------------------------------------------
    //! \fn void FFT_Fwd1024Set7bit()
	//!
	//! \n
    //--------------------------------------------------------------------
global _FFT_Fwd1024Set7bit:label;
<_FFT_Fwd1024Set7bit>
.branch;
	ar5=sp-2;
				gr7=W1_1024_7bit;
	[W1_1024]=	gr7;
				gr7=W2_1024_7bit;
	[W2_1024]=	gr7;
				gr7=14;
	delayed return;
		[DefaultShiftR_1024]=gr7;		
		nul;
.wait;

end ".text_fft";