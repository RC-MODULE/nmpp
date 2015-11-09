//------------------------------------------------------------------------
//
//  $Workfile:: pcSort.cp $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:16 $
//
//! \if file_doc
//!
//! \file   pcSort.cpp
//! \author Сергей Мушкаев
//! \brief  Функции сортировки для векторов.
//!
//! \endif
//!
//------------------------------------------------------------------------

//#include "vec.h"
//#include "nmpp.h"

void VEC_QSort(
	  int*	pSrc,	//Pointer to input massive
	  int	len		//Length of input massive
	  )
{
int mid,buf,*above,*below;
	
	if (len <= 0)	return;
	
	mid = pSrc[0];
	above = pSrc;
	below = pSrc + len - 1;

	for (;;)
	{
		while (mid < *below)
			{	below--;}

		do	{
			if (below == above)
					{
						*pSrc = *above;
						*above = mid;
						
						VEC_QSort(pSrc,(above - pSrc));
						VEC_QSort((above + 1),(len + pSrc - above - 1));
						return;
					}
			
			above++;
			}
		while (*above < mid);

		buf = *above;
		*above = *below;
		*below = buf;
	}
//end
}

/*
int mid,buf,*above,*below;
	
	if (len <= 0)	return;
	
	mid = pSrc[0];
	above = pSrc;
	below = pSrc + len - 1;

	<NextSort>
	gr4 = [--ar5];					Above address	
	gr0 = [--ar5] with gr5 = gr4;	Count;

	gr0--;
	if <= delayed goto Return;
		gr6 = gr5 + gr0;			Below address	
	
	gr7 = [gr5];
LowLoop:
	if (mid >= *below) goto HighLoop;
	below--;
goto LowLoop;
	
	gr2 = [gr6];
	gr2 - gr7;
	if <= goto HighLoop;

	delayed goto LowLoop;
		gr6--;
		nul;
HighLoop:
	if (below == above) goto Middle;

	above++;
	if (*above < mid) goto HighLoop;
	buf = *above;
	*above = *below;
	*below = buf;
goto LowLoop;

	gr5 - gr6;
	if =0 goto Middle;

	gr5++;
	gr1 = [gr5];
	gr1 - gr7;
	if < delayed goto HighLoop;
		gr1 = [gr5];
		gr2 = [gr6];

	delayed	goto LowLoop;
		[gr5] = gr2;
		[gr6] = gr1;
	
Middle:
	*pSrc = *above;
	*above = mid;

	QSort(pSrc,(above - pSrc));
	QSort((above + 1),(len + pSrc - above - 1));

	gr1 = [gr5];
	[gr5] = gr7;
	[gr4] = gr1;

	gr7 = gr5 - gr4;			high massive lenth
	gr0 -= gr7;					low massive lenth

	push	gr0	with gr5++;		low massive data
	push	gr5;				low massive data

	push	gr7;				high massive data
	push	gr4;				high massive data


	call NextSort;				high massive
		pop		ar0,gr0;
	


	call NextSort;				low massive
		pop		ar0,gr0;

<Return>
*/
