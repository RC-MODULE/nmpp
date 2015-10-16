#include "nmpli.h"
int wgh1[]={ 0x1d2f,0x9646,0x4c8b,0 };
int wgh2[]={ 0x1d2f,0x9646,0x4c8b,0 };
void IMG_RGB32ToGray(RGB32_nm8u * pRGB, nm32u* pDstGray, int nSize)
{  int i,j, k;
   unsigned int * p;
   unsigned char * rgb; 
   p=(unsigned int*)pDstGray;
   rgb=(unsigned char *)pRGB;
  j=0;
  for (i=0; i<nSize; i++)
  { 
     k= wgh1[0]*rgb[j];
     k+=wgh1[1]*rgb[j+1];
     k+=wgh1[2]*rgb[j+2];
     j+=4;
     p[i]=k;
     i++;
     k= wgh2[0]*rgb[j];
     k+=wgh2[1]*rgb[j+1];
     k+=wgh2[2]*rgb[j+2];
     j+=4;
     p[i]=k;

  }
   
}
void IMG_RGB32ToGray(RGB32_nm8u * pRGB, nm32s* pDstGray, int nSize)
{  int i,j, k;
   int * p; 
   unsigned char * rgb; 
   p=(int*)pDstGray;
   rgb=(unsigned char*)pRGB;

  j=0;
  for (i=0; i<nSize; i++)
  { 
     k= wgh1[0]*rgb[j];
     k+=wgh1[1]*rgb[j+1];
     k+=wgh1[2]*rgb[j+2];
     j+=4;
     p[i]=k-0x800000;
     i++;
     k= wgh2[0]*rgb[j];
     k+=wgh2[1]*rgb[j+1];
     k+=wgh2[2]*rgb[j+2];
     j+=4;
     p[i]=k-0x800000;

  }
   
}
