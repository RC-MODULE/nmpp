//------------------------------------------------------------------------
//
//  $Workfile:: nmtype.h              $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:02 $
//
//------------------------------------------------------------------------

//!
//! \file nmtype.h 
//! \ru Файл, содержащий определения типов упакованных данных.
//! \en The file contains definition of packed data type.
//!

#ifndef _NMTYPE_H_INCLUDED2_
#define _NMTYPE_H_INCLUDED2_
 
#define MEM_LOCAL  0
#define MEM_GLOBAL 1
#define HEAP0 0
#define HEAP1 1
#define HEAP2 2
#define HEAP3 3

#ifdef __GNUC__
#define __int64 long long
#endif
// if new compiler
#ifdef __NM6403__
	typedef long INT64;
	typedef unsigned long UINT64;
#endif

// if old compiler
#ifdef NM6403 
	#ifndef __NM6403__
		typedef long __int64;
		typedef long INT64;
		typedef unsigned long UINT64;
	#endif
#endif

// if win32 compiler
#ifndef NM6403 
		typedef __int64 INT64;
		typedef unsigned __int64 UINT64;
#endif




//-----------------------------------------------------------------------------
	/**    
		\~
    \ru NM регистр.
    \en NM registry.
	*/
class nmreg { int nVal; };
//-----------------------------------------------------------------------------

//*****************************************************************************

    /**
		\~
    \if Russian
        \defgroup nmtype1 Типы данных для упакованных 64-х разрядных векторных данных.
    \endif
    \if English
        \defgroup nmtype1 Data types for packed 64-bit word.
    \endif
	\ingroup types
    
    \ru Большинство функций библиотеки получают и возвращают
        массивы упакованных чисел.
        Обращение к элементам 
        данных массивов должно производится с помощью функций 
        доступа к элементам Getval() and Setval().
	\en Most of the library functions receive and return 
		arrays of packed 64-bit words. To access elements 
		of the words use library support functions Setval()
		and Getval().
    */


//-----------------------------------------------------------------------------
	/**
		\~
	\ingroup nmvectype
    \ru Тип характеризует векторные данные как массив одноразрядных чисел. \n Начальный адрес массива должен быть выровнен по границе 64р слова.  \n По умолчанию передаваемый размер в функцию должен быть кратен 64. 
  	\en Type characterizes vec data as array of 1-bit signed numbers.   \n Pointer to this class is always aligned to 64-bit address. \n By default amount of numbers have to be multiple to 64.

		\~
  	\ru Диапазон значений: 
	\en Number range is: 
		\~
	\~	\f$[-1,0]\f$
	*/
class nm1{public: int nVal;};
//-----------------------------------------------------------------------------
    /**
	\ingroup nmvectype
	\ru Тип характеризует векторные данные как массив 2-х разрядных чисел со знаком. \n Начальный адрес массива должен быть выровнен по границе 64р слова.  \n По умолчанию передаваемый размер в функцию должен быть кратен 32. 
  	\en Type characterizes vec data as array of 2-bit signed numbers. \n Pointer to this class is always aligned to 64-bit address. \n By default amount of numbers have to be multiple to 32.

		\~
  	\ru Диапазон значений: 
	\en Number range is: 
		\~
	\~	\f$[-2^1,\ldots,+2^1-1]=[-2,\ldots,+1]\f$
	
	
	*/
class nm2s{public: int nVal;};
//-----------------------------------------------------------------------------    
    /**
	\ingroup nmvectype
	\ru Тип характеризует векторные данные как массив 4-х разрядных чисел со знаком. \n Начальный адрес массива должен быть выровнен по границе 64р слова.  \n По умолчанию передаваемый размер в функцию должен быть кратен 16. 
  	\en Type characterizes vec data as array of 4-bit signed numbers. \n Pointer to this class is always aligned to 64-bit address. \n By default amount of numbers have to be multiple to 16.

		\~
	\ru Диапазон значений: 
	\en Number range is: 
		\~
	\~	\f$[-2^3,\ldots,+2^3-1]=[-8,\ldots,+7]\f$  
*/
class nm4s{public: int nVal;};
//-----------------------------------------------------------------------------
    /**
	\ingroup nmvectype
 	\ru Тип характеризует векторные данные как массив 8-ми разрядных чисел со знаком. \n Начальный адрес массива должен быть выровнен по границе 64р слова.  \n По умолчанию передаваемый размер в функцию должен быть кратен 8. 
  	\en Type characterizes vec data as array of 8-bit signed numbers. \n Pointer to this class is always aligned to 64-bit address. \n By default amount of numbers have to be multiple to 8.

		\~
	\ru Диапазон значений: 
	\en Number range is: 
		\~
	\~	\f$[-2^7,\ldots,+2^7-1]=[-128,\ldots,+127]\f$
	*/
typedef char nm8s;
struct int8x8{
#ifdef __NM__	
	unsigned long items;
#else 
	char item[8];
#endif	
};
//-----------------------------------------------------------------------------
    /**
	\ingroup nmvectype
	\ru Тип характеризует векторные данные как массив 8-ми разрядных чисел со знаком. \n Начальный адрес массива должен быть выровнен по границе 64р слова.  \n По умолчанию передаваемый размер в функцию должен быть кратен 8. 
  	\en Type characterizes vec data as array of 8-bit signed numbers. \n Pointer to this class is always aligned to 64-bit address. \n By default amount of numbers have to be multiple to 8.

		\~
	\ru Диапазон значений: 
	\en Number range is: 
		\~
	\~	\f$[-2^6,\ldots,+2^6-1]=[-64,\ldots,+63]\f$
	*/
