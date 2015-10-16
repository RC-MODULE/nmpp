//***************************************************************************/
//*                                                                         */
//*                    Neuroprocessor NM6403 SDK v.1.2                      */
//*                                                                         */
//*				Signed Fixed Point 32-bit Routine                           */
//*                                                                         */
//*             Деление чисел с фиксированной запятой                       */
//*                                                                         */
//*                                                                         */
//*                1999 (c) RC Module Inc., Moscow, Russia                  */
//***************************************************************************/
//	Arg1 - Dividend
//  Arg2 - Divisor
//--------------------------
//	Res1 - Quotient
//!!!!!!!!!!!!!!!!!!! МЕНЯТЬ ЗДЕСЬ !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//const FIXPOINT=16; //Положение двоичной точки в 32-х разрядном слове
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//Div01,Div02,Div03,Div04,Div05,Div06,Div07,Div08,Div09,Div10,
//Div11,Div12,Div13,Div14,Div15,Div16,Div17,Div18,Div19,Div20,
//Div21,Div22,Div23,Div24,Div25,Div26,Div27,Div28,Div29,Div30,
//Div31,Div32 : label;
//**********  Local ********************
//data ".data_nmplc_L"
//	Void:word;
//	Temp:word;
//end ".data_nmplc_L";
/*
	static int Void;
	static int Temp;
	

	static int gr0;
	static int gr1;
	static int gr2;
	static int gr3;
	static int gr4;
	static int gr5;
	static int gr6;
	static int gr7;
	static int c;
	static int carry;

	static void* ar0;
	
#define SHLC(gr)	\
	c=carry;		\
	carry=gr>>31;	\
	gr<<=1;			\
	gr|=(c&1);	

int ADDC(unsigned a, unsigned b) {
	carry= (a + b < a);
	return a+b;
}
//--------------------------------------------
//macro DIV_STEP()		//gr0=x-gr1
//	if carry delayed skip 4 with gr7 C<<=1;
//		with gr0<<=1;	//gr0=2x-2*gr1
//		with gr0-=gr1;	//gr0=2x-3*gr1
//	gr0+=gr1;			//gr0=2x-2*gr1
//	gr0+=gr1;			//gr0=2x-gr1
//end DIV_STEP;
#define DIV_STEP()				\
	if (carry) {				\
		SHLC(gr7);				\
		gr0 <<=1;				\
		gr0=ADDC(gr0,-gr1);		\
	}							\
	else {						\
		SHLC(gr7);				\
		gr0 <<=1;				\
		gr0-=gr1;				\
		gr0+=gr1;				\
		gr0=ADDC(gr0,gr1);		\
	}


//--------------------------------------------
//macro ALIGN(Jump)
//	if u< delayed goto Aligned with gr1 R<<=1 ;
//		ar0=Jump with gr0=gr4-gr1;
//end ALIGN;

#define ALIGN(Jump)				\
	c = ((unsigned)gr1)>>31;	\
	gr1<<=31;					\
	gr1|=c;						\
	ar0 = Jump;			\
	gr0 = ADDC(gr4,-gr1);		\
	if (carry) goto Aligned;
//		ar0=Jump with gr0=gr4-gr1;
//end ALIGN;
//--------------------------------------------


//begin ".text_nmplс"

//! \fn  int SCL_FixDiv32(int nX, int nY)
//!
//! \perfinclude _SCL_FixDiv32__Fii.html

//obal _SCL_FixDiv32 :label;
int SCL_FixDiv32(int a, int b){
	//.branch;
	//ar5=ar7-4;
	//push ar0,gr0;
	//push ar1,gr1 ;
//	gr0=[ar5++];						//Делимое
//	gr1=[ar5++];						//Делитель
	//gr1=[ar5++];						//Делитель
	//gr0=[ar5++];						//Делимое
	gr1= a;
	gr0= b;

	//push ar2,gr2 with gr2=gr1;			//Делитель
	//push ar4,gr4 with gr0;				//Знак делимого
	gr2=gr1;

	//Вычисление модуля делимого 
	//if >= delayed skip 4 ;
	//	[Temp]=ar7 with gr1;			//Знак делителя
	//gr0=-gr0 noflags;					//Изменение знака делимого на "+"
	//gr2=-gr2 noflags;					//Вычисление знака частного
	Temp=gr7;
	if (gr0>=0){

	} else {
		gr0=-gr0;
		gr2=-gr2;
	}


	//Вычисление модуля делителя
	//if >= delayed skip 4 with gr4=gr0;	//Делимое
	//	ar5=[Temp] with gr0=gr0-gr1;	//Разность делимого и делителя
	//gr1=-gr1;							//Изменение знака делителя на "+"
	//with gr0=gr4-gr1;					//разность делимого и делителя
	
	gr4 = gr0;
	gr0 = gr0 - gr1;
	if (gr1>=0){
		
	} else {
		gr1=-gr1;
		gr0-=gr4-gr1;
	}


	//Divisor <?> Dividend
	//if > delayed goto LargeQuotient;	//Если делимое больше делителя...
	//	[Void]=gr7 with gr7-=gr7 noflags;
	Void=gr7;  gr7-=gr7 ;
	if (gr0>0) goto LargeQuotient;

	goto Div01;
	//Пошаговое деление если делимое меньше делителя
	//.repeat FIXPOINT;
		DIV_STEP();
		DIV_STEP();
		DIV_STEP();
		DIV_STEP();
		DIV_STEP();
		DIV_STEP();
		DIV_STEP();
		DIV_STEP();
		DIV_STEP();
		DIV_STEP();
		DIV_STEP();
		DIV_STEP();
		DIV_STEP();
		DIV_STEP();
		DIV_STEP();
		DIV_STEP();
	//.endrepeat;
	//delayed goto SignCorrection with gr7 C<<=1;
	//	[Void]=gr7 with gr2;
	SHLC(gr7);
	Void=gr7; gr2;
	goto SignCorrection; 
	//Сдвиг делителя до тех пор пока Dividend>Divisor 
LargeQuotient:
	//with gr1 R<<=1;		//ALIGN(Div00)
	//with gr0=gr4-gr1;	//ALIGN(Div00)
	c = ((unsigned )gr1)>>31;
	gr1<<=31;
	gr1|=c;
	gr0=ADDC(gr4,-gr1);

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
Aligned:

	//delayed goto ar0 with gr1 R>>=2;//Восстановление gr1 после двух лишних сдвигов
	//	[Void]=gr7 with gr0=gr4-gr1;

	c =(gr1)<<30;
	gr1=((unsigned)gr1)>>2;
	gr1|=c;
	[Void]=gr7; gr0=ADDC(gr4,-gr1);
	goto ar0;

	//Вычисление целой части
	Div32:	
		DIV_STEP();
	Div31:
		DIV_STEP();
	Div30:	
		DIV_STEP();
	Div29:
		DIV_STEP();
	Div28:
		DIV_STEP();
	Div27:
		DIV_STEP();
	Div26:
		DIV_STEP();
	Div25:
		DIV_STEP();
	Div24:	
		DIV_STEP();
	Div23:
		DIV_STEP();
	Div22:
		DIV_STEP();
	Div21:
		DIV_STEP();
	Div20:
		DIV_STEP();
	Div19:
		DIV_STEP();
	Div18:	
		DIV_STEP();
	Div17:
		DIV_STEP();
	Div16:
		DIV_STEP();
	Div15:
		DIV_STEP();
	Div14:
		DIV_STEP();
	Div13:
		DIV_STEP();
	Div12:	
		DIV_STEP();
	Div11:
		DIV_STEP();
	Div10:
		DIV_STEP();
	Div09:
		DIV_STEP();
	Div08:
		DIV_STEP();
	Div07:
		DIV_STEP();
	Div06:	
		DIV_STEP();
	Div05:
		DIV_STEP();
	Div04:
		DIV_STEP();
	Div03:
		DIV_STEP();
	Div02:
		DIV_STEP();
Div01:
		DIV_STEP();
	// Вычисление дробной части
	//.repeat FIXPOINT;
		DIV_STEP();
		DIV_STEP();
		DIV_STEP();
		DIV_STEP();
		DIV_STEP();
		DIV_STEP();
		DIV_STEP();
		DIV_STEP();
		DIV_STEP();
		DIV_STEP();
		DIV_STEP();
		DIV_STEP();
		DIV_STEP();
		DIV_STEP();
		DIV_STEP();
		DIV_STEP();

	//.endrepeat;
	//with gr2;
	// Коррекция знака частного 
	SignCorrection:
	//if >= delayed skip 4;
	//	ar7-=8;
	//gr7=-gr7;//Изменение знака
	//nul;

		if (gr2>=0) {

		}
		else {
			gr7=-gr7;
		}
	// RETURN
	//ar4,gr4=[--ar5];
	//ar2,gr2=[--ar5];
//delayed return;
//	ar1,gr1=[--ar5];
//	ar0,gr0=[--ar5];
//.wait;
//end ".text_nmplс";
		return gr7;
}
*/
int SCL_FixDiv32(int a, int b){
	long long aa=a;
	aa<<=16;
	aa/=b;
	return aa;
}