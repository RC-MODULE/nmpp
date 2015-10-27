  //------------------------------------------------------------------------
//
//  $Workfile:: vSupport. $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.2 $      $Date: 2004/12/21 14:36:01 $
//
//------------------------------------------------------------------------


//------------------------------------------------------------------------
#ifndef __VSUPPORT_H
#define __VSUPPORT_H
#include <stdlib.h>
    /**
    \defgroup VEC_Malloc VEC_Malloc
    \ingroup vSupport
    \brief
        \ru Распределение памяти для векторов библиотеки. 
        \en Memory allocation for library vectors. 
		\~
    \param nSize 
        \ru Число элементов в векторе. 
        \en Number of elements in vec. 
		\~
    \param hint 
        \ru Номер банка памяти. Может принимать значения 
                    MEM_LOCAL, MEM_GLOBAL. 
        \en Number of memory bank. Admissible values for memory bank
                    are MEM_LOCAL, MEM_GLOBAL. 
		\~
    \note 
		\ru Память, распределенная с помощью функций VEC_Malloc должна
              освобождаться с помощью функции VEC_Free(). 
        \en Memory allocated with function VEC_Malloc should be 
              freed with function VEC_Free()
		\~
    */
    //! \{
void VEC_Malloc(nm64s** pptr, int nSize, int hint = MEM_LOCAL);
inline void VEC_Malloc(nm1**   pptr, int nSize, int hint = MEM_LOCAL) { VEC_Malloc((nm64s**)pptr, (nSize>>6) +1, hint);}
inline void VEC_Malloc(nm2s**  pptr, int nSize, int hint = MEM_LOCAL) { VEC_Malloc((nm64s**)pptr, (nSize>>5) +1, hint);}
inline void VEC_Malloc(nm2u**  pptr, int nSize, int hint = MEM_LOCAL) { VEC_Malloc((nm64s**)pptr, (nSize>>5) +1, hint);}
inline void VEC_Malloc(nm4s**  pptr, int nSize, int hint = MEM_LOCAL) { VEC_Malloc((nm64s**)pptr, (nSize>>4) +1, hint);}
inline void VEC_Malloc(nm4u**  pptr, int nSize, int hint = MEM_LOCAL) { VEC_Malloc((nm64s**)pptr, (nSize>>4) +1, hint);}
inline void VEC_Malloc(nm8u**  pptr, int nSize, int hint = MEM_LOCAL) { VEC_Malloc((nm64s**)pptr, (nSize>>3) +1, hint);}
inline void VEC_Malloc(nm8s**  pptr, int nSize, int hint = MEM_LOCAL) { VEC_Malloc((nm64s**)pptr, (nSize>>3) +1, hint);}
inline void VEC_Malloc(nm16u** pptr, int nSize, int hint = MEM_LOCAL) { VEC_Malloc((nm64s**)pptr, (nSize>>2) +1, hint);}
inline void VEC_Malloc(nm16s** pptr, int nSize, int hint = MEM_LOCAL) { VEC_Malloc((nm64s**)pptr, (nSize>>2) +1, hint);}
inline void VEC_Malloc(nm32u** pptr, int nSize, int hint = MEM_LOCAL) { VEC_Malloc((nm64s**)pptr, (nSize>>1) +1, hint);}
inline void VEC_Malloc(nm32s** pptr, int nSize, int hint = MEM_LOCAL) { VEC_Malloc((nm64s**)pptr, (nSize>>1) +1, hint);}
inline void VEC_Malloc(nm64u** pptr, int nSize, int hint = MEM_LOCAL) { VEC_Malloc((nm64s**)pptr, nSize, hint);}
    //! \}

//*****************************************************************************

    /**
    \defgroup VEC_Free VEC_Free
    \ingroup vSupport
    \brief
        \ru Освобождение памяти для векторов. 
        \en Memory deallocation for vectors. 
		\~
    \note 
		  \ru Данная функция должна вызываться только для
              векторов, распределенных с помощью функций 
              VEC_Malloc.
          \en This function should be called only for matrixis
              allocated by VEC_Malloc functions. 
		\~
    */
    //! \{


inline void VEC_Free(void* ptr) {free((void*)ptr);}
    //! \}

