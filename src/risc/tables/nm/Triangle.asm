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
	global _VEC_TBL_Triangle_G:	long[66] = (
    00000000000000000hl, 00000000000000001hl, 00000000000000003hl, 00000000000000007hl, 
    0000000000000000fhl, 0000000000000001fhl, 0000000000000003fhl, 0000000000000007fhl, 
    000000000000000ffhl, 000000000000001ffhl, 000000000000003ffhl, 000000000000007ffhl, 
    00000000000000fffhl, 00000000000001fffhl, 00000000000003fffhl, 00000000000007fffhl, 
    0000000000000ffffhl, 0000000000001ffffhl, 0000000000003ffffhl, 0000000000007ffffhl, 
    000000000000fffffhl, 000000000001fffffhl, 000000000003fffffhl, 000000000007fffffhl, 
    00000000000ffffffhl, 00000000001ffffffhl, 00000000003ffffffhl, 00000000007ffffffhl, 
    0000000000fffffffhl, 0000000001fffffffhl, 0000000003fffffffhl, 0000000007fffffffhl, 
    000000000ffffffffhl, 000000001ffffffffhl, 000000003ffffffffhl, 000000007ffffffffhl,
    00000000fffffffffhl, 00000001fffffffffhl, 00000003fffffffffhl, 00000007fffffffffhl,
    0000000ffffffffffhl, 0000001ffffffffffhl, 0000003ffffffffffhl, 0000007ffffffffffhl,
    000000fffffffffffhl, 000001fffffffffffhl, 000003fffffffffffhl, 000007fffffffffffhl,
    00000ffffffffffffhl, 00001ffffffffffffhl, 00003ffffffffffffhl, 00007ffffffffffffhl, 
    0000fffffffffffffhl, 0001fffffffffffffhl, 0003fffffffffffffhl, 0007fffffffffffffhl, 
    000ffffffffffffffhl, 001ffffffffffffffhl, 003ffffffffffffffhl, 007ffffffffffffffhl,
    00fffffffffffffffhl, 01fffffffffffffffhl, 03fffffffffffffffhl, 07fffffffffffffffhl, 
    0ffffffffffffffffhl, 00000000000000000hl
    );
end ".data_nmplv_G";

data ".data_nmplv_L"
	global _VEC_TBL_Triangle_L:	long[66] = (
    00000000000000000hl, 00000000000000001hl, 00000000000000003hl, 00000000000000007hl, 
    0000000000000000fhl, 0000000000000001fhl, 0000000000000003fhl, 0000000000000007fhl, 
    000000000000000ffhl, 000000000000001ffhl, 000000000000003ffhl, 000000000000007ffhl, 
    00000000000000fffhl, 00000000000001fffhl, 00000000000003fffhl, 00000000000007fffhl, 
    0000000000000ffffhl, 0000000000001ffffhl, 0000000000003ffffhl, 0000000000007ffffhl, 
    000000000000fffffhl, 000000000001fffffhl, 000000000003fffffhl, 000000000007fffffhl, 
    00000000000ffffffhl, 00000000001ffffffhl, 00000000003ffffffhl, 00000000007ffffffhl, 
    0000000000fffffffhl, 0000000001fffffffhl, 0000000003fffffffhl, 0000000007fffffffhl, 
    000000000ffffffffhl, 000000001ffffffffhl, 000000003ffffffffhl, 000000007ffffffffhl,
    00000000fffffffffhl, 00000001fffffffffhl, 00000003fffffffffhl, 00000007fffffffffhl,
    0000000ffffffffffhl, 0000001ffffffffffhl, 0000003ffffffffffhl, 0000007ffffffffffhl,
    000000fffffffffffhl, 000001fffffffffffhl, 000003fffffffffffhl, 000007fffffffffffhl,
    00000ffffffffffffhl, 00001ffffffffffffhl, 00003ffffffffffffhl, 00007ffffffffffffhl, 
    0000fffffffffffffhl, 0001fffffffffffffhl, 0003fffffffffffffhl, 0007fffffffffffffhl, 
    000ffffffffffffffhl, 001ffffffffffffffhl, 003ffffffffffffffhl, 007ffffffffffffffhl,
    00fffffffffffffffhl, 01fffffffffffffffhl, 03fffffffffffffffhl, 07fffffffffffffffhl, 
    0ffffffffffffffffhl, 00000000000000000hl
    );
end ".data_nmplv_L";

