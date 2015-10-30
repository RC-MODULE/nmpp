//------------------------------------------------------------------------
//
//  $Workfile:: vArithmetics.h             $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.2 $      $Date: 2005/06/23 15:15:15 $
//
//! \if file_doc
//!
//! \file   vArithm.h
//! \author Сергей Мушкаев
//! \brief  Определение базовых арифметических функций над векторами
//!
//! \endif
//!
//------------------------------------------------------------------------

#ifndef _VARITHM_H_INCLUDED_
#define _VARITHM_H_INCLUDED_


    /**
    \defgroup nmppsAbs nmppsAbs
    \ingroup vArithmetics
    \brief
        \ru Вычисление абсолютных значений для элементов вектора. 
        \en Calculation of absolute values for vec elements. 
    
		\~
    
	\f[ 
        pDstVec[i]  =  abs \{  pSrcVec[i] \},
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
    
        
    \restr
        \ru Значения элементов вектора не должны быть равны минимальному 
            значению для соответствующего типа (т.е. -128, -2^15 и т.д).
            В противном случае, абсолютное значение для таких элементов
            вычисляется неверно, давая на выходе то же самое число.
        \en Values of elements must not be equal
            to the minimum value of element type. (i.e. -128, -2^15 ...)
            Otherwise absolute values for such elements
            are calculated incorrectly resulting to the same value
            in the output vec.
            
		\~
    \par
    \xmlonly
        <testperf> 
             <param> pSrcVec </param> <values> L G </values>
             <param> pDstVec </param> <values> L G </values>
             <param> nSize   </param> <values> 10240 </values>
        </testperf>
        <testperf> 
             <param> pSrcVec </param> <values> L </values>
             <param> pDstVec </param> <values> G </values>
             <param> nSize   </param> <values> 8 128 1024 10240 </values>
        </testperf>
    \endxmlonly
    
    */
    //! \{
void nmppsAbs_8s(nm8s* pSrcVec, nm8s* pDstVec, int nSize);
void nmppsAbs_16s(nm16s* pSrcVec, nm16s* pDstVec, int nSize);
void nmppsAbs_32s(nm32s* pSrcVec, nm32s* pDstVec, int nSize);
void nmppsAbs_64s(nm64s* pSrcVec, nm64s* pDstVec, int nSize);
    //! \}
void nmppsAbs(nm4s* pSrcVec, nm4s* pDstVec, int nSize);


 /**
    \defgroup nmppsAbs1 nmppsAbs1
    \ingroup vArithmetics
    \brief
        \ru Функция логического вычесления модулей элементов вектора. 
        \en Logical-based calculation of absolute values for vec elements. 
    
		\~
  
	\f[
        pDstVec[i]  =  \{ \begin{array}{*{20}c}
            pSrcVec[i],    &  if &  pSrcVec[i] \ge 0  \\
            -pSrcVec[i]-1,     &  if &  pSrcVec[i] < 0  \\
        \end{array}
    \f]
    
	\f[ i = \overline{0 \ldots nSize-1} \f]
    
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
             <param> nSize   </param> <values> 10240 </values>
        </testperf>
        <testperf> 
             <param> pSrcVec </param> <values> L </values>
             <param> pDstVec </param> <values> G </values>
             <param> nSize   </param> <values> 8 128 1024 10240 </values>
        </testperf>
    \endxmlonly
    
    */
    //! \{
void nmppsAbs1(nm4s* pSrcVec, nm4s* pDstVec, int nSize);
void nmppsAbs1(nm8s* pSrcVec, nm8s* pDstVec, int nSize);
void nmppsAbs1(nm16s* pSrcVec, nm16s* pDstVec, int nSize);
void nmppsAbs1(nm32s* pSrcVec, nm32s* pDstVec, int nSize);
void nmppsAbs1(nm64s* pSrcVec, nm64s* pDstVec, int nSize);
    //! \}


//*****************************************************************************
    
    /**
    \defgroup nmppsNeg nmppsNeg
    \ingroup vArithmetics
    \brief
        \ru Изменение знака элементов вектора на противоположный. 
        \en Change of the vec element sign for the opposite one.   
    
    
		\~
    
	\f[ 
        pDstVec[i]  =  - pDstVec[i]
    \f]
    
	\f[ i = \overline{0 \ldots nSize-1} \f]
    
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
void nmppsNeg(nm8s* pSrcVec, nm8s* pDstVec, int nSize);
void nmppsNeg(nm16s* pSrcVec, nm16s* pDstVec, int nSize);
void nmppsNeg(nm32s* pSrcVec, nm32s* pDstVec, int nSize);
void nmppsNeg(nm64s* pSrcVec, nm64s* pDstVec, int nSize);
    //! \}

//*****************************************************************************

    /**
    \defgroup nmppsAddC nmppsAddC
    \ingroup vArithmetics
    \brief
        \ru Добавление к вектору константы. 
        \en Addition of a constant to a vec. 
    
		\~
    
	\f[
        pDstVec[i]  =  pSrcVec[i]  +  nVal,
    \f]
    
	\f[
        i = \overline{0 \ldots nSize-1}
    \f]
    
    \param  pSrcVec 
        \ru Входной вектор. 
        \en Input vec. 
		\~
    \param  nVal    
        \ru Добавляемая константа. 
        \en Added constant. 
		\~
    \param  pnVal   
        \ru Указатель на добавляемую константу. 
        \en Pointer to the added constant. 
		\~
    \param  nSize   
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
             <param> nVal </param> <values> n </values>
             <param> pnVal </param> <values> &amp;n </values>
             <param> pDstVec </param> <values> L G </values>
             <param> nSize </param> <values> 10240 </values>
        </testperf>
        <testperf> 
             <param> pSrcVec </param> <values> L </values>
             <param> nVal </param> <values> n </values>
             <param> pnVal </param> <values> &amp;n </values>
             <param> pDstVec </param> <values> G </values>
             <param> nSize </param> <values> 8 128 1024 10240 </values>
        </testperf>
    \endxmlonly
    */
    //! \{
