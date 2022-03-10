#ifdef USE_IPP

#include "stdafx.h"
#include "isubpixel2dimpl.h"
#include <math.h>
#include "ipp.h"

///////////////////////////////////////////////////////////////////////////////////////////////////

I_2DSubPixelMinPosition* Create2DSubPixelMinPosition(SPP_TYPE type)
{
	if (type == SPP_par)
		return (I_2DSubPixelMinPosition*) new C_2DSubPixelMinPosition();
	else
		if (type == SPP_trg)
			return (I_2DSubPixelMinPosition*) new C_2DTrigSubPixelMinPosition();
		else return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void C_2DSubPixelMinPosition::Find(float *S9, float& dx, float& dy)
{
	float sums, coeff;

	sums=S9[0]+S9[1]+S9[2]+S9[3]+S9[4]+S9[5]+S9[6]+S9[7]+S9[8];

	coeff=-sums;
//	coeff+=S9[4]+S9[4];
	coeff+=S9[4]+S9[4]+S9[4]+S9[4];
	sums+=coeff+coeff+coeff;

	dx=S9[2]+S9[5]+S9[8]-S9[0]-S9[3]-S9[6];
	dy=S9[6]+S9[7]+S9[8]-S9[0]-S9[1]-S9[2];

	dx/=sums;
	dy/=sums;
}

void C_2DSubPixelMinPosition::Release()
{
	delete this;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

C_2DTrigSubPixelMinPosition::C_2DTrigSubPixelMinPosition()
{
	float pi=3.141592653589f;
	for(int n=0; n<8; n++)
		Teta[n]=n*pi*0.125f;
}

void C_2DTrigSubPixelMinPosition::Release()
{
	delete this;
}

float C_2DTrigSubPixelMinPosition::S9Interpolation(float x, float y, float *S9)
{
	float res=0;
	int Cx=(int)ceil(x);
	int Cy=(int)ceil(y);
	int Fx=(int)floor(x);
	int Fy=(int)floor(y);

	if(x!=Cx && y!=Cy)
		res=(Cx-x)*(Cy-y)*S9[3*Fy+Fx]+
				(Cx-x)*(y-Fy)*S9[3*Cy+Fx]+
				(x-Fx)*(Cy-y)*S9[3*Fy+Cx]+
				(x-Fx)*(y-Fy)*S9[3*Cy+Cx];
	else if(x==Cx && y!=Cy)
		res=(Cy-y)*S9[3*Fy+Fx]+
				(y-Fy)*S9[3*Cy+Fx];
	else if(x!=Cx && y==Cy)
		res=(Cx-x)*S9[3*Fy+Fx]+
				(x-Fx)*S9[3*Cy+Cx];
	else
		res=S9[3*Cy+Cx];

	return res;
}

void C_2DTrigSubPixelMinPosition::Find(float *S9, float& dx, float& dy)
{
	int n;
	float pi=3.141592653589f;
//	pi=IPP_PI;
	float teta;
	float Fteta[8];
	float x, y;
	float xp, yp, xm, ym, CPp, CPm;
	float a, b, c, t;

//	ippsSet(Fteta, 0, 8*sizeof(float));
	ippsSet_32f(0, Fteta, 8*sizeof(float));

	for(n=0; n<8; n++)
	{
		teta=Teta[n];
		float ct=(float)cos(teta);
		float st=(float)sin(teta);
		float ms=(fabs(ct)>fabs(st))?(float)fabs(ct):(float)fabs(st);
		xp=ct/ms;
		yp=st/ms;
		xm=-xp;
		ym=-yp;
		CPp=S9Interpolation(xp+1, yp+1, S9);
		CPm=S9Interpolation(xm+1, ym+1, S9);

		a=0.5f*(CPp+CPm)-S9[4];
		b=0.5f*(CPp-CPm);
		c=S9[4];
		t=-b/(a+a);
		Fteta[n]=a*t*t+b*t+c;
	}

	float vmin=IPP_MAXABS_32F;
	int nmin=-1, nmint;
	IppiSize maskSize={8, 1};
	ippiMinIndx_32f_C1R(Fteta, 8<<2, maskSize, &vmin, &nmin, &nmint);

	a=(Fteta[(nmin+1)%8]+Fteta[(nmin-1+8)%8])*0.5f-Fteta[nmin];
	b=(Fteta[(nmin+1)%8]-Fteta[(nmin-1+8)%8])*0.5f;
	c=Fteta[nmin];
	t=-b/(a+a);
	teta=(t+nmin)*pi*0.125f;


	float ct=(float)cos(teta);
	float st=(float)sin(teta);
	float ms=(fabs(ct)>fabs(st))?(float)fabs(ct):(float)fabs(st);
	xp=(float)ct/ms;
	yp=(float)st/ms;
	xm=-xp;
	ym=-yp;
	CPp=S9Interpolation(xp+1, yp+1, S9);
	CPm=S9Interpolation(xm+1, ym+1, S9);

	a=0.5f*(CPp+CPm)-S9[4];
	b=0.5f*(CPp-CPm);
	c=S9[4];
	t=-b/(a+a);

	x=xp*t;
	y=yp*t;

	dx=x;
	dy=y;

}

#endif