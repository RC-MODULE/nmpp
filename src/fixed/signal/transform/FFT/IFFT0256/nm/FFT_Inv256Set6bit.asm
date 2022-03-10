//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM6403 Software                      */
//*                                                                         */
//*   Fast Fourie Transform Library                                         */
//*   (C-callable functions)                                                */
//*                                                                         */
//*   File:             FFT256.asm                                          */
//*   Contents:         Routine for forward FFT 256 of complex array        */
//*                     with 32 bit elements                                */
//*                                                                         */
//*   Software design:  S.Mushkaev                                          */
//*                                                                         */
//*   Version           1.2                                                 */
//*   Start date:       03.07.2000                                          */
//*   Release  $Date: 2005/02/10 11:47:59 $*/
//*                                                                         */
//*                                                                         */
//***************************************************************************/

extern IW1_256_6bit	:long;
extern IW2_256_6bit	:long;

extern IW1_256:word;
extern IW2_256:word;
extern IDefaultShiftR2_256:word;

begin ".text_fft"
    //--------------------------------------------------------------------
    //! \fn void FFT_Inv256Set6bit()
	//!
	//! \n
    //--------------------------------------------------------------------
global _FFT_Inv256Set6bit:label;
<_FFT_Inv256Set6bit>
.branch;
			 gr7 = IW1_256_6bit;
	[IW1_256]=gr7;
			 gr7 = IW2_256_6bit;
	[IW2_256]=gr7;
			 gr7 = 12;			
	delayed return;
		[IDefaultShiftR2_256] = gr7;		
		nul;
.wait;
end ".text_fft";