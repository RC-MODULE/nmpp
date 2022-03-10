global _nmblas_sger : label;
extern _fpu_sger : label;

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


begin "text"
<_nmblas_sger>
	ar5 = ar7 - 2;
	push ar0,gr0;
	push ar1,gr1;
	push ar2,gr2;
	push ar3,gr3;
	push ar4,gr4;
	push ar6,gr6;


	gr4 = [--ar5];//load ROW ammaunt
	gr0 = [--ar5];//load COLLUM ammaunt
	gr7 = [--ar5];//load ALPHA
	ar2 = [--ar5];//address of vector x
	ar5--;//pass the inc x
	ar1 = [--ar5];//address of vector y
	ar5--;//pass the inc y
	ar0 = [--ar5];//address of matrix
	gr3 = [--ar5];//LDA
	
	delayed call _fpu_sger;
	ar6 = ar0;//the addres of result
	gr6 = gr3;//the LDA of result


	pop ar6,gr6;
	pop ar4,gr4;
	pop ar3,gr3;
	pop ar2,gr2;
	pop ar1,gr1;
	pop ar0,gr0;
	return;
end "text";