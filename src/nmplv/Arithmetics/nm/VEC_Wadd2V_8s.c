#include "nmpp.h"

struct S_nmppsWeightedSum
{
	nm32s pWfifo[40];
};
/*
	\defgroup nmppsWeightedSum_Set nmppsWeightedSum_Set
	\ingroup vArithmetics
    \fn void nmppsWeightedSum_Set8(int W1,int W2, S_nmppsWeightedSum* kerW);

    \perfinclude _nmppsWeightedSum_Set8__Fii12S_nmppsWeightedSumP.html
    \brief
        \ru Поэлементный минимум из двух векторов. 
        \en Generation of the vec of two vectors elementwise minima. 

   \ru  готовит матрицу для прохода по чётным и нечЁтным четвёркам пикселей из
	 \en
   
   \~
   \param W1
      \ru первый весовой коеффициент. Берутся 16 младших бит
   \param W2
      \ru второй весовой коеффициент. Берутся 16 младших бит
   \param kerW  
      \ru указатель на 20 двойных слов результата: 0,0,0,0,w1,w1a,w1b,w1c,0,0,0,0,
          \  w2,w2a,w2b,w2c,0,0,0,0 где
          \  w1a=w1<<16,w1b=w1<<32,w1c=w1<<48; и аналогично  для w2.
*/
   //! \{    

void nmppsWeightedSum_Set8(int W1,int W2, struct S_nmppsWeightedSum* kerW);
void nmppsWeightedSum_Set16(int W1,int W2, struct S_nmppsWeightedSum* kerW);
void nmppsWeightedSum_Set32(nm64s W1,nm64s W2, struct S_nmppsWeightedSum* kerW);

   //! \}


/*
	\defgroup nmppsWeightedSum_Exe nmppsWeightedSum_Exe
	\ingroup vArithmetics
    \fn void nmppsWeightedSum_Set8(int W1,int W2, S_nmppsWeightedSum* kerW);

    \perfinclude _nmppsWeightedSum_Set8__Fii12S_nmppsWeightedSumP.html
    \brief
        \ru Поэлементный минимум из двух векторов. 
        \en Generation of the vec of two vectors elementwise minima. 

   \ru  готовит матрицу для прохода по чётным и нечЁтным четвёркам пикселей из
	 \en
   
   \~
   \param W1
      \ru первый весовой коеффициент. Берутся 16 младших бит
   \param W2
      \ru второй весовой коеффициент. Берутся 16 младших бит
   \param kerW  
      \ru указатель на 20 двойных слов результата: 0,0,0,0,w1,w1a,w1b,w1c,0,0,0,0,
          \  w2,w2a,w2b,w2c,0,0,0,0 где
          \  w1a=w1<<16,w1b=w1<<32,w1c=w1<<48; и аналогично  для w2.


  \par
	\xmlonly
	 <testperf> 
			<param> pSrcVec1 </param> <values> L G </values>
			<param> pSrcVec2 </param> <values> L G </values>
			<param> pDstVec </param> <values> L G </values>
			<param> kerW </param> <values> L G </values>
			<param> nSize </param> <values> 8 128 1024 10240 </values>
			<size> nSize </size>
	 </testperf>
	\endxmlonly



*/
   // \{    
/* Расчёт линейной комбинации w1*Vec1 + w2*Vec2 по предварительно сформированной матрице из
    целых чисел w1 и w2.
    pDstVec[i]=W1*pSrcVec1[i]+W2*pSrcVec2[i] где W1 и W2 аргументы предварительно вызывавшейся
    nmppsWeightedSum_Set8( W1, W2, kerW);
*/

void nmppsWeightedSum_Exe_8s16s(nm8s* pSrcVec1,nm8s* pSrcVec2, struct S_nmppsWeightedSum* kerW, nm16s* pDstVec, int nSize);

// Расчёт линейной комбинации Vec1 и Vec2 по предварительно сформированной матрице с w1,w2
void nmppsWeightedSum_Exe_16s32s(nm16s* pSrcVec1,nm16s* pSrcVec2, struct S_nmppsWeightedSum* kerW, nm32s* pDstVec, int nSize);
// Расчёт линейной комбинации Vec1 и Vec2 по предварительно сформированной матрице с w1,w2
void nmppsWeightedSum_Exe_32s64s(nm32s* pSrcVec1,nm32s* pSrcVec2, struct S_nmppsWeightedSum* kerW, nm64s* pDstVec, int nSize);
   //! \}


//! 
//! \perfinclude _nmppsWeightedSum__FPciPciPSsi.html
//!				 
void nmppsWeightedSum_8s16s(nm8s* pSrcVec1,int W1,nm8s* pSrcVec2,int W2, nm16s* pDstVec, int nSize)
{
	struct S_nmppsWeightedSum kerW;
	nmppsWeightedSum_Set8(W1,W2,&kerW);
	nmppsWeightedSum_Exe_8s16s(pSrcVec1,pSrcVec2, &kerW, pDstVec, nSize);
}

//! 
//! \perfinclude _nmppsWeightedSum__FPSsiPSsiPii.html
//! 
void nmppsWeightedSum_16s32s(nm16s* pSrcVec1,int W1,nm16s* pSrcVec2,int W2, nm32s* pDstVec, int nSize)
{
	struct S_nmppsWeightedSum kerW;
	nmppsWeightedSum_Set16(W1,W2,&kerW);
	nmppsWeightedSum_Exe_16s32s(pSrcVec1,pSrcVec2, &kerW, pDstVec, nSize);
}
//! 
//! \perfinclude _nmppsWeightedSum__FPilPilPli.html
//! 
void nmppsWeightedSum_32s64s(nm32s* pSrcVec1, nm64s W1,nm32s* pSrcVec2, nm64s W2, nm64s* pDstVec, int nSize)
{
	struct S_nmppsWeightedSum kerW;
	nmppsWeightedSum_Set32(W1,W2, &kerW);
	nmppsWeightedSum_Exe_32s64s(pSrcVec1,pSrcVec2, &kerW, pDstVec, nSize);
}

