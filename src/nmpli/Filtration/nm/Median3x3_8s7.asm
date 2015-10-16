//------------------------------------------------------------------------
//
//  $Workfile:: ResizeDown2Y_C7.as              $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2005/02/10 12:36:39 $
//
//! \if file_doc
//!
//! \file   ResizeDown2Y_C7.asm
//! \author S. Mushkaev
//! \brief  Median filter 3x3 (9.0 - clocks per pixel)
//!
//! \endif
//!
//------------------------------------------------------------------------

//***************************************************************************/
//*                                                                         */
//*                    Neuroprocessor NM6403 SDK v.1.0                      */
//*                                                                         */
//*              Median filter 3x3 for 8bit-pixel matrix 384x288            */
//*                                                                         */
//*                 Filter performance :  9.0 - cycles per pixel            */
//*                 Src - In Local                                          */
//*                 Dst - In Global                                         */
//*                 Text - In Local                                         */ 
//*                                                                         */
//*                1999 (c) RC Module Inc., Moscow, Russia                  */
//***************************************************************************/
                                                                                       
global _CopyFrame__FPcPci: label;
global _void._.8.8CopyFrame.1char._.0.9._char._.0.9._int.2 :label;
global _ShiftLeft__FPcPci:label;
global _void._.8.8ShiftLeft.1char._.0.9._char._.0.9._int.2 :label;
global _ShiftRight__FPcPci:label;
global _void._.8.8ShiftRight.1char._.0.9._char._.0.9._int.2 :label;

//--------- Matrix parameters --------------------------------------------------------
// Width=384;				// Разрядность матрицы по Х (Ширина матрицы в 8р. элементах) (Кратно 8)
// Height=288;			// Разрядность матрицы по Y (Высота матица  в строках ) (кратно 32) 
//------------------------------------------------------------------------------------
// Max_X=Width/8;		// Разрядность матрицы по Х в 64-битных векторах 
// Max_Y=Height;			// Разрядность матрицы по Y в строках 
// Max_Y_32 = Height/32;	// Высота матрицы в блоках по 32 вектора в каждом


//**************** LOCAL ************************************************************
data ".data_nmpli_L"
	Width2_8:word;
	Height_32:word;

	//global	_SrcMatrix	:long[Max_X*Max_Y] = (0hl dup Max_X*Max_Y); // Исходная матица
	//--------------------------------------------------------
	L0		:word;//long [Height] = ( 0hl dup Height );		// Промежуточный буфер
	L1		:word;//long [Height] = ( 0hl dup Height );		// Промежуточный буфер
	L2		:word;//long [Height] = ( 0hl dup Height );		// Промежуточный буфер
 	ShiftMatrix : long [32] =  // Матрица, разделяющая каждые 3 соседних элемента по разным массивам, для возможности их дальнейшего сравнения между собой
				(
				// ***** Сдвиг матрицы влево на один байт ***** 
					// Сдвиг центрального вектора на 8 бит влево
					0000000000000100hl,
					0000000000010000hl,
					0000000001000000hl,
					0000000100000000hl,
					0000010000000000hl,
					0001000000000000hl,
					0100000000000000hl,
					0000000000000000hl,
					// Перенос старшего байта из правого(старшего) вектора в младший байт центрального
					0000000000000000hl,
					0000000000000000hl,
					0000000000000000hl,
					0000000000000000hl,
					0000000000000000hl,
					0000000000000000hl,
					0000000000000000hl,
					0000000000000001hl,
				//***** Cдвиг матрицы вправо на один байт ****
					// Сдвиг центрального вектора на 8 бит вправо
					0000000000000000hl,
					0000000000000001hl,
					0000000000000100hl,
					0000000000010000hl,
					0000000001000000hl,
					0000000100000000hl,
					0000010000000000hl,
					0001000000000000hl,
					// Перенос младшего байта из левого(младшего) вектора в старший байт центрального
					0100000000000000hl,
					0000000000000000hl,
					0000000000000000hl,
					0000000000000000hl,
					0000000000000000hl,
					0000000000000000hl,
					0000000000000000hl,
					0000000000000000hl
				);
	AR6 : word =0;												// Буффер для хранения ar6
	GR5 : word =0;
		
