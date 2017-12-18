

/** \ru 
	\page intro Введение 
	\ingroup CORE_Group
	\en 
	\page intro Introduction
	\ingroup CORE_Group
	\~
	
	\ru Функции векторного ядра библиотеки
	\en Functions of vec core
    
		\~
    \ru Функции различных библиотек: nmplv,nmpls, nmpli, nmplm и др. , имеющие С++ интерфейсы, в своей реализации 
        используют вызовы функций ядра. Функции ядра не имеют
        С++ интерфейса. Их вызов возможен только из ассемблера
        процессора NeuroMatrix. Передача параметров и настройка функций 
        производится через регистры.
	\en Library functions with C++ interface use core functions in 
        implementation. Core functions have no C++ interface. Their 
        call is possible from assembler of NeuroMatrix only. Parameter
        transmission and function adjustment is caaried out over registers.

		\~
	\ru	Одна и та же функция ядра может использоваться при реализации одной 
        или нескольких функций библиотеки. Функции ядра также могут быть использованы
        для реализации пользовательских функций.
        Использование функций ядра позволяет минимизировать время разработки, 
        уменьшить размер кода и получить максимальную производительность. 
    \en The same core function could be used in implementation of several
        library functions. Moreover core functions could be used in user
        functions implementation. Usage of core functions allow to 
        minimize time for function development, decrease code size, 
        and get maximum efficiency.	\~
*/



	/**
    *
    * \ru
    *     	\defgroup vCore  Элементарные функции 
    *  	 	\ingroup CORE_Group
    * \en
    *     	\defgroup vCore Kernel functions
    *  		\ingroup CORE_Group
    * \~
    * 
	*/


	/**
    *
    * \ru
    *     \defgroup vsum  функции взвешенного суммирования
    *  		\ingroup CORE_Group
    * \en
    *     \defgroup vsum Kernel functions
    *  		\ingroup CORE_Group
    * \~
    * 
	*/

	/**
    *
    * \ru
    *     \defgroup vcomplex Целевые функции 
	*  		\ingroup CORE_Group
    * \en
    *     \defgroup vcomplex Kernel functions
    *  		\ingroup CORE_Group
    * \~
    * 
	*/


//-----------------------------------------------------------------------------
  


//---------------------------------------------------------------------------------
    /**
		\~
	\defgroup vec_0_sub_data
    \ingroup vCore
    
        \ru Ядро функции nmppsNeg(). 
        \en nmppsNeg() function core. 
    
		\~
        \ru Действие функции эквивалентно следующим псевдоинструкциям: 
        \en The function operation is equivalent to the following pseudoinstructions:   
		\~
		\~
    \code
    	rep N data=[ar0++gr0] with 0-data;
    	rep N [ar6++gr6]=afifo;
    \endcode
    
    \param nb1  
        \ru задает разбиение на колонки (необходимо wtw) 
        \en sets columns partition (wtw is necessary) 
		\~
    \param ar0  
        \ru указатель на столбец SrcMtr1 
        \en pointer to SrcMtr1 column 
		\~
    \param gr0 SrcMtr1 stride
    
    \param gr5  
        \ru Высота матриц N = [0,1,2...31,32,33,...] 
        \en Height of matrixes N = [0,1,2...31,32,33,...] 
		\~
    \param ar6  
        \ru указатель на столбец DstMtr 
        \en pointer to DstMtr column 
		\~
    \param gr6 DstMtr stride
    
    \restr  
        \ru При выходе из функции изменяется содержимое регистров: ar0,ar6. 
        \en On exiting the function the contents of registers changes: ar0,ar6.    	
    
    */

//! \{ 
 void vec_0_sub_data(nmreg nb1, nmreg ar0, nmreg gr0, nmreg gr5, nmreg ar6, nmreg gr6); 
 //! \}


//-----------------------------------------------------------------------------
    /**
		\~
    \defgroup vec_activate_data
    \ingroup vCore
        \ru Ядро функции nmppsCmpLt0_(). 
        \en nmppsCmpLt0_() function core. 
    
		\~
        \ru Действие функции эквивалентно следующим псевдоинструкциям: 
        \en The function operation is equivalent to the following pseudoinstructions: 
		\~
		\~
    \code
    	rep N data=[ar0++gr0] with activate data;
    	rep N [ar6++gr6]=afifo;
    \endcode
    
    \param f1cr 
        \ru задает функцию активации 
        \en sets activation function 
		\~
    \param ar0  
        \ru указатель на столбец SrcMtr1 
        \en pointer to SrcMtr1 column 
		\~
    \param gr0 SrcMtr1 stride
    
    \param gr5  
        \ru Высота матриц N = [0,1,2...31,32,33,...] 
        \en Height of matrixes N = [0,1,2...31,32,33,...] 
		\~
    \param ar6  
        \ru указатель на столбец DstMtr 
        \en pointer to DstMtr column 
		\~
    \param gr6 DstMtr stride
    
    \restr 
        \ru При выходе из функции изменяется содержимое регистров: ar0,ar6. 
        \en On exiting the function the contents of registers changes: ar0,ar6. 
		*/
    
//! \{ 
 void vec_activate_data(nmreg f1cr, nmreg ar0, nmreg gr0, nmreg gr5, nmreg ar6, nmreg gr6); 
 //! \}


//-----------------------------------------------------------------------------
    /**
		\~
    \defgroup vec_activate_data_add_0
    \ingroup vCore
        \ru Функция производит арифметическую активацию. 
        \en The function executes arithmetic activation. 
    
		\~
        \ru Ядро функции nmppsClipPowC_(). 
        \en nmppsClipPowC_() function core. 
		\~
    \ru Действие функции эквивалентныо следующим псевдоинструкциям: 
    \en The function operation is equivalent to the following pseudoinstructions: 
		\~
		\~
    \code
    	rep N data=[ar0++gr0] with activate data + 0;
    	rep N [ar6++gr6]=afifo;
    \endcode
    
    \param f1cr 
        \ru задает функцию активации 
        \en sets activation function 
		\~
    \param ar0  
        \ru указатель на столбец SrcMtr1 
        \en pointer to SrcMtr1 column 
		\~
    \param gr0 SrcMtr1 stride
    
    \param gr5  
        \ru Высота матриц N = [0,1,2...31,32,33,...] 
        \en Height of matrixes N = [0,1,2...31,32,33,...] 
		\~
    \param ar6  
        \ru указатель на столбец DstMtr 
        \en pointer to DstMtr column 
		\~
    \param gr6 DstMtr stride
    
    \restr 
        \ru При выходе из функции изменяется содержимое регистров: ar0,ar6. 
        \en On exiting the function the contents of registers changes: ar0,ar6. 
    */
//! \{ 
 void vec_activate_data_add_0(nmreg f1cr, nmreg ar0, nmreg gr0, nmreg gr5, nmreg ar6, nmreg gr6); 
 //! \}


//-----------------------------------------------------------------------------
    /**
		\~
    \defgroup vec_activate_data_xor_data
    \ingroup vCore
   
        \ru Функция позволяет вычислить приближенное значение модуля. 
        \en The function allow calculate approximate absolute value. 
    
		\~
        \ru Ядро функции nmppsAbs1(). 
        \en nmppsAbs1() function core. 
		\~
    \ru Действие функции эквивалентныо следующим псевдоинструкциям: 
    \en The function operation is equivalent to the following pseudoinstructions: 
		\~
		\~
    \code
    	rep N data=[ar0++gr0] with activate data xor data;
    	rep N [ar6++gr6]=afifo;
    \endcode
    
    \param f1cr 
        \ru задает функцию активации 
        \en sets activation function 
		\~
    \param ar0  
        \ru указатель на столбец SrcMtr1 
        \en pointer to SrcMtr1 column 
		\~
    \param gr0 SrcMtr1 stride
    
    \param gr5  
        \ru Высота матриц N = [0,1,2...31,32,33,...] 
        \en Height of matrixes N = [0,1,2...31,32,33,...] 
		\~
    \param ar6  
        \ru указатель на столбец DstMtr 
        \en pointer to DstMtr column 
		\~
    \param gr6 DstMtr stride
    
    \restr 
        \ru При выходе из функции изменяется содержимое регистров: ar0,ar6. 
        \en On exiting the function the contents of registers changes: ar0,ar6. 
    */
//! \{ 
 void vec_activate_data_xor_data(nmreg f1cr, nmreg ar0, nmreg gr0, nmreg gr5, nmreg ar6, nmreg gr6); 
 //! \}


//-----------------------------------------------------------------------------
    /**
		\~
    \defgroup vec_activate_data_add_ram
    \ingroup vCore
   
        \ru Функция выполняет арифметическую активацию с прибавлением константы. 
        \en The function executes arithmetic activation with adding a constant. 
    
		\~
        \ru Действие функции эквивалентно следующим псевдоинструкциям: 
        \en The function operation is equivalent to the following pseudoinstructions:  
		\~
		\~
    \code
    	rep N ram =[ar1]
    	rep N data=[ar0++gr0] with activate data+ram;
    	rep N [ar6++gr6] = afifo;
    \endcode
    
    \param nb1  
        \ru задает разбиение на колонки (необходимо wtw) 
        \en sets columns partition (wtw is necessary) 
		\~
    \param f1cr 
        \ru задает функцию активации 
        \en sets activation function 
		\~
    \param ar0  
        \ru указатель на столбец SrcMtr1 
        \en pointer to SrcMtr1 column 
		\~
    \param gr0 SrcMtr1 stride
    
    \param ar1  
        \ru указатель на 64р. слово 
        \en pointer to a 64-bit word 
		\~
    \param gr5  
        \ru Высота матриц N = [0,1,2...31,32,33,...] 
        \en Height of matrixes N = [0,1,2...31,32,33,...] 
		\~
    \param ar6  
        \ru указатель на столбец DstMtr	
        \en pointer to DstMtr column 
		\~
    \param gr6 DstMtr stride
    
    \restr 
        \ru При выходе из функции изменяется содержимое регистров: ar0,ar6. 
        \en On exiting the function the contents of registers changes: ar0,ar6. 
    */

//! \{ 
 void vec_activate_data_add_ram(nmreg nb1, nmreg f1cr, nmreg ar0, nmreg gr0, nmreg ar1, nmreg gr5, nmreg ar6, nmreg gr6); 
 //! \}


//-----------------------------------------------------------------------------
    /**
		\~
    \defgroup 	vec_Add_VV_shift	
    \ingroup vcomplex
   
        \ru Функция служит для суммирования двух массивов со сдвигом результата на 1 бит вправо. 
        \en The function serves for two arrays summation with shifting the result for 1 bit to the right. 
    
		\~
        \ru Действие функции эквивалентно следующим псевдоинструкциям: 
        \en The function operation is equivalent to the following pseudoinstructions: 
		\~
		\~
    \code
    	rep N ram = [ar4];
    	rep N data = [ar0++gr0] with data + 0;
    	rep N data = [ar1++gr1] with data + afifo;
    	rep N with mask ram,shift afifo,0;
    	rep N [ar6++gr6] = afifo;
    \endcode
    
    \param nb1  
        \ru задает разбиение на колонки (необходимо wtw) 
        \en sets columns partition (wtw is necessary) 
		\~
    \param sb   
        \ru задает разбиение на строки 
        \en sets rows partition 
		\~
    \param woper 
        \ru в рабочей матрице должны быть загружены весовые коэффициенты 
        \en weight coefficients should be loaded in the working mtr 
		\~
    \param ar0 
        \ru указатель на столбец SrcMtr1	
        \en pointer to SrcMtr1 column 
		\~
    \param gr0 SrcMtr1 stride
    
    \param ar1 
        \ru указатель на столбец SrcMtr2	
        \en pointer to SrcMtr2 column 
		\~
    \param gr1 SrcMtr2 stride
    
    \param ar4 
        \ru указатель на 64р. слово (маска) 
        \en pointer to a 64-bit word (mask) 
		\~
    \param gr5  
        \ru Высота матриц N = [0,1,2...31,32,33,...] 
        \en Height of matrixes N = [0,1,2...31,32,33,...] 
		\~
    \param ar6  
        \ru указатель на столбец DstMtr 
        \en pointer to DstMtr column 
		\~
    \param gr6 DstMtr stride
    
    \restr 
        \ru При выходе из функции изменяется содержимое регистров: 
               ar0,ar1,ar2,ar6,gr2,gr5. 
        \en On exiting the function the contents of registers changes: 
               ar0,ar1,ar2,ar6,gr2,gr5.  
    */

//! \{ 
 void vec_Add_VV_shift(nmreg nb1, nmreg sb, nmreg woper, nmreg ar0, nmreg gr0, nmreg ar1, nmreg gr1, nmreg ar4, nmreg gr5, nmreg ar6, nmreg gr6); 
 //! \}


//-----------------------------------------------------------------------------
    /**
		\~
    \defgroup vec_afifo
    \ingroup vCore
   
        \ru Функция служит для заполнения массива константой. 
        \en The function serves for filling an array with a constant. 
    
		\~
        \ru Действие функции эквивалентно следующим псевдоинструкциям: 
        \en The function operation is equivalent to the following pseudoinstructions:   
		\~
		\~
    \code
    	rep 1 data=[ar0] with data;
    	rep 1*N [ar6++gr6]=afifo with afifo;
    \endcode
    
    \param ar0 
        \ru указатель на 64р. слово 
        \en pointer to a 64-bit word 
		\~
    \param gr5 
        \ru Высота матриц N = [0,1,2...31,32,33,...] 
        \en Height of matrixes N = [0,1,2...31,32,33,...] 
		\~
    \param ar6 
        \ru указатель на столбец DstMtr	
        \en pointer to DstMtr column 
		\~
    \param gr6 DstMtr stride
    
    \restr 
        \ru При выходе из функции изменяется содержимое регистров: ar0,ar6. 
        \en On exiting the function the contents of registers changes: ar0,ar6. 
    */

//! \{ 
 void vec_afifo(nmreg ar0, nmreg gr5, nmreg ar6, nmreg gr6); 
 //! \}


//-----------------------------------------------------------------------------
    /**
		\~
    \defgroup vec_data
    \ingroup vCore
   
        \ru Ядро функции nmppsCopy_(). 
        \en Core of nmppsCopy_() function. 
    
		\~
        \ru Действие функции эквивалентно следующим псевдоинструкциям: 
        \en The function operation is equivalent to the following pseudoinstructions: 
		\~
		\~
    \code
    	rep N data=[ar0++gr0] with data;
    	rep N [ar6++gr6]=afifo;
    \endcode
    
    \param ar0 
        \ru указатель на столбец SrcMtr1 
        \en pointer to SrcMtr1 column 
		\~
    \param gr0 SrcMtr1 stride
    
    \param gr5  
        \ru Высота матриц N = [0,1,2...31,32,33,...] 
        \en Height of matrixes N = [0,1,2...31,32,33,...] 
		\~
    \param ar6 
        \ru указатель на столбец DstMtr 
        \en pointer to DstMtr column 
		\~
    \param gr6 DstMtr stride
    
    \restr 
        \ru При выходе из функции изменяется содержимое регистров: ar0,ar6. 
        \en On exiting the function the contents of registers changes: ar0,ar6. 
            ar0,ar6
		*/

//! \{ 
 void vec_data(nmreg ar0, nmreg gr0, nmreg gr5, nmreg ar6, nmreg gr6); 
 //! \}


