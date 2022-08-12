//------------------------------------------------------------------------
//
//  $Workfile:: 32Clc.cp $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:16 $
//
//! \if file_doc
//!
//! \file   32Clc.cpp
//! \author Сергей Мушкаев
//! \brief  Функции подсчета циклического кода для векторов.
//!
//! \endif
//!
//------------------------------------------------------------------------
extern unsigned int CRC32_Table[];
//#include "vcrc.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned nmppsCrcAcc_32u(
    const unsigned int* pSrcVec, 	// Input Vector			:long Any[Size/2]
    int nSize,             			// Vector size        	:[0,1,2...]
    unsigned int* crcAccumulator    // Init/Output crc
    )
       
{
	unsigned * pTable=CRC32_Table; 
    unsigned a,b;
	int i;

    

    for( i = 0; i < nSize; i++ )
    {
		a = pSrcVec[i];
        b = a & 0x000000FF;
        *crcAccumulator = ( *crcAccumulator >> 8 ) ^ pTable[( b ^ ( *crcAccumulator & 0x000000FF ) )];
        b = ( a >> 8 ) & 0x000000FF;
        *crcAccumulator = ( *crcAccumulator >> 8 ) ^ pTable[( b ^ ( *crcAccumulator & 0x000000FF ) )];
        b = ( a >> 16 ) & 0x000000FF;
        *crcAccumulator = ( *crcAccumulator >> 8 ) ^ pTable[( b ^ ( *crcAccumulator & 0x000000FF ) )];
        b = ( a >> 24 ) & 0x000000FF;
        *crcAccumulator = ( *crcAccumulator >> 8 ) ^ pTable[( b ^ ( *crcAccumulator & 0x000000FF ) )];
    }
    *crcAccumulator = ~ *crcAccumulator;
	return *crcAccumulator;
}



