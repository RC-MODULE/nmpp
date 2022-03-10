//#define NHEIGHT	1080
const NHEIGHT = 1080;

//////////////////////////////////////////////////////////////////////////////////
//										//
//  int FloodFill8(void* src, void *dst, int nWidth, int nHeight, spot_struct *spot, lenSpot, unsigned *pixels,
//		   int mSpot, int dtFull, int dtSpot, int lDiag, int lDropSpot, //
//                 ds_struct *dropSpot, int nPxlMin, int nPxlMax, int dXYmin, int dXYmax);
//										//
//	// 0<nWidth (nWidth & 3)=0 0<nHeight<=1080				//
//	// dst should be null							//
//	// dropSpot should be null						//
//	// size of pixels should be (nHeight-2)*(nWidth-2) of unsigned int	//
//	// size of spot should be						//
//	// 	8 * ( (nHeight-2)*(nWidth-2)/2 + nSpotFict )  of int		//
// 	//	nSpotFict = 1 + [((nHeight-2)*(nWidth-2)/2-1)/255] (???)	//
//		– количество фиктивных пятен					//
//										//
//	return value:	nSpot - number of spots (>0)				//
//			or nError - error-code (<0)				//
//										//
//typedef struct spot_struct{							//
//	int xMin, yMin, xMax, yMax;  // коородинаты минимального прямоугольника, содержащего пятно
//	int noPxl;  // номер начального пиксела следующего пятна в массиве  pixels
//	int dtSpot;     // время обработки пятна (в тактах процессора)		//
//	} spot_struct;								//
//										//
//										//
//typedef struct ds_struct{							//
//	int nnSpot;								//
//	int nnPxl;								//
//	int dttSpot;								//
//	} ds_struct;								//
//										//
//	dropSpot[4*3]	       +0    +1       +2				//
//	  0 - spotPmin:  [ nnSpot, nnPxl, ttSpot]				//
//	  3 - spotPmax:  [ nnSpot, nnPxl, ttSpot]				//
//	  6 - spotDmin:  [ nnSpot, nnPxl, ttSpot]				//
//	  9 - spotDmax:  [ nnSpot, nnPxl, ttSpot]				//
//										//
//typedef struct pixels{							//
//	unsigned ij;  // ([31..16] - i, [15..0]) - j				//
//	} pixels;								//
//										//
//////////////////////////////////////////////////////////////////////////////////

global _FloodFill8:	label;
extern _clock:		label;

local floodFill:	label;
local endFIFO:		label;
local calcP1f:		label;
local emergeExit:	label;

data ".data"
  jjFF:		word[4]=(0000000ffh, 00000ff00h, 000ff0000h, 0ff000000h);
  jjColor:	word[4]=(000000001h, 000000100h, 000010000h, 001000000h);
end ".data";

//nobits ".dataParam"
data ".dataParam"
  src, dst, nH, nW, spot, lenSpot, pixels,
  dtFull, dtSpot, mSpot, lDiag, lDropSpot,
  dropSpot, nPxlMin, nPxlMax, dXYmin, dXYmax: word = -1;

  dXYmin1, dXYmax1, aNspotPmin, aNspotPmax, aNspotDmin, aNspotDmax: word = -1;
  lenSpot1, spot1, nSpot, calcDiag: word = -1;
  dI, dIW32, nPxl, noPxl, nW1, nH1, nW32, nW32neg, n2W32, n2W32neg: word = -1;

  i, j, jFF, jPxl, T0, tSpot0: word = -1;
  src_iw32, dst_iw32, srcIJ: word = -1;
  iw32: word[NHEIGHT] = (0 dup NHEIGHT);

end ".dataParam";

import from macros;
import from rtmacro;

begin ".text"

//--------------------------------------------------------------
////////////////////////////////////////////////////////////////
//--------------------------------------------------------------
<_FloodFill8>

.branch;
ar5=sp-2;
PUSH_REGS();

// Засечь начальное время
////////////////////////////////////////////////
        call _clock;                        //
        [T0]=gr7;                          //
////////////////////////////////////////////////


// Считать входные параметры
//  int FloodFill8(void* src, void *dst, int nWidth, int nHeight, spot_struct *spot, unsigned *pixels,
//
ar0 = [--ar5];  // src
[src] = ar0;

