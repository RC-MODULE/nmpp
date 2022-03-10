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
	global _VEC_TBL_Diagonal_FFh_G:	long[8]= (
		000000000000000ffhl,
		0000000000000ff00hl,
		00000000000ff0000hl,
		000000000ff000000hl,
		0000000ff00000000hl,
		00000ff0000000000hl,
		000ff000000000000hl,
		0ff00000000000000hl);
end ".data_nmplv_G";

data ".data_nmplv_L"
	global _VEC_TBL_Diagonal_FFh_L:	long[8]= (
		000000000000000ffhl,
		0000000000000ff00hl,
		00000000000ff0000hl,
		000000000ff000000hl,
		0000000ff00000000hl,
		00000ff0000000000hl,
		000ff000000000000hl,
		0ff00000000000000hl);
end ".data_nmplv_L";

