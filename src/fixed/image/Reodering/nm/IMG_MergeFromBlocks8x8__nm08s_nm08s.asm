//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM6403 Software                      */
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
//*   Version          1.0                                                  */
//*   Start date:      23.11.2001                                           */
//*   Release  $Date: 2005/02/10 12:36:36 $*/
//*                                                                         */
//*                                                                         */
//***************************************************************************/
import from macros;



begin ".text_nmpli"

////////////////////////////////////////////////////////////////////////////
    //--------------------------------------------------------------------
    //! \fn void nmppiMergeFromBlocks8x8( nm8s* Src, nm8s* Dst, int Width, int Height);
    //!
	//! \perfinclude _nmppiMergeFromBlocks8x8__FPcPcii.html
    //--------------------------------------------------------------------
//	int nmppiMergeFromBlocks8x8(
//			nm8s*	Src,	// Source one-dimensional Array	:long Local[Width*Height/8]
//			nm8s*	Dst,	// Result Image					:long Global[Width*Height/8]
//			int		Width,	// Source Image Width;			:Width=[8,16,24...]
//			int		Height	// Source Image Height;			:Height=[8,16,24..]
//			);
//
// DESCRIPTION:
//  Transforms the one-dimensional array to to image frame. In order:
//
//  Source one-dimensional Array:
//  [A00|A01|A02|...|A06|A07|A20|A21|...|A77|B00|B01|B02|...|B07|B10|...|H77|
//  [I00|I01|I02|...|I06|I07]I10|I11|...|I77|J00|J01|J02|...............|Z77|
//
//  Result Image:
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
//
//  RETURN: 0
//
//  PERFORMANCE:
//		The performance of the ArrangeInLine routines depends on memory allocation for
//		input and output buffers.
//		For the maximum speed performance it is recommended
//		to use the following configurations:
//		Configuration I.
//			Src:		Global SRAM
//			Dst:		Local  SRAM
//		Configuration II.
//			Src:		local  SRAM
//			Dst:		Global SRAM
//
//		For these configuration the following results were achieved:
//		Configuration I:
//			28508 ticks per 384*288 Image with C++ call (0.257 clocks per pixel)
//		Configuration II:
//			19723 ticks per 384*288 Image with C++ call	(0.178 clocks per pixel)
//
// W=384,H=288
//nmppiMergeFromBlocks8x8((nm8s*)GSrc,(nm8s*)GSrc,W,H);// 31401
//nmppiMergeFromBlocks8x8((nm8s*)GSrc,(nm8s*)LSrc,W,H);// 28489
//nmppiMergeFromBlocks8x8((nm8s*)LSrc,(nm8s*)GSrc,W,H);// 19727*
//nmppiMergeFromBlocks8x8((nm8s*)LSrc,(nm8s*)LSrc,W,H);// 37007


global _nmppiMergeFromBlocks8x8: label;
<_nmppiMergeFromBlocks8x8>
.branch;
	ar5=ar7-2;
	PUSH_REGS();
	ar6=[--ar5];		//SrcBuffer
	gr4=[--ar5];		//DstBuffer
	gr0=[--ar5];		//Width
	gr1=[--ar5];		//Height


	gr2=gr0>>2;			// Width in 32bit words

	gr6=gr1>>3;			// Height in Regions by 8Rows

	gr5=gr2<<3;			// Size of Region in 32bit words
	gr3=gr4;
	ar2=gr3;
	gr1=2;
	<To8x8_Next8Rows>
		gr7=gr0>>3;		// Width in 64-bit longs
		gr7--;
		<To8x8_NextCol_by8>
			rep 8 data=[ar6++] with data;
			nul;
		if <>0 delayed goto To8x8_NextCol_by8 with gr7--;
			ar2=gr3 with gr3+=gr1 noflags;
			rep 8 [ar2++gr2]=afifo;
		gr4+=gr5 ;		// To the next Region
		with gr6--;
	if <>0 delayed goto To8x8_Next8Rows;
		gr3=gr4;
		ar2=gr4;

	POP_REGS();
return with gr7=false;
.wait;

end ".text_nmpli";