end ".data_nmpli_L";

//**********  Global ********************
data ".data_nmpli_G"
	//global  _DstMatrix	:long [Max_X*Max_Y] = (0hl dup Max_X*Max_Y);	// Результирующая матрица
	//------------------------------------------------------------
	ShiftRightMask	:long = 0FEFEFEFEFEFEFEFEhl;			// Маска для сдвига вправо
	G0	:word;//long [Height] = ( 0hl dup Height );				// Промежуточный буфер
	G1	:word;//long [Height] = ( 0hl dup Height );				// Промежуточный буфер
	G2	:word;//long [Height] = ( 0hl dup Height );				// Промежуточный буфер
	GDiffMask :word;//long [Height] = ( 0hl dup Height );			// Буффер для хранения разности сравниваемых векторов
	//-------------------------------------------------------------
end ".data_nmpli_G";

macro PUSH_REGS()
    push ar0, gr0;
    push ar1, gr1;
    push ar2, gr2;
    push ar3, gr3;
    push ar4, gr4;
    push ar5, gr5;
    push ar6, gr6;
end PUSH_REGS;

macro POP_REGS()
    pop ar6, gr6;
    pop ar5, gr5;
    pop ar4, gr4;
    pop ar3, gr3;
    pop ar2, gr2;
    pop ar1, gr1;
    pop ar0, gr0;
end POP_REGS;


macro WTW_REG(reg)
.wait;
   nb1 = reg;
   //nb1 = 80808080h;
   wtw;											
.branch;
end WTW_REG;

//*********** TEXT ****************
begin ".text_nmpli"


//////////////////////////////////////////////////////////////////////////////////////////
//																						//
//    Проседура разделения каждых трех соседних элементов в текущей колонке векторов	//
//    в разные массивы. Cдига текущей колонки влево и вправо на один элемент			//
//																						//
//////////////////////////////////////////////////////////////////////////////////////////
<ShiftLR> 
.branch;
	//------- INPUT PARAMETERS --------------------------------------
	//ar0 = Src1				// Исходная матрица			(Global)
	//ar4 = L0;				// Колонка сдвинутая вправо	(Local)
	//ar5 = G0;				// Колонка сдвинутая влево	(Global)
	//ar6 = ShiftMatrix			// Матрица сдвига			(Local)
	//---------------------------------------------------------------
	nul;
	ar1 = ar0 - 2; 				// левая соседняя колонка отн. текущей центральной в SrcMatrix  
	ar2 = ar0 + 2;				// правая соседняя колонка отн. текущей центральной в SrcMatrix  
	gr0 = [Width2_8];				// Шаг чтения для последовательного считывания центр. колонки 
	gr6 = -2*32 with gr1=gr0;	// Смещ. для восстановления ar6 + Шаг чтения для последовательного считывания левой. колонки 
	gr7 = [Height_32] with gr2=gr0;// Цикл. счетчик + Шаг чтения для последовательного считывания правой. колонки    
	gr3 = 80808080h with gr7--;
	<ShiftLRColumn>
		rep 32 ram = [ar0++gr0],ftw with vsum ,data,0;		//G* Центр. колонка SrcMatrix => RAM со сдвигом вправо (влево в векторном виде) 
		WTW_REG(gr3);
		rep 32 data = [ar1++gr1],ftw with vsum ,data,afifo;	//G* Перенос старшего байта из левой колонки в младший байт колонки сдвигаемой вправо(влево в векторном виде)
		ar6=ar6 + gr6 ;										//* Восстановление указателя на Shift Matrix
		WTW_REG(gr3);
		rep 32 [ar4++] = afifo, ftw with vsum , ram,0;		//G Запись колонки сдвинутой вправо в L0
		WTW_REG(gr3);
		rep 32 wfifo = [ar6++];								//L* Загрузка матицы сдвига
		rep 32 data = [ar2++gr2],ftw with vsum ,data,afifo;	//G* Перенос младшего элемента из правой колонки в старший элемент колонки сдвигаемой влево(вправо в векторном виде)
		WTW_REG(gr3);		
	if <>0 delayed goto ShiftLRColumn 	with gr7--;								//*
		rep 32 [ar5++] = afifo;								//L* запись колонки сдвинутой влево в G0
		nul;
												
