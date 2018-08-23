extern DDiv : label;

data ".my_data"
	addr_L : word;
	addr_U : word;
	count : word = 0;
	main_line_addr : word;
	blocks32_count : word;
	blocks32_surplus : word;
	blocks4_count : word;
	blocks4_current : word;
	blocks4_surplus : word;
	buffer :long = 0;
	.align;
	the_two : word[2] = (0, 1073741824);
end ".my_data";

begin ".text"
global _nmppmLUDecomp_64f : label;
<_nmppmLUDecomp_64f>

	push ar1,gr1;
	push ar2,gr2;									// пролог
	push ar3,gr3;
	push ar4,gr4;
	push ar5,gr5;
	push ar6,gr6;

	ar6 = ar7 - 14;

	ar1 = [--ar6];       								// A
	ar2 = [--ar6];       								// L
	ar3 = [--ar6];       								// U
	gr1 = [--ar6];									  	// N


	[main_line_addr] = ar1;
	gr1--;

	gr4 = gr1 << 27;													//остаток от деления N на 32
	gr4 = gr4 >> 27;
	[blocks32_surplus] = gr4;

	gr2 = gr1 >> 5;
	[blocks32_count] = gr2;												//целая часть от деления N на 32

	gr5 = gr1 << 30;
	gr5 = gr5 >> 30;													//остаток от деления N на 4
	[blocks4_surplus] = gr5;

	gr3 = gr1 >> 2;														//целая часть от деления N на 4
	[blocks4_count] = gr3;
	[blocks4_current] = gr3;



<COPY_FIRST_LINE>

	fpu 0 rep 32 vreg0 = [ar1++];
	fpu 0 rep 32 [ar3++] = vreg0;
	gr2--;
	if <>0 goto COPY_FIRST_LINE;
	gr4;
	if < goto START_SETUP;
	vlen = gr4;
	fpu 0 rep vlen vreg0 = [ar1++];
	fpu 0 rep vlen [ar3++] = vreg0;

<START_SETUP>
	gr1++;
	gr2 = gr1 << 1;
	ar2 = ar2 + gr2;													//сдвинула адрес матрицы L на вторую строку
	[addr_L] = ar2;
	gr1 = gr2;														// сдвинули N на 1

	gr5 = [blocks32_count];

	[addr_U] = ar3;
	ar1 = [main_line_addr];														//возвращаем адрес A
	vlen = 31;
	ar4 = ar1 + gr1;													//адрес текущей строки

<FULL_START_4>

	ar5 = buffer;
	ar6= the_two;														//вспомогательные числа для нахождения 1/y
	fpu 0  rep 1 vreg2= [ar6];											// '2'
	gr7= 00400000h;

	fpu 0 rep 1 vreg1 = [ar1];											//y
	fpu 0 rep 1 [ar5++] = vreg1;										// положили y в буфер, нужно для деления

	gr6= [--ar5] with false;        //  clear psw flags
	gr6 C<<= 1;                     //  preserve sign
	gr6= gr6 + gr7 noflags;         //  invert exp 1 getting first interpolation
	gr6= not gr6 noflags;           //  invert exp 2
	gr6 C>>= 1;
	[ar5++]= gr6 with gr7= false;
	fpu 0  rep 1 vreg0= [--ar5];

	fpu 0  .double vreg3= - vreg0*vreg1 +vreg2;
	fpu 0  .double vreg0= vreg3 * vreg0;

	fpu 0  .double vreg3= - vreg0*vreg1 +vreg2;
	fpu 0  .double vreg0= vreg3 * vreg0;

  	fpu 0 .double vreg3= - vreg0*vreg1 +vreg2;
  	fpu 0  .double vreg0= vreg3 * vreg0;

  	fpu 0  .double vreg3= - vreg0*vreg1 +vreg2;
  	fpu 0  .double vreg0= vreg3 * vreg0;

  	fpu 0  .double vreg3= - vreg0*vreg1 +vreg2;
  	fpu 0  .double vreg0= vreg3 * vreg0;
	// Копируем (1/y) во все fpu
	fpu 1 vreg0 = fpu 0 vreg0;
	fpu 2 vreg0 = fpu 0 vreg0;
	fpu 3 vreg0 = fpu 1 vreg0;