typedef char nm8s7b;
struct int7in8x8{
#ifdef __NM__	
	unsigned long items;
#else 
	char item[8];
#endif	
};
//-----------------------------------------------------------------------------
    /**
	\ingroup nmvectype
 	\ru Тип характеризует векторные данные как массив 16-ти разрядных чисел со знаком. \n Начальный адрес массива должен быть выровнен по границе 64р слова.  \n По умолчанию передаваемый размер в функцию должен быть кратен 4. 
  	\en Type characterizes vec data as array of 16-bit signed numbers. \n Pointer to this class is always aligned to 64-bit address. \n By default amount of numbers have to be multiple to 4.

		\~
  	\ru Диапазон значений: 
	\en Number range is: 
		\~
	\~	\f$[-2^{15},\ldots,^+2^{15}-1]\f$.
	*/
typedef short nm16s;
struct int16x4{
#ifdef __NM__	
	unsigned long items;
#else 
	short item[4];
#endif	
};

//-----------------------------------------------------------------------------
    /**
	\ingroup nmvectype
  	\ru Тип характеризует векторные данные как массив 16-ти разрядных чисел со знаком. \n Начальный адрес массива должен быть выровнен по границе 64р слова.  \n По умолчанию передаваемый размер в функцию должен быть кратен 4. 
  	\en Type characterizes vec data as array of 16-bit signed numbers. \n Pointer to this class is always aligned to 64-bit address. \n By default amount of numbers have to be multiple to 4.

		\~
  	\ru Диапазон значений: 
	\en Number range is: 
		\~
	\~ \f$[-2^{14},\ldots,+2^{14}-1]\f$
	*/
typedef short nm16s15b;
struct int15in16x4{
#ifdef __NM__	
	unsigned long items;
#else 
	short item[4];
#endif	
};
//-----------------------------------------------------------------------------
    /**
	\ingroup nmvectype
	\ru Тип характеризует векторные данные как массив 32-ти разрядных чисел со знаком. \n Начальный адрес массива должен быть выровнен по границе 64р слова.  \n По умолчанию передаваемый размер в функцию должен быть кратен 2. 
  	\en Type characterizes vec data as array of 32-bit signed numbers. \n Pointer to this class is always aligned to 64-bit address. \n By default amount of numbers have to be multiple to 2.

		\~
	\ru Диапазон значений: 
	\en Number range is: 
		\~
	\~	\f$[-2^{31},\ldots,+2^{31}-1]\f$.
	*/
typedef int nm32s;
class int32x2{
public:
	unsigned long long data;
	int32x2(){
		data=0;
	}
	int32x2(int item0, int item1){
		set(0,item0);
		set(1,item1);
	}
	int32x2& operator = (unsigned long long value){
		data = value;
		return *this;
	}
	int &lo(){
		return *((int*)&data);
	}
	int &hi(){
		return *(((int*)&data)+1);
	}
	void set(int indx, int value){
		((int*)&data)[indx]=value;
	}
	int get(int indx){
		return ((int*)&data)[indx];
	}
};
//-----------------------------------------------------------------------------
    /**
	\ingroup nmvectype
   \ru Тип характеризует векторные данные как массив 32-ти разрядных чисел со знаком. \n Начальный адрес массива должен быть выровнен по границе 64р слова.  \n По умолчанию передаваемый размер в функцию должен быть кратен 2. 
  	\en Type characterizes vec data as array of 32-bit signed numbers. \n Pointer to this class is always aligned to 64-bit address. \n By default amount of numbers have to be multiple to 2.

		\~
  	\ru Диапазон значений: 
	\en Number range is: 
		\~
	\~	\f$[-2^{30},\ldots,2^{30}-1]\f$.
	*/
typedef int nm32s31b;
struct int31in32x2{
#ifdef __NM__	
	unsigned long items;
#else 
	int item[2];
#endif	
};
//-----------------------------------------------------------------------------
    /**
	\ingroup nmvectype
   \ru Тип характеризует векторные данные как массив 32-ти разрядных чисел со знаком. \n Начальный адрес массива должен быть выровнен по границе 64р слова.  \n По умолчанию передаваемый размер в функцию должен быть кратен 2. 
  	\en Type characterizes vec data as array of 32-bit signed numbers. \n Pointer to this class is always aligned to 64-bit address. \n By default amount of numbers have to be multiple to 2.

		\~
  	\ru Диапазон значений: 
	\en Number range is: 
		\~
	\~	\f$[-2^{29},\ldots,2^{29}-1]\f$.
	*/
typedef int nm32s30b;
struct int30in32x2{
#ifdef __NM__	
	unsigned long items;
#else 
	int item[2];
#endif	
};
//-----------------------------------------------------------------------------
    /**
	\ingroup nmvectype
   \ru Тип характеризует векторные данные как массив 64-х разрядных чисел со знаком. \n Начальный адрес массива должен быть выровнен по границе 64р слова.  \n По умолчанию размер массива произвольный . 
  	\en Type characterizes vec data as array of 64-bit signed numbers. \n Pointer to this class is always aligned to 64-bit address. \n By default amount of numbers may by arbitrary.
	
		\~
  	\ru Диапазон значений: 
	\en Number range is: 
		\~
	\~	\f$[-2^{63},\ldots,^+2^{63}-1]\f$
	*/
//typedef __int64 nm64s;
typedef INT64 nm64s;


//-----------------------------------------------------------------------------
    /**
	\ingroup nmvectype
   	  \ru Тип характеризует векторные данные как массив 64-х разрядных чисел со знаком. \n Начальный адрес массива должен быть выровнен по границе 64р слова.  \n По умолчанию размер массива произвольный . 
  	\en Type characterizes vec data as array of 64-bit signed numbers. \n Pointer to this class is always aligned to 64-bit address. \n By default amount of numbers may by arbitrary.
	
		\~
  	\ru Диапазон значений: 
	\en Number range is: 
		\~
	\~	\f$[-2^{62},\ldots,+2^{62}-1]\f$
	*/
