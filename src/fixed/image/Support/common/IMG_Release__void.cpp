//------------------------------------------------------------------------
//
//  $Workfile:: iSupport_nm.cpp         $
//
//  <�������� ����������>
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2005/02/10 12:36:38 $
//
//! \if file_doc
//!
//! \file   iMalloc_nm.cpp
//! \author ����� �������
//! \brief  ������������� ������ ��� ������ �����������.
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
