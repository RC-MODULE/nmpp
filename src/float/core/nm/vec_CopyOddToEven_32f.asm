
//******************************************************************************************//
//* A.Brodyazhenko, 2019                                                                   *//
//* Prototype: void vec_CopyOddToEven_32f(ar0 = src, ar6 = dst, gr5 = size);               *//
//* Contents: A Copying of a floating point array from odd src address to even dst address *//
//* src - odd address only                                                                 *//
//* dst - even address only                                                                *//
//* size - all size except zero (1, 2, 3, 4, ... )                                         *//
//******************************************************************************************//

// A.Brodyazhenko, 2019
// void vec_CopyOddToEven_32f(ar0 = src, ar6 = dst, gr5 = size);
// src - odd address only
// dst - even address only
// size - all size except zero (1, 2, 3, 4, ... )

global vec_CopyOddToEven_32f: label;
begin ".text_nmplv"
<vec_CopyOddToEven_32f>
	// ar5 = ar7 - 2;
	push ar5, gr5;
	push ar4, gr4;
	push ar1, gr1 with gr4 = false; 

	// ar0 = [--ar5]; // input
	// ar6 = [--ar5]; // output
	// gr5 = [--ar5]; // size N

	ar0-- with gr1 = gr5;

	ar1 = ar0 + 2 with gr4++;                  // an input address with the offset	(2 elements)

	gr7 = gr5 >> 6;
	if =0 goto less64_copy_32f_odd_even_address;

<cycles_copy_32f_odd_even_address>
    fpu rep 32 .packer = [ar0++] with .float .in_low <= .float .in_high;
	fpu 0 rep 32 vreg0 = .packer;
    fpu rep 32 .packer = [ar1++] with .float .in_high <= .float .in_low;
	fpu 0 rep 32 vreg1 = .packer;
    fpu 0 .float vreg2 = vreg0 + vreg1;
	fpu 0 rep 32 [ar6++] = vreg2;
	gr7--;
	if > goto cycles_copy_32f_odd_even_address;
	gr5 = gr5 << 26;
    gr5 = gr5 >> 26;
    if =0 goto exit_copy_32f_odd_even_address;

<less64_copy_32f_odd_even_address>
	ar0++ with gr5 >>= 1;
	if =0 goto copying_last_element;
	gr5--;
	vlen = gr5;
    fpu rep vlen .packer = [ar0++] with .float .in_low <= .float .in_high;
	fpu 0 rep vlen vreg0 = .packer;
    fpu rep vlen .packer = [ar1++] with .float .in_high <= .float .in_low;
	fpu 0 rep vlen vreg1 = .packer;
    fpu 0 .float vreg2 = vreg0 + vreg1;
	fpu 0 rep vlen [ar6++] = vreg2;
    
	gr1 and gr4;
	if =0 goto exit_copy_32f_odd_even_address;

<copying_last_element>
    gr1 = [ar0++];
	[ar6++] = gr1;
<exit_copy_32f_odd_even_address>
	pop ar1, gr1;
	pop ar4, gr4;
	pop ar5, gr5;
	return;
end ".text_nmplv";
