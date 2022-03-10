//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM6403 Software                      */
//*                                                                         */
//*   Fast Fourie Transform Library                                         */
//*   (C-callable functions)                                                */
//*                                                                         */
//*   File:             FFT2048.asm                                         */
//*   Contents:         Routine for forward FFT 2048 of complex array       */
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
extern IW1_2048_7bit	:long;
extern IW2_2048_7bit	:long;
extern IW1_2048_6bit	:long;
extern IW2_2048_6bit	:long;

extern IW1_2048:word;
extern IW2_2048:word;
extern IDefaultShiftR2_2048:word;		

begin ".text_fft"
    //--------------------------------------------------------------------
    //! \fn void FFT_Inv2048Set6bit()
	//!
	//! \n
    //--------------------------------------------------------------------
global _FFT_Inv2048Set6bit:label;
<_FFT_Inv2048Set6bit>
.branch;
	ar5=sp-2;
				gr7 = IW1_2048_6bit;
	[IW1_2048] = gr7;
				gr7 = IW2_2048_6bit;
	[IW2_2048] = gr7;
				gr7 = 12;			
	delayed return;
		[IDefaultShiftR2_2048] = gr7;		
		nul;
.wait;


end ".text_fft";