<FULL_4>
	fpu 0 rep vlen vreg7 = [ar1++];
	fpu 1 vreg7 = fpu 0 vreg7;											// копируем ведущую строку из fpu 0  в fpu 1
	fpu 2 vreg7 = fpu 0 vreg7;											// копируем ведущую строку из fpu 0  в fpu 2
	fpu 3 vreg7 = fpu 1 vreg7;											// копируем ведущую строку из fpu 1  в fpu 3

	fpu 0 rep 1 vreg4 = [ar4];											//x1
	fpu 0 rep vlen vreg6 = [ar4++];										//текущая строка 1

	gr4 = gr1;

	ar4 = ar4 + gr4;
	ar4 = ar4 - 64;

	fpu 1 rep 1 vreg4 = [ar4];											//x2
	fpu 1 rep vlen vreg6 = [ar4++];										//текущая строка 2

	ar4 = ar4 + gr4;
	ar4 = ar4 - 64;

	fpu 2 rep 1 vreg4 = [ar4];											//x3
	fpu 2 rep vlen vreg6 = [ar4++];										//текущая строка  3

	ar4 = ar4 + gr4;
	ar4 = ar4 - 64;

	fpu 3 rep 1 vreg4 = [ar4];											//x4
	fpu 3 rep vlen vreg6 = [ar4++];										//текущая строка 4

	fpu 0  .double vreg5= vreg4 * vreg0;     							// x/y = x*(1/y)
	fpu 1  .double vreg5= vreg4 * vreg0;     							// x/y = x*(1/y)
	fpu 2  .double vreg5= vreg4 * vreg0;     							// x/y = x*(1/y)
	fpu 3  .double vreg5= vreg4 * vreg0;     							// x/y = x*(1/y)

	fpu 0 rep 1 [ar2++gr2] = vreg5;										//злемент L
	fpu 0 .double vreg1 = -vreg5;
	fpu 1 rep 1 [ar2++gr2] = vreg5;										//злемент L
	fpu 1 .double vreg1 = -vreg5;
	fpu 2 rep 1 [ar2++gr2] = vreg5;										//злемент L
	fpu 2 .double vreg1 = -vreg5;
	fpu 3 rep 1 [ar2++gr2] = vreg5;										//злемент L
	fpu 3 .double vreg1 = -vreg5;

	fpu 0 .double vreg3 = vreg7 * .retrive(vreg1);
	fpu 1 .double vreg3 = vreg7 * .retrive(vreg1);
	fpu 2 .double vreg3 = vreg7 * .retrive(vreg1);
	fpu 3 .double vreg3 = vreg7 * .retrive(vreg1);
																		//вычисление строк U
	fpu 0 .double vreg1 = vreg6 + vreg3;
	fpu 1 .double vreg1 = vreg6 + vreg3;
	fpu 2 .double vreg1 = vreg6 + vreg3;
	fpu 3 .double vreg1 = vreg6 + vreg3;

	gr3 = gr1;

	fpu 0 rep vlen [ar3++] = vreg1;										//записали в U
	ar3 = ar3 + gr3;
	ar3 = ar3 - 64;

	fpu 1 rep vlen [ar3++] = vreg1;										//записали в U
	ar3 = ar3 + gr3;
	ar3 = ar3 - 64;

	fpu 2 rep vlen [ar3++] = vreg1;										//записали в U
	ar3 = ar3 + gr3;
	ar3 = ar3 - 64;

	fpu 3 rep vlen [ar3++] = vreg1;										//записали в U

	gr5--;
	if > goto NEXT_32_4;
	gr5 = [blocks32_surplus];
	gr5;
	if >= goto SURPLUS32_4;
	goto NEXT_PACK;

<NEXT_32_4>
	gr4 = -gr4;
	gr3 = -gr3;
	ar4 = ar4 + gr4;
	ar3 = ar3 + gr3;
	ar4 = ar4 + gr4;
	ar3 = ar3 + gr3;
	ar4 = ar4 + gr4;
	ar3 = ar3 + gr3;
	gr4 = -gr4;
	gr3 = -gr3;

	fpu 0 rep vlen vreg7 = [ar1++];
	fpu 1 vreg7 = fpu 0 vreg7;											// копируем ведущую строку из fpu 0  в fpu 1
	fpu 2 vreg7 = fpu 0 vreg7;											// копируем ведущую строку из fpu 0  в fpu 2
	fpu 3 vreg7 = fpu 1 vreg7;											// копируем ведущую строку из fpu 1  в fpu 3


	fpu 0 rep vlen vreg6 = [ar4++];										//текущая строка 1
	ar4 = ar4 + gr4;
	ar4 = ar4 - 64;

	fpu 1 rep vlen vreg6 = [ar4++];										//текущая строка 2
	ar4 = ar4 + gr4;
	ar4 = ar4 - 64;

	fpu 2 rep vlen vreg6 = [ar4++];										//текущая строка  3
	ar4 = ar4 + gr4;
	ar4 = ar4 - 64;

	fpu 3 rep vlen vreg6 = [ar4++];										//текущая строка 4

	fpu 0 .double vreg1 = -vreg5;
	fpu 1 .double vreg1 = -vreg5;
	fpu 2 .double vreg1 = -vreg5;
	fpu 3 .double vreg1 = -vreg5;

	fpu 0 .double vreg3 = vreg7 * .retrive(vreg1);
	fpu 1 .double vreg3 = vreg7 * .retrive(vreg1);
	fpu 2 .double vreg3 = vreg7 * .retrive(vreg1);
	fpu 3 .double vreg3 = vreg7 * .retrive(vreg1);
																		//вычисление строк U
	fpu 0 .double vreg1 = vreg6 + vreg3;
	fpu 1 .double vreg1 = vreg6 + vreg3;
	fpu 2 .double vreg1 = vreg6 + vreg3;
	fpu 3 .double vreg1 = vreg6 + vreg3;

	fpu 0 rep vlen [ar3++] = vreg1;										//записали в U
	ar3 = ar3 + gr3;
	ar3 = ar3 - 64;

	fpu 1 rep vlen [ar3++] = vreg1;										//записали в U
	ar3 = ar3 + gr3;
	ar3 = ar3 - 64;

	fpu 2 rep vlen [ar3++] = vreg1;										//записали в U
	ar3 = ar3 + gr3;
	ar3 = ar3 - 64;

	fpu 3 rep vlen [ar3++] = vreg1;										//записали в U



	gr5--;
	if > goto NEXT_32_4;
	gr5 = [blocks32_surplus];
	gr5;
	if >= goto SURPLUS32_4;
	goto NEXT_PACK;


