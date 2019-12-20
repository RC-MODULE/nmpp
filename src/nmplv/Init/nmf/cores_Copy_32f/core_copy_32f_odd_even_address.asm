
// A.Brodyazhenko, 2019
// void copy_32f_odd_even_address(ar0 = src, ar6 = dst, gr5 = size);
// src - only odd address
// dst - only even address
// size - all 

global core_copy_32f_odd_even_address: label;
begin "text"
<core_copy_32f_odd_even_address>
	// ar5 = ar7 - 2;
	push ar6, gr6;
	push ar5, gr5;
	push ar4, gr4;
	push ar1, gr1 with gr4 = false; 
	push ar0, gr0 with gr4++;

	// ar0 = [--ar5]; // input
	// ar6 = [--ar5]; // output
	// gr5 = [--ar5]; // size N

	ar0-- with gr6 = gr5;

	ar1 = ar0 + 2;                  // an input address with the offset	(2 elements)

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
    
	gr6 and gr4;
	if =0 goto exit_copy_32f_odd_even_address;

<copying_last_element>
    gr0 = [ar0++];
	[ar6++] = gr0;
<exit_copy_32f_odd_even_address>
	pop ar0, gr0;
	pop ar1, gr1;
	pop ar4, gr4;
	pop ar5, gr5;
	pop ar6, gr6;
	return;
end "text";
