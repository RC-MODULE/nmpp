//------------------------------------------------------------------------
//
//  $Workfile:: vInit. $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:02 $
//
//! \if file_doc
//!
//! \file   vInit.h
//! \author Сергей Мушкаев
//! \brief  Определение функций инициализации для векторов.
//!
//! \endif
//!
//------------------------------------------------------------------------
#ifndef _VINIT_H_INCLUDED_
#define _VINIT_H_INCLUDED_


    /**
    \defgroup VEC_Fill VEC_Fill
    \ingroup vInit
    \brief
        \ru Функция инициализации элементов массива постоянным значением. 
        \en Function of array initialization with a constant value.  
    
		\~
    
	\f[
        pVec[i]  =  nVal, 
    \f]
    
	\f[
        i = \overline{0 \ldots nSize-1}
    \f]
    
    \param nSize    
        \ru Размер вектора в элементах. 
        \en Size of vec in elements. 
		\~
    \param nVal     
        \ru Константа. Диапазон значений nVal должен соответсвовать типу результирующего вектора. 
        \en A constant. Range of nVal must correspond to type of result vec
		\~
    \retval pVec    
        \ru Результирующий вектор. 
        \en The result vec. 
		\~
    \return \e void 
     
        
    \par
    \xmlonly
        <testperf>
	        <param> pVec </param> <values> L G </values>
	        <param> nVal </param> <values> n </values>
	        <param> nSize  </param> <values> 10240 </values>
        </testperf>
        <testperf>
	        <param> pVec </param> <values> G </values>
	        <param> nVal </param> <values> n </values>
	        <param> nSize  </param> <values> 8 128 1024 10240 </values>
        </testperf>
    \endxmlonly
    */
    //! \{
void VEC_Fill(nm8s* pVec,  int8b nVal, int nSize);
void VEC_Fill(nm16s* pVec, int16b nVal, int nSize);
void VEC_Fill(nm32s* pVec, int32b nVal, int nSize);
void VEC_Fill(nm64s* pVec, int64b* nVal, int nSize); 
inline void VEC_Fill(nm64s* pVec, int64b  nVal, int nSize)  {VEC_Fill((nm64s*) pVec, (int64b*)&nVal, nSize);}

inline void VEC_Fill(nm8u* pVec,  uint8b nVal, int nSize)	{VEC_Fill((nm8s*) pVec,  (int8b)nVal, nSize);}
inline void VEC_Fill(nm16u* pVec, uint16b nVal, int nSize)	{VEC_Fill((nm16s*) pVec, (int16b)nVal, nSize);}
inline void VEC_Fill(nm32u* pVec, uint32b nVal, int nSize)	{VEC_Fill((nm32s*) pVec, (int32b)nVal, nSize);}
inline void VEC_Fill(nm64u* pVec, uint64b  nVal, int nSize)	{VEC_Fill((nm64s*) pVec, (int64b)nVal, nSize);}
inline void VEC_Fill(nm64u* pVec, uint64b* nVal, int nSize)	{VEC_Fill((nm64s*) pVec, (int64b*)nVal, nSize);}
    //! \}


//*****************************************************************************

    /**
    \defgroup VEC_Rand VEC_Rand
    \ingroup vInit
    \brief
        \ru Инициализация массива случайными числами. 
        \en Initialization of an array with random numbers. 
		\~
    \param nSize		
        \ru Размер вектора. 
        \en Vector size. 
		\~
    \param nRandomize    
        \ru Произвольное число для инициализации 
                            генератора случайных чисел. 
        \en Arbitrary number for initialization 
                            of a random-number generator. 
		\~
    \retval pDstVec     
        \ru Результирующий вектор. 
        \en Result vec. 
		\~
    \return \e void
    
    \par
    \xmlonly
        <testperf> 
             <param> pDstVec </param> <values> L G </values>
             <param> nRandomize </param> <values> 1 </values>
             <param> nSize </param> <values> 10240 </values>
        </testperf>
        <testperf> 
             <param> pDstVec </param> <values> G </values>
             <param> nRandomize </param> <values> 1 </values>
             <param> nSize </param> <values> 8 128 1024 10240 </values>
        </testperf>
    \endxmlonly
    */
    //! \{