<SURPLUS32_4>
	vlen = gr5;
	gr5++;

	gr4 = -gr4;
	gr3 = -gr3;
	ar4 = ar4 + gr4;
	ar3 = ar3 + gr3;
	ar4 = ar4 + gr4;
	ar3 = ar3 + gr3;
	ar4 = ar4 + gr4;
	ar3 = ar3 + gr3;

	
	gr5 = gr5 <<1;
	gr3 = gr1 - gr5;
	gr4 = gr3;

	fpu 0 rep vlen vreg7 = [ar1++];
	fpu 1 vreg7 = fpu 0 vreg7;											// копируем ведущую строку из fpu 0  в fpu 1
	fpu 2 vreg7 = fpu 0 vreg7;											// копируем ведущую строку из fpu 0  в fpu 2
	fpu 3 vreg7 = fpu 1 vreg7;											// копируем ведущую строку из fpu 1  в fpu 3


	fpu 0 rep vlen vreg6 = [ar4++];										//текущая строка 1
	ar4 = ar4 + gr4;

	fpu 1 rep vlen vreg6 = [ar4++];										//текущая строка 2
	ar4 = ar4 + gr4;


	fpu 2 rep vlen vreg6 = [ar4++];										//текущая строка  3
	ar4 = ar4 + gr4;

	fpu 3 rep vlen vreg6 = [ar4++];										//текущая строка 4


	fpu 0 .double vreg1 = -vreg5;
	fpu 1 .double vreg1 = -vreg5;
	fpu 2 .double vreg1 = -vreg5;
	fpu 3 .double vreg1 = -vreg5;

	fpu 0 .double vreg3 = vreg7 * .retrive(vreg1);
	fpu 1 .double vreg3 = vreg7 * .retrive(vreg1);
	fpu 2 .double vreg3 = vreg7 * .retrive(vreg1);
	fpu 3 .double vreg3 = vreg7 * .retrive(vreg1);
																		//вычисление строк U
	fpu 0 .double vreg1 = vreg6 + vreg3;
	fpu 1 .double vreg1 = vreg6 + vreg3;
	fpu 2 .double vreg1 = vreg6 + vreg3;
	fpu 3 .double vreg1 = vreg6 + vreg3;



	fpu 0 rep vlen [ar3++] = vreg1;										//записали в U
	ar3 = ar3 + gr3;

	fpu 1 rep vlen [ar3++] = vreg1;										//записали в U
	ar3 = ar3 + gr3;

	fpu 2 rep vlen [ar3++] = vreg1;										//записали в U
	ar3 = ar3 + gr3;

	fpu 3 rep vlen [ar3++] = vreg1;										//записали в U

<NEXT_PACK>
	gr4 = [count];
	ar4 = ar4 + gr4;
	gr3 = gr4;
	ar3 = ar3 + gr3;
	vlen = 31;

	ar1 = [main_line_addr];

	gr5 = [blocks4_current];
	gr5--;
	[blocks4_current] = gr5;
	gr5;
	if > delayed goto FULL_4;
		gr5 = [blocks32_count];


	gr4 = [blocks4_surplus];
	gr4;
	if =0 goto NEXT_ITER;
	gr4--;
	if =0 delayed goto ONLY_1;
		gr5 = [blocks32_count];

	gr4--;
	if =0 goto ONLY_2;
	gr4--;
	if =0 goto ONLY_3;

<ONLY_3>
	fpu 0 rep vlen vreg7 = [ar1++];
	fpu 1 vreg7 = fpu 0 vreg7;										// копируем ведущую строку из fpu 0  в fpu 1
	fpu 2 vreg7 = fpu 0 vreg7;										// копируем ведущую строку из fpu 0  в fpu 2

	fpu 0 rep 1 vreg4 = [ar4];										//x1
	fpu 0 rep vlen vreg6 = [ar4++];									//текущая строка 1

	gr4 = gr1;

	ar4 = ar4 + gr4;
	ar4 = ar4 - 64;

	fpu 1 rep 1 vreg4 = [ar4];										//x2
	fpu 1 rep vlen vreg6 = [ar4++];									//текущая строка 2

	ar4 = ar4 + gr4;
	ar4 = ar4 - 64;

	fpu 2 rep 1 vreg4 = [ar4];										//x3
	fpu 2 rep vlen vreg6 = [ar4++];									//текущая строка  3


	fpu 0  .double vreg5= vreg4 * vreg0;     						// x/y = x*(1/y)
	fpu 1  .double vreg5= vreg4 * vreg0;     						// x/y = x*(1/y)
	fpu 2  .double vreg5= vreg4 * vreg0;     						// x/y = x*(1/y)

	fpu 0 rep 1 [ar2++gr2] = vreg5;									//злемент L
	fpu 0 .double vreg1 = -vreg5;
	fpu 1 rep 1 [ar2++gr2] = vreg5;									//злемент L
	fpu 1 .double vreg1 = -vreg5;
	fpu 2 rep 1 [ar2++gr2] = vreg5;									//злемент L
	fpu 2 .double vreg1 = -vreg5;

	fpu 0 .double vreg3 = vreg7 * .retrive(vreg1);
	fpu 1 .double vreg3 = vreg7 * .retrive(vreg1);
	fpu 2 .double vreg3 = vreg7 * .retrive(vreg1);
																	//вычисление строк U
	fpu 0 .double vreg1 = vreg6 + vreg3;
	fpu 1 .double vreg1 = vreg6 + vreg3;
	fpu 2 .double vreg1 = vreg6 + vreg3;

	gr3 = gr1;

	fpu 0 rep vlen [ar3++] = vreg1;									//записали в U
	ar3 = ar3 + gr3;
	ar3 = ar3 - 64;

	fpu 1 rep vlen [ar3++] = vreg1;									//записали в U
	ar3 = ar3 + gr3;
	ar3 = ar3 - 64;

	fpu 2 rep vlen [ar3++] = vreg1;									//записали в U

	gr5--;
	if > goto NEXT_32_3;
	gr5 = [blocks32_surplus];
	gr5;
	if >= goto SURPLUS32_3;
	goto NEXT_ITER;

