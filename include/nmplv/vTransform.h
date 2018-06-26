//------------------------------------------------------------------------
//
//  $Workfile:: vTransform. $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:02 $
//
//! \if file_doc
//!
//! \file   vTransform.h
//! \author Сергей Мушкаев
//! \brief  Определение функций перетаскивания по таблице.
//!
//! \endif
//!
//------------------------------------------------------------------------
#ifndef _VTRANSFORM_H_INCLUDED_
#define _VTRANSFORM_H_INCLUDED_

#ifdef __cplusplus
		extern "C" {
#endif		

    /**
    \defgroup VEC_QSort VEC_QSort
    \ingroup vTransform
    \brief
        \ru Сортировка массива по убыванию. 
        \en Descending sort of an array. 
		\~
    \param	pSrcDstVec	
        \ru Входной и результирующий вектор. 
        \en Input and result vec. 
		\~
    \param	nSize		
        \ru Размер вектора в элементах. 
        \en Vector size in elements. 
		\~
    \return \e void
    
    \restr 
        \ru Функция работает рекурсивно, передавая параметры через стек,
			поэтому размер стека должен быть больше 4*log2(nSize) 32-битных слов
			в лучшем случае (элементы массива расположены беспорядочно)
			и больше 6*nSize 32-битных слов в худшем случае
			(элементы массива уже упорядочены) 
        \en The function operates recursively and transfers elements using the stack. 
			That is why the stack size should be greater than 4*log2(nSize) 32-bit words
			at best (elements of the array are located at random) and greater than 6*nSize 32-bit words
			at worst (elements of the array are already ordered) 
		\~
    \par
    \xmlonly
        <testperf> 
			<init> 	
				nmppsRandUniform_32u((nm32u*)L,1024);
				nmppsRShiftC_32s((nm32s*)L, 1, (nm32s*)L, 1024);
				nmppsRandUniform_32u((nm32u*)G,1024);
				nmppsRShiftC_32s((nm32s*)G, 1, (nm32s*)G, 1024);
             </init>
             <param> pSrcDstVec </param> <values> L G 	  	</values>
             <param> nSize </param> <values> 256 	</values>
        </testperf>
        <testperf> 
			<init> 
				nmppsRandUniform_32u((nm32u*)G,1024);
				nmppsRShiftC_32s((nm32s*)G, 1, (nm32s*)G, 1024);
             </init>
             <param> pSrcDstVec </param> <values> G </values>
             <param> nSize </param> <values> 8 128 256 </values>
        </testperf>
    \endxmlonly

    */
    //! \{
void nmppsQSort_32s(nm32s* pSrcDstVec, int nSize);
    //! \}

//*****************************************************************************

    /**
    \defgroup nmppsRemap_ nmppsRemap_
    \ingroup vTransform
    \brief
        \ru Переупорядочивание элементов вектора по таблице. 
        \en Reodering of vector eements by table . 
	
		\~
	
	\f[ 
        pDstVec[i]=pSrcVec[pRemapTable[i]],
    \f]
    
	\f[ i = \overline{0 \ldots nSize-1} \f]
    
		\~
    \param pSrcVec     
        \ru Входной вектор. 
        \en Input vec. 
		\~
    \param pRemapTable 
        \ru Таблица новых индексов для переупорядочивания. 
        \en Index reordering table. 
		\~
    \param nDstVecSize  
        \ru Размер результирующего вектора в элементах. 
        \en Size in elements for destination vec. 
		\~
    \param pTmpBuf1     
        \ru Временный массив nm32u pTmpBuf1[nSrcVecSize]. 
        \en Temporary buffer nm32u pTmpBuf1[nSrcVecSize]. 
		\~
    \param pTmpBuf2     
        \ru Временный массив nm32u pTmpBuf2[nDstVecSize]. 
        \en Temporary buffer nm32u pTmpBuf2[nDstVecSize]. 


    \retval pDstVec		
        \ru Результирующий вектор nm8u pDstVec[nDstVecSize]. 
        \en Result vec nm8u pDstVec[nDstVecSize]. 

		\~
    \return \e void 
    
	\code 
		// Функция 
		// void nmppsRemap_8u(nm8u* pSrcVec, nm8u* pDstVec, nm32s* pRemapTable, int nSrcVecSize, int nDstVecSize, void* pTmpBuf1, void* pTmpBuf2);
		// выполняет следющие действия: 
	    nmppsConvert_8u((nm8u*) pSrcVec, (nm32u*)pTmpBuf1,nSrcVecSize);
	    nmppsRemap_32u((nm32u*)pTmpBuf1,(nm32u*)pTmpBuf2,RemapTable,DstVecSize);
	    nmppsConvert_32s((nm32s*)pTmpBuf2,(nm8s*) pDstVec, DstVecSize);
	\endcode
	
	\note
        \ru Возможность использования inplace параметров определяется исходя из 
	        последовательности процессов чтения/записи: \n
        \en Possible using of in place parameters can be determined from
		\~
            the folowing sequence of actions : \n
	    \~ - pSrcVec => pTmpBuf1 - \ru inplace запрещен; \n 
                                   \en inplace is not valid; \n
	    \~ - pTmpBuf1=>pTmpBuf2 -  \ru inplace запрещен; \n 
                                   \en inplce is not valid; \n 
	    \~ - pTmpBuf2=>pDstVec  -  \ru inplace разрешен; \n
                                   \en inplace is not valid; \n 

								   
    \par
    \xmlonly
        <testperf> 
             <param> pSrcVec </param> <values> L G </values>
             <param> pDstVec </param> <values> L G </values>
             <param> pRemapTable </param> <values> L G </values>
             <param> nDstVecSize </param> <values> 10240 </values>
        </testperf>
        <testperf> 
             <param> pSrcVec </param> <values> L </values>
             <param> pDstVec </param> <values> G </values>
             <param> pRemapTable </param> <values> G </values>
             <param> nDstVecSize </param> <values> 8 128 1024 10240 </values>
        </testperf>
    \endxmlonly
    */
    //! \{
void nmppsRemap_32u(nm32u* pSrcVec, nm32u* pDstVec, nm32s* pRemapTable, int nDstVecSize);
void nmppsRemap_8u(nm8u* pSrcVec, nm8u* pDstVec, nm32s* pRemapTable, int nSrcVecSize, int nDstVecSize, void* pTmpBuf1, void* pTmpBuf2);
    //! \}




	/**
	\internal
	\defgroup Manipulation Manipulation
	\ingroup vTransform
	\brief
		\ru Расщепление массива на несколько отдельных массивов
		\en Array splitting to several arrays
		
		\~
		
	\f[ pDst4Vec[i][j]=pSrcVec[j][i] \f]	
	\~
    \param pSrcVec     
        \ru Входной вектор. 
        \en Input vec. 
		\~
	\param pDst4Vec
		\ru Массив из 4 указателей на отдельные массивы
		\en Array of 4 pointers to separeted arrays
		\~
	\param nSize
		\ru Размер массивов
		\en Size of arrays

		\~
    \par
    \xmlonly
		<testperf>
			<param> pSrcVec </param> <values> L G	</values>
			<param> pDstVec </param> <values> L G	</values>
			<param> nSize	</param> <values> 1024 10240 </values>
		</testperf>
	\endxmlonly
	
	\todo 	Impelenment NM versin of nmppsSplit_(v4nm16s* pSrcVec, nm16s** pDst4Vec, int nSize);

	*/
	//! \{
void nmppsSplit_(v4nm16s* pSrcVec, nm16s** pDst4Vec, int nSize);
	//! \}
	
	
	/**
	    \defgroup nmppSplitTmp nmppSplitTmp
        \ingroup vTransform
    
	 *  \brief Расщепляет массив на два, группируя по четным и нечетным элементам
	 *  
	 *  \param [in]  src  Входной массив
	 *  \param [out] dst1 Выходной массив размера size/2 
	 *  \param [out] dst2 Выходной массив размера size/2 
	 *  \param [in]  size Размер исходного массива в элементах. Кратность параметра size должна соответствовать двум длинным 64-р. словам. 
	 *  \param [in]  tmpSizeOfDst Временный массив размера size/2 
	 *  \return 
	 *  
	 *  \details Details 
	 *  Максимальная производительность достигается при размещении входных, выходных и временных массивов в разных банках памяти. Массивы dst1 и dst2 могут находится в одном банке.
	 *  Макс  производительность  на 64-р. слово результата = 2.1 такта (при size=10240 байт) и 2.5 такта (при size=4096 байт)
	 */
	void nmppsSplitTmp_8s(const nm8s* src, nm8s* dst1, nm8s* dst2, int size, nm8s* tmpSizeOfDst);
	
   /**
	    \defgroup nmppSplit nmppSplit
        \ingroup vTransform
    
	 *  \brief Расщепляет массив на два массива, группируя по четным и нечетным элементам
	 *  
	 *  \param [in]  src  Входной массив
	 *  \param [out] dst1 Выходной массив размера size/2 
	 *  \param [out] dst2 Выходной массив размера size/2 
	 *  \param [in]  size Размер исходного массива в элементах. Кратность параметра size должна соответствовать двум длинным 64-р. словам. 
	 *  \return 
	 *  
	 *  \details Details 
	 *  Максимальная производительность достигается при размещении входных, выходных массивов в разных банках памяти. Массивы dst1 и dst2 могут находится в одном банке.
	 *  Макс  производительность  на 64-р. слово результата = 2.14 такта (при size=10240 байт) и 2.6 такта (при size=4096 байт)
	 */
	void nmppsSplit_8s (const nm8s* src,  nm8s*  dst1, nm8s* dst2,  int size);	
	void nmppsSplit_16s(const nm16s* src, nm16s* dst1, nm16s* dst2, int size);
	void nmppsSplit_32s(const nm32s* src, nm32s* dst1, nm32s* dst2, int size);

   /**
	    \defgroup nmppMerge nmppMerge
        \ingroup vTransform
    
	 *  \brief Собирает массив из двух, чередуя элементы из каждого. Функция обратная nmppsSplit
	 *  
	 *  \param [in]  src0 Входной массив  размера size 
	 *  \param [in]  src1 Входной массив  размера size 
	 *  \param [out] dst  Выходной массив размера 2*size 
	 *  \param [in]  size Размер выходного массива в элементах. Кратность параметра size должна соответствовать 64-р. слову. 
	 *  \return 
	 *  
	 *  \details Details 
	 */
	void nmppsMerge_8s (const nm8s*  src0, const nm8s*  src1, nm8s*  dst, int size);	
	void nmppsMerge_16s(const nm16s* src0, const nm16s* src1, nm16s* dst, int size);
	void nmppsMerge_32s(const nm32s* src0, const nm32s* src1, nm32s* dst, int size);
	
#ifdef __cplusplus
		};
#endif

#endif //_VTRANSFORM_H_INCLUDED_