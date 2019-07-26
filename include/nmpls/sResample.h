//------------------------------------------------------------------------
//
//  $Workfile:: sResampl $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2005/01/12 14:09:07 $
//
//! \if file_doc
//!
//! \file   vResize.h
//! \author Сергей Мушкаев
//! \brief  Определение функций изменения размера для векторов.
//!
//! \endif
//!
//------------------------------------------------------------------------
#include "nmtype.h"
#ifndef _S_RESAMPLE_H_INCLUDED_
#define _S_RESAMPLE_H_INCLUDED_

#ifdef __cplusplus
		extern "C" {
#endif


    /**
    \defgroup nmppsResampleDown2 nmppsResampleDown2
    \ingroup sResample
    \brief
        \ru Уменьшение числа отсчетов в двое. 
        \en Reduction sample count by factor 2. 
    
		\~
    
	\f[
        pDstVec  = \frac{1}{2} \left( pSrcVec(2*x) + pSrcVec(2*x+1) \right)
    \f]
    
    \param	pSrcVec		
        \ru Входной сигнал. 
        \en Source signal data. 
		\~
     \param	nSize		
        \ru Размер массива входных данных. 
        \en Source data array size. 
		\~
    \retval	pDstVec		
        \ru Результирующий сигнал. 
        \en Destination signal. 
		\~
    \note \ru Для того чтобы избежать переполнения при усреднении,
              динамический диапазон исходного изображения должен
              принадлежать диапазону, определенному типом. 
          \en To avoid data overflow dynamic range of source
              image should be in interval defined by type. 
    
		\~        
     
    */

    //! \{
void nmppsResampleDown2_8u8u(nm8u7b* pSrcVec, nm8u7b* pDstVec, int nSrcVecSize, nm64s* pKernel);
void nmppsResampleDown2_16u16u(nm16u15b* pSrcVec, nm16u15b* pDstVec, int nSrcVecSize, nm64s* pKernel);
    //! \}

//\param	pTmpBuf		
//    \ru Временный буффер размера 2*nSize. 
//    \en Temporary buffer with size 2*nSize. 

//void nmppsResampleDown2(nm8u* pSrcVec, nm16u* pDstVec, int nSrcVecSize, nm64s* pKernel, void* pTmpBuf);
void nmppsResampleDown2_8u16u(nm8u* pSrcVec,nm16u*	pDstVec,void*	pTmpBuf,int	nSize);

//*****************************************************************************

    /**
		\~
    \defgroup nmppsResampleUp3Down2 nmppsResampleUp3Down2
    \ingroup sResample
    \brief
        \ru Передискретизации сигнала в 3/2 раза 
        \en Signal resampling by 3/2 times 
		\~
    \ru Передискретизации сигнала осуществляется методом Polyphase: \n
	    - Между отсчетами входного сигнала вставляется по 2 нуля 
	    - Полученный сигнал пропускается через фильтр ФНЧ. Длина фильтра 17 
	    - Из полученного сигнала выбирается каждый 2 отсчет 
    \en Signal is resampled using the Polyphase method: \n
	    - Two zeros are inserted between input signal countings
	    - The received signal passes through a low-pass filter. The filter length is 17
	    - Every second counting is selected from the received signal 
	
		\~
	\~
    \param pSrcVec		
        \ru Входной вектор. Элементы вектора - целые числа со знаком. 
        \en Input vec. Vector elements are integer number with sign. 
		\~
    \param nSrcVecSize	
        \ru Размер входного вектора. 
        \en Input vec size. 
		\~
    \retval pDstVec	    
        \ru Результирующий вектор. Элементы вектора возвращаются в формате fixed-point: [12.4] (целая часть-12 бит, дробная -4бита)
        \en The result vec. Vector elemts returns in fixed-point format: [12.4] (integer part -12 bits, fractional part - 4 bits)
		\~
    \return \e void 
    
    */
    //! \{
void nmppsResampleUp3Down2_8s16s(nm8s* pSrcVec, nm16s* pDstVec, int nSrcVecSize, nm64s* pKernel);
    //! \}
//*****************************************************************************

    /**
    \defgroup nmppsCreateResample nmppsCreateResample
    \ingroup sResample
    \brief
        \ru Создание ядра для функции передискретизации nmppsResample(). 
        \en Creation of the core for resampling function nmppsResample(). 
    
		\~
        \ru Функции выделяют память и инициализируют таблицы весовых коэффициентов для использования в функциях передискретизации. 
        \en The functions allcates the memoty and initialize the tables of weight coefficients to use in resample functions. 

		\~
		\~
    \param	nHint	
        \ru Определяет память(Local или Global) в которой создается служебная структура. nHint=[MEM_LOCAL,MEM_GLOBAL]. 
        \en Set memoty bank (Local or Global) where auxilary structure would be allocated. 
		\~
	\retval	pKernel	
        \ru Указатель на служебную структуру, содержащую весовые коэффиценты фильтра во внутреннем формате. 
        \en Pointer to auxilary structure, which contains filter coefficents in internal format. 

		\~
    \note \ru Используется перед вызовом функции nmppsFilter.
          \en This functions is used before call  of nmppsFilter.
		  \~
    */

    //! \{
void nmppsCreateResampleUp3Down2_8s16s(nm64s** pKernel, int nHint);
void nmppsCreateResampleDown2_8u8u(nm64s** pKernel, int nHint);
void nmppsCreateResampleDown2_16u16u(nm64s** pKernel, int nHint);
    //! \}

//*****************************************************************************

    /**
    \defgroup nmppsSetResample nmppsSetResample
    \ingroup sResample
    \brief
        \ru Создание ядра для функции передискретизации nmppsResample(). 
        \en Creation of the core for resampling function nmppsResample(). 
    
		\~
        \ru Функции инициализируют таблицы весовых коэффициентов для использования в функциях передискретизации. 
        \en The initialize the tables of weight coefficients to use in resample functions. 

		\~
		\~
 	\param	pKernel	
        \ru Указатель на служебную структуру, содержащую весовые коэффиценты фильтра во внутреннем формате. 
        \en Pointer to auxilary structure, which contains filter coefficents in internal format. 
		\~
	\return
		\ru Размер проинициализированной структуры pKernel в 32р. словах
		\en Size of inited structure pKernel in 32 bit words
		\~
    \note \ru Используется перед вызовом функции nmppsFilter.
          \en This functions is used before call  of nmppsFilter.

		\~
    \note \ru Используется перед вызовом функции nmppsResample().
          \en This functions is used before call  of nmppsResample().
		\~ 
		*/

    //! \{
int nmppsSetResampleUp3Down2_8s16s(nm64s* pKernel);
int nmppsSetResampleDown2_8u8u(nm64s* pKernel);
int nmppsSetResampleDown2_16u16u(nm64s* pKernel);
    //! \}


//*****************************************************************************

     /**
    \internal
    \defgroup nmppsDecimate16 nmppsDecimate16
		\ingroup sResample
    */
    //! \{
void nmppsDecimate16_8s(nm8s* pSrcVec,nm8s* pDstVec,int nDstSize);
void nmppsDecimate16_16s(nm16s* pSrcVec,nm16s* pDstVec,int nDstSize);
void nmppsDecimate16_32s(nm32s* pSrcVec,nm32s* pDstVec,int nDstSize);
void nmppsDecimate16_64s(nm64s* pSrcVec,nm64s* pDstVec,int nDstSize);
    //! \}


//*****************************************************************************

    /**
    \defgroup nmppsResample_perf nmppsResample_perf
		\ingroup sResample
		\brief 
			\ru Функции для оценки производительности функций фильтрации nmppsResample()
			\en Functions for performance estimation of nmppsFilter() functions . 
		
		\~
		\ru Функция  эквивалентно следующим псевдоинструкциям: 
        \en The function operation is equivalent to the following pseudoinstructions: 
		\~
		\~
    \code
	void nmppsResample***_perf(nm16u15b* pSrcVec, nm16u15b* pDstVec, int nSrcVecSize, nm64s* pKernel);
	{
		nmppsSetResample***_***(pKernel); 
		clock_t t0,t1;	
		t0=clock();
		nmppsResample***(pSrcVec, pDstVec, nSize,pKernel);
		t1=clock();
		exit(t1-t0);
	}
    \endcode


		\~
	\retval	pKernel	
        \ru Указатель на служебную структуру, содержащую весовые коэффиценты фильтра во внутреннем формате. 
        \en Pointer to auxilary structure, which contains filter coefficents in internal format. 
		\~
    \param	pSrcVec		
        \ru Входной вектор. 
        \en Input vec. 
		\~
    \param	nSrcVecSize		
        \ru Размер входного вектора в элементах. 
        \en Input vec size in elements. 
		\~
	\retval	pDstVec		
        \ru Результирующий вектор. 
        \en The result vec. 
	
		\~
    \note \ru Инициализация служебной структуры производится соответсвующей функцией nmppsSetFilter() и nmppsCreateFilter().
          \en Initialization of Auxilary structure is performed by call of appropriate SIF_SetFilter function and nmppsCreateFilter().

		\~
    \par
    \xmlonly
       <testperf> 
			<param name="pSrcVec"> im0 im1 </param>
			<param name="pDstVec"> im2 im1 </param>
			<param name="pKernel"> im2 im3 </param>
			<param name="nSrcVecSize"> 1024 </param>
        </testperf>
		<testperf> 
			<param name="pSrcVec"> im0  </param>
			<param name="pDstVec"> im1 </param>
			<param name="pKernel"> im2 </param>
			<param name="nSrcVecSize"> 128 1024 4096 </param>
        </testperf>
    \endxmlonly
    */
    //! \{
void nmppsResampleUp3Down2_perf(nm8s* pSrcVec, nm16s* pDstVec, int nSrcVecSize, nm64s* pKernel);
void nmppsResampleDown2_perf_8u(nm8u7b* pSrcVec, nm8u7b* pDstVec, int nSrcVecSize, nm64s* pKernel);
void nmppsResampleDown2_perf_16u(nm16u15b* pSrcVec, nm16u15b* pDstVec, int nSrcVecSize, nm64s* pKernel);
    //! \}
	
	
	
	
	
//! Класс КИХ фильтра
//! \tparam nmbits_in  Тип указывающий разрядность входного вектора. Допустимые типы : nm8s,nm16s,nm32s
//! \tparam nmbits_out Тип указывающий разрядность выходного вектора. Допустимые типы : nm8s,nm16s,nm32s. Разрядность входного вектора не должна превышать разрядности выходного.
//! \par Пример
//! \include app\example\Filter\nmppsFilter_16s32s\main.cpp 
#ifdef EEE
template <class nmbits_in, class nmbits_out> class CnmppsResampleUp3Down2
{
public:
	void (*pfFree32)(void*);	///< Указатель на функции освобождения памяти (pKernel)
	int nWeights;				///< Количество коэффицентов КИХ фильтра 
	nm64s* pKernel;				///< Указатель на внутреннюю структуру коэффициентов
	int nKernelSize;			///< Размер памяти необходимый для хранения внутренней структуру коэффициентов

	//! Конструктор КИХ фильтра 
	/*!
	   Выделяет область памяти под внутреннюю структуру коэффицентов 
      \param nWeights  устанавливает количество коэффицентов КИХ фильтра. nWeights=[3,5,7,9....]. 
      \param malloc32_func  указатель на функцию  выделения динамической памяти 32-разрядными словами.
	  \param free32_func  указатель на функцию динамического особождения памяти
    */
	CSIG_ResampleUp3Down2(void* (*malloc32_func)(unsigned),void (*free32_func)(void*));

	
	//! Функция одномерной фильтрации
	/*!
	\f[
        pDstVec[i]  =  \sum\limits_{j = 0}^{nWeights-1} {pSrcVec[i-nWeights/2] \cdot pWeights[j]}   ,i=0 \ldots  nSize-1
    \f]


      \param pSrcVec входной вектор 
	  \param pDstVec выходной вектор 
	  \param nSize размер вектора в элементах
	  \warning При вычислении первых и последних nWeights/2 отсчетов проивзодится выход за границы входного массива pSrcVec . 
	        Для коректного поведения функции необходимо дополнительные резервировать поля размером не менее nWeight/2 нулевых элементов перед началом и в конце массива pSrcVec.
    */
	void  Eval(nmbits_in* pSrcVec, nmbits_out* pDstVec, int nSize);
	
	//! Освобождает динамическую область памяти pKernel
	~CSIG_ResampleUp3Down2(){
		if (pKernel) 
			pfFree32(pKernel);
	}
	

};
#endif
	
	
	

#ifdef __cplusplus
		};
#endif

	
#endif // 