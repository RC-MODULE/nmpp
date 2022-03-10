//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM6403 Software                      */
//*                                                                         */
//*   Vector Processing  Library                                            */
//*   (C-callable functions)                                                */
//*                                                                         */
//*   $Workfile:: VecArithm.cpp                                            $*/
//*                                                                         */
//*   Contents:        Arithmetic  routines                                 */
//*                                                                         */
//*   Software design: S.Mushkaev                                           */
//*                                                                         */
//*   Version          1.0                                                  */
//*   Start date:      14.11.2001                                           */
//*   Release  $Date: 2004/11/22 13:50:15 $*/
//*                                                                         */
//*                                                                         */
//***************************************************************************/
#include "rpc-host.h"
#include "nmtype.h"


/////////////////////////////////////////////////////////////////////////////////////////
// Sign reversion
void nmppsNeg_8s(
		const nm8s*			pSrcVec,		// input buffer		:long Local [Size/8]
		nm8s*			pDstVec,		// output buffer	:long Global[Size/8]
		int				nSize			// size of input buffer in 8 bit elements. nSize=[0,8,16,24...]
		)
{
	RPC_PPI(pSrcVec,pDstVec,nSize);
}


/////////////////////////////////////////////////////////////////////////////////////////
// Sign reversion
void nmppsNeg_16s(
		const nm16s*			pSrcVec,		// input buffer		:long Local [Size/4]
		nm16s*			pDstVec,		// output buffer	:long Global[Size/4]
		int				nSize			// size of input buffer in 16-bit elements. nSize=[0,4,8,12..]
		)
{
	RPC_PPI(pSrcVec,pDstVec,nSize);
}


/////////////////////////////////////////////////////////////////////////////////////////
// Sign reversion
void nmppsNeg_32s(
		const nm32s*			pSrcVec,		// input buffer		:long Local [Size/2]
		nm32s*			pDstVec,		// output buffer	:long Global[Size/2]
		int				nSize			// size of input buffer in 32-bit elements. nSize=[0,2,4,6...]
		)
{
	RPC_PPI(pSrcVec,pDstVec,nSize);
}


/////////////////////////////////////////////////////////////////////////////////////////
// Sign reversion
void nmppsNeg_64s(
		const nm64s*		pSrcVec,		// input buffer		:long Local [nSize]
		nm64s*		pDstVec,		// output buffer	:long Global[nSize]
		int				nSize			// size of input buffer in 64-bit elements. nSize=[0,1,2,3...]
		)
{
	RPC_PPI(pSrcVec,pDstVec,nSize);
}

