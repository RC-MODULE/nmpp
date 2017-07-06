//***************************************************************************/
//*                                                                         */
//*                    Neuroprocessor NM6403 SDK v.1.2                      */
//*                                                                         */
//*				Signed Fixed Point 32-bit Routine                           */
//*                                                                         */
//*       ПОВОРОТ ВЕКТОРА НА ПЛОСКОСТИ В ДЕКАРТОВЫХ КООРДИНАТАХ             */
//*                                                                         */
//*                                                                         */
//*                1999 (c) RC Module Inc., Moscow, Russia                  */
//***************************************************************************/

//!!!!!!!!!!!!!!!!!!! МЕНЯТЬ ЗДЕСЬ !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//const FIXPOINT=16; //Положение двоичной точки в 32-х разрядном слове
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//import from macros.mlb;
#ifndef MEM
#define MEM(addr)  (*((unsigned volatile*)(addr)))
#endif

//**********  Local ********************
//data "LocalSRAM"
	//NormMul:long=9B7496D6hl;
	//UnNorm:long[2];
	static long long NormMul=0x9B7496D6;
	static int UnNorm[2];
	
	//Void:word;
	static int Void;
	static int gr0;
	static int gr1;
	static int gr2;
	static int gr3;
	static int gr4;
	static int gr5;
	static int gr6;
	static int gr7;

	
	static int* ar1;
	

	
/*	
	FixArctanTable:word[16]=
	(
		0C90Fh,
		076B1h,
		03EB6h,
		01FD5h,
		0FFAh,
		07FFh,
		03FFh,
		01FFh,
		0FFh,
		07Fh,
		03Fh,
		01Fh,
		0Fh,
		07h,
		03h,
		01h
	);
*/

int FixArctanTable[16]={
		0x0C90F,
		0x076B1,
		0x03EB6,
		0x01FD5,
		0x0FFA,
		0x07FF,
		0x03FF,
		0x01FF,
		0x0FF,
		0x07F,
		0x03F,
		0x01F,
		0x0F,
		0x07,
		0x03,
		0x01
	};

//--------------------------------------------
/*
macro ROTATE(Shift)
	if < delayed skip 6	with gr1=gr4 A>>Shift;
		[Void]=gr7 with gr2=gr0 A>>Shift;
	delayed skip 6 with gr0-=gr1;
		gr3=[ar1++] with gr4+=gr2;
		gr7-=gr3;
	//---------------------
	nul;
	gr0+=gr1;
	gr3=[ar1++] with gr4-=gr2;
	gr7+=gr3;
end ROTATE;
*/

//-------------------------------------------
/*
macro ATANROTATE(Shift)
	if < delayed skip 6	with gr1=gr4 A>>Shift;
		[Void]=gr7 with gr2=gr0 A>>Shift;
	delayed skip 6 with gr0+=gr1;
		gr3=[ar1++] with gr4-=gr2;
		gr7+=gr3 noflags;
	//---------------------
	nul;
	gr0-=gr1;
	gr3=[ar1++] with gr4+=gr2;
	gr7-=gr3 noflags;
end ATANROTATE;
*/
void ATANROTATE(int Shift){
	gr1=gr4>>Shift;
	Void=gr7;	gr2=gr0>>Shift;
	if (gr4 < 0) {
		gr0-=gr1;
		gr3=MEM(ar1++); gr4+=gr2;
		gr7-=gr3;
	}
	else {
		gr0+=gr1;
		gr3=MEM(ar1++); gr4-=gr2;
		gr7+=gr3;
	}
}


//*********** TEXT ****************


//global _nmppcFixArcTan32 :label;
//<_nmppcFixArcTan32>



int nmppcFixArcTan32(int val){

	gr4 = val;
//.branch;
	//ar5 = sp-2;
	//push ar0,gr0;
	//push ar1,gr1;
	//push ar2,gr2;
	//push ar3,gr3;
	//push ar4,gr4;
	//push ar5,gr5;
	//push ar6,gr6;
	//gr4 = [--ar5];
	
	//gr0 -Xi
	//gr1 -Shifted gr4;
	//gr3 - +/- Angle=Arctan(pow(2,-i))
	//gr4 -Yi
	//gr5 -New_Y
	//gr2 -Shifted gr0
	//gr7 - Angle
	
	// gr0=10000h with gr7-=gr7;
	gr0=0x10000; gr7=0;
	// ar1=FixArctanTable with gr4;
	ar1=FixArctanTable;

	//if < delayed skip 6	with gr1=gr4;
	//	[Void]=gr7 with gr2=gr0;
	//delayed skip 6 with gr0+=gr1;
	//	gr3=[ar1++] with gr4-=gr2;
	//	with gr7+=gr3 noflags;
	//nul;
	//gr0-=gr1;
	//gr3=[ar1++] with gr4+=gr2;
	//gr7-=gr3 noflags;
	gr1=gr4;
	Void=gr7; gr2=gr0;
	if (gr4<0){
		gr0-=gr1;
		gr3=MEM(ar1++); gr4+=gr2;
		gr7-=gr3;
	}
	else {
		gr0+=gr1;
		gr3=MEM(ar1++); gr4-=gr2;
		gr7+=gr3 ;
	}
	//---------------------

	ATANROTATE(1);
	ATANROTATE(2);
	ATANROTATE(3);
	ATANROTATE(4);
	ATANROTATE(5);
	ATANROTATE(6);
	ATANROTATE(7);
	ATANROTATE(8);
	ATANROTATE(9);
	ATANROTATE(10);
	ATANROTATE(11);
	ATANROTATE(12);
	ATANROTATE(13);
	ATANROTATE(14);
	ATANROTATE(15);
	//pop ar6,gr6;
	//pop ar5,gr5;
	//pop ar4,gr4;
	//pop ar3,gr3;
	//pop ar2,gr2;
	//pop ar1,gr1;
	//pop ar0,gr0;
	
return gr7;	
}

//.wait;
//end ".text_nmplс";