void nmppsAddC(nm8s* pSrcVec,  int8b nVal,    nm8s* pDstVec,  int nSize);
void nmppsAddC(nm16s* pSrcVec, int16b nVal,   nm16s* pDstVec, int nSize);
void nmppsAddC(nm32s* pSrcVec, int32b nVal,   nm32s* pDstVec, int nSize);
void nmppsAddC(nm64s* pSrcVec, int64b* pnVal, nm64s* pDstVec, int nSize);
    //! \}

//*****************************************************************************

    /**
    \defgroup nmppsAdd nmppsAdd
    \ingroup vArithmetics
    \brief
        \ru Сложение двух векторов. 
        \en Two vectors addition. 
    
		\~
    
	\f[
        pDstVec[i]  =  pSrcVec1[i]  +  pSrcVec2[i],
    \f]
    
	\f[
        i = \overline{0 \ldots nSize-1}
    \f]
    
    \param pSrcVec1 
        \ru Первый входной вектор. 
        \en The first input vec. 
		\~
    \param pSrcVec2 
        \ru Второй входной вектор. 
        \en The second input vec. 
		\~
    \param nSize    
        \ru Размер вектора в элементах. 
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
             <param> pSrcVec1 </param> <values> L G </values>
             <param> pSrcVec2 </param> <values> L G </values>
             <param> pDstVec </param> <values> L G </values>
             <param> nSize </param> <values> 10240 </values>
        </testperf>
        <testperf> 
             <param> pSrcVec1 </param> <values> L </values>
             <param> pSrcVec2 </param> <values> G </values>
             <param> pDstVec </param> <values> G </values>
             <param> nSize </param> <values> 8 128 1024 10240 </values>
        </testperf>
    \endxmlonly
    */
    //! \{
void nmppsAdd(nm8s* pSrcVec1, nm8s* pSrcVec2, nm8s* pDstVec, int nSize);
void nmppsAdd(nm16s* pSrcVec1, nm16s* pSrcVec2, nm16s* pDstVec, int nSize);
void nmppsAdd(nm32s* pSrcVec1, nm32s* pSrcVec2, nm32s* pDstVec, int nSize);
void nmppsAdd(nm64s* pSrcVec1, nm64s* pSrcVec2, nm64s* pDstVec, int nSize);
    //! \}


//*****************************************************************************

    /**
    \defgroup nmppsAdd_AddC nmppsAdd_AddC
    \ingroup vArithmetics
    \brief
        \ru Сложение двух векторов с прибавлением константы. 
        \en Summation of two vectors with addition of a constant. 
    
		\~
    
	\f[
        pDstVec[i]  =  pSrcVec1[i]  +  pSrcVec2[i]  +  nVal,
    \f]
    
	\f[
        i = \overline{0 \ldots nSize-1}
    \f]
    
    \param pSrcVec1 
        \ru Первый входной вектор. 
        \en The first input vec. 
		\~
    \param pSrcVec2 
        \ru Второй входной вектор. 
        \en The second input vec. 
		\~
    \param nVal     
        \ru Добавляемая константа. 
        \en Added constant. 
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
             <param> pSrcVec1 </param> <values> L G </values>
             <param> nVal </param> <values> n </values>
             <param> pSrcVec2 </param> <values> L G </values>
             <param> pDstVec </param> <values> L G </values>
             <param> nSize </param> <values> 10240 </values>
        </testperf>
        <testperf> 
             <param> pSrcVec1 </param> <values> L </values>
             <param> nVal </param> <values> n </values>
             <param> pSrcVec2 </param> <values> G </values>
             <param> pDstVec </param> <values> G </values>
             <param> nSize </param> <values> 8 128 1024 10240 </values>
        </testperf>
    \endxmlonly
    */
    //! \{
void nmppsAdd_AddC(nm32s* pSrcVec1, nm32s* pSrcVec2, int nVal, nm32s* pDstVec, int nSize);
    //! \}

//*****************************************************************************

    /**
    \defgroup nmppsSubC nmppsSubC
    \ingroup vArithmetics
    \brief
        \ru Вычитание константы из  вектора. 
        \en Subtraction of a constant from a vec.  
    
		\~
    
	\f[
        pDstVec[i]  =  pSrcVec[i]  -  nVal
    \f]
    
	\f[
        i = \overline{0 \ldots nSize-1}
    \f]
    
    \param pSrcVec  
        \ru Входной вектор. 
        \en Input vec. 
		\~
    \param nVal     
        \ru Вычитаемая константа. 
        \en The deducted constant. 
		\~
    \param  pnVal   
        \ru Указатель на вычитаемую константу. 
        \en Pointer to the deducted constant. 
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
             <param> nVal </param> <values> n </values>
             <param> pnVal </param> <values> &amp;n </values>
             <param> pDstVec </param> <values> L G </values>
             <param> nSize </param> <values> 10240 </values>
        </testperf>
        <testperf> 
             <param> pSrcVec </param> <values> L </values>
             <param> nVal </param> <values> n </values>
             <param> pnVal </param> <values> &amp;n </values>
             <param> pDstVec </param> <values> G </values>
             <param> nSize </param> <values> 8 128 1024 10240 </values>
        </testperf>
    \endxmlonly
    */
    //! \{
