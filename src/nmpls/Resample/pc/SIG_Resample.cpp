#include "nmtype.h"
#include "nmtl.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////
static double PolyphaseFilter3div2[3*4*2+1] = {     
		 0,
   -0.0057,
   -0.0062,
         0,
    0.0323,
    0.0367,
		 0,
   -0.1120,
   -0.1394,
		 0,
    0.3983,
    0.7956,
    1.0000,
    0.7956,
    0.3983,
		 0,
   -0.1394,
   -0.1120,
		 0,
    0.0367,
    0.0323,
         0,
   -0.0062,
   -0.0057,
		 0
};

static double PolyphaseFilter5div4[5*4*2+1] = {     
         0,
   -0.0038,
   -0.0063,
   -0.0066,
   -0.0044,
         0,
    0.0212,
    0.0362,
    0.0391,
    0.0266,
		 0,
   -0.0713,
   -0.1276,
   -0.1455,
   -0.1061,
		 0,
    0.2279,
    0.4844,
    0.7260,
    0.9096,
    1.0000,
    0.9096,
    0.7260,
    0.4844,
    0.2279,
		 0,
   -0.1061,
   -0.1455,
   -0.1276,
   -0.0713,
		 0,
    0.0266,
    0.0391,
    0.0362,
    0.0212,
         0,
   -0.0044,
   -0.0066,
   -0.0063,
   -0.0038,
         0
};

void MakeResampleUp3Down2TblFiles()
{
	
//	mtr<double>	tblDCT_left (ptblDCT_left,8,8);	
//	mtr<double>	tblDCT_right(ptblDCT_right,8,8);	
//	mtr<double>	tblIDCT_left(ptblIDCT_left,8,8);	
//	mtr<double>	tblIDCT_right(ptblIDCT_right,8,8);
//
//	nmmtr64s	packed_tblDCT_left_8   ((nm64s*)ptblDCT_left_8,8,1);
//	nmmtr64s	packed_tblDCT_right_32 ((nm64s*)ptblDCT_right_32,8,4);
//	nmmtr64s	packed_tblIDCT_left_8  ((nm64s*)ptblIDCT_left_8,8,1);
//	nmmtr64s	packed_tblIDCT_right_32((nm64s*)ptblIDCT_right_32,8,4);
//
//	nmmtr64s	repacked_tblDCT_right_32(4,8);
//	nmmtr64s	repacked_tblIDCT_right_32(4,8);
//
//
//	repacked_tblDCT_right_32=packed_tblDCT_right_32.transpose();
//	repacked_tblIDCT_right_32=packed_tblIDCT_right_32.transpose();
//
//	ofstream fout_asm("DctTable.asm");
//	fout_asm << "global DCT_Right: ";
//	AsmArray(fout_asm,repacked_tblDCT_right_32);
//
//	fout_asm << "global DCT_Left: ";
//	AsmArray(fout_asm,packed_tblDCT_left_8);
//
//	fout_asm << "global IDCT_Right: ";
//	AsmArray(fout_asm,repacked_tblIDCT_right_32);
//
//	fout_asm << "global IDCT_Left: ";
//	AsmArray(fout_asm,packed_tblIDCT_left_8);
//
//
//	ofstream fout_cpp("fDctTable.cpp");
//
//	fout_cpp << "double tblDCT_left[8][8]=" << tblDCT_left;
//	fout_cpp << "double tblDCT_right[8][8]=" << tblDCT_left;
}

int SIG_SetResampleUp3Down2_8s16s(nm64s* pKernel)
{
	for(int i=0;i<25;i++)
	{
		((nm16s*)pKernel)[i]=floor(PolyphaseFilter3div2[i]*64+0.5);
	}
	return 0;
}

