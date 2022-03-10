//***************************************************************************/
//*                                                                         */
//*                    Neuroprocessor NM6403 SDK v.1.2                      */
//*                                                                         */
//*				Signed Fixed Point 64-bit Routines                          */
//*                                                                         */
//*             Вычисление синуса,косинуса и арктангенса в Fixed-Point 64   */
//*                                                                         */
//*                1999 (c) RC Module Inc., Moscow, Russia                  */
//***************************************************************************/


//**********  Local ********************
data ".data_nmplc_L"

FixAtanTable64 :long[33]=
// FixAtanTable64[i]=atan(pow(2,-i))
(
0C90FDAA2hl,
076B19C15hl,
03EB6EBF2hl,
01FD5BA9Ahl,
0FFAADDBhl,
07FF556Ehl,
03FFEAABhl,
01FFFD55hl,
0FFFFAAhl,
07FFFF5hl,
03FFFFEhl,
01FFFFFhl,
0FFFFFhl,
07FFFFhl,
03FFFFhl,
01FFFFhl,
0FFFFhl,
07FFFhl,
03FFFhl,
01FFFhl,
0FFFhl,
07FFhl,
03FFhl,
01FFhl,
0FFhl,
07Fhl,
03Fhl,
020hl,
010hl,
08hl,
04hl,
02hl,
01hl
);
end ".data_nmplc_L";
//**********  Global ********************
//*********** TEXT ****************
//import PUSH_REGS,POP_REGS from regs.mlb;
//import FIXSHIFTAR64,FIXADD64,FIXSUB64 from FixMacro64.mlb;
import from macros.mlb;

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
//      Макрос поворота вектора на угол из таблицы FixAtanTable             //
//       (Вектор доворачивается от О град. к заданному углу)                //
//      Проекция вектора но оси x,y определяет Sin и Cos                    //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////
macro SINCOSROTATE64(Shift)
own NegTeta:label;
own JumpNextRotate:label;
	/////////////////////////////////////////////////////////////
	// y[0] = 0;
	// x[0] = 0.607..;
	// x[i+1] = x[i] - sign(theta)*(y[i]*pow(2.0,(double)(-i)));
	// y[i+1] = y[i] + sign(theta)*(x[i]*pow(2.0,(double)(-i)));
	// theta -= sign(theta)*arctantable[i];
	////////////// -обозначения переменных //////////////////////
	// x[i+1]={gr0,gr1}
	// y[i+1]={gr2,gr3}
	// (y[i]*pow(2.0,(double)(-i))={gr4,gr5}
	// (x[i]*pow(2.0,(double)(-i))={gr6,gr7}
	// Theta={gr6,gr7} (хранится в стеке)
	//////////////////////////////////////////////////////////////
if < delayed goto NegTeta;
	gr5=[ar0++];
	gr4=[ar0++];
	FIXSUB64(gr6,gr7,gr4,gr5,gr6,gr7);
	[ar5++]=gr7;
	[ar5++]=gr6;
	FIXSHIFTAR64(gr2,gr3,gr4,gr5,Shift);
	FIXSHIFTAR64(gr0,gr1,gr6,gr7,Shift);
	FIXSUB64(gr0,gr1,gr4,gr5,gr0,gr1);	
	FIXADD64(gr2,gr3,gr6,gr7,gr2,gr3);
	delayed goto JumpNextRotate;
		gr6=[--ar5];
		gr7=[--ar5] with gr6;
<NegTeta>	
	FIXADD64(gr6,gr7,gr4,gr5,gr6,gr7);
	[ar5++]=gr7;
	[ar5++]=gr6;
	FIXSHIFTAR64(gr2,gr3,gr4,gr5,Shift);
	FIXSHIFTAR64(gr0,gr1,gr6,gr7,Shift);
	FIXADD64(gr0,gr1,gr4,gr5,gr0,gr1);	
	FIXSUB64(gr2,gr3,gr6,gr7,gr2,gr3);
	gr6=[--ar5];
	gr7=[--ar5] with gr6;
