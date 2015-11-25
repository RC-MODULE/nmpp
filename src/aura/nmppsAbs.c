//------------------------------------------------------------------------
//
//  $Workfile:: Abs.cpp    $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:15 $
//
//! \if file_doc
//!
//! \file   Abs.cpp
//! \author Сергей Мушкаев
//! \brief  Арифметические функции 
//!
//! \endif
//!
//------------------------------------------------------------------------

#include <aura/aura.h>
#include <ion/ion.h>
#include "nmpp.h"
#include "memory.h"



struct aura_node *n;

void nmppsAbs_4s(
		nm4s*			pSrcVec,		// input buffer		:long Local [VecSize/8]
		nm4s*			pDstVec,		// output buffer	:long Global[VecSize/8]
		int				nSize		// size of input buffer in 8 bit elements. nSize=[8,16,32...]
		)
{
	int ret;
	int size = nSize;
    struct aura_buffer *iobuf_src = aura_buffer_request(n, size/2);
	struct aura_buffer *iobuf_dst = aura_buffer_request(n, size/2);
	memcpy(iobuf_src->data,pSrcVec,size/2);
	struct aura_buffer *retbuf; 
	ret = aura_call(n, "Abs_s4", &retbuf,  iobuf_src, iobuf_dst, size);
	if (ret != 0) 
	    BUG(n, "Call failed!");

	memcpy(pDstVec,iobuf_dst->data,size/2);
	
	aura_buffer_release(n, iobuf_dst);
	aura_buffer_release(n, iobuf_src);
	aura_buffer_release(n, retbuf);
	
	slog(0, SLOG_INFO, "ARM: TEST nmppsAbs_4s ok");
}

void nmppsAbs_8s(
		nm8s*			pSrcVec,		// input buffer		:long Local [VecSize/8]
		nm8s*			pDstVec,		// output buffer	:long Global[VecSize/8]
		int				nSize		// size of input buffer in 8 bit elements. nSize=[8,16,32...]
		)
{
	int ret;
	int size = nSize;
    struct aura_buffer *iobuf_src = aura_buffer_request(n, size);
	struct aura_buffer *iobuf_dst = aura_buffer_request(n, size);
	memcpy(iobuf_src->data,pSrcVec,size);
	struct aura_buffer *retbuf; 
	ret = aura_call(n, "Abs_s8", &retbuf,  iobuf_src, iobuf_dst, size);
	if (ret != 0) 
	    BUG(n, "Call failed!");

	memcpy(pDstVec,iobuf_dst->data,size);
	
	aura_buffer_release(n, iobuf_dst);
	aura_buffer_release(n, iobuf_src);
	aura_buffer_release(n, retbuf);
	
	slog(0, SLOG_INFO, "ARM: TEST nmppsAbs_8s ok");
}

void nmppsAbs_16s(
		nm16s*			pSrcVec,		// input buffer		:long Local [VecSize/4]
		nm16s*			pDstVec,		// output buffer	:long Global[VecSize/4]
		int				nSize		// size of input buffer in 8 bit elements. nSize=[0,4,8,..]
		)
{
	int ret;
	int size = nSize;
    struct aura_buffer *iobuf_src = aura_buffer_request(n, size*2);
	struct aura_buffer *iobuf_dst = aura_buffer_request(n, size*2);
	memcpy(iobuf_src->data,pSrcVec,size*2);
	struct aura_buffer *retbuf; 
	ret = aura_call(n, "rpc_Abs_s16", &retbuf,  iobuf_src, iobuf_dst, size);
	if (ret != 0) 
	    BUG(n, "Call failed!");

	memcpy(pDstVec,iobuf_dst->data,size*2);
	
	aura_buffer_release(n, iobuf_dst);
	aura_buffer_release(n, iobuf_src);
	aura_buffer_release(n, retbuf);

	slog(0, SLOG_INFO, "ARM: TEST nmppsAbs_16s ok");	
}


void nmppsAbs_32s(
		nm32s*			pSrcVec,		// input buffer		:long Local [VecSize/2]
		nm32s*			pDstVec,		// output buffer	:long Global[VecSize/2]
		int				nSize		// size of input buffer in 32 bit elements. nSize=[2,4,6...]
		)
{
	int ret;
	int size = nSize;
    struct aura_buffer *iobuf_src = aura_buffer_request(n, size*4);
	struct aura_buffer *iobuf_dst = aura_buffer_request(n, size*4);
	memcpy(iobuf_src->data,pSrcVec,size*4);
	struct aura_buffer *retbuf; 
	ret = aura_call(n, "rpc_Abs_s32", &retbuf,  iobuf_src, iobuf_dst, size);
	if (ret != 0) 
	    BUG(n, "Call failed!");

	memcpy(pDstVec,iobuf_dst->data,size*4);
	
	aura_buffer_release(n, iobuf_dst);
	aura_buffer_release(n, iobuf_src);
	aura_buffer_release(n, retbuf);
	
	slog(0, SLOG_INFO, "ARM: TEST nmppsAbs_32s ok");
}


void nmppsAbs_64s(
		nm64s*			pSrcVec,		// input buffer		:long Local [VecSize/2]
		nm64s*			pDstVec,		// output buffer	:long Global[VecSize/2]
		int				nSize		// size of input buffer in 32 bit elements. nSize=[2,4,6...]
		)
{
	int ret;
	int size = nSize;
    struct aura_buffer *iobuf_src = aura_buffer_request(n, size*8);
	struct aura_buffer *iobuf_dst = aura_buffer_request(n, size*8);
	memcpy(iobuf_src->data,pSrcVec,size*8);
	struct aura_buffer *retbuf; 
	ret = aura_call(n, "rpc_Abs_s64", &retbuf,  iobuf_src, iobuf_dst, size);
	if (ret != 0) 
	    BUG(n, "Call failed!");

	memcpy(pDstVec,iobuf_dst->data,size*8);
	
	aura_buffer_release(n, iobuf_dst);
	aura_buffer_release(n, iobuf_src);
	aura_buffer_release(n, retbuf);
	
	slog(0, SLOG_INFO, "ARM: TEST nmppsAbs_64s ok");
}

