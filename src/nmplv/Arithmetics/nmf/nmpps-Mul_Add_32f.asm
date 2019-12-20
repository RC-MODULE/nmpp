//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM640x Software                      */
//*                                                                         */
//*   Software design:  I.Zhilenkov                                      	*/
//*                                                                         */
//*   File:             nmpps-MulC_Add_32f.asm                           	*/
//*   Contents:         The function computes f = x1 * x2 + x3 				*/
//***************************************************************************/

global _nmppsMul_Add_32f: label;
//void nmppsMul_Add_32f(nm32f* pSrcVec1, nm32f* pSrcVec2, nm32f* pSrcVecAdd, nm32f* pDstVec, int nSize);
// x1 - pSrcVec1
// x2 - pSrcVec2
// x3 - pSrcVecAdd
// f - pDstVec


begin ".text_nmplv"
<_nmppsMul_Add_32f>
	ar5 = ar7-2;
	push ar0,gr0;
	push ar1,gr1;
	push ar2,gr2;
	push ar5,gr5;
	push ar6,gr6;
	
	ar0 = [--ar5];
	ar1 = [--ar5];
	ar2 = [--ar5];
	ar6 = [--ar5];
	gr5 = [--ar5];
	gr5>>=1;
	
	gr7 = gr5<<27;
	gr7 >>=27;
	gr5 >>=5;
	
	if =0 delayed goto Tail with gr7--;
		nul;
		vlen = gr7;	
	
<Next32>
	fpu 0 rep 32 vreg0 = [ar0++]; 
	fpu 0 rep 32 vreg1 = [ar1++];
	fpu 0 .float vreg2 = vreg0 * vreg1;
	fpu 1 vreg1 = fpu 0 vreg2;
	fpu 1 rep 32 vreg2 = [ar2++]; 	
	fpu 1 .float vreg3 = vreg1 + vreg2; 
	fpu 1 rep 32 [ar6++] = vreg3;
	with gr5--;
	if > goto Next32;
<Tail>	
	gr7;		//flag tail
	if < delayed goto End;	
		nul;
		nul;	
		
	fpu 0 rep vlen vreg0 = [ar0++]; 
	fpu 0 rep vlen vreg1 = [ar1++];
	fpu 0 .float vreg2 = vreg0 * vreg1;
	fpu 1 vreg1 = fpu 0 vreg2;
	fpu 1 rep vlen vreg2 = [ar2++]; 	
	fpu 1 .float vreg3 = vreg1 + vreg2; 
	fpu 1 rep vlen [ar6++] = vreg3;


<End>	
	
	pop ar6,gr6;
	pop ar5,gr5;
	pop ar2,gr2;
	pop ar1,gr1;
	pop ar0,gr0;
	return;
end ".text_nmplv";