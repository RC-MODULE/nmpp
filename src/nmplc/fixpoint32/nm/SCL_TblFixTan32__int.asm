//***************************************************************************/
//*                                                                         */
//*                    Neuroprocessor NM6403 SDK v.1.2                      */
//*                                                                         */
//*				Signed Fixed Point 32-bit Routine                           */
//*                                                                         */
//*             Вычисление тангенса числа с фиксированной запятой           */
//*                                                                         */
//*                                                                         */
//*                1999 (c) RC Module Inc., Moscow, Russia                  */
//***************************************************************************/
//	Arg1 - Angle
//--------------------------
//	Res1 - Sin
//!!!!!!!!!!!!!!!!!!! МЕНЯТЬ ЗДЕСЬ !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
const FIXPOINT=16; //Положение двоичной точки меняется в файлах :
// FixSin32.asm FixCos32.asm FixDivPosMod32.asm
const N=9;//804-точки - константа определяющая размер массива значений тангенса 
//const N=10//1608-точек  меняется в файлах : FixSin32.asm FixCos32.asm 
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
const PI2 = (6487ed51h >> (30-FIXPOINT)) ;//PI2=90 град.
const MAXINDEX=PI2 >> (FIXPOINT-N);//Размер массива значений синуса

import from macros.mlb;

begin ".text_nmplс"
//////////////////////////////////////////////////////////////////////////////
//                                                                          //
//                            Fixed  Point Tangens                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////
//! \fn int SCL_TblFixTan32(int nArg)
//!
//! \perfinclude _SCL_TblFixTan32__Fi.html
global _SCL_TblFixTan32:label;
<_SCL_TblFixTan32>
.branch;
	ar5 = sp-2;
	push ar0,gr0;
	push ar1,gr1;
	gr0 = [--ar5];
//	FIXSIN32(gr0,gr1);
//	FIXCOS32(gr0,gr0);
//	FIXDIV32(gr1,gr0,gr7);
	pop ar1,gr1;
	pop ar0,gr0;
	return;
return;	
.wait;
end ".text_nmplс";
