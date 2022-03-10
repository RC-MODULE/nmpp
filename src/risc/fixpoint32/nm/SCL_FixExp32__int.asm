//***************************************************************************/
//*                                                                         */
//*                    Neuroprocessor NM6403 SDK v.1.2                      */
//*                                                                         */
//*				Signed Fixed Point 32-bit Routine                           */
//*                                                                         */
//*             ВЫЧИСЛЕНИЕ ЭКСПОНЕНТЫ ДЛЯ ЧИСЕЛ С ФИКСИРОВАННОЙ ЗАПЯТОЙ     */
//*                                                                         */
//*                                                                         */
//*     16.01.2000      (c) RC Module Inc., Moscow, Russia                  */
//***************************************************************************/
//!!!!!!!!!!!!!!!!!!! МЕНЯТЬ ЗДЕСЬ !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
const FIXPOINT=16; //Положение двоичной точки в 32-х разрядном слове
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

extern LogBigTable:word;
import from rtmacro;


begin ".text_nmplс"

macro FIRST_LOG_STEP()
	gr1=[ar6++] ;
	with gr0-gr1;
if < delayed skip 10;
	ar3=0;

	gr2=gr7 with gr6=gr7;
	with gr0-=gr1;
if >= delayed skip -4 with gr7=gr6+gr7;
	ar3=0;

	gr0+=gr1;
	gr7=gr2;
end FIRST_LOG_STEP;

macro LOG_STEP(RShift)
	gr1=[ar6++];
	with gr0-gr1;
if < delayed skip 10 ;
	ar3=0;
	
	gr2=gr7 with gr6=gr7>>RShift;
	with gr0-=gr1;
if >= delayed  skip -4 with gr7=gr6+gr7;
	ar3=0;
		

	gr0+=gr1;
	gr7=gr2;
end LOG_STEP;

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
//                     Signed Fixed  Point                                  //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////
//1.030000e+001   2.970201e+004   2.970135e+004   2.211439e-003
//Max error : 6.057355e-003 %     Step=1.030000e-003
// 316 тактов/ exp

//! \fn int nmppcFixExp32( int Arg);
//! 
//! \perfinclude _nmppcFixExp32__Fi.html

global _nmppcFixExp32 :label;
<_nmppcFixExp32>
.branch;
	ar5=sp-2 with gr7=false;
	push ar0,gr0 with gr7=gr7+1;
	push ar1,gr1 with gr7<<=FIXPOINT;
	push ar2,gr2 ;
	push ar3,gr3;
	push ar6,gr6;
	gr0=[--ar5] ;
	ar6=LogBigTable with gr0-gr7;
	
	if<= delayed goto SkipFirstApproximation;
	gr6=14  //MAX_EXP_ARGUMENT;
	with true;
	//Loop First Approximation>
	if < delayed skip -2 with gr6--;
		gr1=[ar6++];
		with gr0-gr1;
	
	ar6-=2 with gr6++;
	gr1=[ar6++] with gr6++;
	LSHIFT32(gr7,gr7,gr6);    //RSHIFT32 ( Res, Arg, Val )
	
	gr6=10000h with gr0-=gr1;
	with gr7+=gr6;
	<SkipFirstApproximation>
	with gr7++;
	with gr7++;
	ar6=LogBigTable+14 with gr7++;
	
	FIRST_LOG_STEP();
	LOG_STEP(1);
	LOG_STEP(2);
	LOG_STEP(3);
	LOG_STEP(4);
	LOG_STEP(5);
	LOG_STEP(6);
	LOG_STEP(7);
	LOG_STEP(8);
	LOG_STEP(9);
	LOG_STEP(10);
	LOG_STEP(11);
	LOG_STEP(12);
	LOG_STEP(13);
	LOG_STEP(14);
	LOG_STEP(15);

	pop ar6,gr6;
	pop ar3,gr3;
	pop ar2,gr2;
	pop ar1,gr1;
	pop ar0,gr0;
return;
.wait;


end ".text_nmplс";
