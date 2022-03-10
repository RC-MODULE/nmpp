//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM6403 Software                      */
//*                                                                         */
//*   Fast Fourie Transform Library                                         */
//*                                                                         */
//*   File:             IW1024Tbl.cpp                                       */
//*   Contents:         Procedure for generation of the sin-cos tables      */
//*                        for FFT_Inv1024 function (for NM6403 part)        */
//*                     (Use this programm to generate i1024tbl.asm)        */
//*                                                                         */
//*   Software design:  S.Mushkaev                                          */
//*                                                                         */
//*   Start date:       15.01.2001                                          */
//*   Last update :     -                                                   */
//*                                                                         */
//*                                                                         */
//***************************************************************************/


#include "fftext.h"

void IReSortW1_1024(vec<nmint64s > &WRe,
					vec<nmint64s > &WIm,
					vec<nmint64s > &Dst)

{
	ASSERTE(WRe.size==32*32*2>>3);
	ASSERTE(WRe.size==32*32*2>>3);
	ASSERTE(Dst.size==32*32*2>>2);

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

void IReSortW2_1024(
				vec<nmint64s > &WRe,
				vec<nmint64s > &WIm,
				vec<nmint64s > &Dst)

{
	ASSERTE(WRe.size==32*16*16*2>>3);
	ASSERTE(WRe.size==32*16*16*2>>3);
	ASSERTE(Dst.size==32*16*16*2>>2);

	int re_idx=0,im_idx=0;
	for(int j=0;j<4096;j+=128)
	{
		int i;
		for (i=0;i<32;i+=2)
		{
			Dst[j+i+0]=WRe[re_idx++];// 0,1,..7
			Dst[j+i+1]=WIm[im_idx++];// 0,1,..7
			
			Dst[j+i+32+0]=WRe[re_idx++];// 8,9,..16
			Dst[j+i+32+1]=WIm[im_idx++];// 8,9,..16
			
		}

		for (i=0;i<32;i+=2)
		{
			Dst[j+64+i+0]=WRe[re_idx++];// 0,1,..7
			Dst[j+64+i+1]=WIm[im_idx++];
			
			Dst[j+64+i+32+0]=WRe[re_idx++];// 8,9,..16
			Dst[j+64+i+32+1]=WIm[im_idx++];
		}
	}
}


///////////////////////////////////////////////////////////////////
// Generation of two tables of sin-cos coefficients for FFT_Fwd1024 function
// Output 2 Tables into stdout 
// Redirect stdout output to file for iW1024tbl.asm generation
// EXAMPLE:  Debug\pcIFFT1024.exe > iW1024tbl.asm
void IOutTableW1W2_1024(double Ampl,
					  char* W1_Name,char *W1_Section,
					  char* W2_Name,char *W2_Section)

{
	int SizeW1=32*32*2;
	int SizeW2=32*16*16*2;
	////////////// Making Table //////////////////////
	vec<cmplx<char > > W1_1024(SizeW1);
	vec<cmplx<char > > W2_1024(SizeW2);

	IMakeTable1024W1W2(W1_1024,W2_1024,Ampl);
	
	////////////// Packing ///////////////////////////
	vec<nmint64s > W1Pack8Re(SizeW1>>3);
	vec<nmint64s > W1Pack8Im(SizeW1>>3);
	
	vec<nmint64s > W2Pack8Re(SizeW2>>3);
	vec<nmint64s > W2Pack8Im(SizeW2>>3);
	
	CmplxPack8to64(W1_1024,W1Pack8Re,W1Pack8Im);
	CmplxPack8to64(W2_1024,W2Pack8Re,W2Pack8Im);
	
	
	//////////// Resorting ///////////////////////////
	vec<nmint64s >  W1Table(SizeW1>>2);
	vec<nmint64s >  W2Table(SizeW2>>2);
	
	IReSortW1_1024(W1Pack8Re,W1Pack8Im,W1Table);
	IReSortW2_1024(W2Pack8Re,W2Pack8Im,W2Table);
	
	//////////// StdOut //////////////////////////////

	OutTable(W1Table,W1_Name,W1_Section);
	OutTable(W2Table,W2_Name,W2_Section);

}


