
// A.Brodyazhenko, 2019
// void core_copy_32f_even_odd_address(ar0 = src, ar6 = dst, gr5 = size);
// src - only even address
// dst - only odd address
// size - all

// ar0 - src
// ar6 - dst
// gr5 - size

global core_copy_32f_even_odd_address: label;
begin "text"
<core_copy_32f_even_odd_address>
	// ar5 = ar7 - 2;
	push ar6, gr6;
	push ar5, gr5;
	push ar4, gr4;
	push ar3, gr3;
	push ar2, gr2;
	push ar1, gr1;
	push ar0, gr0 with gr6 = gr5;

	// ar0 = [--ar5]; // input
	// ar6 = [--ar5]; // output
	// gr5 = [--ar5]; // size N


	ar2 = ar6 + gr6;                // getting a last element address 
	ar2++;                          // getting after the last element address
	gr3 = [ar2] with gr4 = false;   // saving a element after the last element

	gr1 = [ar0];     // reading a first element and saving N (count elements)
	[ar6++] = gr1 with gr4++;       // copying a first element to a output array

    ar1 = ar0 + 2;                  // a input address with the offset	

	gr7 = gr5 >> 6;
	if =0 goto less64_copy_32f_even_odd_address;

<cycles_copy_32f_even_odd_address>
    fpu rep 32 .packer = [ar0++] with .float .in_low <= .float .in_high;
	fpu 0 rep 32 vreg0 = .packer;
    fpu rep 32 .packer = [ar1++] with .float .in_high <= .float .in_low;
	fpu 0 rep 32 vreg1 = .packer;
    fpu 0 .float vreg2 = vreg0 + vreg1;
	fpu 0 rep 32 [ar6++] = vreg2;
	gr7--;
	if > goto cycles_copy_32f_even_odd_address;
	gr5 = gr5 << 26;
    gr5 = gr5 >> 26;
	if =0 goto even_parity;
<less64_copy_32f_even_odd_address>
	gr5 >>= 1;
	if =0 goto even_parity;
    gr5--;
	vlen = gr5;
    fpu rep vlen .packer = [ar0++] with .float .in_low <= .float .in_high;
	fpu 0 rep vlen vreg0 = .packer;
    fpu rep vlen .packer = [ar1++] with .float .in_high <= .float .in_low;
	fpu 0 rep vlen vreg1 = .packer;
    fpu 0 .float vreg2 = vreg0 + vreg1;
	fpu 0 rep vlen [ar6++] = vreg2;

<even_parity>
    gr7 = gr6 and gr4;
	if > goto exit_copy_32f_even_odd_address;
	ar6--;
	[ar6] = gr3;                         // restoring a element after the last element
<exit_copy_32f_even_odd_address>
	pop ar0, gr0;
	pop ar1, gr1;
	pop ar2, gr2;
	pop ar3, gr3;
	pop ar4, gr4;
	pop ar5, gr5;
	pop ar6, gr6;
	return;
end "text";
