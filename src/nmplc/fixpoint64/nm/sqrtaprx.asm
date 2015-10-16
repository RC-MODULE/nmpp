//***************************************************************************/
//*                                                                         */
//*                    Neuroprocessor NM6403 SDK v.1.2                      */
//*                                                                         */
//*				Signed Fixed Point 32-bit Routine                           */
//*                                                                         */
//*             Выделение экспоненты и мантиссы из числа                    */
//*                  с плаваюющей запятой типа double                       */
//*                                                                         */
//*                                                                         */
//*                1999 (c) RC Module Inc., Moscow, Russia                  */
//***************************************************************************/


//////////////////////////////////////////////////////////////////////////////
//                                                                          //
//                Float point DFrExp                                        //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

begin ".text_nmplс"
global _SCL_FrExp :label;
<_SCL_FrExp>
.branch;
	ar5=sp-2;
	push ar0,gr0;
	push ar1,gr1;
	push ar2,gr2;
	push ar6,gr6;
	ar0,gr0=[--ar5];		// аргумент 
	gr1=7FF00000h;
	gr2=gr0 and gr1;
	gr5=00100000h;
	gr2+=gr5;
	with gr7=gr2<<1;
	if > delayed goto NegExp;
		gr6=80000000h;
	<PosExp>
	gr6=gr7-gr6;
	gr6>>=1;
	gr7-=gr6;
	gr7>>=1;
	gr7 = gr7 and gr1;
	goto Exit;
	<NegExp>
	gr6=gr6-gr7;
	gr6>>=1;
	gr7+=gr6;
	gr7>>=1;
	gr7 = gr7 and gr1;
	<Exit>
		
		gr1=not gr1;
		gr0=gr0 and gr1;
		gr7-=gr5;
		gr0=gr0 or gr7;
	gr6=gr0;
	gr7=ar0;
	pop ar6,gr6;
	pop ar2,gr2 with gr6=gr0;	// gr0 - мантисса  операнда
	pop ar1,gr1;
	pop ar0,gr0;
	
	return;	
.wait;
end ".text_nmplс";
