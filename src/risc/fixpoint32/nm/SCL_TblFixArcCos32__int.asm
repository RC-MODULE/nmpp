//***************************************************************************/
//*                                                                         */
//*                    Neuroprocessor NM6403 SDK v.1.2                      */
//*                                                                         */
//*				Signed Fixed Point 32-bit Routine                           */
//*                                                                         */
//*             ���������� ��������� ����� � ������������� �������          */
//*                                                                         */
//*                                                                         */
//*                1999 (c) RC Module Inc., Moscow, Russia                  */
//***************************************************************************/
//	Arg1 - Angle
//--------------------------
//	Res1 - Sin
//!!!!!!!!!!!!!!!!!!! ������ ����� !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
const FIXPOINT=16; //��������� �������� ����� � 32-� ��������� �����
const N=10;//1025-����� - ��������� ������������ ������ ������� �������� ��������� 
//const N=10//1608-�����
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
const MAXINDEX=10000h >> (FIXPOINT-N);//������ ������� �������� ������
const PI2 = (6487ed51h >> (30-FIXPOINT)) ;//PI2=90 ����.

import from macros.mlb;
extern FixArcSinDat:word;


begin ".text_nmpl�"

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
//                            Fixed  Point ArcCosine                        //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////
// gr0 �������� �� gr7 !!!

//! \fn int nmppcTblFixArcCos32(int nArg)
//! 
//! \perfinclude _nmppcTblFixArcCos32__Fi.html
global _nmppcTblFixArcCos32:label;
<_nmppcTblFixArcCos32>
.branch;
	ar5 = sp-2;
	gr7 = [--ar5];
	push ar1,gr1 with gr7;
	//with gr7=Arg;// �������� ���������� ����� gr7			 
	//���������� ������ ����
	if >= delayed skip 4 with gr1=gr7;
		ar1=FixArcSinDat ;
	gr1=-gr1;
	nul;
	//����������� �������� ,�������������� ������� ����
		gr1 >>=(FIXPOINT-N);	//���������� ������� �� �������� ����
		gr7=[ar1+=gr1] with gr7;
	//��������� ����� ���������	 
	if >= delayed skip 4;
		gr1=PI2;
	gr7=-gr7;
	nul;
	with gr7=gr1-gr7;
	pop ar1,gr1;
return;
.wait;
end ".text_nmpl�";
