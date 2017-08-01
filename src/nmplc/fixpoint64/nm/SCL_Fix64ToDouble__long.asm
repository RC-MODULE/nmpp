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





macro SHIFTLEFT64(HiReg,LoReg,Counter)
        if < delayed goto StopShift with gr7++;
         LoReg <<=1;
         HiReg C<<=1;
end SHIFTLEFT64;
begin ".text_nmplс"


//! \fn double nmppcFix64ToDouble(long arg , int fixpoint );
//!
//! \perfinclude _nmppcFix64ToDouble__Fli.html

// На входе число FixedPoint64(long) передается через стек
// На выходе число Double передается через gr7 и gr6. (Показатель находится в gr7)

<_nmppcFix64ToDouble>
global _nmppcFix64ToDouble :label;
.branch;
	ar5=sp-2;
    push ar1,gr1;
    push ar2,gr2;
    push ar3,gr3;
    
	gr6=[--ar5] with gr3-=gr3;  //Старшие 32 бита числа FixedPoint64
    gr1=[--ar5] with gr6;		//Младшие 32 бита числа FixedPoint64
    if >= goto SkipNeg with gr7-=gr7 noflags;//если число отрицательное, то
	//Изменение знака числа FixedPoint64
	gr1=-gr1;
    gr6=not gr6 noflags;
  	gr3=80000000h with gr6=gr6+carry;//установка знака "-" для double числа
	<SkipNeg>
	.repeat 64;
        SHIFTLEFT64(gr6,gr1,gr7);	//послед.-ный сдвиг числа до удаления первой значимой еденицы ,
									//нахождение показателя-gr7
	.endrepeat;
	//double=0.0
	delayed goto EXIT with gr1-=gr1;
		gr6=0; 	
    <StopShift>
	//сдвиг мантиссы к 51 биту
	gr1>>=12;
	gr2=gr6<<20;
	gr1=gr1 or gr2;
	gr2=41Fh with gr6>>=12;
	//вычисление смещенного показателя
	gr7=gr2-gr7;
	/////////
	gr2=32;
	gr2=[--ar5] with gr7+=gr2;
	gr7-=gr2;

	///////
	gr7<<=20;				// сдвиг смещенного показателя к 62 биту
	gr6=gr6 or gr7;			// объеденение мантиссы и показателя
    with gr6=gr3 or gr6;	// установка знака числа

	<EXIT>

	pop ar3,gr3  with gr7=gr1;
    pop ar2,gr2 ;
    pop ar1,gr1;
  	return;	
.wait;


end ".text_nmplс";
