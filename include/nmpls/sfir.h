//------------------------------------------------------------------------
//
//  $Workfile:: sFiltrat $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2005/01/12 14:09:07 $
//
//! \if file_doc
//!
//! \file   vFilter.h
//! \author Сергей Мушкаев
//! \brief  Определение функций фильтраций для векторов.
//!
//! \endif
//!
//------------------------------------------------------------------------

#ifndef _SFIR_H_INCLUDED_
#define _SFIR_H_INCLUDED_

#include "nmtype.h"

#ifdef __cplusplus
		extern "C" {
#endif


//*****************************************************************************

    /**
	\internal
    \defgroup SIG_Filter SIG_Filter
		\ingroup sFiltration
		\brief 
			\ru Одномерная фильтрация. 
			\en One-dimensional filtration. 

		\~
		\~
    \param	pSrcVec		
        \ru Входной вектор. 
        \en Input vec. 
		\~
    \param	nSize		
        \ru Размер входного вектора в элементах. 
        \en Input vec size in elements. 
		\~
	\retval	pDstVec		
        \ru Результирующий вектор. 
        \en The result vec. 
		\~
	\param	pKernel
        \ru Служебная структура, содержащая весовые коэффиценты фильтра во внутреннем формате. 
        \en Auxilary structure, which contains filter coefficents in internal format. 
	
		\~
    \note \ru Инициализация служебной структуры производится соответствующей функцией SIG_SetFilter() и SIG_CreateFilter().
          \en Initialization of Auxilary structure is performed by call of appropriate SIF_SetFilter function and SIG_CreateFilter().
		\~    
    */
#define NmppsFIRState void

void nmppsFIR_8s16s( nm8s* pSrc, nm16s* pDst, int srcSize,  NmppsFIRState* pState);
int  nmppsFIRInit_8s16s(NmppsFIRState* ppState, int* pTaps, int tapsLen);
int  nmppsFIRInitAlloc_8s16s(NmppsFIRState** ppState, int* pTaps, int tapsLen);
void nmppsFIRFree(NmppsFIRState* pState);

void nmppsFIR_8s( nm8s* pSrc, nm8s* pDst, int srcSize,  NmppsFIRState* pState);
int  nmppsFIRInit_8s(NmppsFIRState* ppState, int* pTaps, int tapsLen);
int  nmppsFIRInitAlloc_8s(NmppsFIRState** ppState, int* pTaps, int tapsLen);
void nmppsFIRFree(NmppsFIRState* pState);

void nmppsFIR_16s32s( nm16s* pSrc, nm32s* pDst, int srcSize,  NmppsFIRState* pState);
int  nmppsFIRInit_16s32s(NmppsFIRState* ppState, int* pTaps, int tapsLen);
int  nmppsFIRInitAlloc_16s32s(NmppsFIRState** ppState, int* pTaps, int tapsLen);


    //! \{
//void SIG_Filter(nm32s* pSrcVec, nm32s* pDstVec, int	nSize,  nm64s* pKernel);
//void SIG_Filter(nm16s* pSrcVec, nm32s* pDstVec, int	nSize,  nm64s* pKernel);
//void nmppsFIR_8s16s( nm8s* pSrcVec, nm32s* pDstVec, int	nSize,  nm64s* pFIRState);
//void SIG_Filter(nm16s* pSrcVec, nm16s* pDstVec, int	nSize,  nm64s* pKernel);
//void SIG_Filter( nm8s* pSrcVec, nm16s* pDstVec, int	nSize,  nm64s* pKernel);
//void SIG_Filter( nm8s* pSrcVec,  nm8s* pDstVec, int	nSize,  nm64s* pKernel);
//    //! \}
//int SIG_GetFilterKernelSize_32s32s(int nSize);	
//int SIG_GetFilterKernelSize_16s16s(int nSize);
//int SIG_GetFilterKernelSize_16s32s(int nSize);
//int SIG_GetFilterKernelSize_8s8s  (int nSize);
//int nmppsFIRGetStateSize_8s16s (int nSize);
//int SIG_GetFilterKernelSize_8s32s (int nSize);
//void nmppsFIRFree(void* state);
//*****************************************************************************

    /**
	\internal
    \defgroup SIG_SetFilter SIG_SetFilter
    \ingroup sFiltration
    \brief
        \ru Инициализация ядра для одномерной фильтрации. 
        \en Initialization of the core for one-dimensional filtration. 
    
		\~
        \ru Функции заполняют таблицу весовых коэффициентов из линейного массива 
        коэффициентов окна преобразования для использования в функциях фильтрации. 
        \en The functions init the table of weight coefficients from the linear array 
        of the conversion window to use in filtration functions. 

		\~
		\~
    \param	pWeights		
        \ru Указатель на коэффциенты фильтра . 
        \en Pointer to the filter coefficients. 
		\~
    \param	nWeights	
        \ru Размер окна фильтра. nWeights=[3,5,7,9....]. 
        \en Size of filter window . 
		\~
	\retval	pKernel	
        \ru Указатель на служебную структуру, содержащую весовые коэффиценты фильтра во внутреннем формате. 
        \en Pointer to auxilary structure, which contains filter coefficents in internal format. 
		\~
	\return
		\ru Размер проинициализированной структуры pKernel в 32р. словах
		\en Size of inited structure pKernel in 32 bit words
		\~
    \note \ru Используется перед вызовом функции SIG_Filter.
          \en This functions is used before call  of SIG_Filter.
		\~    
		*/

    //! \{
//int SIG_SetFilter_32s32s(int* pWeights, int nWeights, nm64s* pKernel);
//int SIG_SetFilter_16s16s(int* pWeights, int nWeights, nm64s* pKernel);
//int SIG_SetFilter_16s32s(int* pWeights, int nWeights, nm64s* pKernel);
//int SIG_SetFilter_8s8s  (int* pWeights, int nWeights, nm64s* pKernel);
int nmppsFIRSetCoeff_8s16s (int* pWeights, int nWeights, nm64s* pKernel);
//int SIG_SetFilter_8s32s (int* pWeights, int nWeights, nm64s* pKernel);
    //! \}


/*!
	\defgroup CSIG_FIR КИХ-фильтрация 
	\ingroup sFiltration	 
	\brief КИХ фильтрация 
*/	
//! \{

//! Класс КИХ фильтра
//! \tparam nmbits_in  Тип указывающий разрядность входного вектора. Допустимые типы : nm8s,nm16s,nm32s
//! \tparam nmbits_out Тип указывающий разрядность выходного вектора. Допустимые типы : nm8s,nm16s,nm32s. Разрядность входного вектора не должна превышать разрядности выходного.
//! \par Пример
//! \include app\example\Filter\SIG_Filter_16s32s\main.cpp 
//template <class nmbits_in, class nmbits_out> class CSIG_FIR
//{
//public:
//	void (*pfFree32)(void*);	///< Указатель на функции освобождения памяти (pKernel)
//	int nWeights;				///< Количество коэффициентов КИХ фильтра 
//	nm64s* pKernel;				///< Указатель на внутреннюю структуру коэффициентов
//	int nKernelSize;			///< Размер памяти необходимый для хранения внутренней структуру коэффициентов
//
//	//! Конструктор КИХ фильтра 
//	/*!
//	   Выделяет область памяти под внутреннюю структуру коэффициентов 
//      \param nWeights  устанавливает количество коэффициентов КИХ фильтра. nWeights=[3,5,7,9....]. 
//      \param malloc32_func  указатель на функцию  выделения динамической памяти 32-разрядными словами.
//	  \param free32_func  указатель на функцию динамического освобождения памяти
//    */
//	CSIG_FIR(int nWeights, void* (*malloc32_func)(unsigned), void (*free32_func)(void*));
//	CSIG_FIR(){pKernel=0;};
//
//	//! Конструктор КИХ фильтра 
//	/*!
//	   Выделяет область памяти под внутреннюю структуру коэффициентов 
//      \param nWeights  устанавливает количество коэффициентов КИХ фильтра. nWeights=[3,5,7,9....]. 
//      \param malloc32_func  указатель на функцию  выделения динамической памяти 32-разрядными словами.
//	  \param free32_func  указатель на функцию динамического освобождения памяти
//    */
//	int init(int nWeights, void* (*malloc32_func)(unsigned), void (*free32_func)(void*));
//
//	
//	//! Загружает коэффициенты фильтра и инициализирует внутреннюю структуру хранения коэффициентов в pKernel
//	/*!
//      \param pWeights  коэффициенты фильтра 
//	  \return указатель на внутреннюю структуру коэффициентов. 0- Если память под структуру не была выделена.  
//    */
//	void* setWeights(int* pWeights);
//	
//	//! Функция одномерной фильтрации
//	/*!
//	\f[
//        pDstVec[i]  =  \sum\limits_{j = 0}^{nWeights-1} {pSrcVec[i-nWeights/2] \cdot pWeights[j]}   ,i=0 \ldots  nSize-1
//    \f]
//
//
//      \param pSrcVec входной вектор 
//	  \param pDstVec выходной вектор 
//	  \param nSize размер вектора в элементах
//	  \warning При вычислении первых и последних nWeights/2 отсчетов производится выход за границы входного массива pSrcVec . 
//	        Для коректного поведения функции необходимо дополнительные резервировать поля размером не менее nWeight/2 нулевых элементов перед началом и в конце массива pSrcVec.
//    */
//	void  filter(nmbits_in* pSrcVec, nmbits_out* pDstVec, int nSize);
//	
//	//! Освобождает динамическую область памяти pKernel
//	~CSIG_FIR();	
//
//};

//! \}


//*****************************************************************************

    /**
	\internal
    \defgroup SIG_CreateFilter SIG_CreateFilter
    \ingroup sFiltration
    \brief
        \ru Создание ядра для одномерной фильтрации. 
        \en Creation of the core for one-dimensional filtration. 
    
		\~
        \ru Функции создают таблицу весовых коэффициентов из линейного массива 
        коэффициентов окна преобразования для использования в функциях фильтрации. 
        \en The functions generate the table of weight coefficients from the linear array 
        of the conversion window to use in filtration functions. 

		\~
		\~
    \param	pWeights		
        \ru Указатель на коэффциенты фильтра . 
        \en Pointer to the filter coefficients. 
		\~
    \param	nSize	
        \ru Размер окна фильтра. nSize=[3,5,7,9....]. 
        \en Size of filter window . 
		\~
    \param	nHint	
        \ru Определяет память(Local или Global) в которой создается служебная структура. nHint=[MEM_LOCAL,MEM_GLOBAL]. 
        \en Set memoty bank (Local or Global) where auxilary structure would be allocated. 
		\~
	\retval	pKernel	
        \ru Указатель на служебную структуру, содержащую весовые коэффиценты фильтра во внутреннем формате. 
        \en Pointer to auxilary structure, which contains filter coefficents in internal format. 

		\~
    \note \ru Используется перед вызовом функции SIG_Filter.
          \en This functions is used before call  of SIG_Filter.
		  \~
    */
    //! \{

//		nm64s* SIG_CreateFilter_32s32s(int* pWeights, int nWeights, void * (*malloc_func)(unsigned) );
//		nm64s* SIG_CreateFilter_16s16s(int* pWeights, int nWeights, void * (*malloc_func)(unsigned) );
//		nm64s* SIG_CreateFilter_16s32s(int* pWeights, int nWeights, void * (*malloc_func)(unsigned) );
//		nm64s* SIG_CreateFilter_8s8s  (int* pWeights, int nWeights, void * (*malloc_func)(unsigned) );
//		nm64s* SIG_CreateFilter_8s16s (int* pWeights, int nWeights, void * (*malloc_func)(unsigned) );
//		nm64s* SIG_CreateFilter_8s32s (int* pWeights, int nWeights, void * (*malloc_func)(unsigned) );
    //! \}




#ifdef __cplusplus
		};
#endif

   
#endif // _SFILTRATION_H_INCLUDED_

