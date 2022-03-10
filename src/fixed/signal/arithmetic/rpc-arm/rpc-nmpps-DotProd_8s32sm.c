//------------------------------------------------------------------------
//
//  $Workfile:: Mul_VxxVxx.cp $
//
//  ��������-��������� ����������
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:15 $
//
//! \if file_doc
//!
//! \file   Mul_VxxVxx.cpp
//! \author ������ �������
//! \brief  ������� ��������� ��� ��������.
//!
//! \endif
//!
//------------------------------------------------------------------------
#include "rpc-host.h"
#include "nmtype.h"

int nmppsDotProd_8s32sm(
	const nm8s*		srcVec0,	//Input0 buffer		:long Local [Size].
	const nm32s*		srcVec1,	//Input1 buffer		:long Global[Size].
	int			size,		//Size of input vec
	nm64s*		dst,		//Output buffer		:long Any
	nm64s* 		tmp
	)
{
	struct aura_buffer *iobuf_src0 = aura_buffer_request(n, size*1);	
	struct aura_buffer *iobuf_src1 = aura_buffer_request(n, size*4);	
	memcpy(iobuf_src0->data,srcVec0,size*1);	
	memcpy(iobuf_src1->data,srcVec1,size*4);	
	struct aura_buffer *retbuf; 
	int ret = aura_call(n, "nmppsDotProd_8s32sm", &retbuf,  iobuf_src0,iobuf_src1, size); 
	if (ret != 0) {
		BUG(n, "Call nmppsDotProd_8s32sm failed!"); }
	*dst = aura_buffer_get_u64(retbuf);
	ret  = aura_buffer_get_u32(retbuf);
	aura_buffer_release( iobuf_src0); 
	aura_buffer_release( iobuf_src1); 
	aura_buffer_release( retbuf); 
	slog(3, SLOG_INFO, "ARM: Call nmppsDotProd_8s32sm -ok"); 
	return ret;
}
