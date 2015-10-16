//------------------------------------------------------------------------
//
//  $Workfile:: Resample3div2_8s1      $
//
//  Библиотека обработки сигналов
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2005/02/10 12:36:40 $
//
//! \if file_doc
//!
//! \file   
//! \author Сергей Мушкаев
//! \brief  Функции передескритизации изображения по вертикали в 3/2 раза
//!
//! \endif
//!
//------------------------------------------------------------------------

//#include "vArithm.h"
import from macros;
data ".data_nmpli_G"

VResample3div2Banks_Ram:  long[1*12]=(
0F91933F7_02000000hl,
000400000_00000000hl,
03319F902_00000000hl,
033F70200_00000000hl,
000000000_00000000hl,
0F9020000_00000000hl,
002000000_00000000hl,
000000000_00000000hl,
000000000_00000000hl,
000000000_00000000hl,
000000000_00000000hl,
000000000_00000000hl
);
VResample3div2Banks_Data:  long[1*12]=(
000000000_00000002hl,
000000000_00000000hl,
000000000_000002F7hl,
000000000_0002F919hl,
000000000_00000040hl,
000000000_02F73319hl,
000000002_F91933F7hl,
000000000_00400000hl,
0000002F7_3319F902hl,
00002F919_33F70200hl,
000000040_00000000hl,
002F73319_F9020000hl
);



end ".data_nmpli_G";

extern vec_Mul2D2W8_AddVr:label;
begin ".text_nmpli"


//! \fn void IMG_VResample3div2_Arsh0(nm16s* pSrcImg, int nWidth, int nHeight, nm16s* pDstImg);
//!
//! \n
//! \perfinclude _IMG_VResample3div2_Arsh0__FPSsiiPSs.html

//
global _IMG_VResample3div2_Arsh0__FPSsiiPSs:label;
global _void._.8.8IMG_VResample3div2_Arsh0.1short._.0.9._int.9._int.9._short._.0.2 :label;
<_IMG_VResample3div2_Arsh0__FPSsiiPSs>
<_void._.8.8IMG_VResample3div2_Arsh0.1short._.0.9._int.9._int.9._short._.0.2>
.branch;
	ar5 = sp - 2;
	
	push ar0,gr0;
	push ar1,gr1;
	push ar2,gr2;
	push ar3,gr3;
	push ar4,gr4;
	push ar5,gr5;
	push ar6,gr6;

	ar0 = [--ar5];	// nm16s* pSrcImg
	gr1 = [--ar5];	// int    nWidth
	gr5 = [--ar5];	// int	  nHeight
	ar6 = [--ar5];	// nm16s* pDstImg

	gr2 = gr1>>2;	// Width in nm64s
	gr0 = gr1>>1;	// Width in nm32s
	gr6 = gr0;

	//gr0=-gr0;
	//ar0+=gr0;
	//ar0+=gr0;
	//ar0+=gr0;
	//ar0+=gr0;
	//gr0=-gr0;

	gr0<<=3;		// Displacent upward by 8 rows;
	gr0 =-gr0;
	ar0+= gr0;
	gr0 = gr6;
	
//	gr6 =-gr6;
//	ar6+= gr6;
//	ar6+= gr6;
//	ar6+= gr6;
//	ar6+= gr6;
//	gr6 =-gr6;

	gr4 = 80008000h;
	sb  = 02020202h;
	nb1 = gr4;

	ar1 = VResample3div2Banks_Ram;
	gr1 = VResample3div2Banks_Data;
	rep 12 ram=[ar1++];
	ar5 = gr1;

	rep 8 wfifo= [ar0++gr0],ftw;
	WTW_REG(gr4);
	<NextColumn>
		push ar0,gr0 with gr7 = gr5>>3; //Height in blocks of 8 rows
		push ar6,gr6 with gr7--;

		rep 8 wfifo = [ar0++gr0],ftw;
		<NextBlock8>
			rep 12 with vsum ,ram,0;
			WTW_REG(gr4);
			rep 8 wfifo = [ar0++gr0],ftw;
			rep 12 data= [ar5++] with vsum ,data,afifo;
		if <>0 delayed goto NextBlock8 with gr7--;
			ar5 = gr1;
			rep 12 [ar6++gr6]=afifo;


		pop ar6,gr6;
		pop ar0,gr0	with gr2--;
		ar6+=2;
		ar0+=2;
	if <>0 delayed goto NextColumn;
		WTW_REG(gr4);
		

		
	pop ar6,gr6;
	pop ar5,gr5;
	pop ar4,gr4;
	pop ar3,gr3;
	pop ar2,gr2;
	pop ar1,gr1;
	pop ar0,gr0;
return;
.wait;





end ".text_nmpli";
