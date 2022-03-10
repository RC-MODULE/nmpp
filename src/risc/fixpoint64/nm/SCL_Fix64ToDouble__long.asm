//***************************************************************************/
//*                                                                         */
//*                    Neuroprocessor NM6403 SDK v.1.2                      */
//*                                                                         */
//*				Signed Fixed Point 32-bit Routine           */
//*                                                                         */
//*             ������� ����� �� ���� double � fixed-point 64 b � �������   */
//*               �������� ����� ��������� ����� 31 � 32 �����              */
//*                1999 (c) RC Module Inc., Moscow, Russia                  */
//***************************************************************************/

import from rtmacro.mlb;





macro SHIFTLEFT64(HiReg,LoReg,Counter)
        if < delayed goto StopShift with gr7++;
         LoReg <<=1;
         HiReg C<<=1;
end SHIFTLEFT64;
begin ".text_nmpl�"


//! \fn double nmppcFix64ToDouble(long arg , int fixpoint );
//!
//! \perfinclude _nmppcFix64ToDouble__Fli.html

// �� ����� ����� FixedPoint64(long) ���������� ����� ����
// �� ������ ����� Double ���������� ����� gr7 � gr6. (���������� ��������� � gr7)

<_nmppcFix64ToDouble>
global _nmppcFix64ToDouble :label;
.branch;
	ar5=sp-2;
    push ar1,gr1;
    push ar2,gr2;
    push ar3,gr3;
    
	gr6=[--ar5] with gr3-=gr3;  //������� 32 ���� ����� FixedPoint64
    gr1=[--ar5] with gr6;		//������� 32 ���� ����� FixedPoint64
    if >= goto SkipNeg with gr7-=gr7 noflags;//���� ����� �������������, ��
	//��������� ����� ����� FixedPoint64
	gr1=-gr1;
    gr6=not gr6 noflags;
  	gr3=80000000h with gr6=gr6+carry;//��������� ����� "-" ��� double �����
	<SkipNeg>
	.repeat 64;
        SHIFTLEFT64(gr6,gr1,gr7);	//������.-��� ����� ����� �� �������� ������ �������� ������� ,
									//���������� ����������-gr7
	.endrepeat;
	//double=0.0
	delayed goto EXIT with gr1-=gr1;
		gr6=0; 	
    <StopShift>
	//����� �������� � 51 ����
	gr1>>=12;
	gr2=gr6<<20;
	gr1=gr1 or gr2;
	gr2=41Fh with gr6>>=12;
	//���������� ���������� ����������
	gr7=gr2-gr7;
	/////////
	gr2=32;
	gr2=[--ar5] with gr7+=gr2;
	gr7-=gr2;

	///////
	gr7<<=20;				// ����� ���������� ���������� � 62 ����
	gr6=gr6 or gr7;			// ����������� �������� � ����������
    with gr6=gr3 or gr6;	// ��������� ����� �����

	<EXIT>

	pop ar3,gr3  with gr7=gr1;
    pop ar2,gr2 ;
    pop ar1,gr1;
  	return;	
.wait;


end ".text_nmpl�";