void nmppsSubC(nm8s* pSrcVec,  int8b nVal,    nm8s*  pDstVec,  int nSize);
void nmppsSubC(nm16s* pSrcVec, int16b nVal,   nm16s* pDstVec, int nSize);
void nmppsSubC(nm32s* pSrcVec, int32b nVal,   nm32s* pDstVec, int nSize);
void nmppsSubC(nm64s* pSrcVec, int64b* pnVal, nm64s* pDstVec, int nSize);
    //! \}

//*****************************************************************************
    
    /**
    \defgroup nmppsSubCRev nmppsSubCRev
    \ingroup vArithmetics
    \brief
        \ru Вычитание константы из  вектора  с переменой знака элементов вектора. 
        \en Subtraction of a constant from a vec with change of the vec elements sign.  
    
		\~
    
	\f[
        pDstVec[i]  =  nVal - pSrcVec[i],
    \f]
    
	\f[
        i = \overline{0 \ldots nSize-1}
    \f]
    
    \param pSrcVec  
        \ru Входной вектор. 
        \en Input vec. 
		\~
    \param nVal     
        \ru Константа. 
        \en Constant. 
		\~
    \param  pnVal   
        \ru Указатель на константу. 
        \en Pointer to the constant. 
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
             <param> nVal </param> <values> n </values>
             <param> pnVal </param> <values> &amp;n </values>
             <param> pDstVec </param> <values> L G </values>
             <param> nSize </param> <values> 10240 </values>
        </testperf>
        <testperf> 
             <param> pSrcVec </param> <values> L </values>
             <param> nVal </param> <values> n </values>
             <param> pnVal </param> <values> &amp;n </values>
             <param> pDstVec </param> <values> G </values>
             <param> nSize </param> <values> 8 128 1024 10240 </values>
        </testperf>
    \endxmlonly
    */
    //! \{
void nmppsSubCRev(nm8s* pSrcVec, int8b nVal, nm8s* pDstVec, int nSize);
void nmppsSubCRev(nm16s* pSrcVec, int16b nVal, nm16s* pDstVec, int nSize);
void nmppsSubCRev(nm32s* pSrcVec, int32b nVal, nm32s* pDstVec, int nSize);
void nmppsSubCRev(nm64s* pSrcVec, int64b* pnVal, nm64s* pDstVec, int nSize);
    //! \}

//*****************************************************************************

    /**
    \defgroup nmppsSub nmppsSub
    \ingroup vArithmetics
    \brief
        \ru Вычитание двух вектров. 
        \en Two vectors subtraction. 
    
		\~
    
	\f[
        pDstVec[i] = pSrcVec1[i] - pSrcVec2[i]
    \f] 
    
	\f[
        i = \overline{0 \ldots nSize-1}
    \f]
    
    \param pSrcVec1 
        \ru Уменьшаемый вектор. 
        \en Input vec. 
		\~
    \param pSrcVec2 
        \ru Вычитаемый вектор. 
        \en The deducted vec. 
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
             <param> pSrcVec1 </param> <values> L G </values>
             <param> pSrcVec2 </param> <values> L G </values>
             <param> pDstVec </param> <values> L G </values>
             <param> nSize </param> <values> 10240 </values>
        </testperf>
        <testperf> 
             <param> pSrcVec1 </param> <values> L </values>
             <param> pSrcVec2 </param> <values> G </values>
             <param> pDstVec </param> <values> G </values>
             <param> nSize </param> <values> 8 128 1024 10240 </values>
        </testperf>
    \endxmlonly
    */
    //! \{
void nmppsSub(nm8s* pSrcVec1, nm8s* pSrcVec2, nm8s* pDstVec, int nSize);
void nmppsSub(nm16s* pSrcVec1, nm16s* pSrcVec2, nm16s* pDstVec, int nSize);
void nmppsSub(nm32s* pSrcVec1, nm32s* pSrcVec2, nm32s* pDstVec, int nSize);
void nmppsSub(nm64s* pSrcVec1, nm64s* pSrcVec2, nm64s* pDstVec, int nSize);
    //! \}


//*****************************************************************************

    /**
    \defgroup nmppsAbsDiff nmppsAbsDiff
    \ingroup vArithmetics
    \brief
        \ru Вычисление вектора модулей разности элементов двух векторов. 
        \en Calculation of the vec of modules of two vectors difference.       
		\~
    
	\f[
        pDstVec[i]  =  abs \{ pSrcVec1[i]  -  pSrcVec2[i]\},
    \f]
    
	\f[
        i = \overline{0 \ldots nSize-1}
    \f]
    
    \param pSrcVec1 
        \ru Входной вектор. 
        \en Input vec. 
		\~
    \param pSrcVec2 
        \ru Вычитаемый вектор. 
        \en The deducted vec. 
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

    \restr
        \ru Разность элементов векторов не должна быть равна минимальному 
            значению для соответствующего типа (т.е. -128, -2^15 и т.д).
            В противном случае, абсолютное значение для таких элементов
            вычисляется не верно, давая на выходе то же самое число.
         \en Difference between vec elements must not be equal
            to the minimum value of element type. (i.e. -128, -2^15 ...)
            Otherwise absolute values for such elements
            are calculated incorrectly resulting to the same value
            in the output vec.    
		\~
    \par
    \xmlonly
        <testperf> 
             <param> pSrcVec1 </param> <values> L G </values>
             <param> pSrcVec2 </param> <values> L G </values>
             <param> pDstVec </param> <values> L G </values>
             <param> nSize </param> <values> 10240 </values>
        </testperf>
        <testperf> 
             <param> pSrcVec1 </param> <values> L </values>
             <param> pSrcVec2 </param> <values> G </values>
             <param> pDstVec </param> <values> G </values>
             <param> nSize </param> <values> 8 128 1024 10240 </values>
        </testperf>
    \endxmlonly

    
    */
    //! \{
