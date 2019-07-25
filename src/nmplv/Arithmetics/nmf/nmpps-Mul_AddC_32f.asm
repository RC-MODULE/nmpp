//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM640x Software                      */
//*                                                                         */
//*   Software design:  I.Zhilenkov                                      	*/
//*                                                                         */
//*   File:             nmpps-Mul_AddC_32f.asm                           	*/
//*   Contents:         The function computes f = x1 * x2 + c 				*/
//***************************************************************************/

global _nmppsMul_AddC_32f: label;
//void nmppsMul_AddC_32f(nm32f* pSrcVec1, nm32f* pSrcVec2, float nValueAddC, nm32f* pDstVec, int nSize);
// x1 - pSrcVec1
// x2 - pSrcVec2
// C - nValueC
// f - pDstVec

begin ".data"
	valueC: long;
end ".data";

begin ".text_nmplv"
<_nmppsMul_AddC_32f>
	ar5 = ar7-2;
	push ar0,gr0;
	push ar1,gr1;
	push ar2,gr2;
	push ar5,gr5;
	push ar6,gr6;
	
	ar0 = [--ar5];
	ar1 = [--ar5];
	gr0 = [--ar5];
	ar6 = [--ar5];
	gr5 = [--ar5];
	ar5 = valueC	with gr5>>=1;
	[ar5++] = gr0	with gr7 = gr5<<27;
	[ar5] = gr0		with gr7 >>=27;
	ar5--			with gr5 >>=5;
	fpu 0 rep 32 vreg2 = [ar5];		
	if =0 delayed goto Tail with gr7--;
		nul;
		vlen = gr7 with gr5--;	
	
<Next32>
	fpu 0 rep 32 vreg0 = [ar0++]; 
	fpu 0 rep 32 vreg1 = [ar1++]; 
	if > delayed goto Next32 with gr5--;
		fpu 0 .float vreg7 = vreg0*vreg1 + vreg2; 
		fpu 0 rep 32 [ar6++] = vreg7;
<Tail>	
	gr7;		//flag tail
	if < delayed goto End;	
		nul;
		nul;
	fpu 0 rep vlen vreg2 = [ar5];	
	fpu 0 rep vlen vreg0 = [ar0++]; 
	fpu 0 rep vlen vreg1 = [ar1++];  
	fpu 0 .float vreg7 = vreg0*vreg1+vreg2; 
	fpu 0 rep vlen [ar6++] = vreg7;

<End>	
	
	pop ar6,gr6;
	pop ar5,gr5;
	pop ar2,gr2;
	pop ar1,gr1;
	pop ar0,gr0;
	return;
end ".text_nmplv";