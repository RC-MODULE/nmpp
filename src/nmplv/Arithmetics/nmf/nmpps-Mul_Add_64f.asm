//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM640x Software                      */
//*                                                                         */
//*   Software design:  I.Zhilenkov                                      	*/
//*                                                                         */
//*   File:             nmpps-MulC_Add_32fcr.asm                           	*/
//*   Contents:         The function computes f = x1 * x2 + x3 				*/
//***************************************************************************/

global _nmppsMul_Add_64f: label;
//void nmppsMul_Add_64f(nm64f* pSrcVec1, nm64f* pSrcVec2, nm64f* pSrcVecAdd, nm64f* pDstVec, int nSize);
// x1 - pSrcVec1
// x2 - pSrcVec2
// x3 - pSrcVecAdd
// f - pDstVec

begin ".text"
<_nmppsMul_Add_64f>
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
	
	gr7 = gr5<<27;
	gr7 >>=27;
	gr5 >>=5;
	Next32:label;
	ar5 = Next32;
	
	if =0 delayed goto Tail with gr7--;
		nul;
		vlen = gr7 with gr5--;	
	
<Next32>
	fpu 0 rep 32 vreg0 = [ar0++]; 
	fpu 0 rep 32 vreg1 = [ar1++]; 
	fpu 0 .double vreg6 = vreg0*vreg1; 
	fpu 1 rep 32 vreg2 = [ar2++]; 	
	if > delayed goto ar5 with gr5--;
		fpu 1 vreg6 = fpu 0 vreg6; 
		fpu 1 .double vreg7 = vreg6+vreg2; 
		fpu 1 rep 32 [ar6++] = vreg7;
<Tail>	
	gr7;		//flag tail
	if < delayed goto End;	
		nul;
		nul;	
		
	fpu 0 rep vlen vreg0 = [ar0++]; 
	fpu 0 rep vlen vreg1 = [ar1++]; 
	fpu 0 rep vlen vreg2 = [ar2++]; 
	fpu 0 .double vreg7 = vreg0*vreg1+vreg2; 
	fpu 0 rep vlen [ar6++] = vreg7;

<End>	
	
	pop ar6,gr6;
	pop ar5,gr5;
	pop ar2,gr2;
	pop ar1,gr1;
	pop ar0,gr0;
	return;
end ".text";