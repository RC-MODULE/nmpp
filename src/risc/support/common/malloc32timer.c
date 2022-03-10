#include "time.h"
#include "malloc32.h"
static clock_t t0,t1;
extern struct NmppsMallocSpec nmppsMallocSpec;

void nmppsMallocTimerStart(){
	nmppsMallocSpec.time=0;	
	t0=clock();
}

void nmppsMallocTimerResume(){
	t0=clock();
}

void nmppsMallocTimerStop(){
	t1=clock();
	nmppsMallocSpec.time+=t1-t0;
}