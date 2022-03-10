//------------------------------------------------------------------------
//
//  $Workfile:: iSupport_nm.cpp         $
//
//  <Название библиотеки>
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2005/02/10 12:36:38 $
//
//! \if file_doc
//!
//! \file   iMalloc_nm.cpp
//! \author Рыжов Дмитрий
//! \brief  Распределение памяти для матриц изображений.
//!
//! \endif
//!
//------------------------------------------------------------------------
#include "nmpp.h"




void nmppiFree(void* ptr) {
   
   	 nmppsFree(ptr);
}



void nmppiRelease(void* ptr) {
   
   	 nmppsFree(ptr);
}