ar4 = [--ar5];  // dst
[dst] = ar4;

gr2=[--ar5];  // nWidth
[nW]=gr2	with gr1=gr2-1;
[nW1]=gr1	with gr2>>=2;
[nW32]=gr2	with gr3=-gr2;
[nW32neg]=gr3	with gr2<<=1;
[n2W32]=gr2	with gr3=-gr2;
[n2W32neg]=gr3;

gr3=[--ar5];  //nHeight
[nH] = gr3	with gr3--;
[nH1] = gr3;

ar1 = [--ar5];  //spot
[spot]=ar1;

gr7 = [--ar5];  //lenSpot
[lenSpot]=gr7;

ar2=[--ar5];  // pixels
[pixels]=ar2;


//		   int mSpot, int dtFull, int dtSpot, int lDiag, int lDropSpot,
gr7=[--ar5];  //mSpot
[mSpot]=gr7;

gr7=[--ar5];  //dtFull
[dtFull]=gr7;

 gr7=[--ar5];  //dtSpot
[dtSpot]=gr7;

gr7=[--ar5];  //lDiag
[lDiag] = gr7;

gr7=[--ar5];  //lDropSpot
[lDropSpot] = gr7;


//                 ds_struct *dropSpot, int nPxlMin, int nPxlMax, int dXYmin, int dXYmax);
gr7=[--ar5];  //dropSpot
[dropSpot]=gr7;

gr7=[--ar5];  //nPxlMin
[nPxlMin] = gr7;

gr7=[--ar5];  //nPxlMax
[nPxlMax] = gr7;

gr7=[--ar5];  //dXYmin
[dXYmin] = gr7	with gr7--;
[dXYmin1] = gr7;

gr7=[--ar5];  //dXYmax
[dXYmax] = gr7	with gr7--;
[dXYmax1] = gr7;


//------------------------------------------------------------------
// dI = max(1,dXYmin)
//
gr1 = [dXYmin]		with gr7=false;
			with gr1;
if <>0 goto ready_dI	with gr7++;  // gr7 = dI = 1

  gr1 = gr7;  // gr1 = dI = dXYmin

<ready_dI>  // gr1 = dI

//  dIW32 := dI * nW32
[dI] = gr1;
gr2= [nW32];
MULT32(gr0,gr1,gr2);
[dIW32]  = gr0;


//------------------------------------------------------------------
////  confirm correct in-data
//if ( (nHeight <=0 ) || (nHeight < dI+2) || (1040 < nHeight) )  return -1;
//if ( (nWidth  <= 0) || (nWidth  < dI+2) || ((nWidth & 3)!=0) ) return -2;
//
//if ( (dtSpot < 0)  || ((dtFull != 0) && (dtFull < dtSpot)) )	 return -3;
//
//if ( (nPxlMin < 0)  || (nPxlMax < nPxlMin) )	return -4;
//if ( (dXYmin  < 0)  || (dXYmax  < dXYmin) )	return -5;
//
//if (mSpot < 0)				return -6;


ar4 = emergeExit	with gr7 = true;  // gr7 = -1

//if ( (nHeight<=0) || (nHeight < dI+2) || (1080<nHeight) ) return -1;
//if ( (nHeight<=0) || (nHeight < dI+2) || (NHEIGHT<nHeight) ) return -1;
gr6=[nH]		with gr1++;
//gr5=1080		with gr6;
gr5=NHEIGHT		with gr6;
if <= goto ar4		with gr5-gr6;	// nH <= 0


if < goto ar4		with gr1++;	// 1080 < nH  gr1=dI+2


			with gr6-gr1;
if < goto ar4		with gr3=gr7>>30;  // nH < dI+2  gr3=3


//if ( (nWidth<=0) || (nWidth < dI+2) || ((nWidth & 3)!=0) ) return -2;
gr6=[nW]		with gr7--;	// gr7 = -2
			with gr6;
if <= goto ar4		with gr6-gr1;	// nW <= 0


if < goto ar4		with gr6 and gr3;// nW < dI+2


if <>0 goto ar4;			// (nW & 3) != 0