void SIG_ResampleUp3Down2(nm8s* pSrcVec, nm16s* pDstVec, int nSrcVecSize,  nm64s* pKernel)
{
	nmvec16s vKernel((nm16s*)pKernel,25);				// Filter kernel
	nmvec8s  vSrcUpsample(nSrcVecSize*3,20);	// Resampled vSrc by 3 times
	nmvec16s vDstUpsample(nSrcVecSize*3);		// Filtered vSrcUpsample
	int i,j;
	
	// Filxed point coefficient initialization
	//	for(i=0;i<10;i++)
	//	{
	//		vKernel[i]=0;
	//		vKernel[24-i]=0;
	//	}
	//	vKernel[10]=21;
	//	vKernel[11]=43;
	//	vKernel[13]=43;
	//	vKernel[14]=21;
	//	vKernel[10]=0;
	//	vKernel[11]=64;
	//	vKernel[13]=64;
	//	vKernel[14]=0;



		// Resampling by 3 times
	vSrcUpsample.reset();
	for(i=-4;i<nSrcVecSize+4;i++)
	{
		vSrcUpsample[i*3]=pSrcVec[i];
	}
		// Filtration
	for(i=0;i<nSrcVecSize*3;i++)
	{
		nmvec8s vLocalSrcUpsample(vSrcUpsample.m_data+i-25/2,25);
		vDstUpsample[i]=vLocalSrcUpsample*vKernel;
	}
		// Decimation by 2
	for(i=0,j=0;i<nSrcVecSize*3;i+=2,j++)
	{
		pDstVec[j]=vDstUpsample[i].m_value;
	}
}



void SIG_Resample5div4_RShift0(nm8s* pSrcVec,int nSrcVecSize, nm16s* pDstVec)
{
	nmvec16s vKernel(41);				// Filter kernel
	nmvec8s  vSrcUpsample(nSrcVecSize*5,22);	// Resampled vSrc by 5 times
	nmvec16s vDstUpsample(nSrcVecSize*5);		// Filtered vSrcUpsample
	int i,j;
		// Filxed point coefficient initialization
	for(i=0;i<41;i++)
	{
		
		vKernel[i]=floor(PolyphaseFilter5div4[i]*64+0.5);
	}

		// Resampling by 5 times
	vSrcUpsample.reset();
	for(i=0;i<nSrcVecSize;i++)
	{
		vSrcUpsample[i*5]=pSrcVec[i];
	}
		// Filtration
	for(i=0;i<nSrcVecSize*5;i++)
	{
		nmvec8s vLocalSrcUpsample(vSrcUpsample.m_data+i-41/2,41);
		vDstUpsample[i]=vLocalSrcUpsample*vKernel;
	}
		// Decimation by 4
	for(i=0,j=0;i<nSrcVecSize*5;i+=4,j++)
	{
		pDstVec[j]=vDstUpsample[i].m_value;
	}
}

void SIG_Resample(nm8s* pSrcVec, int nSrcVecSize, int nP, int nQ, int nK, int nWindow, nm16s* pDstVec)
{

	const double PI=3.1415926535897932384626433832795;
	double fP=nP;
	double v;
	int k,i,j;
	int nFixpoint=64;
	if (nP>=nQ)
	{

		
		nmvec16s vKernel(nP*nK+1);
		vec<double> vHamming(nP*nK+1);
		vec<double> vImpulse(nP*nK+1);
		vec<double> vEnergy(nP);
	
		if(nK==1)
		{
			vImpulse.reset();
			for(k=0;k<vKernel.size-1;k++)
			{
				vImpulse[k]=1;
			}

		}
		else
		{
			ASSERTE(nK%2==0);
				// Impulse function generation
			vImpulse[vImpulse.size/2]=1;
			for(k=1;k<=vKernel.size/2;k++)
			{
				v=sin(PI*double(k)/fP)/(PI*k/fP); //1.0/nP*
				vImpulse[vImpulse.size/2+k]=v;
				vImpulse[vImpulse.size/2-k]=v;
			}

			vEnergy.reset();
			for(i=0;i<nP;i++)
				for(k=i;k<vImpulse.size;k+=nP)
					vEnergy[i]+=vImpulse[k];

			if (nWindow)
			{
					// Hamming window function generation
				for(k=0;k<vHamming.size;k++)
				{
					vHamming[k]=0.54-0.46*cos(2*PI*k/(vHamming.size-1));
				}
					// multiplication of impulse response by Hamming window
				for(k=0;k<vImpulse.size;k++)
				{
					vImpulse[k]*=vHamming[k];
				}
			}
		}

		vEnergy.reset();
		for(i=0;i<nP;i++)
			for(k=i;k<vImpulse.size;k+=nP)
				vEnergy[i]+=vImpulse[k];
	
		for(i=0;i<nP;i++)
			for(k=i;k<vImpulse.size;k+=nP)
				vImpulse[k]/=vEnergy[i];
	
		vEnergy.reset();
		for(i=0;i<nP;i++)
			for(k=i;k<vImpulse.size;k+=nP)
				vEnergy[i]+=vImpulse[k];


			// Filxed point kernel coefficient initialization
		for(k=0;k<vImpulse.size;k++)
			vKernel[k]=floor(vImpulse[k]*nFixpoint+0.5);
			// Up-resampling by nP times
		nmvec8s  vSrcUpsample(nSrcVecSize*nP,nP*nK);	// Up-Resampled vSrcVec by nP times
		nmvec16s vDstUpsample(nSrcVecSize*nP);			// Filtered vSrcUpsample

		vSrcUpsample.reset();
		for(i=0;i<nSrcVecSize;i++)
		{
			vSrcUpsample[i*nP]=pSrcVec[i];
		}

			// Filtration
		for(i=0;i<vDstUpsample.size;i++)
		{
			nmvec8s vLocalSrcUpsample(vSrcUpsample.m_data+i-vKernel.size/2,vKernel.size);
			vDstUpsample[i]=vLocalSrcUpsample*vKernel;
		}
			// Decimation by 4
		//for(i=0,j=0;i<vSrcUpsample.size;i+=nQ,j++)
		for(i=0,j=0;j<nSrcVecSize*nP/nQ;i+=nQ,j++)
		{
			pDstVec[j]=vDstUpsample[i].m_value;
		}
	}
}