void nmppsAbsDiff(nm8s* pSrcVec1, nm8s* pSrcVec2, nm8s* pDstVec, int nSize);
void nmppsAbsDiff(nm16s* pSrcVec1, nm16s* pSrcVec2, nm16s* pDstVec, int nSize);
void nmppsAbsDiff(nm32s* pSrcVec1, nm32s* pSrcVec2, nm32s* pDstVec, int nSize);
void nmppsAbsDiff(nm64s* pSrcVec1, nm64s* pSrcVec2, nm64s* pDstVec, int nSize);
    //! \}
	
//*****************************************************************************

    /**
    \defgroup nmppsAbsDiff1 nmppsAbsDiff1
    \ingroup vArithmetics
    \brief
        \ru Функция логического вычисления модулей разностей элементов двух векторов. 
        \en Logical-based calculation of absolute values of two vec difference.     
		\~
    
	\f[
        pDstVec[i]  =  \{ \begin{array}{*{20}c}
        pSrcVec1[i] - pSrcVec2[i] ,    &  if &  pSrcVec1[i] - pSrcVec2[i] \ge 0  \\
        pSrcVec1[i] - pSrcVec2[i]-1,     &  if &  pSrcVec1[i] - pSrcVec2[i] < 0  \\
        \end{array}
    \f]
    
	\f[
        i = \overline{0 \ldots nSize-1}
    \f]
    
    \param pSrcVec1 
        \ru Входной вектор. 
        \en Input vec. 
		\~
    \param pSrcVec2 
        \ru Вычитаемый вектор. 
        \en The deducted vec. 
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

    \restr
        \ru Разность элементов векторов не должна быть равна минимальному 
            значению для соответствующего типа (т.е. -128, -2^15 и т.д).
            В противном случае, абсолютное значение для таких элементов
            вычисляется не верно, давая на выходе то же самое число.
         \en Difference between vec elements must not be equal
            to the minimum value of element type. (i.e. -128, -2^15 ...)
            Otherwise absolute values for such elements
            are calculated incorrectly resulting to the same value
            in the output vec.    
		\~
    \par
    \xmlonly
        <testperf> 
             <param> pSrcVec1 </param> <values> L G </values>
             <param> pSrcVec2 </param> <values> L G </values>
             <param> pDstVec </param> <values> L G </values>
             <param> nSize </param> <values> 10240 </values>
        </testperf>
        <testperf> 
             <param> pSrcVec1 </param> <values> L </values>
             <param> pSrcVec2 </param> <values> G </values>
             <param> pDstVec </param> <values> G </values>
             <param> nSize </param> <values> 8 128 1024 10240 </values>
        </testperf>
    \endxmlonly

    
    */
    //! \{
void nmppsAbsDiff1(nm8s* pSrcVec1, nm8s* pSrcVec2, nm8s* pDstVec, int nSize);
    //! \}	

//*****************************************************************************

    /**
    \defgroup nmppsMulC nmppsMulC
    \ingroup vArithmetics
    \brief
        \ru Умножение вектора на константу. 
        \en Vector by constant multiplication. 
    
		\~
    
	\f[
        pDstVec[i] = nVal \cdot pSrcVec[i],
    \f]
    
	\f[
        i = \overline{0 \ldots nSize-1}
    \f]
    
    \param pSrcVec  
        \ru Входной вектор. 
        \en Input vec. 
		\~
    \param nVal     
        \ru Константа-множитель. 
        \en Multiplier constant. 
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
             <param> nVal </param> <values> n </values>
             <param> pnVal </param> <values> &amp;n </values>
             <param> pDstVec </param> <values> L G </values>
             <param> nSize </param> <values> 10240 </values>
        </testperf>
        <testperf> 
             <param> pSrcVec </param> <values> L </values>
             <param> nVal </param> <values> n </values>
             <param> pnVal </param> <values> &amp;n </values>
             <param> pDstVec </param> <values> G </values>
             <param> nSize </param> <values> 8 128 1024 10240 </values>
        </testperf>
    \endxmlonly
    */
    //! \{
void nmppsMulC(nm8s* pSrcVec, int8b nVal, nm8s* pDstVec, int nSize);
void nmppsMulC(nm8s* pSrcVec, int16b nVal, nm16s* pDstVec, int nSize);
void nmppsMulC(nm16s* pSrcVec, int32b nVal, nm32s* pDstVec, int nSize);
void nmppsMulC(nm32s* pSrcVec, int32b nVal, nm32s* pDstVec, int nSize);
void nmppsMulC(nm32s* pSrcVec, int64b nVal, nm64s* pDstVec, int nSize);
void nmppsMulC(nm64s* pSrcVec, int64b nVal, nm64s* pDstVec, int nSize);
    //! \}


