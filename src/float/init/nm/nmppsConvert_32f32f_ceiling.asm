//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM640x Software, 2021                */
//*                                                                         */
//*   Software design:  S.Mushkaev                                          */
//*                                                                         */
//*   File:             nmppsConvert_32f32f_ceiling.asm                     */
//*   Contents:         Convert data array from nm32f to nm32f              */
//*						ceiling(nm32f) -> nm32f							    */
//*	  Prototype: void nmppsConvert_32f32f_ceiling(const nm32f* pSrcVec,     */
//*                                                      nm32f* pDstVec,    */
//*                                                      int nSize);        */
//*   pSrcVec - pointer to input  array nm32f	                            */
//*   pDstVec - pointer of output array nm32f	                            */
//*   nSize - input and output arrays size	                                */
//***************************************************************************/

global _nmppsConvert_32f32f_ceiling: label;

extern core_nmppsConvert_32f32f_ceiling: label;

begin ".text_nmplv"
<_nmppsConvert_32f32f_ceiling>
	ar5 = ar7 - 2;
	push ar2, gr2;
	push ar1, gr1;
	push ar0, gr0;

	ar0 = [--ar5];    	// input nm32f* pSrcVec
	ar1 = [--ar5];    	// output nm32s* pDstVec
	ar2 = [--ar5];		// scale factor
	gr0 = [--ar5];    	// nSize

	call core_nmppsConvert_32f32f_ceiling;

	pop ar0, gr0;
	pop ar1, gr1;
	pop ar2, gr2;
	return;
end ".text_nmplv";