//if ( (dtSpot < 0)  || ((dtFull != 0) && (dtFull < dtSpot)) )	 return -3;
gr6=[dtSpot]		with gr7--;	// gr7 = -3
gr5=[dtFull]		with gr6;
if < goto ar4		with gr5;	// dtSpot<0  gr7 = -3

if =0 goto confirmPxl;  // dtFull=0

			with gr5 - gr6;  // dtFull - dtSpot
if < goto ar4;	// gr7 = -3

<confirmPxl>
//if ((nPxlMin < 0) || (nPxlMax < nPxlMin))	return -4;
gr6=[nPxlMin];
gr5=[nPxlMax];
			with gr5-=gr6;
			with gr5 or gr6;
if < goto ar4		with gr7--;  // gr7 = -4


//if ((dXYmin < 0)  || (dXYmax < dXYmin) )	return -5;
gr6=[dXYmin];
gr5=[dXYmax];
			with gr5-=gr6;
			with gr5 or gr6;
if < goto ar4		with gr7--;  // gr7 = -5


//if (mSpot < 0)				return -6;
gr6=[mSpot];
			with gr6;
if < goto ar4		with gr7--;  // gr7 = -6;


//if (lenSpot < 6)		lenSpot:=6;
gr6=6;
gr5=[lenSpot];
			with gr5-gr6;
if >= goto leSpotReady;

  gr5 = gr6;


<leSpotReady>
[lenSpot]=gr5	with gr6=gr5-gr6;
		with gr6++;  // gr6 = lenSpot1=lenSpot-6 + 1
[lenSpot1]=gr6;

//////////////////////////////////////////////////////
//  init parameters
//
// null the spot[0]  spot1:=spot0+8  spot[0].dtRest:=dtFull  noPxl:=0  nSpot:=1
ar1=[spot];
ar2=ar1;
rep 3			with vfalse;
rep 3 [ar2++] = afifo;
gr1=[lenSpot];
gr7=[dtFull];
[ar1++gr1]=gr7;
[spot1]=ar1		with gr7=false;
[noPxl]=gr7		with gr7++;
[nSpot] = gr7;


// if (lDropSpot!=0) 	???null the dropSpot
gr7=[lDropSpot]		with gr4=true;
gr7=[dropSpot]		with gr7;

if =0 goto evalDiag	with gr4>>=30;  //gr4=3

//    ar1=gr7;
//    rep 6		with vfalse;
//    rep 6 [ar1++] = afifo;

    // form addresses for dropSpot[Pmin, Pmax, Dmin, Dmax]
    [aNspotPmin]=gr7	with gr7+=gr4;
    [aNspotPmax]=gr7	with gr7+=gr4;
    [aNspotDmin]=gr7	with gr7+=gr4;
    [aNspotDmax]=gr7;

//----------------------------------------------------
//  calcDiag=calcP11, lDiag=1
//	    =endFIFO, lDiag=0
<evalDiag>
gr7 = [lDiag];
gr6 = endFIFO		with gr7;
if =0 goto l_calcDiag;

  gr6 = calcP1f with gr7;

<l_calcDiag>
[calcDiag]=gr6;


//  for (i=0; i+=dI; i<nH;)
//    {
//    dst_iw32[i] = dst + nW32
//    }
gr7=[nH];
gr0=[nW32];
ar4=iw32		with gr4=false;
//--------------------------------------
<begSrcDstI>
[ar4++]=gr4		with gr4 += gr0;
			with gr7--;
if > goto begSrcDstI;


//  null the one-pixel-boarder of src frame
//  ar0=srcI gr0=nW32 gr1=0xffffff00  ar4=srcI+nW32-1 gr4=nW32 gr5=0x00ffffff  gr7=nH-2
ar0=[src]		with gr1=true;
gr0=[nW32]		with gr1 <<= 8;
ar0=ar0+gr0		with gr5=gr1 >> 8;
ar3=ar0+gr0;
gr7=[nH1]		with gr3=gr0;
ar3--			with gr7--;

<nullVBoarder>
gr2=[ar0];  // left border
			with gr2=gr2 and gr1;
[ar0++gr0]=gr2;

gr2=[ar3];  // right border
			with gr2=gr2 and gr5;
[ar3++gr3]=gr2		with gr7--;
if > goto nullVBoarder;

