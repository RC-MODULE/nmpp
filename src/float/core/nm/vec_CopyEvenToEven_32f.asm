//******************************************************************************************//
//* Prototype: void vec_CopyEvenToEven_32f(ar0 = src, ar6 = dst, gr5 = size);              *//
//* Contents: A Copying of a floating point array from even src address to even dst address*//
//* src - even address only                                                                *//
//* dst - even address only                                                                *//
//* size - all sizes (0, 1, 2, 3, 4, ... )                                                 *//
//******************************************************************************************//

global vec_CopyEvenToEven_32f: label;

begin ".text_nmplv"
<vec_CopyEvenToEven_32f>
	push ar1, gr1;
	push ar2, gr2;
	push ar5, gr5;

//	ar0 = [--ar5]; 					// src - pSrcVec
//	ar6 = [--ar5]; 					// dst - pDstVec
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
	if =0 delayed goto core_Copy_32f_one_element;
		gr2--;
		vlen = gr2;
	fpu 0 rep vlen vreg0 = [ar0++];
	fpu 0 rep vlen [ar6++] = vreg0;
<core_Copy_32f_one_element>
	gr5 <<= 31;
	gr5 >>= 31;
	if =0 goto exit_core_Copy_32f;
	gr1 = [ar0++];
	[ar6++] = gr1;
<exit_core_Copy_32f>
	pop ar5, gr5;
	pop ar2, gr2;
	pop ar1, gr1;
	return;
end ".text_nmplv";
