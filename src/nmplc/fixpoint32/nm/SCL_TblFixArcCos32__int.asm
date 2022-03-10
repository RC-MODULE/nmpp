//***************************************************************************/
//*                                                                         */
//*                    Neuroprocessor NM6403 SDK v.1.2                      */
//*                                                                         */
//*				Signed Fixed Point 32-bit Routine                           */
//*                                                                         */
//*             Вычисление арксинуса числа с фиксированной запятой          */
//*                                                                         */
//*                                                                         */
//*                1999 (c) RC Module Inc., Moscow, Russia                  */
//***************************************************************************/
//	Arg1 - Angle
//--------------------------
//	Res1 - Sin
//!!!!!!!!!!!!!!!!!!! МЕНЯТЬ ЗДЕСЬ !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
const FIXPOINT=16; //Положение двоичной точки в 32-х разрядном слове
const N=10;//1025-точек - константа определяющая размер массива значений арксинуса 
//const N=10//1608-точек
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
const MAXINDEX=10000h >> (FIXPOINT-N);//Размер массива значений синуса
const PI2 = (6487ed51h >> (30-FIXPOINT)) ;//PI2=90 град.

import from macros.mlb;
extern FixArcSinDat:word;


begin ".text_nmplс"

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
//                            Fixed  Point ArcCosine                        //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////
// gr0 заменить на gr7 !!!

//! \fn int nmppcTblFixArcCos32(int nArg)
//! 
//! \perfinclude _nmppcTblFixArcCos32__Fi.html
global _nmppcTblFixArcCos32:label;
<_nmppcTblFixArcCos32>
.branch;
	ar5 = sp-2;
	gr7 = [--ar5];
	push ar1,gr1 with gr7;
	//with gr7=Arg;// аргумент передается через gr7			 
	//Вычисление модуля угла
	if >= delayed skip 4 with gr1=gr7;
		ar1=FixArcSinDat ;
	gr1=-gr1;
	nul;
	//Определение четверти ,соответсвующей данному углу
		gr1 >>=(FIXPOINT-N);	//Вычисление индекса по значению угла
		gr7=[ar1+=gr1] with gr7;
	//Коррекция знака арксинуса	 
	if >= delayed skip 4;
		gr1=PI2;
	gr7=-gr7;
	nul;
	with gr7=gr1-gr7;
	pop ar1,gr1;
return;
.wait;
end ".text_nmplс";
