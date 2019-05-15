

all:
	testperf config -i ../../include -b make_mc12101_nmpu0
	testperf config -i ../../include -b make_mc12101_nmpu1 --point fixed
	testperf run

config0:
	testperf config -i ../../include -b make_mc12101_nmpu0

config1:
	testperf config -i ../../include -b make_mc12101_nmpu1 --point fixed

run:
	testperf run

kill:
	testperf kill

outdir:
	testperf outdir