//  ar0=src[0] ar4=src[nH-1]
ar4=ar0;
ar0=[src];
gr7=[nW32]		with gr0=false;

<nullHBoarder>
[ar0++]=gr0;
[ar4++]=gr0		with gr7--;
if > goto nullHBoarder;


////////////////////////////////////////////////////////////////////
//  -- main calculations -------------------------------------------
//  ar2=pixels0  ar6=pixels1  ar0=srcIJ  ar3=srcIW32  ar5=jjFF
//  gr1=i[1..nH-2]  gr5=j[1..nW-2]  gr2=jFF  gr4=jPxl
//  for (i=dI; i+=dI; i<nH-1)

ar3=[src];
gr3=[dIW32];
ar3+=gr3;
[src_iw32]=ar3;
gr1=[dI];  // gr1 = i = dI
//ar5=jjFF;


//----------------------------------------------------------------
//----------------------------------------------------------------
<begLoopI>
gr2=0000ff00h	with gr5=false;
ar0=ar3		with gr5++;	// gr5=j=1
		with gr4=gr5;	// gr4=jPxl=1


//----------------------------------------------------------------
<begLoopJ>	// ar0=src_iw32  gr2=jFF  gr4=jPxl  gr6=(jPixel=00)
gr6=[ar0]	with gr3=true;
		with gr6 and gr2;
if =0 delayed goto nextJ	with gr6 = gr6 and not gr2;
  [ar0]=gr6	with gr3 = gr3>>30;	//gr3=3
  nul;

// pixel(i,j) != 0 - begin new spot
////////////////////////////////////////////////////
        call _clock;				//
        [tSpot0]=gr7;				//
////////////////////////////////////////////////////

ar2=[pixels];
ar6=ar2;
[i]=gr1		with gr7 = gr1<<16;
[j]=gr5		with gr7 = gr7 or gr5;
[ar6++]=gr7;  // pixels1++ =+ (i,j)

[jPxl]  = gr4;
[srcIJ] = ar0;
[jFF]   = gr2;

ar5=jjFF;

//----------------------------------------------------------------
<whileFIFO>		// gr3=3    (i,j) -> ar0..gr7(i,j-1)
gr7=[ar2++];		// gr7=(i,j) pixels0++
gr5=0000ffffh	with gr7--;		//  gr7=(i,j-1) !!! (j-1) OK for j = 1..nW-1
ar1=iw32	with gr1 = gr7>>16;	// ar1=iw32 gr1=i
gr1=[ar1+=gr1]	with gr5 = gr7 and gr5;	// gr1=iw32[i]  gr5=(j-1)
ar0=[src]	with gr0 = gr5>>2;	// ar0=src  gr0=(j-1)Pixel
ar4=ar5		with gr4 = gr5 and gr3;	// ar4=(jjFF)   gr4=(j-1)Pxl
gr2=[ar4+=gr4]	with gr0 += gr1;	// gr2=(j-1)FF  gr0=iw32[i]+(j-1)Pixel


//<calcP0f>  // ar0=srcIW32(i,0)->(i,J-1)->(i-1,J)  gr0=J-1  gr1=i  gr2=(j-1)FF  gr3=3  gr4=(j-1)Pxl  gr7=(i,j-1)
gr6=[ar0+=gr0]	with gr4++;  // ar0=srcIW32(i,J-1)  gr6=pxl4[i,J-1]  gr4=jPxl
		with gr6 and gr2;  // gr0=-W32  ar0=srcIW32(i-1,J-1)
gr0=[nW32neg]	with gr6 = gr6 and not gr2 noflags;  // gr6=pxl4[i,J-1]=(j-1)0

if =0 delayed goto calcPf0	with gr2 R<<= 8;
  [ar0++gr0]=gr6	with gr0 = gr4 >> 2;	//  gr2=jFF
  ar0+=gr0		with gr4 = gr4 and gr3;	// ar0=srcIW32(i-1,J) gr4=jPxl

[ar6++]=gr7;	// pixels1 =+ (i,j-1)