//*****************************************************************************

    /**
    \defgroup VEC_Addr VEC_Addr
    \ingroup vSupport
    \brief
        \ru Возвращает адрес ячейки памяти, содержащей указанный элемент. 
        \en Returns address of memory cell that contains
        the vec element. 
    
		\~
        \ru Реализация для процессора NeuroMatrix возвращает адрес, выровненный 
            в памяти на 32 бита. 
        \en Implementation for NeuroMatrix processor returns an addres aligned 
            with 32 bits in the memory.
		\~
    \param pVec     
        \ru Входной вектор. 
        \en Input vec. 
		\~
    \param nIndex    
        \ru Индекс элемента. 
        \en Element index. 

		\~
    \return         
        \ru Адрес ячейки памяти. 
        \en Address of memory cell. 

		\~
    \note 
        \ru Для ускорения работы на PC возможно использование макроса
            ADDR(ptr, index), который раскрывается на PC как 
            (ptr+index), а на NM как вызов функции VEC_Addr. 
        \en To increase perfomance on PC it's possible to use macros
            ADDR(ptr, index) that equivalent to (ptr+index) expression. 

		\~
    \par
    \xmlonly
        <testperf> 
             <param> pVec   </param> <values> L G </values>
             <param> nIndex </param> <values> 0 </values>
             <size> 1 </size>
        </testperf>
    \endxmlonly
    */
    //! \{
inline nm1* VEC_Addr(nm1*  pVec, int nIndex){	return (nm1*)((int*)pVec+(nIndex>>5));}
inline nm2s* VEC_Addr(nm2s*  pVec, int nIndex){	return (nm2s*)((int*)pVec+(nIndex>>4));}
inline nm4s* VEC_Addr(nm4s*  pVec, int nIndex){	return (nm4s*)((int*)pVec+(nIndex>>3));}

nm8s*  VEC_Addr(const nm8s*  pVec, int nIndex);
nm16s* VEC_Addr(nm16s* pVec, int nIndex);
nm32s* VEC_Addr(nm32s* pVec, int nIndex);

inline nm64s* VEC_Addr(nm64s* pVec, int nIndex) {return pVec+nIndex;}
#ifdef __NM__
inline nm8u*  VEC_Addr(const nm8u*  pVec, int nIndex) {return (nm8u*)VEC_Addr((nm8s*)  pVec, nIndex);}
inline nm16u* VEC_Addr(nm16u* pVec, int nIndex) {return (nm16u*)VEC_Addr((nm16s*)  pVec, nIndex);}
#else 
inline nm8u*  VEC_Addr(const nm8u*  pVec, int nIndex) {return (nm8u*)pVec+nIndex;}
inline nm16u* VEC_Addr(nm16u* pVec, int nIndex) {return pVec+nIndex;}
#endif
inline nm32u* VEC_Addr(nm32u* pVec, int nIndex) {return pVec+nIndex;}
inline nm64u* VEC_Addr(nm64u* pVec, int nIndex) {return pVec+nIndex;}


inline nm64u* VEC_Addr64(nm1*   pVec, int nIndex) {return (nm64u*)pVec+(nIndex>>6);}
inline nm64u* VEC_Addr64(nm2s*  pVec, int nIndex) {return (nm64u*)pVec+(nIndex>>5);}
inline nm64u* VEC_Addr64(nm4s*  pVec, int nIndex) {return (nm64u*)pVec+(nIndex>>4);}
inline nm64u* VEC_Addr64(nm8s*  pVec, int nIndex) {return (nm64u*)pVec+(nIndex>>3);}
inline nm64u* VEC_Addr64(nm16s* pVec, int nIndex) {return (nm64u*)pVec+(nIndex>>2);}
inline nm64u* VEC_Addr64(nm32s* pVec, int nIndex) {return (nm64u*)pVec+(nIndex>>1);}
inline nm64u* VEC_Addr64(nm64s* pVec, int nIndex) {return (nm64u*)pVec+nIndex;}

inline nm64u* VEC_Addr64(nm8u*  pVec, int nIndex) {return (nm64u*)pVec+(nIndex>>3);}
inline nm64u* VEC_Addr64(nm16u* pVec, int nIndex) {return (nm64u*)pVec+(nIndex>>2);}
inline nm64u* VEC_Addr64(nm32u* pVec, int nIndex) {return (nm64u*)pVec+(nIndex>>1);}
inline nm64u* VEC_Addr64(nm64u* pVec, int nIndex) {return (nm64u*)pVec+nIndex;}


    //! \}

