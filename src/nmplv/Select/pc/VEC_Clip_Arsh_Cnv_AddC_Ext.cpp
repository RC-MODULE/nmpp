#include "nmplv.h"
struct S_Clip_Arsh_Cnv_AddC_Ext
{
    long lF1cr1;
    long lF1cr2;
    long lSb1;
    long lSb2;
    long lVr;
    long plWeight[16];
};

void nmppsClipArshCnv_AddC_Ext_Set_(int *pnClip, int *pnShift, nm8s *pchC,  S_Clip_Arsh_Cnv_AddC_Ext *pParams);
void nmppsClipArshCnv_AddC_Ext_Exe_16s(nm16s *pshSrc, S_Clip_Arsh_Cnv_AddC_Ext *pParams, nm8s *pchDst, int nSrcSize);


//------------------------------------------------------------------------
static unsigned short ClipTable[16] = 
{
    0xfffe, 0xfffc, 0xfff8, 0xfff0, 
    0xffe0, 0xffc0, 0xff80, 0xff00, 
    0xfe00, 0xfc00, 0xf800, 0xf000, 
    0xe000, 0xc000, 0x8000, 0x0000
}; 
static unsigned short ShiftTable[8] = 
{
    0x0202, 0x000a, 0x0022, 0x0082,
    0x0202, 0x0802, 0x2002, 0x8002
};
static unsigned __int64 WeightTable[8] = 
{
    0x0000000000000001,
    0x0000000000000100,
    0x0000000000010000,
    0x0000000001000000,
    0x0000000100000000,
    0x0000010000000000,
    0x0001000000000000,
    0x0100000000000000
};
//------------------------------------------------------------------------
void nmppsClipArshCnv_AddC_Ext_(v8nm16s *pSrc, v8nm32s *pnClip, v8nm32s *pnShift,    v8nm32s *pnAdd, v8nm8s *pDst, int nSrcSize)
{
	
    int i, i8;
    short shSrc, shClipSign;

    for(i=0; i<nSrcSize*8; i++)
    {
        i8 = i & 0x7;
        shSrc = nmppsGet_16s((nm16s*)pSrc,i);
        shClipSign = shSrc >> nmppsGet_32s((nm32s*)pnClip,i8);
        if((shSrc > 0) && shClipSign)
        {
            shSrc = ~((short)0xFFFF << nmppsGet_32s((nm32s*)pnClip,i8));
        }
        else if((shSrc < 0) && (shClipSign != -1))
        {
            shSrc = (short)0xFFFF << nmppsGet_32s((nm32s*)pnClip,i8);
        }
        //nmppsSetInt_8s((nm8s*)pDst,i, (char)(shSrc >> nmppsGet_32s((nm32s*)pnShift,i8)) + nmppsGetVal_32s((nm32s*)pnAdd,i8));
		nmppsSetInt_8s((nm8s*)pDst,i, (char)(shSrc >> nmppsGet_32s((nm32s*)pnShift,i8)) + nmppsGet_32s((nm32s*)pnAdd,i8));
    }
}
//------------------------------------------------------------------------
void nmppsClipArshCnv_AddC_Ext_Set_(int *pnClip, int *pnShift, nm8s *pchC, 
        S_Clip_Arsh_Cnv_AddC_Ext *pParams)
{
        
}
//------------------------------------------------------------------------
void nmppsClipArshCnv_AddC_Ext_Aux_16s(nm16s *pshSrc, S_Clip_Arsh_Cnv_AddC_Ext *pParams, 
        nm8s *pchDst, int nSrcSize)
{

}
//------------------------------------------------------------------------
void nmppsClipArshCnv_AddC_Ext_16u(nm16u *pnSrc, int *pnClip, int *pnShift, 
        nm4s *pnAdd, nm4s *pnDst, int nSrcSize)
{
    int i, i16;
    nm8u nSrc,nSrcPrev;

	nm16s pnClipPos[16];
	nm16s pnClipNeg[16];
	nm8s  pnAdd8s[16];

	for(i=0;i<16;i++)
	{
		pnClipPos[i]=1<<pnClip[i];
		pnClipNeg[i]=-pnClipPos[i]-1;
		if (i%2)
			pnAdd8s[i]=((nm8s*)pnAdd)[i/2]&0xF;
		else
			pnAdd8s[i]=((nm8s*)pnAdd)[i/2]>>4;
	}
		
    for(i=0; i<nSrcSize; i++)
    {
        i16 = i%16;
        nSrc = pnSrc[i];
        if (nSrc>pnClipPos[i16])
			nSrc=pnClipPos[i16];
		else
			if (nSrc<pnClipNeg[i16])
				nSrc=pnClipNeg[i16];
        nSrc>>=pnShift[i16];
		nSrc+=pnAdd8s[i16];
		nSrcPrev=nSrc<<4;
		if (i%2)
			((nm8u*)pnDst)[i/2] = nSrcPrev|nSrc;
    }
}
