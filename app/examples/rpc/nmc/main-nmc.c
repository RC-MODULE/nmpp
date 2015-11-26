#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <easynmc/easynmc.h>
#include <easynmc/aura.h>
#include <nmpp.h>


#include "aura-exports.h"
#include <rpc-nmc.h>

unsigned int *pinmux  = (unsigned int *) 0x0800CC21;
unsigned int *port    = (unsigned int *) 0x0800A403;
unsigned int *ddr     = (unsigned int *) 0x0800A407;

void aura_panic() { 
	for (;;) { 
		*port ^= (1<<6);	
		*port ^= (1<<7);	
	} ;
}

void aura_hexdump (char *desc, unsigned int *addr, int len) {
	int i; 
	for (i=0; i<len; i++) { 
		printf("0x%x: 0x%x\n", ((unsigned int)addr << 2), *addr);
		addr++;
	}
}

extern struct aura_object g_aura_eof;
int main(int argc, char **argv)
{
	printf("NMC: Aura RPC demo \n");
	aura_init();
	aura_loop_forever();

	g_aura_eof.id=1;
}

