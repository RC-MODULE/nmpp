//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM640x Software                      */
//*                                                                         */
//*   Software design:  A.Brodyazhenko                                      */
//*                                                                         */
//*   File:             nmpps-vMulConj_32fc.asm                             */
//*   Contents:         Multiplies the elements of two vectors              */
//*                     Vector1 * Conjugate(Vector2)                        */
//***************************************************************************/

// C prototype: void nmppsMulConj_32fc(int N, nm32fcr *vec1, nm32fcr *vec2, nm32fcr *dst);

global _nmppsMulConj_32fc: label;
begin ".text"
<_nmppsMulConj_32fc>
	push ar3, gr3;
	push ar2, gr2;
	push ar1, gr1;
	push ar0, gr0;
	ar0 = ar7 - 10; // здесь на 1 слово меньше, чем лежит первый параметр функции
	gr0 = [--ar0]; // N - эементы массива
	ar1 = [--ar0]; // считываем адрес начала входного вектора1
	ar2 = [--ar0]; // считываем адрес начала входного вектора2
	ar3 = [--ar0]; // считываем адрес начала выходного вектора
	gr1 = 32;
	gr0 - gr1;
	if < goto less32_vmul;
	if =0 goto less32_vmul;
	gr3 = gr0 >> 5;
<lab_vmul>
	fpu 0 rep 32 vreg0 = [ar1++];
	fpu 0 rep 32 vreg1 = [ar2++];
	fpu 0 .packer = vreg1 with .float .in_low <= .float .in_low;
	fpu 0 rep 32 vreg3 = .packer;
	fpu 0 .float vreg1 = vreg1 - vreg3;
	fpu 0 .float vreg1 = vreg1 - vreg3;
	fpu 0 .complex vreg2 = vreg0 * vreg1;
	fpu 0 rep 32 [ar3++] = vreg2;
	gr3--;
	if > goto lab_vmul;
	gr4 = 1fh;
	gr2 = gr0 and gr4; // остаток от деления на 32
	if > delayed goto scrap_vmul;
	gr2--;
	vlen = gr2;
	goto exit_vmul;
<less32_vmul>
	gr0--;
	vlen = gr0;
	fpu 0 rep vlen vreg0 = [ar1++];
	fpu 0 rep vlen vreg1 = [ar2++];
	fpu 0 .packer = vreg1 with .float .in_low <= .float .in_low;
	fpu 0 rep vlen vreg3 = .packer;
	fpu 0 .float vreg1 = vreg1 - vreg3;
	fpu 0 .float vreg1 = vreg1 - vreg3;
	delayed goto exit_vmul;
	fpu 0 .complex vreg2 = vreg0 * vreg1;
	fpu 0 rep vlen [ar3++] = vreg2;
<scrap_vmul>
	fpu 0 rep vlen vreg0 = [ar1++];
	fpu 0 rep vlen vreg1 = [ar2++];
	fpu 0 .packer = vreg1 with .float .in_low <= .float .in_low;
	fpu 0 rep vlen vreg3 = .packer;
	fpu 0 .float vreg1 = vreg1 - vreg3;
	fpu 0 .float vreg1 = vreg1 - vreg3;
	delayed goto exit_vmul;
	fpu 0 .complex vreg2 = vreg0 * vreg1;
	fpu 0 rep vlen [ar3++] = vreg2;
<exit_vmul>
	pop ar0, gr0;
	pop ar1, gr1;
	pop ar2, gr2;
	pop ar3, gr3;
	return;
end ".text";
