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
extern IW1_512_7bit	:long;
extern IW2_512_7bit	:long;
extern IW1_512_6bit	:long;
extern IW2_512_6bit	:long;

extern	IW1_512:word;
extern 	IW2_512:word;
extern  IDefaultShiftR2_512:word;		

begin ".text_fft"

    //--------------------------------------------------------------------
    //! \fn void FFT_Inv512Set7bit()
	//!
	//! \n
    //--------------------------------------------------------------------
global _FFT_Inv512Set7bit:label;
<_FFT_Inv512Set7bit>
.branch;
	gr7=IW1_512_7bit;
	[IW1_512]=gr7;
	gr7=IW2_512_7bit;
	[IW2_512]=gr7;
	gr7=14;
	delayed return;
		[IDefaultShiftR2_512]=gr7;		
		nul;
.wait;



end ".text_fft";