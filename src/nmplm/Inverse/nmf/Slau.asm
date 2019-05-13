data ".data"
	addr_L : word;
	addr_U : word;
	addr_x : word;
	addr_y : word;
	num_N : word;
	my_zero : long = 0000000000000000;
	buffer : long = 0;
	.align;
	the_two : word[2] = (0, 1073741824);
end ".data";

begin ".text"
global _nmppmLUResolve_64f : label;
<_nmppmLUResolve_64f>

	push ar1,gr1;
	push ar2,gr2;									// пролог
	push ar3,gr3;
	push ar4,gr4;
	push ar5,gr5;
	push ar6,gr6;

	ar6 = ar7 -14;

	ar1 = [--ar6];       							// L
	[addr_L] = ar1;
	ar2 = [--ar6];       							// U
	[addr_U] = ar2;
	ar3 = [--ar6];       							// b
	ar4 = [--ar6];									//x
	[addr_x] = ar4;
	ar5 = [--ar6];									//y
	[addr_y] = ar5;

	gr1 = [--ar6];									// N
	gr2 = gr1;
	[num_N] = gr1;
	gr2--;
	gr1 = gr1 << 1;


	//ar5 для записи в вектор y, для чтения будет ar2
	ar2 = my_zero;
	fpu 0 rep 1 vreg7 = [ar2];							//считали 0 для того, что бы использовать .retrive для свертки вектора 
	fpu 0 .double vreg4 = vreg7;
	ar2 = ar5;

	fpu 0 rep 1 vreg0 = [ar3++];						//первый злемент вектора у равен первому злементу вектора b 
	fpu 0 rep 1 [ar5++] = vreg0;

	vlen = 0;			//начинаем с 1 потому что нужно читать на один злемент в L меньше (первый злемент b уже записан)
	gr3 = 0;
<M1>
	ar1 = [addr_L];
	ar1 = ar1 + gr1;						//вычисляем адрес L для чтения
	[addr_L] = ar1;
	ar2 = [addr_y];
			
	
	fpu 0 rep vlen vreg0 = [ar1++];		//считали строку L
	fpu 0 rep vlen vreg1 = [ar2++];		//считали вектор y

	fpu 0 .double vreg2 = vreg0*vreg1;
<M2>
	fpu 0 .double vreg4 = vreg4 +.retrive(vreg2);
	gr3;
	if> delayed goto M2;
		gr3--;
		nul;	


	fpu 0 rep 1 vreg3 = [ar3++];			//считали злемент вектора b
	fpu 0 .double vreg4 = -vreg4 + vreg3;
	fpu 0 rep 1 [ar5++] = vreg4;		//записали лемент y

	gr3 = vlen;
	gr3++;
	vlen = gr3;
	fpu 0 .double vreg4 = vreg7;

	gr2--;
	if> goto M1;




//второй зтап, нахождение вектора x 
//	идем снизу вверх, адресa вектора y находятся в конце - ar2(для чтения)
	gr2 = [num_N];
	gr7 = gr1;
    with gr1 = gr2 *: gr7;						//gr1 = gr1*gr2; результат лежит в gr7
.repeat 15;
    with gr1 = gr2 * gr7;
.endrepeat;
	gr2--;
	gr1 = gr7;

	gr4 = [num_N];
	gr4 = gr4 <<1;
	ar4 = ar4 + gr4;							//поставили указатель на x в конец массива
	[addr_x] = ar4;
	ar3 = ar4;
//  адрес вектора х лежит в ar4(для чтения) ar3(для записи)

	ar1 = [addr_U];								//ar1 будет адресом по U
	ar1 = ar1 + gr1;							//поставили указатель в конец массива
	[addr_U] = ar1;

	gr1 = [num_N];
	gr1 = gr1<<1;
	gr1 = -gr1;

	ar2 = ar5;

	fpu 0 rep 1 vreg4 = [--ar2];				// считали y[n]	//последний злемент вектора x равен y[n]/последний злемент U
	

	ar5 = buffer;
	ar6= the_two;								//вспомогательные числа для нахождения y[n]/последний злемент U
	fpu 0  rep 1 vreg2= [ar6];      			//  '2'
	gr7= 00400000h;


	fpu 0 rep 1 vreg1 = [--ar1];				//считали U последний злемент
	fpu 0 rep 1 [ar5++] = vreg1;				// положили U последний злемент в буфер нужно только для деления


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

    //   y[n]/последний злемент U  

    fpu 0  .double vreg1 = vreg4 * vreg0;     	// y[n]/последний злемент U
	fpu 0 rep 1 [--ar3] = vreg1;				//записали последний злемент х

	ar1 = [addr_U];
	ar1 = ar1 + gr1;
	[addr_U] = ar1;
	ar4 = [addr_x];

	fpu 0 .double vreg4 = vreg7;

	vlen = 0;
	gr3 = 0;
<M3> 
	fpu 0 rep vlen vreg6 = [--ar4];				//считали злементы х
	fpu 0 rep vlen vreg5 = [--ar1];				//считали строку U
	fpu 0 .double vreg6 = vreg6*vreg5;			//умножили вектор х на строку U

<M4>
	fpu 0 .double vreg4 = vreg4 +.retrive(vreg6); 
	gr3;
	if> delayed goto M4;
		gr3--;
		nul;

	fpu 0 .double vreg4 = -vreg4;

	fpu 0 rep 1 vreg5 = [--ar2];				//злемент вектора y
	fpu 0 .double vreg4 = vreg5 + vreg4;		//вычли из злемента вектора у сумму произведений

	ar5 = buffer;
	ar6= the_two;								//вспомогательные числа для нахождения y[n]/последний злемент U
	fpu 0  rep 1 vreg2= [ar6];      			//  '2'
	gr7= 00400000h;

	fpu 0 rep 1 vreg1 = [--ar1];				//считали злемент U 
	fpu 0 rep 1 [ar5++] = vreg1;				// положили злемент U в буфер нужно только для деления


    gr6= [--ar5] with false;       				//  clear psw flags
	gr6 C<<= 1;                     			//  preserve sign
	gr6= gr6 + gr7 noflags;         			//  invert exp 1 getting first interpolation
	gr6= not gr6 noflags;           			//  invert exp 2
	gr6 C>>= 1;
    [ar5++]= gr6 with gr7= false;
    fpu 0  rep 1 vreg0= [--ar5];    			//  ~

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

    //   y[n]/последний злемент U  

    fpu 0  .double vreg1 = vreg4 * vreg0;     	// (сумма произведений злементов U и у) * 1/ злемент U
	fpu 0 rep 1 [--ar3] = vreg1;				//записали злемент х

	ar4 = [addr_x];
	ar1 = [addr_U];
	ar1 = ar1 + gr1;
	[addr_U] = ar1;

	fpu 0 .double vreg4 = vreg7;

	gr3 = vlen;
	gr3++;
	vlen = gr3;

	gr2--;
	if> goto M3;

<END>

	pop ar6,gr6;
	pop ar5,gr5;									//эпилог
	pop ar4,gr4;
	pop ar3,gr3;
	pop ar2,gr2;
	pop ar1,gr1;

return;
end ".text";