return;
.wait;

//////////////////////////////////////////////////////////////////////////////////////////
//																						//
//    Проседура сравнения и выбора минимального и максимального из двух	векторов		//
//		DstMin=Min(Src1,SrcMatrix); -> Local											//
//		DstMax=Max(Src1,SrcMatrix); -> Global											//
//																						//
//////////////////////////////////////////////////////////////////////////////////////////
<Dst_MinL_MaxG> 
.branch;
//.wait;
//------------ INPUT PARAMETERS ----------------
 	//ar0 = Src1;	Первый сравниваемый вектор	// Local 
	//ar1 = Src2;	Второй ср.вектор -DstMatrix	// Global 
	//ar4 = DiffMask; Разность между векторами	// Global 
	//ar3 = DstMin;	  Минимум(Приемник)			// Local  
	//ar6 = DstMax;	  Максимум(Приемник)		// Global 
//---------------------------------------------
	gr4 = ar7;
	gr1 = [Width2_8];
	gr6 = [Height_32] ;
	
	ar2 = ar1 with gr2 = gr1;
	ar7 = ar1 with gr7 = gr1;
	ar5 = ar4 with gr6--;
	
	<Dst_MinL_MaxG_Column>
		rep 32  ram = [ar0++];							//* Загрузка  1 вектора из Src1
		rep 32 data = [ar1++gr1] with ram - data;		// Вычитание 2 вектора из первого
		rep 32 [ar4++]= afifo with activate afifo;		// Запись в DiffMask разности, получение маски сравнения
		
		rep 32 data = [ar2++gr2] with mask afifo,ram,data;	// Сборка минимумов из 1 и 2 вектора
		rep 32 [ar3++] = afifo;							//* Запись минимума в DstMin
		rep 32 data = [ar5++] with activate data ;		//* Загрузка из DiffMask разности и получение маски сравнения
	
	if <>0  delayed goto Dst_MinL_MaxG_Column with gr6--;
		rep 32 data = [ar7++gr7] with mask afifo,data,ram; // Сборка максимумов из 1 и 2 вектора
		rep 32 [ar6++]=afifo;							//* Запись максимума в DstMax
		
	ar7 = gr4;
return;
.wait;


//////////////////////////////////////////////////////////////////////////////////////////
//																						//
//    Проседура сравнения и выбора минимального и максимального из двух					//
//		DstMin=Min(Src1,Src2); -> Local													//
//		DstMax=Max(Src1,Src2); -> Global												//
//																						//
//////////////////////////////////////////////////////////////////////////////////////////
<MinL_MaxG> 
.branch;
//.wait;
//------------ INPUT PARAMETERS ----------------
 	//ar0 = Src1;	Первый сравниваемый вектор	// Local  
	//ar1 = Src2;	Второй сравниваемый	вектор	// Global 
	//ar4 = DiffMask; Разность между векторами	// Global 
	//ar3 = DstMin;	  Минимум(Приемник)			// Local  
	//ar6 = DstMax;	  Максимум(Приемник)		// Global 
//---------------------------------------------
	gr6 = ar7;
	gr1 = [Width2_8];
	gr7 = [Height_32] ;
	
	ar2 = ar1 with gr2 = gr1;
	ar7 = ar1 with gr2 = gr1;
	ar5 = ar4 with gr7--;
	
	<MinL_MaxG_Column>
		rep 32  ram = [ar0++];							//* Загрузка  1 вектора из Src1
		rep 32 data = [ar1++] with ram - data;			// Вычитание 2 вектора из первого
		rep 32 [ar4++]= afifo with activate afifo;		// Запись в DiffMask разности, получение маски сравнения
		
		rep 32 data = [ar2++] with mask afifo,ram,data;	// Сборка минимумов из 1 и 2 вектора
		rep 32 [ar3++] = afifo;							//* Запись минимума в DstMin
		rep 32 data = [ar5++] with activate data ;		//* Загрузка из DiffMask разности и получение маски сравнения
			
		
	if <>0  delayed goto MinL_MaxG_Column with gr7--;
		rep 32 data = [ar7++] with mask afifo,data,ram; // Сборка максимумов из 1 и 2 вектора
		rep 32 [ar6++]=afifo;							//* Запись максимума в DstMax
		
	ar7 = gr6;
