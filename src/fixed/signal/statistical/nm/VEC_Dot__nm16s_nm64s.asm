//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM6403 Software                      */
//*                                                                         */
//*   Vector Processing  Library                                            */
//*   (C-callable functions)                                                */
//*                                                                         */
//*   $Workfile:: Prod64.asm                                               $*/
//*                                                                         */
//*   Contents:        Shift routines                                       */
//*                                                                         */
//*   Software design: Lukashevich Pavel                                    */
//*                                                                         */
//*   Version          1.0                                                  */
//*   Start date:      17.0.2002                                            */
//*   Release  $Date: 2004/11/22 13:50:11 $*/
//*                                                                         */
//*                                                                         */
//***************************************************************************/
//#include "vProd.h"

import from macros.mlb;
begin ".text_nmplv"
.branch;

//! \fn void nmppsDotProd_16s64s (nm16s *pSrcVec1, nm64s *pSrcVec2, int nSize, int64b *pnRes) 
//!
//! \perfinclude nmppsDotProd_16s64s.html

global _nmppsDotProd_16s64s:label;
<_nmppsDotProd_16s64s>
	ar5 = sp - 2;

	PUSH_REGS();

	ar0 = [--ar5];	// Input0 buffer
	ar4 = [--ar5];	// Input1 buffer
	gr6 = [--ar5];	// V0,V1 vectors Size
	ar6 = [--ar5];	// Output buffer 

	sb	= 00020002h;
	gr7 = 00000000h;
	nb1 = gr7 with gr6>>=2;


	rep 4 wfifo=[ar4++],ftw,wtw;
	with gr6--;
	rep 1 with vfalse;

<NextMul16>
	if > delayed goto NextMul16 with gr6--;
		rep 1 data=[ar0++] with vsum, data,afifo;
		rep 4 wfifo=[ar4++],ftw,wtw;
	
	rep 1 [ar6] = afifo;

	POP_REGS();

return;

.wait;
end ".text_nmplv"; 
