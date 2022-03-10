//***************************************************************************/
//*                                                                         */
//*                    Neuroprocessor NM6403 SDK v.1.2                      */
//*                                                                         */
//*				Signed Fixed Point 32-bit Routine                           */
//*                                                                         */
//*           Вычисление косинуса числа с фиксированной запятой             */
//*                                                                         */
//*                                                                         */
//*                1999 (c) RC Module Inc., Moscow, Russia                  */
//***************************************************************************/

const FIXPOINT=16; //Положение двоичной точки в 32-х разрядном слове
const N=9;//804-точки - константа определяющая размер массива значениц косинуса 
//const N=10//1608-точек
const PI2 = (6487ed51h >> (30-FIXPOINT)) ;//PI2=90 град.
//const MAXINDEX=PI2 >> (FIXPOINT-N);//Размер массива значений косинуса

extern FixSinDat:word;

begin ".text_nmplс"

//! \fn int nmppcTblFixCos32(int nArg)
//! 
//! \perfinclude _nmppcTblFixCos32__Fi.html
global _nmppcTblFixCos32:label;
<_nmppcTblFixCos32>
.branch;
	ar5 = sp-2;
	gr7 = [--ar5];
	push ar1,gr1;
	gr1 = PI2;
	with gr7=gr1-gr7;
	//Вычисление модуля угла
	if >= delayed skip 4 with gr1=gr7;
		ar1=FixSinDat ;
	gr1=-gr1;
	nul;
	//Определение четверти ,соответсвующей данному углу
		gr1 >>=(FIXPOINT-N);	//Вычисление индекса по значению угла
		gr7=[ar1+=gr1] with gr7;
	//Коррекция знака арксинуса	 
	if >= delayed skip 4;
		pop ar1,gr1;	
		nul;
	gr7=-gr7;
	nul;

return;



.wait;
end ".text_nmplс";
