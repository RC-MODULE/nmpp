//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM640x Software                      */
//*                                                                         */
//*   Software design:  A.Brodyazhenko                                      */
//*                                                                         */
//*   File:             nmpps-vMul_32fc_pc.c                                */
//*   Contents:         Multiplies the elements of two vectors              */
//***************************************************************************/
#include "nmtype.h"

void nmppsMul_32fc(int N, nm32fcr *vec1, nm32fcr *vec2, nm32fcr *dst)
{
	int i;
	for(i = 0; i < N; i++) {
		dst[i].re = vec1[i].re * vec2[i].re - vec1[i].im * vec2[i].im;
		dst[i].im = vec1[i].re * vec2[i].im + vec1[i].im * vec2[i].re;	
	}
}

