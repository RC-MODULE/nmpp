
default: config_mc12101_1_gcc
	

all: config_mc12101_0_gcc config_mc12101_1_gcc run outdir
	

config_mc12101_1_gcc:
	testperf config -i ../../include -b make_mc12101_nmpu1-gcc-ld --point fixed	

run:


all_mc12101:
	testperf config -i ../../include -b make_mc12101_nmpu0
	testperf config -i ../../include -b make_mc12101_nmpu1 --point fixed
	testperf run

config_mc5103:
	testperf config -i ../../include -b make_mc5103 --point fixed

config_mc12705:
	testperf config -i ../../include -b make_mc12705

config_mc12101_0:
	testperf config -i ../../include -b make_mc12101_nmpu0 -p floating

config_mc12101_1:
	testperf config -i ../../include -b make_mc12101_nmpu1 --point fixed

config_mc12101_0_gcc:
	testperf config -i ../../include -b make_mc12101_nmpu0-gcc-ld

config_mc12101_1_gcc:
	testperf config -i ../../include -b make_mc12101_nmpu1-gcc-ld --point fixed	

run:
	testperf run

kill:
	testperf del

outdir:
	testperf outdir