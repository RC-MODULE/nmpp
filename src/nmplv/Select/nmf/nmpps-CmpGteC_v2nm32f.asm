//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM640x Software                      */
//*                                                                         */
//*   Software design:  A.Brodyazhenko                                     	*/
//*   Year: 2018                                                            */
//*   File:             nmpps-CmpGte_32f.asm                          	 	*/
//*   Contents:         The function computes y = Const * x   				*/
//***************************************************************************/

global _nmppsCmpGteC_v2nm32f: label;
//void nmppsCmpGteC_v2nm32f(const v2nm32f* pSrcVec, const v2nm32f C, nm1* evenFlags, nm1* oddFlags, int step, int nSize);

begin ".text"
<_nmppsCmpGteC_v2nm32f>
	ar5 = ar7 - 2;
	// push ar5, gr5;
	// push ar4, gr4;
	push ar3, gr3;
	push ar2, gr2;
	push ar1, gr1;
	push ar0, gr0;

	ar0 = [--ar5] with gr3 = false; 	  // pSrcVec
	ar3 = [--ar5];
	ar1 = [--ar5]; 		                  // pMask1
	ar2 = [--ar5]; 					      // pMask2
	gr0 = [--ar5]; 		                  // step
	gr1 = [--ar5] with gr0 <<= 1;	      // nSize

	fpu 0 rep 1 vreg1 = [ar3];
	ar3 = gr3;
	sir = ar3,gr3;
	gr2 = gr1 >> 5;
	if =0 delayed goto less32_CmpGte_32f;
		fp0_lmask = sir;
		fp0_hmask = sir;

<CmpGte_32f>
	// fp0_lmask = sir;
	// fp0_hmask = sir;
	fpu 0 rep 32 vreg0 = [ar0++gr0]; 						// читаем 64 элемента массива pSrcVec
	//fpu 0 .float vreg7 = vreg0 - vreg0;
	//fpu 0 .float vreg7 = vreg0 - vreg7, set mask if >=;

	fpu 0 .float vreg2 = vreg0 - .retrive(vreg1), set mask if >=;
	//fpu 0 .float vreg7 = vreg2 - vreg7, set mask if >=;


	//sir = fp0_lmask;
	// sir = fp0_lmask;
	// ar3 = sir;
	//
	// sir = fp0_hmask;
	// gr3 = sir;
	//


	gr2--;
	if > delayed goto CmpGte_32f;
		[ar1++] = fp0_lmask;
		[ar2++] = fp0_hmask;

	gr1 = gr1 << 27;									// вычисляем остаток
	gr1 = gr1 >> 27;									// вычисляем остаток
	if =0 delayed goto exit_CmpGte_32f;					// если остаток 0, значит обработаны все элементы
    	fp0_lmask = sir;
    	fp0_hmask = sir;
<less32_CmpGte_32f>
	gr1--;
	vlen = gr1;
	fpu 0 rep vlen vreg0 = [ar0++gr0];
	fpu 0 .float vreg2 = vreg0 - .retrive(vreg1), set mask if >=;
	[ar1++] = fp0_lmask;
	[ar2++] = fp0_hmask;
<exit_CmpGte_32f>
	pop ar0, gr0;
	pop ar1, gr1;
	pop ar2, gr2;
	pop ar3, gr3;
	// pop ar4, gr4;
	// pop ar5, gr5;
	return;
end ".text";