<NEXT_32_3>
	gr4 = -gr4;
	gr3 = -gr3;
	ar4 = ar4 + gr4;
	ar3 = ar3 + gr3;
	ar4 = ar4 + gr4;
	ar3 = ar3 + gr3;
	gr4 = -gr4;
	gr3 = -gr3;

	fpu 0 rep vlen vreg7 = [ar1++];
	fpu 1 vreg7 = fpu 0 vreg7;										// копируем ведущую строку из fpu 0  в fpu 1
	fpu 2 vreg7 = fpu 0 vreg7;										// копируем ведущую строку из fpu 0  в fpu 2


	fpu 0 rep vlen vreg6 = [ar4++];									//текущая строка 1
	ar4 = ar4 + gr4;
	ar4 = ar4 - 64;

	fpu 1 rep vlen vreg6 = [ar4++];									//текущая строка 2
	ar4 = ar4 + gr4;
	ar4 = ar4 - 64;

	fpu 2 rep vlen vreg6 = [ar4++];									//текущая строка  3

	fpu 0 .double vreg1 = -vreg5;
	fpu 1 .double vreg1 = -vreg5;
	fpu 2 .double vreg1 = -vreg5;

	fpu 0 .double vreg3 = vreg7 * .retrive(vreg1);
	fpu 1 .double vreg3 = vreg7 * .retrive(vreg1);
	fpu 2 .double vreg3 = vreg7 * .retrive(vreg1);
																	//вычисление строк U
	fpu 0 .double vreg1 = vreg6 + vreg3;
	fpu 1 .double vreg1 = vreg6 + vreg3;
	fpu 2 .double vreg1 = vreg6 + vreg3;

	fpu 0 rep vlen [ar3++] = vreg1;									//записали в U
	ar3 = ar3 + gr3;
	ar3 = ar3 - 64;

	fpu 1 rep vlen [ar3++] = vreg1;									//записали в U
	ar3 = ar3 + gr3;
	ar3 = ar3 - 64;

	fpu 2 rep vlen [ar3++] = vreg1;									//записали в U

	gr5--;
	if > goto NEXT_32_3;
	gr5 = [blocks32_surplus];
	gr5;
	if >= goto SURPLUS32_3;
	goto NEXT_ITER;


<SURPLUS32_3>
	vlen = gr5;
	gr5++;

	gr4 = -gr4;
	gr3 = -gr3;
	ar4 = ar4 + gr4;
	ar3 = ar3 + gr3;
	ar4 = ar4 + gr4;
	ar3 = ar3 + gr3;
	gr4 = -gr4;
	gr3 = -gr3;

	gr5 = gr5 <<1;
	gr3 = gr1 - gr5;
	gr4 = gr3;

	fpu 0 rep vlen vreg7 = [ar1++];
	fpu 1 vreg7 = fpu 0 vreg7;									// копируем ведущую строку из fpu 0  в fpu 1
	fpu 2 vreg7 = fpu 0 vreg7;									// копируем ведущую строку из fpu 0  в fpu 2

	fpu 0 rep vlen vreg6 = [ar4++];								//текущая строка 1
	ar4 = ar4 + gr4;

	fpu 1 rep vlen vreg6 = [ar4++];								//текущая строка 2
	ar4 = ar4 + gr4;

	fpu 2 rep vlen vreg6 = [ar4++];								//текущая строка  3



	fpu 0 .double vreg1 = -vreg5;
	fpu 1 .double vreg1 = -vreg5;
	fpu 2 .double vreg1 = -vreg5;

	fpu 0 .double vreg3 = vreg7 * .retrive(vreg1);
	fpu 1 .double vreg3 = vreg7 * .retrive(vreg1);
	fpu 2 .double vreg3 = vreg7 * .retrive(vreg1);
																//вычисление строк U
	fpu 0 .double vreg1 = vreg6 + vreg3;
	fpu 1 .double vreg1 = vreg6 + vreg3;
	fpu 2 .double vreg1 = vreg6 + vreg3;

	fpu 0 rep vlen [ar3++] = vreg1;								//записали в U
	ar3 = ar3 + gr3;

	fpu 1 rep vlen [ar3++] = vreg1;								//записали в U
	ar3 = ar3 + gr3;

	fpu 2 rep vlen [ar3++] = vreg1;								//записали в U

	goto NEXT_ITER;

<ONLY_2>
	fpu 0 rep vlen vreg7 = [ar1++];
	fpu 1 vreg7 = fpu 0 vreg7;									// копируем ведущую строку из fpu 0  в fpu 1

	fpu 0 rep 1 vreg4 = [ar4];									//x1
	fpu 0 rep vlen vreg6 = [ar4++];								//текущая строка 1

	gr4 = gr1;

	ar4 = ar4 + gr4;
	ar4 = ar4 - 64;

	fpu 1 rep 1 vreg4 = [ar4];									//x2
	fpu 1 rep vlen vreg6 = [ar4++];								//текущая строка 2


	fpu 0  .double vreg5= vreg4 * vreg0;     					// x/y = x*(1/y)
	fpu 1  .double vreg5= vreg4 * vreg0;     					// x/y = x*(1/y)

	fpu 0 rep 1 [ar2++gr2] = vreg5;								//злемент L
	fpu 0 .double vreg1 = -vreg5;
	fpu 1 rep 1 [ar2++gr2] = vreg5;								//злемент L
	fpu 1 .double vreg1 = -vreg5;

	fpu 0 .double vreg3 = vreg7 * .retrive(vreg1);
	fpu 1 .double vreg3 = vreg7 * .retrive(vreg1);
																//вычисление строк U
	fpu 0 .double vreg1 = vreg6 + vreg3;
	fpu 1 .double vreg1 = vreg6 + vreg3;

	gr3 = gr1;

	fpu 0 rep vlen [ar3++] = vreg1;								//записали в U
	ar3 = ar3 + gr3;
	ar3 = ar3 - 64;

	fpu 1 rep vlen [ar3++] = vreg1;								//записали в U

	gr5--;
	if > goto NEXT_32_2;
	gr5 = [blocks32_surplus];
	gr5;
	if >= goto SURPLUS32_2;
	goto NEXT_ITER;

