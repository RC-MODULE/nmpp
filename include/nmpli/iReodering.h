#ifndef __IREODERING_H
#define __IREODERING_H

//*****************************************************************************

	/**
    * \ru
    *     \defgroup iReodering Переупорядочивание изображений
    * \en
    *     \defgroup iReodering Image pixels reodering
    * \~
    * \ingroup IMG_Group
    */


//*****************************************************************************

/**
*	\ru
*		\defgroup iBlockReodering Блочное переупорядочивание
*	\en
*		\defgroup iBlockReodering Block reodering.
*   \~
*	\ingroup iReodering
*	\brief 
*		\ru Блочное перупорядочивание изображений.
*		\en Block reodering of images.
*	 
*/

//*****************************************************************************

	/**
	\defgroup IMG_SplitIntoBlocks IMG_SplitIntoBlocks
	\ingroup iBlockReodering
	\brief
		\ru Преобразует изображение в последовательность квадратных блоков.
		\en Transform image into the sequence of square blocks.
	
	\~
	\param pSrcImg
	  \ru Исходное изображение
	  \en Source Image
	\param pDstBlockSeq
	\ru Выходная последовательность блоков
	\en Resaul block sequence
	\param nWidth
	  \ru Ширина исходного изображения в пикселах. nWidth =[8,16,24...]
	  \en Source Image Width. nWidth =[8,16,24...]
	\param nHeight
	  \ru Высота исходного изображения в пикселах. nHeight=[8,16,24...]
	  \en Source Image Height. nHeight=[8,16,24...]

	\note
	\ru Исходное изображение имеет вид
	\en ******************************
	\~
	\verbatim
		[A00|A01|A02|A03|A04|A05|A06|A07|B00|B01|..|B07|C00|....H07]
		[A10|A11|A12|A13|A14|A15|A16|A17|B10|B11|..|B17|C10|....H17]
		[A20|A21|A22|A23|A24|A25|A26|A27|B20|B21|..|B27|C20|....H27]
		[A30|A31|A32|A33|A34|A35|A36|A37|B30|B31|..|B37|C30|....H37]
		............................................................
		[A70|A71|A72|A73|A74|A75|A76|A77|B70|B71|..|B77|C70|....H77]
		............................................................
		[I00|I01|I02|I03|I04|I05|I06|I07|J00|J01|..................]
		[I10|I11|I12|I13|I14|I15|I16|I17|J00|I09|...................
		........................................................Z77]
	\endverbatim
	\ru Выходная последовательность блоков имеет вид
	\en ******************************
	\~
	\verbatim
		[A00|A01|A02|...|A06|A07|A20|A21|...|A77|B00|B01|B02|...|B07|B10|...|H77|
		[I00|I01|I02|...|I06|I07]I10|I11|...|I77|J00|J01|J02|...............|Z77|	
	\endverbatim

    \par
    \xmlonly
        <testperf> 
             <param> pSrcImg </param> <values> L G </values>
             <param> pDstBlockSeq </param> <values> L G </values>
             <param> nHeight </param> <values> 128 </values>
             <param> nWidth </param> <values> 128 </values>
             <size> nWidth*nHeight </size>
        </testperf>
        <testperf> 
             <param> pSrcImg </param> <values> L </values>
             <param> pDstBlockSeq </param> <values> G </values>
             <param> nHeight </param> <values> 128 </values>
             <param> nWidth </param> <values> 8 32 128 </values>
             <size> nWidth*nHeight </size>
        </testperf>
    \endxmlonly

	*/
	//! \{

void IMG_SplitIntoBlocks8x8(
		nm8s*	pSrcImg,	
			nm8s*	pDstBlockSeq,
			int		nWidth,	
			int		nHeight	
			);
	//! \}
	
void IMG_SplitInto2x2Blocks8x8(
							nm8u*	pSrcImg,	
							nm8u*	pDstBlockSeq,
							int		nWidth,	
							int		nHeight	
							);

void IMG_SplitInto2x2Blocks8x8xor(
							   nm8u*	pSrcImg,	
							   nm8u*	pDstBlockSeq,
							   nm8u*	pXor,
							   int		nWidth,	
							   int		nHeight	
							   );


//*****************************************************************************

	/**
	\defgroup IMG_MergeFromBlocks IMG_MergeFromBlocks
	\ingroup iBlockReodering
	\brief
		\ru Объединяет последовательность квадратных блоков в изображение.
		\en Merge a sequence of square blocks into image.

	\~
	\param pSrcBlockSeq
	\ru Входная последовательность блоков . 
	\en Source block sequence 
	\param pDstImg
	\ru Результирующее изображение
	\en Result Image
	\param nWidth
	  \ru Ширина исходного изображения в пикселах.  nWidth=[8,16,24...]
	  \en Source Image Width.  nWidth=[8,16,24...]
	\param nHeight
	  \ru Высота исходного изображения в пикселах. nHeight=[8,16,24..]
	  \en Source Image Height. nHeight=[8,16,24..]

  \note 
	  \ru Входная последовательность блоков имеет вид
		\en
		\~	
		\verbatim
			[A00|A01|A02|...|A06|A07|A20|A21|...|A77|B00|B01|B02|...|B07|B10|...|H77|
			[I00|I01|I02|...|I06|I07]I10|I11|...|I77|J00|J01|J02|...............|Z77|
		\endverbatim
	  \ru Результирующее изображение имеет вид
		\en
		\~
		\verbatim
			[A00|A01|A02|A03|A04|A05|A06|A07|B00|B01|..|B07|C00|....H07]
			[A10|A11|A12|A13|A14|A15|A16|A17|B10|B11|..|B17|C10|....H17]
			[A20|A21|A22|A23|A24|A25|A26|A27|B20|B21|..|B27|C20|....H27]
			[A30|A31|A32|A33|A34|A35|A36|A37|B30|B31|..|B37|C30|....H37]
			............................................................
			[A70|A71|A72|A73|A74|A75|A76|A77|B70|B71|..|B77|C70|....H77]
			............................................................
			[I00|I01|I02|I03|I04|I05|I06|I07|J00|J01|..................]
			[I10|I11|I12|I13|I14|I15|I16|I17|J00|I09|...................
			........................................................Z77]
		\endverbatim

    \par
    \xmlonly
        <testperf> 
             <param> pSrcBlockSeq </param> <values> L G </values>
             <param> pDstImg </param> <values> L G </values>
             <param> nHeight </param> <values> 128 </values>
             <param> nWidth </param> <values> 128 </values>
             <size> nWidth*nHeight </size>
        </testperf>
        <testperf> 
             <param> pSrcBlockSeq </param> <values> L </values>
             <param> pDstImg </param> <values> G </values>
             <param> nHeight </param> <values> 128 </values>
             <param> nWidth </param> <values> 8 32 128 </values>
             <size> nWidth*nHeight </size>
        </testperf>
    \endxmlonly


	*/
	//! \{
void IMG_MergeFromBlocks8x8(
		nm8s*	pSrcBlockSeq,	
			nm8s*	pDstImg,	
			int		nWidth,	
			int		nHeight	
			);
	//! \}


#endif
