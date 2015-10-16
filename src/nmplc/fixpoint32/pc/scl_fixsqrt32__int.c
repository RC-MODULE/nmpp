//***************************************************************************/
//*                                                                         */
//*                    Neuroprocessor NM6403 SDK v.1.2                      */
//*                                                                         */
//*				Signed Fixed Point 32-bit Routine                           */
//*                                                                         */
//*             Вычисление квадратного корня числа с фиксированной запятой  */
//*                                                                         */
//*                                                                         */
//*                1999 (c) RC Module Inc., Moscow, Russia                  */
//***************************************************************************/
//	Arg1 - Angle
//--------------------------
//	Res1 - Sin
//!!!!!!!!!!!!!!!!!!! МЕНЯТЬ ЗДЕСЬ !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//const FIXPOINT=16; //Положение двоичной точки в 32-х разрядном слове
//const N=10//1608-точек
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

//label Pos01,Pos02,Pos03,Pos04,Pos05,Pos06,Pos07,Pos08,Pos09,Pos10,Pos11,Pos12,
//Pos13,Pos14,Pos15,Pos16,Pos17,Pos18,Pos19,Pos20,Pos21,Pos22,Pos23 ;
//Neg01,Neg02,Neg03,Neg04,Neg05,Neg06,Neg07,Neg08,Neg09,Neg10,Neg11,Neg12,
//Neg13,Neg14,Neg15,Neg16,Neg17,Neg18,Neg19,Neg20,Neg21,Neg22,Neg23 :label;
//EndSqrt:label;
//**********  Local ********************
//data ".data_nmplc_L"
//	Void:word;
//end ".data_nmplc_L";
#ifndef MEM
#define MEM(addr)  (*((unsigned volatile*)(addr)))
#endif


static int gr0;
static int gr1;
static int gr2;
static int gr3;
static int gr4;
static int gr5;
static int gr6;
static int gr7;
static int c;
static int Void;

//macro SQRTPOS(JumpNeg)
static int carry;

#define SHLC(gr)	\
	c=carry;		\
	carry=gr>>31;	\
	gr<<=1;			\
	gr|=(c&1);			


int ADDC(unsigned a, unsigned b) {
	carry= (a + b < a);
	return a+b;
}


//gr1 C<<=1;
//gr0 <<=1;
//gr1 C<<=1;
//gr6 = gr7 << 2;
//gr6++;	
//gr1 -= gr6;
//if not carry delayed goto JumpNeg with gr7 C<<=1;
//	gr0 <<=1;
//	nul;
//end SQRTPOS;
#define SQRTPOS(JumpNeg)	\
	SHLC(gr1);				\
	carry=gr0>>31;			\
	gr0<<=1;				\
	SHLC(gr1);				\
	gr6 = gr7 << 2;			\
	gr6++;					\
	gr1 = ADDC(gr1,-gr6);	\
	if (!carry){			\
		SHLC(gr7);			\
		carry=gr0>>31;		\
		gr0=gr0<<1;			\
		goto JumpNeg;		\
	}						\
	SHLC(gr7);				\
	carry=gr0>>31;			\
	gr0<<=1;				



//macro SQRTNEG(JumpPos)
//	gr1 C<<=1;
//	gr0 <<=1;
//	gr1 C<<=1;
//	gr6 = gr7 << 2;
//	gr6 = gr6 or gr4;	
//	gr1 += gr6;
//	if carry delayed goto JumpPos with gr7 C<<=1;
//		gr0 <<=1;
//		nul;
//end SQRTNEG;

#define SQRTNEG(JumpPos)	\
	SHLC(gr1);				\
	carry=gr0>>31;			\
	gr0 <<=1;				\
	SHLC(gr1);				\
	gr6 = gr7 << 2;			\
	gr6 = gr6 | gr4;		\
	gr1 = ADDC(gr1,gr6);	\
	if (carry) {			\
		SHLC(gr7);			\
		carry=gr0>>31;		\
		gr0 <<=1;			\
		goto JumpPos;		\
	}						\
	SHLC(gr7);				\
	carry=gr0>>31;			\
	gr0 <<=1;				


	



//begin ".text_nmplс"
//! \fn 	unsigned int SCL_FixSqrt32(unsigned int x);
//!
//! \perfinclude _SCL_FixSqrt32__FUi.html