//-----------------------------------------------------------------------------
    /**
		\~
    \defgroup vec_data_add_afifo
    \ingroup vcomplex
   
        \ru Ядро функции nmppsSum(). 
        \en Core of nmppsSum() function. 
    
		\~
        \ru Действие функции эквивалентно следующим псевдоинструкциям: 
        \en The function operation is equivalent to the following pseudoinstructions: 
		\~
		\~
    \code
    	rep 1	data=vfalse; 
		.repeat N;
    	rep 1	data=[ar0++gr0] with data + afifo; (rep1 N times)
    	.endrepeat;
		rep 1	[ar6]=afifo;
    \endcode
    
    \param nb1  
        \ru задает разбиение на колонки (необходимо wtw) 
        \en sets columns partition (wtw is necessary) 
		\~
    \param ar0 
        \ru указатель на столбец SrcMtr 
        \en pointer to SrcMtr column 
		\~
    \param gr0 SrcMtr stride
    
    \param gr5  
        \ru Высота матриц N = [0,1,2...31,32,33,...] 
        \en Height of matrixes N = [0,1,2...31,32,33,...] 
		\~
    \param ar6 
        \ru указатель на 64р. слово 
        \en pointer to a 64-bit word 
		\~
    \restr 
        \ru При выходе из функции изменяется содержимое регистров: ar0. 
        \en On exiting the function the contents of registers changes: ar0. 
    */

//! \{ 
 void vec_data_add_afifo(nmreg nb1, nmreg ar0, nmreg gr0, nmreg gr5, nmreg ar6); 
 //! \}


//-----------------------------------------------------------------------------
    /**
		\~
    \defgroup vec_data_add_ram
   \ingroup vCore
   
        \ru Ядро функции nmppsAddC(). 
        \en Core of nmppsAddC() function. 
    
		\~
        \ru Действие функции эквивалентно следующим псевдоинструкциям: 
        \en The function operation is equivalent to the following pseudoinstructions: 
		\~
		\~
    \code
    	rep N ram=[ar1];
    	rep N data=[ar0++gr0] with data+ram;
    	rep N [ar6++gr6]=afifo;
    \endcode
    
    \param nb1  
        \ru задает разбиение на колонки (необходимо wtw) 
        \en sets columns partition (wtw is necessary) 
		\~
    \param ar0 
        \ru указатель на столбец SrcMtr1 
        \en pointer to SrcMtr1 column 
		\~
    \param gr0 SrcMtr stride
    
    \param ar1 
        \ru указатаель на 64р. слово-константу 
        \en pointer to a 64-bit word-constant 
		\~
    \param gr5  
        \ru Высота матриц N = [0,1,2...31,32,33,...] 
        \en Height of matrixes N = [0,1,2...31,32,33,...] 
		\~
    \param ar6 
        \ru указатель на столбец DstMtr 
        \en pointer to DstMtr column 
		\~
    \param gr6 DstMtr stride
    
    \restr 
        \ru При выходе из функции изменяется содержимое регистров: ar0,ar6. 
        \en On exiting the function the contents of registers changes: ar0,ar6. 
    */

//! \{ 
 void vec_data_add_ram(nmreg nb1, nmreg ar0, nmreg gr0, nmreg ar1, nmreg gr5, nmreg ar6, nmreg gr6); 
 //! \}


//-----------------------------------------------------------------------------
    /**
		\~
     \defgroup vec_data_and_ram
   \ingroup vCore
   
        \ru Ядро функции nmppsAndC_(). 
        \en Core of nmppsAndC_() function. 
    
		\~
        \ru Действие функции эквивалентно следующим псевдоинструкциям: 
        \en The function operation is equivalent to the following pseudoinstructions: 
		\~
		\~
    \code 
    	rep N ram =[ar1];
    	rep N data=[ar0++gr0] with data and ram;
    	rep N [ar6++gr6]=afifo;
    \endcode
    
    \param ar0 
        \ru указатель на столбец SrcMtr1 
        \en pointer to SrcMtr1 column 
		\~
    \param gr0 SrcMtr1 stride
    
    \param ar1 
        \ru указатаель на 64р. слово-константу 
        \en pointer to a 64-bit word-constant 
		\~
    \param gr5  
        \ru Высота матриц N = [0,1,2...31,32,33,...] 
        \en Height of matrixes N = [0,1,2...31,32,33,...] 
		\~
    \param ar6 
        \ru указатель на столбец DstMtr 
        \en pointer to DstMtr column 
		\~
    \param gr6 DstMtr stride
    
    \restr 
        \ru При выходе из функции изменяется содержимое регистров: ar0,ar6. 
        \en On exiting the function the contents of registers changes: ar0,ar6. 
    */

//! \{ 
 void vec_data_and_ram(nmreg ar0, nmreg gr0, nmreg ar1, nmreg gr5, nmreg ar6, nmreg gr6); 
 //! \}


//-----------------------------------------------------------------------------
    /**
		\~
     \defgroup vec_data_or_ram
   \ingroup vCore
   
        \ru Ядро функции nmppsOrC_(). 
        \en Core of nmppsOrC_() function. 
    
		\~
        \ru Действие функции эквивалентно следующим псевдоинструкциям: 
        \en The function operation is equivalent to the following pseudoinstructions: 
		\~
		\~
    \code
    	rep N ram =[ar1];
    	rep N data=[ar0++gr0] with data or ram;
    	rep N [ar6++gr6]=afifo;
    \endcode
    
    \param ar0 
        \ru указатель на столбец SrcMtr1 
        \en pointer to SrcMtr1 column 
		\~
    \param gr0 SrcMtr1 stride
    
    \param ar1 
        \ru указатаель на 64р. слово-константу 
        \en pointer to a 64-bit word-constant 
		\~
    \param gr5  
        \ru Высота матриц N = [0,1,2...31,32,33,...] 
        \en Height of matrixes N = [0,1,2...31,32,33,...] 
		\~
    \param ar6 
        \ru указатель на столбец DstMtr 
        \en pointer to DstMtr column 
		\~
    \param gr6 DstMtr stride
    
    \restr 
        \ru При выходе из функции изменяется содержимое регистров: ar0,ar6. 
        \en On exiting the function the contents of registers changes: ar0,ar6. 
    */

//! \{ 
 void vec_data_or_ram(nmreg ar0, nmreg gr0, nmreg ar1, nmreg gr5, nmreg ar6, nmreg gr6); 
 //! \}


//-----------------------------------------------------------------------------
    /**
		\~
     \defgroup vec_data_sub_ram
   \ingroup vCore
   
        \ru Ядро функции nmppsSubC(). 
        \en Core of nmppsSubC() function. 
    
		\~
        \ru Действие функции эквивалентно следующим псевдоинструкциям: 
        \en The function operation is equivalent to the following pseudoinstructions: 
		\~
		\~
    \code
    	rep N ram=[ar1];
    	rep N data=[ar0++gr0] with data-ram;
    	rep N [ar6++gr6]=afifo;
    \endcode
    
    \param nb1  
        \ru задает разбиение на колонки (необходимо wtw) 
        \en sets columns partition (wtw is necessary) 
		\~
    \param ar0 
        \ru указатель на столбец SrcMtr 
        \en pointer to SrcMtr column 
		\~
    \param gr0 SrcMtr stride
    
    \param ar1 
        \ru указатаель на 64р. слово-константу 
        \en pointer to a 64-bit word-constant 
		\~
    \param gr5  
        \ru Высота матриц N = [0,1,2...31,32,33,...] 
        \en Height of matrixes N = [0,1,2...31,32,33,...] 
		\~
    \param ar6 
        \ru указатель на столбец DstMtr 
        \en pointer to DstMtr column 
		\~
    \param gr6 DstMtr stride
    
    \restr 
        \ru При выходе из функции изменяется содержимое регистров: ar0,ar6. 
        \en On exiting the function the contents of registers changes: ar0,ar6. 
    */

//! \{ 
 void vec_data_sub_ram(nmreg nb1, nmreg ar0, nmreg gr0, nmreg ar1, nmreg gr5, nmreg ar6, nmreg gr6); 
 //! \}


//-----------------------------------------------------------------------------
    /**
		\~
    \defgroup vec_data_xor_ram
    \ingroup vCore
   
        \ru Ядро функции nmppsXorC_(). 
        \en Core of nmppsXorC_() function. 
    
		\~
        \ru Действие функции эквивалентно следующим псевдоинструкциям: 
        \en The function operation is equivalent to the following pseudoinstructions: 
		\~
		\~
		\code
			rep N ram = [ar1];
			rep N data = [ar0++gr0] with data xor ram;
			rep N [ar6++gr6] = afifo;
		\endcode
    
    \param ar0 
        \ru указатель на столбец SrcMtr1 
        \en pointer to SrcMtr1 column 
		\~
    \param gr0 SrcMtr1 stride
    
    \param ar1 
        \ru указатель на 64р. слово-константу 
        \en pointer to a 64-bit word-constant 
		\~
    \param gr5  
        \ru Высота матриц N = [0,1,2...31,32,33,...] 
        \en Height of matrixes N = [0,1,2...31,32,33,...] 
		\~
    \param ar6 
        \ru указатель на столбец DstMtr 
        \en pointer to DstMtr column 
		\~
    \param gr6 DstMtr stride
    
    \restr 
        \ru При выходе из функции изменяется содержимое регистров: ar0,ar6. 
        \en On exiting the function the contents of registers changes: ar0,ar6. 
    */

//! \{ 
 void vec_data_xor_ram(nmreg ar0, nmreg gr0, nmreg ar1, nmreg gr5, nmreg ar6, nmreg gr6); 
 //! \}


//-----------------------------------------------------------------------------

    /**
		\~
     \defgroup vec_FilterCoreRow2
   \ingroup vcomplex
   
    \par
    \xmlonly
    \endxmlonly
    */

//! \{ 
 void vec_FilterCoreRow2(nmreg ar0, nmreg ar4, nmreg ar6, nmreg gr1, nmreg gr4, nmreg gr6); 
 //! \}


//-----------------------------------------------------------------------------
    /**
    \defgroup vec_FilterCoreRow4
    \ingroup vcomplex
   
    \par
    \xmlonly
    \endxmlonly
    */

//! \{ 
 void vec_FilterCoreRow4(nmreg ar0, nmreg ar4, nmreg ar6, nmreg gr1, nmreg gr4, nmreg gr6); 
 //! \}


//-----------------------------------------------------------------------------
    /**
    \defgroup vec_FilterCoreRow8
    \ingroup vcomplex
   
    \par
    \xmlonly
    \endxmlonly
    */

//! \{ 
 void vec_FilterCoreRow8(nmreg ar0, nmreg ar4, nmreg ar6, nmreg gr1, nmreg gr4, nmreg gr6); 
 //! \}


//-----------------------------------------------------------------------------
    /**
    \defgroup vec_And
    \ingroup vCore
   
        \ru Ядро функции nmppsAnd_(). 
        \en nmppsAnd_() function core. 
    
		\~
        \ru Действие функции эквивалентно следующим псевдоинструкциям: 
        \en The function operation is equivalent to the following pseudoinstructions:   
		\~
		\~
    \code
    	rep N data=[ar0++gr0] with data;
    	rep N data=[ar1++gr1] with data and afifo;
    	rep N [ar6++gr6]=afifo;
    \endcode
    
    \param ar0 
        \ru указатель на столбец SrcMtr1 
        \en pointer to SrcMtr1 column 
		\~
    \param gr0 SrcMtr1 stride
    
    \param ar1 
        \ru указатель на столбец SrcMtr2 
        \en pointer to SrcMtr2 column 
		\~
    \param gr1 SrcMtr2 stride
    
    \param gr5  
        \ru Высота матриц N = [0,1,2...31,32,33,...] 
        \en Height of matrixes N = [0,1,2...31,32,33,...] 
		\~
    \param ar6  
        \ru указатель на результирующий столбец 
        \en pointer to result column 
		\~
    \param gr6 
		\ru межстрочный шаг для ar6 
		\en stride for ar6
    
		\~
    \restr 
        \ru При выходе из функции изменяется содержимое регистров: ar0,ar1,ar6. 
        \en On exiting the function the contents of registers changes: ar0,ar1,ar6.  
    */

//! \{ 
 void vec_And(nmreg ar0, nmreg gr0, nmreg ar1, nmreg gr1, nmreg gr5, nmreg ar6, nmreg gr6); 
 //! \}


//-----------------------------------------------------------------------------
    /**
		\~
      \defgroup vec_Mask
  \ingroup vCore
   
        \ru Ядро функции nmppsMaskV_(). 
        \en nmppsMaskV_() function core. 
    
		\~
        \ru Действие функции эквивалентно следующим псевдоинструкциям: 
        \en The function operation is equivalent to the following pseudoinstructions:   
		\~
		\~
    \code
    	rep N ram =[ar0++gr0];								
    	rep N data=[ar1++gr1]	with data;					
    	rep N data=[ar2++gr2]	with mask data,ram,afifo;	
    	rep N [ar6++gr6]=afifo;								
    \endcode
    
    \param ar0 
        \ru указатель на столбец SrcMtr1 
        \en pointer to SrcMtr1 column 
		\~
    \param gr0 SrcMtr1 stride
    
    \param ar1 
        \ru указатель на столбец SrcMtr2 
        \en pointer to SrcMtr2 column 
		\~
    \param gr1 SrcMtr2 stride
    
    \param ar2 
        \ru указатель на столбец SrcMtr2 (маска) 
        \en pointer to SrcMtr2 column (the mask) 
		\~
    \param gr2 SrcMtr3 stride
    
    \param gr5  
        \ru Высота матриц N = [0,1,2...31,32,33,...] 
        \en Height of matrixes N = [0,1,2...31,32,33,...] 
		\~
    \param ar6  
        \ru указатель на результирующий столбец 
        \en pointer to result column 
		\~
    \param gr6 
		\ru межстрочный шаг для ar6 
		\en stride for ar6
    
		\~
    \restr 
        \ru При выходе из функции изменяется содержимое регистров: ar0,ar1,ar2,ar6. 
        \en On exiting the function the contents of registers changes: ar0,ar1,ar2,ar6. 
    */

//! \{ 
 void vec_Mask(nmreg ar0, nmreg gr0, nmreg ar1, nmreg gr1, nmreg ar2, nmreg gr2, nmreg gr5, nmreg ar6, nmreg gr6); 
 //! \}


//-----------------------------------------------------------------------------
    /**
		\~
    \defgroup vec_Or
    \ingroup vCore
   
        \ru Ядро функции nmppsOr_(). 
        \en nmppsOr_() function core. 
    
		\~
        \ru Действие функции эквивалентно следующим псевдоинструкциям: 
        \en The function operation is equivalent to the following pseudoinstructions:   
		\~
		\~
    \code
    	rep N data=[ar0++gr0] with data;
    	rep N data=[ar1++gr1] with data or afifo;
    	rep N [ar6++gr6]=afifo;
    \endcode
    
    \param ar0 
        \ru указатель на столбец SrcMtr1 
        \en pointer to SrcMtr1 column 
		\~
    \param gr0 SrcMtr1 stride
    
    \param ar1 
        \ru указатель на столбец SrcMtr2 
        \en pointer to SrcMtr2 column 
		\~
    \param gr1 SrcMtr2 stride
    
    \param gr5  
        \ru Высота матриц N = [0,1,2...31,32,33,...] 
        \en Height of matrixes N = [0,1,2...31,32,33,...] 
		\~
    \param ar6  
        \ru указатель на результирующий столбец 
        \en pointer to result column 
		\~
    \param gr6 
		\ru межстрочный шаг для ar6 
		\en stride for ar6
    
		\~
    \restr 
        \ru При выходе из функции изменяется содержимое регистров: ar0,ar1,ar6. 
        \en On exiting the function the contents of registers changes: ar0,ar1,ar6. 
    */