<NEXT_32_2>
	gr4 = -gr4;
	gr3 = -gr3;
	ar4 = ar4 + gr4;
	ar3 = ar3 + gr3;
	gr4 = -gr4;
	gr3 = -gr3;

	fpu 0 rep vlen vreg7 = [ar1++];
	fpu 1 vreg7 = fpu 0 vreg7;									// копируем ведущую строку из fpu 0  в fpu 1


	fpu 0 rep vlen vreg6 = [ar4++];								//текущая строка 1
	ar4 = ar4 + gr4;
	ar4 = ar4 - 64;

	fpu 1 rep vlen vreg6 = [ar4++];								//текущая строка 2


	fpu 0 .double vreg1 = -vreg5;
	fpu 1 .double vreg1 = -vreg5;

	fpu 0 .double vreg3 = vreg7 * .retrive(vreg1);
	fpu 1 .double vreg3 = vreg7 * .retrive(vreg1);
																//вычисление строк U
	fpu 0 .double vreg1 = vreg6 + vreg3;
	fpu 1 .double vreg1 = vreg6 + vreg3;

	fpu 0 rep vlen [ar3++] = vreg1;								//записали в U
	ar3 = ar3 + gr3;
	ar3 = ar3 - 64;

	fpu 1 rep vlen [ar3++] = vreg1;								//записали в U

	gr5--;
	if > goto NEXT_32_2;
	gr5 = [blocks32_surplus];
	gr5;
	if >= goto SURPLUS32_2;
	goto NEXT_ITER;


<SURPLUS32_2>
	vlen = gr5;
	gr5++;

	gr4 = -gr4;
	gr3 = -gr3;
	ar4 = ar4 + gr4;
	ar3 = ar3 + gr3;
	gr4 = -gr4;
	gr3 = -gr3;

	gr5 = gr5 <<1;
	gr3 = gr1 - gr5;
	gr4 = gr3;

	fpu 0 rep vlen vreg7 = [ar1++];
	fpu 1 vreg7 = fpu 0 vreg7;									// копируем ведущую строку из fpu 0  в fpu 1

	fpu 0 rep vlen vreg6 = [ar4++];								//текущая строка 1
	ar4 = ar4 + gr4;

	fpu 1 rep vlen vreg6 = [ar4++];								//текущая строка 2

	fpu 0 .double vreg1 = -vreg5;
	fpu 1 .double vreg1 = -vreg5;

	fpu 0 .double vreg3 = vreg7 * .retrive(vreg1);
	fpu 1 .double vreg3 = vreg7 * .retrive(vreg1);
																//вычисление строк U
	fpu 0 .double vreg1 = vreg6 + vreg3;
	fpu 1 .double vreg1 = vreg6 + vreg3;

	fpu 0 rep vlen [ar3++] = vreg1;								//записали в U
	ar3 = ar3 + gr3;

	fpu 1 rep vlen [ar3++] = vreg1;								//записали в U

	goto NEXT_ITER;



<ONLY_1>
	fpu 0 rep vlen vreg7 = [ar1++];

	fpu 0 rep 1 vreg4 = [ar4];											//x1
	fpu 0 rep vlen vreg6 = [ar4++];										//текущая строка 1

	fpu 0  .double vreg5= vreg4 * vreg0;     							// x/y = x*(1/y)

	fpu 0 rep 1 [ar2++gr2] = vreg5;										//злемент L
	fpu 0 .double vreg1 = -vreg5;
	fpu 0 .double vreg3 = vreg7 * .retrive(vreg1);
																		//вычисление строк U
	fpu 0 .double vreg1 = vreg6 + vreg3;
	fpu 0 rep vlen [ar3++] = vreg1;										//записали в U

	gr5--;
	if > goto NEXT_32_1;
	gr5 = [blocks32_surplus];
	gr5;
	if >= goto SURPLUS32_1;
	goto NEXT_ITER;

<NEXT_32_1>

	fpu 0 rep vlen vreg7 = [ar1++];										//ведущая строка
	fpu 0 rep vlen vreg6 = [ar4++];										//текущая строка 1

	fpu 0 .double vreg1 = -vreg5;

	fpu 0 .double vreg3 = vreg7 * .retrive(vreg1);
																		//вычисление строк U
	fpu 0 .double vreg1 = vreg6 + vreg3;
	fpu 0 rep vlen [ar3++] = vreg1;										//записали в U

	gr5--;
	if > goto NEXT_32_1;
	gr5 = [blocks32_surplus];
	gr5;
	if >= goto SURPLUS32_1;
	goto NEXT_ITER;


<SURPLUS32_1>
	vlen = gr5;
	gr5++;

	gr5 = gr5 <<1;
	gr3 = gr1 - gr5;
	gr4 = gr3;

	fpu 0 rep vlen vreg7 = [ar1++];										//ведущая строка
	fpu 0 rep vlen vreg6 = [ar4++];										//текущая строка

	fpu 0 .double vreg1 = -vreg5;
	fpu 0 .double vreg3 = vreg7 * .retrive(vreg1);
																		//вычисление строк U
	fpu 0 .double vreg1 = vreg6 + vreg3;
	fpu 0 rep vlen [ar3++] = vreg1;										//записали в U


	goto NEXT_ITER;


<NEXT_ITER>


	vlen = 31;
	gr5 = [count];
	gr5++;
	gr5++;
	[count] = gr5;
	ar5 = [addr_U];
	ar1 = ar5 + 2;
	ar4 = ar1 + gr1;
	ar3 = ar4;
	[addr_U] = ar3;
	[main_line_addr] = ar1;
	ar2 = [addr_L];
	ar2 = ar2 + 2;
	ar2 = ar2 + gr2;
	[addr_L] = ar2;


	gr5 = [blocks32_surplus];
	gr5;
	if < goto BLOCKS_32;
	gr5--;
	[blocks32_surplus] = gr5;
	gr5 = [blocks4_surplus];
	gr5--;
	[blocks4_surplus] = gr5;
	gr5;
	if >= goto DECISION;

