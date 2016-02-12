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
#include "nmplv.h"
#include "malloc32.h"
#include "time.h"

//#include "nmplv/vArithmetics.h"
//#include "nmplv/vInit.h"


//////////////////////////////////////////////////////////////////////////////////////
void nmppsDotProd_16s32s(
	nm16s*		srcVec0,	//Input0 buffer		:long Local [Size].
	nm32s*		srcVec1,	//Input1 buffer		:long Global[Size].
	int			size,		//Size of input vec
	nm64s*		dst		//Output buffer		:long Any
	)
{
	#ifdef RPC
		struct aura_buffer *iobuf_src0 = aura_buffer_request(n, size*2);	
		struct aura_buffer *iobuf_src1 = aura_buffer_request(n, size*4);	
		memcpy(iobuf_src0->data,srcVec0,size*2);	
		memcpy(iobuf_src1->data,srcVec1,size*4);	
		struct aura_buffer *retbuf; 
		int ret = aura_call(n, "nmppsDotProd_16s32s", &retbuf,  iobuf_src0,iobuf_src1, size); 
		if (ret != 0) {
			printf ("bug = %d\r\n",ret);
			BUG(n, "Call nmppsDotProd_16s32s failed!"); }
		*dst = aura_buffer_get_u64(retbuf);
		aura_buffer_release(n, iobuf_src0); 
		aura_buffer_release(n, iobuf_src1); 
		aura_buffer_release(n, retbuf); 
		slog(0, SLOG_INFO, "ARM: Call nmppsDotProd_16s32s -ok"); 
	#else
		Tmp2BuffSpec s;
		Tmp2BuffSpec* spec=&s;
		spec->buffer0=nmppsMalloc_64s(size);
		if (nmppsMallocSuccess()){
			nmppsConvert_32s64s(srcVec1,(nm64s*)spec->buffer0,size);
			nmppsDotProd_16s64s (srcVec0,(nm64s*)spec->buffer0,size,dst);
		}
		nmppsFree(spec->buffer0);
	#endif
}