typedef nm64s nm64s63b;
//=============================================================================
	/**
	\ingroup nmvectype
	\ru Тип характеризует векторные данные как массив 2-х разрядных чисел без знака. \n Начальный адрес массива должен быть выровнен по границе 64р слова.  \n По умолчанию передаваемый размер в функцию должен быть кратен 32. 
  	\en Type characterizes vec data as array of 2-bit unsigned numbers. \n Pointer to this class is always aligned to 64-bit address. \n By default amount of numbers have to be multiple to 32.


		\~
  	\ru Диапазон значений: 
	\en Number range is: 
		\~
	\~	\f$[0,\ldots,+2^2-1]=[0,\ldots,3]\f$
	*/
class nm2u{public: int nVal;};
//-----------------------------------------------------------------------------
    /**
	\ingroup nmvectype
	\ru Тип характеризует векторные данные как массив 4-х разрядных чисел без знака. \n Начальный адрес массива должен быть выровнен по границе 64р слова.  \n По умолчанию передаваемый размер в функцию должен быть кратен 16. 
  	\en Type characterizes vec data as array of 4-bit unsigned numbers. \n Pointer to this class is always aligned to 64-bit address. \n By default amount of numbers have to be multiple to 16.

		\~
	\ru Диапазон значений: 
	\en Number range is: 
		\~
	\~	\f$[0,\ldots,+2^4-1]=[0,\ldots,15]\f$
	*/
class nm4u{public: int nVal;};
//-----------------------------------------------------------------------------
    /**
	\ingroup nmvectype
	\ru Тип характеризует векторные данные как массив 8-ми разрядных чисел без знака. \n Начальный адрес массива должен быть выровнен по границе 64р слова.  \n По умолчанию передаваемый размер в функцию должен быть кратен 8. 
  	\en Type characterizes vec data as array of 8-bit unsigned numbers. \n Pointer to this class is always aligned to 64-bit address. \n By default amount of numbers have to be multiple to 8.

		\~
	\ru Диапазон значений: 
	\en Number range is: 
		\~
	\~	\f$[0,\ldots,+2^8-1]=[0,\ldots,255]\f$
	*/
typedef unsigned char nm8u;
//-----------------------------------------------------------------------------

	/**
	\ingroup nmvectype
	\ru Тип характеризует векторные данные как массив 8-ми разрядных чисел без знака. \n Начальный адрес массива должен быть выровнен по границе 64р слова.  \n По умолчанию передаваемый размер в функцию должен быть кратен 8. 
  	\en Type characterizes vec data as array of 8-bit unsigned numbers. \n Pointer to this class is always aligned to 64-bit address. \n By default amount of numbers have to be multiple to 8.

		\~
	\ru Диапазон значений: 
	\en Number range is: 
		\~
	\~	\f$[0,\ldots,+2^7-1]=[0,\ldots,127]\f$
	*/
typedef unsigned char nm8u7b;
//-----------------------------------------------------------------------------
    /**
	\ingroup nmvectype
	\ru Тип характеризует векторные данные как массив 16-ти разрядных чисел без знака. \n Начальный адрес массива должен быть выровнен по границе 64р слова.  \n По умолчанию передаваемый размер в функцию должен быть кратен 4. 
  	\en Type characterizes vec data as array of 16-bit unsigned numbers. \n Pointer to this class is always aligned to 64-bit address. \n By default amount of numbers have to be multiple to 4.

		\~
	\ru Диапазон значений: 
	\en Number range is: 
		\~
	\~	\f$[0,\ldots,2^{16}-1]\f$.
	*/
typedef unsigned short nm16u;
struct uint16x4{
#ifdef __NM__	
	unsigned long items;
#else 
	short item[4];
#endif	
};
//-----------------------------------------------------------------------------
    /**
	\ingroup nmvectype
	\ru Тип характеризует векторные данные как массив 16-ти разрядных чисел без знака. \n Начальный адрес массива должен быть выровнен по границе 64р слова.  \n По умолчанию передаваемый размер в функцию должен быть кратен 4. 
  	\en Type characterizes vec data as array of 16-bit unsigned numbers. \n Pointer to this class is always aligned to 64-bit address. \n By default amount of numbers have to be multiple to 4.

		\~
	\ru Диапазон значений: 
	\en Number range is: 
		\~
	\~	\f$[-2^{14},\ldots,^+2^{14}-1]\f$.
	*/
typedef unsigned short nm16u15b;
struct uint15in16x4{
#ifdef __NM__	
	unsigned long items;
#else 
	unsigned short item[4];
#endif	
};
//-----------------------------------------------------------------------------
    /**
	\ingroup nmvectype

	\ru Тип характеризует векторные данные как массив 32-ти разрядных чисел без знака. \n Начальный адрес массива должен быть выровнен по границе 64р слова.  \n По умолчанию передаваемый размер в функцию должен быть кратен 2. 
  	\en Type characterizes vec data as array of 32-bit unsigned numbers. \n Pointer to this class is always aligned to 64-bit address. \n By default amount of numbers have to be multiple to 2.

		\~
	\ru Диапазон значений
	\en Number range is
		\~
	\~	\f$[0,\ldots,2^{32}-1]\f$.
	*/
