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
	global _VEC_TBL_NB_Split_nm16s:	long[16] = (
			08000_8000_8000_8000h,// nb [ 16  ]  sh0  
			0c000_c000_c000_c000h,// nb [1 |15]  sh1  
			0a000_a000_a000_a000h,// nb [2 |14]  sh2	 
			09000_9000_9000_9000h,// nb [3 |13]  sh3	 
			08800_8800_8800_8800h,// nb [4 |12]  sh4  
			08400_8400_8400_8400h,// nb [5 |11]  sh5  
			08200_8200_8200_8200h,// nb [6 |10]  sh6  
			08100_8100_8100_8100h,// nb [7 |9 ]  sh7  
			08080_8080_8080_8080h,// nb [8 |8 ]  sh8  
			08040_8040_8040_8040h,// nb [9 |7 ]  sh9  
			08020_8020_8020_8020h,// nb [10|6 ]  sh10 
			08010_8010_8010_8010h,// nb [11|5 ]  sh11 
			08008_8008_8008_8008h,// nb [12|4 ]  sh12 
			08004_8004_8004_8004h,// nb [13|3 ]  sh13 
			08002_8002_8002_8002h,// nb [14|2 ]  sh14 
			08001_8001_8001_8001h // nb [15|1 ]  sh15 
		);
		
		
	global _VEC_TBL_SB_Split_nm16s:	long[8] = (
			00002_0002_0002_0002h,// sb [ 16  ]  sh0     
			0000a_000a_000a_000ah,// sb [14|2 ]  sh2
			00022_0022_0022_0022h,// sb [12|4 ]  sh4 
			00082_0082_0082_0082h,// sb [10|6 ]  sh6 
			00202_0202_0202_0202h,// sb [8 |8 ]  sh8 
			00802_0802_0802_0802h,// sb [6 |10]  sh10
			02002_2002_2002_2002h,// sb [4 |12]  sh12
			08002_8002_8002_8002h // sb [2 |14]  sh14
		);
		
end ".data_nmplv_G";
        
data ".data_nmplv_L"
end ".data_nmplv_L";
        
        
        
        