//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM640x Software, 2017                */
//*                                                                         */
//*   Software design:  A.Bolotnikov                	                      */
//*                                                	                        */
//*   File:             nmppsMerge_32f.asm 				      	                  */
//*   Contents:         Joins 2 float arrays in one array in order 					*/
//*												{src0[0],src1[0],src0[1],src1[1],...}   */
//*																				*/
//*										     								*/
//***************************************************************************/


global _nmppsMerge_32f : label;

begin ".data_nmplv"
.align;
	one_zero : word[2] = (float(1),float(0));
	zero_one : word[2] = (float(0),float(1));
end ".data_nmplv";

begin ".text_nmplv"
<_nmppsMerge_32f>
//void nmppsMerge_32f(const nm32f* pSrcVec1, const nm32f* pSrcVec2, nm32f* pDstVec, int nSize);	
	ar5 = ar7 - 2;
	push ar0,gr0;
	ar0 = one_zero;
	fpu 0 rep 32 vreg2 = [ar0];
	ar0 = zero_one;
	fpu 0 rep 32 vreg5 = [ar0];
	push ar1,gr1;
	push ar2,gr2;
	push ar3,gr3;
	ar0 = [--ar5];
	ar1 = [--ar5];
	ar2 = [--ar5];
	gr7 = [--ar5];
	gr2 = 4;
	gr0 = gr7 << 26;
	gr0 = gr0 >> 27;
	gr7 = gr7 >> 6;
	if =0 delayed goto REMAINDER;
		ar3 = ar2 + 2 with gr3 = gr2;

<LOOP>
	fpu 0 rep 32 vreg0 = [ar0++];
	fpu 0 rep 32 vreg1 = [ar1++];
	fpu 0 .matrix vreg3 = (vreg0,vreg1)*vreg2;
	fpu 0 rep 32 [ar2++gr2] = vreg3;
 	gr7--;
 	if <>0 delayed goto LOOP;
 		fpu 0 .matrix vreg4 = (vreg0,vreg1)*vreg5;
 		fpu 0 rep 32 [ar3++gr3] = vreg4;

<REMAINDER>
	gr0;
	if =0 delayed goto END;
		gr0--;
		vlen = gr0;

	ar5 = one_zero;
	fpu 0 rep vlen vreg2 = [ar5];
	ar5 = zero_one;
	fpu 0 rep vlen vreg5 = [ar5];

	fpu 0 rep vlen vreg0 = [ar0++];
	fpu 0 rep vlen vreg1 = [ar1++];
	fpu 0 .matrix vreg3 = (vreg0,vreg1)*vreg2;
	fpu 0 rep vlen [ar2++gr2] = vreg3;
 	fpu 0 .matrix vreg4 = (vreg0,vreg1)*vreg5;
 	fpu 0 rep vlen [ar3++gr3] = vreg4;

<END>
 	pop ar3,gr3;
 	pop ar2,gr2;
	pop ar1,gr1;
	pop ar0,gr0;
	return;
end ".text_nmplv";
