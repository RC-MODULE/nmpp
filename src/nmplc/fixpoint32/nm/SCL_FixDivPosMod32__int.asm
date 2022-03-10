//***************************************************************************/
//*                                                                         */
//*                    Neuroprocessor NM6403 SDK v.1.2                      */
//*                                                                         */
//*				Signed Fixed Point 32-bit Routine                           */
//*                                                                         */
//*             Деление чисел с фиксированной запятой c остатком            */
//*                со взятием модуля от остатка и целого                    */
//*                                                                         */
//*                1999 (c) RC Module Inc., Moscow, Russia                  */
//***************************************************************************/
//	Arg1 - Dividend
//  Arg2 - Divisor
//--------------------------
//	Res1 - Quotient(целое)
//  Res2 - Reminder(остаток)
//!!!!!!!!!!!!!!!!!!! МЕНЯТЬ ЗДЕСЬ !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
const FIXPOINT=16; //Положение двоичной точки в 32-х разрядном слове
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

Div01,Div02,Div03,Div04,Div05,Div06,Div07,Div08,Div09,Div10,
Div11,Div12,Div13,Div14,Div15,Div16,Div17,Div18,Div19,Div20,
Div21,Div22,Div23,Div24,Div25,Div26,Div27,Div28,Div29,Div30,
Div31,Div32 : label;
//**********  Local ********************
data "LocalSRAM"
	Void:word;
	Temp:word;
end "LocalSRAM";

//--------------------------------------------
macro DIV_STEP()
	if carry delayed skip 4 with gr7 C<<=1;
		with gr1 >>=1;
		with gr0 -=gr1;
	gr0+=gr1;
	gr0+=gr1;
end DIV_STEP;
//--------------------------------------------
macro ALIGN(Jump)
	if u< delayed goto Aligned with gr1 R<<=1 ;
		ar0=Jump with gr7=gr0-gr1;
end ALIGN;
//--------------------------------------------

//*********** TEXT ****************
begin ".text_nmplс"
//////////////////////////////////////////////////////////////////////////////
//                                                                          //
//                     Signed Fixed  Point division                         //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////
//! \fn void nmppcFixDivPosMod32(unsigned int nDividend, unsigned int nDivisor,  int* nQuotient,  int* nReminder);
//!
//! \perfinclude _nmppcFixDivPosMod32__FUiUiPiPi.html

global _nmppcFixDivPosMod32 :label;
<_nmppcFixDivPosMod32>
.branch;
	ar5 = sp-2;
	push ar0,gr0;
	push ar1,gr1;

	gr0=[--ar5];						//Делимое
	gr1=[--ar5];						//Делитель
	with gr7=gr0-gr1;			//разность делимого и делителя
	//Divisor <?> Dividend
	if >= delayed goto LargeQuotient ;	//Если делимое больше делителя то выравнивание
		[Void]=gr7 with gr7-=gr7 noflags;

	//[--ar5]=gr7;
	//[--ar5]=gr0;
	ar1,gr1=[--ar5];
	[gr1]=gr7;//Целое
	[ar1]=gr0;//Остаток
	pop ar1,gr1;
	pop ar0,gr0;

	return;
	//Сдвиг делителя до тех пор пока Dividend>Divisor 
	<LargeQuotient>
	push ar4,gr4 with gr1 R<<=1;		//ALIGN(Div00)
	with gr7=gr0-gr1;	//ALIGN(Div00)
	ALIGN(Div01);
	ALIGN(Div02);
	ALIGN(Div03);
	ALIGN(Div04);
	ALIGN(Div05);
	ALIGN(Div06);	
	ALIGN(Div07);
	ALIGN(Div08);
	ALIGN(Div09);
	ALIGN(Div10);
	ALIGN(Div11);
	ALIGN(Div12);	
	ALIGN(Div13);
	ALIGN(Div14);
	ALIGN(Div15);
	ALIGN(Div16);
	ALIGN(Div17);
	ALIGN(Div18);	
	ALIGN(Div19);
	ALIGN(Div20);
	ALIGN(Div21);
	ALIGN(Div22);
	ALIGN(Div23);
	ALIGN(Div24);	
	ALIGN(Div25);
	ALIGN(Div26);
	ALIGN(Div27);
	ALIGN(Div28);
	ALIGN(Div29);
	ALIGN(Div30);	
	ALIGN(Div31);
	ALIGN(Div32);
	<Aligned>
	delayed goto ar0 with gr1 R>>=2;//Восстановление gr1 после двух лишних сдвигов
		gr4=gr0 with gr7-=gr7; 
		with gr0=gr4-gr1;
	//Вычисление целой части
	<Div32>	
		DIV_STEP();
	<Div31>
		DIV_STEP();
	<Div30>	
		DIV_STEP();
	<Div29>
		DIV_STEP();
	<Div28>
		DIV_STEP();
	<Div27>
		DIV_STEP();
	<Div26>
		DIV_STEP();
	<Div25>
		DIV_STEP();
	<Div24>	
		DIV_STEP();
	<Div23>
		DIV_STEP();
	<Div22>
		DIV_STEP();
	<Div21>
		DIV_STEP();
	<Div20>
		DIV_STEP();
	<Div19>
		DIV_STEP();
	<Div18>	
		DIV_STEP();
	<Div17>
		DIV_STEP();
	<Div16>
		DIV_STEP();
	<Div15>
		DIV_STEP();
	<Div14>
		DIV_STEP();
	<Div13>
		DIV_STEP();
	<Div12>	
		DIV_STEP();
	<Div11>
		DIV_STEP();
	<Div10>
		DIV_STEP();
	<Div09>
		DIV_STEP();
	<Div08>
		DIV_STEP();
	<Div07>
		DIV_STEP();
	<Div06>	
		DIV_STEP();
	<Div05>
		DIV_STEP();
	<Div04>
		DIV_STEP();
	<Div03>
		DIV_STEP();
	<Div02>
		DIV_STEP();
	<Div01>
	if carry delayed skip 4 with gr7 C<<=1;
		pop ar4,gr4;
		with gr7 <<=FIXPOINT;
	gr0+=gr1;
	nul;
	
	//gr7=gr0;
	ar1,gr1=[--ar5];
	[gr1]=gr7;//Целое
	[ar1]=gr0;//Остаток
	pop ar1,gr1;
	pop ar0,gr0;

return;
.wait;
end ".text_nmplс";
