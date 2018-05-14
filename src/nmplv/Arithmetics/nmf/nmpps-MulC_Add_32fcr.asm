//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM640x Software                      */
//*                                                                         */
//*   Software design:  I.Zhilenkov                                      	*/
//*                                                                         */
//*   File:             nmpps-MulC_Add_32fcr.asm                           	*/
//*   Contents:         The function computes f = x1 * C + x2 				*/
//***************************************************************************/

global _nmppsMulC_Add_32fcr: label;
//void nmppsMulC_Add_32fcr(nm32fcr* pSrcVec1, nm32fcr* pSrcVec2, nm32fcr* pDstVec, float C, int nSize);
// x1 - pSrcVec1
// x2 - pSrcVec2
// C  - C
// f - pDstVec

data ".data"
	temp: word[2];
end ".data";


begin ".text"
<_nmppsMulC_Add_32fcr>
	ar5 = ar7-2;
	push ar0,gr0;
	push ar1,gr1;
	push ar2,gr2;
	push ar5,gr5;
	push ar6,gr6;
	
	ar0 = [--ar5];
	ar1 = [--ar5];
	ar6 = [--ar5];
	gr2 = [--ar5];
	gr5 = [--ar5];
	
	ar2=gr2 			with gr7 = gr5<<27;
	[temp] = ar2,gr2 	with gr7 >>=27;
	ar2=temp 			with gr5 >>=5;
		
	if =0 delayed goto Tail with gr7--;
		fpu 0 rep 1 vreg2 = [ar2];
		vlen = gr7 with gr5--;	
	
<Next32>
	fpu 0 rep 32 vreg0 = [ar0++]; 
	fpu 0 rep 32 vreg1 = [ar1++]; 	
	if > delayed goto Next32 with gr5--;
		fpu 0 .float vreg7 = vreg0*.retrive(vreg2)+vreg1; 
		fpu 0 rep 32 [ar6++] = vreg7;
<Tail>	
	gr7;		//flag tail
	if < delayed goto End;	
		nul;
		nul;	
		
	fpu 0 rep vlen vreg0 = [ar0++]; 
	fpu 0 rep vlen vreg1 = [ar1++]; 
	fpu 0 .float vreg7 = vreg0*.retrive(vreg2)+vreg1; 
	fpu 0 rep vlen [ar6++] = vreg7;

<End>	
	
	pop ar6,gr6;
	pop ar5,gr5;
	pop ar2,gr2;
	pop ar1,gr1;
	pop ar0,gr0;
	return;
end ".text";