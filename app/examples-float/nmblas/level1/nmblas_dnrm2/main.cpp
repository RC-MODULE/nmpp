#include "nmblas.h"
#include "stdio.h"
#define SIZE 10
double src[SIZE];

int main(){
	printf("-");
	for(int i=0;i<SIZE;i++){
		src[i] = i;
	}
	
	double result = nmblas_dnrm2(SIZE,src,1);
	return 0;
}