//! \{ 
 void vec_Or(nmreg ar0, nmreg gr0, nmreg ar1, nmreg gr1, nmreg gr5, nmreg ar6, nmreg gr6); 
 //! \}


//-----------------------------------------------------------------------------
    /**
		\~
     \defgroup vec_Xor
   \ingroup vCore
   
        \ru Ядро функции nmppsXor_(). 
        \en nmppsXor_() function core. 
    
		\~
        \ru Действие функции эквивалентно следующим псевдоинструкциям: 
        \en The function operation is equivalent to the following pseudoinstructions:   
		\~
		\~
    \code
    	rep N data=[ar0++gr0] with data;
    	rep N data=[ar1++gr1] with data xor afifo;
    	rep N [ar6++gr6]=afifo;
    \endcode
    
    \param ar0 
        \ru указатель на столбец SrcMtr1 
        \en pointer to SrcMtr1 column 
		\~
    \param gr0 SrcMtr1 stride
    
    \param ar1 
        \ru указатель на столбец SrcMtr2 
        \en pointer to SrcMtr2 column 
		\~
    \param gr1 SrcMtr2 stride
    
    \param gr5  
        \ru Высота матриц N = [0,1,2...31,32,33,...] 
        \en Height of matrixes N = [0,1,2...31,32,33,...] 
		\~
    \param ar6  
        \ru указатель на результирующий столбец 
        \en pointer to result column 
		\~
    \param gr6 
		\ru межстрочный шаг для ar6 
		\en stride for ar6
    
		\~
    \restr 
        \ru При выходе из функции изменяется содержимое регистров: ar0,ar1,ar6. 
        \en On exiting the function the contents of registers changes: ar0,ar1,ar6. 
    */

//! \{ 
 void vec_Xor(nmreg ar0, nmreg gr0, nmreg ar1, nmreg gr1, nmreg gr5, nmreg ar6, nmreg gr6); 
 //! \}


//-----------------------------------------------------------------------------
    /**
		\~
     \defgroup vec_Abs
   \ingroup vcomplex
   
        \ru Ядро функции nmppsAbs(). 
        \en nmppsAbs() function core. 
    
		\~
        \ru Действие функции эквивалентно следующим псевдоинструкциям: 
        \en The function operation is equivalent to the following pseudoinstructions:   
		\~
		\~
    \code
    	rep N ram =[ar0++gr0]	with activate data;
    	rep N					with vsum afifo,ram,ram;			
    	rep N [ar6++gr6]= afifo;
    \endcode
    
    \param nb1  
        \ru задает разбиение на колонки (необходимо wtw) 
        \en sets columns partition (wtw is necessary) 
		\~
    \param sb   
        \ru задает разбиение на 8 строк 
        \en sets partition into eight rows 
		\~
    \param f1cr 
        \ru задает функцию активации 
        \en sets activation function 
		\~
    \param ar0  
        \ru указатель на столбец SrcMtr 
        \en pointer to SrcMtr column 
		\~
    \param gr0 SrcMtr stride
    
    \param gr5  
        \ru Высота матриц N = [0,1,2...31,32,33,...] 
        \en Height of matrixes N = [0,1,2...31,32,33,...] 
		\~
    \param ar6  
        \ru указатель на результирующий столбец 
        \en pointer to result column 
		\~
    \param gr6 
		\ru межстрочный шаг для ar6 
		\en stride for ar6
    
		\~
    \restr 
        \ru При выходе из функции изменяется содержимое регистров: ar0,ar6. 
        \en On exiting the function the contents of registers changes: ar0,ar6.  
    */

//! \{ 
 void vec_Abs(nmreg nb1, nmreg sb, nmreg f1cr, nmreg ar0, nmreg gr0, nmreg gr5, nmreg ar6, nmreg gr6); 
 //! \}


//-----------------------------------------------------------------------------
    /**
		\~
     \defgroup vec_Add
   \ingroup vCore
   
        \ru Ядро функции nmppsAdd(). 
        \en nmppsAdd() function core. 
    
		\~
        \ru Действие функции эквивалентно следующим псевдоинструкциям: 
        \en The function operation is equivalent to the following pseudoinstructions:   
		\~
		\~
    \code
    	rep N data=[ar0++gr0] with data;
    	rep N data=[ar1++gr1] with data + afifo;
    	rep N [ar6++gr6]=afifo;
    \endcode
    
    \param nb1  
        \ru задает разбиение на колонки (необходимо wtw) 
        \en sets columns partition (wtw is necessary) 
		\~
    \param ar0  
        \ru указатель на столбец SrcMtr1 
        \en pointer to SrcMtr1 column 
		\~
    \param gr0 SrcMtr1 stride
    
    \param ar1  
        \ru указатель на столбец SrcMtr2 
        \en pointer to SrcMtr2 column 
		\~
    \param gr1 SrcMtr2 stride
    
    \param gr5  
        \ru Высота матриц N = [0,1,2...31,32,33,...] 
        \en Height of matrixes N = [0,1,2...31,32,33,...] 
		\~
    \param ar6  
        \ru указатель на результирующий столбец 
        \en pointer to result column 
		\~
    \param gr6 
		\ru межстрочный шаг для ar6 
		\en stride for ar6
    
		\~
    \restr 
        \ru При выходе из функции изменяется содержимое регистров: ar0,ar1,ar6. 
        \en On exiting the function the contents of registers changes: ar0,ar1,ar6.  
    */

//! \{ 
 void vec_Add(nmreg nb1, nmreg ar0, nmreg gr0, nmreg ar1, nmreg gr1, nmreg gr5, nmreg ar6, nmreg gr6); 
 //! \}


//-----------------------------------------------------------------------------
    /**
		\~
     \defgroup vec_ClipExt
   \ingroup vcomplex
   
        \ru Ядро функции nmppsClipCC_(). 
        \en nmppsClipCC_() function core. 
    
		\~
        \ru Действие функции эквивалентно следующим псевдоинструкциям: 
        \en The function operation is equivalent to the following pseudoinstructions:   
		\~
		\~
    \code
    	rep N ram  = [ar1];
    	rep N data = [ar0++gr0] with data-ram;
    	rep N data = [ar2]		with activate afifo+data;
    	rep N data = [ar3]		with activate afifo-data;
    	rep N [ar6++gr6] = afifo;
    \endcode
    
    \param nb1  
        \ru задает разбиение на колонки (необходимо wtw) 
        \en sets columns partition (wtw is necessary) 
		\~
    \param f1cr 
        \ru задает функцию активации 
        \en sets activation function 
		\~
    \param ar0  
        \ru указатель на столбец SrcMtr 
        \en pointer to SrcMtr column 
		\~
    \param gr0 SrcMtr stride
    
    \param ar1  
        \ru указатаель на 64р. слово-константу 
        \en pointer to a 64-bit word-constant 
		\~
    \param ar2  
        \ru указатаель на 64р. слово-константу 
        \en pointer to a 64-bit word-constant 
		\~
    \param ar3  
        \ru указатаель на 64р. слово-константу 
        \en pointer to a 64-bit word-constant 
		\~
    \param gr5  
        \ru Высота матриц N = [0,1,2...31,32,33,...] 
        \en Height of matrixes N = [0,1,2...31,32,33,...] 
		\~
    \param ar6  
        \ru указатель на результирующий столбец 
        \en pointer to result column 
		\~
    \param gr6 
		\ru межстрочный шаг для ar6 
		\en stride for ar6
    
		\~
    \restr 
        \ru При выходе из функции изменяется содержимое регистров: ar0,ar6. 
        \en On exiting the function the contents of registers changes: ar0,ar6. 
		\~
    \link nmppsClipCC_
    */
//! \{ 
 void vec_ClipExt(nmreg nb1, nmreg f1cr, nmreg ar0, nmreg gr0, nmreg ar1, nmreg ar2, nmreg ar3, nmreg gr5, nmreg ar6, nmreg gr6); 
 //! \}


//-----------------------------------------------------------------------------
    /**
     \defgroup vec_ClipMul2D2W8_AddVr
   \ingroup vsum
   
        \ru Взвешенное умножение двух массивов с накоплением и активацей 
        \en Weighted multiplication of two arrays with accumulation and activation 
    
		\~
        \ru Ядро функции nmppsClipPowC_RShift_Convert_AddС_(). 
        \en nmppsClipPowC_RShift_Convert_AddС_() function core. 
		\~
    \ru Действие функции эквивалентно следующим псевдоинструкциям: 
    \en The function operation is equivalent to the following pseudoinstructions:   
		\~
		\~
    \code
    	rep 8 wfifo=[ar4++],ftw,wtw;
    	rep N data =[ar0++gr0] with vsum ,activate data,vr;
    	rep 8 wfifo=[ar4++],ftw,wtw;	
    	rep N data =[ar1++gr1] with vsum ,activate data,afifo;
    	rep N [ar6++gr6]=afifo;
    \endcode
    
    \param nb1  
        \ru задает разбиение на колонки 
        \en sets columns partition 
		\~
    \param sb   
        \ru задает разбиение на 8 строк 
        \en sets partition into 8 rows 
		\~
    \param f1cr 
        \ru задает функцию активации 
        \en sets activation function 
		\~
    \param  vr	
        \ru константа для суммирования 
        \en a constant for summation 
		\~
    \param ar0	SrcMtr1		
    
    \param gr0  SrcMtr1 stride 
    
    \param ar1  SrcMtr2		
    
    \param gr1  SrcMtr2 stride 
    
    \param ar4  
        \ru 2 матрицы весовых коэффициентов по 8 64р. слов 
        \en two matrixes of weight coefficients with eight 64-bit words in each mtr 
		\~
    \param gr4  
        \ru дублирует nb1 
        \en it duplicates nb1 
		\~
    \param gr5  
        \ru Высота матриц N = [0,1,2...31,32,33,...] 
        \en Height of matrixes N = [0,1,2...31,32,33,...] 
		\~
     \param ar6  
        \ru указатель на результирующий столбец 
        \en pointer to result column 
		\~
    \param gr6 
		\ru межстрочный шаг для ar6 
		\en stride for ar6
		
		\~
    \restr  
        \ru При выходе из функции изменяется содержимое регистров: ar0,ar1,ar6,gr7. 
        \en On exiting the function the contents of registers changes: ar0,ar1,ar6,gr7. 
    */
//! \{ 
 void vec_ClipMul2D2W8_AddVr(nmreg nb1, nmreg sb, nmreg f1cr, nmreg vr, nmreg ar0, nmreg gr0, nmreg ar1, nmreg gr1, nmreg ar4, nmreg gr4, nmreg gr5, nmreg ar6, nmreg gr6); 
 //! \}


//-----------------------------------------------------------------------------


    /**
		\~
     \defgroup vec_ClipMulNDNW2_AddVr
   \ingroup vsum
   
        \ru Взвешенное умножение нескольких массивов с накоплением и активацей 
        \en Weighted multiplication of several arrays with accumulation and activation 
    
		\~
        \ru Ядро функции SIG_Filter(). 
        \en nmppsFilter_() function core. 
		\~
    \ru Действие функции эквивалентно следующим псевдоинструкциям: 
    \en The function operation is equivalent to the following pseudoinstructions:   
		\~
		\~
    \code
	
		ar2=ar0;
		
		gr2=[ar1++];
		ar0=ar2+gr2;
    	rep 2 wfifo=[ar4++],ftw,wtw;
		rep N data =[ar0++gr0] with vsum ,activate data,vr;
    	
		.repeat K-1;
		gr2=[ar1++];
		ar0=ar2+gr2;
    	rep 2 wfifo=[ar4++],ftw,wtw;	
    	rep N data =[ar0++gr0] with vsum ,activate data,afifo;
    	.endrepeat;
		rep N [ar6++gr6]=afifo;
		
    \endcode
    
    \param nb1  
        \ru задает разбиение на колонки 
        \en sets columns partition 
		\~
    \param sb   
        \ru задает разбиение на 2 строки (sb=2)
        \en sets partition into 2 rows   (sb=2)
		\~
    \param f1cr 
        \ru задает функцию активации 
        \en sets activation function 
		\~
    \param  vr	
        \ru константа для суммирования 
        \en a constant for summation 
		\~
    \param ar0	
		\ru задает базовый адрес для входных массивов (как правило адрес первого массива)		
		\en set base address for input arrays
		\~
    \param gr0 
		\ru шаг чтения входного масиива
		\ru stride for input arrays
    \param ar1  
		\ru массив адресных смещений входных массивов относительно ar0		
		\en array of address displacements of input arrays relatively ar0
		\~
    \param gr1 
		\ru количество массив - K
		\en number of arrays - K
		\~
    \param ar4  
        \ru массив из K матриц весовых коэффициентов по 2 64р. слов 
        \en array of K matrixes of weight coefficients with 2 64-bit words in each mtr 
		\~
    \param gr4  
        \ru дублирует nb1 
        \en it duplicates nb1 
		\~
    \param gr5  
        \ru Высота матриц N = [0,1,2...31,32,33,...] 
        \en Height of matrixes N = [0,1,2...31,32,33,...] 
		\~
    \param ar6  
        \ru указатель на результирующий столбец 
        \en pointer to result column 
		\~
    \param gr6 
		\ru межстрочный шаг для ar6 
		\en stride for ar6
    
		\~
    \restr  
        \ru При выходе из функции изменяется содержимое регистров: ar0,ar1,gr1,ar2,gr2,ar3,gr3,ar4,ar6,gr7. 
        \en On exiting the function the contents of registers changes: ar0,ar1,gr1,ar2,gr2,ar3,gr3,ar4,ar6,gr7. 
    */
//! \{ 
 void vec_ClipMulNDNW2_AddVr(nmreg nb1, nmreg sb, nmreg f1cr, nmreg vr, nmreg ar0, nmreg gr0, nmreg ar1, nmreg gr1, nmreg ar4, nmreg gr4, nmreg gr5, nmreg ar6, nmreg gr6); 
 //! \}


//-----------------------------------------------------------------------------


    /**
		\~
     \defgroup vec_ClipMulNDNW4_AddVr
   \ingroup vsum
   
        \ru Взвешенное умножение нескольких массивов с накоплением и активацей 
        \en Weighted multiplication of several arrays with accumulation and activation 
    
		\~
        \ru Ядро функции SIG_Filter(). 
        \en nmppsFilter_() function core. 
		\~
    \ru Действие функции эквивалентно следующим псевдоинструкциям: 
    \en The function operation is equivalent to the following pseudoinstructions:   
		\~
		\~
    \code
	
		ar2=ar0;
		
		gr2=[ar1++];
		ar0=ar2+gr2;
    	rep 4 wfifo=[ar4++],ftw,wtw;
		rep N data =[ar0++gr0] with vsum ,activate data,vr;
    	
		.repeat K-1;
		gr2=[ar1++];
		ar0=ar2+gr2;
    	rep 4 wfifo=[ar4++],ftw,wtw;	
    	rep N data =[ar0++gr0] with vsum ,activate data,afifo;
    	.endrepeat;
		rep N [ar6++gr6]=afifo;
		
    \endcode
    
    \param nb1  
        \ru задает разбиение на колонки 
        \en sets columns partition 
		\~
    \param sb   
        \ru задает разбиение на 4 строки (sb=20002h)
        \en sets partition into 4 rows   (sb=20002h)
		\~
    \param f1cr 
        \ru задает функцию активации 
        \en sets activation function 
		\~
    \param  vr	
        \ru константа для суммирования 
        \en a constant for summation 
		\~
    \param ar0	
		\ru задает базовый адрес для входных массивов (как правило адрес первого массива)		
		\en set base address for input arrays
		\~
    \param gr0  stride for input arrays
    
    \param ar1  
		\ru массив адресных смещений входных массивов относительно ar0		
		\en array of address displacements of input arrays relatively ar0
		\~
    \param gr1 
		\ru количество массив - K
		\en number of arrays - K
    
		\~
    \param ar4  
        \ru массив из K матриц весовых коэффициентов по 4 64р. слов 
        \en array of K matrixes of weight coefficients with 4 64-bit words in each mtr 
		\~
    \param gr4  
        \ru дублирует nb1 
        \en it duplicates nb1 
		\~
    \param gr5  
        \ru Высота матриц N = [0,1,2...31,32,33,...] 
        \en Height of matrixes N = [0,1,2...31,32,33,...] 
		\~
    \param ar6  
        \ru указатель на результирующий столбец 
        \en pointer to result column 
		\~
    \param gr6 
		\ru межстрочный шаг для ar6 
		\en stride for ar6
	
		\~
	 \restr  
        \ru При выходе из функции изменяется содержимое регистров: ar0,ar1,gr1,ar2,gr2,ar3,gr3,ar4,ar6,gr7. 
        \en On exiting the function the contents of registers changes: ar0,ar1,gr1,ar2,gr2,ar3,gr3,ar4,ar6,gr7. 
    */
