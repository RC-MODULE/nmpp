#ifndef _FFT_32FCR_H_INCLUDED_
#define _FFT_32FCR_H_INCLUDED_

#ifdef __cplusplus
		extern "C" {
#endif

#include "nmtype.h"

#define		NUMBUFF1		21
#define		NUMBUFF2		4

#define			pSrcVecFFTFwdInitAlloc_32fcr(SPEC, SIZE)				nmppsFFT##SIZE##FwdInitAlloc_32fcr(SPEC)
#define			FFTFwdInitAlloc_32fcr(SPEC, SIZE)				pSrcVecFFTFwdInitAlloc_32fcr(SPEC, SIZE)

#define			pSrcVecFFTInvInitAlloc_32fcr(SPEC, SIZE)				nmppsFFT##SIZE##InvInitAlloc_32fcr(SPEC)
#define			FFTInvInitAlloc_32fcr(SPEC, SIZE)				pSrcVecFFTInvInitAlloc_32fcr(SPEC, SIZE)

#define			pSrcVecFFTFwd_32fcr(SRC, DST, SPEC, SIZE)				nmppsFFT##SIZE##Fwd_32fcr(SRC, DST, SPEC)
#define			FFTFwd_32fcr(SRC, DST, SPEC, SIZE)				pSrcVecFFTFwd_32fcr(SRC, DST, SPEC, SIZE)

#define			pSrcVecFFTInv_32fcr(SRC, DST, SPEC, SIZE)				nmppsFFT##SIZE##Inv_32fcr(SRC, DST, SPEC)
#define			FFTInv_32fcr(SRC, DST, SPEC, SIZE)				pSrcVecFFTInv_32fcr(SRC, DST, SPEC, SIZE)

typedef struct
{
    nm32fcr* Buffers[NUMBUFF1];
    nm32fcr* Buffs[NUMBUFF2];
    int order;
} NmppsFFTSpec_32fcr;

// sFFT_32fcr

    /**
    \defgroup sFFTFwdInitAlloc FFTFwdInitAlloc
    \ingroup sFFT_32fcr

 *  \brief Функции инициализации структур коэффициентов, необходимых для вычисления прямого БПФ
 *
	\param [in] addr двойной указатель на структуру коэффициентов
	\return Функции возвращают 0 в случае успешной инициализации и число, отличное от нуля, в случае ошибок
 *  \details
 */
//! \{
int nmppsFFT16FwdInitAlloc_32fcr(NmppsFFTSpec_32fcr** addr);
int nmppsFFT32FwdInitAlloc_32fcr(NmppsFFTSpec_32fcr** addr);
int nmppsFFT64FwdInitAlloc_32fcr(NmppsFFTSpec_32fcr** addr);
int nmppsFFT128FwdInitAlloc_32fcr(NmppsFFTSpec_32fcr** addr);
int nmppsFFT256FwdInitAlloc_32fcr(NmppsFFTSpec_32fcr** addr);
int nmppsFFT512FwdInitAlloc_32fcr(NmppsFFTSpec_32fcr** addr);
int nmppsFFT1024FwdInitAlloc_32fcr(NmppsFFTSpec_32fcr** addr);
int nmppsFFT2048FwdInitAlloc_32fcr(NmppsFFTSpec_32fcr** addr);
int nmppsFFT4096FwdInitAlloc_32fcr(NmppsFFTSpec_32fcr** addr);
//! \}

    /**
    \defgroup sFFTInvInitAlloc FFTInvInitAlloc
    \ingroup sFFT_32fcr

 *  \brief Функции инициализации структур коэффициентов, необходимых для вычисления обратного БПФ
 *
	\param [in] addr двойной указатель на структуру коэффициентов
	\return Функции возвращают 0 в случае успешной инициализации и число, отличное от нуля, в случае ошибок
 *  \details
 */
//! \{
int nmppsFFT16InvInitAlloc_32fcr(NmppsFFTSpec_32fcr** addr);
int nmppsFFT32InvInitAlloc_32fcr(NmppsFFTSpec_32fcr** addr);
int nmppsFFT64InvInitAlloc_32fcr(NmppsFFTSpec_32fcr** addr);
int nmppsFFT128InvInitAlloc_32fcr(NmppsFFTSpec_32fcr** addr);
int nmppsFFT256InvInitAlloc_32fcr(NmppsFFTSpec_32fcr** addr);
int nmppsFFT512InvInitAlloc_32fcr(NmppsFFTSpec_32fcr** addr);
int nmppsFFT1024InvInitAlloc_32fcr(NmppsFFTSpec_32fcr** addr);
int nmppsFFT2048InvInitAlloc_32fcr(NmppsFFTSpec_32fcr** addr);
int nmppsFFT4096InvInitAlloc_32fcr(NmppsFFTSpec_32fcr** addr);
//! \}

    /**
    \defgroup sDFT-8 DFT-8
    \ingroup sFFT_32fcr
   	\brief Функция для вычисления прямого ДПФ с плавающей точкой над вектором, состоящим из 8 комплексных чисел
    */
	/**
 *  \ingroup sDFT-8
	\brief Функция для вычисления прямого ДПФ с плавающей точкой над вектором, состоящим из 8 комплексных чисел

	\param [in] pSrcVec входной вектор комплексных чисел (на мнимая и действительная части имеют тип float)
	\retval [out] pDstVec выходной вектор комплексных чисел (на мнимая и действительная части имеют тип float)
	\param [in] spec структра, содержащая необходимые коэффициенты, для вычисления прямого БПФ определенного размера
 */
//! \{
void nmppsDFT8Fwd_32fcr(const nm32fcr* pSrcVec, nm32fcr* pDstVec, NmppsFFTSpec_32fcr* spec);
//! \}

    /**
    \defgroup sFFT-16 FFT-16
    \ingroup sFFT_32fcr

	\brief Функция для вычисления прямого БПФ с плавающей точкой над вектором, состоящим из 16 комплексных чисел

	\param [in] pSrcVec входной вектор комплексных чисел (на мнимая и действительная части имеют тип float)
	\retval [out] pDstVec выходной вектор комплексных чисел (на мнимая и действительная части имеют тип float)
	\param [in] spec структра, содержащая необходимые коэффициенты, для вычисления прямого БПФ определенного размера
 */
//! \{
void nmppsFFT16Fwd_32fcr(const nm32fcr* pSrcVec, nm32fcr* pDstVec, NmppsFFTSpec_32fcr* spec);
//! \}

    /**
    \defgroup sFFT-32 FFT-32
    \ingroup sFFT_32fcr

	\brief Функция для вычисления прямого БПФ с плавающей точкой над вектором, состоящим из 32 комплексных чисел

	\param [in] pSrcVec входной вектор комплексных чисел (на мнимая и действительная части имеют тип float)
	\retval [out] pDstVec выходной вектор комплексных чисел (на мнимая и действительная части имеют тип float)
	\param [in] spec структра, содержащая необходимые коэффициенты, для вычисления прямого БПФ определенного размера
    \par
    \xmlonly
        <testperf>
		 <init>
		     NmppsFFTSpec_32fcr* spec;
		     nmppsFFT32FwdInitAlloc_32fcr(&amp;spec);
		 </init>
             <param name=" pSrcVec "> im1 im2 im3 im4 im5 </param>
             <param name=" pDstVec "> im1 im2 im3 im4 im5 </param>
    		 <size> 32 </size>
        </testperf>
    \endxmlonly

 *
 */
//! \{
void nmppsFFT32Fwd_32fcr(const nm32fcr* pSrcVec, nm32fcr* pDstVec, NmppsFFTSpec_32fcr* spec);
//! \}

    /**
    \defgroup sFFT-64 FFT-64
    \ingroup sFFT_32fcr

	\brief Функция для вычисления прямого БПФ с плавающей точкой над вектором, состоящим из 64 комплексных чисел

	\param [in] pSrcVec входной вектор комплексных чисел (на мнимая и действительная части имеют тип float)
	\retval [out] pDstVec выходной вектор комплексных чисел (на мнимая и действительная части имеют тип float)
	\param [in] spec структра, содержащая необходимые коэффициенты, для вычисления прямого БПФ определенного размера
    \par
    \xmlonly
        <testperf>
		 <init>
		     NmppsFFTSpec_32fcr* spec;
		     nmppsFFT64FwdInitAlloc_32fcr(&amp;spec);
		 </init>
             <param name=" pSrcVec "> im1 im2 im3 im4 im5 </param>
             <param name=" pDstVec "> im1 im2 im3 im4 im5 </param>
    		 <size> 64 </size>
        </testperf>
    \endxmlonly

 *
 */
//! \{
void nmppsFFT64Fwd_32fcr(const nm32fcr* pSrcVec, nm32fcr* pDstVec, NmppsFFTSpec_32fcr* spec);
//! \}

    /**
    \defgroup sFFT-128 FFT-128
    \ingroup sFFT_32fcr

	\brief Функция для вычисления прямого БПФ с плавающей точкой над вектором, состоящим из 128 комплексных чисел

	\param [in] pSrcVec входной вектор комплексных чисел (на мнимая и действительная части имеют тип float)
	\retval [out] pDstVec выходной вектор комплексных чисел (на мнимая и действительная части имеют тип float)
	\param [in] spec структра, содержащая необходимые коэффициенты, для вычисления прямого БПФ определенного размера
	\par
    \xmlonly
        <testperf>
		 <init>
		     NmppsFFTSpec_32fcr* spec;
		     nmppsFFT128FwdInitAlloc_32fcr(&amp;spec);
		 </init>
             <param name=" pSrcVec "> im1 im2 im3 im4 im5 </param>
             <param name=" pDstVec "> im1 im2 im3 im4 im5 </param>
    		 <size> 128 </size>
        </testperf>
    \endxmlonly
 *
 */
//! \{
void nmppsFFT128Fwd_32fcr(const nm32fcr* pSrcVec, nm32fcr* pDstVec, NmppsFFTSpec_32fcr* spec);
//! \}

    /**
    \defgroup sFFT-256 FFT-256
    \ingroup sFFT_32fcr

	\brief Функция для вычисления прямого БПФ с плавающей точкой над вектором, состоящим из 256 комплексных чисел

	\param [in] pSrcVec входной вектор комплексных чисел (на мнимая и действительная части имеют тип float)
	\retval [out] pDstVec выходной вектор комплексных чисел (на мнимая и действительная части имеют тип float)
	\param [in] spec структра, содержащая необходимые коэффициенты, для вычисления прямого БПФ определенного размера
 *  \details Для достижения максимальной производительности (1763 такта) необходимо положить входной вектор в 1-ый банк, выходной вектор в 5-ый банк
 *  \par
    \xmlonly
        <testperf>
		 <init>
		     NmppsFFTSpec_32fcr* spec;
		     nmppsFFT256FwdInitAlloc_32fcr(&amp;spec);
		 </init>
             <param name=" pSrcVec "> im1 im2 im3 im4 im5 </param>
             <param name=" pDstVec "> im1 im2 im3 im4 im5 </param>
    		 <size> 256 </size>
        </testperf>
    \endxmlonly
 *
 */
//! \{
void nmppsFFT256Fwd_32fcr(const nm32fcr* pSrcVec, nm32fcr* pDstVec, NmppsFFTSpec_32fcr* spec);
//! \}

    /**
    \defgroup sFFT-512 FFT-512
    \ingroup sFFT_32fcr

	\ingroup sFFT-512
	\brief Функция для вычисления прямого БПФ с плавающей точкой над вектором, состоящим из 512 комплексных чисел

	\param [in] pSrcVec входной вектор комплексных чисел (на мнимая и действительная части имеют тип float)
	\retval [out] pDstVec выходной вектор комплексных чисел (на мнимая и действительная части имеют тип float)
	\param [in] spec структра, содержащая необходимые коэффициенты, для вычисления прямого БПФ определенного размера
 *  \details Для достижения максимальной производительности (3675 такта) необходимо положить входной вектор в 2-ый банк, выходной вектор в 5-ый банк
 *  \par
    \xmlonly
        <testperf>
		 <init>
		     NmppsFFTSpec_32fcr* spec;
		     nmppsFFT512FwdInitAlloc_32fcr(&amp;spec);
		 </init>
             <param name=" pSrcVec "> im1 im2 im3 im4 im5 </param>
             <param name=" pDstVec "> im1 im2 im3 im4 im5 </param>
    		 <size> 512 </size>
        </testperf>
    \endxmlonly
 */
//! \{
void nmppsFFT512Fwd_32fcr(const nm32fcr* pSrcVec, nm32fcr* pDstVec, NmppsFFTSpec_32fcr* spec);
//! \}

    /**
    \defgroup sFFT-1024 FFT-1024
    \ingroup sFFT_32fcr

	\brief Функция для вычисления прямого БПФ с плавающей точкой над вектором, состоящим из 1024 комплексных чисел

	\param [in] pSrcVec входной вектор комплексных чисел (на мнимая и действительная части имеют тип float)
	\retval [out] pDstVec выходной вектор комплексных чисел (на мнимая и действительная части имеют тип float)
	\param [in] spec структра, содержащая необходимые коэффициенты, для вычисления прямого БПФ определенного размера
 *  \details Для достижения максимальной производительности (8655 такта) необходимо положить входной вектор в 6-ый банк, выходной вектор в 5-ый банк
 *  \par
    \xmlonly
        <testperf>
		 <init>
		     NmppsFFTSpec_32fcr* spec;
		     nmppsFFT1024FwdInitAlloc_32fcr(&amp;spec);
		 </init>
             <param name=" pSrcVec "> im1 im2 im3 im4 im5 </param>
             <param name=" pDstVec "> im1 im2 im3 im4 im5 </param>
    		 <size> 1024 </size>
        </testperf>
    \endxmlonly
 */
//! \{
void nmppsFFT1024Fwd_32fcr(const nm32fcr* pSrcVec, nm32fcr* pDstVec, NmppsFFTSpec_32fcr* spec);
//! \}

    /**
    \defgroup sFFT-2048 FFT-2048
    \ingroup sFFT_32fcr

	\brief Функция для вычисления прямого БПФ с плавающей точкой над вектором, состоящим из 2048 комплексных чисел

	\param [in] pSrcVec входной вектор комплексных чисел (на мнимая и действительная части имеют тип float)
	\retval [out] pDstVec выходной вектор комплексных чисел (на мнимая и действительная части имеют тип float)
	\param [in] spec структра, содержащая необходимые коэффициенты, для вычисления прямого БПФ определенного размера
 *  \details Для достижения максимальной производительности (19504 такта) необходимо положить входной вектор в 5-ый банк, выходной вектор в 5-ый банк
 *  \par
    \xmlonly
        <testperf>
		 <init>
		     NmppsFFTSpec_32fcr* spec;
		     nmppsFFT2048FwdInitAlloc_32fcr(&amp;spec);
		 </init>
             <param name=" pSrcVec "> im1 im2 im3 im4 im5 </param>
             <param name=" pDstVec "> im1 im2 im3 im4 im5 </param>
    		 <size> 2048 </size>
        </testperf>
    \endxmlonly
 */
//! \{
void nmppsFFT2048Fwd_32fcr(const nm32fcr* pSrcVec, nm32fcr* pDstVec, NmppsFFTSpec_32fcr* spec);
//! \}

    /**
    \defgroup sFFT-4096 FFT-4096
    \ingroup sFFT_32fcr
	\brief Функция для вычисления прямого БПФ с плавающей точкой над вектором, состоящим из 4096 комплексных чисел

	\param [in] pSrcVec входной вектор комплексных чисел (на мнимая и действительная части имеют тип float)
	\retval [out] pDstVec выходной вектор комплексных чисел (на мнимая и действительная части имеют тип float)
	\param [in] spec структра, содержащая необходимые коэффициенты, для вычисления прямого БПФ определенного размера
 *  \details Для достижения максимальной производительности (54258 такта) необходимо положить входной вектор в 5-ый банк, выходной вектор в 5-ый банк
 *  \par
    \xmlonly
        <testperf>
		 <init>
		     NmppsFFTSpec_32fcr* spec;
		     nmppsFFT4096FwdInitAlloc_32fcr(&amp;spec);
		 </init>
             <param name=" pSrcVec "> im1 im3 im4 im5 </param>
             <param name=" pDstVec "> im2 im3 im4 im5 </param>
    		 <size> 4096 </size>
        </testperf>
    \endxmlonly
*/
//! \{
void nmppsFFT4096Fwd_32fcr(const nm32fcr* pSrcVec, nm32fcr* pDstVec, NmppsFFTSpec_32fcr* spec);
//! \}


	/**
    \defgroup sIDFT-8 IDFT-8
    \ingroup sFFT_32fcr

	\brief Функция для вычисления обратного ДПФ с плавающей точкой над вектором, состоящим из 8 комплексных чисел

	\param [in] pSrcVec входной вектор комплексных чисел (на мнимая и действительная части имеют тип float)
	\retval [out] pDstVec выходной вектор комплексных чисел (на мнимая и действительная части имеют тип float)
	\param [in] spec структра, содержащая необходимые коэффициенты, для вычисления обратного БПФ определенного размера
 *
 */
//! \{
void nmppsDFT8Inv_32fcr(const nm32fcr* pSrcVec, nm32fcr* pDstVec, NmppsFFTSpec_32fcr* spec);
//! \}


	/**
    \defgroup sIFFT-16 IFFT-16
    \ingroup sFFT_32fcr
	\brief Функция для вычисления обратного БПФ с плавающей точкой над вектором, состоящим из 16 комплексных чисел

	\param [in] pSrcVec входной вектор комплексных чисел (на мнимая и действительная части имеют тип float)
	\retval [out] pDstVec выходной вектор комплексных чисел (на мнимая и действительная части имеют тип float)
	\param [in] spec структра, содержащая необходимые коэффициенты, для вычисления обратного БПФ определенного размера
*/
//! \{
void nmppsFFT16Inv_32fcr(const nm32fcr* pSrcVec, nm32fcr* pDstVec, NmppsFFTSpec_32fcr* spec);
//! \}


	/**
    \defgroup sIFFT-32 IFFT-32
    \ingroup sFFT_32fcr

	\brief Функция для вычисления обратного БПФ с плавающей точкой над вектором, состоящим из 32 комплексных чисел

	\param [in] pSrcVec входной вектор комплексных чисел (на мнимая и действительная части имеют тип float)
	\retval [out] pDstVec выходной вектор комплексных чисел (на мнимая и действительная части имеют тип float)
	\param [in] spec структра, содержащая необходимые коэффициенты, для вычисления обратного БПФ определенного размера
	\par
    \xmlonly
        <testperf>
		 <init>
		     NmppsFFTSpec_32fcr* spec;
		     nmppsFFT32InvInitAlloc_32fcr(&amp;spec);
		 </init>
             <param name=" pSrcVec "> im1 im2 im3 im4 im5 </param>
             <param name=" pDstVec "> im1 im2 im3 im4 im5 </param>
    		 <size> 32 </size>
        </testperf>
    \endxmlonly

 */
//! \{
void nmppsFFT32Inv_32fcr(const nm32fcr* pSrcVec, nm32fcr* pDstVec, NmppsFFTSpec_32fcr* spec);
//! \}


	/**
    \defgroup sIFFT-64 IFFT-64
    \ingroup sFFT_32fcr

	\brief Функция для вычисления обратного БПФ с плавающей точкой над вектором, состоящим из 64 комплексных чисел

	\param [in] pSrcVec входной вектор комплексных чисел (на мнимая и действительная части имеют тип float)
	\retval [out] pDstVec выходной вектор комплексных чисел (на мнимая и действительная части имеют тип float)
	\param [in] spec структра, содержащая необходимые коэффициенты, для вычисления обратного БПФ определенного размера
	\par
    \xmlonly
        <testperf>
		 <init>
		     NmppsFFTSpec_32fcr* spec;
		     nmppsFFT64InvInitAlloc_32fcr(&amp;spec);
		 </init>
             <param name=" pSrcVec "> im1 im2 im3 im4 im5 </param>
             <param name=" pDstVec "> im1 im2 im3 im4 im5 </param>
    		 <size> 64 </size>
        </testperf>
    \endxmlonly

*/
//! \{
void nmppsFFT64Inv_32fcr(const nm32fcr* pSrcVec, nm32fcr* pDstVec, NmppsFFTSpec_32fcr* spec);
//! \}


	/**
    \defgroup sIFFT-128 IFFT-128
    \ingroup sFFT_32fcr

	\brief Функция для вычисления обратного БПФ с плавающей точкой над вектором, состоящим из 128 комплексных чисел

	\param [in] pSrcVec входной вектор комплексных чисел (на мнимая и действительная части имеют тип float)
	\retval [out] pDstVec выходной вектор комплексных чисел (на мнимая и действительная части имеют тип float)
	\param [in] spec структра, содержащая необходимые коэффициенты, для вычисления обратного БПФ определенного размера
	\par
    \xmlonly
        <testperf>
		 <init>
		     NmppsFFTSpec_32fcr* spec;
		     nmppsFFT128InvInitAlloc_32fcr(&amp;spec);
		 </init>
             <param name=" pSrcVec "> im1 im2 im3 im4 im5 </param>
             <param name=" pDstVec "> im1 im2 im3 im4 im5 </param>
    		 <size> 128 </size>
        </testperf>
    \endxmlonly
 *
 */
//! \{
void nmppsFFT128Inv_32fcr(const nm32fcr* pSrcVec, nm32fcr* pDstVec, NmppsFFTSpec_32fcr* spec);
//! \}

	/**
    \defgroup sIFFT-256 IFFT-256
    \ingroup sFFT_32fcr

	\brief Функция для вычисления обратного БПФ с плавающей точкой над вектором, состоящим из 256 комплексных чисел

	\param [in] pSrcVec входной вектор комплексных чисел (на мнимая и действительная части имеют тип float)
	\retval [out] pDstVec выходной вектор комплексных чисел (на мнимая и действительная части имеют тип float)
	\param [in] spec структра, содержащая необходимые коэффициенты, для вычисления обратного БПФ определенного размера
*  \details Для достижения максимальной производительности (1763 такта) необходимо положить входной вектор в 1-ый банк, выходной вектор в 5-ый банк
	\par
    \xmlonly
        <testperf>
		 <init>
		     NmppsFFTSpec_32fcr* spec;
		     nmppsFFT256InvInitAlloc_32fcr(&amp;spec);
		 </init>
             <param name=" pSrcVec "> im1 im2 im3 im4 im5 </param>
             <param name=" pDstVec "> im1 im2 im3 im4 im5 </param>
    		 <size> 256 </size>
        </testperf>
    \endxmlonly
 */
//! \{
void nmppsFFT256Inv_32fcr(const nm32fcr* pSrcVec, nm32fcr* pDstVec, NmppsFFTSpec_32fcr* spec);
//! \}


	/**
    \defgroup sIFFT-512 IFFT-512
    \ingroup sFFT_32fcr

	\brief Функция для вычисления обратного БПФ с плавающей точкой над вектором, состоящим из 512 комплексных чисел

	\param [in] pSrcVec входной вектор комплексных чисел (на мнимая и действительная части имеют тип float)
	\retval [out] pDstVec выходной вектор комплексных чисел (на мнимая и действительная части имеют тип float)
	\param [in] spec структра, содержащая необходимые коэффициенты, для вычисления обратного БПФ определенного размера
 *  \details Для достижения максимальной производительности (3675 такта) необходимо положить входной вектор в 2-ый банк, выходной вектор в 5-ый банк
    \par
    \xmlonly
        <testperf>
		 <init>
		     NmppsFFTSpec_32fcr* spec;
		     nmppsFFT512InvInitAlloc_32fcr(&amp;spec);
		 </init>
             <param name=" pSrcVec "> im1 im2 im3 im4 im5 </param>
             <param name=" pDstVec "> im1 im2 im3 im4 im5 </param>
    		 <size> 512 </size>
        </testperf>
    \endxmlonly
 */
//! \{
void nmppsFFT512Inv_32fcr(const nm32fcr* pSrcVec, nm32fcr* pDstVec, NmppsFFTSpec_32fcr* spec);
//! \}

	/**
    \defgroup sIFFT-1024 IFFT-1024
    \ingroup sFFT_32fcr
    */


	/**
 *  \ingroup sIFFT-1024
	\brief Функция для вычисления обратного БПФ с плавающей точкой над вектором, состоящим из 1024 комплексных чисел

	\param [in] pSrcVec входной вектор комплексных чисел (на мнимая и действительная части имеют тип float)
	\retval [out] pDstVec выходной вектор комплексных чисел (на мнимая и действительная части имеют тип float)
	\param [in] spec структра, содержащая необходимые коэффициенты, для вычисления обратного БПФ определенного размера
 *  \details Для достижения максимальной производительности (8655 такта) необходимо положить входной вектор в 6-ый банк, выходной вектор в 5-ый банк
 *  \par
    \xmlonly
        <testperf>
		 <init>
		     NmppsFFTSpec_32fcr* spec;
		     nmppsFFT1024InvInitAlloc_32fcr(&amp;spec);
		 </init>
             <param name=" pSrcVec "> im1 im2 im3 im4 im5 </param>
             <param name=" pDstVec "> im1 im2 im3 im4 im5 </param>
    		 <size> 1024 </size>
        </testperf>
    \endxmlonly
 */
//! \{
void nmppsFFT1024Inv_32fcr(const nm32fcr* pSrcVec, nm32fcr* pDstVec, NmppsFFTSpec_32fcr* spec);
//! \}

	/**
    \defgroup sIFFT-2048 IFFT-2048
    \ingroup sFFT_32fcr

	\brief Функция для вычисления обратного БПФ с плавающей точкой над вектором, состоящим из 2048 комплексных чисел

	\param [in] pSrcVec входной вектор комплексных чисел (на мнимая и действительная части имеют тип float)
	\retval [out] pDstVec выходной вектор комплексных чисел (на мнимая и действительная части имеют тип float)
	\param [in] spec структра, содержащая необходимые коэффициенты, для вычисления обратного БПФ определенного размера
 *  \details Для достижения максимальной производительности (19504 такта) необходимо положить входной вектор в 5-ый банк, выходной вектор в 5-ый банк
 *  \par
    \xmlonly
        <testperf>
		 <init>
		     NmppsFFTSpec_32fcr* spec;
		     nmppsFFT2048InvInitAlloc_32fcr(&amp;spec);
		 </init>
             <param name=" pSrcVec "> im1 im2 im3 im4 im5 </param>
             <param name=" pDstVec "> im1 im2 im3 im4 im5 </param>
    		 <size> 2048 </size>
        </testperf>
    \endxmlonly
 */
//! \{
void nmppsFFT2048Inv_32fcr(const nm32fcr* pSrcVec, nm32fcr* pDstVec, NmppsFFTSpec_32fcr* spec);
//! \}

	/**
    \defgroup sIFFT-4096 IFFT-4096
    \ingroup sFFT_32fcr

	\brief Функция для вычисления обратного БПФ с плавающей точкой над вектором, состоящим из 4096 комплексных чисел

	\param [in] pSrcVec входной вектор комплексных чисел (на мнимая и действительная части имеют тип float)
	\retval [out] pDstVec выходной вектор комплексных чисел (на мнимая и действительная части имеют тип float)
	\param [in] spec структра, содержащая необходимые коэффициенты, для вычисления обратного БПФ определенного размера
 *  \details Для достижения максимальной производительности (54258 такта) необходимо положить входной вектор в 5-ый банк, выходной вектор в 5-ый банк
 *  \par
    \xmlonly
        <testperf>
		 <init>
		     NmppsFFTSpec_32fcr* spec;
		     nmppsFFT4096InvInitAlloc_32fcr(&amp;spec);
		 </init>
             <param name=" pSrcVec "> im1 im3 im4 im5 </param>
             <param name=" pDstVec "> im2 im3 im4 im5 </param>
    		 <size> 4096 </size>
        </testperf>
    \endxmlonly
 */
//! \{
void nmppsFFT4096Inv_32fcr(const nm32fcr* pSrcVec, nm32fcr* pDstVec, NmppsFFTSpec_32fcr* spec);
//! \}

	/**
    \defgroup sFFT-Common FFT-Common
    \ingroup sFFT_32fcr
    */
	/**
 *  \ingroup sFFT-Common
	\brief Функция для вычисления прямого БПФ с плавающей точкой над вектором длины от 8 до 2048

	\param [in] pSrcVec входной вектор комплексных чисел (на мнимая и действительная части имеют тип float)
	\retval [out] pDstVec выходной вектор комплексных чисел (на мнимая и действительная части имеют тип float)
	\param [in] spec структра, содержащая необходимые коэффициенты, для вычисления прямого БПФ определенного размера
 *
 */
//int nmppsFFTFwd_32fcr(const nm32fcr* pSrcVec, nm32fcr* pDstVec, NmppsFFTSpec_32fcr *Spc);


/**
 *  \ingroup sFFT-Common
 *  \brief Функция инициализации структуры коэффициентов, необходимых для вычисления прямого БПФ с плавающей точкой над вектором длины от 8 до 2048
 *
 *	\param [in] spec двойной указатель на структуру коэффициентов
 *  \param [in] order размерность БПФ, которое нужно вычислить, например, для БПФ256 этот параметр равен 8 (т.к. 2^8 = 256)
 *  \return Функция возвращают 0 в случае успешной инициализации и отрицательное число (от -1 и меньше) в случае ошибок
 *  \details
 */
//int nmppsFFTFwdInitAlloc_32fcr(NmppsFFTSpec_32fcr** spec, int order);





	/**
    \defgroup sIFFT-Common IFFT-Common
    \ingroup sFFT_32fcr

	\brief Функция для вычисления обратного БПФ с плавающей точкой над вектором длины от 8 до 2048

	\param [in] pSrcVec входной вектор комплексных чисел (на мнимая и действительная части имеют тип float)
	\retval [out] pDstVec выходной вектор комплексных чисел (на мнимая и действительная части имеют тип float)
	\param [in] spec структра, содержащая необходимые коэффициенты, для вычисления обратного БПФ определенного размера
 *
 */
//int nmppsFFTInv_32fcr(const nm32fcr* pSrcVec, nm32fcr* pDstVec, NmppsFFTSpec_32fcr* spec);


/**
 *  \ingroup sIFFT-Common
 *  \brief Функция инициализации структуры коэффициентов, необходимых для вычисления обратного БПФ с плавающей точкой над вектором длины от 8 до 2048
 *
 *	\param [in] spec двойной указатель на структуру коэффициентов
 *  \param [in] order размерность БПФ, которое нужно вычислить, например, для БПФ256 этот параметр равен 8 (т.к. 2^8 = 256)
 *  \return Функция возвращают 0 в случае успешной инициализации и отрицательное число (от -1 и меньше) в случае ошибок
 *  \details
 */
//int nmppsFFTInvInitAlloc_32fcr(NmppsFFTSpec_32fcr** spec, int order);







	/**
 *  \ingroup sFFT_32fcr
	\brief Функция освобождает память, выделенную под коэффициенты, необходимые для вычисления БПФ определенного размера

	\param [in] spec структра, содержащая необходимые коэффициенты, для вычисления обратного БПФ определенного размера
    \return Функция возвращают 0 в случае успешной инициализации и отрицательное число (от -1 и меньше) в случае ошибок
 *
 */
int nmppsFFTFree_32fcr(NmppsFFTSpec_32fcr* spec);

#ifdef __cplusplus
		};
#endif

#endif // _FFT_32FCR_H_INCLUDED_