// gr0-Arg
// gr7-Res
//global _SCL_FixSqrt32 :label;
//<_SCL_FixSqrt32>
int SCL_FixSqrt32(int val){
	//.branch;
	//ar5=sp-2;
	//push ar0,gr0;
	//push ar1,gr1;
	//push ar4,gr4;
	//push ar6,gr6;

	//gr0=[--ar5] with gr7=false;			// gr0 = Arg
	gr0 = val;
	gr7 = 0;

	//gr4=3 with gr1-=gr1;
	//gr0 <<=1;
	gr4=3 ; gr1-=gr1;
	carry = gr0>>31;
	gr0 <<=1;

	//<Pos00>
		SQRTPOS(Neg01);
	Pos01:
		SQRTPOS(Neg02);
	Pos02:
		SQRTPOS(Neg03);
	Pos03:
		SQRTPOS(Neg04);
	Pos04:
		SQRTPOS(Neg05);
	Pos05:
		SQRTPOS(Neg06);
	Pos06:
		SQRTPOS(Neg07);
	Pos07:
		SQRTPOS(Neg08);
	Pos08:
		SQRTPOS(Neg09);
	Pos09:
		SQRTPOS(Neg10);
	Pos10:
		SQRTPOS(Neg11);
	Pos11:
		SQRTPOS(Neg12);
	Pos12:
		SQRTPOS(Neg13);
	Pos13:
		SQRTPOS(Neg14);
	Pos14:
		SQRTPOS(Neg15);
	Pos15:
		SQRTPOS(Neg16);
	Pos16:
		SQRTPOS(Neg17);
	Pos17:
		SQRTPOS(Neg18);
	Pos18:
		SQRTPOS(Neg19);
	Pos19:
		SQRTPOS(Neg20);
	Pos20:
		SQRTPOS(Neg21);
	Pos21:
		SQRTPOS(Neg22);
	Pos22:
		SQRTPOS(Neg23);
	Pos23:
		//gr1 C<<=1;
		//gr0 <<=1;
		//gr1 C<<=1;
		//gr6 = gr7 << 2;
		//delayed goto Finish	with gr6++;	
		//	gr1 -= gr6;
		//	gr7 C<<=1;

	SHLC(gr1);
	carry=gr0>>31;
	gr0 <<=1;
	SHLC(gr1);
	gr6 = gr7 << 2;
	gr6++;	
	gr1 = ADDC(gr1,- gr6);
	SHLC(gr7);
	
	goto Finish;

//----------------------
	Neg01:
		SQRTNEG(Pos02);
	Neg02:
		SQRTNEG(Pos03);
	Neg03:
		SQRTNEG(Pos04);
	Neg04:
		SQRTNEG(Pos05);
	Neg05:
		SQRTNEG(Pos06);
	Neg06:
		SQRTNEG(Pos07);
	Neg07:
		SQRTNEG(Pos08);
	Neg08:
		SQRTNEG(Pos09);
	Neg09:
		SQRTNEG(Pos10);
	Neg10:
		SQRTNEG(Pos11);
	Neg11:
		SQRTNEG(Pos12);
	Neg12:
		SQRTNEG(Pos13);
	Neg13:
		SQRTNEG(Pos14);
	Neg14:
		SQRTNEG(Pos15);
	Neg15:
		SQRTNEG(Pos16);
	Neg16:
		SQRTNEG(Pos17);
	Neg17:
		SQRTNEG(Pos18);
	Neg18:
		SQRTNEG(Pos19);
	Neg19:
		SQRTNEG(Pos20);
	Neg20:
		SQRTNEG(Pos21);
	Neg21:
		SQRTNEG(Pos22);
	Neg22:
		SQRTNEG(Pos23);
	Neg23:
		//gr1 C<<=1;
		//gr0 <<=1;
		//gr1 C<<=1;
		//gr6 = gr7 << 2;
		//with	gr6 = gr6 or gr4;	
		//gr1 += gr6;
		//gr7 C<<=1;

		SHLC(gr1);
		
		carry=gr0>>31;
		gr0 <<=1;

		SHLC(gr1);
		gr6 = gr7 << 2;
		gr6 = gr6 | gr4;	
		
		gr1 = ADDC(gr1,gr6);
		
		SHLC(gr7);

	Finish:
	//pop ar6,gr6;
	//pop ar4,gr4;
	//pop ar1,gr1;
	//pop ar0,gr0;
	return gr7;
}

//.wait;
//end ".text_nmplс";
