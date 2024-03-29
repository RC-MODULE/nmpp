//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM640x Software                      */
//*                                                                         */
//*   Software design:  I.Zhilenkov                        	*/
//*                                                                         */
//*   File:             nmpps-AbsDiff_32f.asm                          	 	    */
//*   Contents:         The function computes y = |x1 - x2|   				*/
//***************************************************************************/

global _nmppsAbsDiff_32f: label;
//void _nmppsAbsDiff_32f(const nm32f* pSrcVec1, const nm32f* pSrcVec2, nm32f* pDstVec, int nSize);

// x1 - pSrcVec1
// x2 - pSrcVec2
// f - pDstVec

begin ".text_nmplv"
<_nmppsAbsDiff_32f>
	ar5 = ar7 - 2;
	push ar2, gr2;
	push ar1, gr1;
	push ar0, gr0;

	ar0 = [--ar5]; // input nm32f* pSrcVec1
	ar1 = [--ar5]; // input nm32f* pSrcVec2
	ar2 = [--ar5]; // output nm32s* pDstVec
	gr0 = [--ar5]; // size N

	gr1 = gr0 >> 6;
	if =0 delayed goto Sub_32f_less64;
		gr1--;
		nul;
<Sub_32f>
	fpu 0 rep 32 vreg0 = [ar0++];
	fpu 0 rep 32 vreg1 = [ar1++];
	fpu 0 .float vreg2 = vreg0 - vreg1;
	fpu 1 vreg0 = fpu 0 vreg2;
	if > delayed goto Sub_32f	with gr1--;
		fpu 1 .float vreg2 = /vreg0/;
		fpu 1 rep 32 [ar2++] = vreg2;

	gr0 = gr0 << 26;				// computing a remainder
	gr0 = gr0 >> 26;				// computing a remainder

<Sub_32f_less64>			    // N < 64
	gr0 = gr0 >> 1;
	if =0 delayed goto exit_Sub_32f;
		gr0--;
		vlen = gr0;
	fpu 0 rep vlen vreg0 = [ar0++];
	fpu 0 rep vlen vreg1 = [ar1++];
	fpu 0 .float vreg2 = vreg0 - vreg1;
	fpu 1 vreg0 = fpu 0 vreg2;
	fpu 1 .float vreg2 = /vreg0/;
	fpu 1 rep vlen [ar2++] = vreg2;

<exit_Sub_32f>
	pop ar0, gr0;
	pop ar1, gr1;
	pop ar2, gr2;
	return;
end ".text_nmplv";
