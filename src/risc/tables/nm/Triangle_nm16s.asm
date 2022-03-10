//-----------------------------------------------------------------------------
//
// $Workfile:: Triangle.asm                             $
//
// Vector processing library
//
// $Revision: 1.1 $        $Date: 2004/11/22 13:50:13 $
//
//! \if file_doc
//!
//! \file   Triangle.asm
//! \author Sergey Landyshev
//! \breif  masks table
//! 
//! \endif 
//!
//----------------------------------------------------------------------------


data ".data_nmplv_G"
	global _VEC_TBL_Triangle_nm16_G:	long[17] = (
    00000_0000_0000_0000hl,
    00001_0001_0001_0001hl, 
    00003_0003_0003_0003hl, 
    00007_0007_0007_0007hl, 
    0000f_000f_000f_000fhl, 
    0001f_001f_001f_001fhl, 
    0003f_003f_003f_003fhl, 
    0007f_007f_007f_007fhl, 
    000ff_00ff_00ff_00ffhl, 
    001ff_01ff_01ff_01ffhl, 
    003ff_03ff_03ff_03ffhl, 
    007ff_07ff_07ff_07ffhl, 
    00fff_0fff_0fff_0fffhl, 
    01fff_1fff_1fff_1fffhl, 
    03fff_3fff_3fff_3fffhl, 
    07fff_7fff_7fff_7fffhl, 
    0ffff_ffff_ffff_ffffhl);
    
    
  
	global _VEC_TBL_BackTriangle_nm16_G:long[17]=(
    00000_0000_0000_0000hl, 
    08000_8000_8000_8000hl, 
    0C000_C000_C000_C000hl, 
    0E000_E000_E000_E000hl, 
    0F000_F000_F000_F000hl, 
    0F800_F800_F800_F800hl, 
    0FC00_FC00_FC00_FC00hl, 
    0FE00_FE00_FE00_FE00hl, 
    0FF00_FF00_FF00_FF00hl, 
    0FF80_FF80_FF80_FF80hl, 
    0FFC0_FFC0_FFC0_FFC0hl, 
    0FFE0_FFE0_FFE0_FFE0hl, 
    0FFF0_FFF0_FFF0_FFF0hl, 
    0FFF8_FFF8_FFF8_FFF8hl, 
    0FFFC_FFFC_FFFC_FFFChl, 
    0FFFE_FFFE_FFFE_FFFEhl, 
    0FFFF_FFFF_FFFF_FFFFhl
    );
 
end ".data_nmplv_G";

data ".data_nmplv_L"
end ".data_nmplv_L";

