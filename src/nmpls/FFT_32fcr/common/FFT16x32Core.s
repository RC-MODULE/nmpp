//*******************************************************************************************************************************************************/
//*                   				  RC Module Inc., Moscow, Russia                      																*/
//*                     			  NeuroMatrix(r) NM640x Software                      																*/
//*                                                                         																			*/
//*   Software design:  A.Brodyazhenko                                      																			*/
//*                                                                         																			*/
//*   File:             FFT16x32Core.s                             																						*/
//*   Contents:         This function has the register interface and computes forward/inverse															*/
//*						(depends on the W-coefficients) FFT16 from N signals (N can change from 1 to 32)												*/
//*	  Description:		Register gr6 receives the memory address (output signals), from which you upload the computed FFT16 from N signals				*/							//
//* 					Register gr1 receives the step (it is needed to multiply on 2 because the every complex element takes 8 bytes from the memory), */
//* 					with which the every complex element is read of one N signal                                                                    */
//* 					Register ar0 receives the array address with indexes of the complex elements for the main FFT                                   */
//* 					Register ar3  receives the array address with the input signals of the main FFT                                                 */
//* 					You have to initialize register vlen(it have to be equal N-1)																	*/
//*******************************************************************************************************************************************************/

global _FFTFwd16x32Core: label;
begin "text"
<_FFTFwd16x32Core>
////////////////////////////////Stage1////////////////////////////////
	ar1 = ar3;
	fpu 0 rep vlen vreg0 = [ar1++gr1]; // x0
	ar1 = ar3 + 8;
	fpu 1 rep vlen vreg0 = [ar1++gr1]; // x4

	ar1 = ar3 + 16;
	fpu 0 rep vlen vreg1 = [ar1++gr1]; // x8

	ar1 = ar3 + 24;
	fpu 1 rep vlen vreg1 = [ar1++gr1]; // x12

	ar1 = ar3 + 4;
	fpu 2 rep vlen vreg0 = [ar1++gr1]; // x2
	
	ar1 = ar3 + 12;
	fpu 3 rep vlen vreg0 = [ar1++gr1]; // x6

	ar1 = ar3 + 20;
	fpu 2 rep vlen vreg1 = [ar1++gr1]; // x10

	ar1 = ar3 + 28;
	fpu 3 rep vlen vreg1 = [ar1++gr1]; // x14
	
	ar4 = [ar5++]; // W4_16
	gr2 = ar0;
	
	fpu 0 .float vreg2 = vreg0 + vreg1; // y0
	fpu 1 .float vreg2 = vreg0 + vreg1; // y2
	fpu 2 .float vreg2 = vreg0 + vreg1; // y4
	fpu 3 .float vreg2 = vreg0 + vreg1; // y6

	fpu 1 rep 1 vreg5 = [ar4]; // W4_16
	fpu 0 vreg4 = fpu 1 vreg2; // y2
	fpu 2 vreg4 = fpu 3 vreg2; // y6

	fpu 0 .float vreg3 = vreg0 - vreg1; // y1
	fpu 1 .float vreg3 = vreg0 - vreg1; // y3
	fpu 2 .float vreg3 = vreg0 - vreg1; // y5
	fpu 3 .float vreg3 = vreg0 - vreg1; // y7

////////////////////////////////Stage2////////////////////////////////

	fpu 1 vreg4 = fpu 0 vreg3; // y1
	fpu 3 vreg4 = fpu 2 vreg3; // y5
	fpu 3 vreg5 = fpu 1 vreg5;

	ar0 = [ar5++]; // W2_16
	ar6 = [ar5++]; // W6_16

	fpu 0 .float vreg5 = vreg2 + vreg4; // Y0
	fpu 1 .complex vreg6 = vreg3 * .retrive(vreg5) + vreg4; // Y1
	fpu 2 .float vreg5 = vreg2 + vreg4; // Y4
	fpu 3 .complex vreg6 = vreg3 * .retrive(vreg5) + vreg4; // Y5	

	gr0 = ar0; // saving W2_16

	fpu 0 .float vreg6 = vreg2 - vreg4; // Y2
	fpu 1 .complex vreg7 = -vreg3 * .retrive(vreg5) + vreg4; // Y3
	fpu 2 .float vreg6 = vreg2 - vreg4; // y6
	fpu 3 .complex vreg7 = -vreg3 * .retrive(vreg5) + vreg4; // Y7

