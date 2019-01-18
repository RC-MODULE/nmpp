//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM640x Software, 2018                */
//*                                                                         */
//*   Software design:  A.Brodyazhenko                                      */
//*                                                                         */
//*   File:             nmppsConvert_32f32s_rounding.asm                    */
//*   Contents:         Convert data array from nm32f to nm32s              */
//*						round(nm32f) -> nm32s								*/
//*	  Prototype: void nmppsConvert_32f32s_rounding(const nm32f* pSrcVec,    */
//*                                                      nm32s* pDstVec,    */
//*                                                      int nSize);        */
//*   pSrcVec - pointer to input  array nm32f	                            */
//*   pDstVec - pointer of output array nm32s	                            */
//*   nSize - input and output arrays size	                                */
//***************************************************************************/

global _nmppsConvert_32f32s_rounding: label;

extern core_nmppsConvert_32f32s_rounding: label;

begin "text"
<_nmppsConvert_32f32s_rounding>
	ar5 = ar7 - 2;
	push ar1, gr1;
	push ar0, gr0;

	ar0 = [--ar5]; // input nm32f* pSrcVec
	ar1 = [--ar5]; // output nm32s* pDstVec
	gr0 = [--ar5]; // nSize
	// gr2 = [--ar5]; // scale factor

	call core_nmppsConvert_32f32s_rounding;

	pop ar0, gr0;
	pop ar1, gr1;
	return;
end "text";
