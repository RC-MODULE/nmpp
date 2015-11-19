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

#ifdef __cplusplus
		extern "C" {
#endif
//#include "nmtype.h"

   

//*****************************************************************************

    /**
    \defgroup nmppsAddr_ nmppsAddr_
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
            (ptr+index), а на NM как вызов функции nmppsAddr_. 
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
/*		
__INLINE__ nm1* nmppsAddr_1*(nm1*  pVec, int nIndex){	return (nm1*)((int*)pVec+(nIndex>>5));}
__INLINE__ nm2s* nmppsAddr_2s(nm2s*  pVec, int nIndex){	return (nm2s*)((int*)pVec+(nIndex>>4));}
__INLINE__ nm4s* nmppsAddr_4s(nm4s*  pVec, int nIndex){	return (nm4s*)((int*)pVec+(nIndex>>3));}

nm8s*  nmppsAddr_(const nm8s*  pVec, int nIndex);
nm16s* nmppsAddr_16s(nm16s* pVec, int nIndex);
nm32s* nmppsAddr_32s(nm32s* pVec, int nIndex);

__INLINE__ nm64s* nmppsAddr_64s(nm64s* pVec, int nIndex) {return pVec+nIndex;}
#ifdef __NM__
__INLINE__ nm8u*  nmppsAddr_(const nm8u*  pVec, int nIndex) {return (nm8u*)nmppsAddr_8s((nm8s*)  pVec, nIndex);}
__INLINE__ nm16u* nmppsAddr_16u(nm16u* pVec, int nIndex) {return (nm16u*)nmppsAddr_16s((nm16s*)  pVec, nIndex);}
#else 
__INLINE__ nm8u*  nmppsAddr_(const nm8u*  pVec, int nIndex) {return (nm8u*)pVec+nIndex;}
__INLINE__ nm16u* nmppsAddr_16u(nm16u* pVec, int nIndex) {return pVec+nIndex;}
#endif
__INLINE__ nm32u* nmppsAddr_32u(nm32u* pVec, int nIndex) {return pVec+nIndex;}
__INLINE__ nm64u* nmppsAddr_64u(nm64u* pVec, int nIndex) {return pVec+nIndex;}
*/
/*
__INLINE__ nm64u* nmppsAddr_1 (nm1*   pVec, int nIndex) {return (nm64u*)pVec+(nIndex>>6);}
__INLINE__ nm64u* nmppsAddr_2s(nm2s*  pVec, int nIndex) {return (nm64u*)pVec+(nIndex>>5);}
__INLINE__ nm64u* nmppsAddr_4s(nm4s*  pVec, int nIndex) {return (nm64u*)pVec+(nIndex>>4);}
__INLINE__ nm64u* nmppsAddr_8s(nm8s*  pVec, int nIndex) {return (nm64u*)pVec+(nIndex>>3);}
__INLINE__ nm64u* nmppsAddr_16s(nm16s* pVec, int nIndex) {return (nm64u*)pVec+(nIndex>>2);}
__INLINE__ nm64u* nmppsAddr_32s(nm32s* pVec, int nIndex) {return (nm64u*)pVec+(nIndex>>1);}
__INLINE__ nm64u* nmppsAddr_64s(nm64s* pVec, int nIndex) {return (nm64u*)pVec+nIndex;}

__INLINE__ nm64u* nmppsAddr_8u(nm8u*  pVec, int nIndex) {return (nm64u*)pVec+(nIndex>>3);}
__INLINE__ nm64u* nmppsAddr_16u(nm16u* pVec, int nIndex) {return (nm64u*)pVec+(nIndex>>2);}
__INLINE__ nm64u* nmppsAddr_32u(nm32u* pVec, int nIndex) {return (nm64u*)pVec+(nIndex>>1);}
__INLINE__ nm64u* nmppsAddr_64u(nm64u* pVec, int nIndex) {return (nm64u*)pVec+nIndex;}
*/

 __INLINE__ nm1  * nmppsAddr_1  (nm1*   pVec, int nIndex) {return (nm1*  )((nm64u*)pVec+(nIndex>>6));}
 __INLINE__ nm2s * nmppsAddr_2s (nm2s*  pVec, int nIndex) {return (nm2s* )((nm64u*)pVec+(nIndex>>5));}
 __INLINE__ nm4s * nmppsAddr_4s (nm4s*  pVec, int nIndex) {return (nm4s* )((nm64u*)pVec+(nIndex>>4));}
 __INLINE__ nm8s * nmppsAddr_8s (nm8s*  pVec, int nIndex) {return (nm8s* )((nm64u*)pVec+(nIndex>>3));}
 __INLINE__ nm16s* nmppsAddr_16s(nm16s* pVec, int nIndex) {return (nm16s*)((nm64u*)pVec+(nIndex>>2));}
 __INLINE__ nm32s* nmppsAddr_32s(nm32s* pVec, int nIndex) {return (nm32s*)((nm64u*)pVec+(nIndex>>1));}
 __INLINE__ nm64s* nmppsAddr_64s(nm64s* pVec, int nIndex) {return (nm64s*)((nm64u*)pVec+nIndex)     ;}
                                                       
 __INLINE__ nm8u * nmppsAddr_8u (nm8u*  pVec, int nIndex) {return (nm8u* )((nm64u*)pVec+(nIndex>>3));}
 __INLINE__ nm16u* nmppsAddr_16u(nm16u* pVec, int nIndex) {return (nm16u*)((nm64u*)pVec+(nIndex>>2));}
 __INLINE__ nm32u* nmppsAddr_32u(nm32u* pVec, int nIndex) {return (nm32u*)((nm64u*)pVec+(nIndex>>1));}
 __INLINE__ nm64u* nmppsAddr_64u(nm64u* pVec, int nIndex) {return (nm64u*)((nm64u*)pVec+nIndex     );}


    //! \}

//*****************************************************************************

    /**
    \defgroup nmppsSetVal_ nmppsSetVal_
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

void		nmppsPut_1 (nm1*  pVec,  int nIndex,  int1b  nVal);
void		nmppsPut_2s(nm2s* pVec,  int nIndex,  int2b  nVal);
void		nmppsPut_4s(nm4s* pVec,  int nIndex,  int4b  nVal);
void		nmppsPut_8s(nm8s* pVec,  int nIndex,  int8b  nVal);
void		nmppsPut_16s(nm16s* pVec, int nIndex,  int16b nVal);
__INLINE__ void nmppsPut_32s(nm32s* pVec, int nIndex,  int32b nVal)	{pVec[nIndex]=nVal;}
__INLINE__ void nmppsPut_64s(nm64s* pVec, int nIndex,  int64b nVal)	{pVec[nIndex]=nVal;}

__INLINE__ void	nmppsPut_2u(nm2u* pVec,  int nIndex, uint2b  nVal)   	{nmppsPut_2s((nm2s*)pVec,nIndex,(int2b)nVal);}
__INLINE__ void	nmppsPut_4u(nm4u* pVec,  int nIndex, uint4b  nVal)   	{nmppsPut_4s((nm4s*)pVec,nIndex,(int4b)nVal);}
__INLINE__ void	nmppsPut_8u(nm8u* pVec,  int nIndex, uint8b nVal)		{nmppsPut_8s((nm8s*)pVec,nIndex,(int8b)nVal);}
__INLINE__ void	nmppsPut_16u(nm16u* pVec, int nIndex, uint16b nVal)   	{nmppsPut_16s((nm16s*)pVec,nIndex,(int16b)nVal);}
__INLINE__ void nmppsPut_32u(nm32u* pVec, int nIndex, uint32b nVal)	{pVec[nIndex]=nVal;}
__INLINE__ void nmppsPut_64u(nm64u* pVec, int nIndex, uint64b nVal)	{pVec[nIndex]=nVal;}

    
    //! \}

//*****************************************************************************

    /**
    \defgroup nmppsGetVal_ nmppsGetVal_
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
		
void			nmppsGetVal_1  (nm1*   pVec, int nIndex, int1b *nVal);
void			nmppsGetVal_2s (nm2s*  pVec, int nIndex, int2b *nVal);
void			nmppsGetVal_4s (nm4s*  pVec, int nIndex, int4b *nVal);
void			nmppsGetVal_8s (nm8s*  pVec, int nIndex, int8b *nVal);
void			nmppsGetVal_16s(nm16s* pVec, int nIndex, int16b *nVal);
__INLINE__ void		nmppsGetVal_32s(nm32s* pVec, int nIndex, int32b* nVal) { *nVal=pVec[nIndex];}
__INLINE__ void		nmppsGetVal_64s(nm64s* pVec, int nIndex, int64b* nVal) { *nVal=pVec[nIndex];}
                

void			nmppsGetVal_2u (nm2u*  pVec, int nIndex, uint2b *nVal);
void			nmppsGetVal_4u (nm4u*  pVec, int nIndex, uint4b *nVal);
void			nmppsGetVal_8u (nm8u*  pVec, int nIndex, uint8b *nVal);
void			nmppsGetVal_16u(nm16u* pVec, int nIndex, uint16b *nVal);
__INLINE__  void	nmppsGetVal_32u(nm32u* pVec, int nIndex, uint32b*  nVal) { *nVal=pVec[nIndex];}
__INLINE__  void	nmppsGetVal_64u(nm64u* pVec, int nIndex, uint64b*  nVal) { *nVal=pVec[nIndex];}

    //! \}

//*****************************************************************************

    /**
    \defgroup nmppsGetVal_ret_ nmppsGetVal_(return)
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
int2b			nmppsGet_2s(nm2s*  pVec, int nIndex);
int4b			nmppsGet_4s(nm4s*  pVec, int nIndex);
int8b			nmppsGet_8s(nm8s*  pVec, int nIndex);
int16b			nmppsGet_16s(nm16s* pVec, int nIndex);
__INLINE__ int32b	nmppsGet_32s(nm32s* pVec, int nIndex) {return pVec[nIndex];}

uint1b			nmppsGet_1(nm1*   pVec, int nIndex);
uint2b			nmppsGet_2u(nm2u*  pVec, int nIndex);
uint4b			nmppsGet_4u(nm4u*  pVec, int nIndex);
uint8b			nmppsGet_8u(nm8u*  pVec, int nIndex);
uint16b			nmppsGet_16u(nm16u* pVec, int nIndex);
__INLINE__ uint32b	nmppsGet_32u(nm32u* pVec, int nIndex) {return pVec[nIndex];}
    //! \}

/*
	__INLINE__ unsigned nmppsSize32_8s(nm8s*  ,unsigned size) {return size/4;}
	__INLINE__ unsigned nmppsSize32_16s(nm16s* ,unsigned size) {return size/2;}
	__INLINE__ unsigned nmppsSize32_32s(nm32s* ,unsigned size) {return size;  }
	__INLINE__ unsigned nmppsSize32_64s(nm64s* ,unsigned size) {return size*2;}

	__INLINE__ unsigned nmppsSize32_8u(nm8u*  ,unsigned size) {return size/4;}
	__INLINE__ unsigned nmppsSize32_16u(nm16u* ,unsigned size) {return size/2;}
	__INLINE__ unsigned nmppsSize32_32u(nm32u* ,unsigned size) {return size;  }
	__INLINE__ unsigned nmppsSize32_64u(nm64u* ,unsigned size) {return size*2;}
*/

#ifdef __cplusplus
		};
#endif

#endif