//! \{ 
 void vec_ClipMulNDNW4_AddVr(nmreg nb1, nmreg sb, nmreg f1cr, nmreg vr, nmreg ar0, nmreg gr0, nmreg ar1, nmreg gr1, nmreg ar4, nmreg gr4, nmreg gr5, nmreg ar6, nmreg gr6); 
 //! \}


//-----------------------------------------------------------------------------


    /**
		\~
     \defgroup vec_ClipMulNDNW8_AddVr
   \ingroup vsum
   
        \ru Взвешенное умножение нескольких массивов с накоплением и активацей 
        \en Weighted multiplication of several arrays with accumulation and activation 
    
		\~
        \ru Ядро функции SIG_Filter(). 
        \en nmppsFilter_() function core. 
		\~
    \ru Действие функции эквивалентно следующим псевдоинструкциям: 
    \en The function operation is equivalent to the following pseudoinstructions:   
		\~
		\~
    \code
	
		ar2=ar0;
		
		gr2=[ar1++];
		ar0=ar2+gr2;
    	rep 8 wfifo=[ar4++],ftw,wtw;
		rep N data =[ar0++gr0] with vsum ,activate data,vr;
    	
		.repeat K-1;
		gr2=[ar1++];
		ar0=ar2+gr2;
    	rep 8 wfifo=[ar4++],ftw,wtw;	
    	rep N data =[ar0++gr0] with vsum ,activate data,afifo;
    	.endrepeat;
		rep N [ar6++gr6]=afifo;
		
    \endcode
    
    \param nb1  
        \ru задает разбиение на колонки 
        \en sets columns partition 
		\~
    \param sb   
        \ru задает разбиение на 8 строки (sb=2020202h)
        \en sets partition into 8 rows   (sb=2020202h)
		\~
    \param f1cr 
        \ru задает функцию активации 
        \en sets activation function 
		\~
    \param  vr	
        \ru константа для суммирования 
        \en a constant for summation 
		\~
    \param ar0	
		\ задает базовый адрес для входных массивов (как правило адрес первого массива)		
		\ set base address for input arrays
    \param gr0  stride for input arrays
    
    \param ar1  
		\ru массив адресных смещений входных массивов относительно ar0		
		\en array of address displacements of input arrays relatively ar0
		\~
    \param gr1 
		\ количество массив - K
		\ number of arrays - K
    
    \param ar4  
        \ru массив из K матриц весовых коэффициентов по 8 64р. слов 
        \en array of K matrixes of weight coefficients with 8 64-bit words in each mtr 
		\~
    \param gr4  
        \ru дублирует nb1 
        \en it duplicates nb1 
		\~
    \param gr5  
        \ru Высота матриц N = [0,1,2...31,32,33,...] 
        \en Height of matrixes N = [0,1,2...31,32,33,...] 
		\~
    \param ar6  
        \ru указатель на результирующий столбец 
        \en pointer to result column 
		\~
    \param gr6 
		\ru межстрочный шаг для ar6 
		\en stride for ar6   
		\~
    \restr  
        \ru При выходе из функции изменяется содержимое регистров: ar0,ar1,gr1,ar2,gr2,ar3,gr3,ar4,ar6,gr7. 
        \en On exiting the function the contents of registers changes: ar0,ar1,gr1,ar2,gr2,ar3,gr3,ar4,ar6,gr7. 
    */
//! \{ 
 void vec_ClipMulNDNW8_AddVr(nmreg nb1, nmreg sb, nmreg f1cr, nmreg vr, nmreg ar0, nmreg gr0, nmreg ar1, nmreg gr1, nmreg ar4, nmreg gr4, nmreg gr5, nmreg ar6, nmreg gr6); 
 //! \}


//-----------------------------------------------------------------------------
    /**
		\~
     \defgroup vec_IncNeg
   \ingroup vcomplex
   
        \ru Увеличивает отрицательные числа на 1. 
        \en It increases negative numbers by 1. 
    
		\~
        \ru Применяется в nmppsDivC(). 
        \en It is used in nmppsDivC(). 
		\~
    \ru Действие функции эквивалентно следующим псевдоинструкциям: 
    \en The function operation is equivalent to the following pseudoinstructions: 
		\~
		\~
    \code
    	rep N ram = [ar0++gr0]	with activate data;				
    	rep N					with ram - afifo;				
    	rep N [ar6++gr6] = afifo;		
    \endcode
    
    \param nb1  
        \ru задает разбиение на колонки (необходимо wtw) 
        \en sets columns partition (wtw is necessary) 
		\~
    \param f1cr 
        \ru задает функцию активации 
        \en sets activation function 
		\~
    \param ar0  
        \ru указатель на столбец SrcMtr 
        \en pointer to SrcMtr column 
		\~
    \param gr0 SrcMtr stride
    
    \param gr5  
        \ru Высота матриц N = [0,1,2...31,32,33,...] 
        \en Height of matrixes N = [0,1,2...31,32,33,...] 
		\~
    \param ar6  
        \ru указатель на столбец DstMtr 
        \en pointer to DstMtr column 
		\~
    \param gr6 DstMtr stride
    
    \restr 
        \ru При выходе из функции изменяется содержимое регистров: ar0,ar6. 
        \en On exiting the function the contents of registers changes: ar0,ar6. 
    */

//! \{ 
 void vec_IncNeg(nmreg nb1, nmreg f1cr, nmreg ar0, nmreg gr0, nmreg gr5, nmreg ar6, nmreg gr6); 
 //! \}

    
//-----------------------------------------------------------------------------
    /**
		\~
     \defgroup vec_Mul2D2W1_AddVr
   \ingroup vsum
   
        \ru Ядро функции nmppsConvert_64s(nm64s* ,nm32s* ,int ). 
        \en nmppsConvert_64s(nm64s* ,nm32s* ,int ) function core. 
    
		\~
        \ru Действие функции эквивалентно следующим псевдоинструкциям: 
        \en The function operation is equivalent to the following pseudoinstructions:   
		\~
		\~
    \code
    	rep 1 wfifo=[ar4++],ftw,wtw;
    	rep N data =[ar0++gr0] with vsum ,data,vr;
    	rep 1 wfifo=[ar4++],ftw,wtw;
    	rep N data =[ar1++gr1] with vsum ,data,afifo;
    	rep N [ar6++gr6]=afifo;
    \endcode
    
    \param nb1  
        \ru задает разбиение на колонки (необходимо wtw) 
        \en sets columns partition (wtw is necessary) 
		\~
    \param sb   
        \ru задает разбиение в 1 строку 
        \en sets partition into 1 row
		\~
    \param vr	
        \ru константа для суммирования 
        \en a constant for summation 
		\~
    \param ar0  
        \ru указатель на столбец SrcMtr1 
        \en pointer to SrcMtr1 column 
		\~
    \param gr0 SrcMtr1 stride
    
    \param ar1  
        \ru указатель на столбец SrcMtr2 
        \en pointer to SrcMtr2 column 
		\~
    \param gr1 SrcMtr2 stride
    
    \param ar4  
        \ru указатель на 2 матрицы весовых коэффициентов по 2 строки в каждой 
        \en pointer to two matrixes of weight coefficients with two rows in each mtr 
		\~
    \param gr4  
        \ru дублирует nb1 
        \en it duplicates nb1 
		\~
    \param gr5  
        \ru Высота матриц N = [0,1,2...31,32,33,...] 
        \en Height of matrixes N = [0,1,2...31,32,33,...] 
		\~
    \param ar6  
        \ru указатель на столбец DstMtr 
        \en pointer to DstMtr column 
		\~
    \param gr6 DstMtr stride
    
    \restr 
        \ru При выходе из функции изменяется содержимое регистров: ar0,ar1,ar6,gr7. 
        \en On exiting the function the contents of registers changes: ar0,ar1,ar6,gr7. 
    */

//! \{ 
 void vec_Mul2D2W1_AddVr(nmreg nb1, nmreg sb, nmreg vr, nmreg ar0, nmreg gr0, nmreg ar1, nmreg gr1, nmreg ar4, nmreg gr4, nmreg gr5, nmreg ar6, nmreg gr6); 
 //! \}

    
//-----------------------------------------------------------------------------
    /**
		\~
    \defgroup vec_Mul2D2W2_AddVr
    \ingroup vsum
   
        \ru Ядро функции nmppsConvert_32s(nm32s* ,nm16s* ,int ). 
        \en nmppsConvert_32s(nm32s* ,nm16s* ,int ) function core. 
    
		\~
        \ru Действие функции эквивалентно следующим псевдоинструкциям: 
        \en The function operation is equivalent to the following pseudoinstructions:   
		\~
		\~
    \code
    	rep 2 wfifo=[ar4++],ftw,wtw;
    	rep N data =[ar0++gr0] with vsum ,data,vr;
    	rep 2 wfifo=[ar4++],ftw,wtw;
    	rep N data =[ar1++gr1] with vsum ,data,afifo;
    	rep N [ar6++gr6]=afifo;
    \endcode
    
    \param nb1  
        \ru задает разбиение на колонки (необходимо wtw) 
        \en sets columns partition (wtw is necessary) 
		\~
    \param sb   
        \ru задает разбиение на 2 строки 
        \en sets partition into 2 rows 
		\~
    \param vr	
        \ru константа для суммирования 
        \en a constant for summation 
		\~
    \param ar0  
        \ru указатель на столбец SrcMtr1 
        \en pointer to SrcMtr1 column 
		\~
    \param gr0 SrcMtr1 stride
    
    \param ar1  
        \ru указатель на столбец SrcMtr2 
        \en pointer to SrcMtr2 column 
		\~
    \param gr1 SrcMtr2 stride
    
    \param ar4  
        \ru указатель на 2 матрицы весовых коэффициентов по 2 строки в каждой 
        \en pointer to two matrixes of weight coefficients with two rows in each mtr 
		\~
    \param gr4  
        \ru дублирует nb1 
        \en it duplicates nb1 
		\~
    \param gr5  
        \ru Высота матриц N = [0,1,2...31,32,33,...] 
        \en Height of matrixes N = [0,1,2...31,32,33,...] 
		\~
    \param ar6  
        \ru указатель на столбец DstMtr 
        \en pointer to DstMtr column 
		\~
    \param gr6 DstMtr stride
    
    \restr 
        \ru При выходе из функции изменяется содержимое регистров: ar0,ar1,ar6,gr7. 
        \en On exiting the function the contents of registers changes: ar0,ar1,ar6,gr7. 
    */

//! \{ 
 void vec_Mul2D2W2_AddVr(nmreg nb1, nmreg sb, nmreg vr, nmreg ar0, nmreg gr0, nmreg ar1, nmreg gr1, nmreg ar4, nmreg gr4, nmreg gr5, nmreg ar6, nmreg gr6); 
 //! \}


//-----------------------------------------------------------------------------
    /**
		\~
     \defgroup vec_Mul2D2W4_AddVr
   \ingroup vsum
   
        \ru Ядро функции nmppsConvert_16s(nm16s* pSrcVec, nm8s* pDstVec, int nSize). 
        \en nmppsConvert_16s(nm16s* pSrcVec, nm8s* pDstVec, int nSize) function core. 
    
		\~
        \ru Действие функции эквивалентно следующим псевдоинструкциям: 
        \en The function operation is equivalent to the following pseudoinstructions:   
		\~
		\~
    \code
    	rep 4 wfifo=[ar4++],ftw,wtw;
    	rep N data =[ar0++gr0] with vsum ,data,vr;
    	rep 4 wfifo=[ar4++],ftw,wtw;
    	rep N data =[ar1++gr1] with vsum ,data,afifo;
    	rep N [ar6++gr6]=afifo;
    \endcode
    
    \param nb1  
        \ru задает разбиение на колонки (необходимо wtw) 
        \en sets columns partition (wtw is necessary) 
		\~
    \param sb   
        \ru задает разбиение на 4 строки 
        \en sets partition into 4 rows 
		\~
    \param f1cr 
        \ru задает функцию активации 
        \en sets activation function 
		\~
    \param vr	
        \ru константа для суммирования 
        \en a constant for summation 
		\~
    \param ar0  
        \ru указатель на столбец SrcMtr1 
        \en pointer to SrcMtr1 column 
		\~
    \param gr0 SrcMtr1 stride
    
    \param ar1  
        \ru указатель на столбец SrcMtr2 
        \en pointer to SrcMtr2 column 
		\~
    \param gr1 SrcMtr2 stride
    
    \param ar4  
        \ru указатель на 2 матрицы весовых коэффициентов по 4 строки в каждой 
        \en pointer to two matrixes of weight coefficients with four rows in each mtr 
		\~
    \param gr5  
        \ru Высота матриц N = [0,1,2...31,32,33,...] 
        \en Height of matrixes N = [0,1,2...31,32,33,...] 
		\~
    \param ar6  
        \ru указатель на столбец DstMtr 
        \en pointer to DstMtr column 
		\~
    \param gr6 DstMtr stride
    
    \restr 
        \ru При выходе из функции изменяется содержимое регистров: ar0,ar1,ar6,gr7. 
        \en On exiting the function the contents of registers changes: ar0,ar1,ar6,gr7. 
    */

//! \{ 
 void vec_Mul2D2W4_AddVr(nmreg nb1, nmreg sb, nmreg f1cr, nmreg vr, nmreg ar0, nmreg gr0, nmreg ar1, nmreg gr1, nmreg ar4, nmreg gr5, nmreg ar6, nmreg gr6); 
  //! \}


