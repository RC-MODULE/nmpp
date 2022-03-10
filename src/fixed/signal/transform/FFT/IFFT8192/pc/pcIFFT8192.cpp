//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM6405 Software                      */
//*                                                                         */
//*   Fast Fourie Transform Library                                         */
//*                                                                         */
//*   File:             pcIFFT8192.cpp                                      */
//*   Contents:         C++ Equivalent of the function FFT_Inv8192.         */
//*                     Additional IFFT8192 functions using                 */
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
#include "nmtl/tcmplx_spec.h"

const unsigned int N = 8192;
const double Pi = 3.14159265359;

class Cplx_float
{
public:
	double Re;
	double Im;
} IW1_8192_float[N * 16], IW2_8192_float[N * 16], IW3_8192_float[N * 16]; //Плавающие коэффициенты

class Wi_fixed
{
public:
	char Re;
	char Im;
} IW1_8192_fixed[N * 16], IW2_8192_fixed[N * 16], IW3_8192_fixed[N * 16]; //Фиксированные коэффициенты

Cplx_float IW8192(unsigned int power) //power = n * k
{
	Cplx_float IW;
	IW.Re = cos(2 * Pi * power / N);
	IW.Im = sin(2 * Pi * power / N);
	return IW;
}

void FFT_Inv8192_float1(Cplx_float *X, Cplx_float *Y) //Плавающая точка (коэффициенты вычисляются в цикле (не заранее))
{
	Cplx_float S[N], T[N], P[N], Summ;

	//Вычисление S (radix-2)

	for (int n = 0; n < N / 2; n++)
		{
			//S[n]=X[n]+X[n+N/2] (для чётных k) (k=0)
			S[n].Re = X[n].Re + X[n + N / 2].Re;
			S[n].Im = X[n].Im + X[n + N / 2].Im;
			//S[n+N/2]=X[n]-X[n+N/2] (для нечётных k) (k=1)
			S[n + N / 2].Re = X[n].Re - X[n + N / 2].Re;
			S[n + N / 2].Im = X[n].Im - X[n + N / 2].Im;
		}

	//Вычисление T

	for (int k2 = 0; k2 < 16; k2++)
		for (int k1 = 0; k1 < 2; k1++)
			for (int j = 0; j < 16; j++)
				for (int i = 0; i < 16; i++)
					{
						Summ.Re = 0;
						Summ.Im = 0;
						for (int m = 0; m < 16; m++)
							{
								//Summ+=W(256(k2*2+k1)m)*S(4096k1+256m+16j+i) (Комплексное умножение)
								Summ.Re += IW8192(256 * (k2 * 2 + k1) * m).Re * S[4096 * k1 + 256 * m + 16 * j + i].Re - IW8192(256 * (k2 * 2 + k1) * m).Im * S[4096 * k1 + 256 * m + 16 * j + i].Im;
								Summ.Im += IW8192(256 * (k2 * 2 + k1) * m).Im * S[4096 * k1 + 256 * m + 16 * j + i].Re + IW8192(256 * (k2 * 2 + k1) * m).Re * S[4096 * k1 + 256 * m + 16 * j + i].Im;
							}
						T[k1 * 4096 + k2 * 256 + j * 16 + i].Re = Summ.Re;
						T[k1 * 4096 + k2 * 256 + j * 16 + i].Im = Summ.Im;
					}

	//Вычисление P
	
	for (int k3 = 0; k3 < 16; k3++)
		for (int k2 = 0; k2 < 16; k2++)
			for (int k1 = 0; k1 < 2; k1++)
				for (int i = 0; i < 16; i++)
					{
						Summ.Re = 0;
						Summ.Im = 0;
						for (int j = 0; j < 16; j++)
							{
								//Summ+=W(16(k3*32+k2*2+k1)*j)*T(k1*4096+k2*256+j*16+i)
								Summ.Re += IW8192(16 * (k3 * 32 + k2 * 2 + k1) * j).Re * T[k1 * 4096 + k2 * 256 + j * 16 + i].Re - IW8192(16 * (k3 * 32 + k2 * 2 + k1) * j).Im * T[k1 * 4096 + k2 * 256 + j * 16 + i].Im;
								Summ.Im += IW8192(16 * (k3 * 32 + k2 * 2 + k1) * j).Im * T[k1 * 4096 + k2 * 256 + j * 16 + i].Re + IW8192(16 * (k3 * 32 + k2 * 2 + k1) * j).Re * T[k1 * 4096 + k2 * 256 + j * 16 + i].Im;
							}
						P[k1 * 4096 + k3 * 256 + k2 * 16 + i].Re = Summ.Re;
						P[k1 * 4096 + k3 * 256 + k2 * 16 + i].Im = Summ.Im;
					}

	//Вычисление Y

	for (int k4 = 0; k4 < 16; k4++)
		for (int k3 = 0; k3 < 16; k3++)
			for (int k2 = 0; k2 < 16; k2++)
				for (int k1 = 0; k1 < 2; k1++)
					{
						Summ.Re = 0;
						Summ.Im = 0;
						for (int i = 0; i < 16; i++)
							{
								//Summ+=W((k4*512+k3*32+k2*2+k1)*i)*P(k1*4096+k3*256+k2*16+i)
								Summ.Re += IW8192((k4 * 512 + k3 * 32 + k2 * 2 + k1) * i).Re * P[k1 * 4096 + k3 * 256 + k2 * 16 + i].Re - IW8192((k4 * 512 + k3 * 32 + k2 * 2 + k1) * i).Im * P[k1 * 4096 + k3 * 256 + k2 * 16 + i].Im;
								Summ.Im += IW8192((k4 * 512 + k3 * 32 + k2 * 2 + k1) * i).Im * P[k1 * 4096 + k3 * 256 + k2 * 16 + i].Re + IW8192((k4 * 512 + k3 * 32 + k2 * 2 + k1) * i).Re * P[k1 * 4096 + k3 * 256 + k2 * 16 + i].Im;
							}
						Y[k4 * 512 + k3 * 32 + k2 * 2 + k1].Re = Summ.Re;
						Y[k4 * 512 + k3 * 32 + k2 * 2 + k1].Im = Summ.Im;
					}
	
	//Деление на N (8192=2^13)

	for (int i = 0; i < N; i++)
		{
			Y[i].Re /= N;
			Y[i].Im /= N;
		}
}

