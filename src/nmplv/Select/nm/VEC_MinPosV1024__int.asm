begin ".text_nmplv"

//--------------------------------------------------------------------
//! \fn int VEC_MinPosV1024(int* pSrcVec,int nStride,int& nPos);
//!
//! \perfinclude _VEC_MinPosV1024__FPiiRi.html
//--------------------------------------------------------------------


global _int._.8.8VEC_MinPosV1024.1int._.0.9._int.9._int._.6.2 :label;
<_int._.8.8VEC_MinPosV1024.1int._.0.9._int.9._int._.6.2>
.branch;

	ar5=ar7-2;
	push ar0,gr0;
	push ar1,gr1;
	push ar2,gr2;
	push ar4,gr4;
	push ar5,gr5;
	push ar6,gr6;
		
	ar0 = [--ar5];	// Src
	gr0 = [--ar5];	// Stride
	ar2 = [--ar5];	// Pos
	
	gr7 = [ar0++gr0] with gr4 = false;	// Min= SAD[0]
	gr1 = [ar0++gr0];					// Read SAD[1]
	ar4 = gr4 with gr6 = gr7-gr1;		// Min-SAD[1]
	
	gr5=62; 
	<Next8>
		.repeat 7;
		if <= delayed skip 4 with gr4++;	// Inc Index
			gr2=[ar0++gr0];				// Read SAD[2]
			gr6=gr7-gr2;				// Min -SAD[2]
		ar4=gr4 with gr7=gr1;			// set MinIndex, set new Min
				with gr6=gr7-gr2;		
			
		if <= delayed skip 4 with gr4++;	// Inc Index
			gr1=[ar0++gr0];				// Read SAD[7]
			gr6=gr7-gr1;				// Min -SAD[7]
		ar4=gr4 with gr7=gr2;			// set MinIndex, set new Min
				with gr6=gr7-gr1;		
		.endrepeat;
		//----- one more rep ---------
		if <= delayed skip 4 with gr4++;	// Inc Index
			gr2=[ar0++gr0];				// Read SAD[2]
			gr6=gr7-gr2;				// Min -SAD[2]
		ar4=gr4 with gr7=gr1;			// set MinIndex, set new Min
		with gr6=gr7-gr2;		
			
		if <= delayed skip 4 with gr4++;	// Inc Index
			gr1=[ar0++gr0] with gr5--;		// Read SAD[7]
			gr6=gr7-gr1 noflags;			// Min -SAD[7]
		ar4=gr4 with gr7=gr2 noflags;			// set MinIndex, set new Min
		with gr6=gr7-gr1 noflags;		
		//-------------------------------
	if <>0 delayed goto Next8;
			with gr6;
			nul;

.repeat 7;
	if <= delayed skip 4 with gr4++;	// Inc Index
		gr2=[ar0++gr0];				// Read SAD[2]
		gr6=gr7-gr2;				// Min -SAD[2]
	ar4=gr4 with gr7=gr1;			// set MinIndex, set new Min
			with gr6=gr7-gr2;		
		
	if <= delayed skip 4 with gr4++;	// Inc Index
		gr1=[ar0++gr0];				// Read SAD[7]
		gr6=gr7-gr1;				// Min -SAD[7]
	ar4=gr4 with gr7=gr2;			// set MinIndex, set new Min
			with gr6=gr7-gr1;		
.endrepeat;

	if <= delayed skip 4 with gr4++;	// Inc Index
		nul;						// Read SAD[2]
		nul;				// Min -SAD[2]
	ar4=gr4 with gr7=gr1;			// set MinIndex, set new Min
			nul;		
		

	[ar2]=ar4;

	pop ar6,gr6;
	pop ar5,gr5;
	pop ar4,gr4;
	pop ar2,gr2;
	pop ar1,gr1;
	pop ar0,gr0;
	
	return;
.wait;

end ".text_nmplv";
