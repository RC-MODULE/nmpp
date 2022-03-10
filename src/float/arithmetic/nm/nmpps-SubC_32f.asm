//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM640x Software                      */
//*                                                                         */
//*   Software design:  I.Zhilenkov                                     	*/
//*                                                                         */
//*   File:             nmpps-SubC_32f.asm                          	 	*/
//*   Contents:         The function computes y = x - С 					*/
//***************************************************************************/

global _nmppsSubC_32f: label;
//void nmppsSubC_32f(const nm32f* pSrcVec, nm32f* pDstVec, float C, int nSize);

// x - pSrcVec
// Const - C
// f - pDstVec

begin ".text_nmplv"
<_nmppsSubC_32f>
	ar5 = ar7 - 2;
	push ar2, gr2;
	push ar1, gr1;
	push ar0, gr0;

	ar0 = [--ar5]; 					// x - pSrcVec
	ar1 = [--ar5]; 					// f - pDstVec
	gr0 = [--ar5]; 					// C - Const
	gr1 = [--ar5];					// size N

	[ar1++] = gr0 with gr2 = gr1 >> 6;
	if =0 delayed goto less64_SubC_32f;
		[ar1++] = gr0 with gr7 = gr1;
		fpu 0 rep 1 vreg1 = [--ar1];					// читаем константу C

<SubC_32f>
	fpu 0 rep 32 vreg0 = [ar0++]; 						// читаем 64 элемента массива pSrcVec
	gr2--;
	if > delayed goto SubC_32f;
		fpu 0 .float vreg2 = vreg0 - .retrive(vreg1);	// умножаем на 64 элемента на константу
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
	fpu 0 rep vlen vreg0 = [ar0++];
	fpu 0 .float vreg2 = vreg0 - .retrive(vreg1);
	fpu 0 rep vlen [ar1++] = vreg2;
<SubC_32f_OneElement>
	gr1 <<= 31;
	if =0 delayed goto exit_SubC_32f;
		ar2, gr2 = [ar1];
		fpu 0 rep 1 vreg0 = [ar0++];
	fpu 0 .float vreg2 = vreg0 - .retrive(vreg1);
	fpu 0 rep 1 [ar1++] = vreg2;
	[--ar1] = gr2;
<exit_SubC_32f>
	pop ar0, gr0;
	pop ar1, gr1;
	pop ar2, gr2;
	return;
end ".text_nmplv";
