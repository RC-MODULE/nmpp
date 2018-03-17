//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM640x Software                      */
//*                                                                         */
//*   Software design:  A.Brodyazhenko                                      */
//*                                                                         */
//*   File:             nmpps-Mul.c                                         */
//*   Contents:         Multiplies the elements of two vectors              */
//***************************************************************************/
#include "nmtype.h"

void nmppsMul_32fcr(const nm32fcr *pSrcVec1, const nm32fcr *pSrcVec2, nm32fcr *pDstVec, int nSize)
{
	int i;
	for(i = 0; i < nSize; i++) {
		pDstVec[i].re = pSrcVec1[i].re * pSrcVec2[i].re - pSrcVec1[i].im * pSrcVec2[i].im;
		pDstVec[i].im = pSrcVec1[i].re * pSrcVec2[i].im + pSrcVec1[i].im * pSrcVec2[i].re;	
	}
}

void nmppsMulConj_32fcr(const nm32fcr *pSrcVec1, const nm32fcr *pSrcVec2, nm32fcr *pDstVec, int nSize)
{
	int i;
	for(i = 0; i < nSize; i++) {
		pDstVec[i].re = pSrcVec1[i].re * pSrcVec2[i].re + pSrcVec1[i].im * pSrcVec2[i].im;
		pDstVec[i].im = -pSrcVec1[i].re * pSrcVec2[i].im + pSrcVec1[i].im * pSrcVec2[i].re;
	}
}

