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
//             Одновременное вычисление синуса и косинуса  в Fixed Point 64 //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////
//   !!!! аргумент должен лежать в пределах [-pi/2;+pi/2]


//! \fn void nmppcFixSinCos64(long nArg, long* pnSin, long *pnCos)
//! 
//! \perfinclude _nmppcFixSinCos64__FlPlPl.html
global _nmppcFixSinCos64 :label; 
<_nmppcFixSinCos64>
.branch;
	ar5=sp-2;

	push ar0,gr0;
    push ar1,gr1 with gr0-=gr0;
    push ar2,gr2;
    push ar3,gr3 with gr2-=gr2;
    push ar4,gr4 with gr3-=gr3;
	push ar5,gr5 with gr4-=gr4;
	
	gr1=9B74EDA8h;
	ar0=FixAtanTable64 ;
	// Передача параметорв
	gr6=[--ar5] with gr5-=gr5;	// Целая часть угла   (Hi(long Angle))
	gr7=[--ar5] with gr6;		// Дробная часть угла (Lo(long Angle))
	ar1=[--ar5];//Sin
	ar2=[--ar5];//Cos
	

	SINCOSROTATE64(0);
	SINCOSROTATE64(1);
	SINCOSROTATE64(2);
	SINCOSROTATE64(3);
	SINCOSROTATE64(4);
	SINCOSROTATE64(5);
	SINCOSROTATE64(6);
	SINCOSROTATE64(7);
	SINCOSROTATE64(8);
	SINCOSROTATE64(9);
	SINCOSROTATE64(10);
	SINCOSROTATE64(11);
	SINCOSROTATE64(12);
	SINCOSROTATE64(13);
	SINCOSROTATE64(14);
	SINCOSROTATE64(15);
	SINCOSROTATE64(16);
	SINCOSROTATE64(17);
	SINCOSROTATE64(18);
	SINCOSROTATE64(19);
	SINCOSROTATE64(20);
	SINCOSROTATE64(21);
	SINCOSROTATE64(22);
	SINCOSROTATE64(23);
	SINCOSROTATE64(24);
	SINCOSROTATE64(25);
	SINCOSROTATE64(26);
	SINCOSROTATE64(27);
	SINCOSROTATE64(28);
	SINCOSROTATE64(29);
	SINCOSROTATE64(30);
	SINCOSROTATE64(31);
	SINCOSROTATE64(32);
	
	[ar1++]=gr3;//LoSin
	[ar1++]=gr2;//HiSin
	[ar2++]=gr1;//LoCos
	[ar2++]=gr0;//HiCos
	pop ar5,gr5;
    pop ar4,gr4;
    pop ar3,gr3;
    pop ar2,gr2;
    pop ar1,gr1;
    pop ar0,gr0;
return;	
.wait;

end ".text_nmplс";