<BLOCKS_4>
	gr5 = 3;
	[blocks4_surplus] = gr5;
	gr5 = [blocks4_count];
	gr5--;
	[blocks4_count] = gr5;
	goto DECISION;


<BLOCKS_32>
	gr5 = 30;
	[blocks32_surplus] = gr5;
	gr5 = [blocks32_count];
	gr5--;
	[blocks32_count] = gr5;
	//goto BLOCKS_4;		
	
	//когда мы после зтого идем сразу в BLOCKS_4 мы не проверяем что в  blocks4_surplus, а нужно проверять, а не просто приравнивать 3

	gr5 = [blocks4_surplus];				//добавила 4 строки вместо одной выше
	gr5--;
	[blocks4_surplus] = gr5;
	goto DECISION;

<DECISION>
	gr3 = [blocks4_count];
	[blocks4_current] = gr3;
	gr4 = [blocks32_count];
	gr4;
	if > delayed goto FULL_START_4;
	gr5 = gr4;
	nul;
	gr3;
	
	if > goto FULL_START;

	gr4 = [blocks4_surplus];
	gr5 = gr4;
	gr4;
	if =0 goto END;
	gr4--;
	if =0 goto ONLY1_START;
	gr4--;
	if =0 goto ONLY2_START;
	gr4--;
	if =0 goto ONLY3_START;
	goto END;


//==========================================================================================================


<FULL_START>
	gr5 = [blocks4_surplus];


	gr7 = [blocks32_surplus];
	gr4 = gr7 + 1;
	gr4 = gr4 <<1;
	vlen = gr7;

	ar5 = buffer;
	ar6= the_two;									//вспомогательные числа для нахождения 1/y
	fpu 0  rep 1 vreg2= [ar6];						// '2'
	gr7= 00400000h;


	fpu 0 rep 1 vreg1 = [ar1];				//y
	fpu 0 rep 1 [ar5++] = vreg1;			// положили у в буфер нужно только для деления
	fpu 0 rep vlen vreg7 = [ar1++]; //		//ведущая строка


    gr6= [--ar5] with false;        //  clear psw flags
	gr6 C<<= 1;                     //  preserve sign
	gr6= gr6 + gr7 noflags;         //  invert exp 1 getting first interpolation
	gr6= not gr6 noflags;           //  invert exp 2
	gr6 C>>= 1;
    [ar5++]= gr6 with gr7= false;
    fpu 0  rep 1 vreg0= [--ar5];

	fpu 0  .double vreg3= - vreg0*vreg1 +vreg2;
    fpu 0  .double vreg0= vreg3 * vreg0;

    fpu 0  .double vreg3= - vreg0*vreg1 +vreg2;
    fpu 0  .double vreg0= vreg3 * vreg0;

    fpu 0 .double vreg3= - vreg0*vreg1 +vreg2;
    fpu 0  .double vreg0= vreg3 * vreg0;

    fpu 0  .double vreg3= - vreg0*vreg1 +vreg2;
    fpu 0  .double vreg0= vreg3 * vreg0;

    fpu 0  .double vreg3= - vreg0*vreg1 +vreg2;
    fpu 0  .double vreg0= vreg3 * vreg0;

	fpu 1 vreg0 = fpu 0 vreg0;
	fpu 2 vreg0 = fpu 0 vreg0;
	fpu 3 vreg0 = fpu 1 vreg0;

	gr4 = gr1 - gr4;

<FULL>
	
	fpu 0 rep 1 vreg4 = [ar4];				//x
	fpu 1 vreg7 = fpu 0 vreg7;				// копируем ведущую строку из fpu 0  в fpu 1
	fpu 0 rep vlen vreg6 = [ar4++];			//текущая строка

	ar4 = ar4+gr4;

	fpu 1 rep 1 vreg4 = [ar4];			//x
	fpu 2 vreg7 = fpu 0 vreg7;			// копируем ведущую строку из fpu 0  в fpu 2
	fpu 3 vreg7 = fpu 1 vreg7;			// копируем ведущую строку из fpu 1  в fpu 3
	fpu 1 rep vlen vreg6 = [ar4++];		//текущая строка

	ar4 = ar4+gr4;

	fpu 2 rep 1 vreg4 = [ar4];									//x
	fpu 2 rep vlen vreg6 = [ar4++];								//текущая строка

	ar4 = ar4+gr4;

	fpu 3 rep 1 vreg4 = [ar4];									//x
	fpu 3 rep vlen vreg6 = [ar4++];								//текущая строка

	ar4 = ar4 +gr4;
    //  (1/y)


    fpu 0  .double vreg1= vreg4 * vreg0;     // x/y = x*(1/y)
	fpu 1  .double vreg1= vreg4 * vreg0;     // x/y = x*(1/y)
	fpu 2  .double vreg1= vreg4 * vreg0;     // x/y = x*(1/y)
	fpu 3  .double vreg1= vreg4 * vreg0;     // x/y = x*(1/y)



	fpu 0 rep 1 [ar2++gr2] = vreg1;			//элемент L
	fpu 1 rep 1 [ar2++gr2] = vreg1;			//элемент L
	fpu 2 rep 1 [ar2++gr2] = vreg1;			//элемент L
	fpu 3 rep 1 [ar2++gr2] = vreg1;			//элемент L

	fpu 0 .double vreg1 = -vreg1;
	fpu 1 .double vreg1 = -vreg1;
	fpu 2 .double vreg1 = -vreg1;
	fpu 3 .double vreg1 = -vreg1;

	fpu 0 .double vreg3 = vreg7 * .retrive(vreg1);
	fpu 1 .double vreg3 = vreg7 * .retrive(vreg1);
	fpu 2 .double vreg3 = vreg7 * .retrive(vreg1);
	fpu 3 .double vreg3 = vreg7 * .retrive(vreg1);
																//вычисления  строк U
	fpu 0 .double vreg1 = vreg6 + vreg3;
	fpu 1 .double vreg1 = vreg6 + vreg3;
	fpu 2 .double vreg1 = vreg6 + vreg3;
	fpu 3 .double vreg1 = vreg6 + vreg3;


	gr3 = gr4;

	fpu 0 rep vlen [ar3++] = vreg1;				//записали в U
	ar3 = ar3+gr3;

	fpu 1 rep vlen [ar3++] = vreg1;				//записали в U
	ar3 = ar3+gr3;

	fpu 2 rep vlen [ar3++] = vreg1;				//записали в U
	ar3 = ar3+gr3;

	fpu 3 rep vlen [ar3++] = vreg1;
	ar3 = ar3+gr3;

	gr3 = [blocks4_current];
	gr3--;
	[blocks4_current] = gr3;
	gr3;
	
	if > goto FULL;
	gr5--;	
	if =0 goto ONLY1;
	gr5--;
	if =0 goto ONLY2;
	gr5--;
	if =0 goto ONLY3;
		
	goto NEXT_ITER;