return;
.wait;


//////////////////////////////////////////////////////////////////////////////////////////
//																						//
//    Проседура сравнения и выбора минимального и максимального из двух					//
//		DstMin=Min(Src1,Src2); -> Global
//		DstMax=Max(Src1,Src2); -> Local
//																						//
//////////////////////////////////////////////////////////////////////////////////////////
<MaxL_MinG>
.branch;
//.wait;
//------------ INPUT PARAMETERS ----------------
 	//ar0 = Src1;	Первый сравниваемый вектор	// Local  
	//ar1 = Src2;	Второй сравниваемый	вектор	// Global 
	//ar4 = DiffMask; Разность между векторами	// Global 
	//ar3 = DstMin;	  Минимум(Приемник)			// Local  
	//ar6 = DstMax;	  Максимум(Приемник)		// Global 
//---------------------------------------------
	gr6 = ar7;
	gr1 = [Width2_8];
	gr7 = [Height_32] ;
	
	ar2 = ar1 with gr2 = gr1;
	ar7 = ar1 with gr2 = gr1;
	ar5 = ar4 with gr7--;
	
	<MaxL_MinG_Column>
		rep 32  ram = [ar0++];							//* Загрузка  1 вектора из Src1
		rep 32 data = [ar1++] with data - ram ;			// Вычитание 2 вектора из первого
		rep 32 [ar4++]= afifo with activate afifo;		// Запись в DiffMask разности, получение маски сравнения
		
		rep 32 data = [ar2++] with mask afifo,ram,data;	// Сборка максимумов из 1 и 2 вектора
		rep 32 [ar3++] = afifo;							//* Запись максимума в DstMax
		rep 32 data = [ar5++] with activate data ;		//* Загрузка из DiffMask разности и получение маски сравнения
			
		
	if <>0  delayed goto MaxL_MinG_Column with gr7--;
		rep 32 data = [ar7++] with mask afifo,data,ram; // Сборка минимумов из 1 и 2 вектора
		rep 32 [ar6++]=afifo;							//*Запись минимума в DstMin 
		
	ar7 = gr6;
return;
.wait;

//////////////////////////////////////////////////////////////////////////////////////////
//																						//
//    Проседура сравнения и выбора минимального из трех элементов						//
//	  Dst=Min( Min(Src1,Src2),Src3)														//
//																						//
//////////////////////////////////////////////////////////////////////////////////////////
<MinMin>  
.branch;
//.wait;
	//------- INPUT PARAMETERS -------------------------------------
	//ar0 = Src1; Первый сравниваемый вектор		Global
	//ar1 = Src2; Второй сравниваемый вектор		Global
	//ar3 = Src3; Третий стравниваемый вектор		Global
	//ar6 = DstMin ; Результат сравнения			Local
	//--------------------------------------------------------------
	gr7 = [Height_32];			// Счетчик
	ar4 = ar1;				// Второй сравниваемый операнд	
	ar2 = ar3 with gr7--;	// Третий сравниваемый операнд	
	<MinMin_Column>
		rep 32 ram = [ar0++];							//* Загрузка  Src1
		rep 32 data = [ar4++] with ram - data ;			// Вычитание Src2 из Src1
 		rep 32 with activate afifo;						// Получение маски сравнения 
		rep 32 data = [ar1++] with mask afifo,ram,data; // Сборка минимумов из Src1 и Src2
		rep 32 [ar6],ram= afifo;						// Сохраниение минимумов в RAM
		rep 32 data = [ar2++] with ram - data;			// Вычитание Src3 из Min(Src1,Src2)
		rep 32 with activate afifo;						// Получение маски сравнения 
	if <>0 delayed goto MinMin_Column with gr7--;		
		rep 32 data = [ar3++] with mask afifo,ram,data;	// Сборка минимумов из Src3 и Min(Src1,Src2)
		rep 32 [ar6++]=afifo;							//* Запись минимума в DstMin
