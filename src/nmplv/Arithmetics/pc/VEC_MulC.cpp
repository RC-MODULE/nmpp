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
//#include "vec.h"
#include "nmplv.h"
//#include "nmtl.h"
/////////////////////////////////////////////////////////////////////////////////////////
// Multiplying 64-bit buffer elements by 64-bit scalar value
void nmppsMulC_64s(
		  nm64s*		pSrcVec,				// input  buffer		:long Local  [nSize]
		  nm64s			MulN,				// 64-bit scalar value
		  nm64s*		pDstVec,				// output buffer		:long Global [nSize]
			int			nSize				// size of input buffer in 64-bit elements. nSize=[0,1,2,3..]
		)
{
	//if (CHECK_OVERFLOW())
	//{
	//	nmvec64s SrcVec(pSrcVec,nSize);
	//	nmint64s C(MulN);
	//	nmvec64s DstVec(pDstVec,nSize);
	//	for(int i=0; i<nSize; i++)
	//		DstVec[i] = SrcVec[i] * C;
	//}
	//else
		for(int i=0;i<nSize;i++)
			pDstVec[i]=pSrcVec[i]*MulN;
	// No IPPS analog

}
/////////////////////////////////////////////////////////////////////////////////////////
// Multiplying 32-bit buffer elements by 64-bit scalar value
void nmppsMulC_32s(
			nm32s*		pSrcVec,			// input  buffer		:long Local  [VecSize/2]
			nm64s		MulN,			// 64-bit scalar value
			nm64s*		pDstVec,			// output buffer		:long Global [nSize]
			int			nSize			// size of input buffer in 32-bit elements. nSize=[0,2,4,6...]
		)
{
	//if (CHECK_OVERFLOW())
	//{
	//	nmvec32s SrcVec((nm32s*)pSrcVec,nSize);
	//	nmint64s C(MulN);
	//	nmvec64s DstVec(pDstVec,nSize);
	//	for(int i=0; i<nSize; i++)
	//		DstVec[i] = SrcVec[i] * C;
	//}
	//else
		for(int i=0;i<nSize;i++)
			pDstVec[i]=pSrcVec[i]*MulN;
	// No IPPS analog
}
/////////////////////////////////////////////////////////////////////////////////////////
// Multiplying 16-bit buffer elements by 32-bit scalar value
void nmppsMulC_16s(
			nm16s*		pSrcVec,		// input  buffer		:long Local  [VecSize/4]
			int			MulN,				// 32-bit scalar value
			nm32s*		pDstVec,		// output buffer		:long Global [VecSize/2]
			int			nSize			// size of input buffer in 16-bit elements. nSize=[0,4,8...]
		)
{
	//if (CHECK_OVERFLOW())
	//{
	//	nmvec16s SrcVec((nm16s*)pSrcVec,nSize);
	//	nmint32s C(MulN);
	//	nmvec32s DstVec(pDstVec,nSize);
	//	for(int i=0; i<nSize; i++)
	//		DstVec[i] = SrcVec[i] * C;
	//}
	//else
		for(int i=0;i<nSize;i++)
			pDstVec[i]=pSrcVec[i]*MulN;
	// No IPPS analog
}

/////////////////////////////////////////////////////////////////////////////////////////
// Multiplying 32-bit buffer elements by scalar value
void nmppsMulC_32s(
			nm32s*		pSrcVec,			// input vec			:long Local  [VecSize/2]
			int			MulN,				// 32-bit scalar value
			nm32s*		pDstVec,			// output vec		:long Global [VecSize/2]
			int			nSize			// size of input buffer in 32-bit elements. nSize=[0,2,4,6...]
		)
{
#ifndef USE_IPP
	//if (CHECK_OVERFLOW())
	//{
	//	nmvec32s SrcVec((int*)pSrcVec,nSize);
	//	nmint32s C(MulN);
	//	nmvec32s DstVec(pDstVec,nSize);
	//	for(int i=0; i<nSize; i++)
	//		DstVec[i] = SrcVec[i] * C;
	//}
	//else
		for(int i=0;i<nSize;i++)
			pDstVec[i]=pSrcVec[i]*MulN;
#else
	if (pSrcVec!=pDstVec)
		ippsMulC_32s_Sfs(pSrcVec,MulN,pDstVec, nSize,0);
	else
		ippsMulC_32s_ISfs(MulN, pSrcVec, nSize,0);
#endif

}


/////////////////////////////////////////////////////////////////////////////////////////
// Multiplying 8-bit buffer elements by 16-bit scalar value
void nmppsMulC_8s(
			nm8s*		pSrcVec,		// input  buffer					:long Local  [VecSize/8]
			int16b		MulN,				// 16-bit scalar value
			nm16s*		pDstVec,		// output buffer					:long Global [VecSize/4]
			int			nSize			// size of input buffer in 8-bit elements. nSize=[0,8,16...]
		)
{
	MulN=short(MulN);
	//if (CHECK_OVERFLOW())
	//{
	//	nmvec8s SrcVec((nm8s*)pSrcVec,nSize);
	//	nmint16s C(MulN);
	//	nmvec16s DstVec(pDstVec,nSize);
	//	for(int i=0; i<nSize; i++)
	//		DstVec[i] = SrcVec[i] * C;
	//}
	//else
		for(int i=0;i<nSize;i++)
			pDstVec[i]=pSrcVec[i]*MulN;
	// No IPP analog
}