//-----------------------------------------------------------------------------
    /**
		\~
    \defgroup vec_Mul2D2W8_AddVr
    \ingroup vsum
   
        \ru Применяется в MTR_Copyua(). 
        \en It is used in MTR_Copyua(). 
    
		\~
        \ru Действие функции эквивалентно следующим псевдоинструкциям: 
        \en The function operation is equivalent to the following pseudoinstructions: 
		\~
		\~
    \code
    	rep 8 wfifo=[ar4++],ftw,wtw;
    	rep N data =[ar0++gr0] with vsum ,data,vr;
    	rep 8 wfifo=[ar4++],ftw,wtw;
    	rep N data =[ar1++gr1] with vsum ,data,afifo;
    	rep N [ar6++gr6]=afifo;
    \endcode
    
    \param nb1  
        \ru задает разбиение на колонки (необходимо wtw) 
        \en sets columns partition (wtw is necessary) 
		\~
    \param sb   
        \ru задает разбиение на 8 строк 
        \en sets partition into 8 rows 
		\~
    \param vr	
        \ru константа для суммирования 
        \en a constant for summation 
		\~
    \param ar0  
        \ru указатель на столбец SrcMtr1 
        \en pointer to SrcMtr1 column 
		\~
    \param gr0 SrcMtr1 stride
    
    \param ar1  
        \ru указатель на столбец SrcMtr2 
        \en pointer to SrcMtr2 column 
		\~
    \param gr1 SrcMtr2 stride
    
    \param ar4  
        \ru указатель на 2 матрицы весовых коэффициентов по 8 строк в каждой 
        \en pointer to two matrixes of weight coefficients with eight rows in each mtr 
		\~
    \param gr4  
        \ru дублирует nb1 
        \en it duplicates nb1 
		\~
    \param gr5  
        \ru Высота матриц N = [0,1,2...31,32,33,...] 
        \en Height of matrixes N = [0,1,2...31,32,33,...] 
		\~
    \param ar6  
        \ru указатель на столбец DstMtr 
        \en pointer to DstMtr column 
		\~
    \param gr6 DstMtr stride
    
    \restr 
        \ru При выходе из функции изменяется содержимое регистров: ar0,ar1,ar6,gr7. 
        \en On exiting the function the contents of registers changes: ar0,ar1,ar6,gr7. 
    */

//! \{ 
 void vec_Mul2D2W8_AddVr(nmreg nb1, nmreg sb, nmreg vr, nmreg ar0, nmreg gr0, nmreg ar1, nmreg gr1, nmreg ar4, nmreg gr4, nmreg gr5, nmreg ar6, nmreg gr6); 
 //! \}


//-----------------------------------------------------------------------------
    /**
		\~
     \defgroup vec_Mul3D3W2_AddVr
   \ingroup vsum
   
        \ru 
        \en 
    
		\~
        \ru Действие функции эквивалентно следующим псевдоинструкциям: 
        \en The function operation is equivalent to the following pseudoinstructions:   
		\~
		\~
    \code
    	rep 2 wfifo=[ar4++],ftw,wtw;
    	rep N data =[ar0++gr0] with vsum ,data,vr;
    	rep 2 wfifo=[ar4++],ftw,wtw;
    	rep N data =[ar1++gr1] with vsum ,data,afifo;
    	rep 2 wfifo=[ar4++],ftw,wtw;
    	rep N data =[ar2++gr2] with vsum ,data,afifo;
    	rep N [ar6++gr6]=afifo;
    \endcode
    
    \param nb1  
        \ru задает разбиение на колонки (необходимо wtw) 
        \en sets columns partition (wtw is necessary) 
		\~
    \param sb   
        \ru задает разбиение на 2 строки 
        \en sets partition into 2 rows 
		\~
    \param vr	
        \ru константа для суммирования 
        \en a constant for summation 
		\~
    \param ar0  
        \ru указатель на столбец SrcMtr1 
        \en pointer to SrcMtr1 column 
		\~
    \param gr0 SrcMtr1 stride
    
    \param ar1  
        \ru указатель на столбец SrcMtr2 
        \en pointer to SrcMtr2 column 
		\~
    \param gr1 SrcMtr2 stride
    
    \param ar2  
        \ru указатель на столбец SrcMtr3 
        \en pointer to SrcMtr3 column 
		\~
    \param gr2 SrcMtr3 stride
    
    \param ar4 
        \ru указатель на 3 матрицы весовых коэффициентов по 2 строки в каждой 
        \en pointer to three matrixes of weight coefficients with two rows in each mtr 
		\~
    \param gr4  
        \ru дублирует nb1 
        \en it duplicates nb1 
		\~
    \param gr5  
        \ru Высота матриц N = [0,1,2...31,32,33,...] 
        \en Height of matrixes N = [0,1,2...31,32,33,...] 
		\~
    \param ar6  
        \ru указатель на столбец DstMtr 
        \en pointer to DstMtr column 
		\~
    \param gr6 DstMtr stride
    
    \restr 
        \ru При выходе из функции изменяется содержимое регистров: ar0,ar1,ar2,ar6,gr7. 
        \en On exiting the function the contents of registers changes: ar0,ar1,ar2,ar6,gr7. 
    */

//! \{ 
 void vec_Mul3D3W2_AddVr(nmreg nb1, nmreg sb, nmreg vr, nmreg ar0, nmreg gr0, nmreg ar1, nmreg gr1, nmreg ar2, nmreg gr2, nmreg ar4, nmreg gr4, nmreg gr5, nmreg ar6, nmreg gr6); 
 //! \}



//-----------------------------------------------------------------------------
    /**
		\~
    \defgroup vec_Mul3D3W8_AddVr
    \ingroup vsum
   
        \ru 
        \en 
    
		\~
        \ru Действие функции эквивалентно следующим псевдоинструкциям: 
        \en The function operation is equivalent to the following pseudoinstructions:   
		\~
		\~
    \code
    	rep 8 wfifo=[ar4++],ftw,wtw;
    	rep N data =[ar0++gr0] with vsum ,data,vr;
    	rep 8 wfifo=[ar4++],ftw,wtw;
    	rep N data =[ar1++gr1] with vsum ,data,afifo;
    	rep 8 wfifo=[ar4++],ftw,wtw;
    	rep N data =[ar2++gr2] with vsum ,data,afifo;
    	rep N [ar6++gr6]=afifo;
    \endcode
    
    \param nb1  
        \ru задает разбиение на колонки (необходимо wtw) 
        \en sets columns partition (wtw is necessary) 
		\~
    \param sb   
        \ru задает разбиение на 8 строк 
        \en sets partition into 8 rows 
		\~
    \param vr	
        \ru константа для суммирования 
        \en a constant for summation 
		\~
    \param ar0  
        \ru указатель на столбец SrcMtr1 
        \en pointer to SrcMtr1 column 
		\~
    \param gr0 SrcMtr1 stride
    
    \param ar1  
        \ru указатель на столбец SrcMtr2 
        \en pointer to SrcMtr2 column 
		\~
    \param gr1 SrcMtr2 stride
    
    \param ar2  
        \ru указатель на столбец SrcMtr3 
        \en pointer to SrcMtr3 column 
		\~
    \param gr2 SrcMtr3 stride
    
    \param ar4 
        \ru указатель на 3 матрицы весовых коэффициентов по 8 строк в каждой 
        \en pointer to three matrixes of weight coefficients with two rows in each mtr 
		\~
    \param gr4  
        \ru дублирует nb1 
        \en it duplicates nb1 
		\~
    \param gr5  
        \ru Высота матриц N = [0,1,2...31,32,33,...] 
        \en Height of matrixes N = [0,1,2...31,32,33,...] 
		\~
    \param ar6  
        \ru указатель на столбец DstMtr 
        \en pointer to DstMtr column 
		\~
    \param gr6 DstMtr stride
    
    \restr 
        \ru При выходе из функции изменяется содержимое регистров: ar0,ar1,ar2,ar6,gr7. 
        \en On exiting the function the contents of registers changes: ar0,ar1,ar2,ar6,gr7. 
    */

//! \{ 
 void vec_Mul3D3W8_AddVr(nmreg nb1, nmreg sb, nmreg vr, nmreg ar0, nmreg gr0, nmreg ar1, nmreg gr1, nmreg ar2, nmreg gr2, nmreg ar4, nmreg gr4, nmreg gr5, nmreg ar6, nmreg gr6); 
 //! \}



//-----------------------------------------------------------------------------
    /**
		\~
     \defgroup vec_Mul4D4W2_AddVr
   \ingroup vsum
   
        \ru Ядро функции nmppsConvert_32s(nm32s* pSrcVec, nm8s* pDstVec, int nSize). 
        \en nmppsConvert_32s(nm32s* pSrcVec, nm8s* pDstVec, int nSize) function core. 
    
		\~
        \ru Действие функции эквивалентно следующим псевдоинструкциям: 
        \en The function operation is equivalent to the following pseudoinstructions:   
		\~
		\~
    \code
    	rep 2 wfifo=[ar4++],ftw,wtw;
    	rep N data =[ar0++gr0] with vsum ,data,vr;
    	rep 2 wfifo=[ar4++],ftw,wtw;
    	rep N data =[ar1++gr1] with vsum ,data,afifo;
    	rep 2 wfifo=[ar4++],ftw,wtw;
    	rep N data =[ar2++gr2] with vsum ,data,afifo;
    	rep 2 wfifo=[ar4++],ftw,wtw;
    	rep N data =[ar3++gr3] with vsum ,data,afifo;
    	rep N [ar6++gr6]=afifo;
    \endcode
    
    \param nb1  
        \ru задает разбиение на колонки (необходимо wtw) 
        \en sets columns partition (wtw is necessary) 
		\~
    \param sb   
        \ru задает разбиение на 2 строки 
        \en sets partition into 2 rows 
		\~
    \param vr	
        \ru константа для суммирования 
        \en a constant for summation 
		\~
    \param ar0  
        \ru указатель на столбец SrcMtr1 
        \en pointer to SrcMtr1 column 
		\~
    \param gr0 SrcMtr1 stride
    
    \param ar1  
        \ru указатель на столбец SrcMtr2 
        \en pointer to SrcMtr2 column 
		\~
    \param gr1 SrcMtr2 stride
    
    \param ar2  
        \ru указатель на столбец SrcMtr3 
        \en pointer to SrcMtr3 column 
		\~
    \param gr2 SrcMtr3 stride
    
    \param ar3  
        \ru указатель на столбец SrcMtr4 
        \en pointer to SrcMtr4 column 
		\~
    \param gr3 SrcMtr4 stride
    
    \param ar4 
        \ru указатель на 4 матрицы весовых коэффициентов по 2 строки в каждой 
        \en pointer to four matrixes of weight coefficients with two rows in each mtr 
		\~
    \param gr4  
        \ru дублирует nb1 
        \en it duplicates nb1 
		\~
    \param gr5  
        \ru Высота матриц N = [0,1,2...31,32,33,...] 
        \en Height of matrixes N = [0,1,2...31,32,33,...] 
		\~
    \param ar6  
        \ru указатель на столбец DstMtr 
        \en pointer to DstMtr column 
		\~
    \param gr6 DstMtr stride
    
    \restr 
        \ru При выходе из функции изменяется содержимое регистров: ar0,ar1,ar2,ar3,ar6,gr7. 
        \en On exiting the function the contents of registers changes: ar0,ar1,ar2,ar3,ar6,gr7. 
    */

//! \{ 
 void vec_Mul4D4W2_AddVr(nmreg nb1, nmreg sb, nmreg vr, nmreg ar0, nmreg gr0, nmreg ar1, nmreg gr1, nmreg ar2, nmreg gr2, nmreg ar3, nmreg gr3, nmreg ar4, nmreg gr4, nmreg gr5, nmreg ar6, nmreg gr6); 
 //! \}


//-----------------------------------------------------------------------------
    /**
		\~
     \defgroup vec_MulVN_AddVN
   \ingroup vsum
   
        \ru Ядро функции MTR_MulC_AddVsVc( ). 
        \en MTR_MulC_AddVsVc( ) function core. 
    
		\~
        \ru Действие функции эквивалентно следующим псевдоинструкциям: 
        \en The function operation is equivalent to the following pseudoinstructions:   
		\~
		\~
    \code
    	rep N data=[ar0++gr0] with vsum ,data, vr;
    	rep N data=[ar1++gr1] with afifo+data;
    	rep N [ar6++gr6]=afifo;
    \endcode
    
    \param nb1  
        \ru задает разбиение на колонки (необходимо wtw) 
        \en sets columns partition (wtw is necessary) 
		\~
    \param sb   
        \ru задает разбиение на 8 строк 
        \en sets partition into 8 rows 
		\~
    \param f1cr 
        \ru задает функцию активации 
        \en sets activation function 
		\~
    \param woper 
        \ru в рабочей матрице должны быть загружены весовые коэффициенты 
        \en weight coefficients should be loaded to the working mtr 
		\~
    \param ar0  
        \ru указатель на столбец SrcMtr1 
        \en pointer to SrcMtr1 column 
		\~
    \param gr0 SrcMtr1 stride
    
    \param ar1  
        \ru указатель на столбец SrcMtr2 
        \en pointer to SrcMtr2 column 
		\~
    \param gr1 SrcMtr2 stride
    
    \param gr5  
        \ru Высота матриц N = [0,1,2...31,32,33,...] 
        \en Height of matrixes N = [0,1,2...31,32,33,...] 
		\~
    \param ar6  
        \ru указатель на столбец DstMtr 
        \en pointer to DstMtr column 
		\~
    \param gr6 DstMtr stride
    
    \restr 
        \ru При выходе из функции изменяется содержимое регистров: ar0,ar1,ar6. 
        \en On exiting the function the contents of registers changes: ar0,ar1,ar6. 
    */

//! \{ 
 void vec_MulVN_AddVN(nmreg nb1, nmreg sb, nmreg f1cr, nmreg woper, nmreg ar0, nmreg gr0, nmreg ar1, nmreg gr1, nmreg gr5, nmreg ar6, nmreg gr6); 
 //! \}


//-----------------------------------------------------------------------------
    /**
		\~
     \defgroup vec_Sub
   \ingroup vCore
   
        \ru Ядро функции nmppsSub(). 
        \en nmppsSub() function core. 
    
		\~
        \ru Действие функции эквивалентно следующим псевдоинструкциям: 
        \en The function operation is equivalent to the following pseudoinstructions:   
		\~
		\~
    \code
    	rep N data=[ar0++gr0] with data;
    	rep N data=[ar1++gr1] with data - afifo;
    	rep N [ar6++gr6]=afifo;
    \endcode
    
    \param nb1  
        \ru задает разбиение на колонки (необходимо wtw) 
        \en sets columns partition (wtw is necessary) 
		\~
    \param ar0  
        \ru указатель на столбец SrcMtr1 
        \en pointer to SrcMtr1 column 
		\~
    \param gr0 SrcMtr1 stride
    
    \param ar1  
        \ru указатель на столбец SrcMtr2 
        \en pointer to SrcMtr2 column 
		\~
    \param gr1 SrcMtr2 stride
    
    \param gr5  
        \ru Высота матриц N = [0,1,2...31,32,33,...] 
        \en Height of matrixes N = [0,1,2...31,32,33,...] 
		\~
    \param ar6  
        \ru указатель на столбец DstMtr 
        \en pointer to DstMtr column 
		\~
    \param gr6 DstMtr stride
    
    \restr 
        \ru При выходе из функции изменяется содержимое регистров: ar0,ar1,ar6. 
        \en On exiting the function the contents of registers changes: ar0,ar1,ar6. 
    */

//! \{ 
 void vec_Sub(nmreg nb1, nmreg ar0, nmreg gr0, nmreg ar1, nmreg gr1, nmreg gr5, nmreg ar6, nmreg gr6); 
 //! \}