void SIG_VResample(nm8s* pSrcImg, int nSrcStride, int nSrcWidth, int nSrcHeight, int nP, int nQ, int nK, int nWindow, nm16s* pDstImg)
{
	nmmtr8s  mSrcImg(pSrcImg,nSrcHeight,nSrcWidth);
	nmmtr16s mDstImg(pDstImg,nSrcHeight*nP/nQ,nSrcWidth);

	const double PI=3.1415926535897932384626433832795;
	double fP=nP;
	double v;
	int k,i,j;
	int nFixpoint=64;
	if (nP>=nQ)
	{

		

		nmvec16s vKernel(nP*nK+1);
		vec<double> vHamming(nP*nK+1);
		vec<double> vImpulse(nP*nK+1);
		vec<double> vEnergy(nP);

		if(nK==1)
		{
			vImpulse.reset();
			for(k=0;k<vKernel.size-1;k++)
			{
				vImpulse[k]=1;
			}

		}
		else
		{
			ASSERTE(nK%2==0);
				// Impulse function generation
			vImpulse[vImpulse.size/2]=1;
			for(k=1;k<=vKernel.size/2;k++)
			{
				v=sin(PI*double(k)/fP)/(PI*k/fP); //1.0/nP*
				vImpulse[vImpulse.size/2+k]=v;
				vImpulse[vImpulse.size/2-k]=v;
			}
			
			if (nWindow)
			{
		
					// Hamming window function generation
				for(k=0;k<vHamming.size;k++)
				{
					vHamming[k]=0.54-0.46*cos(2*PI*k/(vHamming.size-1));
				}
					// multiplication of impulse response by Hamming window
				for(k=0;k<vImpulse.size;k++)
				{
					vImpulse[k]*=vHamming[k];
				}
			}
		}

		vEnergy.reset();
		for(i=0;i<nP;i++)
			for(k=i;k<vImpulse.size;k+=nP)
				vEnergy[i]+=vImpulse[k];
	
		for(i=0;i<nP;i++)
			for(k=i;k<vImpulse.size;k+=nP)
				vImpulse[k]/=vEnergy[i];
	
			// Filxed point kernel coefficient initialization
		for(k=0;k<vImpulse.size;k++)
			vKernel[k]=floor(vImpulse[k]*nFixpoint+0.5);

		nmvec8s  vSrcUpsample(nSrcHeight*nP,nP*nK);		// Up-Resampled vSrcVec by nP times
		nmvec16s vDstUpsample(nSrcHeight*nP);			// Filtered vSrcUpsample
		vSrcUpsample.reset();

		for(int x=0;x<nSrcWidth;x++)
		{
			int y;
				// Up-resampling by nP times
			for( y=0;y<nSrcHeight;y++)
			{
				
				vSrcUpsample[y*nP]= mSrcImg[y][x];
			}

				// Filtration
			for(i=0;i<vSrcUpsample.size;i++)
			{
				nmvec8s vLocalSrcUpsample(vSrcUpsample.m_data+i-vKernel.size/2,vKernel.size);
				vDstUpsample[i]=vLocalSrcUpsample*vKernel;
			}

				// Decimation by 4
			for(y=0,i=0;y<mDstImg.m_height;i+=nQ,y++)
			{
				mDstImg[y][x]=vDstUpsample[i].m_value;
			}
		}

	}
}