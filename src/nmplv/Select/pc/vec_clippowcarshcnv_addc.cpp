#include "nmplv.h"
//
void VEC_ClipArshCnv_AddC( nm32s* pSrcVec, int nClipFactor,
    int nShift, int8b nAddValue,nm8s* pDstVec, int nSize)
{  
	int	ClipPos=(1<<nClipFactor)-1;	
	int ClipNeg=-ClipPos-1;
	
	for(int i=0;i<nSize;i++,pSrcVec++,pDstVec++)
	{
		int x=*pSrcVec;
		if (x>ClipPos)
			x=ClipPos;
		else if (x<ClipNeg)
			x=ClipNeg;
		x>>=nShift;
		x+=nAddValue;
		*pDstVec=x;
	}
	
	/*
	if (nSize)
	{
 
	   _asm
		{  cld;
		   push ebp;
		   mov esi, pSrcVec;
		   mov edi, pDstVec;
		   mov ecx,nClipFactor;
		   sub ecx,nShift;
		   mov edx,1;
		   shl edx,cl;
		   mov ecx,nShift;
		   mov ebx,nSize;
		   mov ebp,dword ptr nAddValue;
	//-------------------------
	  L0:  lodsd;
					 
		   sar eax,cl;
		   Cmp ax,dx;
		   jl L1;
		   mov eax,edx;
		   dec eax;
	  L1:  add eax,edx;
		   jge L2;
		   xor eax,eax;
	  L2:  sub eax,edx;
		   add eax,ebp;
		   stosb;
		   dec ebx;
		   jnz L0;
		   pop ebp;
		}
	}*/
}
