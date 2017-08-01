//***************************************************************************/
//*                                                                         */
//*                    Neuroprocessor NM6403 SDK v.1.2                      */
//*                                                                         */
//*               Заголовочный файл fixpoint64  функций                     */
//*                1999 (c) RC Module Inc., Moscow, Russia                  */
//*                                                                         */
//*                                                                         */
//*  Date:28.12.99                                                          */
//***************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

//=============================================================================
	
	/**
	\defgroup nmppcSqrt nmppcSqrt
	\ingroup cInteger
	\brief
		\ru Вычисление квадратного корня 
		\en Calculation of square root

		\~
	\~
	\param x
		\ru Входное число 
		\en input number
		\~
	\return 
		\ru Квадратный корень 
		\en Squared root 
		\~
	\par
    \xmlonly
        <testperf> 
             <param> x </param> <values> 1 1000 10000000 </values>
			 <size> 1 </size>
        </testperf>
    \endxmlonly
	*/
    //! \{	
	unsigned int nmppcSqrt_64u(unsigned long long x);
//unsigned int nmppcSqrt_32u(unsigned int x);
    //! \}
//=============================================================================

//     Функция деления A/B для целых чисел со знаком 2*abs(A)<abs(B)         
void IDivInv64(
			long*		Dividend,		// делимое 
			long*		Divisor,		// делитель
	const	int			DivIterations,	// кол-во итераций при пошаговом(побитовом) делении
			long*		Quotient		// частное
				);
long Fix64Exp01(long arg);




#ifdef __cplusplus
		};
#endif
