//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM6405 Software                      */
//*                                                                         */
//*   Fast Fourie Transform Library                                         */
//*   (C-callable functions)                                                */
//*                                                                         */
//*   File:             FFT8192.asm                                         */
//*   Contents:         Routine for forward FFT 8192 of complex array       */
//*                     with 32 bit elements                                */
//*                                                                         */
//*   Software design:  D. Spesivtsev                                       */
//*                                                                         */
//*   Version           1.0                                                 */
//*   Start date:       08.04.2009                                          */
//*   Release   $Date: 2009/04/08 14:19:56 $                                */
//*                                                                         */
//*                                                                         */
//***************************************************************************/

global _FFT_Fwd8192: label;

import from rtmacro;
import from macros;

data ".data_fft_L"

	extern W1_8192: word;
	extern W2_8192: word;
	extern W3_8192: word;

	struct SParam
		LSrcBuffer: word;
		GDstBuffer: word;
		LBuffer1: word;
		GBuffer2: word;
	end SParam;
	.align;	Param: SParam;

end ".data_fft_L";

data ".data_fft_G"

	GAddCmplxMask:long[2] = (
			0000000100000000hl,
			00000000FFFFFFFFhl
			);

end ".data_fft_G";

begin ".text_fft"

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
//        Main Forward FFT-8192 procedure                                   //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

<_FFT_Fwd8192>
.branch;
	ar5 = sp - 2 with gr7 = false;									// gr7=0
	push ar0,gr0 with gr7++;										// gr7=1
	push ar1,gr1;
	push ar2,gr2 with gr2 = gr7 << 1;								// gr2=2 (CONST)
	push ar3,gr3 with gr3 = gr7 << 31;								// gr3=8000_0000h (CONST)
	push ar4,gr4 with gr4 = gr2 << 5;								// gr4=2^6
	push ar5,gr5 with gr1 = gr7 << 13;								// gr1=8192
	push ar6,gr6 with gr6 = gr7 << 9;								// gr6=512

//////////////////////////////////////////////////////////////////////////////

	ar0 = [--ar5];													// LSrcBuffer
	ar1 = [--ar5];													// GDstBuffer
	ar2 = [--ar5];													// LBuffer1
	ar3 = [--ar5];													// GBuffer2

	[Param.LSrcBuffer] = ar0;										// LSrcBuffer
	[Param.GDstBuffer] = ar1;										// GDstBuffer
	[Param.LBuffer1]  = ar2;										// LBuffer1
	[Param.GBuffer2]  = ar3;										// GBuffer2

	vr = gr4;														// vr=2^6 (добавляется для нормализации)

	//////////////////////////////////////////////////////////////////////////
	//        First radix-2 FFT
	//------------------------------------------------------------------------
	// X->S (LSrcBuffer->GBuffer2)
	// gr3=8000_0000h (CONST)
	// ar0=[Param.LSrcBuffer]
	// ar3=[Param.GBuffer2]

	nb1 = gr3;														// 2 столбца
	WTW_REG_DEPRICATED(gr3);

	ar1 = ar0;
	ar1 += 4096 * 2;												// X[4096]
	ar4 = ar1;														// X[4096]

	ar2 = ar3;														// GBuffer2[0]
	ar3 += 4096 * 2;												// GBuffer2[4096]

.repeat 128;
	rep 32 ram = [ar0++];											// [L] ram=X[0..4095]  
	rep 32 data = [ar1++] with ram + data;							// [L] data=X[4096..8191]
	rep 32 [ar2++] = afifo;											// [G] S[0..4095]=X[0..4095]+X[4096..8191] (Запись S в GBuffer2)
	rep 32 data = [ar4++] with ram - data;							// [L] data=X[4096..8191]
	rep 32 [ar3++] = afifo;											// [G] S[4096..8191]=X[0..4095]-X[4096..8191] (Запись S в GBuffer2)
.endrepeat;

	//////////////////////////////////////////////////////////////////////////
	//        Second radix-16 FFT
	//------------------------------------------------------------------------
	// S->SABCD (GBuffer2->GBuffer2 (2-я половина))
	// gr1=4096*2
	// gr2=2 (CONST)
	// gr6=256*2

	sb = 02020202h;													// 8 строк
	gr4 = [Param.GBuffer2];											// S
	ar5 = gr4;
	ar5 += 8192 * 2;												// GBuffer2 (2-я половина)

	ar2 = W1_8192;

	gr5 = gr4 with gr4 += gr1;
	ar6 = gr5 with gr5 += gr2;
	rep 16 wfifo = [ar6++gr6], ftw;									// [G] S (8 + 8 т.)
	WTW_REG_DEPRICATED(gr3);															// 1-е 8 т.
