//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM640x Software                      */
//*                                                                         */
//*   Software design:  I.Zhilenkov                                     	*/
//*                                                                         */
//*   File:             nmpps-SubC_32f.asm                          	 	*/
//*   Contents:         The function computes y = x - С 					*/
//***************************************************************************/

global _nmppsSubCRev_32f: label;
//void nmppsSubCRev_32f(const nm32f* pSrcVec, nm32f* pDstVec, float C, int nSize);

// x - pSrcVec
// Const - C
// f - pDstVec

begin ".text_nmplv"
<_nmppsSubCRev_32f>
	ar5 = ar7 - 2;
	push ar3, gr3;
	push ar2, gr2;
	push ar1, gr1;
	push ar0, gr0;

	ar0 = [--ar5]; 					// x - pSrcVec
	ar1 = [--ar5]; 					// f - pDstVec
	gr0 = [--ar5]; 					// C - Const
	gr1 = [--ar5];					// size N
	gr7 = ar1;

	ar5 = ar7;
	ar3 = gr0;
	gr3 = gr0;
	push ar3, gr3 with gr2 = gr1 >> 6;

	if =0 delayed goto less64_SubC_32f;
		ar1 = gr7 with gr7 = gr1;
		fpu 0 rep 32 vreg1 = [ar5];					// читаем константу C

<SubC_32f>
	fpu 0 rep 32 vreg0 = [ar0++]; 						// читаем 64 элемента массива pSrcVec
	gr2--;
	if > delayed goto SubC_32f;
		fpu 0 .float vreg2 = vreg1 - vreg0;	// вычитаем из константы 64 элемента
		fpu 0 rep 32 [ar1++] = vreg2;					// пишем результат в память
	gr7 = gr1 << 26;									// вычисляем остаток
	gr7 = gr7 >> 26;									// вычисляем остаток
	if =0 delayed goto exit_SubC_32f;					// если остаток 0, значит обработаны все элементы
<less64_SubC_32f>
		nul;
		gr7 >>= 1;										// проверяем, 1 в остатке или больше
	if =0 delayed goto SubC_32f_OneElement;
		gr7--;
		vlen = gr7;
	fpu 0 rep vlen vreg1 = [ar5];					// читаем константу C
	fpu 0 rep vlen vreg0 = [ar0++];
	fpu 0 .float vreg2 = vreg1 - vreg0;
	fpu 0 rep vlen [ar1++] = vreg2;
<SubC_32f_OneElement>
	gr1 <<= 31;
	if =0 delayed goto exit_SubC_32f;
		gr7 = [ar0];
		gr2 = [ar5];
	gr7 = gr2 - gr7;
	[ar1] = gr7;
<exit_SubC_32f>
	pop ar3, gr3;
	pop ar0, gr0;
	pop ar1, gr1;
	pop ar2, gr2;
	pop ar3, gr3;
	return;
end ".text_nmplv";
