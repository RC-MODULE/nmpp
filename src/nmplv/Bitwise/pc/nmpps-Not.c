#include "nmpp.h"

void nmppsNot_8u(
const 	nm8u*			pSrcVec,		// input buffer		:long Local [VecSize/8]
		nm8u*			pDstVec,		// output buffer	:long Global[VecSize/8]
		int				nSize		// size of input buffer in 8 bit elements. nSize=[8,16,32...]
		)
{
	int i=0;
	for(i=0; i<nSize; i++)
		pDstVec[i] = ~(pSrcVec[i]);
}


/////////////////////////////////////////////////////////////////////////////////////////
// Notolute value calculation
void nmppsNot_16u(
const 	nm16u*			pSrcVec,		// input buffer		:long Local [VecSize/4]
		nm16u*			pDstVec,		// output buffer	:long Global[VecSize/4]
		int				nSize		// size of input buffer in 8 bit elements. nSize=[0,4,8,..]
		)
{
	int i=0;
	for(i=0; i<nSize; i++)
		pDstVec[i] = ~(pSrcVec[i]);

}



/////////////////////////////////////////////////////////////////////////////////////////
// Notolute value calculation
void nmppsNot_32u(
const 	nm32u*			pSrcVec,		// input buffer		:long Local [VecSize/2]
		nm32u*			pDstVec,		// output buffer	:long Global[VecSize/2]
		int				nSize		// size of input buffer in 32 bit elements. nSize=[2,4,6...]
		)
{
	int i=0;
	for(i=0; i<nSize; i++)
		pDstVec[i] = ~(pSrcVec[i]);

}



/////////////////////////////////////////////////////////////////////////////////////////
// Notolute value calculation
void nmppsNot_64u(
const 	nm64u*			pSrcVec,		// input buffer		:long Local [VecSize/2]
		nm64u*			pDstVec,		// output buffer	:long Global[VecSize/2]
		int				nSize		// size of input buffer in 32 bit elements. nSize=[2,4,6...]
		)
{


	int i=0;
	for(i=0; i<nSize; i++)
		pDstVec[i] = ~(pSrcVec[i]);


}
