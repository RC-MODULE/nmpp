#include "nmtype.h"

#ifdef __cplusplus
		extern "C" {
#endif

float nmppsMSD_32sc(nm32sc* x0,nm32sc* x1, int size);

void nmppsNormDiff_L1_32s (const nm32s* pSrc1, const nm32s* pSrc2, int len, float* pNorm);
void nmppsNormDiff_L2_32s (const nm32s* pSrc1, const nm32s* pSrc2, int len, float* pNorm);
void nmppsNormDiff_Inf_32s(const nm32s* pSrc1, const nm32s* pSrc2, int len, float* pNorm);
void nmppsNormDiff_Inf_32f(const float* pSrc1, const float* pSrc2, int len, float* pNorm);

#ifdef __cplusplus
		};
#endif