<calcPf0>  // gr7=(i,j-1) -> (i-1,j)    ar0=srcIW32(i-1,J) -> (i,J+1)  gr4=jPxl
gr6=[ar0]	with gr4++;  //ar0=src(i-1)J gr6=pxl4[i-1,J] gr4=(j+1)Pxl
gr5=0ffff0001h	with gr6 and gr2;  // gr5=(-1, +1)
		with gr7 += gr5 noflags;  // ar0=srcIW32(i,J+1) gr7=(i-1,j)
gr0=[nW32]	with gr6 = gr6 and not gr2 noflags;  // gr0=nW32  gr6=pxl4[i-1,J]=j0

if =0 delayed goto calcP01	with gr2 R<<= 8;
  [ar0++gr0]=gr6	with gr0=gr4 >> 2;  // ar0=srcIW32(i,J)
  ar0+=gr0		with gr4 = gr4 and gr3;	// gr4=(j+1)Pxl

[ar6++]=gr7;	// pixels1 =+ (i-1,j)


<calcP01>  // gr7=(i-1,j) -> (i,j+1)  ar0..(i,j+1) -> (i+1,j)
gr6=[ar0]	with gr4--;
gr5=00010001h	with gr6 and gr2;  // gr5=(1, 1)
		with gr7 += gr5 noflags;  // gr7=(i,j+1)
gr0=[nW32]	with gr6 = gr6 and not gr2 noflags;  //gr6=(jPxl=0)

if =0 delayed goto calcP10	with gr2 R>>= 8;
  [ar0++gr0]=gr6	with gr0 = gr4 A>> 2;
  ar0+=gr0		with gr4 = gr4 and gr3;

[ar6++]=gr7;	// pixels1 =+ (i,j+1)


<calcP10>  // gr7=(i,j+1) -> (i+1,j)  ar0..(i+1,j) -> (i+1,j-1)
ar1=[calcDiag]	with gr4--;
gr6=[ar0]	with gr0 = gr4 A>> 2;
gr5=0ffff0001h	with gr6 and gr2;

if =0 delayed goto ar1	with gr6 = gr6 and not gr2;  // ar1=endFIFO, lDiag=0 | calcPff, lDiag=1
  [ar0++gr0]=gr6  with gr2 R>>= 8;
		  with gr7 -= gr5;
		  with gr4=gr4 and gr3;

delayed goto ar1;
  [ar6++]=gr7;	// pixels1 =+ (i+1,j)
  nul;
  nul;


//  calcDiag  ///////////////////////////////////////////////////////////////////
//
<calcP1f>  //gr7=(i+1,j) -> (i+1,j-1)    ar0..(i+1,j-1) -> (i-1,j-1)
gr6=[ar0]	with gr7--;  // gr7=(i+1,j-1)
gr0=[n2W32neg]	with gr6 and gr2;  // ar0=src[i,J-1]

if =0 delayed goto calcPff	with gr6 = gr6 and not gr2;  // gr0=-nW32  gr6=(jPxl=0)
  [ar0++gr0]=gr6;  // ar0=src[i-1,J-1]
  nul;

[ar6++]=gr7;	// pixels1 =+ (i+1,j-1)


<calcPff>  // gr7(i+1,j-1) -> (i-1,j-1)   ar0..(i-1,j-1) -> (i-1,j+1)
gr6=[ar0]	with gr4++;  // ar0=srcIW32[i-1,J-1]  gr6=pxl4[i-1,J] gr4=jPxl
		with gr4++;  // gr4=(j+1)Pxl
		with gr0 = gr4 >> 2;
gr5=00020000h	with gr6 and gr2;  // gr5=(-1, 0)
		with gr7 -= gr5 noflags;

if =0 delayed goto calcPf1	with gr6 = gr6 and not gr2;
  [ar0++gr0]=gr6  with gr2 R<<= 16;
		  with gr4 = gr4 and gr3;

[ar6++]=gr7;	// pixels1 =+ (i-1,j-1)


<calcPf1>  //gr7=(i-1,j-1) -> (i-1,j+1)    ar0..(i-1,j+1) -> (i+1,j+1)
gr6=[ar0]	with gr5>>=16;  // gr5=2
gr0=[n2W32]	with gr6 and gr2;  // gr0=-nW32

if =0 delayed goto calcP11	with gr6 = gr6 and not gr2;  // gr1=(jPxl=0)
  [ar0++gr0]=gr6 with gr7+=gr5;  // ar0=src[i+1,J+1]  gr7=(i-1,j+1)
  nul;
  
