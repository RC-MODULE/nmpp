//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM6405 Software                      */
//*                                                                         */
//*   Fast Fourie Transform Library                                         */
//*                                                                         */
//*   File:             pcIFFT4096.cpp                                      */
//*   Contents:         C++ Equivalent of the function FFT_Inv4096.         */
//*                     Additional IFFT4096 functions using                 */
//*                         fixed and floating-point arithmetic             */ 
//*                                                                         */
//*                                                                         */
//*   Software design:  D. Spesivtsev                                       */
//*                                                                         */
//*   Start date:       08.04.2009                                          */
//*   Last update :     -                                                   */
//*                                                                         */
//*                                                                         */
//***************************************************************************/

#include <math.h>
#include "fft.h"
#include "fftext.h"
#include "nmtl/tcmplx_spec.h"

const unsigned int N = 4096;
const double Pi = 3.14159265359;

Cplx_float IW1_4096_float[N * 16], IW2_4096_float[N * 16], IW3_4096_float[N * 16]; //Плавающие коэффициенты

Wi_4096_fixed IW1_4096_fixed[N * 16], IW2_4096_fixed[N * 16], IW3_4096_fixed[N * 16]; //Фиксированные коэффициенты

Cplx_float IW4096(unsigned int power) //power = n * k
{
	Cplx_float IW;
	IW.Re = cos(2 * Pi * power / N);
	IW.Im = sin(2 * Pi * power / N); //Отличается от прямого отсутствием знака минус
	return IW;
}

void FFT_Inv4096_float1(Cplx_float *X, Cplx_float *Y) //Плавающая точка (коэффициенты вычисляются в цикле (не заранее))
{
	Cplx_float S[N], T[N], Summ;

//Вычисление S

	for (int k = 0; k < 16; k++)
		for (int j = 0; j < 16; j++)
			for (int i = 0; i < 16; i++)
				{
					Summ.Re = 0;
					Summ.Im = 0;
					for (int n = 0; n < 16; n++)
						{
							//Summ += W(256kn) * X(256n + 16j + i) (Комплексное умножение)
							Summ.Re += X[256 * n + 16 * j + i].Re * IW4096(256 * k * n).Re - X[256 * n + 16 * j + i].Im * IW4096(256 * k * n).Im;
							Summ.Im += X[256 * n + 16 * j + i].Im * IW4096(256 * k * n).Re + X[256 * n + 16 * j + i].Re * IW4096(256 * k * n).Im;
						}
					S[k * 256 + j * 16 + i].Re = Summ.Re;
					S[k * 256 + j * 16 + i].Im = Summ.Im;
				}

//Вычисление T

	for (int k2 = 0; k2 < 16; k2++)
		for (int k1 = 0; k1 < 16; k1++)
			for (int i = 0; i < 16; i++)
				{
					Summ.Re = 0;
					Summ.Im = 0;
					for (int j = 0; j < 16; j++)
						{
							//Summ += W(16 * ((k2 * 16) + k1) * j) * S(256 * k1 + 16j + i)
							Summ.Re += S[256 * k1 + 16 * j + i].Re * IW4096(16 * ((k2 * 16) + k1) * j).Re - S[256 * k1 + 16 * j + i].Im * IW4096(16 * ((k2 * 16) + k1) * j).Im;
							Summ.Im += S[256 * k1 + 16 * j + i].Im * IW4096(16 * ((k2 * 16) + k1) * j).Re + S[256 * k1 + 16 * j + i].Re * IW4096(16 * ((k2 * 16) + k1) * j).Im;
						}
					T[((k2 * 16) + k1) * 16 + i].Re = Summ.Re; //Эти формы записи тождественны
					T[k2 * 256 + k1 * 16 + i].Im = Summ.Im; //Эти формы записи тождественны
				}

//Вычисление Y

	for (int k3 = 0; k3 < 16; k3++)
		for (int k2 = 0; k2 < 16; k2++)
			for (int k1 = 0; k1 < 16; k1++)
				{
					Summ.Re = 0;
					Summ.Im = 0;
					for (int i = 0; i < 16; i++)
						{
							//Summ += W((k3 * 256 + k2 * 16 + k1) * i) * T((k2 * 16 + k1) * 16 + i)
							Summ.Re += T[(k2 * 16 + k1) * 16 + i].Re * IW4096((k3 * 256 + k2 * 16 + k1) * i).Re - T[(k2 * 16 + k1) * 16 + i].Im * IW4096((k3 * 256 + k2 * 16 + k1) * i).Im;
							Summ.Im += T[(k2 * 16 + k1) * 16 + i].Im * IW4096((k3 * 256 + k2 * 16 + k1) * i).Re + T[(k2 * 16 + k1) * 16 + i].Re * IW4096((k3 * 256 + k2 * 16 + k1) * i).Im;
						}
					Y[k3 * 256 + k2 * 16 + k1].Re = Summ.Re;
					Y[k3 * 256 + k2 * 16 + k1].Im = Summ.Im;
				}

//Деление на N (4096=2^12)

	for (int i = 0; i < N; i++)
		{
			Y[i].Re /= N;
			Y[i].Im /= N;
		}
}

