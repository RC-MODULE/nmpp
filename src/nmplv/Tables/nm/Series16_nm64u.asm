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
	global _VEC_TBL_NegSeries_nm64_G:	long[1] = (
	    0FFFFFFFFFFFFFFFFhl);
	global _VEC_TBL_Series16_nm64_G:	long[16] = (
		00000000000000000hl,
		00000000000000001hl,
		00000000000000002hl,
		00000000000000003hl,
		00000000000000004hl,
		00000000000000005hl,
		00000000000000006hl,
		00000000000000007hl,
		00000000000000008hl,
		00000000000000009hl,
		0000000000000000Ahl,
		0000000000000000Bhl,
		0000000000000000Chl,
		0000000000000000Dhl,
		0000000000000000Ehl,
		0000000000000000Fhl);
end ".data_nmplv_G";

data ".data_nmplv_L"
	global _VEC_TBL_NegSeries_nm64_L:	long[1] = (
	    0FFFFFFFFFFFFFFFFhl);
	global _VEC_TBL_Series16_nm64_L:	long[16] = (
		00000000000000000hl,
		00000000000000001hl,
		00000000000000002hl,
		00000000000000003hl,
		00000000000000004hl,
		00000000000000005hl,
		00000000000000006hl,
		00000000000000007hl,
		00000000000000008hl,
		00000000000000009hl,
		0000000000000000Ahl,
		0000000000000000Bhl,
		0000000000000000Chl,
		0000000000000000Dhl,
		0000000000000000Ehl,
		0000000000000000Fhl);
end ".data_nmplv_L";