////////////////////////////////Stage3////////////////////////////////
	fpu 1 rep 1 vreg0 = [ar0]; // W2_16
	fpu 2 rep 1 vreg0 = [ar4]; // W4_16
	fpu 3 rep 1 vreg0 = [ar6]; // W6_16
	fpu 0 vreg1 = fpu 2 vreg5; // Y4
	fpu 1 vreg1 = fpu 3 vreg6; // Y5
	fpu 2 vreg1 = fpu 0 vreg6; // Y2
	fpu 3 vreg1 = fpu 1 vreg7; // Y3

	fpu 0 .float vreg2 = vreg5 + vreg1; // X0
	fpu 1 .complex vreg2 = vreg1 * .retrive(vreg0) + vreg6; // X1
	fpu 2 .complex vreg2 = vreg6 * .retrive(vreg0) + vreg1; // X2
	fpu 3 .complex vreg2 = vreg7 * .retrive(vreg0) + vreg1; // X3
	ar0 = gr2;
	fpu 0 .float vreg3 = vreg5 - vreg1; // X4
	fpu 1 .complex vreg3 = -vreg1 * .retrive(vreg0) + vreg6; // X5
	fpu 2 .complex vreg3 = -vreg6 * .retrive(vreg0) + vreg1; // X6
	fpu 3 .complex vreg3 = -vreg7 * .retrive(vreg0) + vreg1; // X7

////////////////////////////FFT8_2////////////////////////////////
//2, 18, 10, 26, 6, 22, 14, 30
	ar1 = ar3 + 2;
	fpu 0 rep vlen vreg0 = [ar1++gr1]; // x0
	
	ar1 = ar3 + 10;
	fpu 1 rep vlen vreg0 = [ar1++gr1]; // x2

	ar1 = ar3 + 18;
	fpu 0 rep vlen vreg1 = [ar1++gr1]; // x4

	ar1 = ar3 + 26;
	fpu 1 rep vlen vreg1 = [ar1++gr1]; // x6

	ar1 = ar3 + 6;
	fpu 2 rep vlen vreg0 = [ar1++gr1]; // x1

	ar1 = ar3 + 14;
	fpu 3 rep vlen vreg0 = [ar1++gr1]; // x3

	ar1 = ar3 + 22;
	fpu 2 rep vlen vreg1 = [ar1++gr1]; // x5

	ar1 = ar3 + 30;
	fpu 3 rep vlen vreg1 = [ar1++gr1]; // x7

	fpu 0 .float vreg4 = vreg0 + vreg1; // y0
	fpu 1 .float vreg4 = vreg0 + vreg1; // y2
	fpu 2 .float vreg4 = vreg0 + vreg1; // y4
	fpu 3 .float vreg4 = vreg0 + vreg1; // y6

	fpu 1 rep 1 vreg6 = [ar4]; // W4_16
	fpu 0 vreg7 = fpu 1 vreg4; // y2
	fpu 2 vreg7 = fpu 3 vreg4; // y6
	fpu 3 rep 1 vreg6 = [ar4]; // W4_16

	fpu 0 .float vreg5 = vreg0 - vreg1; // y1
	fpu 1 .float vreg5 = vreg0 - vreg1; // y3
	fpu 2 .float vreg5 = vreg0 - vreg1; // y5
	fpu 3 .float vreg5 = vreg0 - vreg1; // y7

/////////////////////Stage2////////////////////////////////
	//gr2 = ar0;
	ar0 = gr0; // W2_16
	fpu 1 vreg7 = fpu 0 vreg5; // y1
	fpu 3 vreg7 = fpu 2 vreg5; // y5

	fpu 0 .float vreg0 = vreg4 + vreg7; 					// Y0
	fpu 1 .complex vreg0 = vreg5 * .retrive(vreg6) + vreg7; // Y1
	fpu 2 .float vreg0 = vreg4 + vreg7; 					// Y4
	fpu 3 .complex vreg0 = vreg5 * .retrive(vreg6) + vreg7; // Y5	

	fpu 0 .float vreg1 = vreg4 - vreg7; 					 // Y2
	fpu 1 .complex vreg1 = -vreg5 * .retrive(vreg6) + vreg7; // Y3
	fpu 2 .float vreg1 = vreg4 - vreg7; 					 // Y6
	fpu 3 .complex vreg1 = -vreg5 * .retrive(vreg6) + vreg7; // Y7

/////////////////////Stage3////////////////////////////////
	fpu 1 rep 1 vreg4 = [ar0]; // W2_16
	fpu 2 rep 1 vreg4 = [ar4]; // W4_16
	fpu 3 rep 1 vreg4 = [ar6]; // W6_16
	fpu 0 vreg4 = fpu 2 vreg4;
	fpu 0 vreg5 = fpu 2 vreg0; // Y4
	fpu 1 vreg5 = fpu 3 vreg0; // Y5
	fpu 2 vreg5 = fpu 0 vreg1; // Y2
	fpu 3 vreg5 = fpu 1 vreg1; // Y3

	ar0 = [ar5++]; // W1_16
	ar1 = gr6;
	ar2 = [ar5++]; // W3_16
	ar4 = [ar5++]; // W5_16
	ar6 = [ar5++]; // W7_16
	fpu 0 .float vreg6 = vreg0 + vreg5; 					// X8
	fpu 1 .complex vreg6 = vreg5 * .retrive(vreg4) + vreg0; // X9
	fpu 2 .complex vreg6 = vreg1 * .retrive(vreg4) + vreg5; // X10
	fpu 3 .complex vreg6 = vreg1 * .retrive(vreg4) + vreg5; // X11

	fpu 0 .float vreg7 = vreg0 - vreg5; 					 // X12
	fpu 1 .complex vreg7 = -vreg5 * .retrive(vreg4) + vreg0; // X13
	fpu 2 .complex vreg7 = -vreg1 * .retrive(vreg4) + vreg5; // X14
	fpu 3 .complex vreg7 = -vreg1 * .retrive(vreg4) + vreg5; // X15