typedef unsigned int nm32u;
struct uint32x2{
#ifdef __NM__	
	unsigned long items;
#else 
	unsigned item[2];
#endif	
};
//-----------------------------------------------------------------------------
    /**
	\ingroup nmvectype
	\ru Тип характеризует векторные данные как массив 32-ти разрядных чисел без знака. \n Начальный адрес массива должен быть выровнен по границе 64р слова.  \n По умолчанию передаваемый размер в функцию должен быть кратен 2. 
  	\en Type characterizes vec data as array of 32-bit unsigned numbers. \n Pointer to this class is always aligned to 64-bit address. \n By default amount of numbers have to be multiple to 2.

		\~
	\ru Диапазон значений
	\en Number range is
		\~
	\~	\f$[0,\ldots,2^{31}-1]\f$.
	*/
typedef unsigned int nm32u31b;
//-----------------------------------------------------------------------------
    /**
	\ingroup nmvectype
   \ru Тип характеризует векторные данные как массив 64-х разрядных чисел без знака. \n Начальный адрес массива должен быть выровнен по границе 64р слова.  \n По умолчанию размер массива произвольный . 
  	\en Type characterizes vec data as array of 64-bit unsigned numbers. \n Pointer to this class is always aligned to 64-bit address. \n By default amount of numbers may by arbitrary.

		\~
	\ru Диапазон значений
	\en Number range is
		\~
	\~	\f$[0,\ldots,2^{64}-1]\f$.
	*/
typedef UINT64 nm64u;
//=============================================================================



//=============================================================================
    /**
	\ingroup nmtype
    \ru Тип для 32-разрядных скалярных переменных с ограниченным диапазоном значений.
    \en Type for 32-bit scalar variables with limited value range.

		\~
	\ru Диапазон значений: 
	\en Number range is: 
		\~
	\~	\f$[-1,0]\f$
	*/
typedef int int1b;
//-----------------------------------------------------------------------------
    /**
	\ingroup nmtype
    \ru Тип для 32-разрядных скалярных переменных с ограниченным допустимым диапазоном значений.
    \en Type for 32-bit scalar variables with limited admissible value range.

		\~
	\ru Диапазон значений: 
	\en Number range is: 
		\~
	\~	\f$[-2^1,\ldots,+2^1-1]=[-2,\ldots,+1]\f$
	*/
typedef int int2b;
//-----------------------------------------------------------------------------
    /**
	\ingroup nmtype
    \ru Тип для 32-разрядных скалярных переменных с ограниченным допустимым диапазоном значений.
    \en Type for 32-bit scalar variables with limited admissible value range.

		\~
	\ru Диапазон значений: 
	\en Number range is: 
		\~
	\~	\f$[-2^2,\ldots,+2^2-1]=[-4,\ldots,+3]\f$
	*/
typedef int int3b;
//-----------------------------------------------------------------------------
    /**
	\ingroup nmtype
    \ru Тип для 32-разрядных скалярных переменных с ограниченным допустимым диапазоном значений.
    \en Type for 32-bit scalar variables with limited admissible value range.

		\~
	\ru Диапазон значений: 
	\en Number range is: 
		\~
	\~	\f$[-2^3,\ldots,+2^3-1]=[-8,\ldots,+7]\f$
	*/
typedef int int4b;
//-----------------------------------------------------------------------------
    /**
	\ingroup nmtype
    \ru Тип для 32-разрядных скалярных переменных с ограниченным допустимым диапазоном значений.
    \en Type for 32-bit scalar variables with limited admissible value range.

		\~
	\ru Диапазон значений: 
	\en Number range is: 
		\~
	\~	\f$[-2^6,\ldots,+2^6-1]=[-64,\ldots,+63]\f$
	*/
typedef int int7b;
//-----------------------------------------------------------------------------
    /**
	\ingroup nmtype
    \ru Тип для 32-разрядных скалярных переменных с ограниченным диапазоном значений.
    \en Type for 32-bit scalar variables with limited admissible value range.

		\~
	\ru Диапазон значений: 
	\en Number range is: 
		\~
	\~	\f$[-2^7,\ldots,+2^7-1]=[-128,\ldots,+127]\f$
	*/
typedef int int8b;
//-----------------------------------------------------------------------------
    /**
	\ingroup nmtype
    \ru Тип для 32-разрядных скалярных переменных с ограниченным допустимым диапазоном значений.
    \en Type for 32-bit scalar variables with limited admissible value range.

		\~
	\ru Диапазон значений: 
	\en Number range is: 
		\~
	\~	\f$[-2^{14},\ldots,+2^{14}-1]\f$
	*/
typedef int int15b;
//-----------------------------------------------------------------------------
    /**
	\ingroup nmtype
    \ru Тип для 32-разрядных скалярных переменных с ограниченным допустимым диапазоном значений.
    \en Type for 32-bit scalar variables with limited admissible value range.

		\~
	\ru Диапазон значений: 
	\en Number range is: 
		\~
	\~	\f$[-2^{15},\ldots,+2^{15}-1]\f$
	*/
typedef int int16b;
//-----------------------------------------------------------------------------
    /**
	\ingroup nmtype
    \ru Тип для 32-разрядных скалярных переменных с ограниченным допустимым диапазоном значений.
    \en Type for 32-bit scalar variables with limited admissible value range.

		\~
	\ru Диапазон значений: 
	\en Number range is: 
		\~
	\~	\f$[-2^{29},\ldots,+2^{29}-1]\f$
	*/
typedef int int30b;
//-----------------------------------------------------------------------------
    /**
	\ingroup nmtype
    \ru Тип для 32-разрядных скалярных переменных с ограниченным допустимым диапазоном значений.
    \en Type for 32-bit scalar variables with limited admissible value range.

		\~
	\ru Диапазон значений: 
	\en Number range is: 
		\~
	\~	\f$[-2^{30},\ldots,+2^{30}-1]\f$
	*/
