#ifdef USE_IPP

#include "stdafx.h"
#include "iPlessyDetector.h"
//#include "ippe.h"
#include "ipp.h"
#include <math.h>
#include "isubpixel2dimpl.h"

///////////////////////////////////////////////////////////////////////////////////////////////////

I_PlessyCornerDetector* CreatePlessyCornerDetector(PCD_TYPE type)
{
	if (type == PCD_32f)
		return (I_PlessyCornerDetector*) new C_PlessyCornerDetector_32f();
	else
		if (type == PCD_16s)
			return (I_PlessyCornerDetector*) new C_PlessyCornerDetector_16s();
		else return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

C_PlessyCornerDetector::C_PlessyCornerDetector()
{
//	SubPixelMinPosition = new C_2DSubPixelMinPosition();

	SubPixelMinPosition = Create2DSubPixelMinPosition(SPP_par);
}

C_PlessyCornerDetector::~C_PlessyCornerDetector()
{
//	delete SubPixelMinPosition;
	SubPixelMinPosition->Release();
}

void C_PlessyCornerDetector::Release()
{
	delete this;
}

void C_PlessyCornerDetector::Allocate(int w, int h, int ww)
{
	fxi=new short[ww*h];
	fyi=new short[ww*h];

	Picture16=new short[ww*h];

	SumSxxSyy=new float[ww*h];
	Subxy=new float[ww*h];
	cres=new unsigned char[ww*h];
}

void C_PlessyCornerDetector::DeAllocate()
{
	delete[] fxi;
	delete[] fyi;
	delete[] Picture16;
	delete[] SumSxxSyy;
	delete[] Subxy;
	delete[] cres;
}

void C_PlessyCornerDetector_16s::SetThreshold(float _threshold)
{
	threshold=(short)_threshold;
}
void C_PlessyCornerDetector_32f::SetThreshold(float _threshold)
{
	threshold=_threshold;
}



void C_PlessyCornerDetector_16s::Allocate(int w, int h, int ww)
{
	C_PlessyCornerDetector::Allocate(w, h, ww);

	sxxi=new short[ww*h];
	sxyi=new short[ww*h];
	syyi=new short[ww*h];

	Sxxi=new short[ww*h];
	Sxyi=new short[ww*h];
	Syyi=new short[ww*h];

	Sxxit=new short[ww*h];
	Syyit=new short[ww*h];

	SumSxxSyyi=new short[ww*h];
	MulSxxSyyi=new short[ww*h];
	MulSxySxyi=new short[ww*h];
	Subxyi=new short[ww*h];
	cSubxyi=new short[ww*h];
}

void C_PlessyCornerDetector_32f::Allocate(int w, int h, int ww)
{
	C_PlessyCornerDetector::Allocate(w, h, ww);

	fx=new float[ww*h];
	fy=new float[ww*h];

	sxx=new float[ww*h];
	sxy=new float[ww*h];
	syy=new float[ww*h];

	Sxx=new float[ww*h];
	Sxy=new float[ww*h];
	Syy=new float[ww*h];

	SumSxxSyy=new float[ww*h];
	Subxy=new float[ww*h];

	MulSxxSyy=new float[ww*h];
	MulSxySxy=new float[ww*h];
	cSubxy=new float[ww*h];
}



void C_PlessyCornerDetector_16s::DeAllocate()
{
	C_PlessyCornerDetector::DeAllocate();

	delete[] sxxi;
	delete[] sxyi;
	delete[] syyi;

	delete[] Sxxi;
	delete[] Sxyi;
	delete[] Syyi;

	delete[] Sxxit;
	delete[] Syyit;

	delete[] SumSxxSyyi;
	delete[] MulSxxSyyi;
	delete[] MulSxySxyi;
	delete[] Subxyi;
	delete[] cSubxyi;
}	

void C_PlessyCornerDetector_32f::DeAllocate()
{
	C_PlessyCornerDetector::DeAllocate();

	delete[] fx;
	delete[] fy;

	delete[] sxx;
	delete[] sxy;
	delete[] syy;

	delete[] Sxx;
	delete[] Sxy;
	delete[] Syy;

	delete[] MulSxxSyy;
	delete[] MulSxySxy;
	delete[] cSubxy;
}	




void C_PlessyCornerDetector::CountDer(unsigned char *Picture, int w, int h, int ww)
{
	{
		IppiSize imgSize={w, h};
		ippiConvert_8u16s_C1R(Picture, ww, Picture16, ww<<1, imgSize);
	}
	IppiSize imgSize={w-2, h-2};

	ippiFilterSobelHoriz_16s_C1R(Picture16+ww+1, ww<<1, fxi+ww+1, ww<<1, imgSize);
	ippiFilterSobelVert_16s_C1R(Picture16+ww+1, ww<<1, fyi+ww+1, ww<<1, imgSize);
}
void C_PlessyCornerDetector_32f::CountDer(unsigned char *Picture, int w, int h, int ww)
{
	IppiSize imgSize={w, h};

	C_PlessyCornerDetector::CountDer(Picture, w, h, ww);
	ippiConvert_16s32f_C1R(fxi, ww<<1, fx, ww<<2, imgSize);
	ippiConvert_16s32f_C1R(fyi, ww<<1, fy, ww<<2, imgSize);
	ippiMulC_32f_C1IR(0.125f, fx, ww<<2, imgSize);
	ippiMulC_32f_C1IR(0.125f, fy, ww<<2, imgSize);
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void C_PlessyCornerDetector_16s::CountPlessy(int w, int h, int ww)
{
	IppiSize imgSize={w, h};
	IppiSize imgSize1={w-2, h-2};
	IppiSize maskSize={3, 3};
	IppiPoint pnt;
	pnt.x=1;
	pnt.y=1;

	int Maski[9]={1, 1, 1, 
							  1, 1, 1,
							  1, 1, 1};

	ippiRShiftC_16s_C1IR(3, fxi, ww<<1, imgSize);
	ippiRShiftC_16s_C1IR(3, fyi, ww<<1, imgSize);

	ippiSqr_16s_C1RSfs(fxi, ww<<1, sxxi, ww<<1, imgSize, 0);
	ippiMul_16s_C1RSfs(fxi, ww<<1, fyi, ww<<1, sxyi, ww<<1, imgSize, 0);
	ippiSqr_16s_C1RSfs(fyi, ww<<1, syyi, ww<<1, imgSize, 0);

	ippiRShiftC_16s_C1IR(2, sxxi, ww<<1, imgSize);
	ippiRShiftC_16s_C1IR(2, sxyi, ww<<1, imgSize);
	ippiRShiftC_16s_C1IR(2, syyi, ww<<1, imgSize);

	ippiFilter_16s_C1R(sxxi+w+1, ww<<1, Sxxi+w+1, ww<<1, imgSize1, Maski, maskSize, pnt, 1);
	ippiFilter_16s_C1R(sxyi+w+1, ww<<1, Sxyi+w+1, ww<<1, imgSize1, Maski, maskSize, pnt, 1);
	ippiFilter_16s_C1R(syyi+w+1, ww<<1, Syyi+w+1, ww<<1, imgSize1, Maski, maskSize, pnt, 1);

	ippiCopy_16s_C1R(Sxxi, ww<<1, Sxxit, w<<1, imgSize);
	ippiCopy_16s_C1R(Syyi, ww<<1, Syyit, w<<1, imgSize);
	ippiAddC_16s_C1IRSfs(1, Sxxit, ww<<1, imgSize, 0);//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	ippiAddC_16s_C1IRSfs(1, Syyit, ww<<1, imgSize, 0);//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	ippiRShiftC_16s_C1IR(1, Sxxit, ww<<1, imgSize);
	ippiRShiftC_16s_C1IR(1, Syyit, ww<<1, imgSize);

	ippiAdd_16s_C1RSfs(Sxxit, ww<<1, Syyit, ww<<1, SumSxxSyyi, ww<<1, imgSize, 0);

	ippiAddC_16s_C1IRSfs(64, Sxxi, ww<<1, imgSize, 0);//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	ippiAddC_16s_C1IRSfs(64, Sxyi, ww<<1, imgSize, 0);//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	ippiAddC_16s_C1IRSfs(64, Syyi, ww<<1, imgSize, 0);//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	ippiRShiftC_16s_C1IR(7, Sxxi, ww<<1, imgSize);
	ippiRShiftC_16s_C1IR(7, Sxyi, ww<<1, imgSize);
	ippiRShiftC_16s_C1IR(7, Syyi, ww<<1, imgSize);

	ippiMul_16s_C1RSfs(Sxxi, ww<<1, Syyi, ww<<1, MulSxxSyyi, ww<<1, imgSize, 0);
	ippiSqr_16s_C1RSfs(Sxyi, ww<<1, MulSxySxyi, ww<<1, imgSize, 0);
	ippiSub_16s_C1RSfs(MulSxySxyi, ww<<1, MulSxxSyyi, ww<<1, Subxyi, ww<<1, imgSize, 0);
	ippiThreshold_LT_16s_C1IR(Subxyi, ww<<1, imgSize, 0);
//	ippiDiv_16s_C1RSfs(Subxyi, ww<<1, SumSxxSyyi, ww<<1, CPi, ww<<1, imgSize, 0);
	ippiMulC_16s_C1RSfs(Subxyi, w<<1, threshold, cSubxyi, w<<1, imgSize, 0); 
	ippiCompare_16s_C1R(SumSxxSyyi, ww<<1, cSubxyi, ww<<1, cres, ww, imgSize, ippCmpLess);

	ippiConvert_16s32f_C1R(SumSxxSyyi, ww<<1, SumSxxSyy, ww<<2, imgSize);
	ippiConvert_16s32f_C1R(Subxyi, ww<<1, Subxy, ww<<2, imgSize);

}
void C_PlessyCornerDetector_32f::CountPlessy(int w, int h, int ww)
{
	IppiSize imgSize={w, h};
	IppiSize imgSize1={w-2, h-2};
	IppiSize maskSize={3, 3};
	IppiPoint pnt;
	pnt.x=1;
	pnt.y=1;


	float Mask[9]={1, 1, 1, 
			 					 1, 1, 1,
						     1, 1, 1};
	ippiSqr_32f_C1R(fx, ww<<2, sxx, ww<<2, imgSize);
	ippiMul_32f_C1R(fx, ww<<2, fy, ww<<2, sxy, ww<<2, imgSize);
	ippiSqr_32f_C1R(fy, ww<<2, syy, ww<<2, imgSize);
 
	ippiFilter_32f_C1R(sxx+w+1, ww<<2, Sxx+w+1, ww<<2, imgSize1, Mask, maskSize, pnt);
	ippiFilter_32f_C1R(sxy+w+1, ww<<2, Sxy+w+1, ww<<2, imgSize1, Mask, maskSize, pnt);
	ippiFilter_32f_C1R(syy+w+1, ww<<2, Syy+w+1, ww<<2, imgSize1, Mask, maskSize, pnt);

	ippiAdd_32f_C1R(Sxx, ww<<2, Syy, ww<<2, SumSxxSyy, ww<<2, imgSize);
	ippiMul_32f_C1R(Sxx, ww<<2, Syy, ww<<2, MulSxxSyy, ww<<2, imgSize);
	ippiMul_32f_C1R(Sxy, ww<<2, Sxy, ww<<2, MulSxySxy, ww<<2, imgSize);
	ippiSub_32f_C1R(MulSxySxy, ww<<2, MulSxxSyy, ww<<2, Subxy, ww<<2, imgSize);

//	ippiDiv_32f_C1R(Subxy, ww<<2, SumSxxSyy, ww<<2, CP, ww<<2, imgSize);
//	ippiMulC_32f_C1IR(64, CP, ww<<2, imgSize);//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	ippiMulC_32f_C1R(Subxy, w<<2, threshold, cSubxy, w<<2, imgSize); 
	ippiCompare_32f_C1R(SumSxxSyy, ww<<2, cSubxy, ww<<2, cres, ww, imgSize, ippCmpLess);

}

void C_PlessyCornerDetector::FindCorners(unsigned char *Picture, int w, int h, int ww, 
																	 float *px, float *py, int& nc)
{
	CountDer(Picture, w, h, ww);
	CountPlessy(w, h, ww);

	nc=0;
	int i, j;
	IppiSize imgSize={w, h};
	IppiSize maskSize={3, 3};
	float vmin, vmax;
	int ymin, xmin;
	Ipp8u mask[3*3];
	ippiSet_8u_C1R(1, mask, 3, maskSize);
	float Sum9[9], Sub9[9];

	for(j=3; j<h-3; j++)
	{
		for(i=3; i<w-3; i++)
			if(cres[w*j+i])
			{
				ippiCopy_32f_C1MR(&Subxy[w*(j-1)+i-1], ww<<2, Sub9, 3<<2, maskSize, mask, 3);
				ippiCopy_32f_C1MR(&SumSxxSyy[w*(j-1)+i-1], ww<<2, Sum9, 3<<2, maskSize, mask, 3);
				ippiDiv_32f_C1R(Sub9, 3<<2, Sum9, 3<<2, S9, 3<<2, maskSize);
				ippiMinIndx_32f_C1R(S9, 3<<2, maskSize, &vmin, &xmin, &ymin);
				ippiMax_32f_C1R(S9, 3<<2, maskSize, &vmax);

				int cnum=0;
				ippiCountInRange_32f_C1R(S9, 3<<2, maskSize, &cnum, vmin, vmin);


				if(xmin==1 && ymin==1 && vmax<IPP_MAXABS_32F && vmin>=0 && cnum==1)
				{
					float dx5, dy5;
					px[nc]=(float)i;
					py[nc]=(float)j;

					int ncc=nc;
					SubPixelMinPosition->Find(S9, dx5, dy5);
					px[nc]+=dx5;
					py[nc]+=dy5;
					nc++;
				}
			}
	}
}




#endif