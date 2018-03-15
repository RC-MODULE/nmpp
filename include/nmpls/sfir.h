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
    \defgroup sFIR КИХ-фильтрация
		\ingroup sFiltration
		\brief Одномерная КИХ-фильтрация. 
	*/

	
//*****************************************************************************
#define NmppsFIRState void
    /**
    \defgroup nmppsFIR_Xs nmppsFIR_Xs
	\ingroup sFIR 
	\brief Одномерная КИХ-фильтрация 
    \param  [in] pSrc Входной вектор
    \param	[in] srcSize Размер входного вектора в элементах. Размер вектора должен быть кратен количеству элементов в 64-р. слове. 
	\param	[out] pDst Результирующий вектор
	\param	[in] NmppsFIRState  Служебная структура, содержащая весовые коэффициенты фильтра во внутреннем формате. 
    \note Инициализация служебной структуры производится соответствующей функцией nmppsFIRInit_Xs() или nmppsFIRInitAlloc_Xs().
    \perf  Максимальная производительность достигается при размещении pSrc, pDst и pPstate в разных банках памяти .
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
    \defgroup nmppsFIRInit_Xs nmppsFIRInit_Xs
    \ingroup sFIR
    \brief Инициализация функции одномерной фильтрации 

	Функция преобразует таблицу весовых коэффициентов окна фильтра во внутренний формат  
    \param [in]	pTaps Указатель на коэффициенты фильтра  
    \param [in] tapsLen	Размер окна фильтра. tapsLen=[3,5,7,9....] 
	\param [out] pState Указатель на служебную структуру, содержащую весовые коэффициенты фильтра во внутреннем формате. 
		 Размер памяти (в 32р.-словах) необходимый для хранения  служебной структуры  можно получить с помощью функции nmppsFIRGetStateSize_Xs
	\return Размер проинициализированной структуры pState в 32р. словах
		*/
//! \{		
int  nmppsFIRInit_8s	(NmppsFIRState* pState, int* pTaps, int tapsLen);
int  nmppsFIRInit_8s16s	(NmppsFIRState* pState, int* pTaps, int tapsLen);
int  nmppsFIRInit_8s32s	(NmppsFIRState* pState, int* pTaps, int tapsLen);
int  nmppsFIRInit_16s	(NmppsFIRState* pState, int* pTaps, int tapsLen);
int  nmppsFIRInit_16s32s(NmppsFIRState* pState, int* pTaps, int tapsLen);
int  nmppsFIRInit_32s	(NmppsFIRState* pState, int* pTaps, int tapsLen);
//! \}

/**
    \defgroup nmppsFIRInitAlloc_Xs nmppsFIRInitAlloc_Xs
    \ingroup sFIR
    \brief Выделение и инициализация служебной структуры для функции одномерной фильтрации 
    
	Функция выделяет структуру в куче и преобразует таблицу весовых коэффициентов окна фильтра во внутренний формат  
    \param [in]	pTaps Указатель на коэффициенты фильтра 
    \param [in]	tapsLen	Размер окна фильтра. nWeights=[3,5,7,9....] 
	\retval [out]	ppState Возвращает указатель на служебную структуру, содержащую весовые коэффициенты фильтра во внутреннем формате 
	\return Размер проинициализированной структуры pState в 32р. словах
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
    \defgroup nmppsFIRGetStateSize_Xs nmppsFIRGetStateSize_Xs
    \ingroup sFIR
    \brief Возвращает размер памяти (в 32р.-словах) необходимый для хранения  служебной структуры  
    \param [in]	tapsLen	Размер окна фильтра. tapsLen=[3,5,7,9....] 
	\return	Возвращает размер памяти (в 32р.-словах), необходимый для хранения  служебной структуры  NmppsFIRState 
		*/
//! \{	
int nmppsFIRGetStateSize_8s	   (int tapsLen);
int nmppsFIRGetStateSize_8s16s (int tapsLen);
int nmppsFIRGetStateSize_8s32s (int tapsLen);
int nmppsFIRGetStateSize_16s   (int tapsLen);
int nmppsFIRGetStateSize_16s32s(int tapsLen);
int nmppsFIRGetStateSize_32s   (int tapsLen);
//! \}
   
/**
    \defgroup nmppsFIRFree nmppsFIRFree
    \ingroup sFIR
    \brief освобождает структуру pState в куче
	\param [in]	pState указатель на служебную структуру  NmppsFIRState 

    */
//! \{   
void nmppsFIRFree(NmppsFIRState* pState);
//! \}





#ifdef __cplusplus
		};
#endif

   
#endif // _SFILTRATION_H_INCLUDED_