//-----------------------------------------------------------------------------
    /**
		\~
    \defgroup vec_SubAbs
    \ingroup vcomplex
   
        \ru Ядро функции nmppsAbsDiff(). 
        \en nmppsAbsDiff() function core. 
    
		\~
        \ru Действие функции эквивалентно следующим псевдоинструкциям: 
        \en The function operation is equivalent to the following pseudoinstructions:   
		\~
		\~
    \code
    	rep N data=[ar0++gr0]	with data
    	rep N data=[ar1++gr1]	with afifo-data;
    	rep N [ar4],ram =afifo	with activate afifo;
    	rep N					with vsum afifo,ram,ram;			
    	rep N [ar6++gr6]= afifo;
    \endcode
    
    \param nb1  
        \ru задает разбиение на колонки (необходимо wtw) 
        \en sets columns partition (wtw is necessary) 
		\~
    \param sb   
        \ru задает разбиение на 8 строк 
        \en sets partition into 8 rows 
		\~
    \param f1cr 
        \ru задает функцию активации 
        \en sets activation function 
		\~
    \param ar0  
        \ru указатель на столбец SrcMtr1 
        \en pointer to SrcMtr1 column 
		\~
    \param gr0 SrcMtr1 stride
    
    \param ar1  
        \ru указатель на столбец SrcMtr2 
        \en pointer to SrcMtr2 column 
		\~
    \param gr1 SrcMtr2 stride
    
    \param ar4  
        \ru указатель на временный буфер (1 64р. слово) 
        \en pointer to a temporary buffer (one 64-bit word) 
		\~
    \param gr5  
        \ru Высота матриц N = [0,1,2...31,32,33,...] 
        \en Height of matrixes N = [0,1,2...31,32,33,...] 
		\~
    \param ar6  
        \ru указатель на столбец DstMtr 
        \en pointer to DstMtr column 
		\~
    \param gr6 DstMtr stride
    
    \restr 
        \ru При выходе из функции изменяется содержимое регистров: ar0,ar6. 
        \en On exiting the function the contents of registers changes: ar0,ar6. 
    */

//! \{ 
 void vec_SubAbs(nmreg nb1, nmreg sb, nmreg f1cr, nmreg ar0, nmreg gr0, nmreg ar1, nmreg gr1, nmreg ar4, nmreg gr5, nmreg ar6, nmreg gr6); 
 //! \}


//*****************************************************************************

    /**
		\~
    \defgroup vec_SubVN_Abs
    \ingroup vcomplex
   
        \ru Ядро функции mtr_SubMV_Abs(). 
        \en mtr_SubMV_Abs() function core. 
    
		\~
        \ru Действие функции эквивалентно следующим псевдоинструкциям: 
        \en The function operation is equivalent to the following pseudoinstructions:   
		\~
		\~
    \code
    	rep N ram=[ar1]
    	rep N data=[ar0++gr0]	with data-ram;
    	rep N [ar2++]=afifo		with activate afifo;	    
	//  ar2,ar5- internal pointers to temporary buffer size of long[32]
    	rep N data=[ar5++]		with vsum afifo,data,data;
    	rep N [ar6++gr6]=afifo;
    \endcode
    
    \param nb1  
        \ru задает разбиение на колонки (необходимо wtw) 
        \en sets columns partition (wtw is necessary) 
		\~
    \param sb   
        \ru задает разбиение на 8 строк 
        \en sets partition into 8 rows 
		\~
    \param f1cr 
        \ru задает функцию активации 
        \en sets activation function 
		\~
    \param woper 
        \ru в рабочей матрице должны быть загружены весовые коэффициенты 
        \en weight coefficients should be loaded to the working mtr 
		\~
    \param ar0  
        \ru указатель на столбец SrcMtr 
        \en pointer to SrcMtr column 
		\~
    \param gr0 SrcMtr stride
    
    \param ar1  
        \ru указатель на на маску (1 64р. слово) 
        \en pointer to the mask (one 64-bit word) 
		\~
    \param gr5  
        \ru Высота матриц N = [0,1,2...31,32,33,...] 
        \en Height of matrixes N = [0,1,2...31,32,33,...] 
		\~
    \param ar6  
        \ru указатель на столбец DstMtr 
        \en pointer to DstMtr column 
		\~
    \param gr6 DstMtr stride
    
    
    \restr  
        \ru При выходе из функции изменяется содержимое регистров: ar0,ar6. 
        \en On exiting the function the contents of registers changes: ar0,ar6. 
		\~
    \par
    \xmlonly
    \endxmlonly
    */

//! \{ 
 void vec_SubVN_Abs(nmreg nb1, nmreg sb, nmreg f1cr, nmreg woper, nmreg ar0, nmreg gr0, nmreg ar1, nmreg gr5, nmreg ar6, nmreg gr6); 
 //! \}


//-----------------------------------------------------------------------------
    /**
    \defgroup vec_Swap
    \ingroup vcomplex
   
        \ru Ядро функции mtr_SubVN_Abs(). 
        \en mtr_SubVN_Abs() function core. 
		\~
    \ru Функция осуществляет два одноыременных копирования:\n
        [ar0++gr0]	=>	[ar4++gr4] \n
        [ar1++gr1]	=>	[ar6++gr6] \n
        если ar6=ar0,gr6=gr0, ar4=ar1,gr4=gr1\n
        то выполняется перестановка двух векторов\n 
    \en The function performs two simultaneous copyings: \n
        [ar0++gr0]	=>	[ar4++gr4] \n
        [ar1++gr1]	=>	[ar6++gr6] \n
        if ar6=ar0,gr6=gr0, ar4=ar1,gr4=gr1\n
        then two vectors are permuted\n 
    
    
        \ru Действие функции эквивалентно следующим псевдоинструкциям: 
        \en The function operation is equivalent to the following pseudoinstructions:   
		\~
		\~
    \code
    	rep N ram =[ar0++gr0];
    	rep N data=[ar1++gr1]	with data;
    	rep N [ar6++gr6]=afifo	with ram;
    	rep N [ar4++gr4]=afifo;
    \endcode
    
    \param ar0  
        \ru указатель на столбец SrcMtr1 
        \en pointer to SrcMtr1 column 
		\~
    \param gr0 SrcMtr1 stride
    
    \param ar1  
        \ru указатель на столбец SrcMtr2 
        \en pointer to SrcMtr2 column 
		\~
    \param gr1 SrcMtr2 stride
    
    \param ar4  
        \ru указатель на столбец DstMtr1 
        \en pointer to DstMtr1 column 
		\~
    \param gr4 DstVec1 stride
    
    \param gr5  
        \ru Высота матриц N = [0,1,2...31,32,33,...] 
        \en Height of matrixes N = [0,1,2...31,32,33,...] 
		\~
    \param ar6  
        \ru указатель на столбец DstMtr2 
        \en pointer to DstMtr2 column 
		\~
    \param gr6 DstVec2 stride
    
    \restr 
        \ru При выходе из функции изменяется содержимое регистров: ar0,ar1,ar4,ar6. 
        \en On exiting the function the contents of registers changes: ar0,ar1,ar4,ar6. 
    */

//! \{ 
 void vec_Swap(nmreg ar0, nmreg gr0, nmreg ar1, nmreg gr1, nmreg ar4, nmreg gr4, nmreg gr5, nmreg ar6, nmreg gr6); 
 //! \}


//-----------------------------------------------------------------------------
    /**
		\~
     \defgroup vec_MUL_2V4toW8_shift
   \ingroup vcomplex
   
        \ru Ядро функции SIG_ResizeDown2(nm8u7b* pSrcVec, nm8u7b* pDstVec, int nSize). 
        \en SIG_ResizeDown2(nm8u7b* pSrcVec, nm8u7b* pDstVec, int nSize) function core. 
    
		\~
        \ru Действие функции эквивалентно следующим псевдоинструкциям: 
        \en The function operation is equivalent to the following pseudoinstructions:   
		\~
		\~
    \code
    	rep N ram=[ar3];
    	rep 8  wfifo=[ar5++],ftw,wtw;
    	rep N data =[ar0++gr0],ftw,wtw	with vsum ,data,0;
    	rep N data =[ar1++gr1]			with vsum ,data,afifo;
    	rep N							with mask ram,shift afifo,0;
    	rep N [ar6++gr6]=afifo;
    \endcode
    
    \param nb1  
        \ru задает разбиение на колонки 
        \en sets columns partition 
		\~
    \param sb   
        \ru задает разбиение на 4 строки 
        \en sets partition into four rows 
		\~
    \param ar0  
        \ru указатель на столбец SrcMtr 
        \en pointer to SrcMtr column 
		\~
    \param gr0 SrcMtr stride
    
    \param ar1  
        \ru указатель на столбец SrcMtr2 
        \en pointer to SrcMtr2 column 
		\~
    \param gr1 SrcMtr2 stride
    
    \param ar3  
        \ru указатель на 64р. маску 
        \en pointer to a 64-bit mask 
		\~
    \param gr4  
        \ru дублирует nb1 
        \en it duplicates nb1 
		\~
    \param ar5  
        \ru указатель на матрицу весовых коэффициентов (16 64р.слов) 
        \en pointer to the mtr of weight coefficients (sixteen 64-bit words) 
		\~
    \param gr5  
        \ru Высота матриц N = [0,1,2...31,32,33,...] 
        \en Height of matrixes N = [0,1,2...31,32,33,...] 
		\~
    \param ar6  
        \ru указатель на столбец DstMtr 
        \en pointer to DstMtr column 
		\~
    \param gr6 DstMtr stride
    
    \restr  
        \ru При выходе из функции изменяется содержимое регистров: 
                ar0,ar1,ar2,ar4,ar6,gr2,gr5. 
        \en On exiting the function the contents of registers changes: 
                ar0,ar1,ar2,ar4,ar6,gr2,gr5. 
    */

//! \{ 
 void vec_MUL_2V4toW8_shift(nmreg nb1, nmreg sb, nmreg ar0, nmreg gr0, nmreg ar1, nmreg gr1, nmreg ar3, nmreg gr4, nmreg ar5, nmreg gr5, nmreg ar6, nmreg gr6); 
 //! \}


//-----------------------------------------------------------------------------
    /**
		\~
     \defgroup vec_MUL_2V8toW16_shift
   \ingroup vcomplex
   
        \ru Ядро функции SIG_ResizeDown2(nm16u15b* pSrcVec, nm16u15b* pDstVec, int nSize). 
        \en SIG_ResizeDown2(nm16u15b* pSrcVec, nm16u15b* pDstVec, int nSize) function core. 
    
		\~
        \ru Действие функции эквивалентно следующим псевдоинструкциям: 
        \en The function operation is equivalent to the following pseudoinstructions:   
		\~
		\~
    \code
    	rep N ram=[ar3];
    	rep 16 wfifo=[ar5++],ftw,wtw;
    	rep N data =[ar0++gr0],ftw,wtw	with vsum ,data,0;
    	rep N data =[ar1++gr1]			with vsum ,data,afifo;
    	rep N							with mask ram,shift afifo,0;
    	rep N [ar6++gr6]=afifo;
    \endcode
    
    \param nb1  
        \ru задает разбиение на колонки 
        \en sets columns partition 
		\~
    \param sb   
        \ru задает разбиение на 2 строки 
        \en sets partition into two rows 
		\~
    \param ar0  
        \ru указатель на столбец SrcMtr1 
        \en pointer to SrcMtr1 column 
		\~
    \param gr0 SrcMtr1 stride
    
    \param ar1  
        \ru указатель на столбец SrcMtr2 
        \en pointer to SrcMtr2 column 
		\~
    \param gr1 SrcMtr2 stride
    
    \param ar3  
        \ru указатель на 64р. маску 
        \en pointer to a 64-bit mask 
		\~
    \param gr4  
        \ru дублирует nb1 
        \en it duplicates nb1 
		\~
    \param ar5  
        \ru указатель на матрицу весовых коэффициентов (16 64р.слов) 
        \en pointer to the mtr of weight coefficients (sixteen 64-bit words) 
		\~
    \param gr5  
        \ru Высота матриц N = [0,1,2...31,32,33,...] 
        \en Height of matrixes N = [0,1,2...31,32,33,...] 
		\~
    \param ar6  
        \ru указатель на столбец DstMtr 
        \en pointer to DstMtr column 
		\~
    \param gr6 DstMtr stride
    
    \restr 
        \ru При выходе из функции изменяется содержимое регистров: 
               ar0,ar1,ar2,ar4,ar6,gr2,gr5. 
        \en On exiting the function the contents of registers changes: 
               ar0,ar1,ar2,ar4,ar6,gr2,gr5. 
    */

//! \{ 
 void vec_MUL_2V8toW16_shift(nmreg nb1, nmreg sb, nmreg ar0, nmreg gr0, nmreg ar1, nmreg gr1, nmreg ar3, nmreg gr4, nmreg ar5, nmreg gr5, nmreg ar6, nmreg gr6); 
 //! \}


//-----------------------------------------------------------------------------
    /**
		\~
    \defgroup vec_not_data
    \ingroup vCore
   
        \ru Ядро функции nmppsNot_( ). 
        \en nmppsNot_( ) function core. 
    
		\~
        \ru Действие функции эквивалентно следующим псевдоинструкциям: 
        \en The function operation is equivalent to the following pseudoinstructions:   
		\~
		\~
    \code
    	rep N data=[ar0++gr0] with not data;
    	rep N [ar6++gr6]=afifo;
    \endcode
    
    \param ar0  
        \ru указатель на столбец SrcMtr1 
        \en pointer to SrcMtr1 column 
		\~
    \param gr0 SrcMtr1 stride
    
    \param gr5  
        \ru Высота матриц N = [0,1,2...31,32,33,...] 
        \en Height of matrixes N = [0,1,2...31,32,33,...] 
		\~
    \param ar6  
        \ru указатель на столбец DstMtr 
        \en pointer to DstMtr column 
		\~
    \param gr6 DstMtr stride
    
    \restr 
        \ru При выходе из функции изменяется содержимое регистров: ar0,ar1,ar6. 
        \en On exiting the function the contents of registers changes: ar0,ar1,ar6. 
    */

//! \{ 
 void vec_not_data(nmreg ar0, nmreg gr0, nmreg gr5, nmreg ar6, nmreg gr6); 
 //! \}


//-----------------------------------------------------------------------------
    /**
		\~
     \defgroup vec_ram
   \ingroup vCore
   
        \ru Ядро функции nmppsSet_(). 
        \en nmppsSet_() function core. 
    
		\~
        \ru Функция служит для заполнения массива константой. 
        \en the function serves for filling an array with a constant. 
		\~
    \ru Действие функции эквивалентно следующим псевдоинструкциям: 
    \en The function operation is equivalent to the following pseudoinstructions:   
		\~
		\~
    \code
    	rep N ram=[ar0] with data;
    	rep N [ar6++gr6]=afifo;
    \endcode
    
    \param ar0  
        \ru указатель на столбец SrcMtr1 
        \en pointer to SrcMtr1 column 
		\~
    \param gr5  
        \ru Высота матриц N = [0,1,2...31,32,33,...] 
        \en Height of matrixes N = [0,1,2...31,32,33,...] 
		\~
    \param ar6  
        \ru указатель на столбец DstMtr 
        \en pointer to DstMtr column 
		\~
    \param gr6 DstMtr stride
    
    \restr 
        \ru При выходе из функции изменяется содержимое регистров: ar0,ar6. 
        \en On exiting the function the contents of registers changes: ar0,ar6. 
    */

//! \{ 
 void vec_ram(nmreg ar0, nmreg gr5, nmreg ar6, nmreg gr6); 
 //! \}


