//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM640x Software                      */
//*                                                                         */
//*   Software design:  A.Brodyazhenko                                      */
//*                                                                         */
//*   File:             nmpps-MulC_f.c                                      */
//*   Contents:         f = Const * x    							        */
//***************************************************************************/
#include "nmtype.h"

void nmppsMulC_32f(const nm32f* pSrcVec, nm32f* pDstVec, float C, int nSize)
{
    int i;
    for(i = 0; i < nSize; i++) {
        pDstVec[i] = C * pSrcVec[i];
    }
}

void nmppsMulC_AddV_AddC_32f(nm32f* pSrcVec, float mulVal, nm32f* pVecAdd, float addVal, nm32f* pDstVec, int nSize)
{
    int i;
    for(i = 0; i < nSize; i++) {
        pDstVec[i] = mulVal * pSrcVec[i] + pVecAdd[i] + addVal;
    }
}
