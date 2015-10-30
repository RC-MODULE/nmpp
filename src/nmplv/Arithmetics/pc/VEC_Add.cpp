//------------------------------------------------------------------------
//
//  $Workfile:: Add.cpp    $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:15 $
//
//! \if file_doc
//!
//! \file   Remap.cpp
//! \author Сергей Мушкаев
//! \brief  Арифметические функции 
//!
//! \endif
//!
//------------------------------------------------------------------------

//#include "vec.h"
#include "nmplv.h"
//#include "nmtl.h"

/////////////////////////////////////////////////////////////////////////////////////////
// Summation of two char vectors
void nmppsAdd(
		nm8s*			pSrcVec1,		// input buffer		:long Local [VecSize/8]
		nm8s*			pSrcVec2,		// input buffer		:long Local [VecSize/8]
		nm8s*			pDstVec,			// output buffer	:long Global[VecSize/8]
		int				nSize			// size of input buffer in 8 bit elements. nSize=[0,8,16,24...]
		)
{
	//if (CHECK_OVERFLOW())
	//{
	//	nmvec8s SrcVecA(pSrcVec1,nSize);
	//	nmvec8s SrcVecB(pSrcVec2,nSize);
	//	nmvec8s DstVec(pDstVec,nSize);
	//	DstVec=SrcVecA+SrcVecB;
	//}
	//else
		for(int i=0; i<nSize; i++)
			pDstVec[i] = pSrcVec1[i] + pSrcVec2[i];
	// No IPPS analog
	// IppStatus ippsAdd_8u_Sfs(const Ipp8u* pSrc1, const Ipp8u* pSrc2,Ipp8u* pDst, int len, int scaleFactor);
	// IppStatus ippsAdd_8u_ISfs(const Ipp8u* pSrc, Ipp8u* pSrcDst,int len, int scaleFactor);
	// ???
}
/////////////////////////////////////////////////////////////////////////////////////////
// Summation of two short vectors
void nmppsAdd(
		nm16s*			pSrcVec1,		// input buffer		:long Local [VecSize/4]
		nm16s*			pSrcVec2,		// input buffer		:long Local [VecSize/4]
		nm16s*			pDstVec,			// output buffer	:long Global[VecSize/4]
		int				nSize			// size of input buffer in 16-bit elements. nSize=[0,4,8,12..]
		)
{
#ifndef USE_IPP
	//if (CHECK_OVERFLOW())
	//{
	//	nmvec16s SrcVecA(pSrcVec1,nSize);
	//	nmvec16s SrcVecB(pSrcVec2,nSize);
	//	nmvec16s DstVec(pDstVec,nSize);
	//	DstVec=SrcVecA+SrcVecB;
	//}
	//else
		for(int i=0; i<nSize; i++)
			pDstVec[i] = pSrcVec1[i] + pSrcVec2[i];
#else
	if (pSrcVec2==pDstVec)
		ippsAdd_16s_I(pSrcVec1,pSrcVec2,nSize);
	else
		if (pSrcVec1==pDstVec)
			ippsAdd_16s_I(pSrcVec2,pSrcVec1,nSize);
		else
			ippsAdd_16s(pSrcVec1,pSrcVec2,pDstVec,nSize);
#endif

}
/////////////////////////////////////////////////////////////////////////////////////////
// Summation of two int vectors
void nmppsAdd(
		nm32s*			pSrcVec1,		// input buffer		:long Local [VecSize/2]
		nm32s*			pSrcVec2,		// input buffer		:long Local [VecSize/2]
		nm32s*			pDstVec,			// output buffer	:long Global[VecSize/2]
		int				nSize			// size of input buffer in 32-bit elements. nSize=[0,2,4,6...]
		)
{
#ifndef USE_IPP
	//if (CHECK_OVERFLOW())
	//{
	//	nmvec32s SrcVecA(pSrcVec1,nSize);
	//	nmvec32s SrcVecB(pSrcVec2,nSize);
	//	nmvec32s DstVec(pDstVec,nSize);
	//	DstVec=SrcVecA+SrcVecB;
	//}
	//else
		for(int i=0; i<nSize; i++)
			pDstVec[i] = pSrcVec1[i] + pSrcVec2[i];
#else
	if (pSrcVec2==pDstVec)
		ippsAdd_32s_ISfs(pSrcVec1,pSrcVec2,nSize,0);
	else
		if (pSrcVec1==pDstVec)
			ippsAdd_32s_ISfs(pSrcVec2,pSrcVec1,nSize,0);
		else
			ippsAdd_32s_Sfs(pSrcVec1,pSrcVec2,pDstVec,nSize,0);
#endif

}
/////////////////////////////////////////////////////////////////////////////////////////
// Summation of two long vectors
void nmppsAdd(
		nm64s*		pSrcVec1,		// input buffer		:long Local [nSize]
		nm64s*		pSrcVec2,		// input buffer		:long Local [nSize]
		nm64s*		pDstVec,			// output buffer	:long Global[nSize]
		int				nSize			// size of input buffer in 64-bit elements. nSize=[0,1,2,3...]
		)
{
	//if (CHECK_OVERFLOW())
	//{
	//	nmvec64s SrcVecA(pSrcVec1,nSize);
	//	nmvec64s SrcVecB(pSrcVec2,nSize);
	//	nmvec64s DstVec(pDstVec,nSize);
	//	DstVec=SrcVecA+SrcVecB;
	//}
	//else
		for(int i=0; i<nSize; i++)
			pDstVec[i] = pSrcVec1[i] + pSrcVec2[i];
	
	// No IPPS analog
}

