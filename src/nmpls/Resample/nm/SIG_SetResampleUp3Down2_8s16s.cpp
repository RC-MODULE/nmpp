
#include "nmpp.h"
#include "math.h"
float PolyphaseFilter3x4[3*4*2+1] = {     
		 0,
   -0.0057,
   -0.0062,
         0,
    0.0323,
    0.0367,
   -0.0000,
   -0.1120,
   -0.1394,
    0.0000,
    0.3983,
    0.7956,
    1.0000,
    0.7956,
    0.3983,
    0.0000,
   -0.1394,
   -0.1120,
   -0.0000,
    0.0367,
    0.0323,
         0,
   -0.0062,
   -0.0057,
   0};

int SIG_SetResampleUp3Down2_8s16s(nm64s* Kernel)
{
	nm16s* pKernel=(nm16s*)Kernel;

	float* pFilter=PolyphaseFilter3x4;
	int a[8];
	int b[8];

	float K=64;
	
	float x=pFilter[2];
	float r=x*K;
	a[0]=floor(r+0.5);
	a[1]=floor(pFilter[5]*K+0.5);
	a[2]=floor(pFilter[8]*K+0.5);
	a[3]=floor(pFilter[11]*K+0.5);
	a[4]=floor(pFilter[14]*K+0.5);
	a[5]=floor(pFilter[17]*K+0.5);
	a[6]=floor(pFilter[20]*K+0.5);
	a[7]=floor(pFilter[23]*K+0.5);
	
	b[0]=floor(pFilter[1]*K+0.5);
	b[1]=floor(pFilter[4]*K+0.5);
	b[2]=floor(pFilter[7]*K+0.5);
	b[3]=floor(pFilter[10]*K+0.5);
	b[4]=floor(pFilter[13]*K+0.5);
	b[5]=floor(pFilter[16]*K+0.5);
	b[6]=floor(pFilter[19]*K+0.5);
	b[7]=floor(pFilter[22]*K+0.5);
	
	
	nmppsSet_16s(pKernel,((short)0),3*16*4);
	int i;
	for(i=0;i<8;i++)
	{
		nmppsSetInt_16s(pKernel,(5+i)*4+1,b[i]);
		nmppsSetInt_16s(pKernel,(6+i)*4+2,a[i]);

		nmppsSetInt_16s(pKernel,(16+i)*4+1,a[i]);
		nmppsSetInt_16s(pKernel,(17+i)*4+3,b[i]);

		nmppsSetInt_16s(pKernel,(34+i)*4+0,a[i]);
		nmppsSetInt_16s(pKernel,(35+i)*4+2,b[i]);
		nmppsSetInt_16s(pKernel,(36+i)*4+3,a[i]);
	}

	for(i=0;i<6;i++)
	{
		nmppsSetInt_16s(pKernel,(16+i)*4+0,b[i+1]);
	}

	nmppsSetInt_16s(pKernel,8*4+0,(short)K);
	nmppsSetInt_16s(pKernel,10*4+3,(short)K);
	nmppsSetInt_16s(pKernel,20*4+2,(short)K);
	nmppsSetInt_16s(pKernel,38*4+1,(short)K);
	return 16*3*4>>1;
}