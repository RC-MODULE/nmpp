//***************************************************************************/
//*                                                                         */
//*                    Neuroprocessor NM6403 SDK v.1.2                      */
//*                                                                         */
//*                                                                         */
//*      ������� ������� �� ��������� ������������                          */
//*                                                                         */
//*                                                                         */
//* Date:08.01.2000     (c) RC Module Inc., Moscow, Russia                  */
//***************************************************************************/

//import from macros;
//import from vtdef;
//VECTYPEDEF();

data ".data_nmplc_G"
	Buffer64:long[70];
	Two_DelLeftBits:long[66]=(
			2hl,
	
			00000000000000000hl,

			00000000000000001hl,
			00000000000000003hl,
			00000000000000007hl,
			0000000000000000Fhl,

			0000000000000001Fhl,
			0000000000000003Fhl,
			0000000000000007Fhl,
			000000000000000FFhl,

			000000000000001FFhl,
			000000000000003FFhl,
			000000000000007FFhl,
			00000000000000FFFhl,
			
			00000000000001FFFhl,
			00000000000003FFFhl,
			00000000000007FFFhl,
			0000000000000FFFFhl,
			
			0000000000001FFFFhl,
			0000000000003FFFFhl,
			0000000000007FFFFhl,
			000000000000FFFFFhl,
			
			000000000001FFFFFhl,
			000000000003FFFFFhl,
			000000000007FFFFFhl,
			00000000000FFFFFFhl,
			
			00000000001FFFFFFhl,
			00000000003FFFFFFhl,
			00000000007FFFFFFhl,
			0000000000FFFFFFFhl,
			
			0000000001FFFFFFFhl,
			0000000003FFFFFFFhl,
			0000000007FFFFFFFhl,
			000000000FFFFFFFFhl,

			000000001FFFFFFFFhl,
			000000003FFFFFFFFhl,
			000000007FFFFFFFFhl,
			00000000FFFFFFFFFhl,
			
			00000001FFFFFFFFFhl,
			00000003FFFFFFFFFhl,
			00000007FFFFFFFFFhl,
			0000000FFFFFFFFFFhl,

			0000001FFFFFFFFFFhl,
			0000003FFFFFFFFFFhl,
			0000007FFFFFFFFFFhl,
			000000FFFFFFFFFFFhl,

			000001FFFFFFFFFFFhl,
			000003FFFFFFFFFFFhl,
			000007FFFFFFFFFFFhl,
			00000FFFFFFFFFFFFhl,

			00001FFFFFFFFFFFFhl,
			00003FFFFFFFFFFFFhl,
			00007FFFFFFFFFFFFhl,
			0000FFFFFFFFFFFFFhl,

			0001FFFFFFFFFFFFFhl,
			0003FFFFFFFFFFFFFhl,
			0007FFFFFFFFFFFFFhl,
			000FFFFFFFFFFFFFFhl,

			001FFFFFFFFFFFFFFhl,
			003FFFFFFFFFFFFFFhl,
			007FFFFFFFFFFFFFFhl,
			00FFFFFFFFFFFFFFFhl,

			01FFFFFFFFFFFFFFFhl,
			03FFFFFFFFFFFFFFFhl,
			07FFFFFFFFFFFFFFFhl,
			0FFFFFFFFFFFFFFFFhl
			);
			





end ".data_nmplc_G";	   
begin ".text_nmpl�"
//////////////////////////////////////////////////////////////////////////////
//                                                                          //
//    ������� ������� A/B ��� ����� ����� �� ������, 2*abs(A)<abs(B)         //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////
//	void IDivInv64(
//				long*		Dividend,		// ������� 
//				long*		Divisor,		// ��������
//		const	int			DivIterations,	// ���-�� �������� ��� ���������(���������) �������
//				long*		Quotient		// �������
//					);	
//------- ������������ ��������-------
// ������������ �������� �������� IdivInv64 �������������  �������� 
// �� �������������� ������� �� ������  (Divisor<<(DivItearations-1)) �� Divisor.
//----- ��������� --------
// long* Dividend -64 ��������� ����� ������� �� ������
// long* Divisor -64 ��������� ����� �������� �� ������ .
// Divisor ������ ���� ����� ,����� abs( Dividend)<2*abs(Divisor)
// const int DivIterations   -���-�� �������� ��� ���������(���������) �������, �������� DivIterations 
// ����� ���������� � �������� [1,63] � ����� ���� �������� ������.
// ---- ���������� ---------
// ����� ������� �������� ��� �������� �� ������� �� ������� ��������� 
// ����� �.�. �� ������� 62 ����, ���������� ����� �������� ��������� 
// (Dividend<<(DivItearations-1))/Divisor �� ������ ���� ������ ��� (1<<63) 

macro VEC_DIV_STEP()								// A-����������� �������, B-��������
	rep 1 [ar6]=afifo	with vsum ,activate afifo,afifo;//[ar6]=A-B  afifo=0 OR A-B+2B
	rep 1 data=[ar6++]	with afifo+data;		//afifo=(A-B)+(A-B) or (A-B)+(A+B)
	rep	1				with afifo-ram;			//afifo=(2A-2B)-B or 2A-B
