//------------------------------------------------------------------------
//
//  $Workfile:: vStat.h  $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:02 $
//
//! \if file_doc
//!
//! \file   vMinMax.h
//! \author Сергей Мушкаев
//! \brief  Определение функций поиска минимума и максимума
//!
//! \endif
//!
//------------------------------------------------------------------------

 
#ifndef _VSTAT_H_INCLUDED_
#define _VSTAT_H_INCLUDED_

#ifdef __cplusplus
		extern "C" {
#endif

    /**
	\internal
    \defgroup nmppsCrc_ nmppsCrc_
    \ingroup vStat
		\brief 
		    \ru Подсчет циклического кода.
		    \en Cyclic code calculation.

		\~
	  \~
		\param pSrcVec
			\ru Входной вектор.
			\en Input vec.
		\~
		\param nSize
			\ru Размер входного вектора.
			\en Input vec size.

		\~
		\retval nCrc
			\ru Циклический код.
			\en Cyclic code.

		\~
    \par
    \xmlonly
				<testperf>
          <param name="pSrcVec"> im0 im1 		</param>
          <param name="crcAccumulator"> im2 		</param>
          <param name="nSize"> 2048 	</param>
				</testperf>
				<testperf>
          <param name="pSrcVec"> im0 		</param>
          <param name="crcAccumulator"> im2 		</param>
          <param name="nSize"> 8 128 1024 2048 	</param>
				</testperf>

    \endxmlonly
    */
    //! \{
	unsigned nmppsCrc_32u		(const unsigned int* pSrcVec, int nSize);
	unsigned nmppsCrcAcc_32u	(const unsigned int* pSrcVec, int nSize, unsigned int* crcAccumulator);
	
	
   
__INLINE__ unsigned  nmppsCrc_64s(nm64s* pSrcVec, int nSize) {  return nmppsCrc_32u((unsigned*)pSrcVec, nSize<<1); }
__INLINE__ unsigned  nmppsCrc_32s(nm32s* pSrcVec, int nSize) {  return nmppsCrc_32u((unsigned*)pSrcVec, nSize   ); }           
__INLINE__ unsigned  nmppsCrc_16s(nm16s* pSrcVec, int nSize) {  return nmppsCrc_32u((unsigned*)pSrcVec, nSize>>1); }
__INLINE__ unsigned  nmppsCrc_8s (nm8s*  pSrcVec, int nSize) {  return nmppsCrc_32u((unsigned*)pSrcVec, nSize>>2); }
__INLINE__ unsigned  nmppsCrc_4s (nm4s*  pSrcVec, int nSize) {  return nmppsCrc_32u((unsigned*)pSrcVec, nSize>>3); }
__INLINE__ unsigned  nmppsCrc_64u(nm64u* pSrcVec, int nSize) {  return nmppsCrc_32u((unsigned*)pSrcVec, nSize<<1); }
                                                                
//__INLINE__ unsigned  nmppsCrc_32f(nm32f* pSrcVec, int numBitsToClear, int nSize) {  return nmppsCrcMask_32u((unsigned*)pSrcVec,(-1<<numBitsToClear),nSize>>1); }
																
__INLINE__ unsigned  nmppsCrc_16u(nm16u* pSrcVec, int nSize) {  return nmppsCrc_32u((unsigned*)pSrcVec, nSize>>1); }
__INLINE__ unsigned  nmppsCrc_8u (nm8u*  pSrcVec, int nSize) {  return nmppsCrc_32u((unsigned*)pSrcVec, nSize>>2); }


__INLINE__ unsigned nmppsCrcAcc_64s(nm64s* pSrcVec, int nSize, unsigned int* crcAccumulator) {  return nmppsCrcAcc_32u((unsigned*)pSrcVec, nSize<<1, crcAccumulator); }
__INLINE__ unsigned nmppsCrcAcc_32s(nm32s* pSrcVec, int nSize, unsigned int* crcAccumulator) {  return nmppsCrcAcc_32u((unsigned*)pSrcVec, nSize,    crcAccumulator); }           
__INLINE__ unsigned nmppsCrcAcc_16s(nm16s* pSrcVec, int nSize, unsigned int* crcAccumulator) {  return nmppsCrcAcc_32u((unsigned*)pSrcVec, nSize>>1, crcAccumulator); }
__INLINE__ unsigned nmppsCrcAcc_8s (nm8s*  pSrcVec, int nSize, unsigned int* crcAccumulator) {  return nmppsCrcAcc_32u((unsigned*)pSrcVec, nSize>>2, crcAccumulator); }
__INLINE__ unsigned nmppsCrcAcc_64u(nm64u* pSrcVec, int nSize, unsigned int* crcAccumulator) {  return nmppsCrcAcc_32u((unsigned*)pSrcVec, nSize<<1, crcAccumulator); }


__INLINE__ unsigned nmppsCrcAcc_16u(nm16u* pSrcVec, int nSize, unsigned int* crcAccumulator) {  return nmppsCrcAcc_32u((unsigned*)pSrcVec, nSize>>1, crcAccumulator); }
__INLINE__ unsigned nmppsCrcAcc_8u (nm8u*  pSrcVec, int nSize, unsigned int* crcAccumulator) {  return nmppsCrcAcc_32u((unsigned*)pSrcVec, nSize>>2, crcAccumulator); }

unsigned nmppsCrcAcc_32f(const nm32f* pSrcVec, int numBitsToClear, int nSize,  unsigned int* crcAccumulator) ;                                                                                                          
unsigned nmppsCrcAcc_64f(const nm64f* pSrcVec, int numBitsToClear, int nSize,  unsigned int* crcAccumulator) ;

    //! \}
	


//*****************************************************************************
	/**
	\internal
    \defgroup nmppsSadV16_ nmppsSadV16_
    \ingroup vStat
	\brief 
		\ru Сумма абсолютных разностей двух массивов (SAD) размером в 16 элементов 
		\en Sum of absolute differences (SAD) between two array with size of 16 numbers 

		\~
	\param pSrc1
		\ru Массив из 16 элементов. 
        \en array of 16 numbers
		\~
	\param pSrc2
		\ru Массив из 16 элементов. 
        \en array of 16 numbers
		\~
	\return int		
		\ru SAD. 
        \en SAD

		\~
  \par
	\xmlonly
	 <testperf> 
			<param name="pSrc1"> im0 im1 </param>
			<param name="pSrc2"> im0 im1 </param>
			<size> 1 </size>
	 </testperf>
	\endxmlonly
    */

    //! \{
int nmppsSadV16_16s(nm16s* pSrc1,nm16s* pSrc2);
int nmppsSadV16_8s(nm8s*  pSrc1,nm8s*  pSrc2);
    //! \}

	
#ifdef __cplusplus
		};
#endif

#endif // _VSTAT_H_INCLUDED_