[ar6++]=gr7;	// pixels1 =+ (i-1,j+1)


<calcP11>  //gr7=(i-1,j+1) -> (i+1,j+1)    ar0..(i+1,j+1)
gr6=[ar0]	with gr5<<=16;  // gr5=00020000h
		with gr6 and gr2;

if =0 delayed goto endFIFO	with gr6 = gr6 and not gr2;  // gr6=(jPxl=0)
  [ar0]=gr6	with gr7+=gr5;  // gr7=(i+1,j+1)
  nul;

[ar6++]=gr7;	// pixels1 =+ (i+1,j+1)


//----------------------------------------------------------------
<endFIFO>							//
gr2=ar2;							//
gr6=ar6;							//
		with gr2-gr6;					//
if < goto whileFIFO;						//
//////////////////////////////////////////////////////////////////


//----------------------------------------------------------------
//if (nPxl<nPxlMin) or (nPxl>=nPxlMax) goto l_dropSpot	// nextJPP
gr2=[pixels];
gr1=[nPxlMin]		with gr7=gr6-gr2;  //gr7=nPxlSpot

// если (lDropSpot==0), то обход l_dropSpot
gr3 = [lDropSpot];
gr5=[nPxlMax]		with gr3;
if =0 delayed goto calcRect1	with gr7-gr1; 
  [nPxl]=gr7;

  if < delayed goto l_dropSpot	with gr7-gr5;
    ar0=[aNspotPmin];

  if > delayed goto l_dropSpot;
    ar0=[aNspotPmax];

<calcRect1>
// gr7=nPxl ar2=pixels1 gr1=i gr5=j
// gr0:=yMin  gr2:=yMax  gr4:=xMin  gr6:=xMax
gr0=[nH]	with gr2=false;
gr4=[nW]	with gr6=false;
gr3=0000ffffh;

<calcRect>
// gr4:=Xmin  gr0:=Ymin  gr6:=Xmax  gr2:=Ymax
gr5=[--ar2];
		with gr1=gr5>>16;
		with gr5=gr5 and gr3;

		with gr1-gr0;
if > goto calcYmax	with gr1-gr2;

		with gr0=gr1 noflags;

<calcYmax>
if < goto calcXmin	with gr5-gr4;

		with gr2=gr1 noflags;

<calcXmin>
if > goto calcXmax	with gr5-gr6;

		with gr4=gr5 noflags;

<calcXmax>
if < goto noXmax	with gr7--;

		with gr6=gr5 noflags;

<noXmax>
if > goto calcRect;

// если (lDropSpot==0), то обход l_dropSpot
gr3 = [lDropSpot];
gr5=[dXYmin1]		with gr3;
if =0 delayed goto theSpot	with gr1=gr2-gr0; // gr1=dY
  gr7=[dXYmax1]		with gr1-gr5;

    if < delayed goto l_dropSpot	with gr1-gr7;  // dY<dXYmin1
      ar0=[aNspotDmin]	with gr1=gr6-gr4 noflags;  // gr1=dX

    if > delayed goto l_dropSpot	with gr1-gr5;  // dY>dXYmax1
      ar0=[aNspotDmax]; 

    if < delayed goto l_dropSpot	with gr1-gr7;  // dX<dXYmin1
      ar0=[aNspotDmin]; 

    if > delayed goto l_dropSpot;  // dX>dXYmax1
      ar0=[aNspotDmax]; 

<theSpot>
// That is the interesting spot!!!
// if ((nSpot&&255)==0) then spot=+(0,0,0,0,noPxl) nSpot++
ar1=[spot1]	with gr3=true;
gr1=[nSpot]	with gr3 >>= 24;	// gr1=nSpot
gr7=[noPxl]	with gr3=gr1 and gr3;	// gr3=jColor

if <>0 goto nextSpot	with gr5=false;

    // null skippedSpot  ar1+=6  gr1=nSpot++  gr3=jjColor++
    [ar1++]=gr5		with gr1++;
    [ar1++]=gr5		with gr3++;
    [ar1++]=gr5;
    [ar1++]=gr5;
    [ar1++]=gr7;  // noPxl
    [ar1]=gr5;
    gr1=[lenSpot1]	with gr5=gr1;
    ar1+=gr1		with gr1=gr5;  // ar1=spot1  gr1=nSpot

