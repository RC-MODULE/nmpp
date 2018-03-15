#ifndef _SARITHM_H_INCLUDED_
#define _SARITHM_H_INCLUDED_

#ifdef __cplusplus
		extern "C" {
#endif

void nmppsDiv_32f(const nm32f *pSrcVec1, const nm32f *pSrcVec2, nm32f *pDstVec, int nSize);
void nmppsExp_32f(const nm32f *pSrcVec, nm32f *pDstVec, int nSize);
void nmppsExp_64f(const nm64f *pSrcVec, nm64f *pDstVec, int nSize);
void nmppsLog_32f (const nm32f *pSrcVec, nm32f *pDstVec, int nSize);
void nmppsLog_64f(const nm64f *pSrcVec, nm64f *pDstVec, int nSize);
void nmppsPowx_64f(const nm64f *pSrcVec, nm64f *pDstVec, nm32u Deg, int nSize);

#ifdef __cplusplus
		};
#endif

#endif // _SECARITM_H_INCLUDED_