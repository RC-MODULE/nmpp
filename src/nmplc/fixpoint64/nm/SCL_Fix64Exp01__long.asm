//***************************************************************************/
//*                                                                         */
//*                    Neuroprocessor NM6403 SDK v.1.2                      */
//*                                                                         */
//*				Double  Routines                                            */
//*                                                                         */
//*         Вычисление экспоненты в системе с фиксированной точкой(64/60)   */
//*         при значениях аргумента от 0 до 1 включительно                  */
//*                                                                         */
//*                     (c) RC Module Inc., Moscow, Russia                  */
//* Version 1.0  (26.04.2000)                                               */
//* Version 1.1  (13.09.2000)                                               */
//***************************************************************************/



extern Fix64LogTable:long;


import from macros.mlb;


macro EXP_STEP(Shift)
own SkipApproximation: label;
	ar2,gr2=[ar4++];	// ar2,gr2=log(1-pow(2,-n)) gr2-HI, ar2-LO
	gr3=ar2 ;
			with gr3=gr1-gr3;
			with gr2=gr0-gr2-1+carry;
	if <= delayed goto SkipApproximation ;
		nul;
		nul;
	gr0=gr2 with gr1=gr3;
	FIXSHIFTAR64(gr6,gr7,gr4,gr5,Shift);
	gr7=gr7+gr5;
	gr6=gr6+gr4+carry;
	<SkipApproximation>
end EXP_STEP;



begin ".text_nmplс"
//////////////////////////////////////////////////////////////////////////////
//*         Вычисление экспоненты в системе с фиксированной точкой(64/60)   */
//*         при значениях аргумента от 0 до 1 включительно                  */
//////////////////////////////////////////////////////////////////////////////
// не оптимизировано !!!
// 
// long Exp500(long arg);

//------------- double -------------------
//	(0-1 ) (0-7FFh)            (0-FFFFFFFFFFFFFh)
//	[Знак] [Смещенный порядок] [Мантисса]
//	  63   62               52 51       0 
//  [+/-] [порядок + 3FFh ](1.)[Мантисса]      
//  [       gr0      ][        ar0      ]- входной параметр
//  [       gr6      ][        gr7      ]- выходной результат
//---------------------------------------- 
//	for(int k=0;k<iters;k++)
//	{
//	
//		z = LogPos[k];//log(1+pow(2,-k));
//		diff=x-z;
//		if (diff>0)
//		{
//			x = diff;
//			y += fMulPow2(y,-k);
//		}
//	}
//	for(int k=0;k<iters;k++)
//	{
//	
//		z = LogPos[k];//log(1-pow(2,-k));
//		z=x-z;
//		if (diff>0)
//		{
//			x = z;
//			y += fMulPow2(y,-k);
//		}
//	}

//! \fn long nmppcFix64Exp01(long nArg)
//!
//! \perfinclude _nmppcFix64Exp01__Fl.html

global _nmppcFix64Exp01:label;
<_nmppcFix64Exp01>
.branch;
	ar5=sp-2;
	push ar0,gr0;
	push ar1,gr1;
	push ar5,gr5;
		
	ar0,gr0=[--ar5];    // gr0-HI
			
	gr1=ar0;			// gr1-LO
	// ar0-младшая часть мантиссы
	// x=gr0,gr1; gr0-hi gr1-lo
	// z=gr2,gr3;
	// y=gr6,gr7;
	// pow2=gr4,gr5;
	//gr6=40000000h with gr7=false;
	gr6=10000000h with gr7=false;
	ar4=Fix64LogTable;
	
	EXP_STEP(0);
	EXP_STEP(1);
	EXP_STEP(2);
	EXP_STEP(3);
	EXP_STEP(4);
	EXP_STEP(5);
	EXP_STEP(6);
	EXP_STEP(7);
	EXP_STEP(8);
	EXP_STEP(9);
	EXP_STEP(10);
	EXP_STEP(11);
	EXP_STEP(12);
	EXP_STEP(13);
	EXP_STEP(14);
	EXP_STEP(15);
	EXP_STEP(16);
	EXP_STEP(17);
	EXP_STEP(18);
	EXP_STEP(19);
	EXP_STEP(20);
	EXP_STEP(21);
	EXP_STEP(22);
	EXP_STEP(23);
	EXP_STEP(24);
	EXP_STEP(25);
	EXP_STEP(26);
	EXP_STEP(27);
	EXP_STEP(28);
	EXP_STEP(29);
	EXP_STEP(30);
	EXP_STEP(31);
	EXP_STEP(32);
	EXP_STEP(33);
	EXP_STEP(34);
	EXP_STEP(35);
	EXP_STEP(36);
	EXP_STEP(37);
	EXP_STEP(38);
	EXP_STEP(39);
	EXP_STEP(40);
	EXP_STEP(41);
	EXP_STEP(42);
	EXP_STEP(43);
	EXP_STEP(44);
	EXP_STEP(45);
	EXP_STEP(46);
	EXP_STEP(47);
	EXP_STEP(48);
	EXP_STEP(49);
	EXP_STEP(50);
	EXP_STEP(51);
	EXP_STEP(52);
	EXP_STEP(53);
	EXP_STEP(54);
	EXP_STEP(55);
	EXP_STEP(56);
	EXP_STEP(57);
	EXP_STEP(58);
	EXP_STEP(59);
	EXP_STEP(60);
	//EXP_STEP(61);
	//EXP_STEP(62);
	
	pop ar5,gr5;
	pop ar1,gr1;
	pop ar0,gr0;
return;	
.wait;

end ".text_nmplс";