/////////////////////////////////////////////////////////////////////////////////////////
// Multiplying 8-bit buffer elements by 8-bit scalar value
void nmppsMulC_8s(
			nm8s*		pSrcVec,		// input  buffer					:long Local  [VecSize/8]
			int8b		MulN,			// 8-bit scalar value
			nm8s*		pDstVec,		// output buffer					:long Global [VecSize/8]
			int			nSize			// size of input buffer in 8-bit elements. nSize=[0,8,16...]
		)
{
	MulN=short(MulN);
	//if (CHECK_OVERFLOW())
	//{
	//	nmvec8s SrcVec((nm8s*)pSrcVec,nSize);
	//	nmint8s C(MulN);
	//	nmvec8s DstVec(pDstVec,nSize);
	//	for(int i=0; i<nSize; i++)
	//		DstVec[i] = SrcVec[i] * C;
	//}
	//else
		for(int i=0;i<nSize;i++)
			pDstVec[i]=pSrcVec[i]*MulN;
	// No IPP analog
}


/////////////////////////////////////////////////////////////////////////////////////////
// Multiplying 32-bit buffer elements by scalar value
// pDstVec[i]=pSrcVec[i]*MulN+AddN
void nmppsMulC_AddC_32s(
			nm32s*		pSrcVec,			// input vec			:long Local  [VecSize/2]
			int			MulN,			// multiplier 
			int			AddN,			// additional constant
			nm32s*		pDstVec,			// output vec		:long Global [VecSize/2]
			int			nSize			// size of input buffer in 32-bit elements. nSize=[0,2,4,6...]
		)
{
	/*
	if (CHECK_OVERFLOW())
	{
		vec<nmint<32> > Scalar(1);
		vec<nmint<32> > SrcVec(nSize);
		vec<nmint<32> > DstVec(nSize);
		Scalar[0]=MulN;
		SrcVec.SetData(pSrcVec);
		DstVec=SrcVec*Scalar;
		Scalar[0]=AddN;
		DstVec+=Scalar;
		DstVec.GetData(pDstVec);
	}
	else
		for(int i=0;i<nSize;i++)
			pDstVec[i]=pSrcVec[i]*MulN+AddN;
		*/
	nmppsMulC_32s(pSrcVec,MulN,pDstVec,nSize);
	nmppsAddC_32s(pDstVec,AddN,pDstVec,nSize);
}
/*
void nmppsMulC_AddC(int32x2* dataSparseSrc,  int32x2& mulArg, int32x2& addArg, int32x2 *dataSparseDst,  int size, int stepSparseSrc, int stepSparseDst)
{
	int32x2* pSrc=dataSparseSrc;
	int32x2* pDst=dataSparseDst;
	for(int i=0; i<size; i++){
		pDst->lo()=pSrc->lo()*mulArg.lo()+addArg.lo();
		pDst->hi()=pSrc->hi()*mulArg.hi()+addArg.hi();
		pSrc+=stepSparseSrc;
		pDst+=stepSparseDst;
	}
}

void nmppsArshC_MulC_AddC_(int32x2* dataSparseSrc,  int32x2& preshiftArg, int32x2& mulArg, int32x2& addArg, int32x2 *dataSparseDst,  int size, int stepSparseSrc, int stepSparseDst)
{
	int32x2* pSrc=dataSparseSrc;
	int32x2* pDst=dataSparseDst;
	for(int i=0; i<size; i++){
		pDst->lo()=(pSrc->lo()>>preshiftArg.lo())*mulArg.lo()+addArg.lo();
		pDst->hi()=(pSrc->hi()>>preshiftArg.hi())*mulArg.hi()+addArg.hi();
		pSrc+=stepSparseSrc;
		pDst+=stepSparseDst;
	}
}*/

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
	/*
	if (CHECK_OVERFLOW())
	{
		vec<nmint<32> > Scalar(1);
		vec<nmint<32> > Src1(nSize);
		vec<nmint<32> > Src2(nSize);
		vec<nmint<32> > DstVec(nSize);
		Scalar[0]=MulN;
		Src1.SetData(pSrcVec1);
		Src2.SetData(pSrcVec2);
		DstVec=Src1*Scalar;
		DstVec+=Src2;
		Scalar[0]=AddN;
		DstVec+=Scalar;
		DstVec.GetData(pDstVec);
	}
	else
		for(int i=0;i<nSize;i++)
			pDstVec[i]=pSrcVec1[i]*MulN+pSrcVec2[i]+AddN;
			*/
	nmppsMulC_32s(pSrcVec1,MulN,pDstVec,nSize);
	nmppsAdd_32s(pDstVec,pSrcVec2,pDstVec,nSize);
	nmppsAddC_32s(pDstVec,AddN,pDstVec,nSize);
}
