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
#include "nmpp.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned nmppsCrcAcc_64f(
    const double * pSrcVec, // Input Vector			:long Any[Size/2]
	int numBitsToClear,
    int nSize,             // Vector size        	:[0,1,2...]
    unsigned int* crcAccumulator     // Init/Output crc
    )
       
{
	nm32u* pTable=CRC32_Table; 
    unsigned long long a,b;
	int i;

    
	long long mask=(0xFFFFFFFFFFFFFFFF)<<numBitsToClear;
	long long rounder=0;
	long long *p=(long long*)pSrcVec;
	if (numBitsToClear)
		rounder=1L<<(numBitsToClear-1);
    for( i = 0; i < nSize; i++ )
    {
		a = (p[i]+rounder)&mask;
        b = a & 0x000000FF;
        *crcAccumulator = ( *crcAccumulator >> 8 ) ^ pTable[( b ^ ( *crcAccumulator & 0x000000FF ) )];
        b = ( a >> 8 ) & 0x000000FF;
        *crcAccumulator = ( *crcAccumulator >> 8 ) ^ pTable[( b ^ ( *crcAccumulator & 0x000000FF ) )];
        b = ( a >> 16 ) & 0x000000FF;
        *crcAccumulator = ( *crcAccumulator >> 8 ) ^ pTable[( b ^ ( *crcAccumulator & 0x000000FF ) )];
        b = ( a >> 24 ) & 0x000000FF;
       
		*crcAccumulator = ( *crcAccumulator >> 8 ) ^ pTable[( b ^ ( *crcAccumulator & 0x000000FF ) )];
        b = ( a >> 32 ) & 0x000000FF;
        *crcAccumulator = ( *crcAccumulator >> 8 ) ^ pTable[( b ^ ( *crcAccumulator & 0x000000FF ) )];
        b = ( a >> 40 ) & 0x000000FF;
        *crcAccumulator = ( *crcAccumulator >> 8 ) ^ pTable[( b ^ ( *crcAccumulator & 0x000000FF ) )];
        b = ( a >> 48 ) & 0x000000FF;
		*crcAccumulator = ( *crcAccumulator >> 8 ) ^ pTable[( b ^ ( *crcAccumulator & 0x000000FF ) )];
        b = ( a >> 56 ) & 0x000000FF;
		*crcAccumulator = ( *crcAccumulator >> 8 ) ^ pTable[( b ^ ( *crcAccumulator & 0x000000FF ) )];
		
        
	}
    *crcAccumulator = ~ *crcAccumulator;
	return *crcAccumulator;
}



