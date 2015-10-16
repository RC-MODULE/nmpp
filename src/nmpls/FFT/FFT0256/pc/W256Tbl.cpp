//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM6403 Software                      */
//*                                                                         */
//*   Fast Fourie Transform Library                                         */
//*                                                                         */
//*   File:             W256Tbl.cpp                                         */
//*   Contents:         Procedure for generation of the sin-cos tables      */
//*                        for FFT_Fwd256 function (for NM6403 part)          */
//*                     (Use this programm to generate 256tbl.asm)          */
//*                                                                         */
//*   Software design:  S.Mushkaev                                          */
//*                                                                         */
//*   Start date:       15.01.2001                                          */
//*   Last update :     -                                                   */
//*                                                                         */
//*                                                                         */
//***************************************************************************/

//#include "fft.h"
//#include "fftext.h"
//#include "make_tbl.h"
#include "fftext.h"


void ReSortW1_256(	vec<nmint64s > &WRe,
					vec<nmint64s > &WIm,
					vec<nmint64s > &Dst)
{
	ASSERTE(WRe.size==16*16*16>>3);
	ASSERTE(WRe.size==16*16*16>>3);
	ASSERTE(Dst.size==16*16*16>>2);

	int idx=0;
	
	for(int i=0;i<32;i++)
	{
		for(int j=i;j<WRe.size;j+=32)
		{
			Dst[idx++]=WRe[j];
			Dst[idx++]=WIm[j];
		}
	}
	
}

///////////////////////////////////////////////////////////////////
// Generation of two tables of sin-cos coefficients for FFT_Fwd256 function
// Output 2 Tables into stdout 
// Redirect stdout output to file for W256tbl.asm generation
// EXAMPLE:  Debug\pcFFT256.exe > W256tbl.asm
void OutTableW1W2_256(double Ampl,
					  char* W1_Name,char *W1_Section,
					  char* W2_Name,char *W2_Section)
{

	int SizeW1=16*16*16;
	int SizeW2=16*16*16;
	////////////// Making Table //////////////////////
	vec<cmplx<char > > W1_256(SizeW1);
	vec<cmplx<char > > W2_256(SizeW2);

	MakeTable256W1W2(W1_256,W2_256,Ampl);
	
	////////////// Packing ///////////////////////////
	vec<nmint64s > W1Pack8Re(SizeW1>>3);
	vec<nmint64s > W1Pack8Im(SizeW1>>3);
	
	vec<nmint64s > W2Pack8Re(SizeW2>>3);
	vec<nmint64s > W2Pack8Im(SizeW2>>3);
	
	CmplxPack8to64(W1_256,W1Pack8Re,W1Pack8Im);
	CmplxPack8to64(W2_256,W2Pack8Re,W2Pack8Im);
	
	
	//////////// Resorting ///////////////////////////
	vec<nmint64s >  W1Table(SizeW1>>2);
	vec<nmint64s >  W2Table(SizeW2>>2);
	
	ReSortW1_256(W1Pack8Re,W1Pack8Im,W1Table);
	ReSortW1_256(W2Pack8Re,W2Pack8Im,W2Table);
	
	//////////// StdOut //////////////////////////////

	OutTable(W1Table,W1_Name,W1_Section);
	OutTable(W2Table,W2_Name,W2_Section);


	
}