void IMakeTable8192W1W2W3_float(void) //Вычисление коэффициентов (плавающих)
{
	int idx = 0;
	for (int k2 = 0; k2 < 16; k2++)
		for (int k1 = 0; k1 < 2; k1++)
			for (int j = 0; j < 16; j++)
				for (int i = 0; i < 16; i++)
					for (int m = 0; m < 16; m++)
						IW1_8192_float[idx++] = IW8192(256 * (k2 * 2 + k1) * m); //Для T

	idx = 0;
	for (int k3 = 0; k3 < 16; k3++)
		for (int k2 = 0; k2 < 16; k2++)
			for (int k1 = 0; k1 < 2; k1++)
				for (int i = 0; i < 16; i++)
					for (int j = 0; j < 16; j++)
						IW2_8192_float[idx++] = IW8192(16 * (k3 * 32 + k2 * 2 + k1) * j); //Для P

	idx = 0;
	for (int k4 = 0; k4 < 16; k4++)
		for (int k3 = 0; k3 < 16; k3++)
			for (int k2 = 0; k2 < 16; k2++)
				for (int k1 = 0; k1 < 2; k1++)
					for (int i = 0; i < 16; i++)
						IW3_8192_float[idx++] = IW8192((k4 * 512 + k3 * 32 + k2 * 2 + k1) * i); //Для Y
}

