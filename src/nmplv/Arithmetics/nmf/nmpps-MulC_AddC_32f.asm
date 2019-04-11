//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM640x Software                      */
//*                                                                         */
//*   Software design:  I.Zhilenkov                                     	*/
//*                                                                         */
//*   File:             nmpps-MulC_AddC_32f.asm                        	 	*/
//*   Contents:         The function computes y = Const1 * x + Const2		*/
//***************************************************************************/

global _nmppsMulC_AddC_32f: label;
//void nmppsMulC_AddC_32f(const nm32f* pSrcVec, float nMulC, float nAddC, nm32f* pDstVec,  int nSize);

// x - pSrcVec
// Const1 - MulC
// Const2 - AddC
// f - pDstVec

nobits ".data"
	temp: long[2];	//mulC, addC
end ".data";

More_64f:label;

begin ".text"
<_nmppsMulC_AddC_32f>
	ar5 = ar7 - 2;
	push ar0, gr0;
	push ar5, gr5;
	push ar6, gr6;
	
	ar0 = [--ar5]; 					// x - pSrcVec
	gr0 = [--ar5]; 					// C - Const	
	ar6 = temp;
	[ar6++] = gr0;
	[ar6++] = gr0;
	gr0 = [--ar5]; 					// C - Const
	[ar6++] = gr0;
	[ar6++] = gr0;
	ar6 = [--ar5]; 					// f - pDstVec
	gr5 = [--ar5];					// size N
	gr5>>=1;
	ar5 = temp		with gr7 = gr5<<27;
	fpu 0 rep 32 vreg1 = [ar5];
	ar5+=2			with gr7 >>= 27;
	fpu 0 rep 32 vreg2 = [ar5];
	gr7--;
	ar5 = More_64f	with gr5>>=5;
	if =0 delayed goto Less_64f;
		vlen = gr7;
		gr5--;
<More_64f>
	if > delayed goto ar5	with gr5--;
		fpu 0 rep 32 vreg0 = [ar0++];
		fpu 0 .float vreg7 = vreg0*vreg1+vreg2;
		fpu 0 rep 32 [ar6++] = vreg7;
<Less_64f>	
	gr7;
	if < delayed goto end_program;
		ar5 = temp;
	fpu 0 rep vlen vreg1 = [ar5];
	ar5+=2;
	fpu 0 rep vlen vreg2 = [ar5];
	fpu 0 rep vlen vreg0 = [ar0++];
	fpu 0 .float vreg7 = vreg0*vreg1+vreg2;
	fpu 0 rep vlen [ar6++] = vreg7;
<end_program>
	pop ar6, gr6;
	pop ar5, gr5;
	pop ar0, gr0;
	return;
end ".text";