//*****************************************************************************

    /**
    \defgroup VEC_SetVal VEC_SetVal
    \ingroup vSupport
    \brief
        \ru Модификация элемента вектора. 
        \en Vector element modification. 
    
		\~
    
	\f[
        pVec(nIndex)  =  Val
    \f]
    \param pVec   
        \ru Вектор. 
        \en Vector. 
		\~
    \param nIndex    
        \ru Позиция элемента 
        \en Position of the element. 
		\~
    \param nVal  
        \ru Значение элемента 
        \en Value of the element. 
		\~
    \return \e void
    
    \par
    \xmlonly
        <testperf> 
             <param> pVec </param> <values> L G </values>
             <param> nVal    </param> <values> 3 </values>
             <param> nIndex  </param> <values> 0 </values>
             <size> 1 </size>
        </testperf>
    \endxmlonly
    */
    //! \{

void		VEC_SetVal(nm1*  pVec,  int nIndex,  int1b  nVal);
void		VEC_SetVal(nm2s* pVec,  int nIndex,  int2b  nVal);
void		VEC_SetVal(nm4s* pVec,  int nIndex,  int4b  nVal);
void		VEC_SetVal(nm8s* pVec,  int nIndex,  int8b  nVal);
void		VEC_SetVal(nm16s* pVec, int nIndex,  int16b nVal);
inline void VEC_SetVal(nm32s* pVec, int nIndex,  int32b nVal)	{pVec[nIndex]=nVal;}
inline void VEC_SetVal(nm64s* pVec, int nIndex,  int64b nVal)	{pVec[nIndex]=nVal;}

inline void	VEC_SetVal(nm2u* pVec,  int nIndex, uint2b  nVal)   {VEC_SetVal((nm2s*)pVec,nIndex,(int2b)nVal);}
inline void	VEC_SetVal(nm4u* pVec,  int nIndex, uint4b  nVal)   {VEC_SetVal((nm4s*)pVec,nIndex,(int4b)nVal);}
inline void	VEC_SetVal(nm8u* pVec,  int nIndex, uint8b nVal)	{VEC_SetVal((nm8s*)pVec,nIndex,(int8b)nVal);}
inline void	VEC_SetVal(nm16u* pVec, int nIndex, uint16b nVal)   {VEC_SetVal((nm16s*)pVec,nIndex,(int16b)nVal);}
inline void VEC_SetVal(nm32u* pVec, int nIndex, uint32b nVal)	{pVec[nIndex]=nVal;}
inline void VEC_SetVal(nm64u* pVec, int nIndex, uint64b nVal)	{pVec[nIndex]=nVal;}

    
    //! \}

//*****************************************************************************

    /**
    \defgroup VEC_GetVal VEC_GetVal
    \ingroup vSupport
    \brief
        \ru Извлекает значение элемента вектора. 
        \en Extracts the vec element value. 
		\~
    \param pVec     
        \ru Вектор. 
        \en Vector. 
		\~
    \param nIndex   
        \ru Позиция элемента. 
        \en Position of the element. 
		\~
    \retval nVal   
        \ru Значение элемента. 
        \en Value of the element. 
		\~
    \return \e void
    \par
    \xmlonly
        <testperf> 
             <param> pVec		</param> <values> L G	</values>
             <param> nVal		</param> <values> n		</values>
             <param> nIndex		</param> <values> 0		</values>
             <size> 1 </size>
        </testperf>
    \endxmlonly
    
    */
    //! \{
void			VEC_GetVal(nm1*   pVec, int nIndex, int1b &nVal);
void			VEC_GetVal(nm2s*  pVec, int nIndex, int2b &nVal);
void			VEC_GetVal(nm4s*  pVec, int nIndex, int4b &nVal);
void			VEC_GetVal(nm8s*  pVec, int nIndex, int8b &nVal);
void			VEC_GetVal(nm16s* pVec, int nIndex, int16b &nVal);
inline  void	VEC_GetVal(nm32s* pVec, int nIndex, int32b& nVal) { nVal=pVec[nIndex];}
inline  void	VEC_GetVal(nm64s* pVec, int nIndex, int64b& nVal) { nVal=pVec[nIndex];}