void FFT_Inv8192_float2(Cplx_float *X, Cplx_float *Y) //Плавающая точка (коэффициенты вычисляются заранее)
{
	Cplx_float S[N], T[N], P[N], Summ;

//Вычисление коэффициентов

	IMakeTable8192W1W2W3_float();

//Вычисление S (radix-2)

	for (int n = 0; n < N / 2; n++)
		{
			//S[n]=X[n]+X[n+N/2] (для чётных k) (k=0)
			S[n].Re = X[n].Re + X[n + N / 2].Re;
			S[n].Im = X[n].Im + X[n + N / 2].Im;
			//S[n+N/2]=X[n]-X[n+N/2] (для нечётных k) (k=1)
			S[n + N / 2].Re = X[n].Re - X[n + N / 2].Re;
			S[n + N / 2].Im = X[n].Im - X[n + N / 2].Im;
		}

//Вычисление T

	int idx = 0;
	for (int k2 = 0; k2 < 16; k2++)
		for (int k1 = 0; k1 < 2; k1++)
			for (int j = 0; j < 16; j++)
				for (int i = 0; i < 16; i++)
					{
						Summ.Re = 0;
						Summ.Im = 0;
						for (int m = 0; m < 16; m++)
							{
								//Summ+=W(256(k2*2+k1)m)*S(4096k1+256m+16j+i) (Комплексное умножение)
								Summ.Re += IW1_8192_float[idx].Re * S[4096 * k1 + 256 * m + 16 * j + i].Re - IW1_8192_float[idx].Im * S[4096 * k1 + 256 * m + 16 * j + i].Im;
								Summ.Im += IW1_8192_float[idx].Im * S[4096 * k1 + 256 * m + 16 * j + i].Re + IW1_8192_float[idx].Re * S[4096 * k1 + 256 * m + 16 * j + i].Im;
								idx++;
							}
						T[k1 * 4096 + k2 * 256 + j * 16 + i].Re = Summ.Re;
						T[k1 * 4096 + k2 * 256 + j * 16 + i].Im = Summ.Im;
					}

//Вычисление P
	
	idx = 0;
	for (int k3 = 0; k3 < 16; k3++)
		for (int k2 = 0; k2 < 16; k2++)
			for (int k1 = 0; k1 < 2; k1++)
				for (int i = 0; i < 16; i++)
					{
						Summ.Re = 0;
						Summ.Im = 0;
						for (int j = 0; j < 16; j++)
							{
								//Summ+=W(16(k3*32+k2*2+k1)*j)*T(k1*4096+k2*256+j*16+i)
								Summ.Re += IW2_8192_float[idx].Re * T[k1 * 4096 + k2 * 256 + j * 16 + i].Re - IW2_8192_float[idx].Im * T[k1 * 4096 + k2 * 256 + j * 16 + i].Im;
								Summ.Im += IW2_8192_float[idx].Im * T[k1 * 4096 + k2 * 256 + j * 16 + i].Re + IW2_8192_float[idx].Re * T[k1 * 4096 + k2 * 256 + j * 16 + i].Im;
								idx++;
							}
						P[k1 * 4096 + k3 * 256 + k2 * 16 + i].Re = Summ.Re;
						P[k1 * 4096 + k3 * 256 + k2 * 16 + i].Im = Summ.Im;
					}

//Вычисление Y

	idx = 0;
	for (int k4 = 0; k4 < 16; k4++)
		for (int k3 = 0; k3 < 16; k3++)
			for (int k2 = 0; k2 < 16; k2++)
				for (int k1 = 0; k1 < 2; k1++)
					{
						Summ.Re = 0;
						Summ.Im = 0;
						for (int i = 0; i < 16; i++)
							{
								//Summ+=W((k4*512+k3*32+k2*2+k1)*i)*P(k1*4096+k3*256+k2*16+i)
								Summ.Re += IW3_8192_float[idx].Re * P[k1 * 4096 + k3 * 256 + k2 * 16 + i].Re - IW3_8192_float[idx].Im * P[k1 * 4096 + k3 * 256 + k2 * 16 + i].Im;
								Summ.Im += IW3_8192_float[idx].Im * P[k1 * 4096 + k3 * 256 + k2 * 16 + i].Re + IW3_8192_float[idx].Re * P[k1 * 4096 + k3 * 256 + k2 * 16 + i].Im;
								idx++;
							}
						Y[k4 * 512 + k3 * 32 + k2 * 2 + k1].Re = Summ.Re;
						Y[k4 * 512 + k3 * 32 + k2 * 2 + k1].Im = Summ.Im;
					}

	//Деление на N (8192=2^13)

	for (int i = 0; i < N; i++)
		{
			Y[i].Re /= N;
			Y[i].Im /= N;
		}
}