.repeat 255;
	ar1 = ar2;														// Возврат к началу нужного фрагмента таблицы коэффициентов (т. к. они повторяются)
	rep 32 data = [ar1++], ftw with vsum, data, 0;					// [L] W1_8192
	WTW_REG_DEPRICATED(gr3);															// 2-е 8 т.
	ar6 = gr5 with gr5 += gr2;
	rep 16 wfifo = [ar6++gr6];										// [G] S (8 + 8 т.)
	rep 32 data = [ar1++], ftw with vsum, data, afifo;				// [L] W1_8192
	WTW_REG_DEPRICATED(gr3);															// 1-е 8 т.
	rep 32 [ar5++] = afifo;											// [G] Запись A, B, C, D в GBuffer2 (2-я половина)
.endrepeat;
	rep 32 data = [ar2++], ftw with vsum, data, 0;					// [L] W1_8192
	WTW_REG_DEPRICATED(gr3);															// 2-е 8 т.

	ar6 = gr4 with gr4 += gr2;
	rep 16 wfifo = [ar6++gr6];										// [G] S (8 + 8 т.)

	rep 32 data = [ar2++], ftw with vsum, data, afifo;				// [L] W1_8192
	rep 32 [ar5++] = afifo;											// [G] Запись A, B, C, D в GBuffer2 (2-я половина)

	WTW_REG_DEPRICATED(gr3);															// 1-е 8 т.
.repeat 255;
	ar1 = ar2;														// Возврат к началу нужного фрагмента таблицы коэффициентов (т. к. они повторяются)
	rep 32 data = [ar1++], ftw with vsum, data, 0;					// [L] W1_8192
	WTW_REG_DEPRICATED(gr3);															// 2-е 8 т.
	ar6 = gr4 with gr4 += gr2;
	rep 16 wfifo = [ar6++gr6];										// [G] S (8 + 8 т.)
	rep 32 data = [ar1++], ftw with vsum, data, afifo;				// [L] W1_8192
	WTW_REG_DEPRICATED(gr3);															// 1-е 8 т.
	rep 32 [ar5++] = afifo;											// [G] Запись A, B, C, D в GBuffer2 (2-я половина)
.endrepeat;
	rep 32 data = [ar2++], ftw with vsum, data, 0;					// [L] W1_8192
	WTW_REG_DEPRICATED(gr3);															// 2-е 8 т.

	sb = gr2;														// 2 строки
	ar6 = GAddCmplxMask;
	rep 2 wfifo = [ar6++];											// [G] [1|0][0|-1] => wfifo

	rep 32 data = [ar2++], ftw with vsum, data, afifo;				// [L] W1_8192
	rep 32 [ar5++] = afifo;											// [G] Запись A, B, C, D в GBuffer2 (2-я половина)

	//////////////////////////////////////////////////////////////////////////
	//        Second Summation [re*im+im*re | re*re-im*im]
	//------------------------------------------------------------------------
	// SABCD->T (не нормализованное) (GBuffer2 (2-я половина)->LBuffer1)
	// gr7=1

	WTW_REG_DEPRICATED(gr3);
	ar6 = [Param.GBuffer2] with gr4 = gr7 << 2;						// gr4=4
	ar6 += 8192 * 2;												// GBuffer2 (2-я половина)
	ar0 = [Param.LBuffer1] with gr6 = gr7 << 1;
	ar4 = ar6 + gr6 with gr6 = gr4;									// gr6=4
.repeat 256;
	rep 32 data = [ar4++gr4] with vsum, data, vr;					// [G] GBuffer2 (Im)
	rep 32 data = [ar6++gr6] with data + afifo;						// [G] GBuffer2 (Re)
	rep 32 [ar0++] = afifo;											// [L] LBuffer1
