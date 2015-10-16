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
	global _VEC_TBL_MinusOne_G:	long =  0FFFFFFFFFFFFFFFFhl;
	global _VEC_TBL_Zero_G:	long = 		00000000000000000hl;
	global _VEC_TBL_One_G: long =		00000000000000001hl;
end ".data_nmplv_G";

data ".data_nmplv_L"
	global _VEC_TBL_MinusOne_L:	long =  0FFFFFFFFFFFFFFFFhl;
	global _VEC_TBL_Zero_L:	long = 		00000000000000000hl;
	global _VEC_TBL_One_L: long =		00000000000000001hl;
end ".data_nmplv_L";