void IMakeTable4096W1W2W3_float(void) //Вычисление коэффициентов (плавающих)
{
	int idx = 0;
	for (int k = 0; k < 16; k++)
		for (int j = 0; j < 16; j++)
			for (int i = 0; i < 16; i++)
				for (int n = 0; n < 16; n++)
					IW1_4096_float[idx++] = IW4096(256 * k * n); //Для S

	idx = 0;
	for (int k2 = 0; k2 < 16; k2++)
		for (int k1 = 0; k1 < 16; k1++)
			for (int i = 0; i < 16; i++)
				for (int j = 0; j < 16; j++)
					IW2_4096_float[idx++] = IW4096(16 * ((k2 * 16) + k1) * j); //Для T

	idx = 0;
	for (int k3 = 0; k3 < 16; k3++)
		for (int k2 = 0; k2 < 16; k2++)
			for (int k1 = 0; k1 < 16; k1++)
				for (int i = 0; i < 16; i++)
					IW3_4096_float[idx++] = IW4096((k3 * 256 + k2 * 16 + k1) * i); //Для Y
}

void FFT_Inv4096_float2(Cplx_float *X, Cplx_float *Y) //Плавающая точка (коэффициенты вычисляются заранее)
{
	Cplx_float S[N], T[N], Summ;

//Вычисление коэффициентов

	IMakeTable4096W1W2W3_float();

//Вычисление S

	int idx = 0;
	for (int k = 0; k < 16; k++)
		for (int j = 0; j < 16; j++)
			for (int i = 0; i < 16; i++)
				{
					Summ.Re = 0;
					Summ.Im = 0;
					for (int n = 0; n < 16; n++)
						{
							//Summ += W(256kn) * X(256n + 16j + i) (Комплексное умножение)
							Summ.Re += X[256 * n + 16 * j + i].Re * IW1_4096_float[idx].Re - X[256 * n + 16 * j + i].Im * IW1_4096_float[idx].Im;
							Summ.Im += X[256 * n + 16 * j + i].Im * IW1_4096_float[idx].Re + X[256 * n + 16 * j + i].Re * IW1_4096_float[idx].Im;
							idx++;
						}
					S[k * 256 + j * 16 + i].Re = Summ.Re;
					S[k * 256 + j * 16 + i].Im = Summ.Im;
				}

//Вычисление T

	idx = 0;
	for (int k2 = 0; k2 < 16; k2++)
		for (int k1 = 0; k1 < 16; k1++)
			for (int i = 0; i < 16; i++)
				{
					Summ.Re = 0;
					Summ.Im = 0;
					for (int j = 0; j < 16; j++)
						{
							//Summ += W(16 * ((k2 * 16) + k1) * j) * S(256 * k1 + 16j + i)
							Summ.Re += S[256 * k1 + 16 * j + i].Re * IW2_4096_float[idx].Re - S[256 * k1 + 16 * j + i].Im * IW2_4096_float[idx].Im;
							Summ.Im += S[256 * k1 + 16 * j + i].Im * IW2_4096_float[idx].Re + S[256 * k1 + 16 * j + i].Re * IW2_4096_float[idx].Im;
							idx++;
						}
					T[((k2 * 16) + k1) * 16 + i].Re = Summ.Re; //Эти формы записи тождественны
					T[k2 * 256 + k1 * 16 + i].Im = Summ.Im; //Эти формы записи тождественны
				}

//Вычисление Y

	idx = 0;
	for (int k3 = 0; k3 < 16; k3++)
		for (int k2 = 0; k2 < 16; k2++)
			for (int k1 = 0; k1 < 16; k1++)
				{
					Summ.Re = 0;
					Summ.Im = 0;
					for (int i = 0; i < 16; i++)
						{
							//Summ += W((k3 * 256 + k2 * 16 + k1) * i) * T((k2 * 16 + k1) * 16 + i)
							Summ.Re += T[(k2 * 16 + k1) * 16 + i].Re * IW3_4096_float[idx].Re - T[(k2 * 16 + k1) * 16 + i].Im * IW3_4096_float[idx].Im;
							Summ.Im += T[(k2 * 16 + k1) * 16 + i].Im * IW3_4096_float[idx].Re + T[(k2 * 16 + k1) * 16 + i].Re * IW3_4096_float[idx].Im;
							idx++;
						}
					Y[k3 * 256 + k2 * 16 + k1].Re = Summ.Re;
					Y[k3 * 256 + k2 * 16 + k1].Im = Summ.Im;
				}

//Деление на N (4096=2^12)

	for (int i = 0; i < N; i++)
		{
			Y[i].Re /= N;
			Y[i].Im /= N;
		}
}

