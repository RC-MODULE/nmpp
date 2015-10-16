//***************************************************************************/
//*                                                                         */
//*                    Neuroprocessor NM6403 SDK v.1.2                      */
//*                                                                         */
//*             Signed Fixed Point 32-bit Routine                           */
//*                                                                         */
//*             Перевод из числа типа double в fixed-point 32   и обратно   */
//*                                                                         */
//*                1999 (c) RC Module Inc., Moscow, Russia                  */
//***************************************************************************/


//////////////////////////////////////////////////////////////////////////////
//                                                                          //
//                DoubleToFix64                                             //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
//  Макрос сдвига слова HiReg,LoReg на Shift бит вправо или влево           // 
//                      с переходом                                         //
//       "+"-сдвиг влево , "-"- сдвиг вправо                                //
//////////////////////////////////////////////////////////////////////////////
// HiReg,LoReg cдвигается на Shift бит враво или влево,
// изменяются все регистры 
// результат сохранаяется только в HiReg
/*
macro R2SHIFT(Reg,Shift)
	delayed goto Exit with Reg>>=Shift;
		nul;nul;
end R2SHIFT;

macro L2SHIFT(HiReg,LoReg,Shift)
	delayed goto Exit with HiReg<<=Shift;
		LoReg>>=32-Shift;
		HiReg=HiReg or LoReg;
end L2SHIFT;

macro SHIFT2TO1(HiReg,LoReg,Shift)
	NoShift:label;
	gr7=NoShift with Shift<<=2;
	gr4+=gr7;
	goto gr4;

	R2SHIFT(HiReg,21);
	R2SHIFT(HiReg,20);
	R2SHIFT(HiReg,19);
	R2SHIFT(HiReg,18);
	R2SHIFT(HiReg,17);
	R2SHIFT(HiReg,16);
	R2SHIFT(HiReg,15);
	R2SHIFT(HiReg,14);
	R2SHIFT(HiReg,13);
	R2SHIFT(HiReg,12);
	R2SHIFT(HiReg,11);
	R2SHIFT(HiReg,10);
	R2SHIFT(HiReg,09);
	R2SHIFT(HiReg,08);
	R2SHIFT(HiReg,07);
	R2SHIFT(HiReg,06);
	R2SHIFT(HiReg,05);
	R2SHIFT(HiReg,04);
	R2SHIFT(HiReg,03);
	R2SHIFT(HiReg,02);
	R2SHIFT(HiReg,01);
	<NoShift>
	delayed goto Exit with HiReg;
		nul; nul;
	L2SHIFT(HiReg,LoReg,01);
	L2SHIFT(HiReg,LoReg,02);
	L2SHIFT(HiReg,LoReg,03);
	L2SHIFT(HiReg,LoReg,04);
	L2SHIFT(HiReg,LoReg,05);
	L2SHIFT(HiReg,LoReg,06);
	L2SHIFT(HiReg,LoReg,07);
	L2SHIFT(HiReg,LoReg,08);
	L2SHIFT(HiReg,LoReg,09);
	L2SHIFT(HiReg,LoReg,10);
	<Exit>		
end SHIFT2TO1;

begin ".text_nmplс"





//////////////////////////////////////////////////////////////////////////////
//                                                                          //
//  Функция перевода из Fixed-Point 32 в Double                             //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////
// На входе число FixedPoint64(long) передается через стек
// На выходе число Double передается через gr7 и gr6. (Показатель находится в gr7)
//! \fn  double SCL_Fix32ToDouble(int Fix32)
//!
//! \perfinclude _SCL_Fix32ToDouble__Fi.html
global _SCL_Fix32ToDouble :label;
<_SCL_Fix32ToDouble>
	.branch;
	ar5=sp-2;
	push ar1,gr1;
	push ar2,gr2;
	push ar3,gr3;
    
	gr6=[--ar5] with gr3-=gr3;				// FixedPoint32
	with gr6;
	if =0 goto EXIT with gr7-=gr7 noflags;
	if >= goto SkipNeg with gr7-=gr7 noflags;//если число отрицательное, то
	gr3=80000000h 							// установка знака "-" для double числа	
	with gr6=-gr6 noflags;					// вычисление модуля числа FixedPoint32
	<SkipNeg>
	//	Сдвиг числа Fixed-Point32 к 31 биту с потерей старшей еденицы 
	with gr6<<=1; 
	.repeat 32;
	if < delayed goto StopShift with gr7++;	// gr7 кол-
		gr6<<=1;
		nul;
	.endrepeat;
	<StopShift>
	gr2=40Eh								// смещение показателя
	with gr1=gr6<<20;						// младшая часть мантиссы
	gr6>>=12;								// сдвиг мантиссы к 51 биту
	gr7=gr2-gr7;							// вычисление смещенного показателя
	gr7<<=20;								// сдвиг смещенного показателя к 62 биту
	gr6=gr6 or gr7;							// объеденение мантиссы и показателя
	gr6=gr3 or gr6;							// установка знака числа

	<EXIT>
	pop ar3,gr3  with gr7=gr1;
	pop ar2,gr2;
	pop ar1,gr1;
	return;	
	.wait;
end ".text_nmplс";
*/

double SCL_Fix32ToDouble(int x){
	double d=x>>16;
	double p=x&0xFFFF;
	p/=65536;
	d+=p;
	return d;
}