return;
.wait;
//////////////////////////////////////////////////////////////////////////////////////////
//																						//
//    Проседура сравнения и выбора минимального из трех элементов						//
//	  Dst=Max( Min(Src1,Src2),Src3)														//
//																						//
//////////////////////////////////////////////////////////////////////////////////////////
<MinMax> 
.branch;
	//------- INPUT PARAMETERS -------------------------------------
	//ar0 = Src1; Первый сравниваемый вектор		Global
	//ar1 = Src2; Второй сравниваемый вектор		Global
	//ar3 = Src3; Третий стравниваемый вектор		Global
	//ar6 = Dst ; Результат сравнения				Local
	//--------------------------------------------------------------
	gr7 = [Height_32];			// Счетчик
	ar4 = ar1;				// Второй сравниваемый операнд	
	ar2 = ar3 with gr7--;	// Третий сравниваемый операнд	
	<MinMax_Column>
		rep 32 ram  = [ar0++];							//* Загрузка  Src1
		rep 32 data = [ar4++] with ram - data ;			// Вычитание Src2 из Src1
 		rep 32 with activate afifo;						// Получение маски сравнения 
		rep 32 data = [ar1++] with mask afifo,ram,data;	//* Сборка минимумов из Src1 и Src2
		rep 32 [ar6],ram= afifo;						// Сохраниение минимумов в RAM
		rep 32 data = [ar2++] with ram - data;			// Вычитание Src3 из Min(Src1,Src2)
		rep 32 with activate afifo;						// Получение маски сравнения 
	if <>0 delayed goto MinMax_Column with gr7--;		
		rep 32 data = [ar3++] with mask afifo,data,ram;	//Сборка максимумов из Src3 и Min(Src1,Src2)
		rep 32 [ar6++]=afifo;							//* Запись максимумов в DstMax
return;
.wait;


//////////////////////////////////////////////////////////////////////////////////////////
//																						//
//			Dst=Max(Min(Max(Max(Src1,Src2),Src3),Src4),Src5) 							//
//																						//
//////////////////////////////////////////////////////////////////////////////////////////

<MaxMaxMinMax> 
.branch;
//.wait;
	//------- INPUT PARAMETERS -------------------------------------
	//ar4 = Src1; Первый сравниваемый вектор    (Global)
	//gr1 = Src2; Второй сравниваемый вектор	(Global)
	//gr2 = Src3; Третий сравниваемый вектор 	(Global)
	//gr4 = Src4; Четвертый сравниваемый вектор (Global)
	//gr6 = Src5; Пятый сравниваемый вектор		(Global)
	//ar3 = Dst ; Результат 					(Local)
	//--------------------------------------------------------------
	ar0 = 0;
	gr5 = 2*32 with gr0=gr1;
	gr7 = [Height_32];										// Счетчик
	gr3 = [Width2_8] with gr7--;
	<MaxMaxMinMaxColumn>
		rep 32 ram = [ar4++];							//* Загрузка  Src1
			ar1 = ar0 + gr0;							//ar1=Src2
			ar2 = ar0 + gr0 with gr0 = gr2 noflags;				//ar2=Src2
		rep 32 data = [ar1++] with data - ram ;			// Вычитание Src2 из Src1
		rep 32 with activate afifo;						// Получение маски сравнения 
		rep 32 data = [ar2++] with mask afifo,ram,data;	//* Сборка Max(Src1,Src2)
		rep 32 [ar4],ram= afifo;						// Запись результата стравнения в RAM
			ar1 = ar0 + gr0;							//ar1=Src3
			ar2 = ar0 + gr0 with gr0 = gr4 noflags;				//ar2=Src3
		rep 32 data = [ar1++] with data - ram;			// Вычитание Src3 из Max(Src1,Src2)
		rep 32 with activate afifo;						// Получение маски сравнения 
		rep 32 data = [ar2++] with mask afifo,ram,data;	// Сборка Max(Max(Src1,Src2),Src3)
		rep 32 [ar4],ram=afifo;							// Запись результата стравнения в RAM
			ar1 = ar0 + gr0;							//ar1=Src4
			ar2 = ar0 + gr0 with gr0 = gr6 noflags;				//ar2=Src4
		rep 32 data = [ar1++] with ram - data ;			// Вычитание Max(Max(Src1,Src2),Src3) из Src4
		rep 32 with activate afifo;						// Получение маски сравнения 
		rep 32 data = [ar2++] with mask afifo,ram,data;	// Сборка Min(Max(Max(Src1,Src2),Src3),Src4)
		rep 32 [ar4],ram = afifo;						// Запись результата стравнения в RAM
			ar1 = ar0 + gr0 with gr1+=gr5 noflags;		//ar1=Src5, Src2=Src2+2*32
			ar2 = ar0 + gr0 with gr2+=gr5 noflags;		//ar2=Src5,	Src3=Src3+2*32
			with gr4+=gr5 noflags;								//			Src4=Src4+2*32
			with gr6+=gr5 noflags;								//			Src5=Src5+2*32
			with gr0 = gr1 noflags;
		rep 32 data = [ar1++] with data - ram;			// Вычитание Src5 из Min(Max(Max(Src1,Src2),Src3),Src4)
		rep 32 with activate afifo;						// Получение маски сравнения 
	if <>0  delayed goto MaxMaxMinMaxColumn with gr7--;							
		rep 32 data = [ar2++] with mask afifo,ram,data;	// Сборка Max(Min(Max(Max(Src1,Src2),Src3),Src4),Src5)
		rep 32 [ar3++gr3] = afifo;						// Запись результата стравнения