<nextSpot>
[jjColor]=gr3	with gr3 <<= 8;
[jjColor+1]=gr3 with gr3 <<= 8;
[jjColor+2]=gr3 with gr3 <<= 8;
[jjColor+3]=gr3;

// fill spot param  ar1=spot1
gr7=[nPxl]	with gr3=gr7;	// gr3=noPxl
[ar1++]=gr4	with gr3+=gr7;  // Xmin   gr3=noPxl++nPxl
[ar1++]=gr0;			// Ymin
[ar1++]=gr6;			// Xmax
[ar1++]=gr2;			// Ymax
[ar1++]=gr3;			// noPxl++nPxl
[spot1]=ar1	with gr1++;	// spot1++5 gr1=nSpot++
[nSpot]=gr1;
[noPxl]=gr3;

// FloodFill the spot:  ar2=pixels  gr7=nPxl  gr3=3  gr6=0000ffffh
ar0=[dst]	with gr6=true;
ar5=jjColor	with gr3=gr6>>30;
gr2=floodFill	with gr6 >>= 16;

//------------------------------------------------------------
<floodFill>
gr5=[ar2++];
ar1=iw32	with gr1=gr5>>16;
gr1=[ar1+=gr1]	with gr5=gr5 and gr6;	// gr1=iw32[i] gr5=j
ar4=ar5		with gr4 = gr5>>2;	// gr4=jPixel
ar1=ar0		with gr1 += gr4;	// ar1=dst  gr1=iw32[i] + jPixel
gr1=[ar1+=gr1]	with gr4=gr5 and gr3;	// gr1=dstIJ   gr4=jPxl
gr4=[ar4+=gr4]	with gr7--;
if > delayed goto gr2	with gr1 = gr1 or gr4;  // floodFill
  [ar1]=gr1;
  nul;
//------------------------------------------------------------

[pixels]=ar2;


//--------------------------------------------------------
//--------------------------------------------------------
// finalSpot
//////////////////////////////////////////////////////////
// dtSpot1=clock-tSpot0  spot[0].dtRest=dtFull-(clock-T0)	//
ar1=[spot1];						//
gr1=[lenSpot1];						//
gr2=[tSpot0];						//
							//
call _clock;		// gr7=clock			//
gr0=[T0]	with gr5=gr7-gr2;  // gr0=T0  gr5=dtSpot1=clock-tSpot0
[ar1++gr1]=gr5;		// spot.dtSpot			//
							//
gr2=[dtFull]	with gr7-=gr0;	   // gr2=dtFull  gr7=clock-T0
gr0=[dtSpot]	with gr7=gr2-gr7;  // gr0=dtSpot  gr7=dtRest=dtFull-(clock-T0)
ar0=[spot]	with gr2;  // (dtFull==0)		//
[spot1]=ar1;  // spot1 = spot+lenSpot			//
							//
if =0 delayed goto if_mSpot with gr7-gr0;  // (dtRest-dtSpot)	//
  [ar0++]=gr7;  // spot[0].dtRest			//
  nul;							//
							//
// если НЕ осталось предполагаемое время dtSpot, то выход из программы
if < delayed goto exitProg	with gr0 = false; // dtRest-dtSpot<0  gr0=1
				with gr0++;		//
  nul;							//
  nul;							//
							//
<if_mSpot>						//
// если уже найдено mSpot (>0) пятен, то выход из программы
gr1=[mSpot];						//
gr3=[nSpot]	with gr1;				//
							//
// если mSpot==0, то проверка на nSpot не нужна		//
if =0 goto nextJPP	with gr3-gr1;			//
							//
// если уже найдено mSpot (>0) пятен, то выход из программы
if >= delayed goto exitProg	with gr0=false;  // nSpot >= mSpot  gr0=2
			with gr0++;			//
			with gr0++;			//
  nul;							//
//////////////////////////////////////////////////////////


//--------------------------------------------------------
<nextJPP>
gr2=[jFF]	with gr3=true;
gr4=[jPxl]	with gr3 >>= 30;
ar0=[srcIJ]	with gr2 R<<= 8;
gr5=[j]		with gr4++;
gr1=[i]		with gr5++;  // gr5=j+2 - след пятно м.б. только через 1 пиксел

