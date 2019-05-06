//***************************************************************************/
//*                                                                         */
//*                    Neuroprocessor NM6403 SDK v.1.2                      */
//*                                                                         */
//*                                                                         */
//*                 ��������� ������                                        */
//*                                                                         */
//*                                                                         */
//* Date:25.01.2000     (c) RC Module Inc., Moscow, Russia                  */
//***************************************************************************/
import from macros.mlb;

data ".data_nmpls_L"
	//----- input parameters--------
	SrcBuffer:word;		// �������� ������ 
	GBuffer:word;		// ����� ���������� ������� �� ���������� ����
	LBuffer:word;		// ����� ���������� ������� �� ��������� ����
	DstBuffer:word;		// �������������� ������ 
	Length64:word;		// ����� ��������� ������� � 64�. ������ 
	WindowSize:word;	// ������ ����������� ����
	Median:word;		// ����� ����������� �������
	//------------------------------
	Length32:word;		// ����� ��������� ������� � 32�. ������ 
	BlocksBy32:word;	// ����� ��������� ������� � ������ �� 32-� 64�. �������� 
end ".data_nmpls_L";
data ".data_nmpls_G"
	ActivateMask:long=7FFF7FFF7FFF7FFFhl;
	FFFFx4 :long[4]=(
		0000000000000FFFFhl,
		000000000FFFF0000hl,
		00000FFFF00000000hl,
		0FFFF000000000000hl
		);
	SelectMedian:long [17]=(
		00000000000000000hl,
		00001000100010001hl,
		00002000200020002hl,
		00003000300030003hl,
		00004000400040004hl,
		00005000500050005hl,
		00006000600060006hl,
		00007000700070007hl,
		00008000800080008hl,
		00009000900090009hl,
		0000A000A000A000Ahl,
		0000B000B000B000Bhl,
		0000C000C000C000Chl,
		0000D000D000D000Dhl,
		0000E000E000E000Ehl,
		0000F000F000F000Fhl,
		00010001000100010hl
					 );

end ".data_nmpls_G";
begin ".text_nmpls"
//////////////////////////////////////////////////////////////////////////////
//                                                                          //
//           ������ ���������� ����������� ����                             //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

//	void SIG_XMedian( nm
//				void*	SrcBuffer,	// �������� ��c���� (vt16)
//					void*	DstBuffer,	// �������������� ������ (vt16)
//			const	int		WindowSize,	// ������ ����������� ����
//			const	int		Median,		// ����� ����������� �������
//			const	int		Length64,	// ����� ��������� ������� � 64�. ��������
//					void*	LBuffer,	// ��������� ����� ������� Length64*WindowSize
//					void*	GBuffer		// ��������� ����� ������� Length64*WindowSize
//					);	
// 
// Length64 - ������ ���� ������ 32-��
// Median=1,2...16
// WindowSize/Length64 - Nicks 
// 4/32		- 1251
// 16/450	- 74591 (57600)	10.36*N*K
// 16/1024	- 170064		10.38*N*K
// => 10.38*1800/4*16=74736 ������ ~=1.9 �� (40���)

// nSize=256
// nWindowSize=9
// LLLL 26698
// LGLG 23787

// nSize=512
// nWindowSize=64
// 351891 
//! \fn void SIG_XMedian(v4nm16s* pSrc4v, v4nm16s* pDst4v, int nWindowSize, int nXMedian, int nSize, void* pTmp0, void* pTmp1)
//! \perfinclude _SIG_Median3__FUiUiUi.html
global _void._.8.8SIG_XMedian.1class._v4nm16s._.0.9._class._v4nm16s._.0.9._int.9._int.9._int.9._void._.0.9._void._.0.2:label;
<_void._.8.8SIG_XMedian.1class._v4nm16s._.0.9._class._v4nm16s._.0.9._int.9._int.9._int.9._void._.0.9._void._.0.2>



