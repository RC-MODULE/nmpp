#include <aura/aura.h>
#include <ion/ion.h>
#include "nmpp.h"

struct aura_node *n;
int main() {

	slog_init(NULL, 0);

	int ret; 
	n = aura_open("nmc", "./rpc-demo.abs");
	if (!n) {
		slog (0, SLOG_ERROR, "Failed to open node");
		exit(1);
	}
	aura_wait_status(n, AURA_STATUS_ONLINE);

	
	int src0[16];
	int src1[16];
	int dst[16];
	int i=0;
	for(i=0; i<16; i++){
		src0[i]=i;
		src1[i]=i-15;
	}
	nmppsAdd_32s(src0,src1,dst,16);
	nmppsAbs_32s(dst,dst,16);

	for(i=0; i<16; i++){
		printf("%d\r\n",dst[i]);
	}
	printf("===========\n");
	aura_close(n);
	
	slog (0, SLOG_INFO, "Finished");

	return 0;
}


