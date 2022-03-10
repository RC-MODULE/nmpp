//------------------------------------------------------------------------
//
//  $Workfile:: 32Clc.cp $
//
//  ��������-��������� ����������
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:16 $
//
//! \if file_doc
//!
//! \file   32Clc.cpp
//! \author ������ �������
//! \brief  ������� �������� ������������ ���� ��� ��������.
//!
//! \endif
//!
//------------------------------------------------------------------------
extern unsigned int CRC32_Table[];
//#include "vcrc.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////

unsigned nmppsCrcAcc_32f(
    const float * pSrcVec, // Input Vector			:long Any[Size/2]
	int numBitsToClear,
    int nSize,             // Vector size        	:[0,1,2...]
    unsigned int* crcAccumulator     // Init/Output crc
    )
       
{
	unsigned* pTable=CRC32_Table; 
    unsigned a,b;
	int i;

    
	unsigned mask=-1<<numBitsToClear;
	unsigned rounder=0;
	unsigned *p=(unsigned*)pSrcVec;
	if (numBitsToClear)
		rounder=1<<(numBitsToClear-1);
    for( i = 0; i < nSize; i++ )
    {
		unsigned v=p[i];
		unsigned mantissa=v&0x7FFFFF;
		unsigned nearzero=(mantissa-rounder)&0x80000000;
		mask=mask&(~nearzero);
		a = (v+rounder)&mask;
		
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