/**
	/ru  Инициализация массива 32-разрядными случайными числами. 
	/en Random initialization of 32-bit buffer
	/~
*/
void VEC_Rand(nm32u* pDstVec, int nSize, unsigned nRandomize = 1);
inline void VEC_Rand(nm8s* pDstVec,  int nSize, unsigned nRandomize = 1) {VEC_Rand((nm32u*)pDstVec,  nSize>>2, nRandomize);}
inline void VEC_Rand(nm16s* pDstVec, int nSize, unsigned nRandomize = 1) {VEC_Rand((nm32u*)pDstVec,  nSize>>1, nRandomize);}
inline void VEC_Rand(nm32s* pDstVec, int nSize, unsigned nRandomize = 1) {VEC_Rand((nm32u*)pDstVec,  nSize, nRandomize);}
//inline void VEC_Rand(nm64s* pDstVec, int nSize, unsigned nRandomize = 1) {VEC_Rand((nm32u*)pDstVec,  nSize<<1, nRandomize);}
inline void VEC_Rand(nm8u* pDstVec,  int nSize, unsigned nRandomize = 1) {VEC_Rand((nm32u*)pDstVec,  nSize>>2, nRandomize);}
inline void VEC_Rand(nm16u* pDstVec, int nSize, unsigned nRandomize = 1) {VEC_Rand((nm32u*)pDstVec,  nSize>>1, nRandomize);}
inline void VEC_Rand(nm64u* pDstVec, int nSize, unsigned nRandomize = 1) {VEC_Rand((nm32u*)pDstVec,  nSize<<1, nRandomize);}


/**
	/ru  Инициализация массива 64-разрядными случайными числами. 
	/en Random initialization of 64-bit buffer
	/~

*/
void VEC_Rand(nm64s* pDstVec, int nSize, int nRandomize = 1);
    //! \}

	

//*****************************************************************************

    /**
    \defgroup VEC_Rand VEC_Rand
    \ingroup vInit
    \brief 
        \ru Генерация случайного числа с равномерным раcпределением.
        \en Random number generation with uniform distribution.

		\~
	  \~
    \param nMin		
        \ru Минимальное возможное значение случайного числа.
        \en Minimal value for random number.
		\~
    \param nMax    
        \ru Максимальное возможное значение случайного числа.
        \en Maximal value for random number.
		\~
    \param nDivisible     
        \ru Значение, которому будет кратно случайное число.
        \en Random number will be divisible by this value.
		\~
    \return \e int
		\ru Случайное число в диапазоне либо [nMin, nMax]. Для функции без параметров
			данный диапазон [-2^31; 2^31-1].
        \en Random number in range [nMin, nMax]. For function without parameters
			this range is [-2^31; 2^31-1].

		\~
    \par
    \xmlonly
        <testperf>
          <param> nMin </param> <values> 0 128 		</values>
          <param> nMax  </param> <values> 10240 </values>
          <param> nDivisible </param> <values> 1 </values>
          <size> 1 </size>
        </testperf>
        <testperf>
          <param> nMin </param> <values> 128 		</values>
          <param> nMax  </param> <values> 1024 10240 </values>
          <param> nDivisible </param> <values> 1 </values>
          <size> 1 </size>
        </testperf>
        <testperf>
          <param> nMin </param> <values> 128 		</values>
          <param> nMax  </param> <values> 10240 </values>
          <param> nDivisible </param> <values> 1 2 </values>
          <size> 1 </size>
        </testperf>

    \endxmlonly
    */
    //! \{
int VEC_Rand(int nMin, int nMax, int nDivisible);
int VEC_Rand(int nMin, int nMax);
int VEC_Rand();
    //! \}

	
