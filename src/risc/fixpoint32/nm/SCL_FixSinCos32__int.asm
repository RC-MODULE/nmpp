//***************************************************************************/
//*                                                                         */
//*                    Neuroprocessor NM6403 SDK v.1.2                      */
//*                                                                         */
//*				Signed Fixed Point 32-bit Routine                           */
//*                                                                         */
//*       ПОВОРОТ ВЕКТОРА НА ПЛОСКОСТИ В ДЕКАРТОВЫХ КООРДИНАТАХ             */
//*                                                                         */
//*                                                                         */
//*                1999 (c) RC Module Inc., Moscow, Russia                  */
//***************************************************************************/

//!!!!!!!!!!!!!!!!!!! МЕНЯТЬ ЗДЕСЬ !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
const FIXPOINT=16; //Положение двоичной точки в 32-х разрядном слове
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
import from macros.mlb;
//**********  Local ********************
data "LocalSRAM"
	NormMul:long=9B7496D6hl;
	UnNorm:long[2];
	
	Void:word;
	FixArctanTable:word[16]=
	(
		0C90Fh,
		076B1h,
		03EB6h,
		01FD5h,
		0FFAh,
		07FFh,
		03FFh,
		01FFh,
		0FFh,
		07Fh,
		03Fh,
		01Fh,
		0Fh,
		07h,
		03h,
		01h
	);
end "LocalSRAM";
//**********  Global ********************
data "GlobalSRAM"
end "GlobalSRAM";
//--------------------------------------------
macro ROTATE(Shift)
	if < delayed skip 6	with gr1=gr4 A>>Shift;
		[Void]=gr7 with gr2=gr0 A>>Shift;
	delayed skip 6 with gr0-=gr1;
		gr3=[ar1++] with gr4+=gr2;
		gr7-=gr3;
	//---------------------
	nul;
	gr0+=gr1;
	gr3=[ar1++] with gr4-=gr2;
	gr7+=gr3;
end ROTATE;
//-------------------------------------------
macro ATANROTATE(Shift)
	if < delayed skip 6	with gr1=gr4 A>>Shift;
		[Void]=gr7 with gr2=gr0 A>>Shift;
	delayed skip 6 with gr0+=gr1;
		gr3=[ar1++] with gr4-=gr2;
		gr7+=gr3 noflags;
	//---------------------
	nul;
	gr0-=gr1;
	gr3=[ar1++] with gr4+=gr2;
	gr7-=gr3 noflags;
end ATANROTATE;

//*********** TEXT ****************
begin ".text_nmplс"


//! \fn void nmppcFixSinCos32(int nArg, int* pnSin, int* pnCos)
//!
//! \perfinclude _nmppcFixSinCos32__FiPiPi.html

global _nmppcFixSinCos32 :label;
<_nmppcFixSinCos32>
.branch;
	ar5 = sp-2;
	push ar0,gr0;
	push ar1,gr1;
	push ar2,gr2;
	push ar3,gr3;
	push ar4,gr4;
	push ar5,gr5;
	push ar6,gr6;
	
	gr7 = [--ar5];	// nArg
	ar6 = [--ar5];  // pnSin
	gr6 = [--ar5];	// pnCos 
	//gr0 -Xi
	//gr1 -Shifted gr4;
	//gr3 - +/- Angle=Arctan(pow(2,-i))
	//gr4 -Yi
	//gr5 -New_Y
	//gr2 -Shifted gr0
	//gr7 - Angle
	gr0=09B74h with gr4-=gr4;
	ar1=FixArctanTable with gr7;
	//ROTATE(0)
	if < delayed skip 6	with gr1=gr4;
		[Void]=gr7 with gr2=gr0;
	delayed skip 6 with gr0-=gr1;
		gr3=[ar1++] with gr4+=gr2;
		ar5=sp with gr7-=gr3;
	nul;
	ar5=sp with gr0+=gr1;
	gr3=[ar1++] with gr4-=gr2;
	gr7+=gr3;
	//---------------------

	ROTATE(1);
	ROTATE(2);
	ROTATE(3);
	ROTATE(4);
	ROTATE(5);
	ROTATE(6);
	ROTATE(7);
	ROTATE(8);
	ROTATE(9);
	ROTATE(10);
	ROTATE(11);
	ROTATE(12);
	ROTATE(13);
	ROTATE(14);
	ROTATE(15);
	
	[ar6]=gr4; //sin
	[gr6]=gr0; //cos

	pop ar6,gr6;
	pop ar5,gr5;
	pop ar4,gr4;
	pop ar3,gr3;
	pop ar2,gr2;
	pop ar1,gr1;
	pop ar0,gr0;
	
return;	
	//[ar5++]=gr0;//x-cos
	//[ar5++]=gr4;//y-sin
.wait;
//////////////////////////////////////////////////////////////////////////////
//                                                                          //
//                     Signed Fixed  Point                                  //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////
<FixArcTan32>
.branch;
	//gr0 -Xi
	//gr1 -Shifted gr4;
	//gr3 - +/- Angle=Arctan(pow(2,-i))
	//gr4 -Yi
	//gr5 -New_Y
	//gr2 -Shifted gr0
	//gr7 - Angle
	gr0=10000h with gr7-=gr7;
	ar1=FixArctanTable with gr4;
	//ROTATE(0)
	if < delayed skip 6	with gr1=gr4;
		[Void]=gr7 with gr2=gr0;
	delayed skip 6 with gr0+=gr1;
		gr3=[ar1++] with gr4-=gr2;
		with gr7+=gr3 noflags;
	nul;
	gr0-=gr1;
	gr3=[ar1++] with gr4+=gr2;
	gr7-=gr3 noflags;
	//---------------------

	ATANROTATE(1);
	ATANROTATE(2);
	ATANROTATE(3);
	ATANROTATE(4);
	ATANROTATE(5);
	ATANROTATE(6);
	ATANROTATE(7);
	ATANROTATE(8);
	ATANROTATE(9);
	ATANROTATE(10);
	ATANROTATE(11);
	ATANROTATE(12);
	ATANROTATE(13);
	ATANROTATE(14);
	ATANROTATE(15);
return;	


.wait;
end ".text_nmplс";