<JumpNextRotate>
end SINCOSROTATE64;

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
//      Макрос поворота вектора на угол из таблицы FixAtanTable             //
//      Вектор доворачивается от (1,Y) до (X,0) ,                           //
//      угол поворота соотв. арктангенсу                                    //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////
macro ATANROTATE64(Shift)
own NegTeta:label;
own JumpNextRotate:label;
	//////////////////////////////////////////////////////////////
	//	y[0] = Y;
	//	x[0] = 1;
	//	x[i+1] = x[i] + sign(y[i])*(y[i]*pow(2.0,(double)(-i)));
	//	y[i+1] = y[i] - sign(y[i])*(x[i]*pow(2.0,(double)(-i)));
	//	theta += sign(y[i])*arctantable[i];
	//////////////  обозначения переменных //////////////////////
	// x[i+1]={gr0,gr1}
	// y[i+1]={gr2,gr3}
	// (y[i]*pow(2.0,(double)(-i))={gr4,gr5}
	// (x[i]*pow(2.0,(double)(-i))={gr6,gr7}
	// Theta={gr6,gr7} (хранится в стеке)
	//////////////////////////////////////////////////////////////
if < delayed goto NegTeta;
	gr5=[ar0++];
	gr4=[ar0++];
	FIXADD64(gr6,gr7,gr4,gr5,gr6,gr7);
	[ar5++]=gr7;
	[ar5++]=gr6;
	FIXSHIFTAR64(gr2,gr3,gr4,gr5,Shift);
	FIXSHIFTAR64(gr0,gr1,gr6,gr7,Shift);
	FIXADD64(gr0,gr1,gr4,gr5,gr0,gr1);	
	FIXSUB64(gr2,gr3,gr6,gr7,gr2,gr3);
	delayed goto JumpNextRotate;
		gr6=[--ar5];
		gr7=[--ar5] with gr2;
<NegTeta>	
	FIXSUB64(gr6,gr7,gr4,gr5,gr6,gr7);
	[ar5++]=gr7;
	[ar5++]=gr6;
	FIXSHIFTAR64(gr2,gr3,gr4,gr5,Shift);
	FIXSHIFTAR64(gr0,gr1,gr6,gr7,Shift);
	FIXSUB64(gr0,gr1,gr4,gr5,gr0,gr1);	
	FIXADD64(gr2,gr3,gr6,gr7,gr2,gr3);
	gr6=[--ar5];
	gr7=[--ar5] with gr2;
<JumpNextRotate>
end ATANROTATE64;

begin ".text_nmplс"


//////////////////////////////////////////////////////////////////////////////
//                                                                          //
//  Вычисление арктангенса в Fixed Point 64                                 //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

//! \fn long nmppcFixArcTan64(long nArg)
//! 
//! \perfinclude _nmppcFixArcTan64__Fl.html
global _nmppcFixArcTan64 :label; 
<_nmppcFixArcTan64>
.branch;
	ar5=sp-2;
	push ar0,gr0 with gr6-=gr6;
    push ar1,gr1 with gr1-=gr1;
    push ar2,gr2 with gr0=gr1+1;
    push ar3,gr3 with gr2-=gr2;
    push ar4,gr4 with gr3-=gr3;
	push ar5,gr5 with gr4-=gr4;
	
	ar0=FixAtanTable64 with gr5-=gr5;
	// Передача параметров
	gr2=[--ar5] with gr7-=gr7;		// Hi(long Input)
	gr3=[--ar5] with gr2;			// Lo(long Input)

	ATANROTATE64(0);
	ATANROTATE64(1);
	ATANROTATE64(2);
	ATANROTATE64(3);
	ATANROTATE64(4);
	ATANROTATE64(5);
	ATANROTATE64(6);
	ATANROTATE64(7);
	ATANROTATE64(8);
	ATANROTATE64(9);
	ATANROTATE64(10);
	ATANROTATE64(11);
	ATANROTATE64(12);
	ATANROTATE64(13);
	ATANROTATE64(14);
	ATANROTATE64(15);
	ATANROTATE64(16);
	ATANROTATE64(17);
	ATANROTATE64(18);
	ATANROTATE64(19);
	ATANROTATE64(20);
	ATANROTATE64(21);
	ATANROTATE64(22);
	ATANROTATE64(23);
	ATANROTATE64(24);
	ATANROTATE64(25);
	ATANROTATE64(26);
	ATANROTATE64(27);
	ATANROTATE64(28);
	ATANROTATE64(29);
	ATANROTATE64(30);
	ATANROTATE64(31);
	ATANROTATE64(32);
					// Output
	pop ar5,gr5;	// gr7=Lo(long Atan(Input))
    pop ar4,gr4;	// gr6=Hi(long Atan(Input))
    pop ar3,gr3;
    pop ar2,gr2;
    pop ar1,gr1;
    pop ar0,gr0;

return;	
.wait;
end ".text_nmplс";


