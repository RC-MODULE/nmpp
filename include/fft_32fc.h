#ifndef _FFT_32FC_H_INCLUDED_
#define _FFT_32FC_H_INCLUDED_

#ifdef __cplusplus
		extern "C" {
#endif

#include "nmtype.h"


#define		NUMBUFF1		21
#define		NUMBUFF2		4

typedef struct
{   
    nm32fcr *Buffers[NUMBUFF1];
    nm32fcr *Buffs[NUMBUFF2];
    int order;
} NmppsFFTSpec_32fc;

typedef struct
{
  NmppsFFTSpec_32fc *specX;
  NmppsFFTSpec_32fc *specY;
} NmppiFFTSpec_32fc;

// sFFT_32fc


    /**
    \defgroup sFFT_Fwd FFTFwd_32fc
    \ingroup sFFT_32fc
   	\brief Функции для вычисления прямого БПФ с плавающей точкой на векторами комплексных чисел
	
	\param [in] x входной вектор комплексных чисел (на мнимая и действительная части имеют тип float)
	\retval [out] X выходной вектор комплексных чисел (на мнимая и действительная части имеют тип float)
	\param [in] spec структра, содержащая необходимые коэффициенты, для вычисления прямого БПФ определенного размера
    */
    //! \{
void nmppsDFT8Fwd_32fc(nm32fcr *x, nm32fcr *X, NmppsFFTSpec_32fc *spec);
void nmppsFFT16Fwd_32fc(nm32fcr *x, nm32fcr *X, NmppsFFTSpec_32fc *spec);
void nmppsFFT32Fwd_32fc(nm32fcr *x, nm32fcr *X, NmppsFFTSpec_32fc *spec);
void nmppsFFT64Fwd_32fc(nm32fcr *x, nm32fcr *X, NmppsFFTSpec_32fc *spec);
void nmppsFFT128Fwd_32fc(nm32fcr *x, nm32fcr *X, NmppsFFTSpec_32fc *spec);
void nmppsFFT256Fwd_32fc(nm32fcr *x, nm32fcr *X, NmppsFFTSpec_32fc *spec);
void nmppsFFT512Fwd_32fc(nm32fcr *x, nm32fcr *X, NmppsFFTSpec_32fc *spec);
void nmppsFFT1024Fwd_32fc(nm32fcr *x, nm32fcr *X, NmppsFFTSpec_32fc *spec);
void nmppsFFT2048Fwd_32fc(nm32fcr *x, nm32fcr *X, NmppsFFTSpec_32fc *spec);
    //! \}
	


	
    /**
    \defgroup sFFT_Fwd FFTInv
    \ingroup sFFT_32fc
   	\brief Функции для вычисления обратного БПФ с плавающей точкой на векторами комплексных чисел
	
	\param [in] x входной вектор комплексных чисел (на мнимая и действительная части имеют тип float)
	\retval [out] X выходной вектор комплексных чисел (на мнимая и действительная части имеют тип float)
	\param [in] ispec структра, содержащая необходимые коэффициенты, для вычисления обратного БПФ определенного размера
    */
    //! \{
void nmppsDFT8Inv_32fc(nm32fcr *ix, nm32fcr *iX, NmppsFFTSpec_32fc *ispec);
void nmppsFFT16Inv_32fc(nm32fcr *ix, nm32fcr *iX, NmppsFFTSpec_32fc *ispec);
void nmppsFFT32Inv_32fc(nm32fcr *ix, nm32fcr *iX, NmppsFFTSpec_32fc *ispec);
void nmppsFFT64Inv_32fc(nm32fcr *ix, nm32fcr *iX, NmppsFFTSpec_32fc *ispec);
void nmppsFFT128Inv_32fc(nm32fcr *ix, nm32fcr *iX, NmppsFFTSpec_32fc *ispec);
void nmppsFFT256Inv_32fc(nm32fcr *ix, nm32fcr *iX, NmppsFFTSpec_32fc *ispec);
void nmppsFFT512Inv_32fc(nm32fcr *ix, nm32fcr *iX, NmppsFFTSpec_32fc *ispec);
void nmppsFFT1024Inv_32fc(nm32fcr *ix, nm32fcr *iX, NmppsFFTSpec_32fc *ispec);
void nmppsFFT2048Inv_32fc(nm32fcr *ix, nm32fcr *iX, NmppsFFTSpec_32fc *ispec);
    //! \}	

/**
 *  \ingroup sFFT_32fc
 *  \brief Функция для вычисления прямого БПФ с плавающей точкой на векторами комплексных чисел
 *  
 *  \param [in] x входной вектор комплексных чисел (на мнимая и действительная части имеют тип float)
 *  \param [in] X выходной вектор комплексных чисел (на мнимая и действительная части имеют тип float)
 *  \param [in] Spc структра, содержащая необходимые коэффициенты, для вычисления прямого БПФ определенного размера
 *  \return Функция возвращают 0 в случае успешной инициализации и отрицательное число (от -1 и меньше) в случае ошибок
 * 
 */
int nmppsFFTFwd_32fc(nm32fcr *x, nm32fcr *X, NmppsFFTSpec_32fc *Spc);

/**
 *  \ingroup sFFT_32fc
 *  \brief Функция для вычисления обратного БПФ с плавающей точкой на векторами комплексных чисел
 *  
 *  \param [in] ix входной вектор комплексных чисел (на мнимая и действительная части имеют тип float)
 *  \param [in] iX выходной вектор комплексных чисел (на мнимая и действительная части имеют тип float)
 *  \param [in] iSpc структра, содержащая необходимые коэффициенты, для вычисления обратного БПФ определенного размера
 *  \return Функция возвращают 0 в случае успешной инициализации и отрицательное число (от -1 и меньше) в случае ошибок
 * 
 */
int nmppsFFTInv_32fc(nm32fcr *ix, nm32fcr *iX, NmppsFFTSpec_32fc *iSpc);


    /**
    \defgroup sFFT_Fwd FFTInvInitAlloc
    \ingroup sFFT_32fc
   	\brief Функции инициализации структур коэффициентов, необходимых для вычисления обратного БПФ определенного размера
	
	\param [in] iaddr двойной указатель на структуру коэффициентов
	\return Функции возвращают 0 в случае успешной инициализации и отрицательное число (от -1 и меньше) в случае ошибок
    */
    //! \{
int nmppsFFT16InvInitAlloc_32fc(NmppsFFTSpec_32fc **iaddr);
int nmppsFFT32InvInitAlloc_32fc(NmppsFFTSpec_32fc **iaddr);
int nmppsFFT64InvInitAlloc_32fc(NmppsFFTSpec_32fc **iaddr);
int nmppsFFT128InvInitAlloc_32fc(NmppsFFTSpec_32fc **iaddr);
int nmppsFFT256InvInitAlloc_32fc(NmppsFFTSpec_32fc **iaddr);
int nmppsFFT512InvInitAlloc_32fc(NmppsFFTSpec_32fc **iaddr);
int nmppsFFT1024InvInitAlloc_32fc(NmppsFFTSpec_32fc **iaddr);
int nmppsFFT2048InvInitAlloc_32fc(NmppsFFTSpec_32fc **iaddr);
    //! \}	


    /**
    \defgroup sFFT_Fwd FFTFwdInitAlloc
    \ingroup sFFT_32fc
   	\brief Функции инициализации структур коэффициентов, необходимых для вычисления прямого БПФ определенного размера
	
	\param [in] addr двойной указатель на структуру коэффициентов
	\return Функции возвращают 0 в случае успешной инициализации и отрицательное число (от -1 и меньше) в случае ошибок
    */
    //! \{
int nmppsFFT16FwdInitAlloc_32fc(NmppsFFTSpec_32fc **addr);
int nmppsFFT32FwdInitAlloc_32fc(NmppsFFTSpec_32fc **addr);
int nmppsFFT64FwdInitAlloc_32fc(NmppsFFTSpec_32fc **addr);
int nmppsFFT128FwdInitAlloc_32fc(NmppsFFTSpec_32fc **addr);
int nmppsFFT256FwdInitAlloc_32fc(NmppsFFTSpec_32fc **addr);
int nmppsFFT512FwdInitAlloc_32fc(NmppsFFTSpec_32fc **addr);
int nmppsFFT1024FwdInitAlloc_32fc(NmppsFFTSpec_32fc **addr);
int nmppsFFT2048FwdInitAlloc_32fc(NmppsFFTSpec_32fc **addr);
    //! \}	

/**
 *  \ingroup sFFT_32fc
 *  \brief Функция инициализации структур коэффициентов, необходимых для вычисления прямого БПФ определенного размера
 *  
 *  \param [in] Spec двойной указатель на структуру коэффициентов
 *  \param [in] Order размерность БПФ, которое нужно вычислить, например, для БПФ256 этот параметр равен 8 (т.к. 2^8 = 256)
 *  \return Функция возвращают 0 в случае успешной инициализации и отрицательное число (от -1 и меньше) в случае ошибок
 *  \details 
 */
int nmppsFFTFwdInitAlloc_32fc(NmppsFFTSpec_32fc **Spec, int Order);

/**
 *  \ingroup sFFT_32fc
 *  \brief Функция инициализации структур коэффициентов, необходимых для вычисления обратного БПФ определенного размера
 *  
 *  \param [in] iSpec двойной указатель на структуру коэффициентов
 *  \param [in] iOrder размерность БПФ, которое нужно вычислить, например, для БПФ256 этот параметр равен 8 (т.к. 2^8 = 256)
 *  \return Функция возвращают 0 в случае успешной инициализации и отрицательное число (от -1 и меньше) в случае ошибок
 *  \details 
 */
int nmppsFFTInvInitAlloc_32fc(NmppsFFTSpec_32fc **iSpec, int iOrder);


/**
 *  \ingroup sFFT_32fc
 *  \brief Функция освобождает память, выделенную под коэффициенты, хранящиеся в структуре spec
 *  
 *  \param [in] spec указатель на структуру коэффициентов
 *  \return возвращает 0 в случае успешного освобождения памяти и -1 в случае ошибки
 */
int nmppsFFTFree_32fc(NmppsFFTSpec_32fc *spec);

#ifdef __cplusplus
		};
#endif

#endif // _FFT_32FC_H_INCLUDED_