#include "nmpp.h"
#include "minrep.h"


nm64s *L0;
nm64s *L1;
nm64s *G0;
nm64s *G1;
const int KB=1024/8;
const int SizeL0=30*KB;
const int SizeL1=30*KB;

const int SizeG0=30*KB;
const int SizeG1=30*KB;
/*
void Test_nmppsSub_8s8sc(nm32u& crc)
{
	int	MaxCharSize=2048;
	MaxCharSize=MIN(MaxCharSize,SizeL0*8);
	MaxCharSize=MIN(MaxCharSize,SizeG0*8);

	nmppsSet_32s((nm32s*)L0,(int)0xCCCCCCCC,(SizeL0*2));
	nmppsRandUniform_32u((nm32u*)G0,SizeG0*2);

	for(int CharSize=0;CharSize<=MaxCharSize;Charsize+=8*NMPP_MIN_REP)
	{
		nmppsSub_8s((nm8s*)L0,(nm8s*)G0,(nm8s*)G0,CharSize);	
		nmppsCrcAcc_32u((nm32u*)G0,MIN(CharSize/4+128,SizeG0*2),&crc);
	}
	//! \fn void nmppsSub_8s(nm8s*,nm8s*,nm8s*,int)	
}

void Test_nmppsSub_16s16ss(nm32u& crc)
{
	int	MaxShortSize=2048;
	MaxShortSize=MIN(MaxShortSize,SizeL0*4);
	MaxShortSize=MIN(MaxShortSize,SizeG0*4);

	nmppsSet_32s((nm32s*)L0,(int)0xCCCCCCCC,(SizeL0*2));
	nmppsRandUniform_32u((nm32u*)G0,SizeG0*2);

	for(int ShortSize=0;ShortSize<=MaxShortSize;ShortSize+=4*NMPP_MIN_REP)
	{
		nmppsSub_16s((nm16s*)L0,(nm16s*)G0,(nm16s*)G0,ShortSize);	
		nmppsCrcAcc_32u((nm32u*)G0,MIN(ShortSize/2+128,SizeG0*2),&crc);
	}
	//! \fn void nmppsSub_16s(nm16s*,nm16s*,nm16s*,int)	
}

void Test_nmppsSub_32s32si(nm32u& crc)
{
	int	MaxIntSize=2048;
	MaxIntSize=MIN(MaxIntSize,SizeL0*2);
	MaxIntSize=MIN(MaxIntSize,SizeG0*2);

	nmppsSet_32s((nm32s*)L0,(int)0xCCCCCCCC,(SizeL0*2));
	nmppsRandUniform_32u((nm32u*)G0,SizeG0*2);

	for(int IntSize=0;IntSize<=MaxIntSize;IntSize+=2*NMPP_MIN_REP)
	{
		nmppsSub_32s((nm32s*)L0,(nm32s*)G0,(nm32s*)G0,IntSize);	
		nmppsCrcAcc_32u((nm32u*)G0,MIN(IntSize+128,SizeG0*2),&crc);
	}
	//! \fn void nmppsSub_32s(nm32s*,nm32s*,nm32s*,int)	
}

void Test_nmppsSub_64s64sl(nm32u& crc)
{
	int	MaxLongSize=2048;
	MaxLongSize=MIN(MaxLongSize,SizeL0);
	MaxLongSize=MIN(MaxLongSize,SizeG0);

	nmppsSet_32s((nm32s*)L0,(int)0xCCCCCCCC,(SizeL0*2));
	nmppsRandUniform_32u((nm32u*)G0,SizeG0*2);

	for(int LongSize=0;LongSize<=MaxLongSize;LongSize+=NMPP_MIN_REP)
	{
		nmppsSub_64s((nm64s*)L0,(nm64s*)G0,(nm64s*)G0,LongSize);	
		nmppsCrcAcc_32u((nm32u*)G0,MIN(LongSize*2+128,SizeG0*2),&crc);
	}
	//! \fn void nmppsSub_64s(nm64s*,nm64s*,nm64s*,int)	
}
//=======================================================================================
void Test_nmppsAbsDiff_8s8sc(nm32u& crc)
{
	int	MaxCharSize=2048;
	MaxCharSize=MIN(MaxCharSize,SizeL0*8);
	MaxCharSize=MIN(MaxCharSize,SizeG0*8);

	nmppsSet_32s((nm32s*)L0,(int)0xCCCCCCCC,(SizeL0*2));
	nmppsRandUniform_32u((nm32u*)G0,SizeG0*2);

	for(int CharSize=0;CharSize<=MaxCharSize;Charsize+=8*NMPP_MIN_REP)
	{
		nmppsAbsDiff_8s((nm8s*)L0,(nm8s*)G0,(nm8s*)G0,CharSize);	
		nmppsCrcAcc_32u((nm32u*)G0,MIN(CharSize/4+128,SizeG0*2),&crc);
	}
	//! \fn void nmppsAbsDiff_8s(nm8s*,nm8s*,nm8s*,int)	
}

void Test_nmppsAbsDiff_16s16ss(nm32u& crc)
{
	int	MaxShortSize=2048;
	MaxShortSize=MIN(MaxShortSize,SizeL0*4);
	MaxShortSize=MIN(MaxShortSize,SizeG0*4);

	nmppsSet_32s((nm32s*)L0,(1),(SizeL0*2));
	nmppsRandUniform_32u((nm32u*)G0,SizeG0*2);

	for(int ShortSize=0;ShortSize<=MaxShortSize;ShortSize+=4*NMPP_MIN_REP)
	{
		nmppsAbsDiff_16s((nm16s*)L0,(nm16s*)G0,(nm16s*)G0,ShortSize);	
		nmppsCrcAcc_32u((nm32u*)G0,MIN(ShortSize/2+128,SizeG0*2),&crc);
	}
	//! \fn void nmppsAbsDiff_16s(nm16s*,nm16s*,nm16s*,int)	

}

void Test_nmppsAbsDiff_32s32si(nm32u& crc)
{
	int	MaxIntSize=2048;
	MaxIntSize=MIN(MaxIntSize,SizeL0*2);
	MaxIntSize=MIN(MaxIntSize,SizeG0*2);

	nmppsSet_32s((nm32s*)L0,(1),(SizeL0*2));
	nmppsRandUniform_32u((nm32u*)G0,SizeG0*2);

	for(int IntSize=0;IntSize<=MaxIntSize;IntSize+=2*NMPP_MIN_REP)
	{
		nmppsAbsDiff_32s((nm32s*)L0,(nm32s*)G0,(nm32s*)G0,IntSize);	
		nmppsCrcAcc_32u((nm32u*)G0,MIN(IntSize+128,SizeG0*2),&crc);
	}
	//! \fn void nmppsAbsDiff_32s(nm32s*,nm32s*,nm32s*,int)	
}*/
//=======================================================================================
/*
void Test_nmppsSubN8_Abs_8s8sc(nm32u& crc)
{
	int	MaxCharSize=1024;
	MaxCharSize=MIN(MaxCharSize,SizeL0*8);
	MaxCharSize=MIN(MaxCharSize,SizeG0*8);

	nmppsRandUniform_64s((nm64s*)L0,SizeL0);
	nmppsRandUniform_64s((nm64s*)G0,SizeG0);
	nmppsSet_64s((nm64s*)L1,(0xCCCCCCCCAAAAAAAAl),(SizeL1));
	
	union
	{
		nm1	bits;
		char	Char[8];
		int		Int[2];
	}N8;
	for(int CharSize=0;CharSize<=MaxCharSize;Charsize+=8*NMPP_MIN_REP)
	{
		N8.Int[0]=nmppcRand();
		N8.Int[1]=nmppcRand();

		nmppsSubN8_Abs((nm8s*)L0,(nm8s*)N8.Char,(nm8s*)G0,CharSize);	
		nmppsCrcAcc_32u((nm32u*)G0,MIN(CharSize/4+128,SizeL1*2),&crc);
	}
	//! \fn void nmppsSubN8_Abs(nm8s*,nm8s*,nm8s*,int)	
}


void Test_nmppsSubN8_Abs_16s16ss(nm32u& crc)
{
	int	MaxShortSize=1024;
	MaxShortSize=MIN(MaxShortSize,SizeL0*4);
	MaxShortSize=MIN(MaxShortSize,SizeG0*4);

	nmppsRandUniform_64s((nm64s*)L0,SizeL0);
	nmppsSet_32s((nm32s*)G0,(0xCCCCCCCC),(SizeL1*2));
	
	union
	{
		nm1	Bits;
		char	Short[8];
		int		Int[4];
	}N8;
	
	for(int ShortSize=0;ShortSize<=MaxShortSize;ShortSize+=8)
	{
		N8.Int[0]=nmppcRand();
		N8.Int[1]=nmppcRand();
		N8.Int[2]=nmppcRand();
		N8.Int[3]=nmppcRand();

		nmppsSubN8_Abs((nm16s*)L0,(nm16s*)N8.Short,(nm16s*)G0,ShortSize);	
		nmppsCrcAcc_32u((nm32u*)G0,MIN(ShortSize/4+128,SizeL1*2),&crc);
	}
	//! \fn void nmppsSubN8_Abs(nm16s*,nm16s*,nm16s*,int)	
}
*/
//=======================================================================================
/*
void Test_nmppsSubC_8s8s(nm32u& crc)
{
	int	charMaxSize=1024;
	charMaxSize=MIN(charMaxSize,LONG2char(SizeL0));
	charMaxSize=MIN(charMaxSize,LONG2char(SizeG0));

	nmppsRandUniform_64s((nm64s*)L0,SizeL0);
	nm64s c=0xCCCCCCCCAAAAAAAAl;
	nmppsSet_64s((nm64s*)G0,c,(SizeG0));
	
	for(int nSize=0;nSize<=charMaxSize;nSize+=8)
	{
		char nVal=nmppcRand();
		nmppsSubC_8s((nm8s*)L0,nVal,(nm8s*)G0,nSize);	
		nmppsCrcAcc_32u((nm32u*)G0,MIN(char2INT(nSize)+128,LONG2INT(SizeG0)),&crc);
	}
	//! \fn void nmppsSubC_8s(nm8s*,char,nm8s*,int)	
}

void Test_nmppsSubC_16s16s(nm32u& crc)
{
	int	shortMaxSize=1024;
	shortMaxSize=MIN(shortMaxSize,LONG2short(SizeL0));
	shortMaxSize=MIN(shortMaxSize,LONG2short(SizeG0));

	nmppsRandUniform_64s((nm64s*)L0,SizeL0);
	nm64s c=0xCCCCCCCCAAAAAAAAl;
	nmppsSet_64s((nm64s*)G0,c,(SizeG0));
	
	for(int nSize=0;nSize<=shortMaxSize;nSize+=4*NMPP_MIN_REP)
	{
		short nVal=nmppcRand();
		nmppsSubC_16s((nm16s*)L0,nVal,(nm16s*)G0,nSize);	
		nmppsCrcAcc_32u((nm32u*)G0,MIN(short2INT(nSize)+128,LONG2INT(SizeG0)),&crc);
	}
	//! \fn void nmppsSubC_16s(nm16s*,short,nm16s*,int)	
}

void Test_nmppsSubC_32s32s(nm32u& crc)
{
	int	intMaxSize=1024;
	intMaxSize=MIN(intMaxSize,LONG2int(SizeL0));
	intMaxSize=MIN(intMaxSize,LONG2int(SizeG0));

	nmppsRandUniform_64s((nm64s*)L0,SizeL0);
	nm64s c=0xCCCCCCCCAAAAAAAAl;
	nmppsSet_64s((nm64s*)G0,c,(SizeG0));
	
	for(int nSize=0;nSize<=intMaxSize;nSize+=2*NMPP_MIN_REP)
	{
		int nVal=nmppcRand();
		nmppsSubC_32s((nm32s*)L0,nVal,(nm32s*)G0,nSize);	
		nmppsCrcAcc_32u((nm32u*)G0,MIN(int2INT(nSize)+128,LONG2INT(SizeG0)),&crc);
	}
	//! \fn void nmppsSubC_32s(nm32s*,int,nm32s*,int)	
}

void Test_nmppsSubC_64s64sl(nm32u& crc)
{
	int	MaxLongSize=512;
	MaxLongSize=MIN(MaxLongSize,SizeL0);
	MaxLongSize=MIN(MaxLongSize,SizeG0);

	nmppsRandUniform_64s((nm64s*)L0,SizeL0);
	nm64s c=0xCCCCCCCCAAAAAAAAl;
	nmppsSet_64s((nm64s*)G0,c,(SizeG0));

	__int64 nVal;
	nmppsRandUniform_32u((nm32u*)&nVal,2);
	
	for(int LongSize=0;LongSize<=MaxLongSize;LongSize+=NMPP_MIN_REP)
	{
		nmppsSubC_64s((nm64s*)L0,&nVal,(nm64s*)G0,LongSize);	
		nmppsCrcAcc_32u((nm32u*)G0,MIN(LongSize*2+128,SizeG0*2),&crc);
	}
	//! \fn void nmppsSubC_64s(nm64s*,nm64s*,nm64s*,int)	

}

//=======================================================================================

void Test_nmppsSubCRev_8s8s(nm32u& crc)
{
	int	charMaxSize=1024;
	charMaxSize=MIN(charMaxSize,LONG2char(SizeL0));
	charMaxSize=MIN(charMaxSize,LONG2char(SizeG0));

	nmppsRandUniform_64s((nm64s*)L0,SizeL0);
	nm64s c=0xCCCCCCCCAAAAAAAAl;
	nmppsSet_64s((nm64s*)G0,c,(SizeG0));
	
	for(int nSize=0;nSize<=charMaxSize;nSize+=8)
	{
		char nVal=nmppcRand();
		nmppsSubCRev_8s((nm8s*)L0,nVal,(nm8s*)G0,nSize);	
		nmppsCrcAcc_32u((nm32u*)G0,MIN(char2INT(nSize)+128,LONG2INT(SizeG0)),&crc);
	}
	//! \fn void nmppsSubCRev_8s(nm8s*,char,nm8s*,int)	
}

void Test_nmppsSubCRev_16s16s(nm32u& crc)
{
	int	shortMaxSize=1024;
	shortMaxSize=MIN(shortMaxSize,LONG2short(SizeL0));
	shortMaxSize=MIN(shortMaxSize,LONG2short(SizeG0));

	nmppsRandUniform_64s((nm64s*)L0,SizeL0);
	nm64s c=0xCCCCCCCCAAAAAAAAl;
	nmppsSet_64s((nm64s*)G0,c,(SizeG0));
	
	for(int nSize=0;nSize<=shortMaxSize;nSize+=4*NMPP_MIN_REP)
	{
		short nVal=nmppcRand();
		nmppsSubCRev_16s((nm16s*)L0,nVal,(nm16s*)G0,nSize);	
		nmppsCrcAcc_32u((nm32u*)G0,MIN(short2INT(nSize)+128,LONG2INT(SizeG0)),&crc);
	}
	//! \fn void nmppsSubCRev_16s(nm16s*,short,nm16s*,int)	
}

void Test_nmppsSubCRev_32s32s(nm32u& crc)
{
	int	intMaxSize=1024;
	intMaxSize=MIN(intMaxSize,LONG2int(SizeL0));
	intMaxSize=MIN(intMaxSize,LONG2int(SizeG0));

	nmppsRandUniform_64s((nm64s*)L0,SizeL0);
	nm64s c=0xCCCCCCCCAAAAAAAAl;
	nmppsSet_64s((nm64s*)G0,c,(SizeG0));
	
	for(int nSize=0;nSize<=intMaxSize;nSize+=2*NMPP_MIN_REP)
	{
		int nVal=nmppcRand();
		nmppsSubCRev_32s((nm32s*)L0,nVal,(nm32s*)G0,nSize);	
		nmppsCrcAcc_32u((nm32u*)G0,MIN(int2INT(nSize)+128,LONG2INT(SizeG0)),&crc);
	}
	//! \fn void nmppsSubCRev_32s(nm32s*,int,nm32s*,int)	
}

/////////////////////////////////////////////////////////////////////////////////////////

void Test_nmppsSubCRev_64s64sl(nm32u& crc)
{
	int	MaxLongSize=512;
	MaxLongSize=MIN(MaxLongSize,SizeL0);
	MaxLongSize=MIN(MaxLongSize,SizeG0);

	nmppsRandUniform_64s((nm64s*)L0,SizeL0);
	nm64s c=0xCCCCCCCCAAAAAAAAl;
	nmppsSet_64s((nm64s*)G0,c,(SizeG0));

	__int64 nVal;
	nmppsRandUniform_32u((nm32u*)&nVal,2);
	
	for(int LongSize=0;LongSize<=MaxLongSize;LongSize+=NMPP_MIN_REP)
	{
		nmppsSubCRev_64s((nm64s*)L0,&nVal,(nm64s*)G0,LongSize);	
		nmppsCrcAcc_32u((nm32u*)G0,MIN(LongSize*2+128,SizeG0*2),&crc);
	}
	//! \fn void nmppsSubCRev_64s(nm64s*,nm64s*,nm64s*,int)	
}

void Test_nmppsAbsDiff_64s64sl(nm32u& crc)
{
	int	MaxLongSize=512;
	MaxLongSize=MIN(MaxLongSize,SizeL0);
	MaxLongSize=MIN(MaxLongSize,SizeG0);

	nmppsRandUniform_64s((nm64s*)L0,SizeL0);
	nm64s c=0xCCCCCCCCAAAAAAAAl;
	nmppsSet_64s((nm64s*)G0,c,(SizeG0));

	for(int LongSize=0;LongSize<=MaxLongSize;LongSize+=NMPP_MIN_REP)
	{
		nmppsAbsDiff_64s((nm64s*)L0,(nm64s*)G0,(nm64s*)G0,LongSize);	
		nmppsCrcAcc_32u((nm32u*)G0,MIN(LongSize*2+128,SizeG0*2),&crc);

	}
	//! \fn void nmppsAbsDiff_64s(nm64s*,nm64s*,nm64s*,int)	
}*/
/*
void Test_nmppsSubN8_Abs_32s32si(nm32u& crc)
{
	int	MaxIntSize=512;
	MaxIntSize=MIN(MaxIntSize,SizeL0*2);
	MaxIntSize=MIN(MaxIntSize,SizeG0*2);

	nmppsRandUniform_64s((nm64s*)L0,SizeL0);
	nmppsSet_64s((nm64s*)G0,(0xCCCCCCCCAAAAAAAAl),(SizeG0));
	
	__int64 N8[4];
	
	for(int IntSize=0;IntSize<=MaxIntSize;IntSize+=2*NMPP_MIN_REP)
	{
		nmppsRandUniform_64s((nm64s*)N8,4,95367181l*IntSize);

		nmppsSubN8_Abs((nm32s*)L0,(nm32s*)N8,(nm32s*)G0,IntSize);	
		nmppsCrcAcc_32u((nm32u*)G0,MIN(IntSize+128,SizeG0*2),&crc);
	}
	//! \fn void nmppsSubN8_Abs(nm32s*,nm32s*,nm32s*,int)		
}

void Test_nmppsSubN16_Abs_32s32si(nm32u& crc)
{
	int	MaxIntSize=512;
	MaxIntSize=MIN(MaxIntSize,SizeL0*2);
	MaxIntSize=MIN(MaxIntSize,SizeG0*2);

	nmppsRandUniform_64s((nm64s*)L0,SizeL0);
	nmppsSet_64s((nm64s*)G0,(0xCCCCCCCCAAAAAAAAl),(SizeG0));
	
	__int64 N16[8];
	
	for(int IntSize=0;IntSize<=MaxIntSize;IntSize+=2*NMPP_MIN_REP)
	{
		nmppsRandUniform_64s((nm64s*)N16,8,95367181l*IntSize);

		nmppsSubN8_Abs((nm32s*)L0,(nm32s*)N16,(nm32s*)G0,IntSize);	
		nmppsCrcAcc_32u((nm32u*)G0,MIN(IntSize+128,SizeG0*2),&crc);
	}
	//! \fn void nmppsSubN16_Abs(nm32s*,nm32s*,nm32s*,int)		
}

void Test_nmppsSubN16_Abs_8s8sc(nm32u& crc)
{
	int	MaxCharSize=512;
	MaxCharSize=MIN(MaxCharSize,SizeL0*8);
	MaxCharSize=MIN(MaxCharSize,SizeG0*8);

	nmppsRandUniform_64s((nm64s*)L0,SizeL0);
	nmppsSet_64s((nm64s*)G0,(0xCCCCCCCCAAAAAAAAl),(SizeG0));
	
	__int64 N16[2];
	
	for(int CharSize=0;CharSize<=MaxCharSize;CharSize+=2)
	{
		nmppsRandUniform_64s((nm64s*)N16,2,95367181l*CharSize);

		nmppsSubN16_Abs((nm8s*)L0,(nm8s*)N16,(nm8s*)G0,CharSize);	
		nmppsCrcAcc_32u((nm32u*)G0,MIN(CharSize/4+128,SizeG0*2),&crc);
	}
	//! \fn void nmppsSubN16_Abs(nm8s*,nm8s*,nm8s*,int)		
}

  */
