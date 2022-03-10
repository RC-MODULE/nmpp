//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM6405 Software                      */
//*                                                                         */
//*   Fast Fourie Transform Library                                         */
//*                                                                         */
//*   File:             pcFFT4096.cpp                                       */
//*   Contents:         C++ Equivalent of the function FFT_Fwd4096.         */
//*                     Additional FFT4096 functions using                  */
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


Cplx_float W1_4096_float[N * 16], W2_4096_float[N * 16], W3_4096_float[N * 16]; //��������� ������������

Wi_4096_fixed  W1_4096_fixed[N * 16], W2_4096_fixed[N * 16], W3_4096_fixed[N * 16]; //������������� ������������


Cplx_float W4096(unsigned int power) //power = n * k
{
	Cplx_float W;
	W.Re = cos(2 * Pi * power / N);
	W.Im = -sin(2 * Pi * power / N);
	return W;
}

void FFT_Fwd4096_float1(Cplx_float *X, Cplx_float *Y) //��������� ����� (������������ ����������� � ����� (�� �������))
{
	Cplx_float S[N], T[N], Summ;

//���������� S

	for (int k = 0; k < 16; k++)
		for (int j = 0; j < 16; j++)
			for (int i = 0; i < 16; i++)
				{
					Summ.Re = 0;
					Summ.Im = 0;
					for (int n = 0; n < 16; n++)
						{
							//Summ += W(256kn) * X(256n + 16j + i) (����������� ���������)
							Summ.Re += X[256 * n + 16 * j + i].Re * W4096(256 * k * n).Re - X[256 * n + 16 * j + i].Im * W4096(256 * k * n).Im;
							Summ.Im += X[256 * n + 16 * j + i].Im * W4096(256 * k * n).Re + X[256 * n + 16 * j + i].Re * W4096(256 * k * n).Im;
						}
					S[k * 256 + j * 16 + i].Re = Summ.Re;
					S[k * 256 + j * 16 + i].Im = Summ.Im;
				}

//���������� T

	for (int k2 = 0; k2 < 16; k2++)
		for (int k1 = 0; k1 < 16; k1++)
			for (int i = 0; i < 16; i++)
				{
					Summ.Re = 0;
					Summ.Im = 0;
					for (int j = 0; j < 16; j++)
						{
							//Summ += W(16 * ((k2 * 16) + k1) * j) * S(256 * k1 + 16j + i)
							Summ.Re += S[256 * k1 + 16 * j + i].Re * W4096(16 * ((k2 * 16) + k1) * j).Re - S[256 * k1 + 16 * j + i].Im * W4096(16 * ((k2 * 16) + k1) * j).Im;
							Summ.Im += S[256 * k1 + 16 * j + i].Im * W4096(16 * ((k2 * 16) + k1) * j).Re + S[256 * k1 + 16 * j + i].Re * W4096(16 * ((k2 * 16) + k1) * j).Im;
						}
					T[((k2 * 16) + k1) * 16 + i].Re = Summ.Re; //��� ����� ������ ������������
					T[k2 * 256 + k1 * 16 + i].Im = Summ.Im; //��� ����� ������ ������������
				}

//���������� Y

	for (int k3 = 0; k3 < 16; k3++)
		for (int k2 = 0; k2 < 16; k2++)
			for (int k1 = 0; k1 < 16; k1++)
				{
					Summ.Re = 0;
					Summ.Im = 0;
					for (int i = 0; i < 16; i++)
						{
							//Summ += W((k3 * 256 + k2 * 16 + k1) * i) * T((k2 * 16 + k1) * 16 + i)
							Summ.Re += T[(k2 * 16 + k1) * 16 + i].Re * W4096((k3 * 256 + k2 * 16 + k1) * i).Re - T[(k2 * 16 + k1) * 16 + i].Im * W4096((k3 * 256 + k2 * 16 + k1) * i).Im;
							Summ.Im += T[(k2 * 16 + k1) * 16 + i].Im * W4096((k3 * 256 + k2 * 16 + k1) * i).Re + T[(k2 * 16 + k1) * 16 + i].Re * W4096((k3 * 256 + k2 * 16 + k1) * i).Im;
						}
					Y[k3 * 256 + k2 * 16 + k1].Re = Summ.Re;
					Y[k3 * 256 + k2 * 16 + k1].Im = Summ.Im;
				}
}

