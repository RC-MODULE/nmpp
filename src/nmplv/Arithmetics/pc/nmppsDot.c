//------------------------------------------------------------------------
//
//  $Workfile:: Mul_VxxVxx.cp $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:15 $
//
//! \if file_doc
//!
//! \file   Mul_VxxVxx.cpp
//! \author Сергей Мушкаев
//! \brief  Функции умножения для векторов.
//!
//! \endif
//!
//------------------------------------------------------------------------

#include "rpc-host.h"
#include "nmpp.h"

/////////////////////////////////////////////////////////////////////////////////////////
// Scalar multiplication of two vectors
/*
int	nmppsDotProd_32s(
			nm32s*		pSrcVec1,		// input  32-bit vec		:long -----[Size/2]
			nm32s*		pSrcVec2,		// input  32-bit vec		:long -----[Size/2]
			int			nSize			// size of input buffers	:nSize=[0,2,4...]
		)
{
	#ifdef RPC
	RPC_PPI(pSrcVec,pDstVec,nSize);
	#else

	int Res=0;
	int i;
	for (i=0;i<nSize;i++)
		Res+=pSrcVec1[i]*pSrcVec2[i];
	return Res;

	//ippsDotProd_32s_Sfs(const Ipp32s* pSrc1, const Ipp32s*pSrc2, int len, Ipp32s* pDp, int scaleFactor);

	#endif
}
*/


//////////////////////////////////////////////////////////////////////////////////////
// Vector multiplication
//////////////////////////////////////////////////////////////////////////////////////
void nmppsDotProd_64s64s(
	nm64s*	srcVec0,	//Input0 buffer		:long Local [Size].
	nm64s*	srcVec1,	//Input1 buffer		:long Global[Size].
	int		size,		//Size of input vec
	int64b*	dst			//Output buffer		:long Any
	)
{
	#ifdef RPC
		struct aura_buffer *iobuf_src0 = aura_buffer_request(n, size*8);	
		struct aura_buffer *iobuf_src1 = aura_buffer_request(n, size*8);	
		memcpy(iobuf_src0->data,srcVec0,size*8);	
		memcpy(iobuf_src1->data,srcVec1,size*8);	
		struct aura_buffer *retbuf; 
		int ret = aura_call(n, "nmppsDotProd_64s64s", &retbuf,  iobuf_src0,iobuf_src1, size); 
		if (ret != 0) {
			printf ("bug = %d\r\n",ret);
			BUG(n, "Call nmppsDotProd_64s64s failed!"); }
		*dst = aura_buffer_get_u64(retbuf);
		aura_buffer_release( iobuf_src0); 
		aura_buffer_release( iobuf_src1); 
		aura_buffer_release( retbuf); 
		slog(0, SLOG_INFO, "ARM: Call nmppsDotProd_64s64s -ok");
	#else

		int i;
		*dst=0;
		for (i=0; i<size; i++)
			*dst += ((nm64s)srcVec0[i])*((nm64s)srcVec1[i]);

	#endif
}

//////////////////////////////////////////////////////////////////////////////////////
void nmppsDotProd_32s64s(
	nm32s*	srcVec0,	//Input0 buffer		:long Local [Size].
	nm64s*	srcVec1,	//Input1 buffer		:long Global[Size].
	int		size,		//Size of input vec
	int64b*	dst			//Output buffer		:long Any
	)
{
	#ifdef RPC
		struct aura_buffer *iobuf_src0 = aura_buffer_request(n, size*4);	
		struct aura_buffer *iobuf_src1 = aura_buffer_request(n, size*8);	
		memcpy(iobuf_src0->data,srcVec0,size*4);	
		memcpy(iobuf_src1->data,srcVec1,size*8);	
		struct aura_buffer *retbuf; 
		int ret = aura_call(n, "nmppsDotProd_32s64s", &retbuf,  iobuf_src0,iobuf_src1, size); 
		if (ret != 0) {
			printf ("bug = %d\r\n",ret);
			BUG(n, "Call nmppsDotProd_32s64s failed!"); }
		*dst = aura_buffer_get_u64(retbuf);
		aura_buffer_release( iobuf_src0); 
		aura_buffer_release( iobuf_src1); 
		aura_buffer_release( retbuf); 
		slog(0, SLOG_INFO, "ARM: Call nmppsDotProd_32s64s -ok");
	#else

	int i;
	*dst = 0;
	for (i=0; i<size; i++)
		*dst += ((nm64s)srcVec0[i])*((nm64s)srcVec1[i]);

	#endif
}

//////////////////////////////////////////////////////////////////////////////////////
void nmppsDotProd_16s64s(
	nm16s*	srcVec0,	//Input0 buffer		:long Local [Size].
	nm64s*	srcVec1,	//Input1 buffer		:long Global[Size].
	int		size,		//Size of input vec
	int64b*	dst			//Output buffer		:long Any
	)
{
	#ifdef RPC
		struct aura_buffer *iobuf_src0 = aura_buffer_request(n, size*2);	
		struct aura_buffer *iobuf_src1 = aura_buffer_request(n, size*8);	
		memcpy(iobuf_src0->data,srcVec0,size*2);	
		memcpy(iobuf_src1->data,srcVec1,size*8);	
		struct aura_buffer *retbuf; 
		int ret = aura_call(n, "nmppsDotProd_16s64s", &retbuf,  iobuf_src0,iobuf_src1, size); 
		if (ret != 0) {
			printf ("bug = %d\r\n",ret);
			BUG(n, "Call nmppsDotProd_16s64s failed!"); }
		*dst = aura_buffer_get_u64(retbuf);
		aura_buffer_release( iobuf_src0); 
		aura_buffer_release( iobuf_src1); 
		aura_buffer_release( retbuf); 
		slog(0, SLOG_INFO, "ARM: Call nmppsDotProd_16s64s -ok");
	#else
		int i;
		*dst = 0;
		for (i=0; i<size; i++)
			*dst += ((nm64s)srcVec0[i])*((nm64s)srcVec1[i]);

	#endif
}

//////////////////////////////////////////////////////////////////////////////////////
void nmppsDotProd_8s64s(
	nm8s*	srcVec0,	//Input0 buffer		:long Local [Size].
	nm64s*	srcVec1,	//Input1 buffer		:long Global[Size].
	int		size,		//Size of input vec
	int64b*	dst			//Output buffer		:long Any
	)
{
	#ifdef RPC
		struct aura_buffer *iobuf_src0 = aura_buffer_request(n, size*1);	
		struct aura_buffer *iobuf_src1 = aura_buffer_request(n, size*8);	
		memcpy(iobuf_src0->data,srcVec0,size*1);	
		memcpy(iobuf_src1->data,srcVec1,size*8);	
		struct aura_buffer *retbuf; 
		int ret = aura_call(n, "nmppsDotProd_8s64s", &retbuf,  iobuf_src0,iobuf_src1, size); 
		if (ret != 0) {
			printf ("bug = %d\r\n",ret);
			BUG(n, "Call nmppsDotProd_8s64s failed!"); }
		*dst = aura_buffer_get_u64(retbuf);
		aura_buffer_release( iobuf_src0); 
		aura_buffer_release( iobuf_src1); 
		aura_buffer_release( retbuf); 
		slog(0, SLOG_INFO, "ARM: Call nmppsDotProd_8s64s -ok");
	#else
	int i;
	*dst = 0;
	for (i=0; i<size; i++)
		*dst += ((nm64s)srcVec0[i])*((nm64s)srcVec1[i]);

	#endif
}