end VEC_DIV_STEP;	

//! \fn  void nmppcFixDiv64(long* nDividend,	long* nDivisor, int nFixpoint, long* nQuotient)
//!
//! \perfinclude _nmppcFixDiv64__FPlPliPl.html

global _nmppcFixDiv64:label;
<_nmppcFixDiv64>
.branch;
EndVecDiv:label;
EndMakeQuotient:label;
	ar5=sp-2;

	push ar0,gr0;
	push ar1,gr1 with gr7= false;
	nb1=gr7;							// nb=0
	sb=gr7;								// sb=0
	ar0=[--ar5];						// ar0=&Dividend
	ar1=[--ar5] with gr0=true;			// ar1=&Divisor
	f1cr=gr0;							// gr0=-1;
	wtw; // WTW_REG_DEPRICATED(gr7);
	//--- ���������� ������ �������� ------------
	rep 1 ram=[ar1] with mask ,activate data,0;
	rep 1 [ar7++]=afifo with 0-ram;
	rep 1 data=[--ar7] with mask data,afifo,ram; 
	//--- afifo=abs(Divisor)---------------------
	//--- �������� � WBUF -2*Divisor -----------
	rep 1 [ar7],ram=afifo with afifo+afifo;
	rep 1			with 0-afifo;
	rep 1 [ar7++]=afifo;
	rep 1 wfifo=[--ar7],ftw;
	//--- ���������� ������ �������� ------------
	push ar2,gr2;
	ar2,gr2=[ar0];						// gr2=sign(Dividend)
	push ar6,gr6 with gr2;
	if >= delayed goto SkipNegation with gr7=true;
		rep 1 data=[ar0] with data;
		ar6,gr6=[ar1];					// gr6=sign(Divisor)
	rep 1 with 0-afifo;
	nul;
	<SkipNegation>
	rep 1 with afifo-ram;				// ���������� ������ �������� Dividend-Divisor
	gr1=[--ar5] with gr6=gr6 xor gr2;	// gr1=DivIterations (must be odd)
gr1++;

										// gr6=sign(Quotient)
	f2cr = gr7 with gr0=gr1-1;			// gr0=DivIterations-1 (even)
	ar5=[--ar5] with gr7=gr0<<1;		// ar5=&Quotient;
										// 
	ar0=EndVecDiv with gr0+=gr7;		// gr0=3*(DivIterations-1);(Sizeof(DIV_VEC_STEP)=3)
	ar1=Two_DelLeftBits	with gr0=-gr0;	// gr0: Jump back from <EndDivVec>
	ar2=EndMakeQuotient	with gr2=gr1-1;	// gr2=(DivIterations-1);
	ar6=Buffer64 with gr2=-gr2;			// gr2: Jump back from <EndMakeQuotient>
	ar0+=gr0 with gr1<<=1;				// ar1+gr1: ����� ����� ��� ��������� ������ ������ � �������
	ar2+=gr2 with gr7=false;
	push ar6,gr6;						// push ar6=Buffer64
	 wtw; //WTW_REG_DEPRICATED(gr7);						// �������� � WOPER -2*Divisor
	delayed goto ar0;
		rep 1 wfifo=[ar1++],ftw ;		// �������� 2h � WBUF
		nul;
		nul;
	// --- ����-�� ���������(���������) ������� (����������� ������� Buffer64)---
	// Qoutient[i]=sign([Buffer64+i]); i-����� ���� ��������
	.align;
	.repeat 64;
		VEC_DIV_STEP();
	.endrepeat;
	<EndVecDiv>
	rep 1 [ar6]=afifo with vfalse;		// ��������� ����������� VEC_DIV_STEP
	//--- ���������������� ���������� �������� ��������(63-��) ������ �������� ������� Buffer64 
	nb1 = gr7;				// �������� 2h � WOPER
	delayed goto ar2;
		pop ar6,gr6 ;						// pop ar6=Buffer64
		nul;
	.align;
	.repeat 64;
		rep 1 data=[ar6++] with vsum ,afifo,activate data;
	.endrepeat;
	<EndMakeQuotient>
	rep 1 data=[ar6++] with vsum ,afifo,activate data;
	with gr6;							//gr6=sign(Quotient)
	//------- ��������� �������� � ����� �������� -----------
	if >= delayed goto SkipResultNegation;
		rep 1 with afifo-1;				// ��������� �������� ���� �������� 
		rep 1 data=[ar1+=gr1] with afifo and data;	//  ��������� ������ ������ � ����� ����� ��������
	rep 1 with 0-afifo;					
	nul;
	<SkipResultNegation>
	rep 1 [ar5]=afifo;					// ar5=&Quotient
	pop ar6,gr6;
	pop ar2,gr2;
	pop ar1,gr1;
	pop ar0,gr0;
return;
.wait;

end ".text_nmpl�";