//-----------------------------------------------------------------------------
    /**
		\~
     \defgroup vec_ram_sub_data
   \ingroup vCore
   
        \ru Ядро функции nmppsSubCRev(). 
        \en nmppsSubCRev() function core. 
    
		\~
        \ru Действие функции эквивалентно следующим псевдоинструкциям: 
        \en The function operation is equivalent to the following pseudoinstructions:   
		\~
		\~
    \code
    	rep N ram=[ar1];
    	rep N data=[ar0++gr0] with ram-data;
    	rep N [ar6++gr6]=afifo;
    \endcode
    
    \param nb1  
        \ru задает разбиение на колонки (необходимо wtw) 
        \en sets columns partition (wtw is necessary) 
		\~
    \param ar0  
        \ru указатель на столбец SrcMtr 
        \en pointer to SrcMtr column 
		\~
    \param gr0 SrcMtr stride
    
    \param gr5  
        \ru Высота матриц N = [0,1,2...31,32,33,...] 
        \en Height of matrixes N = [0,1,2...31,32,33,...] 
		\~
    \param ar6  
        \ru указатель на столбец DstMtr 
        \en pointer to DstMtr column 
		\~
    \param gr6 DstMtr stride
    
    \restr 
        \ru При выходе из функции изменяется содержимое регистров: ar0,ar6. 
        \en On exiting the function the contents of registers changes: ar0,ar6. 
    */

//! \{ 
 void vec_ram_sub_data(nmreg nb1, nmreg ar0, nmreg gr0, nmreg gr5, nmreg ar6, nmreg gr6); 
 //! \}


//-----------------------------------------------------------------------------
    /**
		\~
    \defgroup vec_vsum_activate_data_0
    \ingroup vCore
   
        \ru Действие функции эквивалентно следующим псевдоинструкциям: 
        \en The function operation is equivalent to the following pseudoinstructions:   
		\~
		\~
    \code
    	rep N data=[ar0++gr0] with vsum ,activate,0;
    	rep N [ar6++gr6]=afifo;
    \endcode
    
    \param nb1  
        \ru задает разбиение на колонки (необходимо wtw) 
        \en sets columns partition (wtw is necessary) 
		\~
    \param sb   
        \ru задает разбиение на 8 строк 
        \en sets partition into eight rows 
		\~
    \param f1cr 
        \ru задает функцию активации 
        \en sets activation function 
		\~
    \param woper 
        \ru в рабочей матрице должны быть загружены весовые коэффициенты 
        \en weight coefficients should be loaded to the working mtr 
		\~
    \param ar0  
        \ru указатель на столбец SrcMtr1 
        \en pointer to SrcMtr1 column 
		\~
    \param gr0 SrcMtr1 stride
    
    \param ar1  
        \ru указатель на столбец SrcMtr2 
        \en pointer to SrcMtr2 column 
		\~
    \param gr1 SrcMtr2 stride
    
    \param gr5  
        \ru Высота матриц N = [0,1,2...31,32,33,...] 
        \en Height of matrixes N = [0,1,2...31,32,33,...] 
		\~
    \param ar6  
        \ru указатель на столбец DstMtr 
        \en pointer to DstMtr column 
		\~
    \param gr6 DstMtr stride
    
    \restr 
        \ru При выходе из функции изменяется содержимое регистров: ar0,ar6. 
        \en On exiting the function the contents of registers changes: ar0,ar6. 
    */

//! \{ 
 void vec_vsum_activate_data_0(nmreg nb1, nmreg sb, nmreg f1cr, nmreg woper, nmreg ar0, nmreg gr0, nmreg ar1, nmreg gr1, nmreg gr5, nmreg ar6, nmreg gr6); 
 //! \}


//-----------------------------------------------------------------------------
    /**
		\~
    \defgroup vec_vsum_data_0
    \ingroup vsum
   
        \ru Действие функции эквивалентно следующим псевдоинструкциям: 
        \en The function operation is equivalent to the following pseudoinstructions:   
		\~
		\~
    \code
    	rep N data=[ar0++gr0] with vsum ,data,0;
    	rep N [ar6++gr6]=afifo;
    \endcode
    
    \param nb1  
        \ru задает разбиение на колонки (необходимо wtw) 
        \en sets columns partition (wtw is necessary) 
		\~
    \param sb   
        \ru задает разбиение на 8 строк 
        \en sets partition into eight rows 
		\~
    \param woper 
        \ru в рабочей матрице должны быть загружены весовые коэффициенты 
        \en weight coefficients should be loaded to the working mtr 
		\~
    \param ar0  
        \ru указатель на столбец SrcMtr 
        \en pointer to SrcMtr column 
		\~
    \param gr0 SrcMtr stride
    
    \param gr5  
        \ru Высота матриц N = [0,1,2...31,32,33,...] 
        \en Height of matrixes N = [0,1,2...31,32,33,...] 
		\~
    \param ar6  
        \ru указатель на столбец DstMtr 
        \en pointer to DstMtr column 
		\~
    \param gr6 DstMtr stride
    
    \restr 
        \ru При выходе из функции изменяется содержимое регистров: ar0,ar6. 
        \en On exiting the function the contents of registers changes: ar0,ar6. 
    */

//! \{ 
 void vec_vsum_data_0(nmreg nb1, nmreg sb, nmreg woper, nmreg ar0, nmreg gr0, nmreg gr5, nmreg ar6, nmreg gr6); 
 //! \}


//-----------------------------------------------------------------------------
    /**
		\~
     \defgroup vec_vsum_data_afifo
   \ingroup vcomplex
   
        \ru Используется в nmppsSum(nm1* pSrcVec, void* pTmpBuf, int nSize) 
        \en It is used in nmppsSum(nm1* pSrcVec,  void* pTmpBuf, int nSize) 
    
		\~
        \ru Действие функции эквивалентно следующим псевдоинструкциям: 
        \en The function operation is equivalent to the following pseudoinstructions:   
		\~
		\~
    \code
    	rep 1   data=vfalse; 
		.repeat N;
    	rep 1	data=[ar0++gr0] with vsum ,data,afifo; 
		.endrepeat;
    	rep 1   [ar6]=afifo;
    \endcode
    
    \param nb1  
        \ru задает разбиение на колонки (необходимо wtw) 
        \en sets columns partition (wtw is necessary) 
		\~
    \param sb   
        \ru задает разбиение на строки 
        \en sets partition into rows 
		\~
    \param woper 
        \ru в рабочей матрице должны быть загружены весовые коэффициенты 
        \en weight coefficients should be loaded to the working mtr 
		\~
    \param ar0  
        \ru указатель на столбец SrcMtr 
        \en pointer to SrcMtr column 
		\~
    \param gr0 SrcMtr stride
    
    \param gr5  
        \ru Высота матриц N = [0,1,2...31,32,33,...] 
        \en Height of matrixes N = [0,1,2...31,32,33,...] 
		\~
    \param ar6  
        \ru указатель на столбец DstMtr 
        \en pointer to DstMtr column 
		\~
    \restr  
        \ru При выходе из функции изменяется содержимое регистров: ar0. 
        \en On exiting the function the contents of registers changes: ar0. 
    */

//! \{ 
 void vec_vsum_data_afifo(nmreg nb1, nmreg sb, nmreg woper, nmreg ar0, nmreg gr0, nmreg gr5, nmreg ar6); 
 //! \}


//-----------------------------------------------------------------------------
    /**
		\~
    \defgroup vec_vsum_data_vr
    \ingroup vsum
   
        \ru Действие функции эквивалентно следующим псевдоинструкциям: 
        \en The function operation is equivalent to the following pseudoinstructions:   
		\~
		\~
    \code
    	rep N data=[ar0++gr0] with vsum ,data,vr;
    	rep N [ar6++gr6]=afifo;
    \endcode
    
    \param nb1  
        \ru задает разбиение на колонки (необходимо wtw) 
        \en sets columns partition (wtw is necessary) 
		\~
    \param sb   
        \ru задает разбиение на 8 строк 
        \en sets partition into eight rows 
		\~
    \param f1cr 
        \ru задает функцию активации 
        \en sets activation function 
		\~
    \param woper 
        \ru в рабочей матрице должны быть загружены весовые коэффициенты 
        \en weight coefficients should be loaded to the working mtr 
		\~
    \param vr	
        \ru константа для суммирования 
        \en the constant for summation 
		\~
    \param ar0  
        \ru указатель на столбец SrcMtr 
        \en pointer to SrcMtr column 
		\~
    \param gr0 SrcMtr stride
    
    \param gr5  
        \ru Высота матриц N = [0,1,2...31,32,33,...] 
        \en Height of matrixes N = [0,1,2...31,32,33,...] 
		\~
    \param ar6  
        \ru указатель на столбец DstMtr 
        \en pointer to DstMtr column 
		\~
    \param gr6 DstMtr stride
    
    \restr  
        \ru При выходе из функции изменяется содержимое регистров: ar0,ar6. 
        \en On exiting the function the contents of registers changes: ar0,ar6. 
    */

//! \{ 
 void vec_vsum_data_vr(nmreg nb1, nmreg sb, nmreg woper, nmreg vr, nmreg ar0, nmreg gr0, nmreg gr5, nmreg ar6, nmreg gr6); 
 //! \}


//-----------------------------------------------------------------------------
    /**
		\~
    \defgroup vec_vsum_shift_data_0
    \ingroup vsum
   
        \ru Действие функции эквивалентно следующим псевдоинструкциям: 
        \en The function operation is equivalent to the following pseudoinstructions:   
		\~
		\~
    \code
    	rep N data=[ar0++gr0] with vsum ,shift data,0;
    	rep N [ar6++gr6]=afifo;
    \endcode
    
    \param nb1  
        \ru задает разбиение на колонки (необходимо wtw) 
        \en sets columns partition (wtw is necessary) 
		\~
    \param sb   
        \ru задает разбиение на 8 строк 
        \en sets partition into eight rows 
		\~
    \param woper 
        \ru в рабочей матрице должны быть загружены весовые коэффициенты 
        \en weight coefficients should be loaded to the working mtr 
		\~
    \param ar0  
        \ru указатель на столбец SrcMtr1 
        \en pointer to SrcMtr1 column 
		\~
    \param gr0 SrcMtr1 stride
    
    \param gr5  
        \ru Высота матриц N = [0,1,2...31,32,33,...] 
        \en Height of matrixes N = [0,1,2...31,32,33,...] 
		\~
    \param ar6  
        \ru указатель на столбец DstMtr 
        \en pointer to DstMtr column 
		\~
    \param gr6 DstMtr stride
    
    \restr 
        \ru При выходе из функции изменяется содержимое регистров: ar0,ar6. 
        \en On exiting the function the contents of registers changes: ar0,ar6. 
    */

//! \{ 
 void vec_vsum_shift_data_0(nmreg nb1, nmreg sb, nmreg woper, nmreg ar0, nmreg gr0, nmreg gr5, nmreg ar6, nmreg gr6); 
 //! \}


//-----------------------------------------------------------------------------
    /**
		\~
     \defgroup vec_vsum_shift_data_vr
   \ingroup vsum
   
        \ru Действие функции эквивалентно следующим псевдоинструкциям: 
        \en The function operation is equivalent to the following pseudoinstructions:   
		\~
		\~
    \code
    	rep N data=[ar0++gr0] with vsum ,shift data, vr;
    	rep N [ar6++gr6]=afifo;
    \endcode
    
    \param nb1  
        \ru задает разбиение на колонки (необходимо wtw) 
        \en sets columns partition (wtw is necessary) 
		\~
    \param sb   
        \ru задает разбиение на 8 строк 
        \en sets partition into eight rows 
		\~
    \param woper 
        \ru в рабочей матрице должны быть загружены весовые коэффициенты 
        \en weight coefficients should be loaded to the working mtr 
		\~
    \param vr	
        \ru константа для суммирования 
        \en the constant for summation 
		\~
    \param ar0  
        \ru указатель на столбец SrcMtr1 
        \en pointer to SrcMtr1 column 
		\~
    \param gr0 SrcMtr1 stride
    
     \param gr5  
        \ru Высота матриц N = [0,1,2...31,32,33,...] 
        \en Height of matrixes N = [0,1,2...31,32,33,...] 
		\~
    \param ar6  
        \ru указатель на столбец DstMtr 
        \en pointer to DstMtr column 
		\~
    \param gr6 DstMtr stride
    
    \restr 
        \ru При выходе из функции изменяется содержимое регистров: ar0,ar6. 
        \en On exiting the function the contents of registers changes: ar0,ar6. 
    */

//! \{ 
 void vec_vsum_shift_data_vr(nmreg nb1, nmreg sb, nmreg woper, nmreg vr, nmreg ar0, nmreg gr0, nmreg gr5, nmreg ar6, nmreg gr6); 
 //! \}

//-----------------------------------------------------------------------------
    /**
		\~
     \defgroup vec_vsum_shift_data_afifo
   \ingroup vsum
   
        \ru Действие функции эквивалентно следующим псевдоинструкциям: 
        \en The function operation is equivalent to the following pseudoinstructions:   
		\~
		\~
    \code
    	rep 1   data=vfalse; 
    	rep 1*N data=[ar0++gr0] with vsum , shift data,afifo; (rep1 N times)
    	rep 1   [ar6]=afifo;
    \endcode
    
    \param nb1  
        \ru задает разбиение на колонки (необходимо wtw) 
        \en sets columns partition (wtw is necessary) 
		\~
    \param sb   
        \ru задает разбиение на 8 строк 
        \en sets partition into eight rows 
		\~
    \param f1cr 
        \ru задает функцию активации 
        \en sets activation function 
		\~
    \param woper 
        \ru в рабочей матрице должны быть загружены весовые коэффициенты 
        \en weight coefficients should be loaded to the working mtr 
		\~
    \param ar0  
        \ru указатель на столбец SrcMtr 
        \en pointer to SrcMtr column 
		\~
    \param gr0 SrcMtr stride
    
    \param gr5  
        \ru Высота матриц N = [0,1,2...31,32,33,...] 
        \en Height of matrixes N = [0,1,2...31,32,33,...] 
		\~
    \param ar6  
        \ru указатель на столбец DstMtr 
        \en pointer to DstMtr column 
		\~
    \restr  
        \ru При выходе из функции изменяется содержимое регистров: ar0. 
        \en On exiting the function the contents of registers changes: ar0. 
    */

//! \{ 
 void vec_vsum_shift_data_afifo(nmreg nb1, nmreg sb, nmreg f1cr, nmreg woper, nmreg ar0, nmreg gr0, nmreg gr5, nmreg ar6); 
 //! \}

//-----------------------------------------------------------------------------



	/**
		\~
    \defgroup vec_CompareMinV
	\ingroup vcomplex
	\brief
		\ru Поэлементный поиск минимального 
		\en Elementwise minimum search

		\~
		\ru Действие функции эквивалентно следующим псевдоинструкциям: 
        \en The function operation is equivalent to the following pseudoinstructions:   
		\~
		\~
    \code
		rep N ram=[ar0++gr0]; 
		rep N data=[ar1++gr1] with ram-data;
		rep N                 with activate afifo;
		rep N data=[ar3++gr3] with mask afifo, ram, data;
		rep N [ar6++gr6]=afifo;
    \endcode

	\param nb1
        \ru задает разбиение на колонки (необходимо wtw) 
        \en sets columns partition (wtw is necessary) 
		\~
 	\param f1cr
        \ru задает функцию активации 
        \en sets activation function 
		\~
 	\param ar0
        \ru указатель на столбец SrcMtr1
        \en pointer to SrcMtr1 column 
		\~
	\param gr0 SrcMtr1 stride

	\param ar1,ar3
        \ru указатель на столбец SrcMtr2
        \en pointer to SrcMtr2 column 
		\~
	\param gr1,gr3 SrcMtr2 stride
	
	\param gr5
        \ru Высота матриц N = [0,1,2...31,32,33,...] 
        \en Height of matrixes N = [0,1,2...31,32,33,...] 
		\~
	\param ar6
        \ru указатель на столбец DstMtr 
        \en pointer to DstMtr column 
		\~
	\param gr6 DstMtr stride
    \restr  
        \ru При выходе из функции изменяется содержимое регистров: ar0,ar1,ar3,ar6. 
        \en On exiting the function the contents of registers changes: ar0,ar1,ar3,ar6.  
	*/
