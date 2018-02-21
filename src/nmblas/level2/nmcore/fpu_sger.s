global _fpu_sger : label;

//void nmblas_srefger
//(
//   const int                  M,//ROW
//   const int                  N,//COLUMN
//   const float                ALPHA,
//   const float                * X,
//   const int                  INCX,
//   const float                * Y,
//   const int                  INCY,
//   float                      * A,
//   const int                  LDA
//)

	//gr4 = [--ar5];//load ROW ammaunt
	//gr0 = [--ar5];//load COLLUM ammaunt
	//ar2 = [--ar5];//address of vector x
	//ar5--;//pass the inc x
	//ar1 = [--ar5];//address of vector y
	//ar5--;//pass the inc y
	//ar0 = [--ar5];//address of matrix
	//gr3 = [--ar5];//LDA

nobits "nobits"
	load2duplicate : word[2];
end "nobits";


begin "text"
<_fpu_sger>
	//list of purpuse of registers
	//free to use sir,vlen
	//ar3 uses to save ar0(address of the matrix)
	//ar5 keaps the addres of buff
	//ar4 saves gr4(row counter);
	//gr1 uses to save ar6(address to wrt result)
	//gr2 = 1

	gr2 = 1; 
	ar5 = load2duplicate;
	[ar5++] = gr7; 
	[ar5++] = gr7;	
	fpu 0 rep 1 vreg0 = [--ar5];//load ALPHA
	
	gr7 = gr0 << 26;
	gr7 = gr7 >> 27;//reminder of collums
	vlen = gr7;
	gr0 = gr0 >> 6;//qoutient of collums
	
	gr1 = ar6;//init result address keaper
	if =0 delayed goto REMINDER;
	ar4 = gr4;//init row counter keaper
	ar3 = ar0;//save the matrix address 

<LOOP_COLUME2COLUME>
	gr4 = ar4;
	fpu 0 rep 32 vreg3 = [ar1++];//load the vec Y
<LOOP_ROW2ROW>
	gr7 = [ar2++gr2];//load x 2 dublicate
	[ar5++] = gr7;
	[ar5++] = gr7;
	ar6 = gr1;
	ar0 = ar3;
	gr1 = ar6;
	fpu 0 rep 1 vreg1 = [--ar5];//load dublicated x
	fpu 1 rep 32 vreg0 = [ar0++];//load the matrix
	fpu 0 .float vreg2 = vreg1*vreg0;
	fpu 0 .float vreg4 = vreg3*.retrive(vreg2);//got ALPHA*x[i]*vecY
	fpu 1 vreg1 = fpu 0 vreg4;
	fpu 1 .float vreg2 = vreg0 + vreg1;
	fpu 1 rep 32 [ar6++] = vreg2;//upload the result
	gr4--;
	if <>0 delayed goto LOOP_ROW2ROW;
	ar3 = ar3 + gr3;//next row to download information
	gr1 = gr1 + gr3;//next row to upload the result
	
	///////next set of collums
	ar3 = ar0 with gr3 = -gr3 noflags;
	gr0--;
	if <>0 delayed goto LOOP_COLUME2COLUME with gr2 = -gr2 noflags;
	gr1 = ar6;
	ar2 = ar2 + gr2; 


<REMINDER>
	gr4 = ar4;
	gr7 = vlen;
	gr7;
	if =0 delayed goto END;
	gr7--;
	vlen = gr7;
	fpu 0 rep vlen vreg3 = [ar1++];//load the vec Y
<LOOP_ROW2ROW_REM>
	gr7 = [ar2++gr2];//load x 2 dublicate
	[ar5++] = gr7;
	[ar5++] = gr7;
	ar0 = ar3;
	ar6 = gr1;
	gr1 = ar6;
	fpu 0 rep 1 vreg1 = [--ar5];//load dublicated x
	fpu 1 rep vlen vreg0 = [ar0++];//load the matrix
	fpu 0 .float vreg2 = vreg1*vreg0;
	fpu 0 .float vreg4 = vreg3*.retrive(vreg2);//got ALPHA*x[i]*vecY
	fpu 1 vreg1 = fpu 0 vreg4;
	fpu 1 .float vreg2 = vreg0 + vreg1;
	fpu 1 rep vlen [ar6++] = vreg2;//upload the result
	gr4--;
	if <>0 delayed goto LOOP_ROW2ROW_REM;
	ar3 = ar3 + gr3;//next row to download information
	gr1 = gr1 + gr3;//next row to upload the result

	//gr7 = gr4;

<END>
	return;
end "text";
