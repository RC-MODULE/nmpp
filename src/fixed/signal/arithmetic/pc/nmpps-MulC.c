//------------------------------------------------------------------------
//
//  $Workfile:: Mul_VxxNxx.cp $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:15 $
//
//! \if file_doc
//!
//! \file   Mul_VxxNxx.cpp
//! \author Сергей Мушкаев
//! \brief  Функции умножения для векторов.
//!
//! \endif
//!
//------------------------------------------------------------------------


#include "nmtype.h"
/////////////////////////////////////////////////////////////////////////////////////////
// Multiplying 64-bit buffer elements by 64-bit scalar value
void nmppsMulC_64s(
const 	  nm64s*		pSrcVec,				// input  buffer		:long Local  [nSize]
		  nm64s			MulN,				// 64-bit scalar value
		  nm64s*		pDstVec,				// output buffer		:long Global [nSize]
			int			nSize				// size of input buffer in 64-bit elements. nSize=[0,1,2,3..]
		)
{
	int i;
	for (i=0;i<nSize;i++)
		pDstVec[i]=pSrcVec[i]*MulN;
}

/////////////////////////////////////////////////////////////////////////////////////////
// Multiplying 32-bit buffer elements by 64-bit scalar value
void nmppsMulC_32s64s(
const 		nm32s*		pSrcVec,			// input  buffer		:long Local  [VecSize/2]
			nm64s		MulN,			// 64-bit scalar value
			nm64s*		pDstVec,			// output buffer		:long Global [nSize]
			int			nSize			// size of input buffer in 32-bit elements. nSize=[0,2,4,6...]
		)
{
	int i;
	for (i=0;i<nSize;i++)
		pDstVec[i]=pSrcVec[i]*MulN;
}

/////////////////////////////////////////////////////////////////////////////////////////
// Multiplying 16-bit buffer elements by 16-bit scalar value
void nmppsMulC_16s(
const 		nm16s*		pSrcVec,		// input  buffer		:long Local  [VecSize/4]
			int			MulN,			// 32-bit scalar value
			nm16s*		pDstVec,		// output buffer		:long Global [VecSize/2]
			int			nSize			// size of input buffer in 16-bit elements. nSize=[0,4,8...]
		)
{
	int i;
	for (i=0;i<nSize;i++)
		pDstVec[i]=pSrcVec[i]*MulN;

}


/////////////////////////////////////////////////////////////////////////////////////////
// Multiplying 16-bit buffer elements by 32-bit scalar value
void nmppsMulC_16s32s(
const 		nm16s*		pSrcVec,		// input  buffer		:long Local  [VecSize/4]
			int			MulN,				// 32-bit scalar value
			nm32s*		pDstVec,		// output buffer		:long Global [VecSize/2]
			int			nSize			// size of input buffer in 16-bit elements. nSize=[0,4,8...]
		)
{
	int i;
	for (i=0;i<nSize;i++)
		pDstVec[i]=pSrcVec[i]*MulN;
}


/////////////////////////////////////////////////////////////////////////////////////////
// Multiplying 32-bit buffer elements by scalar value
void nmppsMulC_32s(
const 		nm32s*		pSrcVec,			// input vec			:long Local  [VecSize/2]
			int			MulN,				// 32-bit scalar value
			nm32s*		pDstVec,			// output vec		:long Global [VecSize/2]
			int			nSize			// size of input buffer in 32-bit elements. nSize=[0,2,4,6...]
		)
{
	int i;
	for (i=0;i<nSize;i++)
		pDstVec[i]=pSrcVec[i]*MulN;
}



/////////////////////////////////////////////////////////////////////////////////////////
// Multiplying 8-bit buffer elements by 16-bit scalar value
void nmppsMulC_8s16s(
const 		nm8s*		pSrcVec,		// input  buffer					:long Local  [VecSize/8]
			int16b		MulN,				// 16-bit scalar value
			nm16s*		pDstVec,		// output buffer					:long Global [VecSize/4]
			int			nSize			// size of input buffer in 8-bit elements. nSize=[0,8,16...]
		)
{
	int i;
	MulN=(short)MulN;
	for (i=0;i<nSize;i++)
		pDstVec[i]=pSrcVec[i]*MulN;
}