.endrepeat;

	//////////////////////////////////////////////////////////////////////////
	//        Second Right Shift Normalization
	//------------------------------------------------------------------------
	// T (не нормализованное)->T (LBuffer1->GBuffer2)

	ar0 = [Param.LBuffer1];											// [L] LBuffer1 (не нормализованное T)
	gr5 = 7;
	ar6 = [Param.GBuffer2];											// [G] GBuffer2 (будет нормализованное T)
	VEC_ARSH32_aaCG(ar0, ar6, 8192 * 2, gr5);

	//////////////////////////////////////////////////////////////////////////
	//        Third radix-16 FFT
	//------------------------------------------------------------------------
	// T->TABCD (GBuffer2->GBuffer2 (2-я половина))
	// gr3=80000000h (CONST)
	// gr1=4096*2
	// gr2=2 (CONST)

	nb1 = gr3;														// 2 столбца
	sb = 02020202h;													// 8 строк
	gr4 = [Param.GBuffer2] with gr7 = false;						// T
	ar5 = gr4 with gr7++;											// gr7=1
	ar5 += 8192 * 2;												// GBuffer2 (2-я половина)
	gr6 = gr7 << 9;													// gr6=256*2

	ar2 = W2_8192;

	gr5 = gr4 with gr4 += gr1;
	ar6 = gr5 with gr5 += gr2;
	rep 16 wfifo = [ar6++gr6], ftw;									// [G] T (8 + 8 т.)
	WTW_REG_DEPRICATED(gr3);															// 1-е 8 т.
.repeat 15;
	ar1 = ar2;														// Возврат к началу нужного фрагмента таблицы коэффициентов (т. к. они повторяются)
		.repeat 16;
			rep 32 data = [ar1++], ftw with vsum, data, 0;			// [L] W2_8192
			WTW_REG_DEPRICATED(gr3);													// 2-е 8 т.
			ar6 = gr5 with gr5 += gr2;
			rep 16 wfifo = [ar6++gr6];								// [G] S (8 + 8 т.)
			rep 32 data = [ar1++], ftw with vsum, data, afifo;		// [L] W2_8192
			WTW_REG_DEPRICATED(gr3);													// 1-е 8 т.
			rep 32 [ar5++] = afifo;									// [G] Запись A, B, C, D в GBuffer2 (2-я половина)
		.endrepeat;
.endrepeat;
.repeat 15;
	rep 32 data = [ar2++], ftw with vsum, data, 0;					// [L] W2_8192
	WTW_REG_DEPRICATED(gr3);															// 2-е 8 т.
	ar6 = gr5 with gr5 += gr2;
	rep 16 wfifo = [ar6++gr6];										// [G] S (8 + 8 т.)
	rep 32 data = [ar2++], ftw with vsum, data, afifo;				// [L] W2_8192
	WTW_REG_DEPRICATED(gr3);															// 1-е 8 т.
	rep 32 [ar5++] = afifo;											// [G] Запись A, B, C, D в GBuffer2 (2-я половина)
.endrepeat;
	rep 32 data = [ar2++], ftw with vsum, data, 0;					// [L] W2_8192
	WTW_REG_DEPRICATED(gr3);															// 2-е 8 т.

	ar6 = gr4 with gr4 += gr2;
	rep 16 wfifo = [ar6++gr6];										// [G] T (8 + 8 т.)

	rep 32 data = [ar2++], ftw with vsum, data, afifo;				// [L] W2_8192
	rep 32 [ar5++] = afifo;											// [G] Запись A, B, C, D в GBuffer2 (2-я половина)

	WTW_REG_DEPRICATED(gr3);															// 1-е 8 т.
.repeat 15;
	ar1 = ar2;														// Возврат к началу нужного фрагмента таблицы коэффициентов (т. к. они повторяются)
		.repeat 16;
			rep 32 data = [ar1++], ftw with vsum, data, 0;			// [L] W2_8192
			WTW_REG_DEPRICATED(gr3);													// 2-е 8 т.
			ar6 = gr4 with gr4 += gr2;
			rep 16 wfifo = [ar6++gr6];								// [G] T (8 + 8 т.)
			rep 32 data = [ar1++], ftw with vsum, data, afifo;		// [L] W2_8192
			WTW_REG_DEPRICATED(gr3);													// 1-е 8 т.
			rep 32 [ar5++] = afifo;									// [G] Запись A, B, C, D в GBuffer2 (2-я половина)
		.endrepeat;
