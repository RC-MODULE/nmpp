//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM640x Software                      */
//*                                                                         */
//*   Software design:  A.Brodyazhenko                                      */
//*                                                                         */
//*   File:             nmpps-Mul_Mul_Sub_f.c                               */
//*   Contents:         f = x1 * y1 - x2 * y2     							*/
//***************************************************************************/

// x1 - pSrcVec1
// y1 - pSrcVec2
// x2 - pSrcVec3
// y2 - pSrcVec4
// f  - pDstVec

#include "nmtype.h"

void nmppsMul_Mul_Sub_32f(const nm32f* pSrcVec1, const nm32f* pSrcVec2, const nm32f* pSrcVec3, const nm32f* pSrcVec4, nm32f* pDstVec, int nSize)
{
  int i;
  for(i = 0; i < nSize; i++) {
    pDstVec[i] = pSrcVec1[i] * pSrcVec2[i] - pSrcVec3[i] * pSrcVec4[i];
  }
}