//! \{ 
 void vec_CompareMinV(nmreg nb1, nmreg f1cr, nmreg ar0, nmreg gr0, nmreg ar1, nmreg gr1, nmreg ar3, nmreg gr3, nmreg gr5, nmreg ar6, nmreg gr6); 
 //! \}

//-----------------------------------------------------------------------------	
	/**
		\~
    \defgroup vec_CompareMaxV
	\ingroup vcomplex
	\brief
		\ru Поэлементный поиск максимального 
		\en Elementwise maximum search

		\~
		\ru Действие функции эквивалентно следующим псевдоинструкциям: 
        \en The function operation is equivalent to the following pseudoinstructions:   
		\~
		\~
    \code
		rep N ram=[ar0++gr0]; 
		rep N data=[ar1++gr1] with ram-data;
		rep N                 with activate afifo;
		rep N data=[ar3++gr3] with mask afifo, data, ram;
		rep N [ar6++gr6]=afifo;
    \endcode

	\param nb1
        \ru задает разбиение на колонки (необходимо wtw) 
        \en sets columns partition (wtw is necessary) 
		\~
 	\param f1cr
        \ru задает функцию активации 
        \en sets activation function 
		\~
 	\param ar0
        \ru указатель на столбец SrcMtr1
        \en pointer to SrcMtr1 column 
		\~
	\param gr0 SrcMtr1 stride

	\param ar1,ar3
        \ru указатель на столбец SrcMtr2
        \en pointer to SrcMtr2 column 
		\~
	\param gr1,gr3 SrcMtr2 stride
	
	\param gr5
        \ru Высота матриц N = [0,1,2...31,32,33,...] 
        \en Height of matrixes N = [0,1,2...31,32,33,...] 
		\~
	\param ar6
        \ru указатель на столбец DstMtr 
        \en pointer to DstMtr column 
		\~
	\param gr6 DstMtr stride
    \restr  
        \ru При выходе из функции изменяется содержимое регистров: ar0,ar1,ar3,ar6. 
        \en On exiting the function the contents of registers changes: ar0,ar1,ar3,ar6.  
	*/
//! \{ 
 void vec_CompareMaxV(nmreg nb1, nmreg f1cr, nmreg ar0, nmreg gr0, nmreg ar1, nmreg gr1, nmreg ar3, nmreg gr3, nmreg gr5, nmreg ar6, nmreg gr6); 
 //! \}


//-----------------------------------------------------------------------------

	/**
		\~
    \defgroup vec_DupValueInVector8
	\ingroup vcomplex
	\brief
		\ru Размножение 8-ми битового значения по всему вектору.
		\en Dublicate 8 bit value in a vec.

		\~
        \ru Действие функции эквивалентно следующим псевдоинструкциям: 
        \en The function operation is equivalent to the following pseudoinstructions:   
		\~
		\~
    \code
        gr1 = gr1 and 0FFh;
        [ar1] = gr1 + (gr1 << 8) + (gr1 << 16) + (gr1 << 24) +
                (gr1 << 32) + (gr1 << 40) + (gr1 << 48) + (gr1 << 56).
    	ar1 += 2;
    \endcode

	\param ar1
		\ru Адрес 64-х битового вектора.
		\en Address of 64-bit vec.
		\~
	\param gr1
		\ru Значение (8 бит).
		\en Value (8 bits).
		\~
    \restr  
        \ru При выходе из функции изменяется содержимое регистров: ar1, gr1. 
        \en On exiting the function the contents of registers changes: ar1, gr1.  
	*/
//! \{ 
 void vec_DupValueInVector8(nmreg ar1, nmreg gr1); 
 //! \}


//-----------------------------------------------------------------------------

	/**
		\~
    \defgroup vec_DupValueInVector16
	\ingroup vcomplex
	\brief
		\ru Размножение 16-ти битового значения по всему вектору.
		\en Dublicate 16 bit value in a vec.

		\~
        \ru Действие функции эквивалентно следующим псевдоинструкциям: 
        \en The function operation is equivalent to the following pseudoinstructions:   
		\~
		\~
    \code
        gr1 = gr1 and 0FFFFh;
        [ar1] = gr1 + (gr1 << 16) + (gr1 << 32) + (gr1 << 48).
    	ar1 += 2;
    \endcode

	\param ar1
		\ru Адрес 64-х битового вектора.
		\en Address of 64-bit vec.
		\~
	\param gr1
		\ru Значение (8 бит).
		\en Value (8 bits).
		\~
    \restr  
        \ru При выходе из функции изменяется содержимое регистров: ar1, gr1. 
        \en On exiting the function the contents of registers changes: ar1, gr1.  
	*/
//! \{ 
 void vec_DupValueInVector16(nmreg ar1, nmreg gr1); 
 //! \}


//-----------------------------------------------------------------------------

	/**
		\~
    \defgroup vec_BuildDiagWeights8
	\ingroup vcomplex
	\brief
		\ru Построение диагональной матрицы весовых коеффициентов (8x8).
		\en Building of diagonal mtr (8x8).

		\~
	\param ar1
		\ru Адрес 64-х буфера весовых коеффициентов (8x64 бит). 
		\en Address of mtr.
		\~
	\param gr1
		\ru Значение (8 бит).
		\en Value (8 bits).
		\~
    \restr  
        \ru При выходе из функции изменяется содержимое регистров: ar1, gr1.
        \en On exiting the function the contents of registers changes: ar1, gr1.

*/
//! \{ 
 void vec_BuildDiagWeights8(nmreg ar1, nmreg gr1); 
 //! \}


//-----------------------------------------------------------------------------


	/**
		\~
    \defgroup vec_BuildDiagWeights16
	\ingroup vcomplex
	\brief
		\ru Построение диагональной матрицы весовых коеффициентов (16x16).
		\en Building of diagonal mtr (16x16).

		\~
	\param ar1
		\ru Адрес 64-х буфера весовых коеффициентов (4x64 бит). 
		\en Address of mtr.
		\~
	\param gr1
		\ru Значение (16 бит).
		\en Value (16 bits).
		\~
    \restr  
        \ru При выходе из функции изменяется содержимое регистров: ar1, gr1. 
        \en On exiting the function the contents of registers changes: ar1, gr1.  
	*/
//! \{ 
 void vec_BuildDiagWeights16(nmreg ar1, nmreg gr1); 
 //! \}

//-----------------------------------------------------------------------------


	/**
		\~
    \defgroup vec_MaxVal_v8nm8s
	\ingroup vcomplex
	\brief
		\ru Поиск максимума в 8 байтах
		\en Maximum search in 8 bytes

		\~
	\~
	\param ar0
		\ru Адрес 64р. слова
		\en Addres of 64 bit word
		\~
	\retval gr7
		\ru Максимум из  8 байт
		\en Maximim of 8 bytes
		\~
	\restr
		\ru При выходе из функции изменяется содержимое регистров: gr0, gr1, gr2, gr3, ar5, gr5, gr7. 
		\en On exiting the function the contents of registers changes: gr0, gr1, gr2, gr3, ar5, gr5, gr7.  
	*/
//! \{ 
 void vec_MaxVal_v8nm8s(nmreg ar0, nmreg gr7); 
 //! \}

//-----------------------------------------------------------------------------
	/**
		\~
    \defgroup vec_MaxVal_v4nm16s
	\ingroup vcomplex
	\brief
		\ru Поиск максимума в 4-х 16р. элементах
		\en Maximum search in 4 16bit words
		\~
	\~
	\param ar0
		\ru Адрес 64р. слова
		\en Addres of 64 bit word
		\~
	\retval gr7
		\ru Максимум из  8 байт
		\en Maximim of 8 bytes
		\~
	\restr
		\ru При выходе из функции изменяется содержимое регистров: gr0, gr1, gr2, gr3, ar5, gr5, gr7. 
		\en On exiting the function the contents of registers changes: gr0, gr1, gr2, gr3, ar5, gr5, gr7.  
	*/
//! \{ 
 void vec_MaxVal_v4nm16s(nmreg ar0, nmreg gr7); 
 //! \}

//-----------------------------------------------------------------------------



	/**
		\~
    \defgroup vec_MaxVal
	\ingroup vcomplex
	\brief
		\ru Поиск максимумов в колонках матрицы SrcMtr1.  
		\en Maximium search in columns of SrcMtr1 mtr

		\~
	\~
	\param nb1
        \ru задает разбиение на колонки (необходимо wtw) 
        \en sets columns partition (wtw is necessary) 
		\~
 	\param f1cr
        \ru задает функцию активации 
        \en sets activation function 
		\~
 	\param ar0
        \ru указатель на столбец SrcMtr1
        \en pointer to SrcMtr1 column 
		\~
    \param gr0 SrcMtr stride

	\param ar4
		\ru указатель на временный массив размером nm64s[64]
		\en pointer to temporery array with sizr of nm64s[64]
		\~
	\param gr5
        \ru Высота матрицы SrcMtr1 N = [32,64,...] 
        \en Height of mtr SrcMtr1 N = [32,64,...] 
		\~
	\retval ar6
        \ru указатель на 64р. слово результатов (максимумов) 
        \en pointer to 64 bit result word of maximums 
		\~
    \restr  
        \ru При выходе из функции изменяется содержимое регистров: ar0,gr0,ar4,ar3,ar6,gr7. 
        \en On exiting the function the contents of registers changes: ar0,ar1,ar3,ar6,gr7.  

	*/
//! \{ 
 void vec_MaxVal( nmreg nb1, nmreg f1cr, nmreg ar0, nmreg gr0, nmreg ar4, nmreg gr5, nmreg ar6); 
 //! \}

//-----------------------------------------------------------------------------


	/**
		\~
    \defgroup vec_MinVal_v8nm8s
	\ingroup vcomplex
	\brief
		\ru Поиск минимума в 8 байтах
		\en Minimum search in 8 bytes

		\~
	\~
	\param ar0
		\ru Адрес 64р. слова
		\en Addres of 64 bit word
		\~
	\retval gr7
		\ru Максимум из  8 байт
		\en Maximim of 8 bytes
		\~
	\restr
		\ru При выходе из функции изменяется содержимое регистров: gr0, gr1, gr2, gr3, ar5, gr5, gr7. 
		\en On exiting the function the contents of registers changes: gr0, gr1, gr2, gr3, ar5, gr5, gr7.  
	*/
//! \{ 
 void vec_MinVal_v8nm8s(nmreg ar0, nmreg gr7); 
 //! \}

//-----------------------------------------------------------------------------
	/**
		\~
    \defgroup vec_MinVal_v4nm16s
	\ingroup vcomplex
	\brief
		\ru Поиск минимума в 4-х 16р. элементах
		\en Minimum search in 4 16bit words
		\~
	\~
	\param ar0
		\ru Адрес 64р. слова
		\en Addres of 64 bit word
		\~
	\retval gr7
		\ru Максимум из  8 байт
		\en Maximim of 8 bytes
		\~
	\restr
		\ru При выходе из функции изменяется содержимое регистров: gr0, gr1, gr2, gr3, ar5, gr5, gr7. 
		\en On exiting the function the contents of registers changes: gr0, gr1, gr2, gr3, ar5, gr5, gr7.  
	*/
//! \{ 
 void vec_MinVal_v4nm16s(nmreg ar0, nmreg gr7); 
 //! \}

//-----------------------------------------------------------------------------



	/**
		\~
    \defgroup vec_MinVal
	\ingroup vcomplex
	\brief
		\ru Поиск минимумов в колонках матрицы SrcMtr1.  
		\en Maximium search in columns of SrcMtr1 mtr

		\~
	\~
	\param nb1
        \ru задает разбиение на колонки (необходимо wtw) 
        \en sets columns partition (wtw is necessary) 
		\~
 	\param f1cr
        \ru задает функцию активации 
        \en sets activation function 
		\~
 	\param ar0
        \ru указатель на столбец SrcMtr1
        \en pointer to SrcMtr1 column 
		\~
    \param gr0 SrcMtr stride

	\param ar4
		\ru указатель на временный массив размером nm64s[64]
		\en pointer to temporery array with sizr of nm64s[64]
		\~
	\param gr5
        \ru Высота матрицы SrcMtr1 N = [32,64,...] 
        \en Height of mtr SrcMtr1 N = [32,64,...] 
		\~
	\retval ar6
        \ru указатель на 64р. слово результатов (максимумов) 
        \en pointer to 64 bit result word of Minimums 
		\~
    \restr  
        \ru При выходе из функции изменяется содержимое регистров: ar0,gr0,ar4,ar3,ar6,gr7. 
        \en On exiting the function the contents of registers changes: ar0,ar1,ar3,ar6,gr7.  

	*/
//! \{ 
 void vec_MinVal( nmreg nb1, nmreg f1cr, nmreg ar0, nmreg gr0, nmreg ar4, nmreg gr5, nmreg ar6); 
 //! \}


//-----------------------------------------------------------------------------


	/**
		\~
    \defgroup vec_AccMul1D1W32_AddVr
	\ingroup vcomplex
	\brief
		\ru Умножение с накоплением 
		\en Multiplication with accumulation
 
		\~
    \ru Действие функции эквивалентно следующим псевдоинструкциям: 
    \en The function operation is equivalent to the following pseudoinstructions:   
		\~
		\~
    \code

		rep 32 wfifo=[ar4++],ftw,wtw;
		rep 32 wfifo data = [ar0++gr0] with vsum ,data,vr;
		with gr5--;
		with gr5--;
    	<Loop>
			rep 32 wfifo=[ar4++],ftw,wtw;
    		rep 32 data=[ar0++gr0] with vsum ,data,afifo;
		if <>0 goto Loop with gr5--;
		rep 32 [ar6++gr6]=afifo;
    \endcode

	\~
	\param nb1
        \ru задает разбиение на колонки (необходимо wtw) 
        \en sets columns partition (wtw is necessary) 
		\~
    \param sb   
        \ru задает разбиение на 32 строки
        \en sets partition into 32 rows 
		\~
    \param vr	
        \ru константа для суммирования 
        \en the constant for summation 
		\~
 	\param ar0
        \ru указатель на столбец SrcMtr1
        \en pointer to SrcMtr1 column 
		\~
    \param gr0 SrcMtr stride

    \param ar4  
        \ru матрицы весовых коэффициентов 
        \en matrixes of weight coefficients 
		\~
    \param gr4  
        \ru дублирует nb1 
        \en it duplicates nb1 
		\~
	\param gr5
		\ru кол-во итераций умножений с накоплением
		\en number of iteration of multiplication with accumulation
		\~
	\retval ar6
        \ru указатель на столбец DstMtr, сосотоящий из 32 длинных слов
        \en pointer to DstMtr column, consisting of 32 long words;
		\~
	\param gr6 DstMtr stride
	*/
//! \{ 
 void vec_AccMul1D1W32_AddVr(nmreg nb1, nmreg sb, nmreg vr, nmreg ar0, nmreg gr0,  nmreg ar4, nmreg gr4, nmreg gr5, nmreg ar6, nmreg gr6); 
 //! \}




