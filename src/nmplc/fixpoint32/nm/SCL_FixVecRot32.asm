//***************************************************************************/
//*                                                                         */
//*                    Neuroprocessor NM6403 SDK v.1.2                      */
//*                                                                         */
//*				Signed Fixed Point 32-bit Routine                           */
//*                                                                         */
//*       œŒ¬Œ–Œ“ ¬≈ “Œ–¿ Õ¿ œÀŒ— Œ—“» ¬ ƒ≈ ¿–“Œ¬€’  ŒŒ–ƒ»Õ¿“¿’             */
//*                                                                         */
//*                                                                         */
//*                1999 (c) RC Module Inc., Moscow, Russia                  */
//***************************************************************************/

//!!!!!!!!!!!!!!!!!!! Ã≈Õﬂ“‹ «ƒ≈—‹ !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
const FIXPOINT=16; //œÓÎÓÊÂÌËÂ ‰‚ÓË˜ÌÓÈ ÚÓ˜ÍË ‚ 32-ı ‡Áˇ‰ÌÓÏ ÒÎÓ‚Â
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
global FixVecRot32 :label;
global FixSinCos32 :label;
global FixArcTan32 :label;
//import FIXMUL32,FIXMACROMUL32 from FixMacro.mlb;
import from macros.mlb;
//import WTW_REG from Regs.mlb;
//**********  Local ********************
data ".data_nmplc_L"
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
end ".data_nmplc_L";
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
begin ".text_nmplÒ"
//////////////////////////////////////////////////////////////////////////////
//                                                                          //
//                     Signed Fixed  Point                                  //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////
<FixVecRot32>
.branch;
	//gr0 -Old_X
	//gr1 -New_X
	//gr2 -Shifted gr4;
	//gr3 -Angle
	//gr4 -Old_Y
	//gr5 -New_Y
	ar1=FixArctanTable with gr3-=gr3;
	ar2=NormMul with gr7;
	nb1=gr3;
	sb=gr3;
	rep 1 wfifo=[ar2++],ftw;
	if < delayed skip 6	with gr1=gr4;
		[Void]=gr7 with gr2=gr0;
	delayed skip 6 with gr0-=gr1;
		gr3=[ar1++] with gr4+=gr2;
		ar5=sp with gr7-=gr3;
	//---------------------
	nul;
	ar5=sp with gr0+=gr1;
	gr3=[ar1++] with gr4-=gr2;
	gr7+=gr3;

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
	[ar2++]=gr0 with gr7 = gr0 A>>31;  
	[ar2++]=gr7;
	[ar2++]=gr4 with gr7 = gr4 A>>31;
	[ar2++]=gr7 with gr3-=gr3;
	nb1= gr3; 
	wtw; 
	rep 2 ram,data=[--ar2] with vsum ,data,0;
	rep 2 [ar2++]=afifo;
	ar0,gr0=[--ar2];
	ar4,gr4=[--ar2];
delayed return;	
	[ar5++]=gr0;
	[ar5++]=gr4;
.wait;
//////////////////////////////////////////////////////////////////////////////
//                                                                          //
//                     Signed Fixed  Point                                  //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////
<FixSinCos32>
.branch;
	
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
delayed return;	
	[ar5++]=gr0;//x-cos
	[ar5++]=gr4;//y-sin
	nul;
.wait;




end ".text_nmplÒ";