//*****************************************************************************

    /**
    \defgroup nmppsMul_AddC nmppsMul_AddC
    \ingroup vArithmetics
    \brief
        \ru Поэлементное умножение векторов с прибавлением константы. 
        \en Elementwise multiplication of two vectors with constat addition 
    
		\~
    
	\f[
        pDstVec[i] = pSrcVec1[i] \cdot pSrcVec2[i] + nVal,
    \f]
    
	\f[
        i = \overline{0 \ldots nSize-1}
    \f]
    
    \param pSrcVec1  
        \ru Входной вектор. 
        \en Input vec. 
		\~
	\param pSrcVec2  
        \ru Входной вектор. 
        \en Input vec. 
		\~
    \param nVal     
        \ru указаель на константу-инкремент. 
        \en pointer to increment-constant. 
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
             <param> pSrcVec1 </param> <values> L G </values>
			 <param> pSrcVec2 </param> <values> L G </values>
             <param> nVal </param> <values> n </values>
             <param> pnVal </param> <values> &amp;n </values>
             <param> pDstVec </param> <values> L G </values>
             <param> nSize </param> <values> 10240 </values>
        </testperf>
        <testperf> 
             <param> pSrcVec </param> <values> L </values>
             <param> nVal </param> <values> n </values>
             <param> pnVal </param> <values> &amp;n </values>
             <param> pDstVec </param> <values> G </values>
             <param> nSize </param> <values> 8 128 1024 10240 </values>
        </testperf>
    \endxmlonly
    */
    //! \{
void nmppsMul_AddC(nm64s* pSrcVec1,nm64s* pSrcVec2, nm64s* pnVal, nm64s* pDstVec, int nSize);
    //! \}
//*****************************************************************************

    /**
    \defgroup nmppsMulC_AddC nmppsMulC_AddC
    \ingroup vArithmetics
    \brief
        \ru Умножение вектора на константу с прибавлением константы. 
        \en Vector by constant multiplication with addition of a constant. 
    
		\~
    
	\f[
        pDstVec[i]  =  nMulVal \cdot pSrcVec[i] + nAddVal,
    \f]
    
	\f[
        \quad i = \overline{0 \ldots nSize-1}
    \f]
    
    \param pSrcVec  
        \ru Входной вектор. 
        \en Input vec. 
		\~
    \param nMulVal   
        \ru Константа-множитель. 
        \en Multiplier constant. 
		\~
    \param nAddVal   
        \ru Добавляемая константа.
        \en Addition constant. 
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
             <param> nMulVal </param> <values> m </values>
             <param> nAddVal </param> <values>  n </values>
             <param> pDstVec </param> <values> L G </values>
             <param> nSize </param> <values> 10240 </values>
        </testperf>
        <testperf> 
             <param> pSrcVec </param> <values> L </values>
             <param> nMulVal </param> <values> m </values>
             <param> nAddVal </param> <values>  n </values>
             <param> pDstVec </param> <values> G </values>
             <param> nSize </param> <values> 8 128 1024 10240 </values>
        </testperf>
    \endxmlonly
    */
    //! \{
void nmppsMulC_AddC(nm32s* pSrcVec, int nMulVal, int nAddVal, nm32s* pDstVec, int nSize);
    //! \}

	


/**
 *   \ingroup nmppsMulC_AddC
 *
 *  \brief Sparse vector by constant multiplication with addition of constant. 
 *  \f[
 *       dataSparseDst[i \cdot stepSparseDst][k]  =  dataSparseSrc[i \cdot stepSparseSrc][k]\cdot mulArg[k] + addArg[k],
 *  \f]
 *	\f[
 *       i = \overline{0 \ldots size-1}; k = \overline{0 \ldots K-1},
 *  \f]
 *  where K is value of intWxK type
 *  
 *  \param [in] dataSparseSrc Input sparse vector of 64-bit packed words
 *  \param [in] mulArg Packed 64-bit word with values to multiply 
 *  \param [in] addArg Packed 64-bit word with values to add 
 *  \param [in] dataSparseDst Ouput sparse vector of 64-bit packed words
 *  \param [in] size actual amount of 64-bit packed words in sparse vector to be processed
 *  \param [in] stepSparseSrc 64-bit step between input packed words in memory .  By default=1 means that input vector is continuous 
 *  \param [in] stepSparseDst 64-bit step between output packed words in memory. By default=1 means that output vector is continuous
 *  \return  \e void 
 *  
 *  \details 
 */
//! \{
void nmppsMulC_AddC(int32x2* dataSparseSrc,  int32x2& mulArg, int32x2& addArg, int32x2 *dataSparseDst,  int size, int stepSparseSrc=1, int stepSparseDst=1);
//! \}


/**
 *  \defgroup VEC_ArshC_MulC_AddC VEC_ArshC_MulC_AddC
 *  \ingroup vArithmetics
 *
 *  Sparse vector by constant multiplication with addition of constant. 
 *  \f[
 *       dataSparseDst[i \cdot stepSparseDst][k]  =  (dataSparseSrc[i \cdot stepSparseSrc][k]>>preshiftArg[k])\cdot mulArg[k] + addArg[k],
 *  \f]
 *	\f[
 *       i = \overline{0 \ldots size-1}; k = \overline{0 \ldots K-1},
 *  \f]
 *  where K is value of intWxK type
 *  
 *  \param [in] dataSparseSrc Input sparse vector of 64-bit packed words
 *  \param [in] preshiftArg  Packed 64-bit word of values for preshifting of input data = [2,4,6,8...28,30]
 *  \param [in] mulArg Packed 64-bit word with values to multiply 
 *  \param [in] addArg Packed 64-bit word with values to add 
 *  \param [in] dataSparseDst Ouput sparse vector of 64-bit packed words
 *  \param [in] size actual amount of 64-bit packed words in sparse vector to be processed
 *  \param [in] stepSparseSrc 64-bit step between input packed words in memory . By default=1 means that input vector is continuous 
 *  \param [in] stepSparseDst 64-bit step between output packed words in memory. By default=1 means that output vector is continuous
 *  \return  \e void 
 *  
 *  \details 
 */
