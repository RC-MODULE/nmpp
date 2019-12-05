
global core_Copy_32f: label;

begin ".text_nmplv"
<core_Copy_32f>
	push ar1, gr1;
	push ar2, gr2;
	push ar5, gr5;

//	ar0 = [--ar5]; 					// x - pSrcVec
//	ar6 = [--ar5]; 					// f - pDstVec
//	gr0 = [--ar5]; 					// step
//	gr5 = [--ar5];					// size N

	gr1 = gr5 >> 6;
	if =0 delayed goto less64_core_Copy_32f;
		gr2 = gr5;
		nul;

<start_cycle_core_Copy_32f>
	fpu 0 rep 32 vreg0 = [ar0++]; 						// читаем 64 элемента массива pSrcVec
	fpu 0 rep 32 [ar6++] = vreg0;					    // пишем результат в память
	gr1--;
	if > goto start_cycle_core_Copy_32f;
	gr2 = gr5 << 26;									   // вычисляем остаток
	gr2 = gr2 >> 26;									   // вычисляем остаток
	if =0 delayed goto exit_core_Copy_32f;				   // если остаток 0, значит обработаны все элементы
<less64_core_Copy_32f>
		nul;
		gr2 >>= 1;										   // проверяем, 1 в остатке или больше
	if =0 delayed goto core_Copy_32f_OneElement;
		gr2--;
		vlen = gr2;
	fpu 0 rep vlen vreg0 = [ar0++];
	fpu 0 rep vlen [ar6++] = vreg0;
<core_Copy_32f_OneElement>
	gr5 <<= 31;
	if =0 delayed goto exit_core_Copy_32f;
		ar1, gr1 = [ar6];
		fpu 0 rep 1 vreg0 = [ar0++];
	fpu 0 rep 1 [ar6++] = vreg2;
	[--ar6] = gr1;
<exit_core_Copy_32f>
	pop ar5, gr5;
	pop ar2, gr2;
	pop ar1, gr1;
	return;
end ".text_nmplv";