void MakeTable4096W1W2W3_float(void) //���������� ������������� (���������)
{
	int idx = 0;
	for (int k = 0; k < 16; k++)
		for (int j = 0; j < 16; j++)
			for (int i = 0; i < 16; i++)
				for (int n = 0; n < 16; n++)
					W1_4096_float[idx++] = W4096(256 * k * n); //��� S

	idx = 0;
	for (int k2 = 0; k2 < 16; k2++)
		for (int k1 = 0; k1 < 16; k1++)
			for (int i = 0; i < 16; i++)
				for (int j = 0; j < 16; j++)
					W2_4096_float[idx++] = W4096(16 * ((k2 * 16) + k1) * j); //��� T

	idx = 0;
	for (int k3 = 0; k3 < 16; k3++)
		for (int k2 = 0; k2 < 16; k2++)
			for (int k1 = 0; k1 < 16; k1++)
				for (int i = 0; i < 16; i++)
					W3_4096_float[idx++] = W4096((k3 * 256 + k2 * 16 + k1) * i); //��� Y
}

void FFT_Fwd4096_float2(Cplx_float *X, Cplx_float *Y) //��������� ����� (������������ ����������� �������)
{
	Cplx_float S[N], T[N], Summ;

//���������� �������������

	MakeTable4096W1W2W3_float();

//���������� S

	int idx = 0;
	for (int k = 0; k < 16; k++)
		for (int j = 0; j < 16; j++)
			for (int i = 0; i < 16; i++)
				{
					Summ.Re = 0;
					Summ.Im = 0;
					for (int n = 0; n < 16; n++)
						{
							//Summ += W(256kn) * X(256n + 16j + i) (����������� ���������)
							Summ.Re += X[256 * n + 16 * j + i].Re * W1_4096_float[idx].Re - X[256 * n + 16 * j + i].Im * W1_4096_float[idx].Im;
							Summ.Im += X[256 * n + 16 * j + i].Im * W1_4096_float[idx].Re + X[256 * n + 16 * j + i].Re * W1_4096_float[idx].Im;
							idx++;
						}
					S[k * 256 + j * 16 + i].Re = Summ.Re;
					S[k * 256 + j * 16 + i].Im = Summ.Im;
				}

//���������� T

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
							Summ.Re += S[256 * k1 + 16 * j + i].Re * W2_4096_float[idx].Re - S[256 * k1 + 16 * j + i].Im * W2_4096_float[idx].Im;
							Summ.Im += S[256 * k1 + 16 * j + i].Im * W2_4096_float[idx].Re + S[256 * k1 + 16 * j + i].Re * W2_4096_float[idx].Im;
							idx++;
						}
					T[((k2 * 16) + k1) * 16 + i].Re = Summ.Re; //��� ����� ������ ������������
					T[k2 * 256 + k1 * 16 + i].Im = Summ.Im; //��� ����� ������ ������������
				}

//���������� Y

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
							Summ.Re += T[(k2 * 16 + k1) * 16 + i].Re * W3_4096_float[idx].Re - T[(k2 * 16 + k1) * 16 + i].Im * W3_4096_float[idx].Im;
							Summ.Im += T[(k2 * 16 + k1) * 16 + i].Im * W3_4096_float[idx].Re + T[(k2 * 16 + k1) * 16 + i].Re * W3_4096_float[idx].Im;
							idx++;
						}
					Y[k3 * 256 + k2 * 16 + k1].Re = Summ.Re;
					Y[k3 * 256 + k2 * 16 + k1].Im = Summ.Im;
				}
}

