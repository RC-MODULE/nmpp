//------------------------------------------------------------------------
//
//  $Workfile:: FilterCoreRow02.asm             $
//
//  <Название библиотеки>
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.3 $      $Date: 2005/01/21 19:22:37 $
//
//! \if file_doc
//!
//! \file   FilterCoreRow02.asm
//! \author S. Mushkaev
//! \brief  <Краткое описание>
//!
//! \endif
//!
//------------------------------------------------------------------------




begin ".text_nmvcore"

import from minrep.mlb;
DEF_MIN_REP();

macro FilterN(N)
.if (NMPP_MIN_REP <= N);
	own Next_Block:label;
	// <First_Block>
	rep N data=[ar0++gr0] with vsum ,activate data, vr;
	nul;
	<Next_Block>
		gr2 = [ar1++] with gr1--;	// Read next disp
		ar0 = ar2 + gr2;			// Set next pointer

		wtw;
		nul;
	if > delayed goto Next_Block;
		rep N data=[ar0++gr0] with vsum ,activate data,afifo;
		rep 8 wfifo=[ar4++],ftw;

	//<Last_Block>
	gr2 = [ar1++];					// Read last disp
	ar0 = ar2 + gr2;				// Set last pointer, Dec packet counter
	delayed return;
		wtw;
		rep N data=[ar0++gr0] with vsum ,activate data,afifo;
		rep N [ar6++gr6]=afifo;		// Output result
.endif;
end FilterN;

/////////////////////////////////////////////////////////////////////////////////////////
// Core Weight summation of several vectors
/////////////////////////////////////////////////////////////////////////////////////////
//		ar0			First Input Buffer		
//		gr0			Input Buffer Stride for ar0		
//		ar1			Array of displacements from First Input Buffer
//		gr1			Number input buffers (must 3 or grater)
//		ar4			WeightBuffer				
//		gr4			nb1							
//		gr5			Input buffer size in longs
//		ar6			Ouput Buffer
//		gr6			Output Buffer Stride	
//		nb1	
//		sb
//		vr
//		f1cr
/////////////////////////////////////////////////////////////////////////////////////////

#define AR_1 ar5
#define AR_2 gr5
#define AR_4 ar3
#define GR_1 gr3

    //------------------------------------------------------------------------
    //! \fn void vec_ClipMulNDNW8_AddVr(nmreg nb1, nmreg sb, nmreg f1cr, nmreg vr, nmreg ar0, nmreg gr0, nmreg ar1, nmreg gr1, nmreg ar4, nmreg gr4, nmreg gr5, nmreg ar6, nmreg gr6);
    //!			 
    //------------------------------------------------------------------------

global vec_ClipMulNDNW8_AddVr:label;
<vec_ClipMulNDNW8_AddVr>
.branch;

	push ar5,gr5;
	ar3 = ar4 with					// Store pointer to weight array  
	gr7 = gr5>>5;					// Count of blocks by rep 32
	rep 8 wfifo=[ar4++],ftw;		// preload matrix for First_vsum

	ar5 = ar1 with					// Store pointer to array of displacemts
	gr3 = gr1 noflags;				// Store number of arrays
	gr5 = ar0;						// Anchor pointer
//	ar1 = ar5;						// Restore pointer to array of displacemts
//	gr1 = gr3;						// Restore number of arrays
	gr2 = [ar1++]   with gr1-- noflags;	// Read first disp   , Dec number of arrays
	ar2 = gr5;						// Restore anchor pointer
	ar0 = ar2 + gr2 with gr1-- noflags;	// Set  first pointer, Dec number of arrays
	wtw;
	with gr7;
	if =0 delayed goto Rep_N;
		rep 8 wfifo=[ar4++],ftw;		// Preload matrix for Next_vsum
		nul;
	<Next_Packet>
		// <First_Block>
		rep 32 data=[ar0++gr0] with vsum ,activate data, vr;
		gr5 = ar0;						// Store last position to anchor pointer
		gr5-= gr2;						// Correct new anchor pointer
		<Next_Block>
			gr2 = [ar1++] with gr1--;	// Read next disp
			ar0 = ar2 + gr2;			// Set next pointer
			wtw;
			nul;
		if > delayed goto Next_Block;
			rep 32 data=[ar0++gr0] with vsum ,activate data,afifo;
			rep 8 wfifo=[ar4++],ftw;

		//<Last_Block>
		ar4 = ar3;						// Restore pointer to weight array  
		gr2 = [ar1++];					// Read last disp
		ar0 = ar2 + gr2 with gr7--;		// Set last pointer, Dec packet counter
		wtw;
		rep 32 data=[ar0++gr0] with vsum ,activate data,afifo;
		rep 8 wfifo=[ar4++],ftw;		// Preload matrix for First_Block
		//<First_Block>
		ar1 = ar5;						// Restore pointer to array of displacemts
		ar2 = gr5 with					// Restore anchor pointer
		gr1 = gr3 noflags;				// Restore number of arrays
		gr2 = [ar1++]   with gr1-- noflags;		// Read first disp   , Dec number of arrays
		ar0 = ar2 + gr2 with gr1-- noflags;		// Set  first pointer, Dec number of arrays
		wtw;
	if > delayed goto Next_Packet;
		rep 8 wfifo=[ar4++],ftw;		// Preload matrix for Next_Block
		rep 32 [ar6++gr6]=afifo;		// Output result


	<Rep_N>
local Start:label;
	pop ar5,gr5;	// restore size
	gr3 = gr5<<32-5;
	ar3 = Start with
	///gr3>>=32-10;
	gr3>>=32-10+1;
	ar3 += gr3;
	if >= delayed goto ar3;
		nul;
		nul;
<Start>
	delayed return;
		wtw;
		nul;
		nul;
	///.repeat 28;
	.repeat 12;
		nul;
	.endrepeat;

	FilterN(1);
	FilterN(2);
	FilterN(3);
	FilterN(4);
	FilterN(5);
	FilterN(6);
	FilterN(7);
	FilterN(8);
	FilterN(9);
	FilterN(10);
	FilterN(11);
	FilterN(12);
	FilterN(13);
	FilterN(14);
	FilterN(15);
	FilterN(16);
	FilterN(17);
	FilterN(18);
	FilterN(19);
	FilterN(20);
	FilterN(21);
	FilterN(22);
	FilterN(23);
	FilterN(24);
	FilterN(25);
	FilterN(26);
	FilterN(27);
	FilterN(28);
	FilterN(29);
	FilterN(30);
	FilterN(31);


.wait;
end ".text_nmvcore"; 