//! \{
void VEC_ArshC_MulC_AddC(int32x2* dataSparseSrc,  int32x2& preshiftArg, int32x2& mulArg, int32x2& addArg, int32x2 *dataSparseDst,  int size, int stepSparseSrc=1, int stepSparseDst=1);
//! \}
	

//*****************************************************************************

    /**
    \defgroup nmppsMulC_AddV_AddC nmppsMulC_AddV_AddC
    \ingroup vArithmetics
    \brief
        \ru Умножение вектора на константу с прибавлением вектора и константы. 
        \en Vector by constant multiplication with addition of a vec and a  constant. 
    
		\~
    
	\f[
        pDstVec[i]  =  nMulVal \cdot pSrcVec1[i] + pSrcVec2[i] +  nAddVal,
    \f]
    
	\f[
        i = \overline{0 \ldots nSize-1}
    \f]
    
    \param pSrcVec1 
        \ru Первый входной вектор. 
        \en The first input vec. 
		\~
    \param nMulVal   
        \ru Константа-множитель. 
        \en Multiplier constant. 
		\~
    \param pSrcVec2 
        \ru Второй входной вектор. 
        \en The second input vec. 
		\~
    \param nAddVal   
        \ru Добавляемая константа.
        \en Addition constant. 
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
             <param> pSrcVec1 </param> <values> L G </values>
             <param> nMulVal </param> <values> m </values>
             <param> pSrcVec2 </param> <values> L G </values>
             <param> nAddVal </param> <values>  n </values>
             <param> pDstVec </param> <values> L G </values>
             <param> nSize </param> <values> 10240 </values>
        </testperf>
        <testperf> 
             <param> pSrcVec1 </param> <values> L </values>
             <param> nMulVal </param> <values> m </values>
             <param> pSrcVec2 </param> <values> G </values>
             <param> nAddVal </param> <values>  n </values>
             <param> pDstVec </param> <values> G </values>
             <param> nSize </param> <values> 8 128 1024 10240 </values>
        </testperf>
    \endxmlonly
    */
    //! \{
void nmppsMulC_AddV_AddC(nm32s* pSrcVec1, int nMulVal, nm32s* pSrcVec2, int nAddVal, nm32s* pDstVec, int nSize);
    //! \}
 
//*****************************************************************************

    /**
    \defgroup nmppsSumN nmppsSumN
    \ingroup vArithmetics
    \brief
        \ru Сложение нескольких векторов. 
        \en Summation of several vectors. 
    
		\~
    
	\f[
        pDstVec[i]  =  \sum\limits_{j = 0}^{(nNumberOfVectors - 1)} {ppSrcVec(j)(i)}     
    \f]
    
    \param ppSrcVec 
        \ru Массив указателей на суммируемые вектора. 
        \en The array of pointers to the summable vectors. 
		\~
    \param nNumberOfVectors 
        \ru Число суммируемых векторов. 
        \en The number of summable vectors. 
		\~
    \param nSize    
        \ru Размер векторов в элементах =[32*PACK]
        \en Vector size in elements =[32*PACK]
		\~
    \retval pDstVec 
        \ru Результирующий вектор. 
        \en The result vec. 
		\~
    \return \e void 
    
    \par
    \xmlonly
        <testperf> 
             <init> 	
                long *pL[4]={L, L+1024, L+2048, L+4096};
	            long *pG[4]={G, G+1024, G+2048, G+4096};
             </init>
             <param> ppSrcVec </param> <values> pL pG </values>
             <param> pDstVec </param> <values> L G </values>
             <param> nNumberOfVectors </param> <values> 4 </values>
             <param> nSize </param> <values> 10240 </values>
        </testperf>
        <testperf> 
             <init> 	
                long *pL[4]={L, L+1024, L+2048, L+4096};
	            long *pG[4]={G, G+1024, G+2048, G+4096};
             </init>
             <param> ppSrcVec </param> <values> pL </values>
             <param> pDstVec </param> <values> G </values>
             <param> nNumberOfVectors </param> <values> 4 </values>
             <param> nSize </param> <values> 256 1024 10240 </values>
        </testperf>
    \endxmlonly

    */
    //! \{
void nmppsSumN(nm8s  ** ppSrcVec, nm16s* pDstVec, int nSize, int nNumberOfVectors);
void nmppsSumN(nm16s ** ppSrcVec, nm16s* pDstVec, int nSize, int nNumberOfVectors);
    //! \}

		
void nmppsSum4(
		nm16s**			Vectors,		// array of pointers to buffers	:nm8s*  Any  [NumberOfBuffer]
		nm16s*			pDstVec,		// result buffer				:long Local  [VecSize/4]
		int				nSize			// buffer size in 8-bit elements:nSize    =[256,512,..]
		);	
		