void MakeTable4096W1W2W3_fixed(void) //���������� ������������� (�������������) (���������� ������ ����������� ��������� � ������������� � ������ ��������)
{
	for (int idx = 0; idx < N * 16; idx++)
		{
			W1_4096_fixed[idx].Re = (char) floor(127 * W1_4096_float[idx].Re + 0.5);
			W1_4096_fixed[idx].Im = (char) floor(127 * W1_4096_float[idx].Im + 0.5);
			W2_4096_fixed[idx].Re = (char) floor(127 * W2_4096_float[idx].Re + 0.5);
			W2_4096_fixed[idx].Im = (char) floor(127 * W2_4096_float[idx].Im + 0.5);
			W3_4096_fixed[idx].Re = (char) floor(127 * W3_4096_float[idx].Re + 0.5);
			W3_4096_fixed[idx].Im = (char) floor(127 * W3_4096_float[idx].Im + 0.5);
		}
}
extern "C" {
void FFT_Fwd4096(nm32sc* GSrcBuffer, nm32sc* GDstBuffer, void* LBuffer, void* GBuffer) //������ ������������ �������
{
	class Cplx_fixed
		{
			public:
				int Re;
				int Im;
		} S_fixed[N], T_fixed[N], Summ_fixed;

	const unsigned int Half = 1 << 6; //������������ ��� ������������

//���������� �������������

	MakeTable4096W1W2W3_float();
	MakeTable4096W1W2W3_fixed();

//���������� S

	int idx = 0;
	for (int k = 0; k < 16; k++)
		for (int j = 0; j < 16; j++)
			for (int i = 0; i < 16; i++)
				{
					Summ_fixed.Re = 0;
					Summ_fixed.Im = 0;
					for (int n = 0; n < 16; n++)
						{
							//Summ += W(256kn) * X(256n + 16j + i) (����������� ���������)
							Summ_fixed.Re += GSrcBuffer[256 * n + 16 * j + i].re * W1_4096_fixed[idx].Re - GSrcBuffer[256 * n + 16 * j + i].im * W1_4096_fixed[idx].Im;
							Summ_fixed.Im += GSrcBuffer[256 * n + 16 * j + i].im * W1_4096_fixed[idx].Re + GSrcBuffer[256 * n + 16 * j + i].re * W1_4096_fixed[idx].Im;
							idx++;
						}
					S_fixed[k * 256 + j * 16 + i].Re = Summ_fixed.Re;
					S_fixed[k * 256 + j * 16 + i].Im = Summ_fixed.Im;
				}

//������������ S

	for (int i = 0; i < N; i++)
		{
			S_fixed[i].Re += Half;
			S_fixed[i].Re >>= 7;
			S_fixed[i].Im += Half;
			S_fixed[i].Im >>= 7;
		}

//���������� T

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
							Summ_fixed.Re += S_fixed[256 * k1 + 16 * j + i].Re * W2_4096_fixed[idx].Re - S_fixed[256 * k1 + 16 * j + i].Im * W2_4096_fixed[idx].Im;
							Summ_fixed.Im += S_fixed[256 * k1 + 16 * j + i].Im * W2_4096_fixed[idx].Re + S_fixed[256 * k1 + 16 * j + i].Re * W2_4096_fixed[idx].Im;
							idx++;
						}
					T_fixed[((k2 * 16) + k1) * 16 + i].Re = Summ_fixed.Re; //��� ����� ������ ������������
					T_fixed[k2 * 256 + k1 * 16 + i].Im = Summ_fixed.Im; //��� ����� ������ ������������
				}

//������������ T

	for (int i = 0; i < N; i++)
		{
			T_fixed[i].Re += Half;
			T_fixed[i].Re >>= 7;
			T_fixed[i].Im += Half;
			T_fixed[i].Im >>= 7;
		}

//���������� Y

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
							Summ_fixed.Re += T_fixed[(k2 * 16 + k1) * 16 + i].Re * W3_4096_fixed[idx].Re - T_fixed[(k2 * 16 + k1) * 16 + i].Im * W3_4096_fixed[idx].Im;
							Summ_fixed.Im += T_fixed[(k2 * 16 + k1) * 16 + i].Im * W3_4096_fixed[idx].Re + T_fixed[(k2 * 16 + k1) * 16 + i].Re * W3_4096_fixed[idx].Im;
							idx++;
						}
					GDstBuffer[k3 * 256 + k2 * 16 + k1].re = Summ_fixed.Re;
					GDstBuffer[k3 * 256 + k2 * 16 + k1].im = Summ_fixed.Im;
				}

//������������ Y

	for (int i = 0; i < N; i++)
		{
			GDstBuffer[i].re += Half;
			GDstBuffer[i].re >>= 7;
			GDstBuffer[i].im += Half;
			GDstBuffer[i].im >>= 7;
		}
}
};