typedef int int31b;
//-----------------------------------------------------------------------------
    /**
	\ingroup nmtype
    \ru Тип для 32-разрядных скалярных переменных с ограниченным допустимым диапазоном значений.
    \en Type for 32-bit scalar variables with limited admissible value range.

		\~
	\ru Диапазон значений: 
	\en Number range is: 
		\~
	\~	\f$[-2^{31},\ldots,+2^{31}-1]\f$
	*/
typedef int int32b;
//-----------------------------------------------------------------------------
    /**
	\ingroup nmtype
    \ru Тип для 64-разрядных скалярных переменных с ограниченным допустимым диапазоном значений.
    \en Type for 64-bit scalar variables with limited admissible value range.

		\~
	\ru Диапазон значений: 
	\en Number range is: 
		\~
	\~	\f$[-2^{62},\ldots,+2^{62}-1]\f$
	*/
typedef INT64 int63b;
//-----------------------------------------------------------------------------
    /**
	\ingroup nmtype
    \ru Тип для 64-разрядных скалярных переменных с ограниченным допустимым диапазоном значений.
    \en Type for 64-bit scalar variables with limited admissible value range.

		\~
	\ru Диапазон значений: 
	\en Number range is: 
		\~
	\~	\f$[-2^{63},\ldots,+2^{63}-1]\f$
	*/
typedef INT64 int64b;
//=============================================================================
    /**
	\ingroup nmtype
    \ru Тип для 32-разрядных скалярных переменных с ограниченным допустимым диапазоном значений.
    \en Type for 32-bit scalar variables with limited admissible value range.

		\~
	\ru Диапазон значений: 
	\en Number range is: 
		\~
	\~	\f$[0,1]=[0,1]\f$
	*/
typedef unsigned int uint1b;
//-----------------------------------------------------------------------------
    /**
	\ingroup nmtype
    \ru Тип для 32-разрядных скалярных переменных с ограниченным допустимым диапазоном значений.
    \en Type for 32-bit scalar variables with limited admissible value range.

		\~
	\ru Диапазон значений: 
	\en Number range is: 
		\~
	\~	\f$[0,\ldots,2^2-1]=[0,\ldots,3]\f$
	*/
typedef unsigned int uint2b;
//-----------------------------------------------------------------------------
    /**
	\ingroup nmtype
    \ru Тип для 32-разрядных скалярных переменных с ограниченным допустимым диапазоном значений.
    \en Type for 32-bit scalar variables with limited admissible value range.

		\~
	\ru Диапазон значений: 
	\en Number range is: 
		\~
	\~	\f$[0,\ldots,2^3-1]=[0,\ldots,7]\f$
	*/
typedef unsigned int uint3b;
//-----------------------------------------------------------------------------
    /**
	\ingroup nmtype
    \ru Тип для 32-разрядных скалярных переменных с ограниченным допустимым диапазоном значений.
    \en Type for 32-bit scalar variables with limited admissible value range.

		\~
	\ru Диапазон значений: 
	\en Number range is: 
		\~
	\~	\f$[0,\ldots,2^4-1]=[0,\ldots,15]\f$
	*/
typedef unsigned int uint4b;
//-----------------------------------------------------------------------------
    /**
	\ingroup nmtype
    \ru Тип для 32-разрядных скалярных переменных с ограниченным допустимым диапазоном значений.
    \en Type for 32-bit scalar variables with limited admissible value range.

		\~
	\ru Диапазон значений: 
	\en Number range is: 
		\~
	\~	\f$[0,\ldots,2^7-1]=[0,\ldots,127]\f$
	*/
typedef unsigned int uint7b;
//-----------------------------------------------------------------------------
    /**
	\ingroup nmtype
    \ru Тип для 32-разрядных скалярных переменных с ограниченным допустимым диапазоном значений.
    \en Type for 32-bit scalar variables with limited admissible value range.

		\~
	\ru Диапазон значений: 
	\en Number range is: 
		\~
	\~	\f$[0,\ldots,2^8-1]=[0,\ldots,255]\f$
	*/
typedef unsigned int uint8b;
//-----------------------------------------------------------------------------
    /**
	\ingroup nmtype
    \ru Тип для 32-разрядных скалярных переменных с ограниченным допустимым диапазоном значений.
    \en Type for 32-bit sclars with limited admissible value range.

		\~
	\ru Диапазон значений: 
	\en Number range is: 
		\~
	\~	\f$[0,\ldots,2^{15}-1]\f$
	*/
typedef unsigned int uint15b;
//-----------------------------------------------------------------------------
    /**
	\ingroup nmtype
    \ru Тип для 32-разрядных скалярных переменных с ограниченным допустимым диапазоном значений.
    \en Type for 32-bit scalar variables with limited admissible value range.

		\~
	\ru Диапазон значений: 
	\en Number range is: 
		\~
	\~	\f$[0,\ldots,2^{16}-1]\f$
	*/
typedef unsigned int uint16b;
//-----------------------------------------------------------------------------
    /**
	\ingroup nmtype
    \ru Тип для 32-разрядных скалярных переменных с ограниченным допустимым диапазоном значений.
    \en Type for 32-bit scalar variables with limited admissible value range.

		\~
	\ru Диапазон значений: 
	\en Number range is: 
		\~
	\~	\f$[0,\ldots,2^{31}-1]\f$
	*/
typedef unsigned int uint31b;
//-----------------------------------------------------------------------------
    /**
	\ingroup nmtype
    \ru Тип для 32-разрядных скалярных переменных с ограниченным допустимым диапазоном значений.
    \en Type for 32-bit scalar variables with limited admissible value range.

		\~
	\ru Диапазон значений: 
	\en Number range is: 
		\~
	\~	\f$[0,\ldots,2^{32}-1]\f$
	*/
