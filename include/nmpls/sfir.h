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


    /**
	\internal
    \defgroup sFIR КИХ-фильтрация
		\ingroup sFiltration
		\brief 
			\ru Одномерная КИХ-фильтрация. 
			\en One-dimensional filtration. 
	*/

	
//*****************************************************************************
#define NmppsFIRState void
    /**
	\internal
    \defgroup nmppsFIR_Xs nmppsFIR_Xs
		\ingroup sFIR
		\brief 
			\ru Одномерная КИХ-фильтрация. 
			\en One-dimensional filtration. 

		\~
		\~
    \param	pSrc		
        \ru Входной вектор. 
        \en Input vec. 
		\~
    \param	srcSize		
        \ru Размер входного вектора в элементах. 
        \en Input vec size in elements. 
		\~
	\retval	pDst		
        \ru Результирующий вектор. 
        \en The result vec. 
		\~
	\param	NmppsFIRState
        \ru Служебная структура, содержащая весовые коэффициенты фильтра во внутреннем формате. 
        \en Auxilary structure, which contains filter coefficents in internal format. 
	
		\~
    \note \ru Инициализация служебной структуры производится соответствующей функцией nmppsFIRInit_Xs() или nmppsFIRInitAlloc_Xs().
	      \en Initialization of Auxilary structure is performed by call of appropriate nmppsFIRInit_Xs function and nmppsFIRInitAlloc_Xs().
    \perf  \ru Максимальная производительность достигается при размещении pSrc, pDst и pPstate в разных банках памяти .
		\~    
	*/
//! \{
void nmppsFIR_8s	( nm8s* pSrc, nm8s* pDst, int srcSize,  NmppsFIRState* pState);
void nmppsFIR_8s16s	( nm8s* pSrc, nm16s* pDst, int srcSize,  NmppsFIRState* pState);
void nmppsFIR_8s32s	( nm8s* pSrc, nm32s* pDst, int srcSize,  NmppsFIRState* pState);
void nmppsFIR_16s	( nm16s* pSrc, nm16s* pDst, int srcSize,  NmppsFIRState* pState);
void nmppsFIR_16s32s( nm16s* pSrc, nm32s* pDst, int srcSize,  NmppsFIRState* pState);
void nmppsFIR_32s	( nm32s* pSrc, nm32s* pDst, int srcSize,  NmppsFIRState* pState);
   //! \}

/**
	\internal
    \defgroup nmppsFIRInit_Xs nmppsFIRInit_Xs
    \ingroup sFIR
    \brief
        \ru Инициализация функции одномерной фильтрации. 
        \en Initialization of the core for one-dimensional filtration. 
    
		\~
        \ru Функция преобразует таблицу весовых коэффициентов окна фильтра во внутренний формат  
        \en The functions init the table of weight coefficients from the linear array 
        to internal format . 

		\~
		\~
    \param	pTaps		
        \ru Указатель на коэффциенты фильтра . 
        \en Pointer to the filter coefficients. 
		\~
    \param	tapsLen	
        \ru Размер окна фильтра. nWeights=[3,5,7,9....]. 
        \en Size of filter window . 
		\~
	\retval	NmppsFIRState	
        \ru Указатель на служебную структуру, содержащую весовые коэффиценты фильтра во внутреннем формате. 
		 Размер памяти (в 32р.-словах) необходимый для хранения  служебной структуры  можно с помощью функции nmppsFIRGetStateSize_Xs
        \en Pointer to auxilary structure, which contains filter coefficents in internal format. 
		\~
	\return
		\ru Размер проинициализированной структуры pKernel в 32р. словах
		\en Size of inited structure pKernel in 32 bit words
		\~
		*/
