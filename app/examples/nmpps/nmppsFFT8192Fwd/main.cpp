#include "fft.h"
#include "nmpp.h"
#include <time.h>
#include <stdio.h>

#define FFT_SIZE 8192
//8192

//#define SPEEDTEST ON

#ifdef SPEEDTEST
	#define BUF_SIZE FFT8192_TBL0_SIZE64+FFT8192_TBL1_SIZE64
	
	#pragma data_section ".data_bank0"
		nm64s buffer0[BUF_SIZE];
		nm64s tblFwdCos0[1]; // dummy table
		nm64s tblFwdCos1[1]; // dummy table
		nm64s tblFwdSin0[1]; // dummy table
		nm64s tblFwdSin1[1]; // dummy table
		
	#pragma data_section ".data_bank1"
		nm64s buffer1[BUF_SIZE];
		
	#pragma data_section ".data_bank2"
		nm64s buffer2[BUF_SIZE];
		
	#pragma data_section ".data_bank3"
		nm64s buffer3[BUF_SIZE];
#else		
	// 1-232003        147901
	// 1-232103        147898
	// 1-323002        147900
	// 1-323102        147948
	// 2-131003        147900
	// 2-131203        147898
	// 2-313001        147901
	// 2-313201        147898
	// 3-121002        147901
	// 3-121302        147898
	// 3-212001        147901
	// 3-212301        147898

	#pragma data_section ".data_bank0"
		
		nm64s  tblFwdSin0[FFT8192_TBL0_SIZE64];
		nm64s  buffer1 [1];
	#pragma data_section ".data_bank1"
		nm64s  buffer0   [FFT_SIZE];
		nm64s  tblFwdCos1[FFT8192_TBL1_SIZE64];
		
	#pragma data_section ".data_bank2"
		nm64s  buffer2   [FFT_SIZE];
		nm64s  tblFwdCos0[FFT8192_TBL0_SIZE64];
	#pragma data_section ".data_bank3"
		nm64s  buffer3   [FFT_SIZE];
		nm64s  tblFwdSin1[FFT8192_TBL1_SIZE64];
		

#endif

#pragma data_section ".data_bank0"	
	
	

	
	
int memoryOverflow(int i0, int i1, int i2, int i3, int i4, int i5, int i6, int i7) 
{
	int mem[4]={0,0,0,0};
	mem[i0]+=8192;
	mem[i1]+=8192;
	mem[i2]+=8192;
	mem[i3]+=8192;
	mem[i4]+=FFT8192_TBL0_SIZE64;
	mem[i5]+=FFT8192_TBL1_SIZE64;
	mem[i6]+=FFT8192_TBL0_SIZE64;
	mem[i7]+=FFT8192_TBL1_SIZE64;
	if (mem[0]>16536) return true;
	if (mem[1]>16536) return true;
	if (mem[2]>16536) return true;
	if (mem[3]>16536) return true;
	return false;
}
int speedTest(){

	clock_t t0,t1,dt,bestTime=0xFFFFF;
	unsigned int crc = 0;
	
	
	nm64s* buf[4]={buffer0, buffer1, buffer2, buffer3};

	NmppsFFTSpec spec;
	nmppsFFT8192FwdInit(&spec,SKIP_SINCOS,(nm64s*)buffer0,(nm64s*)buffer0,(nm64s*)buffer0,(nm64s*)buffer0,(nm64s*)buffer0,(nm64s*)buffer0);
	int bestRoute;
	for(int i0=0; i0<4; i0++){
		nm32sc* src=(nm32sc*)buf[i0];
		for(int i1=0; i1<4; i1++){
			nm32sc* dst=(nm32sc*)buf[i1];
			for(int i2=0; i2<4; i2++){
				spec.buffer[0]=(nm32sc*)buf[i2];
				for(int i3=0; i3<4; i3++){
					spec.buffer[1]=(nm32sc*)buf[i3];
					for(int i4=0; i4<  4; i4++){
						spec.fftTable[0]=buf[i4];
						for(int i5=0; i5<4; i5++){
							spec.fftTable[1]=buf[i5];
							for(int i6=0; i6<  4; i6++){
								spec.fftTable[2]=buf[i6];
								for(int i7=0; i7<4; i7++){
									spec.fftTable[3]=buf[i7];
									
									if (memoryOverflow(i0, i1, i2, i3, i4, i5, i6, i7)) continue;
									
									
									t0=clock();
									dt=nmppsFFT8192Fwd(dst,dst,&spec); 
									t1=clock();
									dt =t1-t0;
									if (dt<=bestTime){
										bestTime=dt;
										printf("%d%d%d%d%d%d%d%d\t%d\n",i0,i1,i2,i3,i4,i5,i6,i7, dt);		
									}
									
									//if (dt<155000)
									//	printf("%d%d%d%d%d%d%d%d\t%d\n",i0,i1,i2,i3,i4,i5,i6,i7, dt);		
								}
							}
						}
					}
				}
			}
		}
	}

	printf("Best time=%d; %d/8192/2=%f ; Best route = %07x \n",bestTime,bestTime,float(bestTime)/8192/2,bestRoute);
	return bestTime;
}



int selfTest(){
	clock_t t,t0,t1;
	unsigned int crc = 0;

		
	NmppsFFTSpec specFwd;

	
	//t0=clock();
	nmppsFFT8192FwdInit(&specFwd,0,buffer2,buffer3,tblFwdCos0,tblFwdCos1,tblFwdSin0,tblFwdSin1);
	//t1=clock();
	//return t1-t0;
	nm32sc* src = (nm32sc*)buffer0;	
	nm32sc* dst = src;	
		
	nmppsRandUniform_64s((nm64s*)src,FFT_SIZE);
	nmppsRShiftC_32s((nm32s*)src,24,(nm32s*)src,2*FFT_SIZE);
		
	t0=clock();
	t=nmppsFFT8192Fwd (src,dst,&specFwd); 

	//return t;
	t1=clock();
	t=t1-t0;
	crc=nmppsCrc_32s((nm32s*)src,8192*2)-0xcd7cd700;
	if (crc!=0)
		return 0xBEDABEDA;
	printf("time=%d; crc=%d\n",t,crc);
	return t;
	
}
// 6406: 147882
// soc : 176697



int main()
{
     
	//return 123;
	
	#ifdef SPEEDTEST
		return speedTest();
	#else 
		return selfTest();
	#endif
	
}
	