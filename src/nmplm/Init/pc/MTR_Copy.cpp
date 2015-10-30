#include "nmplv.h"


/////////////////////////////////////////////////////////////////////////////////
// Copying short submatrix from 64 bit odd position of source mtr
void MTR_Copy(
		nm16s*	SrcMtr,
			int		nSrcStride,
			nm16s*	DstMtr,
			int		nDstStride,
			int		nHeight,
			int		nWidth)


{
#ifdef USE_IPP
	IppiSize roiSize={nWidth,nHeight};
	ippiCopy_16s_C1R(SrcMtr,nSrcStride<<1,DstMtr,nDstStride<<1,roiSize);
#else
	for(int i=0;i<nHeight;i++)
	{
		nmppsCopy_16s(SrcMtr,DstMtr,nWidth);
		SrcMtr+=nSrcStride;
		DstMtr+=nDstStride;
	}
#endif

	
}

/////////////////////////////////////////////////////////////////////////////////
// Copying char submatrix from 64 bit odd position of source mtr
void MTR_Copy(
		nm8s*	SrcMtr,
			int		nSrcStride,
			nm8s*	DstMtr,
			int		nDstStride,
			int		nHeight,
			int		nWidth)

{
	for(int i=0;i<nHeight;i++)
	{
		nmppsCopy_8s(SrcMtr,DstMtr,nWidth);
		SrcMtr+=nSrcStride;
		DstMtr+=nDstStride;
	}
}
/////////////////////////////////////////////////////////////////////////////////
//*****************************************************************************//
//*****************************************************************************//
//*****************************************************************************//
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
// Copying int submatrix from 64 bit odd position of source mtr
void MTR_Copy(
		nm32s*	SrcMtr,
			int		nSrcStride,
			nm32s*	DstMtr,
			int		nDstStride,
			int		nHeight,
			int		nWidth)

{
	for(int i=0;i<nHeight;i++)
	{
		nmppsCopy_32s(SrcMtr,DstMtr,nWidth);
		SrcMtr+=nSrcStride;
		DstMtr+=nDstStride;
	}
}

/////////////////////////////////////////////////////////////////////////////////
// Copying long submatrix from 64 bit odd position of source mtr
void MTR_Copy(
		nm64s*	SrcMtr,
			int		nSrcStride,
			nm64s*	DstMtr,
			int		nDstStride,
			int		nHeight,
			int		nWidth)

{
	for(int i=0;i<nHeight;i++)
	{
		nmppsCopy_64s(SrcMtr,DstMtr,nWidth);
		SrcMtr+=nSrcStride;
		DstMtr+=nDstStride;
	}
}
/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
// Copying char submatrix from any position of source mtr
void MTR_Copyua(
		nm8s*	SrcMtr,
			int		nSrcStride,
			int		SrcDsp,
			nm8s*	DstMtr,
			int		nDstStride,
			int		nHeight,
			int		nWidth)

{
	for(int i=0;i<nHeight;i++)
	{
		nmppsCopy_8s(SrcMtr+SrcDsp,DstMtr,nWidth);
		SrcMtr+=nSrcStride;
		DstMtr+=nDstStride;
	}
}

/////////////////////////////////////////////////////////////////////////////////
// Copying short submatrix from any position of source mtr
void MTR_Copyua(
		nm16s*	SrcMtr,
			int		nSrcStride,
			int		SrcDsp,
			nm16s*	DstMtr,
			int		nDstStride,
			int		nHeight,
			int		nWidth)

{
	for(int i=0;i<nHeight;i++)
	{
		nmppsCopy_16s(SrcMtr+SrcDsp,DstMtr,nWidth);
		SrcMtr+=nSrcStride;
		DstMtr+=nDstStride;
	}
}


/////////////////////////////////////////////////////////////////////////////////
// Copying int submatrix from any position of source mtr
void MTR_Copyua(
		nm32s*	SrcMtr,
			int		nSrcStride,
			int		SrcDsp,
			nm32s*	DstMtr,
			int		nDstStride,
			int		nHeight,
			int		nWidth)

{
	for(int i=0;i<nHeight;i++)
	{
		nmppsCopy_32s(SrcMtr+SrcDsp,DstMtr,nWidth);
		SrcMtr+=nSrcStride;
		DstMtr+=nDstStride;
	}
}

/////////////////////////////////////////////////////////////////////////////////
//*****************************************************************************//
//*****************************************************************************//
//*****************************************************************************//
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
// Copying char submatrix from any position of source mtr
void MTR_Copyau(
		nm8s*	SrcMtr,
			int		nSrcStride,
			nm8s*	DstMtr,
			int		nDstStride,
			int		DstDsp,
			int		nHeight,
			int		nWidth)

{
	for(int i=0;i<nHeight;i++)
	{
		nmppsCopy_8s(SrcMtr,DstMtr+DstDsp,nWidth);
		SrcMtr+=nSrcStride;
		DstMtr+=nDstStride;
	}
}

/////////////////////////////////////////////////////////////////////////////////
// Copying short submatrix from any position of source mtr
void MTR_Copyau(
		nm16s*	SrcMtr,
			int		nSrcStride,
			nm16s*	DstMtr,
			int		nDstStride,
			int		DstDsp,
			int		nHeight,
			int		nWidth)

{
	for(int i=0;i<nHeight;i++)
	{
		nmppsCopy_16s(SrcMtr,DstMtr+DstDsp,nWidth);
		SrcMtr+=nSrcStride;
		DstMtr+=nDstStride;
	}
}


/////////////////////////////////////////////////////////////////////////////////
// Copying int submatrix from any position of source mtr
void MTR_Copyau(
		nm32s*	SrcMtr,
			int		nSrcStride,
			nm32s*	DstMtr,
			int		nDstStride,
			int		DstDsp,
			int		nHeight,
			int		nWidth)

{
	for(int i=0;i<nHeight;i++)
	{
		nmppsCopy_32s(SrcMtr,DstMtr+DstDsp,nWidth);
		SrcMtr+=nSrcStride;
		DstMtr+=nDstStride;
	}
}