<ONLY3_START>
	gr4 = 8;
	vlen = 3;

	ar5 = buffer;
	ar6= the_two;									//вспомогательные числа для нахождения 1/y (возможно можно считать один раз!)
	fpu 0  rep 1 vreg2= [ar6];			 // '2'
	gr7= 00400000h;

	fpu 0 rep 1 vreg1 = [ar1];			//y
	fpu 0 rep 1 [ar5++] = vreg1;		// положили у в буфер нужно только для деления
	fpu 0 rep vlen vreg7 = [ar1++];		//ведущая строка

    gr6= [--ar5] with false;        //  clear psw flags
	gr6 C<<= 1;                     //  preserve sign
	gr6= gr6 + gr7 noflags;         //  invert exp 1 getting first interpolation
	gr6= not gr6 noflags;           //  invert exp 2
	gr6 C>>= 1;
    [ar5++]= gr6 with gr7= false;
    fpu 0  rep 1 vreg0= [--ar5];

	fpu 0  .double vreg3= - vreg0*vreg1 +vreg2;
    fpu 0  .double vreg0= vreg3 * vreg0;

    fpu 0  .double vreg3= - vreg0*vreg1 +vreg2;
    fpu 0  .double vreg0= vreg3 * vreg0;

    fpu 0 .double vreg3= - vreg0*vreg1 +vreg2;
    fpu 0  .double vreg0= vreg3 * vreg0;

    fpu 0  .double vreg3= - vreg0*vreg1 +vreg2;
    fpu 0  .double vreg0= vreg3 * vreg0;

    fpu 0  .double vreg3= - vreg0*vreg1 +vreg2;
    fpu 0  .double vreg0= vreg3 * vreg0;

	fpu 1 vreg0 = fpu 0 vreg0;
	fpu 2 vreg0 = fpu 0 vreg0;

	gr4 = gr1 - gr4;

<ONLY3>
	
	fpu 0 rep 1 vreg4 = [ar4];			//x
	fpu 1 vreg7 = fpu 0 vreg7;			// копируем ведущую строку из fpu 0  в fpu 1
	fpu 0 rep vlen vreg6 = [ar4++];		//текущая строка

	ar4 = ar4+gr4;

	fpu 1 rep 1 vreg4 = [ar4];			//x
	fpu 2 vreg7 = fpu 0 vreg7;			// копируем ведущую строку из fpu 0  в fpu 2
	fpu 1 rep vlen vreg6 = [ar4++];		//текущая строка

	ar4 = ar4+gr4;

	fpu 2 rep 1 vreg4 = [ar4];									//x
	fpu 2 rep vlen vreg6 = [ar4++];								//текущая строка


    //  (1/y)
    fpu 0  .double vreg1= vreg4 * vreg0;     // x/y = x*(1/y)
	fpu 1  .double vreg1= vreg4 * vreg0;     // x/y = x*(1/y)
	fpu 2  .double vreg1= vreg4 * vreg0;     // x/y = x*(1/y)

	fpu 0 rep 1 [ar2++gr2] = vreg1;			//элемент L
	fpu 1 rep 1 [ar2++gr2] = vreg1;			//элемент L
	fpu 2 rep 1 [ar2++gr2] = vreg1;			//элемент L
	
	
	fpu 0 .double vreg1 = -vreg1;
	fpu 1 .double vreg1 = -vreg1;
	fpu 2 .double vreg1 = -vreg1;

	fpu 0 .double vreg3 = vreg7 * .retrive(vreg1);
	fpu 1 .double vreg3 = vreg7 * .retrive(vreg1);
	fpu 2 .double vreg3 = vreg7 * .retrive(vreg1);
																//вычисления  строк U
	fpu 0 .double vreg1 = vreg6 + vreg3;
	fpu 1 .double vreg1 = vreg6 + vreg3;
	fpu 2 .double vreg1 = vreg6 + vreg3;

	gr3 = gr4;
	
	fpu 0 rep vlen [ar3++] = vreg1;				//записали в U
	ar3 = ar3+gr3;
	
	fpu 1 rep vlen [ar3++] = vreg1;				//записали в U
	ar3 = ar3+gr3;
	fpu 2 rep vlen [ar3++] = vreg1;				//записали в U
	goto NEXT_ITER;

