#include <time.h>
#include "nmplv.h"
#include <stdio.h>
#include "nmpls.h"
#include "nmplm.h"

#define SIZE 1024
#pragma data_section ".heap"
	long buffer0[SIZE];
	long state0[128];
#pragma data_section ".heap1"
	long buffer1[SIZE];
	long state1[128];
#pragma data_section ".heap2"
	long buffer2[SIZE];
	long state2[128];
#pragma data_section ".heap3"
	long buffer3[SIZE];
	long state3[128];
#pragma data_section ".heap4"
	long buffer4[SIZE];
	long state4[128];
#pragma data_section ".heap5"
	long buffer5[SIZE];
	long state5[128];

int* buffer[6]	= {(int*)buffer0,(int*)buffer1,(int*)buffer2,(int*)buffer3,(int*)buffer4,(int*)buffer5};

 extern "C" {
	unsigned run5streams(int* ram, int* wfifo, int* data, int* afifo, int* scalar, int size);
 };
int main()
{  
		
	int size=102400;
	clock_t t0,t1,best=0xFFFFFF;
	int n=0;
//	t0=clock();
//		run5streams( buffer[5], buffer[2], buffer[4], buffer[1], buffer[0], size);
//		t1=clock();
//		return t1-t0;
//		
//	for(int i=0; i<10000; i++){
//		run5streams( buffer[5], buffer[2], buffer[4], buffer[1], buffer[0], size);
//		//printf("%d\n",n++);
//	}
//	return 123;
//	
	while(1){
		t0=clock();
		run5streams( buffer[5], buffer[2], buffer[4], buffer[1], buffer[0], size);
		t1=clock();
		printf("%d\n",t1-t0);
	}
	return 1;
	
	for(int ram=0; ram<6; ram++){
		for(int wfifo=0; wfifo<6; wfifo++){		
			for(int data=0; data<6; data++){
				for(int afifo=0; afifo<6; afifo++){
					for(int scalar=0; scalar<6; scalar++){
			
						t0=clock();
						run5streams( buffer[ram], buffer[wfifo], buffer[data], buffer[afifo], buffer[scalar], size);
						t1=clock();
				
						if ((t1-t0)<best){
							best=t1-t0;
						}
						//float t=(t1-t0)*2.0/size;
						//printf("[%d-%d-%d-%d-%d]\t%.3f\n",ram,wfifo,data,afifo,scalar,t);
					}
					printf("[%d-%d-%d-%d]\t%.3f\n",ram,wfifo,data,afifo,0);
				}
			}
		}
		
	}
	
	float t=best*2.0/size;
	printf("[best time %.3f\n",t);
			
	
	
	
	
	return t1-t0; 
} 