void IMakeTable4096W1W2W3_fixed(void) //Вычисление коэффициентов (фиксированных) (Фактически просто копирование плавающих в фиксированные с учётом точности)
{
	for (int idx = 0; idx < N * 16; idx++)
		{
			IW1_4096_fixed[idx].Re = (char) floor(127 * IW1_4096_float[idx].Re + 0.5);
			IW1_4096_fixed[idx].Im = (char) floor(127 * IW1_4096_float[idx].Im + 0.5);
			IW2_4096_fixed[idx].Re = (char) floor(127 * IW2_4096_float[idx].Re + 0.5);
			IW2_4096_fixed[idx].Im = (char) floor(127 * IW2_4096_float[idx].Im + 0.5);
			IW3_4096_fixed[idx].Re = (char) floor(127 * IW3_4096_float[idx].Re + 0.5);
			IW3_4096_fixed[idx].Im = (char) floor(127 * IW3_4096_float[idx].Im + 0.5);
		}
}

extern "C" {
void FFT_Inv4096(nm32sc* GSrcBuffer, nm32sc* GDstBuffer, void* LBuffer, void* GBuffer) //Аналог ассемблерной функции
{
	class Cplx_fixed
		{
			public:
				int Re;
				int Im;
		} S_fixed[N], T_fixed[N], Summ_fixed;

	unsigned int Half = 1 << 6;

//Вычисление коэффициентов

	IMakeTable4096W1W2W3_float();
	IMakeTable4096W1W2W3_fixed();

//Вычисление S

	int idx = 0;
	for (int k = 0; k < 16; k++)
		for (int j = 0; j < 16; j++)
			for (int i = 0; i < 16; i++)
				{
					Summ_fixed.Re = 0;
					Summ_fixed.Im = 0;
					for (int n = 0; n < 16; n++)
						{
							//Summ += W(256kn) * X(256n + 16j + i) (Комплексное умножение)
							Summ_fixed.Re += GSrcBuffer[256 * n + 16 * j + i].re * IW1_4096_fixed[idx].Re - GSrcBuffer[256 * n + 16 * j + i].im * IW1_4096_fixed[idx].Im;
							Summ_fixed.Im += GSrcBuffer[256 * n + 16 * j + i].im * IW1_4096_fixed[idx].Re + GSrcBuffer[256 * n + 16 * j + i].re * IW1_4096_fixed[idx].Im;
							idx++;
						}
					S_fixed[k * 256 + j * 16 + i].Re = Summ_fixed.Re;
					S_fixed[k * 256 + j * 16 + i].Im = Summ_fixed.Im;
				}

//Нормализация S

	for (int i = 0; i < N; i++)
		{
			S_fixed[i].Re += Half;
			S_fixed[i].Re >>= 7;
			S_fixed[i].Im += Half;
			S_fixed[i].Im >>= 7;
		}

//Вычисление T

	idx = 0;
	for (int k2 = 0; k2 < 16; k2++)
		for (int k1 = 0; k1 < 16; k1++)
			for (int i = 0; i < 16; i++)
				{
					Summ_fixed.Re = 0;
					Summ_fixed.Im = 0;
					for (int j = 0; j < 16; j++)
						{
							//Summ += W(16 * ((k2 * 16) + k1) * j) * S(256 * k1 + 16j + i)
							Summ_fixed.Re += S_fixed[256 * k1 + 16 * j + i].Re * IW2_4096_fixed[idx].Re - S_fixed[256 * k1 + 16 * j + i].Im * IW2_4096_fixed[idx].Im;
							Summ_fixed.Im += S_fixed[256 * k1 + 16 * j + i].Im * IW2_4096_fixed[idx].Re + S_fixed[256 * k1 + 16 * j + i].Re * IW2_4096_fixed[idx].Im;
							idx++;
						}
					T_fixed[((k2 * 16) + k1) * 16 + i].Re = Summ_fixed.Re; //Эти формы записи тождественны
					T_fixed[k2 * 256 + k1 * 16 + i].Im = Summ_fixed.Im; //Эти формы записи тождественны
				}

//Нормализация T

	for (int i = 0; i < N; i++)
		{
			T_fixed[i].Re += Half;
			T_fixed[i].Re >>= 7;
			T_fixed[i].Im += Half;
			T_fixed[i].Im >>= 7;
		}

//Вычисление Y

	idx = 0;
	for (int k3 = 0; k3 < 16; k3++)
		for (int k2 = 0; k2 < 16; k2++)
			for (int k1 = 0; k1 < 16; k1++)
				{
					Summ_fixed.Re = 0;
					Summ_fixed.Im = 0;
					for (int i = 0; i < 16; i++)
						{
							//Summ += W((k3 * 256 + k2 * 16 + k1) * i) * T((k2 * 16 + k1) * 16 + i)
							Summ_fixed.Re += T_fixed[(k2 * 16 + k1) * 16 + i].Re * IW3_4096_fixed[idx].Re - T_fixed[(k2 * 16 + k1) * 16 + i].Im * IW3_4096_fixed[idx].Im;
							Summ_fixed.Im += T_fixed[(k2 * 16 + k1) * 16 + i].Im * IW3_4096_fixed[idx].Re + T_fixed[(k2 * 16 + k1) * 16 + i].Re * IW3_4096_fixed[idx].Im;
							idx++;
						}
					GDstBuffer[k3 * 256 + k2 * 16 + k1].re = Summ_fixed.Re;
					GDstBuffer[k3 * 256 + k2 * 16 + k1].im = Summ_fixed.Im;
				}

//Нормализация Y (с делением на N)

	Half = 1 << 18;
	for (int i = 0; i < N; i++)
		{
			GDstBuffer[i].re += Half;
			GDstBuffer[i].re >>= 19;
			GDstBuffer[i].im += Half;
			GDstBuffer[i].im >>= 19;
		}
}
};