//--------------------------------------------------------
<nextJ>
gr7=[nW1] 	with gr4++;  // gr4=jPxl++
		with gr5++;  // gr5=j++
		with gr5-gr7;

if < delayed goto begLoopJ	with gr0=gr4 >> 2;
  ar0+=gr0	with gr4 = gr4 and gr3;
		with gr2 R<<= 8;

//--------------------------------------------------------
<nextI>
//////////////////////////////////////////////////////////
// spot[0].dtRest=dtFull-(clock-T0)			//
gr3=[dtFull];			// gr3=dtFull  gr0=ExitCode
		with gr3; 	// (dtFull==0)
if =0 delayed goto nextI1;	// gr0=ExitCode=1
  gr6=[T0];			// gr6=T0

call _clock;			// gr7=clock		//
							//
		with gr7-=gr6;		// gr7=clock-T0
gr0=[dtSpot]	with gr7=gr3-gr7;	// gr0=dtSpot  gr7=dtRest=dtFull-(clock-T0)
		with gr7-gr0;		// (dtRest-dtSpot)
							//
// если НЕ осталось предполагаемое время dtSpot, то выход из программы
if < delayed goto exitProg	with gr0 = false; // dtRest-dtSpot<0  gr0=ExitCode
  nul				with gr0++;	  // gr0=ExitCode=1
  nul;							//
  nul;							//
//////////////////////////////////////////////////////////

<nextI1>
gr0=[dI];
gr7=[nH1]	with gr1 += gr0;
gr3=[dIW32]	with gr1-gr7;
if < delayed goto begLoopI;
  ar3+=gr3	with gr0=false;
  nul;

//--------------------------------------------------------
<exitProg>
ar0=[spot];
call _clock;	// gr7=clock
gr1=[T0];	// gr0=T0
gr2=[dtFull]	with gr7-=gr1;	   // gr2=dtFull  gr7=clock-T0
		with gr7=gr2-gr7;  // gr0=dtSpot  gr7=dtRest=dtFull-(clock-T0)
[ar0++]=gr7;  // spot[0].dtRest
[ar0]=gr0;  // spot[0].nExitCode = 1 - exit on timeout
	    //		       	   2 - exit on nSpot >= mSpot
gr7=[nSpot];

//--------------------------------------------------------
<emergeExit>
POP_REGS();
return;  //FloodFill8


//////////////////////////////////////////////////////////
<l_dropSpot>						//
// nnSpot++						//
gr7=[ar0];  // ar0=dropSpot(Pmin,Pmax,Dmin,Dmax) = (nnSpot nnPxl ttSpots)  gr7=nnSpot
		with gr7++;				//
[ar0++]=gr7;						//
							//
// nnPxl++nPxl						//
gr7=[ar0];						//
gr0=[nPxl];						//
gr2=[tSpot0]	with gr7+=gr0;				//
[ar0++]=gr7;						//
							//
// dttSpot+=dtSpot1  dtRest=dtFull-(clock-T0)		//
call _clock;  // gr7=clock				//
gr0=[ar0]	with gr5=gr7-gr2;  // gr0=dttSpot  gr5=dtSpot1=clock-tSpot0
gr0=[T0]	with gr5+=gr0;     // gr0=T0  gr5=dttSpot++dtSpot1
gr2=[dtFull]	with gr7-=gr0;     // gr2=dtFull  gr7=clock-T0
gr0=[dtSpot]	with gr7=gr2-gr7;  // gr0=dtSpot  gr7=dtRest=dtFull-(clock-T0)
[ar0]=gr5;						//
ar0=[spot]	with gr2;  // (dtFull==0)		//
							//
if =0 delayed goto nextJPP with gr7-gr0;  // (dtRest-dtSpot)	//
  [ar0++]=gr7;  // spot[0].dtRest				//
  nul;							//

// если осталось предполагаемое время dtSpot идем на новое пятно
if >= goto nextJPP	with gr0=false;  // dtRest-dtSpot>=0
							//
goto exitProg		with gr0++;  // gr0=1		//
//////////////////////////////////////////////////////////


end ".text";