//*****************************************************************************

    /**
    \defgroup nmppsDivC  nmppsDivC
    \ingroup vArithmetics
    \brief
        \ru Деление вектора на константу. 
        \en Division of a vec by a constant. 
    
		\~
    
	\f[ 
        pDstVec[i]  =  \frac {pSrcVec[i]}{Divisor},
    \f]
    
	\f[
        i = \overline{0 \ldots nSize-1}
    \f]
    
    \param pSrcVec  
        \ru Входной вектор. 
        \en Input vec. 
		\~
    \param nDivisor	
        \ru Константа-делитель. 
        \en Constant-divisor. 
		\~
    \param nSize	
        \ru Размер входного вектора в элементах. 
        \en Input vec size in elements. 
		\~
    \param pTmpBuf1	
        \ru Временный массив размером nSize 64-х разрядных слов. 
        \en Temporary array sized nSize of 64-bit words. 
		\~
    \param pTmpBuf2	
        \ru Временный массив размером nSize 64-х разрядных слов. 
        \en Temporary array sized nSize of 64-bit words. 
		\~
    \retval pDstVec	
        \ru Результирующий вектор. 
        \en The result vec. 
		\~
    \return void
    
    \restr
        - \ru Допустимые значения для элементов входного вектора лежат
            в диапазоне [-4095,...,4095];
          \en Admissible values for input vec elements are in the range [-4095,...,4095];
		\~
        - \ru Допустимые значения для делителя лежат в диапазоне [1,2,..145].
          \en Admissible values for devisor are in the range [1,2,..145]. 

		\~
    \note 
        \ru Для коректного использования in-place параметров
    	    следует учитывать порядок получения промежуточных результатов:\n
    	\en To use in-place parameters correctly one should take into account
		\~
    	    the order of obtaining intermediate results: \n
        \~  pSrcVec			=> pTmpBuf1		(1cpl:L<=>G)		- 1/x Multiplying	(in-place is supported)\n
    	    pTmpBuf1		=> pTmpBuf2		(1cpl:G<=>L)		- Scaling down		(in-place is supported)\n
    	    pTmpBuf2		=> pDstVec		(2cpl:L<=>G)		- Result correction	(in-place is supported)\n\n
    	\ru Примеры использования in-place параметров:\n
    	\en Examples of in-place parameters use: \n
        \~  VEC_Div(L0,G0,10240,3,G0,L0);\n
    	    VEC_Div(L0,L0,10240,3,L0,L0);\n
    
         
    \par
    \xmlonly
        <testperf> 
             <param> pSrcVec </param> <values> L G </values>
             <param> pDstVec </param> <values> L G </values>
             <param> nDivisor </param> <values> n </values>
             <param> pnDivisor </param> <values> &amp;n </values>
             <param> pTmpBuf1 </param> <values> L G </values>
             <param> pTmpBuf2 </param> <values> L G </values>
             <param> nSize </param> <values> 10240 </values>
        </testperf>
        <testperf> 
             <param> pSrcVec </param> <values> L </values>
             <param> pDstVec </param> <values> G </values>
             <param> nDivisor </param> <values> n </values>
             <param> pnDivisor </param> <values> &amp;n </values>
             <param> pTmpBuf1 </param> <values> G </values>
             <param> pTmpBuf2 </param> <values> L </values>
             <param> nSize </param> <values> 8 128 1024 10240 </values>
        </testperf>
    \endxmlonly
    \{
    */
void nmppsDivC(nm32s* pSrcVec, int nDivisor, nm32s* pDstVec, int nSize, void* pTmpBuf1, void* pTmpBuf2);
    //! \}

//*****************************************************************************

    /**
    \defgroup nmppsSum nmppsSum
    \ingroup vArithmetics
    \brief
        \ru Возвращает сумму всех элементов вектора. 
        \en Returns the sum of all vec elements. 

		\~
    
	\f[
        return  =  \sum\limits_{i = 0}^{(nSize - 1)} {pSrcVec[i]}     
    \f]
    
    \param pSrcVec  
        \ru Входной вектор. 
        \en Input vec. 
		\~
    \param pTmpBuf  
        \ru Временный массив размера nSize 64-х разрядных слов. 
        \en A temporary array sized nSize 64-bit words. 
		\~
    \param nSize    
        \ru Размер векторов в элементах. 
        \en Vector size in elements. 
		\~
    \return         
        \ru Сумма элементов вектора. 
        \en The sum of vec elements. 
    
        
		\~
    \par
    \xmlonly
        <testperf> 
             <param> pSrcVec </param> <values> L G </values>
             <param> pTmpBuf </param> <values> L G </values>
             <param> pnRes  </param> <values> &amp;n </values>
             <param> nSize </param> <values> 10240 </values>
        </testperf>
        <testperf> 
             <param> pSrcVec </param> <values> G </values>
             <param> pTmpBuf </param> <values> L </values>
             <param> pnRes  </param> <values> &amp;n </values>
             <param> nSize </param> <values> 8 128 1024 10240 </values>
        </testperf>
    \endxmlonly
    
    */
    //! \{
void nmppsSum(nm1* pSrcVec, int nSize, int32b *pnRes, void* pTmpBuf);
void nmppsSum(nm8s* pSrcVec, int nSize, int32b *pnRes);
void nmppsSum(nm16s* pSrcVec, int nSize, int64b *pnRes);
void nmppsSum(nm32s* pSrcVec, int nSize, int64b *pnRes);
void nmppsSum(nm64s* pSrcVec, int nSize, int64b *pnRes);
    //! \}

