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