//////////////////////////////////////////////////////////////////



int main()
{
	

	L0=nmppsMalloc_64s(SizeL0);
	L1=nmppsMalloc_64s(SizeL1);
	G0=nmppsMalloc_64s(SizeG0);
	G1=nmppsMalloc_64s(SizeG1);
	if ((L0==0)||(L1==0)||(G0==0)||(G1==0)) return -1;


	unsigned int crc = 0;

	int	MaxCharSize=2048;
	MaxCharSize=MIN(MaxCharSize,SizeL0*8);
	MaxCharSize=MIN(MaxCharSize,SizeG0*8);

	nmppsSet_32s((nm32s*)L0,(int)0xCCCCCCCC,(SizeL0*2));
	nmppsRandUniform_32u((nm32u*)G0,SizeG0*2);

	for(int CharSize=0;CharSize<=MaxCharSize;Charsize+=8*NMPP_MIN_REP)
	{
		nmppsSub_8s((nm8s*)L0,(nm8s*)G0,(nm8s*)G0,CharSize);	
		nmppsCrcAcc_32u((nm32u*)G0,MIN(CharSize/4+128,SizeG0*2),&crc);
	}
	//! \fn void nmppsSub_8s(nm8s*,nm8s*,nm8s*,int)

	nmppsFree(L0);
	nmppsFree(L1);
	nmppsFree(G0);
	nmppsFree(G1);

	

	return crc>>2;

}

