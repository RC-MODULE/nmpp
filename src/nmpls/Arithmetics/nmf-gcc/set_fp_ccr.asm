
global _set_fp_ccr : label;

begin ".text_int"

ccr_switch : label;

<_set_fp_ccr>

	gr7 = [ar7 - 3];
	gr7 <<= 29;		//	на случай, если передадут бяку
	gr7 >>= 27;		//	gr7 = param * 4
	ar5 = gr7;
	delayed goto ar5 + ccr_switch;
		sir = fp_ccr;
		gr7 = sir;
<ccr_switch>
	//	0
	delayed return;
		set fp_wait;
		set fp_round_to_nearest;
		vnul;
	//	1
	delayed return;
		set fp_branch;
		set fp_round_to_nearest;
		vnul;
	//	2
	delayed return;
		set fp_wait;
		set fp_round_down;
		vnul;
	//	3
	delayed return;
		set fp_branch;
		set fp_round_down;
		vnul;
	//	4
	delayed return;
		set fp_wait;
		set fp_round_up;
		vnul;
	//	5
	delayed return;
		set fp_branch;
		set fp_round_up;
		vnul;
	//	6
	delayed return;
		set fp_wait;
		set fp_round_to_zero;
		vnul;
	//	7
	delayed return;
		set fp_branch;
		set fp_round_to_zero;
		vnul;

end ".text_int";

