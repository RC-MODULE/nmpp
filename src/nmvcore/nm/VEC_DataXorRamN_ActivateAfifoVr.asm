    //--------------------------------------------------------------------
macro M(N)
    nul;
    rep N ram = [ar1];
	delayed return;
        rep N data = [ar0++gr0] with data xor ram;
        rep N with vsum, activate afifo, vr;
        rep N [ar6++gr6] = afifo;
end M;

    //--------------------------------------------------------------------
begin ".text_nmvcore"

    //--------------------------------------------------------------------
    // Вход:
    //      ar0 - входной массив.
    //      gr0 - шаг для входных данных.
    //      ar6 - выходной массив.
    //      gr6 - шаг для выходных данных.
    //      gr5 - размер входного массива в 64-битовых элементах.
    //      ar1 - вектор - константа.
    // Изменяет регистры: ar0, ar6.
    //--------------------------------------------------------------------
local lab_rep0: label;
global VEC_DataXorRamN_ActivateAfifoVr: label;
<VEC_DataXorRamN_ActivateAfifoVr>
.branch;
    push ar2,gr2 with gr2 = gr5 << 27;
    push ar5,gr5 with gr5 >>= 5;

    if =0 delayed goto lab_repN with gr2 >>= 27;
        ar2 = lab_rep0 with gr5--;

    rep 32 ram = [ar1];

<lab_next_rep32>
    rep 32 data = [ar0++gr0] with data xor ram;
    if <>0 delayed goto lab_next_rep32 with gr5--;
        rep 32 with vsum, activate afifo, vr;
        rep 32 [ar6++gr6] = afifo;

<lab_repN>
    gr5 = gr2 << 1;
    gr2 <<= 2;
    gr2 = gr2 + gr5;
    ar2 += gr2;
    delayed goto ar2; 
        pop ar5,gr5;
        pop ar2,gr2;

<lab_rep0>
    delayed return;
        nul;
        nul;
        nul;
    nul;
    nul;
    M(1);
    M(2);
    M(3);
    M(4);
    M(5);
    M(6);
    M(7);
    M(8);
    M(9);
    M(10);
    M(11);
    M(12);
    M(13);
    M(14);
    M(15);
    M(16);
    M(17);
    M(18);
    M(19);
    M(20);
    M(21);
    M(22);
    M(23);
    M(24);
    M(25);
    M(26);
    M(27);
    M(28);
    M(29);
    M(30);
    M(31);
return;
.wait;
        
end ".text_nmvcore";