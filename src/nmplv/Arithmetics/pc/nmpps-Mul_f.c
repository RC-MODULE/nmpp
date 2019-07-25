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


void nmppsMul_32f(const nm32f* pSrcVec1, const nm32f* pSrcVec2, nm32f* pDstVec, int nSize)
{
	int i;
	for(i = 0; i < nSize; i++) {
		pDstVec[i] = pSrcVec1[i] * pSrcVec2[i];
	}
}

void nmppsMul_32fcr(const nm32fcr* pSrcVec1, const nm32fcr* pSrcVec2, nm32fcr* pDstVec, int nSize)
{
	int i;
	for(i = 0; i < nSize; i++) {
		float re, im;
		re = pSrcVec1[i].re * pSrcVec2[i].re - pSrcVec1[i].im * pSrcVec2[i].im;
		im = pSrcVec1[i].re * pSrcVec2[i].im + pSrcVec1[i].im * pSrcVec2[i].re;
		pDstVec[i].re = re;
		pDstVec[i].im = im;
	}
}

void nmppsConjMul_32fcr(const nm32fcr* pSrcVec1, const nm32fcr* pSrcVec2, nm32fcr* pDstVec, int nSize)
{
	int i;
	for(i = 0; i < nSize; i++) {
		float re, im;
		re = pSrcVec1[i].re * pSrcVec2[i].re + pSrcVec1[i].im * pSrcVec2[i].im;
		im = -pSrcVec1[i].re * pSrcVec2[i].im + pSrcVec1[i].im * pSrcVec2[i].re;
		pDstVec[i].re = re;
		pDstVec[i].im = im;
	}
}