.endrepeat;
.repeat 15;
	rep 32 data = [ar2++], ftw with vsum, data, 0;					// [L] W2_8192
	WTW_REG_DEPRICATED(gr3);															// 2-е 8 т.
	ar6 = gr4 with gr4 += gr2;
	rep 16 wfifo = [ar6++gr6];										// [G] T (8 + 8 т.)
	rep 32 data = [ar2++], ftw with vsum, data, afifo;				// [L] W2_8192
	WTW_REG_DEPRICATED(gr3);															// 1-е 8 т.
	rep 32 [ar5++] = afifo;											// [G] Запись A, B, C, D в GBuffer2 (2-я половина)
.endrepeat;
	rep 32 data = [ar2++], ftw with vsum, data, 0;					// [L] W2_8192
	WTW_REG_DEPRICATED(gr3);															// 2-е 8 т.

	sb = gr2;														// 2 строки
	ar6 = GAddCmplxMask;
	rep 2 wfifo = [ar6++];											// [G] [1|0][0|-1] => wfifo

	rep 32 data = [ar2++], ftw with vsum, data, afifo;				// [L] W2_8192
	rep 32 [ar5++] = afifo;											// [G] Запись A, B, C, D в GBuffer2 (2-я половина)

	//////////////////////////////////////////////////////////////////////////
	//        Third Summation [re*im+im*re | re*re-im*im]
	//------------------------------------------------------------------------
	// TABCD->P (не нормализованное) (GBuffer2 (2-я половина)->LBuffer1)
	// gr7=1

	WTW_REG_DEPRICATED(gr3);
	ar6 = [Param.GBuffer2] with gr4 = gr7 << 2;						// gr4=4
	ar6 += 8192 * 2;												// GBuffer2 (2-я половина)
	ar0 = [Param.LBuffer1] with gr6 = gr7 << 1;
	ar4 = ar6 + gr6 with gr6 = gr4;									// gr6=4
.repeat 256;
	rep 32 data = [ar4++gr4] with vsum, data, vr;					// [G] GBuffer2 (2-я половина) (Im)
	rep 32 data = [ar6++gr6] with data + afifo;						// [G] GBuffer2 (2-я половина) (Re)
	rep 32 [ar0++] = afifo;											// [L] LBuffer1
.endrepeat;

	//////////////////////////////////////////////////////////////////////////
	//        Third Right Shift Normalization
	//------------------------------------------------------------------------
	// P (не нормализованное)->P (LBuffer1->GBuffer2)

	ar0 = [Param.LBuffer1];											// [L] LBuffer1 (не нормализованное P)
	gr5 = 7;
	ar6 = [Param.GBuffer2];											// [G] GBuffer2 (будет нормализованное P)
	VEC_ARSH32_aaCG(ar0, ar6, 8192 * 2, gr5);

	//////////////////////////////////////////////////////////////////////////
	//        Fourth radix-16 FFT
	//------------------------------------------------------------------------
	// P->PABCD (GBuffer2->GBuffer2 (2-я половина))
	// gr3=80000000h (CONST)
	// gr1=4096*2
	// gr2=2 (CONST)

	nb1 = gr3;														// 2 столбца
	sb = 02020202h;													// 8 строк
	gr4 = [Param.GBuffer2] with gr7 = false;						// P
	ar5 = gr4 with gr7++;											// gr7=1
	ar5 += 8192 * 2;												// GBuffer2 (2-я половина)
	gr6 = gr7 << 9;													// gr6=256*2

	ar1 = W3_8192;

	gr5 = gr4 with gr4 += gr1;
	ar6 = gr5 with gr5 += gr2;
	rep 16 wfifo = [ar6++gr6], ftw;									// [G] P (8 + 8 т.)
	WTW_REG_DEPRICATED(gr3);															// 1-е 8 т.
.repeat 255;
	rep 32 data = [ar1++], ftw with vsum, data, 0;					// [L] W3_8192
	WTW_REG_DEPRICATED(gr3);															// 2-е 8 т.
	ar6 = gr5 with gr5 += gr2;
	rep 16 wfifo = [ar6++gr6];										// [G] P (8 + 8 т.)
	rep 32 data = [ar1++], ftw with vsum, data, afifo;				// [L] W3_8192
	WTW_REG_DEPRICATED(gr3);															// 1-е 8 т.
	rep 32 [ar5++] = afifo;											// [G] Запись A, B, C, D в GBuffer2 (2-я половина)
