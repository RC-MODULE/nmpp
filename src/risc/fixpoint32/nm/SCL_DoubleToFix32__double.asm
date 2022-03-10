//***************************************************************************/
//*                                                                         */
//*                    Neuroprocessor NM6403 SDK v.1.2                      */
//*                                                                         */
//*             Signed Fixed Point 32-bit Routine                           */
//*                                                                         */
//*             ������� �� ����� ���� double � fixed-point 32   � �������   */
//*                                                                         */
//*                1999 (c) RC Module Inc., Moscow, Russia                  */
//***************************************************************************/


//////////////////////////////////////////////////////////////////////////////
//                                                                          //
//                DoubleToFix64                                             //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
//  ������ ������ ����� HiReg,LoReg �� Shift ��� ������ ��� �����           // 
//                      � ���������                                         //
//       "+"-����� ����� , "-"- ����� ������                                //
//////////////////////////////////////////////////////////////////////////////
// HiReg,LoReg c��������� �� Shift ��� ����� ��� �����,
// ���������� ��� �������� 
// ��������� ������������ ������ � HiReg

macro R2SHIFT(Reg,Shift)
	delayed goto Exit with Reg>>=Shift;
		nul;nul;
end R2SHIFT;

macro L2SHIFT(HiReg,LoReg,Shift)
	delayed goto Exit with HiReg<<=Shift;
		LoReg>>=32-Shift;
		HiReg=HiReg or LoReg;
end L2SHIFT;

macro SHIFT2TO1(HiReg,LoReg,Shift)
	NoShift:label;
	gr7=NoShift with Shift<<=2;
	gr4+=gr7;
	goto gr4;

	R2SHIFT(HiReg,21);
	R2SHIFT(HiReg,20);
	R2SHIFT(HiReg,19);
	R2SHIFT(HiReg,18);
	R2SHIFT(HiReg,17);
	R2SHIFT(HiReg,16);
	R2SHIFT(HiReg,15);
	R2SHIFT(HiReg,14);
	R2SHIFT(HiReg,13);
	R2SHIFT(HiReg,12);
	R2SHIFT(HiReg,11);
	R2SHIFT(HiReg,10);
	R2SHIFT(HiReg,09);
	R2SHIFT(HiReg,08);
	R2SHIFT(HiReg,07);
	R2SHIFT(HiReg,06);
	R2SHIFT(HiReg,05);
	R2SHIFT(HiReg,04);
	R2SHIFT(HiReg,03);
	R2SHIFT(HiReg,02);
	R2SHIFT(HiReg,01);
	<NoShift>
	delayed goto Exit with HiReg;
		nul; nul;
	L2SHIFT(HiReg,LoReg,01);
	L2SHIFT(HiReg,LoReg,02);
	L2SHIFT(HiReg,LoReg,03);
	L2SHIFT(HiReg,LoReg,04);
	L2SHIFT(HiReg,LoReg,05);
	L2SHIFT(HiReg,LoReg,06);
	L2SHIFT(HiReg,LoReg,07);
	L2SHIFT(HiReg,LoReg,08);
	L2SHIFT(HiReg,LoReg,09);
	L2SHIFT(HiReg,LoReg,10);
	<Exit>		
end SHIFT2TO1;

begin ".text_nmpl�"



//////////////////////////////////////////////////////////////////////////////
//                                                                          //
//  ������� �������� �� Double � Fixed-Point 32                             //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////
//------------- double -------------------
//	(0-1 ) (0-7FFh)            (0-FFFFFFFFFFFFFh)
//	[����] [��������� �������] [��������]
//	  63   62               52 51       0 
//  [+/-] [������� + 3FFh ](1.)[��������]      
//----------------------------------------             


//! \fn int nmppcDoubleToFix32(double x)
//!
//! \perfinclude _nmppcDoubleToFix32__F6double.html
global _nmppcDoubleToFix32 :label;
<_nmppcDoubleToFix32>
.branch;
	ar5=sp-2;
	push ar0,gr0;
	push ar1,gr1;
	push ar2,gr2;
	push ar3,gr3;
	push ar4,gr4;

	gr0=[--ar5];        //���������� � ������� ����� ��������
	gr1=[--ar5];        //������� ����� ��������
	gr7=000FFFFFh;      //����� ��� ��������� �������� ��������
	gr2=gr0 and gr7;    //������� ����� ��������
	gr7=00100000h;
	gr2=gr2 or gr7;     //�������������� ������� ������� 
	gr7=7FF00000h;      //����� ��� ��������� ����������
	gr3=gr0 and gr7;    //��������� ����������
	gr7=3FF00000h;      //c������� 
	gr3-=gr7;			//����������� ����������
	gr3 A>>=20;
	// gr2,gr1		- �������� 
	// gr3			- ����������
	// gr0			- ���� (32-�� ���)
	gr7=17;
	gr4=4 with gr7+=gr3; //���������� ��� ������� �� ���� �������� ��������
	if < delayed goto Finish with gr7-=gr7;
		gr4=gr3-gr4;
		nul;
	SHIFT2TO1(gr2,gr1,gr4);

	//SignCorrect
	with gr0;
	if >= goto Finish with gr7=gr2;
	gr7=-gr2;
	<Finish>
	pop ar4,gr4;
	pop ar3,gr3;
	pop ar2,gr2;
	pop ar1,gr1;
	pop ar0,gr0;
	return;	
	.wait;

end ".text_nmpl�";
