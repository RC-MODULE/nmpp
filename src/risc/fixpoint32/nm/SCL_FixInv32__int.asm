//***************************************************************************/
//*                                                                         */
//*                    Neuroprocessor NM6403 SDK v.1.2                      */
//*                                                                         */
//*				Signed Fixed Point 32-bit Routine Library                   */
//*                                                                         */
//*             ���������� ��������� �������� ����� (1/x)                   */
//*                                                                         */
//*                                                                         */
//* Date:20.12.99  1999 (c) RC Module Inc., Moscow, Russia                  */
//***************************************************************************/

//--------------------------------------------
macro DIV_STEP()		//gr0=x-gr1
	if carry delayed skip 4 with gr7 C<<=1;
		with gr0<<=1;	//gr0=2x-2*gr1
		with gr0-=gr1;	//gr0=2x-3*gr1
	gr0+=gr1;			//gr0=2x-2*gr1
	gr0+=gr1;			//gr0=2x-gr1
end DIV_STEP;

begin ".text_nmpl�"
//////////////////////////////////////////////////////////////////////////////
//                                                                          //
//    ���������� ��������� �������� ����� (1/Divisor)  �� ������            //                         //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////
// int IDivInv32( int Divisor,int DivIterations );
//				int		Divisor			-�������� �����	
//		const	int		DivIterations   -���-�� �������� ��� ���������(���������) �������,
//      �������� DivIterations ������ ������ � �������� [1,62]    
// ������������ �������� �������� IDivInv32 ������������� 
// �������� �� �������������� ������� (1<<(DivItearations-1))/Divisor
// ����� ������� �������� ��� �������� �� ������� �� ������� ��������� ����� �.�.
// �� ������� 31 ����, ���������� ����� �������� ���������
// (1<<(DivItearations-1))/Divisor �� ������ ���� ������ 1<<31 =>
// DivIterations <= Min(Divisor)*31; (Min(Divisor)- ���������� ��������� �� ������ ����� Divisor)
// DivIterations =Min(Divisor) - ������������ ������������ �������� ��������
//////// Examples ////////////////////////////////////////////////////////////
// 1/x=IDivInv(x,itres) =return value
// IDivInv32(1,1)		=1;
// IDivInv32(1,2)		=2;
// IDivInv32(1,3)		=4;
// IDivInv32(1,17)		=0x10000;
// IDivInv32(1,31)		=0x40000000;
// IDivInv32(1,32)		=0x80000000;(error)
// IDivInv32(1,33)		=0;(error)
// IDivInv32(-1,1)		=0xFFFFFFFF;
// 1/2=
// IDivInv32(2,1)=0;
// IDivInv32(2,2)=1;
// 1/0x10000=
// IDivInv32(0x10000,17)=0x1;
// IDivInv32(0x10000,33)=0x10000;
// IDivInv32(0x10000,47)=0x40000000;
// IDivInv32(0x10000,48)=0x80000000;(error)
// IDivInv32(0x10000,49)=0;(error)
// 1/0x7FFFFFFF=
// IDivInv32(0x7FFFFFF,32)=1;
// IDivInv32(0x7FFFFFF,48)=0x10000;
// IDivInv32(0x7FFFFFF,62)=0x40000000;
// IDivInv32(0x7FFFFFF,63)=0x80000001;(error)
////// Clocks ///////////////////////////////////////////////////////////////
// DivIterations	Clocks
// 1-				31
// 2-				<34
// 4-				<46
// 8-				<70
// 16-				<118
// 17-				<124
// 31-				<208
// 63-				<400
// +50 ������ - ����� ������� �� ��
//////////////////////////////////////////////////////////////////////////////

//! \fn int nmppcFixInv32(int nVal, int nFixpoint)
//!
//! \perfinclude _nmppcFixInv32__Fii.html
global _nmppcFixInv32 :label;
<_nmppcFixInv32>

.branch;
	EndDiv :label;
	ar5=ar7-4;
	push ar2,gr2;
	gr2=[ar5++];					// ���-�� �������� ��� ���������(���������) �������
	gr2++;
	// ---����. 3 ������� - ��������� gr2 �� 6 (6 - ������ ������� DIV_STEP)------
	push ar1,gr1 with gr7=gr2<<2;	// 
	gr1=[ar5++]	 with gr2<<=1;		// gr1- �������� 
	ar2=EndDiv	 with gr2+=gr7;		// gr2=gr2*6
	push ar0,gr0 with gr2=-gr2;		//  gr2-�������� ��� ���������� ����� ����� � ��������� �������
	ar2+=gr2 with gr1;				// ar2-���������� ����� ����� � ��������� �������
	// --- ���������� ������ �������� ---
	if >= delayed skip 4 with gr2=gr1;// ��������� ���� �������� � gr2
		ar5=0 with gr7=false;		// gr7-������� =0
	gr1=-gr1;							
	nul;
	delayed goto ar2 with gr0=gr7+1;// gr0-�������=1
		ar5=0 with gr0-=gr1;		
	// -- ��������� ������� -----
	.repeat 63;
	DIV_STEP();
	.endrepeat;
	// DIV_STEP 64
	with gr7 C<<=1;
	with gr2;						// ���� ��������
	//----- ��������� ����� �������� ----
	if >= delayed skip 4;
		pop ar0,gr0;
		pop ar1,gr1;
	<EndDiv>
	gr7=-gr7;						//��������� ����� ��������
	nul;
	pop ar2,gr2;
return;
.wait;
end ".text_nmpl�";

