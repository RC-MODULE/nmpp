/*
// алогритм БПФ с прореживанием по времени и частоте
void nmppsFFT16Fwd242High_RefFloat(const nm32sc* src, nm32sc* dst)
{
	vec<cmplx<double> > X(16);
	vec<cmplx<double> > Y(16);

	vec<cmplx<double> > A(8);
	vec<cmplx<double> > B(8);
	vec<cmplx<double> > C(8);
	vec<cmplx<double> > D(8);


	for (int i = 0; i < 16; i++) {
		X[i].re = src[i].re;
		X[i].im = src[i].im;
	}

	Y.reset();
	A.reset();
	B.reset();



	for (int j = 0; j < 8; j++) {
		C[j] = X[j] + X[j+ 8];
		D[j ]    = X[j] - X[j+ 8];
	}
		

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++) {
			A[2 * i] += C[2*j]	* expFFT<8>(2 * i*j);
			B[2 * i] += C[2*j+1]* expFFT<8>(2 * i*j + i);
		}

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++) {
			A[2 * i + 1] += D[2*j]		* expFFT<8>(2 * i*j + j);
			B[2 * i + 1] += D[2 * j+1]	* expFFT<8>(2 * i*j + j + i)*expFFT<16>(1);
		}

	for (int i = 0; i < 8; i++) {
		Y[i] = A[i] + B[i];
		Y[i + 8] = A[i] - B[i];
	}

	for (int i = 0; i<16; i++) {
		dst[i].re = floor(Y[i].re + 0.5);
		dst[i].im = floor(Y[i].im + 0.5);
	}
}
*/