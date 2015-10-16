#ifndef __PLESSYDETECTOR_H
#define __PLESSYDETECTOR_H

#include "iplessy.h"
#include "isubpixel2dimpl.h"


class C_PlessyCornerDetector : public I_PlessyCornerDetector
{
protected:
	I_2DSubPixelMinPosition *SubPixelMinPosition;
	short *fxi, *fyi;
	short *Picture16;
	float *SumSxxSyy, *Subxy;
	float S9[9];
	float threshold;
	unsigned char *cres;

	virtual void CountDer(unsigned char *Picture, int w, int h, int ww);
	virtual void CountPlessy(int w, int h, int ww) {};
public:

	C_PlessyCornerDetector();
	~C_PlessyCornerDetector();
	virtual void Allocate(int w, int h, int ww);
	virtual void DeAllocate();
	virtual void FindCorners(unsigned char *Picture, int w, int h, int ww, float *px, float *py, int& nc);
	virtual void Release();
	virtual void SetThreshold(float _threshold)=0;
};



class C_PlessyCornerDetector_32f : public C_PlessyCornerDetector
{
protected:
	float *fx, *fy;
	float *sxx, *sxy, *syy;
	float *Sxx, *Sxy, *Syy;
	float *MulSxxSyy, *MulSxySxy;
	float *cSubxy;
	float threshold;

	virtual void CountPlessy(int w, int h, int ww);
	virtual void CountDer(unsigned char *Picture, int w, int h, int ww);
public:
	C_PlessyCornerDetector_32f(){};
	~C_PlessyCornerDetector_32f(){};
	virtual void Allocate(int w, int h, int ww);
	virtual void DeAllocate();
	virtual void SetThreshold(float _threshold);
};



class C_PlessyCornerDetector_16s : public C_PlessyCornerDetector
{
protected:
	short *sxxi, *sxyi, *syyi;
	short *Sxxi, *Sxyi, *Syyi;
	short *Sxxit, *Syyit;
	short *SumSxxSyyi, *MulSxxSyyi, *MulSxySxyi, *Subxyi;
	short *cSubxyi;
	short threshold;

	virtual void CountPlessy(int w, int h, int ww);

public:
	C_PlessyCornerDetector_16s(){};
	~C_PlessyCornerDetector_16s(){};
	virtual void Allocate(int w, int h, int ww);
	virtual void DeAllocate();
	virtual void SetThreshold(float _threshold);
};

#endif