/////////////////////////////////////////////////////////////////////////////////////////
// Multiplying 8-bit buffer elements by 8-bit scalar value
void nmppsMulC_8s(
const 		nm8s*		pSrcVec,		// input  buffer					:long Local  [VecSize/8]
			int8b		MulN,			// 8-bit scalar value
			nm8s*		pDstVec,		// output buffer					:long Global [VecSize/8]
			int			nSize			// size of input buffer in 8-bit elements. nSize=[0,8,16...]
		)
{
	int i;
	MulN=(short)MulN;
	for (i=0;i<nSize;i++)
		pDstVec[i]=pSrcVec[i]*MulN;


}



/////////////////////////////////////////////////////////////////////////////////////////
// Multiplying 32-bit buffer elements by scalar value
// pDstVec[i]=pSrcVec[i]*MulN+AddN
void nmppsMulC_AddC_32s(
const 		nm32s*		pSrcVec,			// input vec			:long Local  [VecSize/2]
			int			MulN,			// multiplier
			int			AddN,			// additional constant
			nm32s*		pDstVec,			// output vec		:long Global [VecSize/2]
			int			nSize			// size of input buffer in 32-bit elements. nSize=[0,2,4,6...]
		)
{
	nmppsMulC_32s(pSrcVec,MulN,pDstVec,nSize);
	nmppsAddC_32s(pDstVec,AddN,pDstVec,nSize);
}


void nmppsMulC_AddC_2x32s(int32x2* dataSparseSrc,  int32x2* mulArg, int32x2* addArg, int32x2 *dataSparseDst,  int size, int stepSparseSrc, int stepSparseDst)
{
	int32x2* pSrc=dataSparseSrc;
	int32x2* pDst=dataSparseDst;
	int i;
	for (i=0; i<size; i++){
		pDst->lo=pSrc->lo*mulArg->lo+addArg->lo;
		pDst->hi=pSrc->hi*mulArg->hi+addArg->hi;
		pSrc+=stepSparseSrc;
		pDst+=stepSparseDst;
	}
}


void nmppsRShiftC_MulC_AddC_2x32s(int32x2* dataSparseSrc,  int32x2* preshiftArg, int32x2* mulArg, int32x2* addArg, int32x2* dataSparseDst,  int size, int stepSparseSrc, int stepSparseDst)
{
	int32x2* pSrc=dataSparseSrc;
	int32x2* pDst=dataSparseDst;
	int i;
	for (i=0; i<size; i++){
		pDst->lo=(pSrc->lo>>preshiftArg->lo)*mulArg->lo+addArg->lo;
		pDst->hi=(pSrc->hi>>preshiftArg->hi)*mulArg->hi+addArg->hi;
		pSrc+=stepSparseSrc;
		pDst+=stepSparseDst;
	}
}


/////////////////////////////////////////////////////////////////////////////////////////
// Multiplying 32-bit buffer elements by scalar value with vec and constant addition
// pDstVec[i]=pSrcVec1[i]*MulN+pSrcVec2[i]+AddN
void nmppsMulC_AddV_AddC_32s(
			nm32s*		pSrcVec1,		// input vec			:long Local  [VecSize/2]
			int			MulN,			// multiplier
			nm32s*		pSrcVec2,		// input add vec		:long Any	 [VecSize/2]
			int			AddN,			// additional constant
			nm32s*		pDstVec,			// output vec		:long Global [VecSize/2]
			int			nSize			// size of input buffer in 32-bit elements. nSize=[0,2,4,6...]
		)
{
	int i;
	for (i=0;i<nSize;i++)
		pDstVec[i]=pSrcVec1[i]*MulN+pSrcVec2[i]+AddN;
}
