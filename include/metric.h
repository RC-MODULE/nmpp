#include "nmtype.h"

#ifdef __cplusplus
		extern "C" {
#endif

float nmppsMSD_32sc(const nm32sc* x0, const nm32sc* x1, int size);
float nmppsRMSD_32fc(const nm32fc *src1, const nm32fc *src2, int num);

void nmppsNormDiff_L1_32s (const nm32s* pSrc1, const nm32s* pSrc2, int len, float* pNorm);
void nmppsNormDiff_L2_32s (const nm32s* pSrc1, const nm32s* pSrc2, int len, float* pNorm);
void nmppsNormDiff_L2_32f(const float* pSrc1, const float* pSrc2, int len, float* pNorm);
void nmppsNormDiff_L2_32fc(const nm32fcr *src1, const nm32fcr *src2, int num, float* pNorm);
void nmppsNormDiff_Inf_32s(const nm32s* pSrc1, const nm32s* pSrc2, int len, float* pNorm);
void nmppsNormDiff_Inf_32f(const float* pSrc1, const float* pSrc2, int len, float* pNorm);


#ifdef __cplusplus
		};
#endif
