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

//  int IMG_SplitInto2x2Blocks8x8xor(
//		    nm8u*	Src,	// Source Image						:long Src[Width*Height/8]
//			nm8u*	Dst,	// Result one-dimensional Array:	:long Dst[Width*Heihgt/8]
//			nm8u*	Xor,	// Result one-dimensional Array:	:long 
//			int		Width,	// Source Image Width				:Width =[32,48,64...]
//			int		Height	// Source Image Height				:Height=[16,32,48...]
//			);
//


global _void._.8.8IMG_SplitInto2x2Blocks8x8xor.1unsigned._char._.0.9._unsigned._char._.0.9._unsigned._char._.0.9._int.9._int.2 :label;
      <_void._.8.8IMG_SplitInto2x2Blocks8x8xor.1unsigned._char._.0.9._unsigned._char._.0.9._unsigned._char._.0.9._int.9._int.2>
 
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
	ar2=[--ar5];		//Xor
	gr4=[--ar5];		//Width
	gr6=[--ar5];		//Height
	rep 8 ram=[ar2];
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
		
		rep 8 data=[ar0++gr0] with data xor ram;
		rep 8 [ar6++]=afifo ;
		rep 8 data=[ar1++gr1] with data xor ram;
		rep 8 [ar6++]=afifo ; 
		
		rep 8 data=[ar0++gr0] with data xor ram;
		rep 8 [ar6++]=afifo ;
		rep 8 data=[ar1++gr1] with data xor ram;
		rep 8 [ar6++]=afifo ; 

		push ar0,gr0 with gr2 += gr5 noflags ;
		push ar1,gr1 with gr3 += gr5 noflags ;
		
		ar0 = gr2  with gr2 += gr5 noflags ;
		ar1 = gr3  with gr3 += gr5 noflags ;

		<NextMacroblock>
			rep 8 data=[ar0++gr0] with data xor ram;
			rep 8 [ar6++]=afifo ;
			rep 8 data=[ar1++gr1] with data xor ram;
			rep 8 [ar6++]=afifo ; 
			
			rep 8 data=[ar0++gr0] with data xor ram;
			rep 8 [ar6++]=afifo ;
			rep 8 data=[ar1++gr1] with data xor ram;
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
