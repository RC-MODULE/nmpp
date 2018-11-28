//------------------------------------------------------------------------
//
//  $Workfile:: pcCompare.cp $
//
//  ��������-��������� ����������
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:15 $
//
//! \if file_doc
//!
//! \file   pcCompare.cpp
//! \author ������ �������
//! \brief  ������� ���������.
//!
//! \endif
//!
//------------------------------------------------------------------------
#include "nmplv.h"
void nmppsCmpGteC_v2nm32f(const v2nm32f* pSrcVec, nm1* evenFlags, nm1* oddFlags, const v2nm32f C, int step, int nSize)
{
  int i;
  int offset = 0;
  if (step == 1) {
    step = 0;
  }
//  step <<= 1;
  for(i = 0; i < nSize; i++) {
    if(pSrcVec[i + offset].v0 - C.v0 >= 0.0f) {
      nmppsPut_1(evenFlags, i, 1);
    }
    else {
      nmppsPut_1(evenFlags, i, 0);
    }

    if(pSrcVec[i + offset].v1 - C.v1 >= 0) {
      nmppsPut_1(oddFlags, i, 1);
    }
    else {
       nmppsPut_1(oddFlags, i, 0);
    }
    offset += step;
  }
}

void nmppsCmpLteC_v2nm32f(const v2nm32f* pSrcVec, nm1* evenFlags, nm1* oddFlags, const v2nm32f C, int step, int nSize)
{
  int i;
  int offset = 0;
  if (step == 1) {
    step = 0;
  }
//  step <<= 1;
  for(i = 0; i < nSize; i++) {
    if(pSrcVec[i + offset].v0 - C.v0 <= 0.0f) {
      nmppsPut_1(evenFlags, i, 1);
    }
    else {
      nmppsPut_1(evenFlags, i, 0);
    }

    if(pSrcVec[i + offset].v1 - C.v1 >= 0.0f) {
      nmppsPut_1(oddFlags, i, 1);
    }
    else {
       nmppsPut_1(oddFlags, i, 0);
    }
    offset += step;
  }
}


//******************************************************************************
//	Logical conversion from 32-bit buffer to 1-bit(binary) buffer by
//	setting of resulting bit to "1" if corresponding 32-bit input element is positive
//  and to "0" for each zero element and vice versa if nTrueFlag =-1
//	For negative numbers result is not defined.
void nmppsCmpEq0_32u31b(
			nm32u31b*	pSrcVec,				//Input buffer.	:Local[size].
			nm1*	pDstVec,				//Bit vectors.	:Global[size/32].
			int		nSize,					//Input buffer size in 32-bit elements. nSize = 2..nSize*2.
			int		nTrueFlag				//if invFlab == -1 (0xffffffff) then result is invert.
			)
{
	#ifdef RPC
	//RPC_HOST_PPI(nmppsAbs1_4s,pSrcVec,pDstVec,nSize);
	#else

    nm32s* src = (nm32s*)pSrcVec;
	nm32u* dst = (nm32u*)pDstVec;
	int i, j, k, s, rem;
	nTrueFlag&=1;
	nTrueFlag-=1;

	s = nSize >> 5;
	rem = nSize & 0x1f;

	for(i=0; i<s; i++)
	{
		dst[i] = 0;
		k = 1;
		for(j=0; j<32; j++)
		{
			if(src[i*32+j])
				dst[i] |= k;
			k <<= 1;
		}
		dst[i] ^= nTrueFlag;
	}
	if(rem)
	{
		dst[i] = 0;
		k = 1;
		for(j=0; j<rem; j++)
		{
			if(src[i*32+j])
				dst[i] |= k;
			k <<= 1;
		}
		dst[i] ^= nTrueFlag;
	}

	#endif
}
//******************************************************************************
//	Logical conversion from 16-bit buffer to 1-bit(binary) buffer by
//	setting of resulting bit to "1" if corresponding 32-bit input element is positive
//  and to "0" for each zero element and vice versa if nTrueFlag =-1
//	For negative numbers result is not defined.
void nmppsCmpEq0_16u15b(
			nm16u15b*	pSrcVec,				//Input buffer.	:Local[size].
			nm1*	pDstVec,				//Bit vectors.	:Global[size/32].
			int		nSize,					//Input buffer size in 16-bit elements. nSize = 4..nSize*4.
			int		nTrueFlag				//if invFlab == -1 (0xffffffff) then result is invert.
			)
{
	#ifdef RPC
	//RPC_HOST_PPI(nmppsAbs1_4s,pSrcVec,pDstVec,nSize);
	#else

    nm16s* src = (nm16s*)pSrcVec;
	nm32u* dst = (nm32u*)pDstVec;
	int i, j, k, s, rem;
	nTrueFlag&=1;
	nTrueFlag-=1;

	s = nSize >> 5;
	rem = nSize & 0x1f;
	for(i=0; i<s; i++)
	{
		dst[i] = 0;
		k = 1;
		for(j=0; j<32; j++)
		{
			if(src[i*32+j])
				dst[i] |= k;
			k <<= 1;
		}
		dst[i] ^= nTrueFlag;
	}
	if(rem)
	{
		dst[i] = 0;
		k = 1;
		for(j=0; j<rem; j++)
		{
			if(src[i*32+j])
				dst[i] |= k;
			k <<= 1;
		}
		dst[i] ^= nTrueFlag;
	}

	#endif
}
//******************************************************************************
//	Logical conversion from 8-bit buffer to 1-bit(binary) buffer by
//	setting of resulting bit to "1" if corresponding 32-bit input element is positive
//  and to "0" for each zero element and vice versa if nTrueFlag =-1
//	For negative numbers result is not defined.
void nmppsCmpEq0_8u7b(
			nm8u7b*	pSrcVec,				//Input buffer.	:Local[size].
			nm1*	pDstVec,				//Bit vectors.	:Global[size/32].
			int		nSize,					//Input buffer size in 8-bit elements. nSize = 8..nSize*8.
			int		nTrueFlag				//if invFlab == -1 (0xffffffff) then result is invert.
			)
{
	#ifdef RPC
	//RPC_HOST_PPI(nmppsAbs1_4s,pSrcVec,pDstVec,nSize);
	#else

    nm8s* src = (nm8s*) pSrcVec;
	nm32u* dst = (nm32u*)pDstVec;
	int i, j, k, s, rem;

	nTrueFlag&=1;
	nTrueFlag-=1;

	s = nSize >> 5;
	rem = nSize & 0x1f;
	for(i=0; i<s; i++)
	{
		dst[i] = 0;
		k = 1;
		for(j=0; j<32; j++)
		{
			if(src[i*32+j])
				dst[i] |= k;
			k <<= 1;
		}
		dst[i] ^= nTrueFlag;
	}
	if(rem)
	{
		dst[i] = 0;
		k = 1;
		for(j=0; j<rem; j++)
		{
			if(src[i*32+j])
				dst[i] |= k;
			k <<= 1;
		}
		dst[i] ^= nTrueFlag;
	}

	#endif
}
