//------------------------------------------------------------------------
//
//  $Workfile:: activate_data.as $
//
//  ��������-��������� ����������
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:06 $
//
//! \if file_doc
//!
//! \file   activate_data.asm
//! \author ������ �������
//! \brief  ������� ���������� ����.
//!
//! \endif
//!
//------------------------------------------------------------------------

begin ".text_nmvcore"
    
    //------------------------------------------------------------------------
    //! \fn void vec_MaxVal( nmreg nb1, nmreg f1cr, nmreg ar0, nmreg gr0, nmreg ar4, nmreg gr5, nmreg ar6)
    //!
    //------------------------------------------------------------------------

.branch;
global vec_MaxVal:label;
<vec_MaxVal>
	push ar5,gr5 with gr7 = gr5>>5;
	with gr7--;
	if <= delayed goto CompareLT64; // if size<64
		rep 1 ram=[ar0];
		nul;

	
//	Begin Compare by rep32
	with gr7--;
	rep 32 data=[ar0++gr0]		with data;
	<Next_Compare_rep32_>								
		nul;
		rep 32 data,ram =[ar0++gr0]	with data - afifo;
	if <>0 delayed goto Next_Compare_rep32_ with gr7--;
		rep 32					with activate afifo and afifo;
		rep 32					with ram - afifo;
	
	rep 32 [ar4++]=afifo;
//	Begin Compare by rep32
//<CompareIn32V>
	rep 16 data=[--ar4]			with data;
	rep 16 data,ram =[--ar4]	with data - afifo;
	rep 16						with activate afifo and afifo;
	rep 16						with ram - afifo;
	rep 16 [ar4++]=afifo;
	
	// Buble maximum search by rep 8
	rep 8 data=[--ar4]			with data;
	rep 8 data,ram =[--ar4]		with data - afifo;
	rep 8						with activate afifo and afifo;
	rep 8						with ram - afifo;
	rep 8 [ar4++]=afifo;
	// Buble maximum search by rep 4
	rep 4 data=[--ar4]			with data;
	rep 4 data,ram =[--ar4]		with data - afifo;
	rep 4						with activate afifo and afifo;
	rep 4						with ram - afifo;
	rep 4 [ar4++]=afifo;
	// Buble maximum search by rep 2
	rep 2 data=[--ar4]			with data;
	rep 2 data,ram =[--ar4]		with data - afifo;
	rep 2						with activate afifo and afifo;
	rep 2						with ram - afifo;
	rep 2 [ar4++]=afifo;
	// Buble maximum search by rep 1
	rep 1 data=[--ar4]			with data;
	rep 1 data,ram =[--ar4]		with data - afifo;	
	rep 1						with activate afifo and afifo;
	rep 1						with ram - afifo;
	rep 1 [ar6],ram =afifo;

	with gr5<<=27;
	with gr5>>=27;				// number of longs to compare

<CompareLT64>
	pop ar5,gr5  with gr7 = gr5;
				 with gr7--;
	if <  return;

	rep 1 with ram;
	<Next_Compare_rep1>									
		nul;
		rep 1 data,ram =[ar0++gr0]	with data - afifo;
	if <>0 delayed goto Next_Compare_rep1 with gr7--;
		rep 1					with activate afifo and afifo;
		rep 1					with ram - afifo;

	delayed return;			
		rep 1 [ar6]=afifo;
		nul;
		nul;
.wait;




end ".text_nmvcore";