//*****************************************************************************

    /**
    \defgroup VEC_Ramp VEC_Ramp
    \ingroup vInit
    \brief
        \ru Инициализация массива элементами арифметической прогрессии. 
        \en Initialization of an array by ramped numbers. 
    
		\~
    
	\f[
        pVec[i] = nOffset + nSlope \cdot i
    \f]
    
	\f[
        i = \overline{0 \ldots nSize-1}
    \f]
    
    \~
    \param nOffset		
        \ru Первый член арифметической прогрессии.
        \en Init value.
		\~
    \param nSlope		
        \ru Разность арифметической прогрессии.
        \en Common difference.
		\~
    \param nSize		
        \ru Размер вектора. 
        \en Vector size. 
		\~
    \retval pVec     
        \ru Результирующий массив. 
        \en Result array. 
		\~
    \return \e void


    \par
    \xmlonly
        <testperf> 
             <param> pVec </param> <values> L G </values>
             <param> nOffset </param> <values> 10 </values>
             <param> nSlope </param> <values> 2 </values>
             <param> nSize </param> <values> 10240 </values>
        </testperf>
        <testperf> 
             <param> pVec </param> <values> G </values>
             <param> nOffset </param> <values> -10 10 </values>
             <param> nSlope </param> <values> 2 </values>
             <param> nSize </param> <values> 10240 </values>
        </testperf>
        <testperf> 
             <param> pVec </param> <values> G </values>
             <param> nOffset </param> <values> 10 </values>
             <param> nSlope </param> <values> -2 2 </values>
             <param> nSize </param> <values> 10240 </values>
        </testperf>
        <testperf> 
             <param> pVec </param> <values> G </values>
             <param> nOffset </param> <values> 10 </values>
             <param> nSlope </param> <values> 2 </values>
             <param> nSize </param> <values> 8 128 1024 10240 </values>
        </testperf>
    \endxmlonly
    */
    //! \{
void VEC_Ramp(nm8s* pVec,  int8b nOffset,  int8b nSlope, int nSize);
void VEC_Ramp(nm16s* pVec, int16b nOffset, int16b nSlope, int nSize);
void VEC_Ramp(nm32s* pVec, int32b nOffset, int32b nSlope, int nSize);
void VEC_Ramp(nm64s* pVec, int64b nOffset, int64b nSlope, int nSize);
    //! \}

//*****************************************************************************

    /**
    \defgroup VEC_Cnv VEC_Cnv
    \ingroup vInit
    \brief
        \ru Изменение разрядности элементов вектора. 
        \en Change of vec elements word-length. 
    
		\~
        \ru Преобразование знаковых данных к меньшей разрядности осуществляется 
	        отбрасыванием старших битов.
	        Преобразование знаковых данных к большей разрядности осуществляется 
	        c распространением влево старшего (знакового) бита.
            Преобразование беззнаковых данных к большей разрядности осуществляется 
	        добавлением слева старших нулевых битов. 
        \en Signed data are converted to lesser word-length is made by means of 
            the most significant bits truncation.
            Signed data are converted to greater word-length is made with
            left expansion of the most significant (sign) bit.
            Unsigned data are converted to greater word-length is made by means of
            addition of the most significant zero bits on the left. 
		\~
    \param pSrcVec  
        \ru Входной вектор. 
        \en Input vec. 
		\~
    \param nSize    
        \ru Размер векторов в элементах. 
        \en Vector size in elements. 
		\~
    \retval pDstVec 
        \ru Результирующий вектор. 
        \en The result vec. 
		\~
    \return \e void 
    
        
    \par
    \xmlonly
        <testperf> 
             <param> pSrcVec </param> <values> L G </values>
             <param> pDstVec </param> <values> L G </values>
             <param> nSize </param> <values> 10240 </values>
        </testperf>
        <testperf> 
             <param> pSrcVec </param> <values> L </values>
             <param> pDstVec </param> <values> G </values>
             <param> nSize </param> <values> 8 128 1024 10240 </values>
        </testperf>
    \endxmlonly



    */
	//todo Impelenment NM versin of void VEC_Cnv(nm32s *pSrcVec, nm4s *pDstVec, int nSize);
    //! \{

