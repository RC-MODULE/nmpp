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
#include "nmplv.h"




void IMG_Free(void* ptr) {
   
   	 nmppsFree(ptr);
}



void IMG_Release(void* ptr) {
   
   	 nmppsFree(ptr);
}
