//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM6403 Software                      */
//*                                                                         */
//*   Fast Fourie Transform Library                                         */
//*                                                                         */
//*   File:             W2048Tbl.cpp                                        */
//*   Contents:         Procedure for generation of the sin-cos tables      */
//*                        for FFT_Fwd2048 function (for NM6403 part)         */
//*                     (Use this programm to generate 2048tbl.asm)         */
//*                                                                         */
//*   Software design:  S.Mushkaev                                          */
//*                                                                         */
//*   Start date:       15.01.2001                                          */
//*   Last update :     -                                                   */
//*                                                                         */
//*                                                                         */
//***************************************************************************/



#include "fftext.h"

void ReSortW1_2048(vec<nmint64s > &WRe,
					vec<nmint64s > &WIm,
					vec<nmint64s > &Dst)

{
	ASSERTE(WRe.size==2048>>3);
	ASSERTE(WRe.size==2048>>3);
	ASSERTE(Dst.size==2048>>2);

	int im_idx=0;
	int re_idx=0;
	
	int i,j,idx=0;
	
	////// first 32*4 re ////////////
	for (i=0;i<4;i++)
	{
		for (j=0;j<128;j+=4)
			Dst[idx++]=WRe[j+i];// 0,1,..7
	}

	////// first 32*4 im ////////////
	for (i=0;i<4;i++)
	{
		for (j=0;j<128;j+=4)
			Dst[idx++]=WIm[j+i];// 0,1,..7
	}
	////// second 32*4 re ////////////

	for (i=0;i<4;i++)
	{
		for (j=0;j<128;j+=4)
			Dst[idx++]=WRe[128+j+i];// 0,1,..7
	}
	////// second 32*4 im ////////////
	for (i=0;i<4;i++)
	{
		for (j=0;j<128;j+=4)
			Dst[idx++]=WIm[128+j+i];// 0,1,..7
	}

}

void ReSortW2_2048(
				vec<nmint64s > &WRe,
				vec<nmint64s > &WIm,
				vec<nmint64s > &Dst)

{
	ASSERTE(WRe.size==2048*32>>3);
	ASSERTE(WRe.size==2048*32>>3);
	ASSERTE(Dst.size==2048*32>>2);

	int im_idx=0;
	int re_idx=0;
	for (int  j=0;j<2048*32*2/8;j+=512)
	{
		int i;
		for (i=0;i<32;i++)
		{
			Dst[j+i+0] =WRe[re_idx++];// 0,1,..7
			Dst[j+i+32]=WRe[re_idx++];// 8,9,..15
			Dst[j+i+64]=WRe[re_idx++];// 16,17..23
			Dst[j+i+96]=WRe[re_idx++];// 24,25..31
			
			Dst[j+i+ 0+128]=WIm[im_idx++];// 0,1,..7
			Dst[j+i+32+128]=WIm[im_idx++];// 8,9,..15
			Dst[j+i+64+128]=WIm[im_idx++];// 16,17..23
			Dst[j+i+96+128]=WIm[im_idx++];// 24,25..31
		}
		
		for (i=0;i<32;i++)
		{
			Dst[j+i+256+0] =WRe[re_idx++];// 32,33,..39
			Dst[j+i+256+32]=WRe[re_idx++];// 40,41,..47
			Dst[j+i+256+64]=WRe[re_idx++];// 48,49..
			Dst[j+i+256+96]=WRe[re_idx++];// 56,57..
			
			Dst[j+i+256+ 0+128]=WIm[im_idx++];// 32,33,..39
			Dst[j+i+256+32+128]=WIm[im_idx++];// 40,41,..47
			Dst[j+i+256+64+128]=WIm[im_idx++];// 48,49..
			Dst[j+i+256+96+128]=WIm[im_idx++];// 56,57..
		}
	}
}


///////////////////////////////////////////////////////////////////
// Generation of two tables of sin-cos coefficients for FFT_Fwd2048 function
// Output 2 Tables into stdout 
// Redirect stdout output to file for W2048tbl.asm generation
// EXAMPLE:  Debug\pcFFT2048.exe > W2048tbl.asm
void OutTableW1W2_2048(double Ampl,
					  char* W1_Name,char *W1_Section,
					  char* W2_Name,char *W2_Section)

{
	int SizeW1=2048;
	int SizeW2=2048*32;
	////////////// Making Table //////////////////////
	vec<cmplx<char > > W1_2048(SizeW1);
	vec<cmplx<char > > W2_2048(SizeW2);

	MakeTable2048W1W2(W1_2048,W2_2048,Ampl);
	
	////////////// Packing ///////////////////////////
	vec<nmint64s > W1Pack8Re(SizeW1>>3);
	vec<nmint64s > W1Pack8Im(SizeW1>>3);
	
	vec<nmint64s > W2Pack8Re(SizeW2>>3);
	vec<nmint64s > W2Pack8Im(SizeW2>>3);
	
	CmplxPack8to64(W1_2048,W1Pack8Re,W1Pack8Im);
	CmplxPack8to64(W2_2048,W2Pack8Re,W2Pack8Im);
	
	
	//////////// Resorting ///////////////////////////
	vec<nmint64s >  W1Table(SizeW1>>2);
	vec<nmint64s >  W2Table(SizeW2>>2);
	
	ReSortW1_2048(W1Pack8Re,W1Pack8Im,W1Table);
	ReSortW2_2048(W2Pack8Re,W2Pack8Im,W2Table);
	
	//////////// StdOut //////////////////////////////

	OutTable(W1Table,W1_Name,W1_Section);
	OutTable(W2Table,W2_Name,W2_Section);

}