.endrepeat;
	rep 32 data = [ar1++], ftw with vsum, data, 0;					// [L] W3_8192
	WTW_REG_DEPRICATED(gr3);															// 2-е 8 т.

	ar6 = gr4 with gr4 += gr2;
	rep 16 wfifo = [ar6++gr6];										// [G] P (8 + 8 т.)

	rep 32 data = [ar1++], ftw with vsum, data, afifo;				// [L] W3_8192
	rep 32 [ar5++] = afifo;											// [G] Запись A, B, C, D в GBuffer2 (2-я половина)

	WTW_REG_DEPRICATED(gr3);															// 1-е 8 т.
.repeat 255;
	rep 32 data = [ar1++], ftw with vsum, data, 0;					// [L] W3_8192
	WTW_REG_DEPRICATED(gr3);															// 2-е 8 т.
	ar6 = gr4 with gr4 += gr2;
	rep 16 wfifo = [ar6++gr6];										// [G] P (8 + 8 т.)
	rep 32 data = [ar1++], ftw with vsum, data, afifo;				// [L] W3_8192
	WTW_REG_DEPRICATED(gr3);															// 1-е 8 т.
	rep 32 [ar5++] = afifo;											// [G] Запись A, B, C, D в GBuffer2 (2-я половина)
.endrepeat;
	rep 32 data = [ar1++], ftw with vsum, data, 0;					// [L] W3_8192
	WTW_REG_DEPRICATED(gr3);															// 2-е 8 т.

	sb = gr2;														// 2 строки
	ar6 = GAddCmplxMask;
	rep 2 wfifo = [ar6++];											// [G] [1|0][0|-1] => wfifo

	rep 32 data = [ar1++], ftw with vsum, data, afifo;				// [L] W3_8192
	rep 32 [ar5++] = afifo;											// [G] Запись A, B, C, D в GBuffer2 (2-я половина)

	//////////////////////////////////////////////////////////////////////////
	//        Fourth Summation [re*im+im*re | re*re-im*im]
	//------------------------------------------------------------------------
	// PABCD->Y (GBuffer2 (2-я половина)->LBuffer1)
	// (с расстановкой Y в правильном порядке)
	// gr7=1

	WTW_REG_DEPRICATED(gr3);
	ar6 = [Param.GBuffer2] with gr4 = gr7 << 2;						// gr4=4
	ar6 += 8192 * 2;												// GBuffer2 (2-я половина)
	gr0 = [Param.LBuffer1] with gr6 = gr7 << 1;
	ar4 = ar6 + gr6 with gr6 = gr4;									// gr6=4

	gr7 <<= 6;														// gr7=32*2
	gr5 = gr7 << 4;													// gr5=512*2

.repeat 2;
	gr1 = gr0 with gr0 += gr2;										// +=1*2
		.repeat 16;
			gr3 = gr1 with gr1 += gr4;								// +=2*2
				.repeat 16;
					rep 16 data = [ar4++gr4] with vsum, data, vr;	// [G] GBuffer2 (Im)
					rep 16 data = [ar6++gr6] with data + afifo;		// [G] GBuffer2 (Re)
					ar5 = gr3 with gr3 += gr7;						// +=32*2
					rep 16 [ar5++gr5] = afifo;						// [L] LBuffer1 (+=512*2)
				.endrepeat;
		.endrepeat;
.endrepeat;

	//////////////////////////////////////////////////////////////////////////
	//        Fourth Right Shift Normalization
	//------------------------------------------------------------------------
	// Y (не нормализованный)->Y (LBuffer1->GDstBuffer)

	ar0 = [Param.LBuffer1];											// [L] LBuffer1 (не нормализованное Y)
	gr5 = 7;
	ar6 = [Param.GDstBuffer];										// [G] Y (будет нормализованное Y)
	VEC_ARSH32_aaCG(ar0, ar6, 8192 * 2, gr5);

//////////////////////////////////////////////////////////////////////////////

	pop ar6,gr6;
	pop ar5,gr5;
	pop ar4,gr4;
	pop ar3,gr3;
	pop ar2,gr2;
	pop ar1,gr1;
	pop ar0,gr0;
	return with gr7 = false;
.wait;
end ".text_fft";