/////////////////////////////////////////////////////////////////////////////////////////
// Summation of two long complex vectors
void nmppsAdd(nm64sc *pSrcVec1, nm64sc *pSrcVec2, nm64sc *pDstVec, int nSize)
{
	int i;
	for(i=0;i<nSize;i++)
	{
		pDstVec[i].re = pSrcVec1[i].re + pSrcVec2[i].re;
		pDstVec[i].im = pSrcVec1[i].im + pSrcVec2[i].im;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////
// Multiple Summation of several arrays with accumulation of result
void nmppsSum4(
		nm16s**			Vectors,		// array of pointers to buffers	:nm8s*  Any  [NumberOfBuffer]
		nm16s*			pDstVec,		// result buffer				:long Local  [VecSize/4]
		int				nSize			// buffer size in 8-bit elements:nSize    =[256,512,..]
		)								// Buffer - char packed array	:long Global [VecSize/8]
{
	int i, j;
	for(i=0; i<nSize; i++)
	{
		pDstVec[i] = 0;
		for(j=0; j<4; j++)
			pDstVec[i] += (short)(Vectors[j][i]);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////
// Multiple Summation of several arrays with accumulation of result
void nmppsSumN(
		nm8s**			Vectors,		// array of pointers to buffers	:nm8s*  Any  [NumberOfBuffer]
		nm16s*			pDstVec,		// result buffer				:long Local  [VecSize/4]
		int				nSize,			// buffer size in 8-bit elements:nSize    =[256,512,..]
		int				VecNumber		// number of being added buffers:NumbersOfVectors=[2,3,4....]
		)								// Buffer - char packed array	:long Global [VecSize/8]
{
	int i, j;
	for(i=0; i<nSize; i++)
	{
		pDstVec[i] = 0;
		for(j=0; j<VecNumber; j++)
			pDstVec[i] += (short)(Vectors[j][i]);
	}
}
/////////////////////////////////////////////////////////////////////////////////////////
// Multiple Summation of several arrays with accumulation of result
// pDstVec[i]=Buffers[0][i]+Buffers[1][i]+...+Buffers[NumberOfBuffers-1][i]
void nmppsSumN(
		nm16s**			Vectors,		// array of pointers to buffers	:nm8s*  Any  [NumberOfBuffer]
		nm16s*			pDstVec,			// result buffer				:long Local  [VecSize/4]
		int				nSize,		// buffer size in 8-bit elements:nSize    =[***,..]
		int				VecNumber		// number of being added buffers:NumbersOfVectors=[2,3,4...256]
		)								// Buffer - char packed array	:long Global [VecSize/8]
{

	nmppsAdd(Vectors[0],Vectors[1],pDstVec,nSize);
	for(int i=2;i<VecNumber;i++)
		nmppsAdd(Vectors[i],pDstVec,pDstVec,nSize); // with IPP use
}



/////////////////////////////////////////////////////////////////////////////////////////
// Increment of vec elements by constant value
// pDstVec[i]=pSrcVec[i]+Increment
void nmppsAddC(
		nm8s*			pSrcVec,			// input buffer		:long Local [VecSize/8]
		int8b			nVal,				// increment		:Increment=[-128...+127]
		nm8s*			pDstVec,			// output buffer	:long Global[VecSize/8]
		int				nSize			// size of input buffer in 8 bit elements. nSize=[8,16,32...]
		)
{
	nVal=char(nVal);

	//if (CHECK_OVERFLOW())
	//{
	//	nmvec8s SrcVec(pSrcVec,nSize);
	//	nmint8s C(nVal);
	//	nmvec8s DstVec(pDstVec,nSize);
	//	for(int i=0; i<nSize; i++)
	//		DstVec[i] = SrcVec[i] + C;
	//}
	//else
		for(int i=0; i<nSize; i++)
			pDstVec[i] = pSrcVec[i] + nVal;
	// No IPPS analog
}

/////////////////////////////////////////////////////////////////////////////////////////
// Increment of vec elements by constant value
// pDstVec[i]=Increment+pSrcVec[i]
void nmppsAddC(
		nm16s*			pSrcVec,				// input buffer		:long Local [VecSize/4]
		int16b			nVal,					// increment		:
		nm16s*			pDstVec,				// output buffer	:long Global[VecSize/4]
		int				nSize				// size of input buffer in 16-bit elements. nSize=[0,4,8,12...]
		)
{
	nVal=short(nVal);
#ifndef USE_IPP
	//if (CHECK_OVERFLOW())
	//{
	//	nmvec16s SrcVec(pSrcVec,nSize);
	//	nmint16s C(nVal);
	//	nmvec16s DstVec(pDstVec,nSize);
	//	for(int i=0; i<nSize; i++)
	//		DstVec[i] = SrcVec[i] + C;
	//}
	//else
		for(int i=0; i<nSize; i++)
			pDstVec[i] = pSrcVec[i] + nVal;

#else
	if (pSrcVec==pDstVec)
		ippsAddC_16s_I(nVal, pSrcVec,nSize);
	else
		ippsAddC_16s_Sfs(pSrcVec,nVal, pDstVec,nSize,0);
#endif
}


/////////////////////////////////////////////////////////////////////////////////////////
// Increment of vec elements by constant value
// pDstVec[i]=pSrcVec[i]+Increment
void nmppsAddC(
		nm32s*			pSrcVec,			// input buffer		:long Local [VecSize/2]
		int				nVal,				// increment		:
		nm32s*			pDstVec,			// output buffer	:long Global[VecSize/2]
		int				nSize			// size of input buffer in 32-bit elements. nSize=[0,2,4,6...]
		)
{
#ifndef USE_IPP
	//if (CHECK_OVERFLOW())
	//{
	//	nmvec32s SrcVec(pSrcVec,nSize);
	//	nmint32s C(nVal);
	//	nmvec32s DstVec(pDstVec,nSize);
	//	for(int i=0; i<nSize; i++)
	//		DstVec[i] = SrcVec[i] + C;
	//}
	//else
		for(int i=0; i<nSize; i++)
			pDstVec[i] = pSrcVec[i] + nVal;
#else
	if (pSrcVec==pDstVec)
		ippsAddC_32s_ISfs(nVal, pSrcVec,nSize,0);
	else
		ippsAddC_32s_Sfs(pSrcVec,nVal, pDstVec,nSize,0);
#endif

}

/////////////////////////////////////////////////////////////////////////////////////////
// Summation of two int vectors with addition of constant
void nmppsAdd_AddC(
		nm32s*			SrcVecA,		// input buffer		:long Local [VecSize/2]
		nm32s*			SrcVecB,		// input buffer		:long Local [VecSize/2]
		int				nVal,				// additional constant
		nm32s*			pDstVec,			// output buffer	:long Global[VecSize/2]
		int				nSize			// size of input buffer in 32-bit elements. nSize=[0,2,4,6...]
		)
{
	/*if (CHECK_OVERFLOW())
	{
		vec<nmint<32> > SrcA(nSize);SrcA.SetData(SrcVecA);
		vec<nmint<32> > SrcB(nSize);SrcB.SetData(SrcVecB);
		vec<nmint<32> > DstVec (nSize);
		nmint<32>    C(nVal);
		DstVec=SrcA+SrcB+C;
		DstVec.GetData(pDstVec);
	}
	else{
	*/	
	nmppsAdd(SrcVecA,SrcVecB,pDstVec,nSize);
	nmppsAddC(pDstVec,nVal,pDstVec,nSize);
	//}

}

/////////////////////////////////////////////////////////////////////////////////////////
// Increment of vec elements by constant value
// pDstVec[i]=pSrcVec[i]+Increment
void nmppsAddC(
		nm32s*			pSrcVec,			// input buffer		:long Local [VecSize/8]
		int*			nVal,				// increment		:Increment=[-128...+127]
		nm32s*			pDstVec,			// output buffer	:long Global[VecSize/8]
		int				nSize			// size of input buffer in 8 bit elements. nSize=[8,16,32...]
		)
{
	nmppsAddC(pSrcVec,*nVal,pDstVec,nSize);
}

/////////////////////////////////////////////////////////////////////////////////////////
// Increment of vec elements by constant value
// pDstVec[i]=pSrcVec[i]+Increment
void nmppsAddC(
		nm64s*			pSrcVec,			// input buffer		:long Local [VecSize/8]
		nm64s*			nVal,				// increment		:Increment=[-128...+127]
		nm64s*			pDstVec,			// output buffer	:long Global[VecSize/8]
		int				nSize			// size of input buffer in 8 bit elements. nSize=[8,16,32...]
		)
{
	//if (CHECK_OVERFLOW())
	//{
	//	nmvec64s SrcVec(pSrcVec,nSize);
	//	nmint64s C(*nVal);
	//	nmvec64s DstVec(pDstVec,nSize);
	//	for(int i=0; i<nSize; i++)
	//		DstVec[i] = SrcVec[i] + C;
	//}
	//else
		for(int i=0; i<nSize; i++)
			pDstVec[i] = pSrcVec[i] + *nVal;
	// No IPPS analog
}

