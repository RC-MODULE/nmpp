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

inline int nmppsSizeOf_8s(nm8s*, int nCount){
	return nCount>>2;
}
inline int nmppsSizeOf_8u(nm8u*, int nCount){
	return nCount>>2;
}
inline int nmppsSizeOf_32s(nm32s*, int nCount){
	return nCount;
}
inline int nmppsSizeOf_32u(nm32u*, int nCount){
	return nCount;
}

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
		//nmppsMalloc_(&m_pContainer, m_nStride*(m_nHeight+2*m_nBorder), nHint);
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
			nmppsFree_(m_pContainer);
	}
	void Fill(T color)
	{
		nmppsSet_(m_pContainer,color,m_nSize+2*m_nBorder*m_nStride);
	}
};

//*****************************************************************************

    /**
	\internal
    \defgroup IMG_Malloc IMG_Malloc
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
    \note \ru Память, распределенная с помощью функций IMG_Malloc должна
              освобождаться только с помощью функции IMG_Free. 
          \en Memory allocated by function IMG_Malloc should be 
              deallocated by IMG_Free function only. 
			  \~
    */
    //! \{

void IMG_Malloc(nm1** pptr, int nWidth, int nHeight, int hint = MEM_LOCAL);
void IMG_Malloc(nm2s** pptr, int nWidth, int nHeight, int hint = MEM_LOCAL);
void IMG_Malloc(nm2u** pptr, int nWidth, int nHeight, int hint = MEM_LOCAL);
void IMG_Malloc(nm4s** pptr, int nWidth, int nHeight, int hint = MEM_LOCAL);
void IMG_Malloc(nm4u** pptr, int nWidth, int nHeight, int hint = MEM_LOCAL);
void IMG_Malloc(nm8u** pptr, int nWidth, int nHeight, int hint = MEM_LOCAL);
void IMG_Malloc(nm8s** pptr, int nWidth, int nHeight, int hint = MEM_LOCAL);
void IMG_Malloc(nm16u** pptr, int nWidth, int nHeight, int hint = MEM_LOCAL);
void IMG_Malloc(nm16s** pptr, int nWidth, int nHeight, int hint = MEM_LOCAL);
void IMG_Malloc(nm32u** pptr, int nWidth, int nHeight, int hint = MEM_LOCAL);
void IMG_Malloc(nm32s** pptr, int nWidth, int nHeight, int hint = MEM_LOCAL);
void IMG_Malloc(nm64u** pptr, int nWidth, int nHeight, int hint = MEM_LOCAL);
void IMG_Malloc(nm64s** pptr, int nWidth, int nHeight, int hint = MEM_LOCAL);

    //! \}

//*****************************************************************************

    /**
    \defgroup IMG_Free IMG_Free
    \ingroup iSupport
    \brief
        \ru Освобождение памяти для изображений. 
        \en Memory deallocation for images. 
		\~
    \note \ru Данная функция должна вызываться только для
              векторов, распределенных с помощью функций 
              IMG_Malloc.
          \en This function should be called only for matrixis
              allocated by IMG_Malloc functions. 
			  \~
   */
    //! \{

void IMG_Free(void* ptr);
    //! \}


/**
	\defgroup IMG_Release IMG_Release
	\ingroup iSupport
   \brief
        \ru Освобождение блоков памяти, выделенных функиями  IMG_Create***. 
        \en Deallocation of memory blocks allocated by IMG_Create*** functions. 
		\~
*/
	//! \{
static inline void IMG_ReleaseObject(nm64s* pKernel);
	//! \}



#endif