//! \{		
int  nmppsFIRInit_8s	(NmppsFIRState* ppState, int* pTaps, int tapsLen);
int  nmppsFIRInit_8s16s	(NmppsFIRState* ppState, int* pTaps, int tapsLen);
int  nmppsFIRInit_8s32s	(NmppsFIRState* ppState, int* pTaps, int tapsLen);
int  nmppsFIRInit_16s	(NmppsFIRState* ppState, int* pTaps, int tapsLen);
int  nmppsFIRInit_16s32s(NmppsFIRState* ppState, int* pTaps, int tapsLen);
int  nmppsFIRInit_32s	(NmppsFIRState* ppState, int* pTaps, int tapsLen);
//! \}

/**
	\internal
    \defgroup nmppsFIRInit_Xs nmppsFIRInit_Xs
    \ingroup sFIR
    \brief
        \ru Выделение и инициализация служебной стуктуры для функции одномерной фильтрации. 
        \en Initialization of the core for one-dimensional filtration. 
    
		\~
        \ru Функция выдляет структуру в куче и преобразует таблицу весовых коэффициентов окна фильтра во внутренний формат  
        \en The functions init the table of weight coefficients from the linear array 
        to internal format . 

		\~
		\~
    \param	pTaps		
        \ru Указатель на коэффциенты фильтра . 
        \en Pointer to the filter coefficients. 
		\~
    \param	tapsLen	
        \ru Размер окна фильтра. nWeights=[3,5,7,9....]. 
        \en Size of filter window . 
		\~
	\retval	NmppsFIRState	
        \ru Возвращает указатель на служебную структуру, содержащую весовые коэффиценты фильтра во внутреннем формате. 
		\en Pointer to auxilary structure, which contains filter coefficents in internal format. 
		\~
	\return
		\ru Размер проинициализированной структуры pKernel в 32р. словах
		\en Size of inited structure pKernel in 32 bit words
		\~
		*/
//! \{	
int  nmppsFIRInitAlloc_8s	 (NmppsFIRState** ppState, int* pTaps, int tapsLen);
int  nmppsFIRInitAlloc_8s16s (NmppsFIRState** ppState, int* pTaps, int tapsLen);
int  nmppsFIRInitAlloc_8s32s (NmppsFIRState** ppState, int* pTaps, int tapsLen);
int  nmppsFIRInitAlloc_16s	 (NmppsFIRState** ppState, int* pTaps, int tapsLen);
int  nmppsFIRInitAlloc_16s32s(NmppsFIRState** ppState, int* pTaps, int tapsLen);
int  nmppsFIRInitAlloc_32s	 (NmppsFIRState** ppState, int* pTaps, int tapsLen);
//! \}
  
/**
	\internal
    \defgroup nmppsFIRInit_Xs nmppsFIRInit_Xs
    \ingroup sFIR
    \brief
        \ru Возващает размер памяти (в 32р.-словах) необходимый для хранения  служебной структуры  
        \en Initialization of the core for one-dimensional filtration. 
		\~
    \param	tapsLen	
        \ru Размер окна фильтра. nWeights=[3,5,7,9....]. 
        \en Size of filter window . 
		\~
	\return
		\ru Возващает размер памяти (в 32р.-словах), необходимый для хранения  служебной структуры  
		\en Size of inited structure pKernel in 32 bit words
		\~
		*/
//! \{	
int nmppsFIRGetStateSize_8s	   (int tapsLen);
int nmppsFIRGetStateSize_8s16s (int tapsLen);
int nmppsFIRGetStateSize_8s32s (int tapsLen);
int nmppsFIRGetStateSize_16s   (int tapsLen);
int nmppsFIRGetStateSize_16s32s(int tapsLen);
int nmppsFIRGetStateSize_32s	(int tapsLen);
//! \}
   
/**
	\internal
    \defgroup nmppsFIRFree nmppsFIRFree
    \ingroup sFIR
    \brief
        \ru осоводжадет структру pState в куче
        \en Initialization of the core for one-dimensional filtration. 
		\~
    	*/
//! \{   
void nmppsFIRFree(NmppsFIRState* pState);
//    //! \}





#ifdef __cplusplus
		};
#endif

   
#endif // _SFILTRATION_H_INCLUDED_

