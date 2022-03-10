//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM6403 Software                      */
//*                                                                         */
//*   Fast Fourie Transform Library                                         */
//*                                                                         */
//*   File:             W512Tbl.cpp                                         */
//*   Contents:         Procedure for generation of the sin-cos tables      */
//*                        for FFT_Fwd512 function (for NM6403 part)          */
//*                     (Use this programm to generate 512tbl.asm)          */
//*                                                                         */
//*   Software design:  S.Mushkaev                                          */
//*                                                                         */
//*   Start date:       15.01.2001                                          */
//*   Last update :     -                                                   */
//*                                                                         */
//*                                                                         */
//***************************************************************************/

#include "fftext.h"

void ReSortW1_512(	vec<nmint64s > &WRe,
					vec<nmint64s > &WIm,
					vec<nmint64s > &Dst)

{
	ASSERTE(WRe.size==16*2*16>>3);
	ASSERTE(WRe.size==16*2*16>>3);
	ASSERTE(Dst.size==16*2*16>>2);

	size_t idx=0;
	size_t re_idx=0;
	size_t im_idx=0;
	int i;
	for (i=0;i<32;i+=2)
	{
		Dst[i+0]		=WRe[re_idx++];	// 0,1,..7
		Dst[i+0 +1]		=WIm[im_idx++];
	
		Dst[i+32]		=WRe[re_idx++];	// 8,9,..15
		Dst[i+32+1]		=WIm[im_idx++];
	}

	for (i=0;i<32;i+=2)
	{
		Dst[i+0+64]			=WRe[re_idx++];	// 0,1,..7
		Dst[i+1+64]			=WIm[im_idx++];
		
		Dst[i+32+0+64]		=WRe[re_idx++];	// 8,9,..15
		Dst[i+32+1+64]		=WIm[im_idx++];
	}
}

void ReSortW2_512(
				vec<nmint64s > &WRe,
				vec<nmint64s > &WIm,
				vec<nmint64s > &Dst)

{
	ASSERTE(WRe.size==16*16*16*2>>3);
	ASSERTE(WRe.size==16*16*16*2>>3);
	ASSERTE(Dst.size==16*16*16*2>>2);

	size_t idx=0;
	size_t re_idx=0;
	size_t im_idx=0;
	for(int j=0;re_idx<16*16*16*2/8;j+=128)
	{
		int i;
		for (i=0;i<32;i+=2)
		{
			Dst[j+i+0]	=WRe[re_idx++];// 0,1,..7
			Dst[j+i+1]	=WIm[im_idx++];
			
			Dst[j+i+32+0]=WRe[re_idx++];// 8,9,..16
			Dst[j+i+32+1]=WIm[im_idx++];
			
		}

		for (i=0;i<32;i+=2)
		{
			Dst[j+64+i+0]	=WRe[re_idx++];// 0,1,..7
			Dst[j+64+i+1]	=WIm[im_idx++];
			
			Dst[j+64+i+32+0]=WRe[re_idx++];// 8,9,..16
			Dst[j+64+i+32+1]=WIm[im_idx++];
		}
	}
}

///////////////////////////////////////////////////////////////////
// Generation of two tables of sin-cos coefficients for FFT_Fwd512 function
// Output 2 Tables into stdout 
// Redirect stdout output to file for W512tbl.asm generation
// EXAMPLE:  Debug\pcFFT512.exe > W512tbl.asm
void OutTableW1W2_512(double Ampl,
					  char* W1_Name,char *W1_Section,
					  char* W2_Name,char *W2_Section)

{
	int SizeW1=16*2*16;
	int SizeW2=16*16*16*2;
	////////////// Making Table //////////////////////
	vec<cmplx<char > > W1_512(SizeW1);
	vec<cmplx<char > > W2_512(SizeW2);

	MakeTable512W1W2(W1_512,W2_512,Ampl);
	
	////////////// Packing ///////////////////////////
	vec<nmint64s > W1Pack8Re(SizeW1>>3);
	vec<nmint64s > W1Pack8Im(SizeW1>>3);
	
	vec<nmint64s > W2Pack8Re(SizeW2>>3);
	vec<nmint64s > W2Pack8Im(SizeW2>>3);
	
	CmplxPack8to64(W1_512,W1Pack8Re,W1Pack8Im);
	CmplxPack8to64(W2_512,W2Pack8Re,W2Pack8Im);
	
	
	//////////// Resorting ///////////////////////////
	vec<nmint64s >  W1Table(SizeW1>>2);
	vec<nmint64s >  W2Table(SizeW2>>2);
	
	ReSortW1_512(W1Pack8Re,W1Pack8Im,W1Table);
	ReSortW2_512(W2Pack8Re,W2Pack8Im,W2Table);
	
	//////////// StdOut //////////////////////////////

	OutTable(W1Table,W1_Name,W1_Section);
	OutTable(W2Table,W2_Name,W2_Section);

}