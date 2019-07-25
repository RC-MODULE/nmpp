//------------------------------------------------------------------------
//
//  $Workfile:: Crc32.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:11 $
//
//! \if file_doc
//!
//! \file Crc32.asm
//! \author Сергей Мушкаев
//! \brief Подсчет избыточного кода
//! 
//! \endif
//!
//------------------------------------------------------------------------

 #include "nmpp.h"



extern "C"{
/////////////////////////////////////////////////////////////////////////////////////////////////////////

unsigned nmppmCrcAcc_32u(const unsigned int* pSrcVec, int height, int width, int stride, unsigned int* crc){
	for(int y=0; y<height; y++){
		nmppsCrcAcc_32u(pSrcVec,width,crc);
		pSrcVec+=stride;
	}
	return *crc;
}

unsigned nmppmCrc_32u(const unsigned int* pSrcVec, int height, int width, int stride){
	unsigned crc=0xCCCCCCCC;
	for(int y=0; y<height; y++){
		nmppsCrcAcc_32u(pSrcVec,width,&crc);
		pSrcVec+=stride;
	}
	return crc;
}

};