void			VEC_GetVal(nm1*   pVec, int nIndex, uint1b &nVal);
void			VEC_GetVal(nm2u*  pVec, int nIndex, uint2b &nVal);
void			VEC_GetVal(nm4u*  pVec, int nIndex, uint4b &nVal);
void			VEC_GetVal(nm8u*  pVec, int nIndex, uint8b &nVal);
void			VEC_GetVal(nm16u* pVec, int nIndex, uint16b &nVal);
inline  void	VEC_GetVal(nm32u* pVec, int nIndex, uint32b&  nVal) { nVal=pVec[nIndex];}
inline  void	VEC_GetVal(nm64u* pVec, int nIndex, uint64b&  nVal) { nVal=pVec[nIndex];}

void			nmppsGetVal_1  (nm1*   pVec, int nIndex, int1b &nVal);
void			nmppsGetVal_2s (nm2s*  pVec, int nIndex, int2b &nVal);
void			nmppsGetVal_4s (nm4s*  pVec, int nIndex, int4b &nVal);
void			nmppsGetVal_8s (nm8s*  pVec, int nIndex, int8b &nVal);
void			nmppsGetVal_16s(nm16s* pVec, int nIndex, int16b &nVal);
inline  void	nmppsGetVal_32s(nm32s* pVec, int nIndex, int32b& nVal) { nVal=pVec[nIndex];}
inline  void	nmppsGetVal_64s(nm64s* pVec, int nIndex, int64b& nVal) { nVal=pVec[nIndex];}
                
void			nmppsGetVal_1  (nm1*   pVec, int nIndex, uint1b &nVal);
void			nmppsGetVal_2s (nm2u*  pVec, int nIndex, uint2b &nVal);
void			nmppsGetVal_4s (nm4u*  pVec, int nIndex, uint4b &nVal);
void			nmppsGetVal_8s (nm8u*  pVec, int nIndex, uint8b &nVal);
void			nmppsGetVal_16s(nm16u* pVec, int nIndex, uint16b &nVal);
inline  void	nmppsGetVal_32s(nm32u* pVec, int nIndex, uint32b&  nVal) { nVal=pVec[nIndex];}
inline  void	nmppsGetVal_64s(nm64u* pVec, int nIndex, uint64b&  nVal) { nVal=pVec[nIndex];}

    //! \}

//*****************************************************************************

    /**
    \defgroup VEC_GetVal_ret VEC_GetVal(return)
    \ingroup vSupport
    \brief
        \ru Извлекает значение элемента вектора. 
        \en Extracts the vec element value. 
		\~
    \param pVec     
        \ru Вектор. 
        \en Vector. 
		\~
    \param nIndex   
        \ru Позиция элемента. 
        \en Position of the element. 
		\~
    \return \e 
        \ru Значение элемента. 
        \en Value of the element. 
		\~
    \par
    \xmlonly
        <testperf> 
             <param> pVec </param> <values> L G </values>
             <param> nIndex  </param> <values> 0 </values>
             <size> 1 </size>
        </testperf>
    \endxmlonly
    
    */
    //! \{
int2b			VEC_GetVal(nm2s*  pVec, int nIndex);
int4b			VEC_GetVal(nm4s*  pVec, int nIndex);
int8b			VEC_GetVal(nm8s*  pVec, int nIndex);
int16b			VEC_GetVal(nm16s* pVec, int nIndex);
inline  int32b	VEC_GetVal(nm32s* pVec, int nIndex) {return pVec[nIndex];}

uint1b			VEC_GetVal(nm1*   pVec, int nIndex);
uint2b			VEC_GetVal(nm2u*  pVec, int nIndex);
uint4b			VEC_GetVal(nm4u*  pVec, int nIndex);
uint8b			VEC_GetVal(nm8u*  pVec, int nIndex);
uint16b			VEC_GetVal(nm16u* pVec, int nIndex);
inline  uint32b	VEC_GetVal(nm32u* pVec, int nIndex) {return pVec[nIndex];}
    //! \}


	inline unsigned VEC_Size32(nm8s*  ,unsigned size) {return size/4;}
	inline unsigned VEC_Size32(nm16s* ,unsigned size) {return size/2;}
	inline unsigned VEC_Size32(nm32s* ,unsigned size) {return size;  }
	inline unsigned VEC_Size32(nm64s* ,unsigned size) {return size*2;}

	inline unsigned VEC_Size32(nm8u*  ,unsigned size) {return size/4;}
	inline unsigned VEC_Size32(nm16u* ,unsigned size) {return size/2;}
	inline unsigned VEC_Size32(nm32u* ,unsigned size) {return size;  }
	inline unsigned VEC_Size32(nm64u* ,unsigned size) {return size*2;}

#endif




