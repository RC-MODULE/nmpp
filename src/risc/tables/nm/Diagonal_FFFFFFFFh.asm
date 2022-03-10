//-----------------------------------------------------------------------------
//
// $Workfile:: SadV16.asm                             $
//
// Vector processing library
//
// $Revision: 1.1 $        $Date: 2004/11/22 13:50:13 $
//
//! \if file_doc
//!
//! \file   SadV16.asm
//! \author Sergey Mushkaev
//! \breif  Weight table
//! 
//! \endif 
//!
//----------------------------------------------------------------------------


data ".data_nmplv_G"
	global _VEC_TBL_Diagonal_FFFFFFFFh_G:	long[2] = (
		000000000ffffffffhl,
		0ffffffff00000000hl);
end ".data_nmplv_G";

data ".data_nmplv_L"
	global _VEC_TBL_Diagonal_FFFFFFFFh_L:	long[2] = (
		000000000ffffffffhl,
		0ffffffff00000000hl);
end ".data_nmplv_L";

