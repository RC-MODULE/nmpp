#include "nmblas.h"
#define SIZE 10
double src[SIZE]={1,2,3,4,5,6,7,8,9,10};

int main(){
	for(int i=0;i<SIZE;i++){
		src[i] = i;
	}
	
	double result = nmblas_dasum(SIZE,src,1);
	return result;
}

