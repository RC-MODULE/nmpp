//***************************************************************************/
//*                                                                         */
//*                    Neuroprocessor NM6403 SDK v.1.2                      */
//*                                                                         */
//*				Signed Fixed Point 64-bit Routines                          */
//*                                                                         */
//*             Вычисление квадратного корня в Fixed Point 64               */
//*                                                                         */
//*                1999 (c) RC Module Inc., Moscow, Russia                  */
//***************************************************************************/


import from macros.mlb;

Pos01,Pos02,Pos03,Pos04,Pos05,Pos06,Pos07,Pos08,Pos09,Pos10,Pos11,Pos12,
Pos13,Pos14,Pos15,Pos16,Pos17,Pos18,Pos19,Pos20,Pos21,Pos22,Pos23,Pos24,
Pos25,Pos26,Pos27,Pos28,Pos29,Pos30,Pos31,Pos32 :label;

Neg01,Neg02,Neg03,Neg04,Neg05,Neg06,Neg07,Neg08,Neg09,Neg10,Neg11,Neg12,
Neg13,Neg14,Neg15,Neg16,Neg17,Neg18,Neg19,Neg20,Neg21,Neg22,Neg23,Neg24,
Neg25,Neg26,Neg27,Neg28,Neg29,Neg30,Neg31,Neg32 :label;


macro SQRTPOS(JumpNeg)
	gr1 <<=1;
	gr0 C<<=1;
	gr3 C<<=1;
	gr2 C<<=1;
	gr1 <<=1;
	gr0 C<<=1;
	gr3 C<<=1;
	gr2 C<<=1;

	gr4=gr6<<2;
	gr5=gr7>>30;
	gr4=gr6 or gr5;
	gr5=gr7<<2;
	
	FIXINC64(gr4,gr5);
	FIXSUB64(gr2,gr3,gr4,gr5,gr2,gr3);

	if not carry delayed goto JumpNeg with gr7 C<<=1;
		gr6 C<<=1;
		nul;
end SQRTPOS;

macro SQRTNEG(JumpPos)
	gr1 <<=1;
	gr0 C<<=1;
	gr3 C<<=1;
	gr2 C<<=1;
	gr1 <<=1;
	gr0 C<<=1;
	gr3 C<<=1;
	gr2 C<<=1;

	gr4=gr6<<2;
	gr5=gr7>>30;
	[sp++]=gr7 with gr4=gr6 or gr5;
	gr7=3 with gr5=gr7<<2;
	gr7=[--sp] with gr5 = gr5 or gr7;	
	FIXADD64(gr2,gr3,gr4,gr5,gr2,gr3);
	if carry delayed goto JumpPos with gr7 C<<=1;
		gr6 C<<=1;
		nul;
end SQRTNEG;

begin ".text_nmplс"

//! \fn 	unsigned long SCL_Sqrt64(unsigned long x);
//!
//! \perfinclude _SCL_Sqrt64__FUl.html
global _SCL_Sqrt64 :label; 
<_SCL_Sqrt64>
.branch;
	ar5=sp-2;

	push ar0,gr0 with gr7-=gr7;
    push ar1,gr1 with gr0-=gr0;
    push ar2,gr2 with gr1-=gr1;
    push ar3,gr3 with gr2-=gr2;
    push ar4,gr4 with gr3-=gr3;
	push ar5,gr5 with gr4-=gr4;
	gr0=[--ar5] with gr5-=gr5; // Hi (long Input)
	gr1=[--ar5] with gr6-=gr6; // Lo (long Input)
	//<Pos00>
		SQRTPOS(Neg01);
	<Pos01>
		SQRTPOS(Neg02);
	<Pos02>
		SQRTPOS(Neg03);
	<Pos03>
		SQRTPOS(Neg04);
	<Pos04>
		SQRTPOS(Neg05);
	<Pos05>
		SQRTPOS(Neg06);
	<Pos06>
		SQRTPOS(Neg07);
	<Pos07>
		SQRTPOS(Neg08);
	<Pos08>
		SQRTPOS(Neg09);
	<Pos09>
		SQRTPOS(Neg10);
	<Pos10>
		SQRTPOS(Neg11);
	<Pos11>
		SQRTPOS(Neg12);
	<Pos12>
		SQRTPOS(Neg13);
	<Pos13>
		SQRTPOS(Neg14);
	<Pos14>
		SQRTPOS(Neg15);
	<Pos15>
		SQRTPOS(Neg16);
	<Pos16>
		SQRTPOS(Neg17);
	<Pos17>
		SQRTPOS(Neg18);
	<Pos18>
		SQRTPOS(Neg19);
	<Pos19>
		SQRTPOS(Neg20);
	<Pos20>
		SQRTPOS(Neg21);
	<Pos21>
		SQRTPOS(Neg22);
	<Pos22>
		SQRTPOS(Neg23);
	<Pos23>
		SQRTPOS(Neg24);
	<Pos24>
		SQRTPOS(Neg25);
	<Pos25>
		SQRTPOS(Neg26);
	<Pos26>
		SQRTPOS(Neg27);
	<Pos27>
		SQRTPOS(Neg28);
	<Pos28>
		SQRTPOS(Neg29);
	<Pos29>
		SQRTPOS(Neg30);
	<Pos30>
		SQRTPOS(Neg31);
	<Pos31>
		SQRTPOS(Neg32);
	goto Pos32;
//----------------------
	<Neg01>
		SQRTNEG(Pos02);
	<Neg02>
		SQRTNEG(Pos03);
	<Neg03>
		SQRTNEG(Pos04);
	<Neg04>
		SQRTNEG(Pos05);
	<Neg05>
		SQRTNEG(Pos06);
	<Neg06>
		SQRTNEG(Pos07);
	<Neg07>
		SQRTNEG(Pos08);
	<Neg08>
		SQRTNEG(Pos09);
	<Neg09>
		SQRTNEG(Pos10);
	<Neg10>
		SQRTNEG(Pos11);
	<Neg11>
		SQRTNEG(Pos12);
	<Neg12>
		SQRTNEG(Pos13);
	<Neg13>
		SQRTNEG(Pos14);
	<Neg14>
		SQRTNEG(Pos15);
	<Neg15>
		SQRTNEG(Pos16);
	<Neg16>
		SQRTNEG(Pos17);
	<Neg17>
		SQRTNEG(Pos18);
	<Neg18>
		SQRTNEG(Pos19);
	<Neg19>
		SQRTNEG(Pos20);
	<Neg20>
		SQRTNEG(Pos21);
	<Neg21>
		SQRTNEG(Pos22);
	<Neg22>
		SQRTNEG(Pos23);
	<Neg23>
		SQRTNEG(Pos24);
	<Neg24>
		SQRTNEG(Pos25);
	<Neg25>
		SQRTNEG(Pos26);
	<Neg26>
		SQRTNEG(Pos27);
	<Neg27>
		SQRTNEG(Pos28);
	<Neg28>
		SQRTNEG(Pos29);
	<Neg29>
		SQRTNEG(Pos30);
	<Neg30>
		SQRTNEG(Pos31);
	<Neg31>
		SQRTNEG(Pos32);
	<Neg32>
	<Pos32>
	pop ar5,gr5;//gr7 =Lo(sqrt(long Input))
    pop ar4,gr4;//gr6 =Hi(sqrt(long Input))
    pop ar3,gr3;
    pop ar2,gr2;
    pop ar1,gr1;
    pop ar0,gr0;

return;	
.wait;

end ".text_nmplс";


