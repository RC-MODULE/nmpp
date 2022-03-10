/******************************************************************************
*    RC Module
*    NeuroMatrix(r) NM6403 Software
*
*    Image Processing Library 
*    (C-callable functions)
*
*    File:               FFill.c 
*    Contents:           FloodFill routines
*    Software design:    Alex Ruzavin
*    
*    Start date:         1aug99
*    Release date:		 3aug99	
*
*
******************************************************************************/

#include "nmpli.h"

/*
Finds spots on the input band and returns the number of spots,
the number of points in every spot and coordinates of the spots.
The pixel size in the input bad is 32 bits.Stack size must be 
2*maxSpotWidth*maxSpotHeight.


Input parameters :
	Frame - input image
	aTetr - array of struct with ( xmin, ymin ) and ( xmax, ymax ) 
	Stack - stack
	w     - image width (pixels)
	h     - image height

Return:
	the number of spots in the picture  

*/

#include "nmpli/iFloodFill.h"
int nmppiFloodFill( unsigned int * Frame, /* input frame */
               SegmentInfo * aTetr,      /* array of struct with ( xmin, ymin ) and ( xmax, ymax ) */
               unsigned int * Image,    /* output picture */
               int w,                   /* input frame width ( in 32 bit words ) */
               int h,                   /* input frame height */
               unsigned int * Stack     /* working buff */
                              )
{
    int i, x, y, x1, y1;
    int nTetr, N;
    unsigned int * Current, * StackBase;
    int xMin, xMax, yMin, yMax;

    nTetr = 0;
    StackBase = Stack;
    Current = Frame;

    for( y = 0; y < h; y++ )
        for( x = 0; x < w; x++ )
        {
            if( * Current != 0 )
            {
                * Stack = y;
                Stack++;
                * Stack = x;
                Stack++;
                xMin = w;
                xMax = 0;
                yMin = h;
                yMax = 0;
				N=0;
                * Current = 0;

                while( Stack != StackBase )
                {
                    Stack--;
                    x1 = * Stack;
                    Stack--;
                    y1 = * Stack;
                    N++;
                    if( x1 < xMin ) xMin = x1;
                    if( x1 > xMax ) xMax = x1;
                    if( y1 < yMin ) yMin = y1;
                    if( y1 > yMax ) yMax = y1;
                    i = w * y1 + x1;
                    Image[i] = nTetr + 1;

                    if( x1 > 0 && Frame[( i - 1 )] != 0 )
                    {
                        * Stack = y1;
                        Stack++;
                        * Stack = x1 - 1;
                        Stack++;
                        Frame[( i - 1 )] = 0;
                    }
                    if( x1 < ( w - 1 ) && Frame[( i + 1 )] != 0 )
                    {
                        * Stack =  y1;
                        Stack++;
                        * Stack = x1 + 1;
                        Stack++;
                        Frame[( i + 1 )] = 0;
                    }
                    if( y1 > 0 && Frame[( i - w )] != 0 )
                    {
                        * Stack = y1 - 1;
                        Stack++;
                        * Stack = x1;
                        Stack++;
                        Frame[( i - w )] = 0;
                    }
                    if( y1 < ( h - 1 ) && Frame[( i + w )] != 0 )
                    {
                        * Stack = y1 + 1;
                        Stack++;
                        * Stack = x1;
                        Stack++;
                        Frame[( i + w )] = 0;
                    }
//////////////////////DIAGONAL/////////////////////////////////////////////////////////////////
                    if( x1 > 0 && y1 > 0 && Frame[( i - w - 1 )] != 0 )
                    {
                        * Stack = y1 - 1;
                        Stack++;
                        * Stack = x1 - 1;
                        Stack++;
                        Frame[( i - w - 1 )] = 0;
                    }
                    if( x1 > 0 && y1 < ( h - 1 ) && Frame[( i + w - 1 )] != 0 )
                    {
                        * Stack = y1 + 1;
                        Stack++;
                        * Stack = x1 - 1;
                        Stack++;
                        Frame[( i + w - 1 )] = 0;
                    }
                    if( x1 < ( w - 1 ) && y1 > 0 && Frame[( i - w + 1 )] != 0 )
                    {
                        * Stack = y1 - 1;
                        Stack++;
                        * Stack = x1 + 1;
                        Stack++;
                        Frame[( i - w + 1 )] = 0;
                    }
                    if( x1 < ( w - 1 ) && y1 < ( h - 1 ) && Frame[( i + w + 1 )] != 0 )
                    {
                        * Stack = y1 + 1;
                        Stack++;
                        * Stack = x1 + 1;
                        Stack++;
                        Frame[( i + w + 1 )] = 0;
                    }
//////////////////////DIAGONAL/////////////////////////////////////////////////////////////////
                }
                aTetr[nTetr].xMin = xMin;
                aTetr[nTetr].xMax = xMax;
                aTetr[nTetr].yMin = yMin;
                aTetr[nTetr].yMax = yMax;
                aTetr[nTetr].N = N;
                nTetr++;
            }
			Current++;
        }
    return nTetr;
}





