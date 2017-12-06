//------------------------------------------------------------------------
//
//  $Workfile:: vInit. $
//
//  Âåêòîðíî-ìàòðè÷íàÿ áèáëèîòåêà
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:02 $
//
//! \if file_doc
//!
//! \file   vInit.h
//! \author Ñåðãåé Ìóøêàåâ
//! \brief  Îïðåäåëåíèå ôóíêöèé èíèöèàëèçàöèè äëÿ âåêòîðîâ.
//!
//! \endif
//!
//------------------------------------------------------------------------
#ifndef _VINIT_H_INCLUDED_
#define _VINIT_H_INCLUDED_

#ifdef __cplusplus
		extern "C" {
#endif		

    /**
    \defgroup nmppsSet nmppsSet
    \ingroup vInit
    \brief
        \ru Ôóíêöèÿ èíèöèàëèçàöèè ýëåìåíòîâ ìàññèâà ïîñòîÿííûì çíà÷åíèåì. 
        \en Function of array initialization with a constant value.  
    
		\~
    
	\f[
        pVec[i]  =  nVal, 
    \f]
    
	\f[
        i = \overline{0 \ldots nSize-1}
    \f]
    
    \param nSize    
        \ru Ðàçìåð âåêòîðà â ýëåìåíòàõ. 
        \en Size of vec in elements. 
		\~
    \param nVal     
        \ru Êîíñòàíòà. Äèàïàçîí çíà÷åíèé nVal äîëæåí ñîîòâåòñâîâàòü òèïó ðåçóëüòèðóþùåãî âåêòîðà. 
        \en A constant. Range of nVal must correspond to type of result vec
		\~
    \retval pVec    
        \ru Ðåçóëüòèðóþùèé âåêòîð. 
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

void nmppsSet_8s(nm8s* pVec,  int8b nVal, int nSize);
void nmppsSet_16s(nm16s* pVec, int16b nVal, int nSize);
void nmppsSet_32s(nm32s* pVec, int32b nVal, int nSize);
void nmppsSet_64sp(nm64s* pVec, int64b* nVal, int nSize); 
__INLINE__ void nmppsSet_64s(nm64s* pVec, int64b  nVal, int nSize)  {nmppsSet_64sp((nm64s*) pVec, (int64b*)&nVal, nSize);}

__INLINE__ void nmppsSet_8u(nm8u* pVec,  uint8b nVal, int nSize)	{nmppsSet_8s((nm8s*) pVec,  (int8b)nVal, nSize);}
__INLINE__ void nmppsSet_16u(nm16u* pVec, uint16b nVal, int nSize)	{nmppsSet_16s((nm16s*) pVec, (int16b)nVal, nSize);}
__INLINE__ void nmppsSet_32u(nm32u* pVec, uint32b nVal, int nSize)	{nmppsSet_32s((nm32s*) pVec, (int32b)nVal, nSize);}
__INLINE__ void nmppsSet_64u(nm64u* pVec, uint64b  nVal, int nSize)	{nmppsSet_64s((nm64s*) pVec, (int64b)nVal, nSize);}
__INLINE__ void nmppsSet_64up(nm64u* pVec, uint64b* nVal, int nSize){nmppsSet_64sp((nm64s*) pVec, (int64b*)nVal, nSize);}


    //! \}


//*****************************************************************************

    /**
    \defgroup nmppsRandUniform nmppsRandUniform
    \ingroup vInit
    \brief
        \ru Èíèöèàëèçàöèÿ ìàññèâà ñëó÷àéíûìè ÷èñëàìè. 
        \en Initialization of an array with random numbers. 
		\~
    \param nSize		
        \ru Ðàçìåð âåêòîðà. 
        \en Vector size. 
		\~
    \param nRandomize    
        \ru Ïðîèçâîëüíîå ÷èñëî äëÿ èíèöèàëèçàöèè 
                            ãåíåðàòîðà ñëó÷àéíûõ ÷èñåë. 
        \en Arbitrary number for initialization 
                            of a random-number generator. 
		\~
    \retval pDstVec     
        \ru Ðåçóëüòèðóþùèé âåêòîð. 
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
	/ru  Èíèöèàëèçàöèÿ ìàññèâà 32-ðàçðÿäíûìè ñëó÷àéíûìè ÷èñëàìè. 
	/en Random initialization of 32-bit buffer
	/~
*/
//void nmppsRandUniform_32u(nm32u* pDstVec, int nSize, unsigned nRandomize );
void nmppsRandUniform_64s(nm64s* pDstVec, int nSize);
__INLINE__ void nmppsRandUniform_8s (nm8s* pDstVec,  int nSize) {nmppsRandUniform_64s((nm64s*)pDstVec,  nSize>>3);}
__INLINE__ void nmppsRandUniform_16s(nm16s* pDstVec, int nSize) {nmppsRandUniform_64s((nm64s*)pDstVec,  nSize>>2);}
__INLINE__ void nmppsRandUniform_32s(nm32s* pDstVec, int nSize) {nmppsRandUniform_64s((nm64s*)pDstVec,  nSize>>1);}
__INLINE__ void nmppsRandUniform_8u (nm8u* pDstVec,  int nSize) {nmppsRandUniform_64s((nm64s*)pDstVec,  nSize>>3);}
__INLINE__ void nmppsRandUniform_16u(nm16u* pDstVec, int nSize) {nmppsRandUniform_64s((nm64s*)pDstVec,  nSize>>2);}
__INLINE__ void nmppsRandUniform_32u(nm32u* pDstVec, int nSize) {nmppsRandUniform_64s((nm64s*)pDstVec,  nSize>>1);}
__INLINE__ void nmppsRandUniform_64u(nm64u* pDstVec, int nSize) {nmppsRandUniform_64s((nm64s*)pDstVec,  nSize   );}

void nmppsRandUniform_64f(nm64f* pDstVec, int nSize, double low, double hi);
void nmppsRand_32f(nm32f* pDstVec, int nSize,float low,float hi);

void nmppsRandUniform_32f_integer(nm32f *pDstVec,int nSize,int hi,int low);

//__INLINE__ void nmppsRandUniform_64s(nm64s* pDstVec, int nSize, unsigned nRandomize = 1) {nmppsRandUniform_32u((nm32u*)pDstVec,  nSize<<1, nRandomize);}

/**
	/ru  Èíèöèàëèçàöèÿ ìàññèâà 64-ðàçðÿäíûìè ñëó÷àéíûìè ÷èñëàìè. 
	/en Random initialization of 64-bit buffer
	/~

*/

    //! \}

	

//*****************************************************************************

    /**
    \defgroup nmppsRandUniform_ nmppsRandUniform_
    \ingroup vInit
    \brief 
        \ru Ãåíåðàöèÿ ñëó÷àéíîãî ÷èñëà ñ ðàâíîìåðíûì ðàcïðåäåëåíèåì.
        \en Random number generation with uniform distribution.

		\~
	  \~
    \param nMin		
        \ru Ìèíèìàëüíîå âîçìîæíîå çíà÷åíèå ñëó÷àéíîãî ÷èñëà.
        \en Minimal value for random number.
		\~
    \param nMax    
        \ru Ìàêñèìàëüíîå âîçìîæíîå çíà÷åíèå ñëó÷àéíîãî ÷èñëà.
        \en Maximal value for random number.
		\~
    \param nDivisible     
        \ru Çíà÷åíèå, êîòîðîìó áóäåò êðàòíî ñëó÷àéíîå ÷èñëî.
        \en Random number will be divisible by this value.
		\~
    \return \e int
		\ru Ñëó÷àéíîå ÷èñëî â äèàïàçîíå ëèáî [nMin, nMax]. Äëÿ ôóíêöèè áåç ïàðàìåòðîâ
			äàííûé äèàïàçîí [-2^31; 2^31-1].
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
int nmppsRandUniform2_32s(int nMin, int nMax, int nDivisible);
int nmppsRandUniform3_32s(int nMin, int nMax);
int nmppsRandUniform();

    //! \}

	
//*****************************************************************************

    /**
    \defgroup nmppsRamp_ nmppsRamp_
    \ingroup vInit
    \brief
        \ru Èíèöèàëèçàöèÿ ìàññèâà ýëåìåíòàìè àðèôìåòè÷åñêîé ïðîãðåññèè. 
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
        \ru Ïåðâûé ÷ëåí àðèôìåòè÷åñêîé ïðîãðåññèè.
        \en Init value.
		\~
    \param nSlope		
        \ru Ðàçíîñòü àðèôìåòè÷åñêîé ïðîãðåññèè.
        \en Common difference.
		\~
    \param nSize		
        \ru Ðàçìåð âåêòîðà. 
        \en Vector size. 
		\~
    \retval pVec     
        \ru Ðåçóëüòèðóþùèé ìàññèâ. 
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
void nmppsRamp_8s(nm8s* pVec,  int8b nOffset,  int8b nSlope, int nSize);
void nmppsRamp_16s(nm16s* pVec, int16b nOffset, int16b nSlope, int nSize);
void nmppsRamp_32s(nm32s* pVec, int32b nOffset, int32b nSlope, int nSize);
void nmppsRamp_64s(nm64s* pVec, int64b nOffset, int64b nSlope, int nSize);
    //! \}

//*****************************************************************************

    /**
    \defgroup nmppsConvert nmppsConvert
    \ingroup vInit
    \brief
        \ru Èçìåíåíèå ðàçðÿäíîñòè ýëåìåíòîâ âåêòîðà. 
        \en Change of vec elements word-length. 
    
		\~
        \ru Ïðåîáðàçîâàíèå çíàêîâûõ äàííûõ ê ìåíüøåé ðàçðÿäíîñòè îñóùåñòâëÿåòñÿ 
	        îòáðàñûâàíèåì ñòàðøèõ áèòîâ.
	        Ïðåîáðàçîâàíèå çíàêîâûõ äàííûõ ê áîëüøåé ðàçðÿäíîñòè îñóùåñòâëÿåòñÿ 
	        c ðàñïðîñòðàíåíèåì âëåâî ñòàðøåãî (çíàêîâîãî) áèòà.
            Ïðåîáðàçîâàíèå áåççíàêîâûõ äàííûõ ê áîëüøåé ðàçðÿäíîñòè îñóùåñòâëÿåòñÿ 
	        äîáàâëåíèåì ñëåâà ñòàðøèõ íóëåâûõ áèòîâ. 
        \en Signed data are converted to lesser word-length is made by means of 
            the most significant bits truncation.
            Signed data are converted to greater word-length is made with
            left expansion of the most significant (sign) bit.
            Unsigned data are converted to greater word-length is made by means of
            addition of the most significant zero bits on the left. 
		\~
    \param pSrcVec  
        \ru Âõîäíîé âåêòîð. 
        \en Input vec. 
		\~
    \param nSize    
        \ru Ðàçìåð âåêòîðîâ â ýëåìåíòàõ. 
        \en Vector size in elements. 
		\~
    \retval pDstVec 
        \ru Ðåçóëüòèðóþùèé âåêòîð. 
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
	//todo Impelenment NM versin of void nmppsConvert_32s(nm32s *pSrcVec, nm4s *pDstVec, int nSize);
    //! \{

/**
 \restr nSize =[32*64,32*64*2,32*64*3,....]
*/
void nmppsConvert_1s2s  (const nm1* pSrcVec, nm2s* pDstVec, int nSize);
/**
 \restr nSize =[32*64,32*64*2,32*64*3,....]
*/
void nmppsConvert_1u2u  (const nm1* pSrcVec, nm2u* pDstVec, int nSize);
void nmppsConvert_1u4u  (const nm1* pSrcVec, nm4u* pDstVec, int nSize);
						 
void nmppsConvert_2s1s	(const nm2s* pSrcVec, nm1*  pDstVec, int nSize);
void nmppsConvert_2s4s  (const nm2s* pSrcVec, nm4s* pDstVec, int nSize);
void nmppsConvert_2u4u  (const nm2u* pSrcVec, nm4u* pDstVec, int nSize);
						 
void nmppsConvert_4s1s	(const nm4s* pSrcVec, nm1*  pDstVec, int nSize);
void nmppsConvert_4s2s	(const nm4s* pSrcVec, nm2s* pDstVec, int nSize);
void nmppsConvert_4s8s  (const nm4s* pSrcVec, nm8s* pDstVec, int nSize);
void nmppsConvert_4u8u  (const nm4u* pSrcVec, nm8u* pDstVec, int nSize);
                         
void nmppsConvert_8s4s  (const nm8s* pSrcVec, nm4s*  pDstVec, int nSize);
void nmppsConvert_8s16s (const nm8s* pSrcVec, nm16s* pDstVec, int nSize);
void nmppsConvert_8s32s (const nm8s* pSrcVec, nm32s* pDstVec, int nSize);
void nmppsConvert_8s64s (const nm8s* pSrcVec, nm64s* pDstVec, int nSize);
void nmppsConvert_8u16u (const nm8u* pSrcVec, nm16u* pDstVec, int nSize);
void nmppsConvert_8u32u (const nm8u* pSrcVec, nm32u* pDstVec, int nSize);
void nmppsConvert_8u64u (const nm8u* pSrcVec, nm64u* pDstVec, int nSize);
                         
void nmppsConvert_16s4s (const nm16s* pSrcVec, nm4s* pDstVec, int nSize);
void nmppsConvert_16s8s (const nm16s* pSrcVec, nm8s* pDstVec, int nSize);
void nmppsConvert_16s32s(const nm16s* pSrcVec, nm32s* pDstVec, int nSize);
void nmppsConvert_16s64s(const nm16s* pSrcVec, nm64s* pDstVec, int nSize);
void nmppsConvert_16u32u(const nm16u* pSrcVec, nm32u* pDstVec, int nSize);
void nmppsConvert_16u64u(const nm16u* pSrcVec, nm64u* pDstVec, int nSize);
                         
void nmppsConvert_32s8s (const nm32s* pSrcVec, nm8s* pDstVec, int nSize);
void nmppsConvert_32s16s(const nm32s* pSrcVec, nm16s* pDstVec, int nSize);
void nmppsConvert_32s64s(const nm32s* pSrcVec, nm64s* pDstVec, int nSize);
void nmppsConvert_32u64u(const nm32u* pSrcVec, nm64u* pDstVec, int nSize);
				         
void nmppsConvert_64s32s(const nm64s* pSrcVec, nm32s* pDstVec, int nSize);
void nmppsConvert_64s16s(const nm64s* pSrcVec, nm16s* pDstVec, int nSize);
    //! \}
//void nmppsConvert_32s(nm32s *pSrcVec, nm4s *pDstVec, int nSize);




	
//*****************************************************************************

    /**
    \defgroup nmppsCopy_ nmppsCopy_
    \ingroup vInit
    \brief
        \ru Êîïèðîâàíèå âåêòîðà. 
        \en Vector copying. 
    
		\~
    
	\f[
        pDstVec[i]  =  pSrcVec[i],
    \f]
    
	\f[
        i = \overline{0 \ldots nSize-1}
    \f]
    
    \param pSrcVec  
        \ru Âõîäíîé âåêòîð. 
        \en Input vec. 
		\~
    \param nSize    
        \ru Ðàçìåð âåêòîðîâ â ýëåìåíòàõ. 
        \en Vector size in elements. 
		\~
    \retval pDstVec 
        \ru Ðåçóëüòèðóþùèé âåêòîð. 
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
void nmppsCopy_2s (const nm2s*  pSrcVec, nm2s*  pDstVec, int nSize);
void nmppsCopy_8s (const nm8s*  pSrcVec, nm8s*  pDstVec, int nSize);
void nmppsCopy_16s(const nm16s* pSrcVec, nm16s* pDstVec, int nSize);
void nmppsCopy_32s(const nm32s* pSrcVec, nm32s* pDstVec, int nSize);
void nmppsCopy_64s(const nm64s* pSrcVec, nm64s* pDstVec, int nSize);

__INLINE__ void nmppsCopy_8u (const nm8u*  pSrcVec, nm8u*  pDstVec, int nSize) { nmppsCopy_8s (( nm8s*)  pSrcVec, (nm8s*)  pDstVec,  nSize);}
__INLINE__ void nmppsCopy_16u(const nm16u* pSrcVec, nm16u* pDstVec, int nSize) { nmppsCopy_16s(( nm16s*) pSrcVec, (nm16s*) pDstVec,  nSize);}
__INLINE__ void nmppsCopy_32u(const nm32u* pSrcVec, nm32u* pDstVec, int nSize) { nmppsCopy_32s(( nm32s*) pSrcVec, (nm32s*) pDstVec,  nSize);}
__INLINE__ void nmppsCopy_64u(const nm64u* pSrcVec, nm64u* pDstVec, int nSize) { nmppsCopy_64s(( nm64s*) pSrcVec, (nm64s*) pDstVec,  nSize);}

    //! \}



//*****************************************************************************

    /**
    \defgroup nmppsCopyua_ nmppsCopyua_
    \ingroup vInit
    \brief
        \ru Êîïèðîâàíèå âåêòîðà ñ íåâûðîâíåííîé áàéòîâîé ïîçèöèè â âûðîâíåííóþ. 
        \en Copying a vec from an unaligned byte position to aligned one. 
    
		\~
    
	\f[
        pDstVec[i] = pSrcVec[nSrcOffset+i]
    \f]
    
	\f[
        i = \overline{0 \ldots nSize-1}
    \f]

	\ru Ïîçèöèÿ áàéòà ñ÷èòàåòñÿ âûðîâíåííîé åñëè îíà ñîâïàäàåò ñ ãðàíèöåé 64ð. ñëîâ â ïàìÿòè. 
    \en Position is defined as aligned if it points to 64-bit words boundary in memory.
	
		\~
	\~
	\param pSrcVec      
        \ru Âõîäíîé âåêòîð. 
        \en Input vec. 
		\~
    \param pDstVec      
        \ru Ðåçóëüòèðóþùèé âåêòîð. 
        \en Output vec. 
		\~
    \param nSrcOffset  
        \ru Ñìåùåíèå â ýëåìåíòàõ îòíîñèòåëüíî íà÷àëà âåêòîðà. nSrcOffset Ìîæåò ïðèíèìàòü ëþáîå çíà÷åíèå.
        \en Shift in elements relatively to the origin of the vec. nSrcOffset may be any. 
		\~
    \param nSize   
        \ru Êîë-âî êîïèðóåìûõ ýëåìåíòîâ. 
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
void nmppsCopyua_8s(const nm8s* pSrcVec, int nSrcOffset, nm8s* pDstVec,  int nSize);
    //! \}

//*****************************************************************************

    /**
    \defgroup nmppsSwap_ nmppsSwap_
    \ingroup vInit
    \brief
        \ru Ïåðåñòàíîâêà äâóõ âåêòîðîâ. 
        \en Swap of two vectors. 
    
 
		\~
    \param pSrcVec1  
        \ru Ïåðâûé âõîäíîé âåêòîð. 
        \en The first input vec. 
		\~
    \param pSrcVec2  
        \ru Âòîðîé âõîäíîé âåêòîð. 
        \en The second input vec. 
		\~
    \param nSize     
        \ru Ðàçìåð âåêòîðîâ â ýëåìåíòàõ. 
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
void nmppsSwap_64s(nm64s* pSrcVec1, nm64s* pSrcVec2, int nSize);
    //! \}

	void nmppsSplitEco_8s(nm8s* src, nm8s* dst1, nm8s* dst2, int size);
	void nmppsSplit_8s(nm8s* src, nm8s* dst1, nm8s* dst2, int size, nm8s* tmpSizeofDst);

#ifdef __cplusplus
		};
#endif
	
#endif // _INIT_H_INCLUDED_



