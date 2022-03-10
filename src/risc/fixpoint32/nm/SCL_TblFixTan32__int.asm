//***************************************************************************/
//*                                                                         */
//*                    Neuroprocessor NM6403 SDK v.1.2                      */
//*                                                                         */
//*				Signed Fixed Point 32-bit Routine                           */
//*                                                                         */
//*             ���������� �������� ����� � ������������� �������           */
//*                                                                         */
//*                                                                         */
//*                1999 (c) RC Module Inc., Moscow, Russia                  */
//***************************************************************************/
//	Arg1 - Angle
//--------------------------
//	Res1 - Sin
//!!!!!!!!!!!!!!!!!!! ������ ����� !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
const FIXPOINT=16; //��������� �������� ����� �������� � ������ :
// FixSin32.asm FixCos32.asm FixDivPosMod32.asm
const N=9;//804-����� - ��������� ������������ ������ ������� �������� �������� 
//const N=10//1608-�����  �������� � ������ : FixSin32.asm FixCos32.asm 
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
const PI2 = (6487ed51h >> (30-FIXPOINT)) ;//PI2=90 ����.
const MAXINDEX=PI2 >> (FIXPOINT-N);//������ ������� �������� ������

import from macros.mlb;

begin ".text_nmpl�"
//////////////////////////////////////////////////////////////////////////////
//                                                                          //
//                            Fixed  Point Tangens                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////
//! \fn int nmppcTblFixTan32(int nArg)
//!
//! \perfinclude _nmppcTblFixTan32__Fi.html
global _nmppcTblFixTan32:label;
<_nmppcTblFixTan32>
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
end ".text_nmpl�";
