#include "nmpp.h"
/*
//int btnum( void *src, int n);
int btnum( void *src, int n)
{ _asm {
   push ebx
   mov ebx,src
   mov eax,n
   bt [ebx],eax
   sbb eax,eax
   pop ebx
}}

int s2(int *Q, int j) // 2х битное число со знаком, начиная с номера бита=j
{ if (btnum(Q,j++)) // интерфейс команды bt [ptr],reg
   { if (btnum(Q,j))return -1; else return 1;
   } else
   { if (btnum(Q,j)) return -2; else return 0;
   }
} // s2 = 2х разрядное число

void nmppsMulC_AddC_2s16s(const nm2s* pSrcVec, int32b nMulC, int  nAddC, nm16s* pDstVec, int nSize)
//int MulC_2s16s (int *psrc, short C, short *pdst, int N2s, short vr)
{  int i,j; 
   short *p=pDstVec;
   int* psrc=(int*)pSrcVec;
   for (i=0; i<nSize; i++)
   { j=s2( psrc, i+i); j*=nMulC;  j+=nAddC;
     *p++=(short)(j & 0xffff);
   }
    
   return (int)p;
} // MulC_2s16s
*/

void nmppsMulC_AddC_2s16s(const nm2s* pSrcVec, int32b nMulC, int  nAddC, nm16s* pDstVec, int nSize)
{
	for (int i=0; i<nSize; i++){ 
		int s= nmppsGet_2s(pSrcVec,i);
		s*=nMulC;
		s+=nAddC;
		pDstVec[i]=s;
   }
}