.branch;
	ar5=sp-2;
	PUSH_REGS();   
	gr5=[--ar5];				// SrcBuffer-�������� ��c���� (vt16)
	[SrcBuffer]=gr5;
	gr5=[--ar5];				// DstBuffer-�������������� ������ (vt16)
	[DstBuffer]=gr5;
	gr5=[--ar5];				// WindowSize - ������ ����������� ����
	[WindowSize]=gr5;
	gr5=[--ar5];				// Median	-����� ����������� �������
	[Median]=gr5;				
	gr5=[--ar5];				// Length64	-����� ��������� ������� � 64�. ��������
	[Length64]=gr5;				
	gr5=[--ar5];				// LBuffer	-��������� ����� ������� Length64*WindowSize
	[LBuffer]=gr5;				
	gr5=[--ar5];				// GBuffer	-��������� ����� ������� Length64*WindowSize
	[GBuffer]=gr5;	

	f1cr=80008000h;	
	gr4=80008000h;
	sb=00020002h;
	ar4=FFFFx4;
	nb1=gr4;
	rep 4 wfifo=[ar4++],ftw,wtw;	
	//WTW_REG_DEPRICARTED(gr4);
	

	gr5=[Length64];
	gr6=gr5 with gr5<<=1;
	[Length32]=gr5 with gr6>>=5;
	[BlocksBy32]=gr6;
	
	//////////////////////////////////////////////////////////
	// ���������� �������������� ���������� �������
	//
	//
	CalcDiffSignsBy32:label;
	gr0=64;
	gr2=2;							// �������� ��� ������ ����������� ���� ������ �� 1 ������ 
	gr3=[Length32];					// �������� ��� ������ �� ���� ������ ���� � ������� ���������� �������
	ar0=[SrcBuffer];
	gr5=[BlocksBy32];
	gr4=[WindowSize];
	gr6=[GBuffer];
	ar5=CalcDiffSignsBy32;
	with gr4--;
	with gr4--;
	<CalcColumnOfDiffSignsBy32>
		push ar6,gr6;
		gr1=ar0 with gr7=gr4;
		rep 32 ram=[ar0++];
		<CalcDiffSignsBy32>
			ar6=gr6 with gr1+=gr2 noflags;	// ����� ���� �� 1 64�. ������ ������
			ar1=gr1 with gr6+=gr3 noflags;	// ����� �� ���� ������ ���� � ������� ���������� �������
		if <>0 delayed goto ar5 with gr7--;
			rep 32 data=[ar1++] with ram-data;
			rep 32 with activate afifo;
			rep 32 [ar6++]=afifo;
		with gr5--;
	if > delayed goto CalcColumnOfDiffSignsBy32;
		pop ar6,gr6;
		gr6+=gr0;
	/////////////////////////////////////////////////////////
	//  ������������ ����� � ������� � ��������������� ������� 
	//
	//
	ar6=SelectMedian;
	gr4=[WindowSize];
	gr6=[Median];
	gr6=gr4-gr6;
	gr6<<=1;
	ar6+=gr6;
	rep 32 ram=[ar6];
	gr3=[Length32];					// �������� ��� ������ �� ���� ������ ���� � ������� ���������� �������
	gr2=-2;
	gr2+=gr3;
	ar1=[LBuffer];
	ar6=[GBuffer];
	gr0=[BlocksBy32];
	gr4--;
	gr4--;
	gr4--;
	<CreateSummColumnBy32>
		gr6=ar6;					// GBuffer-DiffArray
		gr5=gr6-gr3;				// GBuffer-DiffArray
		rep 32 data=[ar6++] with ram+data;
		push ar6,gr6;
		with gr6+=gr3;
		gr1=ar1 with gr7=gr4;
		<BaseSummBy32>
		if <>0 delayed goto BaseSummBy32 with gr7--;
			ar6=gr6 with gr6+=gr3 noflags;	
			rep 32 data=[ar6++] with afifo+data;
		rep 32 [ar1++]=afifo with afifo-1;
		push ar1,gr1;
		gr1+=gr3;
		gr6-=gr3;
		gr5+=gr2;
		with gr7=gr4;
		<ContinueSumm>
			ar1=gr1 with gr1+=gr3 noflags;
			ar6=gr6 with gr6-=gr3 noflags;
			ar5=gr5 with gr5+=gr2 noflags;
			rep 32 data=[ar6++] with afifo-data;
		if <>0 delayed goto ContinueSumm with gr7--;
			rep 32 data=[ar5++] with afifo-data;
			rep 32 [ar1++]=afifo with afifo-1;
					
		ar1=gr1 with gr1+=gr3 noflags;
		ar6=gr6 with gr6-=gr3 noflags;
		ar5=gr5 with gr5+=gr2 noflags;
		rep 32 data=[ar6++] with afifo-data;
		rep 32 data=[ar5++] with afifo-data;
		rep 32 [ar1++]=afifo;
		pop ar1,gr1;
		with gr0--;	
	if <>0 delayed goto CreateSummColumnBy32;
		pop ar6,gr6;
		nul;
	//////////////////////////////////////////////////////////
	//  �������� ����� ��� ��������� �������� �������
	//  
	f1cr=0FFFEFFFEh;
	
	ar6=ActivateMask;
	rep 32 ram=[ar6];
	ar0=[LBuffer];
	ar6=[GBuffer];
	gr4=[WindowSize];
	gr4--;
	with gr7=gr4;
	gr5=[BlocksBy32];
	<CreateMaskBy32>
		if <>0 delayed goto CreateMaskBy32 with gr7--;
			rep 32 data=[ar0++] with vsum ram, activate data,0;
			rep 32 [ar6++]=afifo;
		with gr5--;
	if <>0 delayed goto CreateMaskBy32;
		with gr7=gr4;
		nul;

	/////////////////////////////////////////////////////////
	// ������ ��������������� ���������������� �������
	//
	gr2=2;
	ar0=[SrcBuffer];
	ar6=[GBuffer];
	gr3=[Length32];
	gr3++;
	gr3++;
	ar1=[DstBuffer];
	gr5=[BlocksBy32];
	gr4=[WindowSize];
	gr4--;
	gr4--;
	
	
	<MaskColumnResultBy32>
		gr6=ar6 ;
		gr0=ar0;
		with gr6+=gr3;
		with gr0+=gr2;
		rep 32 ram=[ar0++];
		rep 32 data=[ar6++] with mask data,0,ram;
		push ar0,gr0;
		push ar6,gr6;
		with gr7=gr4;
		<MaskResultBy32>
			ar0=gr0 with gr0+=gr2 noflags;
			ar6=gr6 with gr6+=gr3 noflags;
		if <>0 delayed goto MaskResultBy32 with gr7--;
			rep 32 ram=[ar0++];
			rep 32 data=[ar6++] with mask data,afifo,ram;
		rep 32 [ar1++]=afifo;
		with gr5--;
	if <>0 delayed goto MaskColumnResultBy32;
		pop ar6,gr6;
		pop ar0,gr0;
		
	POP_REGS();
return;
.wait;


end ".text_nmpls";