//*****************************************************************************

    /**
    \defgroup nmppsDotProd nmppsDotProd
    \ingroup vArithmetics
    \brief
        \ru Скалярное умножение двух векторов. 
        \en Scalar multiplication of two vectors. 
    
		\~
    
	\f[
        nRes = \sum_{i=}^{nSize-1} pSrcVec1[i] \cdot pSrcVec2[i] 
    \f]
    
    \param pSrcVec1  
        \ru Первый вектор. 
        \en The first vec. 
		\~
    \param pSrcVec2  
        \ru Второй вектор. 
        \en The second vec. 
		\~
    \param nSize     
        \ru Размер векторов в элементах. 
        \en Vector size in elements. 
		\~
    \retval pnRes    
        \ru Указатель на результирующее значение. 
        \en Pointer to the result value. 
		\~
	\return pTmpBuff
		\ru Временный массив из nSize элементов.
		\en Temporary buffer of nSize elements.
		\~
    \return \e void
    
    \par
    \xmlonly
        <testperf> 
             <param> pSrcVec1 </param> <values> L G </values>
             <param> pSrcVec2 </param> <values> L G </values>
             <param> pTmpBuff </param> <values> L G </values>
             <param> pnRes  </param> <values> &amp;n </values>
             <param> nSize </param> <values> 8192 </values>
        </testperf>
        <testperf> 
             <param> pSrcVec1 </param> <values> G </values>
             <param> pSrcVec2 </param> <values> L </values>
             <param> pTmpBuff </param> <values> G </values>
             <param> pnRes  </param> <values> &amp;n </values>
             <param> nSize </param> <values> 8 128 1024 8192 </values>
        </testperf>
    \endxmlonly
    */
    //! \{
void nmppsDotProd(nm8s*  pSrcVec1,  nm8s* pSrcVec2, int nSize, int64b* pnRes, void* pTmpBuff);
void nmppsDotProd(nm8s*  pSrcVec1, nm16s* pSrcVec2, int nSize, int64b* pnRes, void* pTmpBuff);
void nmppsDotProd(nm8s*  pSrcVec1, nm32s* pSrcVec2, int nSize, int64b* pnRes, void* pTmpBuff);
void nmppsDotProd(nm8s*  pSrcVec1, nm64s* pSrcVec2, int nSize, int64b* pnRes);

void nmppsDotProd(nm16s* pSrcVec1, nm16s* pSrcVec2, int nSize, int64b* pnRes, void* pTmpBuff);
void nmppsDotProd(nm16s* pSrcVec1, nm32s* pSrcVec2, int nSize, int64b* pnRes, void* pTmpBuff);
void nmppsDotProd(nm16s* pSrcVec1, nm64s* pSrcVec2, int nSize, int64b* pnRes);

void nmppsDotProd(nm32s* pSrcVec1, nm32s* pSrcVec2, int nSize, int64b* pnRes, void* pTmpBuff);
void nmppsDotProd(nm32s* pSrcVec1, nm64s* pSrcVec2, int nSize, int64b* pnRes);

void nmppsDotProd(nm64s* pSrcVec1, nm64s* pSrcVec2, int nSize, int64b* pnRes);
    //! \}

	/**
	\internal
	\addtogroup nmppsDotProd
	*/
	//! \{
//void nmppsDotProd(nm16sc *pSrcVec1, nm64sc *pSrcVec2, int nSize, nm64sc *pnRes);//pc version is not available
void nmppsDotProd(nm64sc *pSrcVec1, nm64sc *pSrcVec2, int nSize, nm64sc *pnRes);
	//! \}

//*****************************************************************************
	/**
	\defgroup nmppsWeightedSum nmppsWeightedSum
	\ingroup vArithmetics
	\brief
		\ru Поэлементное взвешенное суммирование элементов двух векторов
		\en Elementwise weighted multiplication of two vectors

		\~
	
	\f[ 
        pDstVec[i]  =  nW1 \cdot pSrcVec1[i] + nW2 \cdot pSrcVec2[i], 
	\f]
	
	\f[  = \overline{0 \ldots nSize-1}    \f]

	\~
	\param pSrcVec1
		\ru 1-ый входной вектор. 
		\en 1-st input vec
		\~
	\param nW1
		\ru 1-ый весовой коэффициент
		\en 2-nd weight coefficient 
		\~
	\param pSrcVec2
		\ru 2-ой входной вектор. 
		\en 2-nd input vec
		\~
	\param nW2
		\ru 2-ой весовой коэффициент
		\en 2-nd weight coefficient 
		\~
	\param nSize
		\ru Размер векторов в элементах. 
		\en Vector size in elements
		\~
	\retval pDstVec
        \ru Результирующий вектор. 
        \en The result vec. 
		\~
   \return \e void 

  \par
	\xmlonly
	 <testperf> 
			<param> pSrcVec1 </param> <values> L G </values>
			<param> pSrcVec2 </param> <values> L G </values>
			<param> pDstVec </param> <values> L G </values>
			<param> nW1 </param> <values> 0 </values>
			<param> nW2 </param> <values> 0 </values>
			<param> nSize </param> <values> 8 128 1024 10240 </values>
			<size> nSize </size>
	 </testperf>
	\endxmlonly


	*/

   //! \{    
void nmppsWeightedSum(nm8s* pSrcVec1,int nW1,nm8s* pSrcVec2,int nW2, nm16s* pDstVec, int nSize);
void nmppsWeightedSum(nm16s* pSrcVec1,int nW1,nm16s* pSrcVec2,int nW2, nm32s* pDstVec, int nSize);
void nmppsWeightedSum(nm32s* pSrcVec1,nm64s nW1,nm32s* pSrcVec2,nm64s nW2, nm64s* pDstVec, int nSize);
    //! \}


#endif // _VECARITM_H_INCLUDED_