typedef unsigned int uint32b;
//-----------------------------------------------------------------------------
    /**
	\ingroup nmtype
    \ru Тип для 64-разрядных скалярных переменных с ограниченным допустимым диапазоном значений.
    \en Type for 64-bit scalar variables with limited admissible value range.

		\~
	\ru Диапазон значений: 
	\en Number range is: 
		\~
	\~	\f$[0,\ldots,2^{63}-1]\f$
	*/
typedef UINT64 uint63b;
//-----------------------------------------------------------------------------
    /**
	\ingroup nmtype
    \ru Тип для 64-разрядных скалярных переменных с ограниченным допустимым диапазоном значений.
    \en Type for 64-bit scalar variables with limited admissible value range.

		\~
	\ru Диапазон значений: 
	\en Number range is: 
		\~
	\~	\f$[0,\ldots,2^{64}-1]\f$
	*/
typedef nm64u uint64b;


//=============================================================================

//================= nmget ===========================================    
inline int2b	nmget(nm2s*  pVec, int nIndex)
{
	nm32u nBase=(nm32u(nIndex))/16;
	nm32u nDisp=(nm32u(nIndex))%16;
	nm32s nVal=((nm32s*)pVec)[nBase];
	nDisp<<=1;
	nVal<<=(32-2-nDisp);
	nVal>>=30;
	return nVal;
}

inline int4b nmget(nm4s*  pVec, int nIndex)
{
	nm32u nBase=(nm32u(nIndex))/8;
	nm32u nDisp=(nm32u(nIndex))%8;
	nm32s nVal=((nm32s*)pVec)[nBase];
	nDisp<<=2;
	nVal<<=(32-4-nDisp);
	nVal>>=28;
	return nVal;
}

inline int8b	nmget(nm8s*  pVec, int nIndex)
{
	return pVec[nIndex];
}

inline int16b	nmget(nm16s* pVec, int nIndex)
{
	return pVec[nIndex];
}

//---------------- uint ------------------------------------ 
inline uint1b nmget(nm1*   pVec, int nIndex)
{
	nm32u nBase=(nm32u(nIndex))/32;
	nm32u nDisp=(nm32u(nIndex))%32;
	nm32u nVal=((nm32u*)pVec)[nBase];
	nVal>>=nDisp;
	nVal&=1;
	return nVal;
}
inline uint2b	nmget(nm2u*  pVec, int nIndex)
{
	nm32u nBase=(nm32u(nIndex))/16;
	nm32u nDisp=(nm32u(nIndex))%16;
	nm32u nVal=((nm32u*)pVec)[nBase];
	nVal>>=nDisp*2;
	nVal&=3;
	return nVal;
}


inline uint4b	nmget(nm4u*  pVec, int nIndex)
{
	nm32u nBase=(nm32u(nIndex))/8;
	nm32u nDisp=(nm32u(nIndex))%8;
	nm32u nVal=((nm32u*)pVec)[nBase];
	nVal>>=nDisp*4;
	nVal&=15;
	return nVal;
}

inline uint8b	nmget(nm8u*  pVec, int nIndex)
{
	return pVec[nIndex];
}

inline uint16b	nmget(nm16u* pVec, int nIndex)
{
	return pVec[nIndex];
}


//=============================================================================
#define VEC_NM1(X)  nm32u data[(X)/32];  
#define VEC_NM2U(X) nm32u data[(X)/16];
#define VEC_NM2S(X) nm32s data[(X)/16];
#define VEC_NM4U(X) \
	nm32u data[(X)/8]; \
	uint4b get(int nIndex){return nmget((nm4u*)data,nIndex); }\
	uint4b operator[] (int index){ return nmget((nm4u*)data,index);}


#define VEC_NM4S(X) nm32s data[(X)/8]; 
#define VEC_NM8U(X) nm32u data[(X)/4]; 
#define VEC_NM8S(X) \
	nm32s data[(X)/4]; \
	void set(int i, int val){ ((nm8s*)data)[i]=val;}		\
	nm8s operator[] (int index){ return ((nm8s*)data)[index];}

#define VEC_NM16U(X) \
	nm32u data[(X)/2]; \
	void set(int i, int val){ ((nm16u*)data)[i]=val;}		\
	nm16u operator[] (int index){ return ((nm16u*)data)[index];}

#define VEC_NM16S(X) \
	nm32s data[(X)/2]; \
	void set(int i, int val){ ((nm16s*)data)[i]=val;}		\
	nm16s operator[] (int index){ return ((nm16s*)data)[index];}

#define VEC_NM32U(X) nm32u data[(X)];  
#define VEC_NM32S(X) \
	nm32s data[(X)];  \
	void set(int i, int val){ ((nm32s*)data)[i]=val;}		\
	nm32s operator[] (int index){ return ((nm32s*)data)[index];}




//-----------------------------------------------------------------------------
    /**
	\ingroup nmvectype
    \ru Тип векторной структуры, состоящей из 16-ти 4-р. чисел со знаком. 
    \en Type of vec structure consisting of 16 4-bit sigened words.
	*/
struct v16nm4s {VEC_NM4S(16)};

//-----------------------------------------------------------------------------
    /**
		\~
	\ingroup nmvectype
    \ru Тип векторной структуры, состоящей из 4-х 8р. чисел со знаком. 
    \en Type of vec structure consisting of 4 8-bit sigened words.
	*/