/**
 \restr nSize =[32*64,32*64*2,32*64*3,....]
*/
void VEC_Cnv(nm1* pSrcVec, nm2s* pDstVec, int nSize);
/**
 \restr nSize =[32*64,32*64*2,32*64*3,....]
*/
void VEC_Cnv(nm1* pSrcVec, nm2u* pDstVec, int nSize);

void VEC_Cnv(nm8s* pSrcVec, nm4s*  pDstVec, int nSize);
void VEC_Cnv(nm8s* pSrcVec, nm16s* pDstVec, int nSize);
void VEC_Cnv(nm8s* pSrcVec, nm32s* pDstVec, int nSize);
void VEC_Cnv(nm8s* pSrcVec, nm64s* pDstVec, int nSize);
void VEC_Cnv(nm8u* pSrcVec, nm16u* pDstVec, int nSize);
void VEC_Cnv(nm8u* pSrcVec, nm32u* pDstVec, int nSize);
void VEC_Cnv(nm8u* pSrcVec, nm64u* pDstVec, int nSize);

void VEC_Cnv(nm16s* pSrcVec, nm4s* pDstVec, int nSize);
void VEC_Cnv(nm16s* pSrcVec, nm8s* pDstVec, int nSize);
void VEC_Cnv(nm16s* pSrcVec, nm32s* pDstVec, int nSize);
void VEC_Cnv(nm16s* pSrcVec, nm64s* pDstVec, int nSize);
void VEC_Cnv(nm16u* pSrcVec, nm32u* pDstVec, int nSize);
void VEC_Cnv(nm16u* pSrcVec, nm64u* pDstVec, int nSize);

void VEC_Cnv(nm32s* pSrcVec, nm8s* pDstVec, int nSize);
void VEC_Cnv(nm32s* pSrcVec, nm16s* pDstVec, int nSize);
void VEC_Cnv(nm32s* pSrcVec, nm64s* pDstVec, int nSize);
void VEC_Cnv(nm32u* pSrcVec, nm64u* pDstVec, int nSize);

void VEC_Cnv(nm64s* pSrcVec, nm32s* pDstVec, int nSize);
void VEC_Cnv(nm64s* pSrcVec, nm16s* pDstVec, int nSize);
    //! \}
//void VEC_Cnv(nm32s *pSrcVec, nm4s *pDstVec, int nSize);




	
//*****************************************************************************

    /**
    \defgroup VEC_Copy VEC_Copy
    \ingroup vInit
    \brief
        \ru Копирование вектора. 
        \en Vector copying. 
    
		\~
    
	\f[
        pDstVec[i]  =  pSrcVec[i],
    \f]
    
	\f[
        i = \overline{0 \ldots nSize-1}
    \f]
    
    \param pSrcVec  
        \ru Входной вектор. 
        \en Input vec. 
		\~
    \param nSize    
        \ru Размер векторов в элементах. 
        \en Vector size in elements. 
		\~
    \retval pDstVec 
        \ru Результирующий вектор. 
        \en The result vec. 
		\~
    \return \e void
    
    \par
    \xmlonly
        <testperf> 
             <param> pSrcVec </param> <values> L G </values>
             <param> pDstVec </param> <values> L G </values>
             <param> nSize </param> <values> 10240 </values>
        </testperf>
        <testperf> 
             <param> pSrcVec </param> <values> L </values>
             <param> pDstVec </param> <values> G </values>
             <param> nSize </param> <values> 8 128 1024 10240 </values>
        </testperf>
    \endxmlonly
    
        */
    //! \{
void VEC_Copy( nm8s*  pSrcVec, nm8s*  pDstVec, int nSize);
void VEC_Copy( nm16s* pSrcVec, nm16s* pDstVec, int nSize);
void VEC_Copy( nm32s* pSrcVec, nm32s* pDstVec, int nSize);
void VEC_Copy( nm64s* pSrcVec, nm64s* pDstVec, int nSize);