return;
.wait;


///////////////////////////////////////////////////////////////////////////////////////
//***********************************************************************************//
//*																					*//
//*	Процедура медианной фильтрации окном 3х3 над массивом из 8-разрядных элементов	*//
//*																					*//
//***********************************************************************************//
///////////////////////////////////////////////////////////////////////////////////////
//global _IMG_Median3x3__F5nm8s7P5nm8s7PiiPvPv :label;
//<_IMG_Median3x3__F5nm8s7P5nm8s7PiiPvPv>
<_void._.8.8IMG_Median3x3.1class._nm8s7._.0.9._class._nm8s7._.0.9._int.9._int.9._void._.0.9._void._.0.2>
global _IMG_Median3x3__FPcPciiPvPv :label;
global _void._.8.8IMG_Median3x3.1char._.0.9._char._.0.9._int.9._int.9._void._.0.9._void._.0.2 :label;
<_IMG_Median3x3__FPcPciiPvPv>
<_void._.8.8IMG_Median3x3.1char._.0.9._char._.0.9._int.9._int.9._void._.0.9._void._.0.2>
.branch;
    ar5 = ar7 - 2;
    PUSH_REGS();
//******* Предварительная загрузка WFIFO *******************************************************
	ar6 = ShiftMatrix;	// Матрица сдвига
	gr3 = 80808080h;      
	nb1 = gr3;
	f1cr= 80808080h;
	sb  = 02020202h;
	rep 32 wfifo = [ar6++],ftw;
	WTW_REG(gr3);
	[AR6]=ar6;			// Сохранение ar6

//***[0]****************************************************************************************
	ar0 = [--ar5];				// Src - SrcMatrix Исходая матрица
	ar4 = [--ar5];				// Dst - DstMatrix Матрица приемник,сдвинутая на бит вправо 
	gr0 = [--ar5];				// Width
	gr4 = [--ar5] with gr0>>=2;	// Height
	gr1 = [--ar5];				// Local Buffer
	gr2 = [--ar5];				// Global Buffer
	gr7 = gr4<<1;
	[L0]=gr1 with gr1+=gr7;
	[L1]=gr1 with gr1+=gr7;
	[L2]=gr1;
	[G0]=gr2 with gr2+=gr7;
	[G1]=gr2 with gr2+=gr7;
	[G2]=gr2 with gr2+=gr7;
	[GDiffMask]=gr2;
	[Width2_8]=gr0 with gr4>>=5;
	[Height_32]=gr4;

	//call ShiftRight;