struct v4nm8s {VEC_NM8S(4)};
//-----------------------------------------------------------------------------
    /**
		\~
	\ingroup nmvectype
    \ru Тип векторной структуры, состоящей из 8-ми 8р. чисел со знаком. 
    \en Type of vec structure consisting of 8 8-bit sigened words.
	*/
struct v8nm8s {VEC_NM8S(8)};
//-----------------------------------------------------------------------------
    /**
		\~
	\ingroup nmvectype
    \ru Тип векторной структуры, состоящей из 16-ти 8р. чисел со знаком. 
    \en Type of vec structure consisting of 16 8-bit sigened words.
	*/
struct v16nm8s {VEC_NM8S(16)};
//-----------------------------------------------------------------------------
    /**
		\~
	\ingroup nmvectype
    \ru Тип векторной структуры, состоящей из 4-х 16р. чисел со знаком. 
    \en Type of vec structure consisting of 4 16-bit sigened words.
	*/
struct  v4nm16s {VEC_NM16S(4)};


//-----------------------------------------------------------------------------
    /**
		\~
	\ingroup nmvectype
    \ru Тип векторной структуры, состоящей из 8-ми 16р. чисел со знаком. 
    \en Type of vec structure consisting of 8 16-bit sigened words.
	*/
struct v8nm16s {VEC_NM16S(8)};
//-----------------------------------------------------------------------------
    /**
		\~
	\ingroup nmvectype
    \ru Тип векторной структуры, состоящей из 16-ти 16р. чисел со знаком. 
    \en Type of vec structure consisting of 16 16-bit sigened words.
	*/
struct v16nm16s {VEC_NM16S(16)};
//struct v16nm16s 
//-----------------------------------------------------------------------------
    /**
		\~
	\ingroup nmvectype
    \ru Тип векторной структуры, состоящей из 2-х 32р. чисел со знаком. 
    \en Type of vec structure consisting of 2 32-bit sigened words.
	*/
struct v2nm32s {VEC_NM32S(2)};
//-----------------------------------------------------------------------------
    /**
		\~
	\ingroup nmvectype
    \ru Тип векторной структуры, состоящей из 4-х 32р. чисел со знаком. 
    \en Type of vec structure consisting of 4 32-bit sigened words.
	*/
struct v4nm32s {VEC_NM32S(4)};
//-----------------------------------------------------------------------------
    /**
		\~
	\ingroup nmvectype
    \ru Тип векторной структуры, состоящей из 8-ми 32р. чисел со знаком. 
    \en Type of vec structure consisting of 8 32-bit sigened words.
	*/
struct v8nm32s {VEC_NM32S(8)	};
//-----------------------------------------------------------------------------
    /**
		\~
	\ingroup nmvectype
    \ru Тип векторной структуры, состоящей из 16-ти 32р. чисел со знаком. 
    \en Type of {VECtor structure consisting of 16 32-bit sigened words.
	*/
struct v16nm32s {VEC_NM32S(16)	};
//-----------------------------------------------------------------------------
    /**
		\~
	\ingroup nmvectype
    \ru Тип векторной структуры, состоящей из 16-ти 32р. чисел со знаком. 
    \en Type of {VECtor structure consisting of 16 32-bit sigened words.

		\~
	\ru Диапазон значений элементов структуры: 
	\en Number range of structure elements is: 
		\~
	\~	\f$[-64,\ldots,+63]\f$
	*/
typedef v16nm8s v16nm8s7b;

//=============================================================================

//-----------------------------------------------------------------------------
    /**
	\ingroup nmvectype
    \ru Тип векторной структуры, состоящей из 16-ти 4-р. чисел без знака. 
    \en Type of {VECtor structure consisting of 16 4-bit unsigened words.
	*/
struct v16nm4u {VEC_NM4U(16)	};
//-----------------------------------------------------------------------------
    /**
		\~
	\ingroup nmvectype
    \ru Тип векторной структуры, состоящей из 4-х 8р. чисел без знака. 
    \en Type of {VECtor structure consisting of 4 8-bit unsigened words.
	*/
struct v4nm8u {VEC_NM8U(4)		};
//-----------------------------------------------------------------------------
    /**
		\~
	\ingroup nmvectype
    \ru Тип векторной структуры, состоящей из 8-ми 8р. чисел без знака. 
    \en Type of {VECtor structure consisting of 8 8-bit unsigened words.
	*/
struct v8nm8u {VEC_NM8U(8)		};
//-----------------------------------------------------------------------------
    /**
		\~
	\ingroup nmvectype
    \ru Тип векторной структуры, состоящей из 16-ти 8р. чисел без знака. 
    \en Type of {VECtor structure consisting of 16 8-bit unsigened words.
	*/
struct v16nm8u {VEC_NM8U(16)	};
//-----------------------------------------------------------------------------
    /**
		\~
	\ingroup nmvectype
    \ru Тип векторной структуры, состоящей из 4-х 16р. чисел без знака. 
    \en Type of {VECtor structure consisting of 4 16-bit unsigened words.
	*/
struct v4nm16u {VEC_NM16U(4)	};
//-----------------------------------------------------------------------------
    /**
		\~
	\ingroup nmvectype
    \ru Тип векторной структуры, состоящей из 8-ми 16р. чисел без знака. 
    \en Type of {VECtor structure consisting of 8 16-bit unsigened words.
	*/
struct v8nm16u {VEC_NM16U(8)	};
//-----------------------------------------------------------------------------
    /**
		\~
	\ingroup nmvectype
    \ru Тип векторной структуры, состоящей из 16-ти 16р. чисел без знака. 
    \en Type of {VECtor structure consisting of 16 16-bit unsigened words.
	*/
