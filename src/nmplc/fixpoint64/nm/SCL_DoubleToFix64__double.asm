//***************************************************************************/
//*                                                                         */
//*                    Neuroprocessor NM6403 SDK v.1.2                      */
//*                                                                         */
//*				Signed Fixed Point 32-bit Routine           */
//*                                                                         */
//*             Перевод числа из типа double в fixed-point 64 b и обратно   */
//*               двоичная точка находится между 31 и 32 битом              */
//*                1999 (c) RC Module Inc., Moscow, Russia                  */
//***************************************************************************/

import from rtmacro.mlb;

begin ".text_nmplс"
//! \fn	long SCL_DoubleToFix64(double arg, int fixpoint);
//!
//! \perfinclude _SCL_DoubleToFix64__F6doublei.html
global _SCL_DoubleToFix64 :label;
<_SCL_DoubleToFix64>
.branch;
	ar5=sp-2;
    push ar0,gr0;
    push ar1,gr1;
    push ar2,gr2;
    push ar3,gr3;
    push ar4,gr4;
    
	gr0=[--ar5];        //показатель и старшая часть мантиссы
    gr1=[--ar5];        //младшая часть мантиссы
    gr7=000FFFFFh;      //маска для выделения старшеей мантиссы
    gr2=gr0 and gr7;    //старшая часть мантиссы
    gr7=00100000h;
    gr2=gr2 or gr7;     //восстановление единицы 
    gr7=7FF00000h;      //маска для выделения показателя
    gr3=gr0 and gr7;    //смещенный показатель
    gr7=3FF00000h;      
    gr3-=gr7;			//приведенный показатель (в старших разрядах)
    gr3 A>>=20;			//приведенный показатель - нормализованный
    // (gr2,gr1)-мантисса - gr3 - показатель gr0-знак   
    gr4=20;//показатель при котором не надо сдвигать мантиссу
	gr7=gr3-gr4;
	///////
	gr4=32;
	gr4=[--ar5] with gr7-=gr4;
	with gr7+=gr4;
	///////
    if < goto RShift;
    LSHIFT64(gr4,gr3,gr1,gr2,gr7);
    goto SignCorrect;
    <RShift>
    gr7=-gr7;
    RSHIFT64(gr4,gr3,gr1,gr2,gr7);
    
    <SignCorrect>
    with gr0;
    if >= goto Finish;
        gr4=-gr4;
        gr3=not gr3 noflags;
        gr3=gr3+carry;

    <Finish>
    pop ar4,gr4 with gr7=gr4;//Lo
    pop ar3,gr3 with gr6=gr3;//Hi
    pop ar2,gr2;
    pop ar1,gr1;
    pop ar0,gr0;
	return;	
.wait;



end ".text_nmplс";