//*******************************************************************************************
	ar1 = ar0;//[ar5++];		// Исходная матрица - DstMatrix (_SrcMatrx-сдвинутая на 1 бит вправо)
	ar2 = ar4;//[ar5++];		// Результирующая матрица -SrcMatrix
	gr5 = [Width2_8];			// Счетчик = Число колонок
	gr1 = 2 with gr5>>=1;		// Шаг перехода от колонки к колонке
	[GR5]=gr5 with gr2 = gr1;	// Шаг перехода от колонки к колонке;
    push ar5, gr5;
	push ar2,gr2;		// DstMatrix=> stack
	push ar1,gr1;		// SrcMatrix=> stack

	<AllColumn>
	//***[1]*****************************************************************************************		
		pop ar1,gr1;
		ar0 = ar1;			// Src1- _SrcMatrix;
		push ar1,gr1;
		ar4 = [G0];			// Dst1- колонка сдвинутая влево
		ar5 = [L0];			// Dst2- колонка сдвинутая вправо
		delayed call ShiftLR;
		ar6 = [AR6];
		[AR6] = ar6;
	//***[2]*****************************************************************************************
		ar0 = [L0];			// Src1 - колонка сдвинутая влево 
		ar1 = [G0];			// Src2 - колонка сдвинутая вправо
		ar4 = [GDiffMask];	
		ar3 = [L1];			// DstMax - Максимум
		delayed call MaxL_MinG;
		ar6 = [G1];			// DstMin - Минимум
	//***[3]*****************************************************************************************		
		pop ar0,gr0;
		ar1 = ar0;			// Src2- _DstMatrix;
		ar0 = ar0 + gr0;	// Переход к следующей колонке
		push ar0,gr0;
		ar0 = [L1];			// Src1 - Максимум от [1]
		ar4 = [GDiffMask];	
		ar3 = [L0];			// DstMin - Минимум 
		delayed call Dst_MinL_MaxG;
		ar6 = [G0];			// DstMax - Максимум
	//***[4]****************************************************************************************
		ar0 = [L0];			// Src1 - Минимум от [3]
		ar1 = [G1];			// Src2 - Минимум от [2]
		ar4 = [GDiffMask];	
		ar3 = [L1];			// DstMax - Максимум
		delayed call MaxL_MinG;
		ar6 = [G2];			// DstMin - Минимум
	//***[5]*****************************************************************************************
		ar0 = [G0];			// Src1 - Максимум от [3]
		ar3 = [G0];			// Src3 - Максимум от [3] 
		ar6 = [L0];			// DstMin - Минимум 
		delayed call MinMin;
			ar1 = ar0-2;	// Src2 - Максимум от [3]
	//***[7]*****************************************************************************************
		ar0 = [L1];			// Src1 - Максимум от [4]
		ar4 = [GDiffMask];
		ar3 = [L2];			// DstMin - Минимум 
		ar6 = [G0];			// DstMax - Максимум
		delayed call MinL_MaxG;
			ar1 = ar0+2;	// Src2 - Максимум от [4]
	//***[8]*****************************************************************************************
		ar0 = [L1];
		ar1 = [G0];			// Src2 - Максимум от [7]	
		ar3 = [L2];			// Src3 - Минимум от  [7]	
		ar6 = [G1];			// Dst - Минимум
		delayed call MinMax;
			ar0-=2;			// Src1 - Максимум от [4]	
	//***[10]*****************************************************************************************
		ar0 = [L0];			// Src1 - Минимум от [6]
		ar1 = [G1];			// Src2 - Среднее от [8]
		ar4 = [GDiffMask];
		ar3 = [L1];			// DstMin - Минимум 
		delayed call MinL_MaxG;	
			ar6 = [G0];		// DstMax - Максимум
	//***[11]*****************************************************************************************
		pop ar1,gr1;
		 pop ar5,gr5;
		  ar3 = ar5;		// Dst - _SrcMatrix;
		  ar5 = ar5 + gr5;	// Переход к следующей колонке
		 push ar5,gr5;
		push ar1,gr1;

		gr4 = [G2];						// Максимум от [4]
		ar4 = gr4 with gr1 = gr4 - gr5; // Src1 G2-2;  
										// Src2
		gr6 = [L1] with gr2 = gr4 + gr5;// Src5 G2+2
										// Src3
		delayed call MaxMaxMinMax;
			gr4 = [G0];						// Src4
	//********************************************************************************************
		gr5=[GR5];
		gr5--;
	if <>0 delayed goto AllColumn;
		[GR5]=gr5;
//***[15]*****************************************************************************************
	pop ar1,gr1;
	pop ar1,gr1;
    pop ar5, gr5;
	//ar0 = [--ar5];	// Src1 - Отфильтрованная матрица 
	//ar4 = [--ar5];	// Dst - Матрица , сдвинутая влево на один бит
	//call ShiftLeft;