void IMakeTable8192W1W2W3_fixed(void) //Вычисление коэффициентов (фиксированных) (Фактически просто копирование плавающих в фиксированные с учётом точности)
{
	for (int idx = 0; idx < N * 16; idx++)
		{
			IW1_8192_fixed[idx].Re = (char) floor(127 * IW1_8192_float[idx].Re + 0.5);
			IW1_8192_fixed[idx].Im = (char) floor(127 * IW1_8192_float[idx].Im + 0.5);
			IW2_8192_fixed[idx].Re = (char) floor(127 * IW2_8192_float[idx].Re + 0.5);
			IW2_8192_fixed[idx].Im = (char) floor(127 * IW2_8192_float[idx].Im + 0.5);
			IW3_8192_fixed[idx].Re = (char) floor(127 * IW3_8192_float[idx].Re + 0.5);
			IW3_8192_fixed[idx].Im = (char) floor(127 * IW3_8192_float[idx].Im + 0.5);
		}
}

extern "C" {
void FFT_Inv8192(nm32sc* SrcBuffer, nm32sc* DstBuffer, void* Buffer1, void* Buffer2) //Аналог ассемблерной функции
{
	class Cplx_fixed
		{
			public:
				int Re;
				int Im;
		} S_fixed[N], T_fixed[N], P_fixed[N], Summ_fixed;

	unsigned int Half = 1 << 6; //Используется для нормализации

//Вычисление коэффициентов

	IMakeTable8192W1W2W3_float();
	IMakeTable8192W1W2W3_fixed();

//Вычисление S (radix-2)

	for (int n = 0; n < N / 2; n++)
		{
			//S[n]=X[n]+X[n+N/2] (для чётных k) (k=0)
			S_fixed[n].Re = SrcBuffer[n].re + SrcBuffer[n + N / 2].re;
			S_fixed[n].Im = SrcBuffer[n].im + SrcBuffer[n + N / 2].im;
			//S[n+N/2]=X[n]-X[n+N/2] (для нечётных k) (k=1)
			S_fixed[n + N / 2].Re = SrcBuffer[n].re - SrcBuffer[n + N / 2].re;
			S_fixed[n + N / 2].Im = SrcBuffer[n].im - SrcBuffer[n + N / 2].im;
		}

//Вычисление T

	int idx = 0;
	for (int k2 = 0; k2 < 16; k2++)
		for (int k1 = 0; k1 < 2; k1++)
			for (int j = 0; j < 16; j++)
				for (int i = 0; i < 16; i++)
					{
						Summ_fixed.Re = 0;
						Summ_fixed.Im = 0;
						for (int m = 0; m < 16; m++)
							{
								//Summ+=W(256(k2*2+k1)m)*S(4096k1+256m+16j+i) (Комплексное умножение)
								Summ_fixed.Re += IW1_8192_fixed[idx].Re * S_fixed[4096 * k1 + 256 * m + 16 * j + i].Re - IW1_8192_fixed[idx].Im * S_fixed[4096 * k1 + 256 * m + 16 * j + i].Im;
								Summ_fixed.Im += IW1_8192_fixed[idx].Im * S_fixed[4096 * k1 + 256 * m + 16 * j + i].Re + IW1_8192_fixed[idx].Re * S_fixed[4096 * k1 + 256 * m + 16 * j + i].Im;
								idx++;
							}
						T_fixed[k1 * 4096 + k2 * 256 + j * 16 + i].Re = Summ_fixed.Re;
						T_fixed[k1 * 4096 + k2 * 256 + j * 16 + i].Im = Summ_fixed.Im;
					}

//Нормализация T

	for (int i = 0; i < N; i++)
		{
			T_fixed[i].Re += Half;
			T_fixed[i].Re >>= 7;
			T_fixed[i].Im += Half;
			T_fixed[i].Im >>= 7;
		}

//Вычисление P
	
	idx = 0;
	for (int k3 = 0; k3 < 16; k3++)
		for (int k2 = 0; k2 < 16; k2++)
			for (int k1 = 0; k1 < 2; k1++)
				for (int i = 0; i < 16; i++)
					{
						Summ_fixed.Re = 0;
						Summ_fixed.Im = 0;
						for (int j = 0; j < 16; j++)
							{
								//Summ+=W(16(k3*32+k2*2+k1)*j)*T(k1*4096+k2*256+j*16+i)
								Summ_fixed.Re += IW2_8192_fixed[idx].Re * T_fixed[k1 * 4096 + k2 * 256 + j * 16 + i].Re - IW2_8192_fixed[idx].Im * T_fixed[k1 * 4096 + k2 * 256 + j * 16 + i].Im;
								Summ_fixed.Im += IW2_8192_fixed[idx].Im * T_fixed[k1 * 4096 + k2 * 256 + j * 16 + i].Re + IW2_8192_fixed[idx].Re * T_fixed[k1 * 4096 + k2 * 256 + j * 16 + i].Im;
								idx++;
							}
						P_fixed[k1 * 4096 + k3 * 256 + k2 * 16 + i].Re = Summ_fixed.Re;
						P_fixed[k1 * 4096 + k3 * 256 + k2 * 16 + i].Im = Summ_fixed.Im;
					}

//Нормализация P

	for (int i = 0; i < N; i++)
		{
			P_fixed[i].Re += Half;
			P_fixed[i].Re >>= 7;
			P_fixed[i].Im += Half;
			P_fixed[i].Im >>= 7;
		}

//Вычисление Y

	idx = 0;
	for (int k4 = 0; k4 < 16; k4++)
		for (int k3 = 0; k3 < 16; k3++)
			for (int k2 = 0; k2 < 16; k2++)
				for (int k1 = 0; k1 < 2; k1++)
					{
						Summ_fixed.Re = 0;
						Summ_fixed.Im = 0;
						for (int i = 0; i < 16; i++)
							{
								//Summ+=W((k4*512+k3*32+k2*2+k1)*i)*P(k1*4096+k3*256+k2*16+i)
								Summ_fixed.Re += IW3_8192_fixed[idx].Re * P_fixed[k1 * 4096 + k3 * 256 + k2 * 16 + i].Re - IW3_8192_fixed[idx].Im * P_fixed[k1 * 4096 + k3 * 256 + k2 * 16 + i].Im;
								Summ_fixed.Im += IW3_8192_fixed[idx].Im * P_fixed[k1 * 4096 + k3 * 256 + k2 * 16 + i].Re + IW3_8192_fixed[idx].Re * P_fixed[k1 * 4096 + k3 * 256 + k2 * 16 + i].Im;
								idx++;
							}
						DstBuffer[k4 * 512 + k3 * 32 + k2 * 2 + k1].re = Summ_fixed.Re;
						DstBuffer[k4 * 512 + k3 * 32 + k2 * 2 + k1].im = Summ_fixed.Im;
					}

//Нормализация Y

	Half = 1 << 19;
	for (int i = 0; i < N; i++)
		{
			DstBuffer[i].re += Half;
			DstBuffer[i].re >>= 20;
			DstBuffer[i].im += Half;
			DstBuffer[i].im >>= 20;
		}
}
};
