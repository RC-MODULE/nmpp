//------------------------------------------------------------------------
//
//  $Workfile:: 32Ini.cp $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:16 $
//
//! \if file_doc
//!
//! \file   32Ini.cpp
//! \author Александр Рузавин
//! \brief  Функции подсчета циклического кода для векторов.
//!
//! \endif
//!
//------------------------------------------------------------------------

//#include "vcrc.h"
#include "nmpp.h"
const unsigned int CRC32POLY = 0xEDB88320;

void InitCRC32Table( nm32u* pT )
{
	int i, j;
	nm32u* p = pT;

	for( i = 0; i < 256; i++ )
	{
		* p = i;

		for( j = 7; j >= 0; j-- )
		{
			if( * p & 1 )
				* p = ( * p >> 1 ) ^ CRC32POLY;
			else
				* p = * p >> 1;
		}
		p++;
	}
}