//***********************************************************************************************
	ftw;
	nul;
	
    POP_REGS();
	return;
.wait;

<_CopyFrame__FPcPci>
<_void._.8.8CopyFrame.1char._.0.9._char._.0.9._int.2>
.branch;
    ar5 = ar7 - 2;
    push ar0, gr0;
    push ar4, gr4;

    ar0 = [--ar5];  //  Source Buffer; Size: SIZE8
    ar4 = [--ar5];  //  Result Buffer; Size: SIZE8
    gr0 = [--ar5];	//  Length in chars
    gr0>>=8;
	gr0--;
	<CL7>    
    if > delayed goto CL7 with gr0--;
		rep 32 data = [ar0++] with data;
		rep 32 [ar4++] = afifo;

    pop ar4, gr4;
    pop ar0, gr0;
    return;
.wait;


//////////////////////////////////////////////////////////////////////////////////////////
//																						//
//	Cдвиг матрицы на один бит влево - преобразование 7-разрядного со знаком в			//
//        8-разрядоное безнаковое число													//
//																						//
//////////////////////////////////////////////////////////////////////////////////////////
<_ShiftLeft__FPcPci> 
<_void._.8.8ShiftLeft.1char._.0.9._char._.0.9._int.2>
.branch;
	//------- INPUT PARAMETERS --------------------------------------
	//ar0 = _Src; (_SrcMatrix)				// Колонка сдвинутая влево	
	//ar4 = _Dst; (_DstMatrix)				// Колонка сдвинутая вправо 
	//---------------------------------------------------------------
    ar5 = ar7 - 2;
    push ar0, gr0;
    push ar4, gr4;

    ar0 = [--ar5];  //  Source Buffer; Size: SIZE8
    ar4 = [--ar5];  //  Result Buffer; Size: SIZE8
    gr0 = [--ar5];  //	Length in chars
    with gr0>>=8;
	nb1 = 80808080h with gr0--;
	wtw;

	<ShiftLeftAll_>	
	if > delayed goto ShiftLeftAll_ with gr0--;
		rep 32 data = [ar0++] with  data+data;	//* Cдвиг вектора на один бит влево 
		rep 32 [ar4++] = afifo;					//* запись колонки сдвинутой вправо в G0

	pop ar4,gr4;
	pop ar0,gr0;
return;
.wait;
//////////////////////////////////////////////////////////////////////////////////////////
//																						//
//	Cдвиг матрицы на один бит враво - преобразование 8-разрядоного безнакового числа в	//
//         7-разрядное со знаком														//
//																						//
//////////////////////////////////////////////////////////////////////////////////////////
<_ShiftRight__FPcPci> 
<_void._.8.8ShiftRight.1char._.0.9._char._.0.9._int.2>
.branch;
	//------- INPUT PARAMETERS --------------------------------------
	//ar0 = _SrcMatrix;				//L Исходная Матрица 
	//ar4 = _DstMatrix;				//G Матрица приемник,сдвинутая на бит вправо
	//ar6 = ShiftRightMask			//G Маска для сдвига вправо
	//---------------------------------------------------------------
    ar5 = ar7 - 2;
    push ar0, gr0;
    push ar4, gr4;

	ar4 = ShiftRightMask; // Матрица сдвига
	rep 32 ram = [ar4];	  // Маска для сдвига вправо

	
	ar0 = [--ar5];  //  Source Buffer; Size: SIZE8
    ar4 = [--ar5];  //  Result Buffer; Size: SIZE8
    gr0 = [--ar5];  //	Length in chars
    with gr0>>=8;
    with gr0--;

	<ShiftRightAll_>	
 	if <>0 delayed goto ShiftRightAll_ with gr0--;			
		rep 32 data = [ar0++] with  mask ram, shift data, 0;	//* Перенос старшего элемента из правой колонки в младший элемент колонки сдвигаемой влево
		rep 32 [ar4++] = afifo;									//* запись колонки сдвинутой вправо
	
	pop ar4,gr4;
	pop ar0,gr0;
	return;
.wait;

end ".text_nmpli";