////////////////////////Stage4////////////////////////////
	fpu 2 vreg4 = fpu 1 vreg4; // W2_16
	fpu 1 rep 1 vreg4 = [ar0]; // W1_16
	fpu 1 rep 1 vreg5 = [ar4]; // W5_16
	fpu 2 vreg5 = fpu 3 vreg4; // W6_16
	fpu 3 rep 1 vreg4 = [ar2]; // W3_16
	fpu 3 rep 1 vreg5 = [ar6]; // W7_16

	fpu 0 .float vreg0 = vreg2 + vreg6; 					// X0
	fpu 1 .complex vreg0 = vreg6 * .retrive(vreg4) + vreg2; // X1
	fpu 2 .complex vreg0 = vreg6 * .retrive(vreg4) + vreg2; // X2
	fpu 3 .complex vreg0 = vreg6 * .retrive(vreg4) + vreg2; // X3

	fpu 0 rep vlen [ar1++gr1] = vreg0;
	ar4 = gr6;
	ar4 = ar4 + 2;
	ar1 = ar4;
	fpu 1 rep vlen [ar1++gr1] = vreg0;
	ar4 = ar4 + 2;
	ar1 = ar4;
	fpu 2 rep vlen [ar1++gr1] = vreg0;
	ar4 = ar4 + 2;
	ar1 = ar4;
	fpu 3 rep vlen [ar1++gr1] = vreg0;

	fpu 0 .complex vreg1 = vreg7 * .retrive(vreg4) + vreg3; // X4
	fpu 1 .complex vreg1 = vreg7 * .retrive(vreg5) + vreg3; // X5
	fpu 2 .complex vreg1 = vreg7 * .retrive(vreg5) + vreg3; // X6
	fpu 3 .complex vreg1 = vreg7 * .retrive(vreg5) + vreg3; // X7

	ar4 = ar4 + 2;
	ar1 = ar4;
	fpu 0 rep vlen [ar1++gr1] = vreg1;
	ar4 = ar4 + 2;
	ar1 = ar4;
	fpu 1 rep vlen [ar1++gr1] = vreg1;
	ar4 = ar4 + 2;
	ar1 = ar4;
	fpu 2 rep vlen [ar1++gr1] = vreg1;
	ar4 = ar4 + 2;
	ar1 = ar4;
	fpu 3 rep vlen [ar1++gr1] = vreg1;

	fpu 0 .float vreg2 = vreg2 - vreg6; 					 // X8
	fpu 1 .complex vreg2 = -vreg6 * .retrive(vreg4) + vreg2; // X9
	fpu 2 .complex vreg2 = -vreg6 * .retrive(vreg4) + vreg2; // X10
	fpu 3 .complex vreg2 = -vreg6 * .retrive(vreg4) + vreg2; // X11

	ar4 = ar4 + 2;
	ar1 = ar4;
	fpu 0 rep vlen [ar1++gr1] = vreg2;
	ar4 = ar4 + 2;
	ar1 = ar4;	
	fpu 1 rep vlen [ar1++gr1] = vreg2;
	ar4 = ar4 + 2;
	ar1 = ar4;
	fpu 2 rep vlen [ar1++gr1] = vreg2;
	ar4 = ar4 + 2;
	ar1 = ar4;	
	fpu 3 rep vlen [ar1++gr1] = vreg2;

	fpu 0 .complex vreg3 = -vreg7 * .retrive(vreg4) + vreg3; // X12
	fpu 1 .complex vreg3 = -vreg7 * .retrive(vreg5) + vreg3; // X13
	fpu 2 .complex vreg3 = -vreg7 * .retrive(vreg5) + vreg3; // X14
	fpu 3 .complex vreg3 = -vreg7 * .retrive(vreg5) + vreg3; // X15


	ar4 = ar4 + 2;
	ar1 = ar4;
	fpu 0 rep vlen [ar1++gr1] = vreg3;
	ar4 = ar4 + 2;
	ar1 = ar4;	
	fpu 1 rep vlen [ar1++gr1] = vreg3;
	ar4 = ar4 + 2;
	ar1 = ar4;	
	fpu 2 rep vlen [ar1++gr1] = vreg3;
	ar4 = ar4 + 2;
	ar1 = ar4;
	fpu 3 rep vlen [ar1++gr1] = vreg3;
	return;
end "text";