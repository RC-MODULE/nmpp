//------------------------------------------------------------------------
//
//  $Workfile:: iSupport.h            $
//
//  Neuro mtr processing library
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2005/02/10 12:36:38 $
//
//! \if file_doc
//!
//! \file   iMalloc.h
//! \author Дмитрий Рыжов
//! \brief  Распределение памяти для изображений библиотеки.
//!
//! \endif
//!
//------------------------------------------------------------------------
#ifndef __IMALLOC_H
#define __IMALLOC_H
#include "nmtype.h"
/*
__INLINE__ int nmppsSizeOf_8s(nm8s* a, int nCount) {
	return nCount>>2;
}
__INLINE__ int nmppsSizeOf_8u(nm8u*, int nCount) {
	return nCount>>2;
}
__INLINE__ int nmppsSizeOf_32s(nm32s*, int nCount) {
	return nCount;
}
__INLINE__ int nmppsSizeOf_32u(nm32u*, int nCount) {
	return nCount;
}

*/

// __INLINE__ int nmppsSizeOf_8s(nm8s*, int nCount){
// 	return nCount>>2;
// }
// __INLINE__ int nmppsSizeOf_8u(nm8u*, int nCount){
// 	return nCount>>2;
// }
// __INLINE__ int nmppsSizeOf_32s(nm32s*, int nCount){
// 	return nCount;
// }
// __INLINE__ int nmppsSizeOf_32u(nm32u*, int nCount){
// 	return nCount;
// }

template <class T> class C_Img
{
protected:

public:
	int m_nBorder;
	T*  m_pContainer;
	T*  m_pData;
	int m_nWidth;
	int m_nHeight;
	int m_nStride;
	int m_nSize;
	C_Img(int nWidth,int nHeight, int nStride, int nBorder, void* (*allocator32)(int))
	{
		m_nWidth=nWidth;
		m_nHeight=nHeight;
		m_nBorder=nBorder;
		m_nStride=nStride;
		m_nSize=m_nStride*m_nHeight;
		m_pContainer=(T*)allocator32(nmppsSizeOf_(m_pData,m_nStride*(m_nHeight+2*m_nBorder)));
		//nmppsMalloc_64s(&m_pContainer, m_nStride*(m_nHeight+2*m_nBorder), nHint);
		m_pData=nmppsAddr_(m_pContainer,m_nStride*m_nBorder);
	}
	C_Img(T* pData, int nWidth,int nHeight, int nStride, int nBorder)
	{
		m_nWidth=nWidth;
		m_nHeight=nHeight;
		m_nBorder=nBorder;
		m_nStride=nStride;
		m_nSize=m_nStride*m_nHeight;
		m_pContainer=0;;
		m_pData=pData;

	}
	~C_Img()
	{
		if (m_pContainer)
			nmppsFree(m_pContainer);
	}
	void Fill(T color)
	{
		nmppsSet_(m_pContainer,color,m_nSize+2*m_nBorder*m_nStride);
	}
};

//*****************************************************************************

    /*
	\internal
    \defgroup nmppiMalloc nmppiMalloc
    \ingroup iSupport
    \brief
        \ru Распределение памяти для изображений библиотеки.
        \en Memory allocation for library images.

		\~
        \ru Начало и конец распределяемой памяти выравнивается на начало
        64-х разрядного слова.
        \en Begin and end of the allocated memory are being
        aligned to 64-bit word.
		\~
    \param nWidth
        \ru Ширина изображения в пикселях.
        \en Image width in pixels.
		\~
    \param nHeight
        \ru Высота изображения в пикселях.
        \en Image height in pixels.
		\~
    \param hint
        \ru Номер банка памяти. Может принимать значения
                        MEM_LOCAL, MEM_GLOBAL.
        \en Number of memory bank. Admissible values for memory bank
                        are MEM_LOCAL, MEM_GLOBAL.
		\~
    \note \ru Память, распределенная с помощью функций nmppiMalloc должна
              освобождаться только с помощью функции nmppiFree.
          \en Memory allocated by function nmppiMalloc should be
              deallocated by nmppiFree function only.
			  \~
    */
    //! \{
/*
void nmppiMalloc(nm1** pptr, int nWidth, int nHeight, int hint = MEM_LOCAL);
void nmppiMalloc(nm2s** pptr, int nWidth, int nHeight, int hint = MEM_LOCAL);
void nmppiMalloc(nm2u** pptr, int nWidth, int nHeight, int hint = MEM_LOCAL);
void nmppiMalloc(nm4s** pptr, int nWidth, int nHeight, int hint = MEM_LOCAL);
void nmppiMalloc(nm4u** pptr, int nWidth, int nHeight, int hint = MEM_LOCAL);
void nmppiMalloc(nm8u** pptr, int nWidth, int nHeight, int hint = MEM_LOCAL);
void nmppiMalloc(nm8s** pptr, int nWidth, int nHeight, int hint = MEM_LOCAL);
void nmppiMalloc(nm16u** pptr, int nWidth, int nHeight, int hint = MEM_LOCAL);
void nmppiMalloc(nm16s** pptr, int nWidth, int nHeight, int hint = MEM_LOCAL);
void nmppiMalloc(nm32u** pptr, int nWidth, int nHeight, int hint = MEM_LOCAL);
void nmppiMalloc(nm32s** pptr, int nWidth, int nHeight, int hint = MEM_LOCAL);
void nmppiMalloc(nm64u** pptr, int nWidth, int nHeight, int hint = MEM_LOCAL);
void nmppiMalloc(nm64s** pptr, int nWidth, int nHeight, int hint = MEM_LOCAL);
*/
    //! \}

//*****************************************************************************
    /*
	\defgroup nmppiFree nmppiFree
	\ingroup iSupport
	\brief
		\ru Освобождение памяти для изображений.
		\en Memory deallocation for images.
		\~
	\note 
		\ru Данная функция должна вызываться только для
			  векторов, распределенных с помощью функций
			  nmppiMalloc.
		\en This function should be called only for matrixis
			  allocated by nmppiMalloc functions.
		\~
	*/
    //! \{
//void nmppiFree(void* ptr);
    //! \}


/**
	\defgroup nmppiRelease nmppiRelease
	\ingroup iSupport
   \brief
        \ru Освобождение блоков памяти, выделенных функиями  nmppiCreate***.
        \en Deallocation of memory blocks allocated by nmppiCreate*** functions.
		\~
*/
	//! \{
__INLINE__ void nmppiReleaseObject(nm64s* pKernel);
	//! \}



#endif
