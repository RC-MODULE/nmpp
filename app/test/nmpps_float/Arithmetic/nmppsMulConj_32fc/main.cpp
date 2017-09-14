#include <nmtype.h>
#include <malloc32.h>
#include <nmpp.h>

#define PI 3.1415

int main()
{
	int N = 512;
	int i;
	nm32fcr* vec0 = (nm32fcr *) nmppsMalloc_32fc((N + 2) * sizeof(nm32fcr));
	nm32fcr* vec1 = (nm32fcr *) nmppsMalloc_32fc((N + 2) * sizeof(nm32fcr));
	nm32fcr* dst  = (nm32fcr *) nmppsMalloc_32fc((N + 2) * sizeof(nm32fcr));
	unsigned crc = 0;
	for(int i = 0; i < N + 2; i++) {
		vec0[i].re = i * PI;
		vec1[i].re = i + PI;
		vec0[i].im = i + PI/2;
		vec1[i].im = i - 2 * PI;
		dst[i].re = 0;
		dst[i].im = 0;
	}
	for(i = 0; i < N; i++) {
		nmppsMulConj_32fc(N - i, vec0, vec1, dst);
		nmppsCrcAcc_32f((float *)dst, 11, 2 * (N - i + 2), &crc);
	}
	free(vec0);
	free(vec1);
	free(dst);
	return crc>>2;
}