inline void VEC_Copy( nm8u*  pSrcVec, nm8u*  pDstVec, int nSize) { VEC_Copy(( nm8s*)  pSrcVec, (nm8s*)  pDstVec,  nSize);}
inline void VEC_Copy( nm16u* pSrcVec, nm16u* pDstVec, int nSize) { VEC_Copy(( nm16s*) pSrcVec, (nm16s*) pDstVec,  nSize);}
inline void VEC_Copy( nm32u* pSrcVec, nm32u* pDstVec, int nSize) { VEC_Copy(( nm32s*) pSrcVec, (nm32s*) pDstVec,  nSize);}
inline void VEC_Copy( nm64u* pSrcVec, nm64u* pDstVec, int nSize) { VEC_Copy(( nm64s*) pSrcVec, (nm64s*) pDstVec,  nSize);}

    //! \}



//*****************************************************************************

    /**
    \defgroup VEC_Copyua VEC_Copyua
    \ingroup vInit
    \brief
        \ru Копирование вектора с невыровненной байтовой позиции в выровненную. 
        \en Copying a vec from an unaligned byte position to aligned one. 
    
		\~
    
	\f[
        pDstVec[i] = pSrcVec[nSrcOffset+i]
    \f]
    
	\f[
        i = \overline{0 \ldots nSize-1}
    \f]

	\ru Позиция байта считается выровненной если она совпадает с границей 64р. слов в памяти. 
    \en Position is defined as aligned if it points to 64-bit words boundary in memory.
	
		\~
	\~
	\param pSrcVec      
        \ru Входной вектор. 
        \en Input vec. 
		\~
    \param pDstVec      
        \ru Результирующий вектор. 
        \en Output vec. 
		\~
    \param nSrcOffset  
        \ru Смещение в элементах относительно начала вектора. nSrcOffset Может принимать любое значение.
        \en Shift in elements relatively to the origin of the vec. nSrcOffset may be any. 
		\~
    \param nSize   
        \ru Кол-во копируемых элементов. 
        \en Number of elements being copied. 
		\~
    \return \e void
    
    \par
    \xmlonly
        <testperf> 
            <param> pSrcVec    </param> <values> L G </values>
            <param> pDstVec    </param> <values> L G </values>
            <param> nSrcOffset </param> <values> 3 </values>
            <param> nSize </param> <values> 10240 </values>
        </testperf>
        <testperf> 
            <param> pSrcVec    </param> <values> L </values>
            <param> pDstVec    </param> <values> G </values>
            <param> nSrcOffset </param> <values> 0 3 7 </values>
            <param> nSize </param> <values> 10240 </values>
        </testperf>
        <testperf> 
            <param> pSrcVec    </param> <values> L </values>
            <param> pDstVec    </param> <values> G </values>
            <param> nSrcOffset </param> <values> 3 </values>
            <param> nSize </param> <values> 8 128 1024 10240 </values>
        </testperf>
    \endxmlonly

    */
    //! \{
void VEC_Copyua(nm8s* pSrcVec, int nSrcOffset, nm8s* pDstVec,  int nSize);
    //! \}

//*****************************************************************************

    /**
    \defgroup VEC_Swap VEC_Swap
    \ingroup vInit
    \brief
        \ru Перестановка двух векторов. 
        \en Swap of two vectors. 
    
 
		\~
    \param pSrcVec1  
        \ru Первый входной вектор. 
        \en The first input vec. 
		\~
    \param pSrcVec2  
        \ru Второй входной вектор. 
        \en The second input vec. 
		\~
    \param nSize     
        \ru Размер векторов в элементах. 
        \en Vector size in elements. 
		\~
    \return \e void
    
        
    \par
    \xmlonly
        <testperf> 
             <param> pSrcVec1 </param> <values> L G </values>
             <param> pSrcVec2 </param> <values> L G </values>
             <param> nSize </param> <values> 10240 </values>
        </testperf>
        <testperf> 
             <param> pSrcVec1 </param> <values> L </values>
             <param> pSrcVec2 </param> <values> G </values>
             <param> nSize </param> <values> 8 128 1024 10240 </values>
        </testperf>
    \endxmlonly
    
    */
    //! \{
void VEC_Swap(nm64s* pSrcVec1, nm64s* pSrcVec2, int nSize);
    //! \}

#endif // _INIT_H_INCLUDED_



