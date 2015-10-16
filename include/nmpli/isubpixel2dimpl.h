#ifndef __SUBPIXEL2DIMPL_H
#define __SUBPIXEL2DIMPL_H

#include "isubpixel2d.h"


class C_2DSubPixelMinPosition : public I_2DSubPixelMinPosition
{
protected:

public:
	C_2DSubPixelMinPosition(){};
	~C_2DSubPixelMinPosition(){};
	virtual void Find(float *S9, float& dx, float& dy);
	virtual void Release();
};



class C_2DTrigSubPixelMinPosition  : public I_2DSubPixelMinPosition
{
protected:
	float Teta[8];
	float S9Interpolation(float x, float y, float *S9);

public:
	C_2DTrigSubPixelMinPosition();
	~C_2DTrigSubPixelMinPosition(){};
	virtual void Find(float *S9, float& dx, float& dy);
	virtual void Release();
};


#endif