<ONLY2_START>
	gr4 = 6;
	vlen = 2;

	ar5 = buffer;
	ar6= the_two;									//вспомогательные числа для нахождения 1/y (возможно можно считать один раз!)
	fpu 0  rep 1 vreg2= [ar6];      //  '2'
	gr7= 00400000h;


	fpu 0 rep 1 vreg1 = [ar1];			//y
	fpu 0 rep 1 [ar5++] = vreg1;		// положили у в буфер нужно только для деления
	fpu 0 rep vlen vreg7 = [ar1++];		//ведущая строка

    gr6= [--ar5] with false;        //  clear psw flags
	gr6 C<<= 1;                     //  preserve sign
	gr6= gr6 + gr7 noflags;         //  invert exp 1 getting first interpolation
	gr6= not gr6 noflags;           //  invert exp 2
	gr6 C>>= 1;
    [ar5++]= gr6 with gr7= false;
    fpu 0  rep 1 vreg0= [--ar5];    //  ~

	fpu 0  .double vreg3= - vreg0*vreg1 +vreg2;
    fpu 0  .double vreg0= vreg3 * vreg0;

    fpu 0  .double vreg3= - vreg0*vreg1 +vreg2;
    fpu 0  .double vreg0= vreg3 * vreg0;

    fpu 0 .double vreg3= - vreg0*vreg1 +vreg2;
    fpu 0  .double vreg0= vreg3 * vreg0;

    fpu 0  .double vreg3= - vreg0*vreg1 +vreg2;
    fpu 0  .double vreg0= vreg3 * vreg0;

    fpu 0  .double vreg3= - vreg0*vreg1 +vreg2;
    fpu 0  .double vreg0= vreg3 * vreg0;

	fpu 1 vreg0 = fpu 0 vreg0;
	fpu 2 vreg0 = fpu 0 vreg0;
	gr4 = gr1 - gr4;

<ONLY2>
	
	fpu 0 rep 1 vreg4 = [ar4];			//x
	fpu 1 vreg7 = fpu 0 vreg7;			// копируем ведущую строку из fpu 0  в fpu 1
	fpu 0 rep vlen vreg6 = [ar4++];		//текущая строка

	ar4 = ar4+gr4;

	fpu 1 rep 1 vreg4 = [ar4];			//x
	fpu 1 rep vlen vreg6 = [ar4++];		//текущая строка


    //  (1/y)
    fpu 0  .double vreg1= vreg4 * vreg0;     // x/y = x*(1/y)
	fpu 1  .double vreg1= vreg4 * vreg0;     // x/y = x*(1/y)


	fpu 0 rep 1 [ar2++gr2] = vreg1;			//элемент L
	fpu 1 rep 1 [ar2++gr2] = vreg1;			//элемент L

	fpu 0 .double vreg1 = -vreg1;
	fpu 1 .double vreg1 = -vreg1;

	fpu 0 .double vreg3 = vreg7 * .retrive(vreg1);
	fpu 1 .double vreg3 = vreg7 * .retrive(vreg1);
																//вычисления  строк U
	fpu 0 .double vreg1 = vreg6 + vreg3;
	fpu 1 .double vreg1 = vreg6 + vreg3;

	gr3 = gr4;

	fpu 0 rep vlen [ar3++] = vreg1;				//записали в U
	ar3 = ar3+gr3;

	fpu 1 rep vlen [ar3++] = vreg1;				//записали в U
	goto NEXT_ITER;

<ONLY1_START>

	gr4 = 4;
	vlen = 1;

	ar5 = buffer;
	ar6= the_two;									//вспомогательные числа для нахождения 1/y (возможно можно считать один раз!)
	fpu 0  rep 1 vreg2= [ar6];      //  '2'
	gr7= 00400000h;


	fpu 0 rep 1 vreg1 = [ar1];			//y
	fpu 0 rep 1 [ar5++] = vreg1;		// положили у в буфер нужно только для деления
	fpu 0 rep vlen vreg7 = [ar1++];		//ведущая строка



    gr6= [--ar5] with false;        //  clear psw flags
	gr6 C<<= 1;                     //  preserve sign
	gr6= gr6 + gr7 noflags;         //  invert exp 1 getting first interpolation
	gr6= not gr6 noflags;           //  invert exp 2
	gr6 C>>= 1;
    [ar5++]= gr6 with gr7= false;
    fpu 0  rep 1 vreg0= [--ar5];    //  ~

	fpu 0  .double vreg3= - vreg0*vreg1 +vreg2;
    fpu 0  .double vreg0= vreg3 * vreg0;

    fpu 0  .double vreg3= - vreg0*vreg1 +vreg2;
    fpu 0  .double vreg0= vreg3 * vreg0;

    fpu 0 .double vreg3= - vreg0*vreg1 +vreg2;
    fpu 0  .double vreg0= vreg3 * vreg0;

    fpu 0  .double vreg3= - vreg0*vreg1 +vreg2;
    fpu 0  .double vreg0= vreg3 * vreg0;

    fpu 0  .double vreg3= - vreg0*vreg1 +vreg2;
    fpu 0  .double vreg0= vreg3 * vreg0;

	gr4 = gr1 - gr4;

<ONLY1>

	fpu 0 rep 1 vreg4 = [ar4];			//x
	fpu 0 rep vlen vreg6 = [ar4++];		//текущая строка

    //  (1/y)

    fpu 0  .double vreg1= vreg4 * vreg0;     // x/y = x*(1/y)
	fpu 0 rep 1 [ar2++gr2] = vreg1;			//элемент L
	fpu 0 .double vreg1 = -vreg1;
	fpu 0 .double vreg3 = vreg7 * .retrive(vreg1);																	//вычисления  строк U
	fpu 0 .double vreg1 = vreg6 + vreg3;

	fpu 0 rep vlen [ar3++] = vreg1;				//записали в U
	goto NEXT_ITER;


<END>

	pop ar6,gr6;
	pop ar5,gr5;									//эпилог
	pop ar4,gr4;
	pop ar3,gr3;
	pop ar2,gr2;
	pop ar1,gr1;

return;
end ".text";
