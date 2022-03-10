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
#include "nmtype.h"

void nmppsDotProd_16s64s(
	const nm16s*	srcVec0,	//Input0 buffer		:long Local [Size].
	const nm64s*	srcVec1,	//Input1 buffer		:long Global[Size].
	int		size,		//Size of input vec
	int64b*	dst			//Output buffer		:long Any
	)
{
	struct aura_buffer *iobuf_src0 = aura_buffer_request(n, size*2);	
	struct aura_buffer *iobuf_src1 = aura_buffer_request(n, size*8);	
	memcpy(iobuf_src0->data,srcVec0,size*2);	
	memcpy(iobuf_src1->data,srcVec1,size*8);	
	struct aura_buffer *retbuf; 
	int ret = aura_call(n, "nmppsDotProd_16s64s", &retbuf,  iobuf_src0,iobuf_src1, size); 
	if (ret != 0) {
		BUG(n, "Call nmppsDotProd_16s64s failed!"); }
	*dst = aura_buffer_get_u64(retbuf);
	aura_buffer_release( iobuf_src0); 
	aura_buffer_release( iobuf_src1); 
	aura_buffer_release( retbuf); 
	slog(3, SLOG_INFO, "ARM: Call nmppsDotProd_16s64s -ok");
}