struct v16nm16u {VEC_NM16U(16)	};
//-----------------------------------------------------------------------------
    /**
		\~
	\ingroup nmvectype
    \ru Тип векторной структуры, состоящей из 2-х 32р. чисел без знака. 
    \en Type of {VECtor structure consisting of 2 32-bit unsigened words.
	*/
struct v2nm32u {VEC_NM32U(2)	};
//-----------------------------------------------------------------------------
    /**
		\~
	\ingroup nmvectype
    \ru Тип векторной структуры, состоящей из 4-х 32р. чисел без знака. 
    \en Type of {VECtor structure consisting of 4 32-bit unsigened words.
	*/
struct v4nm32u {VEC_NM32U(4)	};
//-----------------------------------------------------------------------------
    /**
		\~
	\ingroup nmvectype
    \ru Тип векторной структуры, состоящей из 8-ми 32р. чисел без знака. 
    \en Type of {VECtor structure consisting of 8 32-bit unsigened words.
	*/
struct v8nm32u {VEC_NM32U(8)	};
//-----------------------------------------------------------------------------
    /**
		\~
	\ingroup nmvectype
    \ru Тип векторной структуры, состоящей из 16-ти 32р. чисел без знака. 
    \en Type of {VECtor structure consisting of 16 32-bit unsigened words.
	*/
struct v16nm32u {VEC_NM32U(16)	};
//-----------------------------------------------------------------------------

    /**
		\~
	\ingroup nmvectype
    \ru Тип векторной структуры, состоящей из 16-ти 32р. чисел со знаком. 
    \en Type of vec structure consisting of 16 32-bit sigened words.

		\~
	\ru Диапазон значений элементов структуры: 
	\en Number range of structure elements is: 
		\~
	\~	\f$[0,\ldots,7]\f$
	*/
typedef v16nm4u v16nm4b3u;
//=============================================================================
//-----------------------------------------------------------------------------
	/**
	\internal
	\ingroup nmvectype
    \ru Тип для пары 64-х битных векторных данных, соответствующих вещественной и мнимой
		части одного комплексного каждое из которых состоит
		из четырех упакованных 16-х битовые комплексные знаковые числа 
        с диапазоном значений \f$[-2^{15},\ldots,^+2^{15}-1]\f$. 
    \en Packed 16-bit complex signed numbers with
		\~
       \f$[-2^{15},\ldots,^+2^{15}-1]\f$ value range.

	\ru Диапазон значений [-128,\ldots,127]. 
	\en Number range is [-128,\ldots,127].
	*/
class nm16sc
{
public:
	nm16s r;
	nm16s c;
	
	nm16sc() : r(0), c(0) {}
	nm16sc(nm16s b) : r(b), c(0) {}
};
//-----------------------------------------------------------------------------
	/**
	\internal
	\ingroup nmvectype
    \ru Тип для пары 64-х разрядных векторных данных, содержащих упакованные вещественные и 
		мнимые части 2-х комплексных чисел.
    \en Type for pair of 64-bit words with packed real and imaginary parts of
		two complex numbers.

		\~
	\ru Диапазон значений для вещественных и мнимых частей комплексного числа
	\en Number range for real and imaginary parts of complex number is
		\~
	\~	\f$[-2^{31},\ldots,^+2^{31}-1]\f$
	*/
class nm32sc
{
public:
	nm32s re;
	nm32s im;
	
	nm32sc() : re(0), im(0) {}
	nm32sc(nm32s b) : re(b), im(0) {}
};

//-----------------------------------------------------------------------------

	/**
	\internal
	\ingroup nmvectype
    \ru Тип для пары 64-х разрядных векторных данных, содержащих вещественную и мнтмую часть 
		комплексного числа.
    \en Type for pair of 64-bit words with real and imaginary parts of complex number.
		\~
       \f$[-2^{63},\ldots,^+2^{63}-1]\f$ value range.

	\ru Диапазон значений для вещественной и мнимой части
	\en Number range is for real and imaginary parts is 
		\~
	\~ \f$[-2^{63},\ldots,+2^{63}-1]\f$.
	*/
class nm64sc
{
public:
		//!
		//! \ru Вещественная часть комплексоного числа.
		//! \en Real part of complex number.
		//! \~
	nm64s re;

		//!
		//! \ru Мнимая часть комплексного числа.
		//! \en Imaginary part of complex number.
		//! \~
	nm64s im;
	
	nm64sc() : re(0), im(0) {}
	nm64sc(nm64s b) : re(b), im(0) {}

	int Print();
};


inline int NM_CAPACITY(nm1*)  {return 64;}

inline int NM_CAPACITY(nm2s*)  {return 32;}
inline int NM_CAPACITY(nm4s*)  {return 16;}
inline int NM_CAPACITY(nm8s*)  {return 8;}
inline int NM_CAPACITY(nm16s*) {return 4;}
inline int NM_CAPACITY(nm32s*) {return 2;}
inline int NM_CAPACITY(nm64s*) {return 1;}

inline int NM_CAPACITY(nm2u*)  {return 32;}
inline int NM_CAPACITY(nm4u*)  {return 16;}
inline int NM_CAPACITY(nm8u*)  {return 8;}
inline int NM_CAPACITY(nm16u*) {return 4;}
inline int NM_CAPACITY(nm32u*) {return 2;}
inline int NM_CAPACITY(nm64u*) {return 1;}

#define CAPACITY_nm64s 1
#define CAPACITY_nm32s 2
#define CAPACITY_nm16s 4
#define CAPACITY_nm8s 8
#define CAPACITY_nm4s 16
#define CAPACITY_nm2s 32
#define CAPACITY_nm1 64



#endif

 // _NMTYPE_H_INCLUDED_


