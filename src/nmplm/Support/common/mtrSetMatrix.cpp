//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM6403 Software                      */
//*                                                                         */
//*   Vector Processing  Library                                            */
//*   (C-callable functions)                                                */
//*                                                                         */
//*   $Workfile:: mtrSetMatrix.cpp                                         $*/
//*                                                                         */
//*   Contents:        Routines for vec copying                          */
//*                                                                         */
//*   Software design: S.Mushkaev                                           */
//*                                                                         */
//*   Version          1.0                                                  */
//*   Start date:      27.05.2002                                           */
//*   Release  $Date: 2005/01/12 14:05:15 $*/
//*                                                                         */
//*                                                                         */
//***************************************************************************/

#include "nmplv.h"

    //--------------------------------------------------------------------
    //! 
	//!
	//! \perfinclude _MTR_SetM__FPciiPciiii.html
    //--------------------------------------------------------------------
 
void MTR_SetM(
   		nm8s*	pSrcMtr,
			int		nSrcRows,		// =[0,1,2,3...]
			int		nSrcStride,		// =[8,16,24...]
			nm8s*	pDstMtr,			
			int		nDstRows,		// =[0,1,2,3...]
			int		nDstStride,		// =[8,16,24,..]
			int		nDstRowIndex,			// =[0,1,2,3...]
			int		nDstOffset			// =[0,8,16,24.]
			)
{
	pDstMtr=nmppsAddr_8s(pDstMtr,nDstStride*nDstRowIndex+nDstOffset);
	for(int col=0;col<nSrcRows;col++)
	{
		nmppsCopy_8s(pSrcMtr,pDstMtr,nSrcStride);
		pSrcMtr=nmppsAddr_8s(pSrcMtr,nSrcStride);
		pDstMtr=nmppsAddr_8s(pDstMtr,nDstStride);
	}
}


