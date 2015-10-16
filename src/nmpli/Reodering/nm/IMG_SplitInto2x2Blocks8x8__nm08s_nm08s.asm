//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r)  Software                            */
//*                                                                         */
//*   DCT Library                                                           */
//*   (C-callable functions)                                                */
//*                                                                         */
//*   $Workfile:: Block.asm                                                $*/
//*                                                                         */
//*   Contents:         Routines for computing the forward                  */
//*                     and inverse 2D DCT of an image                      */
//*                                                                         */
//*   Software design: S.Mushkaev                                           */
//*                                                                         */
//*                                                                         */
//***************************************************************************/


begin ".text_nmpli"

////////////////////////////////////////////////////////////////////////////
    //--------------------------------------------------------------------
    //! \fn void IMG_SplitInto2x2Blocks8x8(	nm8s*	Src, nm8s* Dst, int Width, int Height);
    //! 
	//! \perfinclude _IMG_SplitIntoBlocks8x8__FPcPcii.html
    //--------------------------------------------------------------------

//  int IMG_SplitInto2x2Blocks8x8(
//		    nm8s*	Src,	// Source Image						:long Local[Width*Height/8]
//			nm8s*	Dst,	// Result one-dimensional Array:	:long Global[Width*Heihgt/8]
//			int		Width,	// Source Image Width;				:Width =[8,16,24...]
//			int		Height	// Source Image Height;				:Height=[8,16,24...]
//			);
//
// DESCRIPTION:
//  Transforms image frame to the sequence of the 8x8 blocks. In order:
//  Source Image:
//  [A00|A01|A02|A03|A04|A05|A06|A07|B00|B01|..|B07|C00|....H07]
//  [A10|A11|A12|A13|A14|A15|A16|A17|B10|B11|..|B17|C10|....H17]
//  [A20|A21|A22|A23|A24|A25|A26|A27|B20|B21|..|B27|C20|....H27]
//  [A30|A31|A32|A33|A34|A35|A36|A37|B30|B31|..|B37|C30|....H37]
//  ............................................................
//  [A70|A71|A72|A73|A74|A75|A76|A77|B70|B71|..|B77|C70|....H77]
//  ............................................................
//  [I00|I01|I02|I03|I04|I05|I06|I07|J00|J01|..................]
//  [I10|I11|I12|I13|I14|I15|I16|I17|J00|I09|...................
//  ........................................................Z77]
// 
//  Result one-dimensional Array:
//  [A00|A01|A02|...|A06|A07|A20|A21|...|A77|B00|B01|B02|...|B07|B10|...|H77|
//  [I00|I01|I02|...|I06|I07]I10|I11|...|I77|J00|J01|J02|...............|Z77|
//  
//
//  RETURN: 0
//  


global _void._.8.8IMG_SplitInto2x2Blocks8x8.1unsigned._char._.0.9._unsigned._char._.0.9._int.9._int.2 :label;
      <_void._.8.8IMG_SplitInto2x2Blocks8x8.1unsigned._char._.0.9._unsigned._char._.0.9._int.9._int.2>
 
.branch;
	ar5=ar7-2;
	
	push ar0,gr0;
	push ar1,gr1;
	push ar2,gr2;
	push ar3,gr3;
	push ar4,gr4;
	push ar5,gr5;
	push ar6,gr6;
	
	ar0=[--ar5];		//SrcBuffer
	ar6=[--ar5];		//DstBuffer
	gr4=[--ar5];		//Width
	gr6=[--ar5];		//Height

	gr6>>=4;		// Height in macroblocks 
	gr0 = gr4>>2;	// Width in 32 bit words
	gr1 = gr0 ;		// Width in 32 bit words
	ar1 = ar0 ;		// 
	ar1+= 2;		// Odd  column
	gr5 = 4;		// Even column to even column step
	gr4>>=4;		// Width in macroblocks
	gr4--;
	<NextMacroblockRow>
		gr2 = ar0 with gr7=gr4;
		gr3 = ar1 with gr7--;
		
		rep 8 data=[ar0++gr0] with data ;
		rep 8 [ar6++]=afifo ;
		rep 8 data=[ar1++gr1] with data ;
		rep 8 [ar6++]=afifo ; 
		
		rep 8 data=[ar0++gr0] with data ;
		rep 8 [ar6++]=afifo ;
		rep 8 data=[ar1++gr1] with data ;
		rep 8 [ar6++]=afifo ; 

		push ar0,gr0 with gr2 += gr5 noflags ;
		push ar1,gr1 with gr3 += gr5 noflags ;
		
		ar0 = gr2  with gr2 += gr5 noflags ;
		ar1 = gr3  with gr3 += gr5 noflags ;

		<NextMacroblock>
			rep 8 data=[ar0++gr0] with data ;
			rep 8 [ar6++]=afifo ;
			rep 8 data=[ar1++gr1] with data ;
			rep 8 [ar6++]=afifo ; 
			
			rep 8 data=[ar0++gr0] with data ;
			rep 8 [ar6++]=afifo ;
			rep 8 data=[ar1++gr1] with data ;
			rep 8 [ar6++]=afifo ; 
		if <>0 delayed goto NextMacroblock with gr7--;
			ar0 = gr2 with gr2 += gr5 noflags ;
			ar1 = gr3 with gr3 += gr5 noflags ;
		
		with gr6--;
		
	if <>0 delayed goto NextMacroblockRow;
		pop ar1,gr1;
		pop ar0,gr0;

	pop ar6,gr6;
	pop ar5,gr5;
	pop ar4,gr4;
	pop ar3,gr3;
	pop ar2,gr2;
	pop ar1,gr1;
	pop ar0,gr0;
	
	
	
	
	
	

	
return ;
 
.wait;



end ".text_nmpli";
