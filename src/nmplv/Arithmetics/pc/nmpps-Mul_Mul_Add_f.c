//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM640x Software                      */
//*                                                                         */
//*   Software design:  A.Brodyazhenko                                      */
//*                                                                         */
//*   File:             nmpps-Mul_Mul_Add.c                                 */
//*   Contents:         f = x1 * y1 + x2 * y2     							*/
//*   			        f = x1 * y1 + x2 * Conjugate(y2)     				*/
//***************************************************************************/

// x1 - pSrcVec1
// y1 - pSrcVec2
// x2 - pSrcVec3
// y2 - pSrcVec4
// f  - pDstVec

#include "nmtype.h"

void nmppsMul_Mul_Add_64f(const nm64f *pSrcVec1, const nm64f *pSrcVec2, const nm64f *pSrcVec3, const nm64f *pSrcVec4, nm64f *pDstVec, int nSize)
{
  int i;
  for(i = 0; i < nSize; i++) {
    pDstVec[i] = pSrcVec1[i] * pSrcVec2[i] + pSrcVec3[i] * pSrcVec4[i];
  }
}
void nmppsMul_Mul_Add_32fcr(const nm32fcr *pSrcVec1, const nm32fcr *pSrcVec2, const nm32fcr *pSrcVec3, const nm32fcr *pSrcVec4, nm32fcr *pDstVec, int nSize)
{
	int i;
	for(i = 0; i < nSize; i++) {
		float re1, im1;
		float re2, im2;

		/***************************x1 * y1******************************/
		re1 = pSrcVec1[i].re * pSrcVec2[i].re - pSrcVec1[i].im * pSrcVec2[i].im;
		im1 = pSrcVec1[i].re * pSrcVec2[i].im + pSrcVec1[i].im * pSrcVec2[i].re;

		/***********************x2 * Conjugate(y2)***********************/
		re2 = pSrcVec3[i].re * pSrcVec4[i].re - pSrcVec3[i].im * pSrcVec4[i].im;
		im2 = pSrcVec3[i].re * pSrcVec4[i].im + pSrcVec3[i].im * pSrcVec4[i].re;

		/************************f = x1 * y1 + x2 * y2*******************/
		pDstVec[i].re = re1 + re2;
		pDstVec[i].im = im1 + im2;
	}
}

void nmppsMul_ConjMul_Add_32fcr(const nm32fcr *pSrcVec1, const nm32fcr *pSrcVec2, const nm32fcr *pSrcVec3, const nm32fcr *pSrcVec4, nm32fcr *pDstVec, int nSize)
{
	int i;
	for(i = 0; i < nSize; i++) {
		float re1, im1;
		float re2, im2;

		/***************************x1 * y1******************************/
		re1 = pSrcVec1[i].re * pSrcVec2[i].re - pSrcVec1[i].im * pSrcVec2[i].im;
		im1 = pSrcVec1[i].re * pSrcVec2[i].im + pSrcVec1[i].im * pSrcVec2[i].re;

		/***********************x2 * Conjugate(y2)***********************/
		re2 = pSrcVec3[i].re * pSrcVec4[i].re + pSrcVec3[i].im * pSrcVec4[i].im;
		im2 = -pSrcVec3[i].re * pSrcVec4[i].im + pSrcVec3[i].im * pSrcVec4[i].re;

		/**********************f = x1 * y1 + x2 * Conjugate(y2)**************/
		pDstVec[i].re = re1 + re2;
		pDstVec[i].im = im1 + im2;
	}
}
