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
          <param> pSrcVec </param> <values> L G 		</values>
          <param> nCrc  </param> <values> nn 		</values>
          <param> nSize     </param> <values> 10240 	</values>
				</testperf>
				<testperf>
          <param> pSrcVec </param> <values> G 		</values>
          <param> nCrc  </param> <values> nn 		</values>
          <param> nSize     </param> <values> 8 128 1024 10240 	</values>
				</testperf>

    \endxmlonly
    */
    //! \{
           void nmppsCrc_32u(nm32u* pSrcVec, int nSize, unsigned int* nCrc);
__INLINE__ void nmppsCrc_64s(nm64s* pSrcVec, int nSize, unsigned int* nCrc) {  nmppsCrc_32u((unsigned*)pSrcVec, nSize<<1, nCrc); }
__INLINE__ void nmppsCrc_32s(nm32s* pSrcVec, int nSize, unsigned int* nCrc) {  nmppsCrc_32u((unsigned*)pSrcVec, nSize,    nCrc); }           
__INLINE__ void nmppsCrc_16s(nm16s* pSrcVec, int nSize, unsigned int* nCrc) {  nmppsCrc_32u((unsigned*)pSrcVec, nSize>>1, nCrc); }
__INLINE__ void nmppsCrc_8s (nm8s*  pSrcVec, int nSize, unsigned int* nCrc) {  nmppsCrc_32u((unsigned*)pSrcVec, nSize>>2, nCrc); }
__INLINE__ void nmppsCrc_64u(nm64u* pSrcVec, int nSize, unsigned int* nCrc) {  nmppsCrc_32u((unsigned*)pSrcVec, nSize<<1, nCrc); }

__INLINE__ void nmppsCrc_16u(nm16u* pSrcVec, int nSize, unsigned int* nCrc) {  nmppsCrc_32u((unsigned*)pSrcVec, nSize>>1, nCrc); }
__INLINE__ void nmppsCrc_8u (nm8u*  pSrcVec, int nSize, unsigned int* nCrc) {  nmppsCrc_32u((unsigned*)pSrcVec, nSize>>2, nCrc); }


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
			<param> pSrc1 </param> <values> L G </values>
			<param> pSrc2 </param> <values> L G </values>
			<size> 1 </size>
	 </testperf>
	\endxmlonly
    */

    //! \{
int nmppsSadV16_16s(nm16s* pSrc1,nm16s* pSrc2);
int nmppsSadV16_8s(nm8s*  pSrc1,nm8s*  pSrc2);
    //! \}


#endif // _VSTAT_H_INCLUDED_