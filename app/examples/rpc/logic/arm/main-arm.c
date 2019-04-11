#define __STDC_FORMAT_MACROS
#include <aura/aura.h>
#include <ion/ion.h>
#include "nmpp.h"
#include "fft.h"

struct aura_node *n;
int main() {

	printf("START-%s\n", aura_get_version());
	slog_init(NULL, 0);
       sleep(1);
	int ret; 
		n = aura_open("nmc", "./rpc-demo.abs");
	if (!n) {
		printf("ERROR:Failed to open node\n");
		slog (0, SLOG_ERROR, "Failed to open node");
		exit(1);
	}
	printf("START-1\n");
	aura_wait_status(n, AURA_STATUS_ONLINE);

	printf("START-2\n");
	static signed char  src0_8s[256] ,    src1_8s[256];
	static signed short src0_16s[256],    src1_16s[256];
	static signed int   src0_32s[2*2048], src1_32s[256];
	static long long    src0_64s[256], src1_64s[256];
	static signed char  dst_8s[256];
	signed short dst_16s[256];
	signed int 	 dst_32s[2*2048];
	signed long long dst_64s[256];
	
	int i=0;

	for(i=0; i<256; i++){
		src0_8s[i] =i;  
		src0_16s[i]=i;  
		src0_32s[i]=i;  
		src0_64s[i]=i;  
		            
		src1_8s[i] =8-i;
		src1_16s[i]=8-i;
		src1_32s[i]=8-i;
		src1_64s[i]=8-i;
	}
	
	unsigned crc=-1;
	
	nmppsRShiftC_8s ((nm8s* )src0_8s ,1,(nm8s* )dst_8s ,16);				nmppsCrcAcc_8s (dst_8s, 8, &crc);
	nmppsRShiftC_16s((nm16s*)src0_16s,1,(nm16s*)dst_16s,16);                nmppsCrcAcc_16s(dst_16s,16,&crc);
	nmppsRShiftC_32s((nm32s*)src0_32s,1,(nm32s*)dst_32s,16);                nmppsCrcAcc_32s(dst_32s,16,&crc);
	nmppsRShiftC_64s((nm64s*)src0_64s,1,(nm64s*)dst_64s,16);                nmppsCrcAcc_64s(dst_64s,16,&crc);
                                                                                                    
	nmppsRShiftC_8u ((nm8u* )src0_8s ,1,(nm8u* )dst_8s ,16);				nmppsCrcAcc_8s (dst_8s, 16,&crc);
	nmppsRShiftC_16u((nm16u*)src0_16s,1,(nm16u*)dst_16s,16);                nmppsCrcAcc_16s(dst_16s,16,&crc);
 	nmppsRShiftC_32u((nm32u*)src0_32s,1,(nm32u*)dst_32s,16);                nmppsCrcAcc_32s(dst_32s,16,&crc);
	nmppsRShiftC_64u((nm64u*)src0_64s,1,(nm64u*)dst_64s,16);                nmppsCrcAcc_64s(dst_64s,16,&crc);
                                                                                                    
	nmppsAndC_8u((nm8u*)  src0_8s, 5, (nm8s*) dst_8s,16);					nmppsCrcAcc_8s (dst_8s, 16,&crc);
	nmppsAndC_16u((nm16u*)src0_16s,5,(nm16u*)dst_16s,16);                   nmppsCrcAcc_16s(dst_16s,16,&crc);
	nmppsAndC_32u((nm32u*)src0_32s,5,(nm32u*)dst_32s,16);                   nmppsCrcAcc_32s(dst_32s,16,&crc);
	nmppsAndC_64u((nm64u*)src0_64s,5,(nm64u*)dst_64s,16);                   nmppsCrcAcc_64s(dst_64s,16,&crc);
                                                                                                    
	nmppsOrC_8u ((nm8u*)src0_8s,1,  (nm8s*) dst_8s,16);						nmppsCrcAcc_8s (dst_8s, 16,&crc);
	nmppsOrC_16u((nm16u*)src0_16s,1,(nm16u*)dst_16s,16);                    nmppsCrcAcc_16s(dst_16s,16,&crc);
	nmppsOrC_32u((nm32u*)src0_32s,1,(nm32u*)dst_32s,16);                    nmppsCrcAcc_32s(dst_32s,16,&crc);
	nmppsOrC_64u((nm64u*)src0_64s,1,(nm64u*)dst_64s,32);                    nmppsCrcAcc_64s(dst_64s,32,&crc);
                                                                                                    
	nmppsXorC_8u((nm8u*)  src0_8s,1, (nm8s*) dst_8s,16);					nmppsCrcAcc_8s (dst_8s, 16,&crc);
	nmppsXorC_16u((nm16u*)src0_16s,1,(nm16u*)dst_16s,16);                   nmppsCrcAcc_16s(dst_16s,16,&crc);
	nmppsXorC_32u((nm32u*)src0_32s,1,(nm32u*)dst_32s,16);                   nmppsCrcAcc_32s(dst_32s,16,&crc);
	nmppsXorC_64u((nm64u*)src0_64s,1,(nm64u*)dst_64s,32);                   nmppsCrcAcc_64s(dst_64s,32,&crc);
	                                                                                                
	nmppsNot_8u ((nm8u* )src0_8s, (nm8s* )dst_8s ,16);						nmppsCrcAcc_8s (dst_8s, 16,&crc);
	nmppsNot_16u((nm16u*)src0_16s,(nm16s*)dst_16s,16);                      nmppsCrcAcc_16s(dst_16s,16,&crc);
	nmppsNot_32u((nm32u*)src0_32s,(nm32s*)dst_32s,16);                      nmppsCrcAcc_32s(dst_32s,16,&crc);
	nmppsNot_64u((nm64u*)src0_64s,(nm64s*)dst_64s,16);                      nmppsCrcAcc_64s(dst_64s,16,&crc);
                                                                                                    
	nmppsAnd_8u ((nm8u*) src0_8s, (nm8u*) src1_8s, (nm8s*) dst_8s,16);		nmppsCrcAcc_8s (dst_8s, 16,&crc);
	nmppsAnd_16u((nm16u*)src0_16s,(nm16u*)src1_16s,(nm16u*)dst_16s,16);     nmppsCrcAcc_16s(dst_16s,16,&crc);
	nmppsAnd_32u((nm32u*)src0_32s,(nm32u*)src1_32s,(nm32u*)dst_32s,16);     nmppsCrcAcc_32s(dst_32s,16,&crc);
	nmppsAnd_64u((nm64u*)src0_64s,(nm64u*)src1_64s,(nm64u*)dst_64s,32);     nmppsCrcAcc_64s(dst_64s,32,&crc);
	                                                                                                
	nmppsOr_8u ((nm8u*) src0_8s, (nm8u*) src1_8s, (nm8s*) dst_8s,16);		nmppsCrcAcc_8s (dst_8s, 16,&crc);
	nmppsOr_16u((nm16u*)src0_16s,(nm16u*)src1_16s,(nm16u*)dst_16s,16);      nmppsCrcAcc_16s(dst_16s,16,&crc);
	nmppsOr_32u((nm32u*)src0_32s,(nm32u*)src1_32s,(nm32u*)dst_32s,16);      nmppsCrcAcc_32s(dst_32s,16,&crc);
	nmppsOr_64u((nm64u*)src0_64s,(nm64u*)src1_64s,(nm64u*)dst_64s,32);      nmppsCrcAcc_64s(dst_64s,32,&crc);
                                                                                                    
	nmppsXor_8u ((nm8u*) src0_8s, (nm8u*) src1_8s, (nm8s*) dst_8s,16);		nmppsCrcAcc_8s (dst_8s, 16,&crc);
	nmppsXor_16u((nm16u*)src0_16s,(nm16u*)src1_16s,(nm16u*)dst_16s,16);     nmppsCrcAcc_16s(dst_16s,16,&crc);
	nmppsXor_32u((nm32u*)src0_32s,(nm32u*)src1_32s,(nm32u*)dst_32s,16);     nmppsCrcAcc_32s(dst_32s,16,&crc);
	nmppsXor_64u((nm64u*)src0_64s,(nm64u*)src1_64s,(nm64u*)dst_64s,32);     nmppsCrcAcc_64s(dst_64s,32,&crc);

	nmppsCmpLtC_8s8um ((nm8s*) src0_8s ,1,(nm8u*)dst_8s,16,0);				nmppsCrcAcc_8s (dst_8s, 16,&crc); 
	nmppsCmpLtC_16s8um((nm16s*)src0_16s,1,(nm8u*)dst_8s,16,0);              nmppsCrcAcc_16s(dst_16s,16,&crc);
	nmppsCmpLtC_32s8um((nm32s*)src0_32s,1,(nm8u*)dst_8s,16,0);              nmppsCrcAcc_32s(dst_32s,16,&crc);
//	nmppsCmpLtC_64s8um((nm64s*)src0_32s,1,(nm8u*)dst_8s,16,0);              //nmppsCrcAcc_64s(dst_64s,16,&crc);
                                                                            //
	nmppsCmpNeC_8s8um ((nm8s*) src0_8s ,1,(nm8u*)dst_8s,16,0);				nmppsCrcAcc_8s (dst_8s, 16,&crc);  
	nmppsCmpNeC_16s8um((nm16s*)src0_16s,1,(nm8u*)dst_8s,16,0);              nmppsCrcAcc_16s(dst_16s,16,&crc);
	nmppsCmpNeC_32s8um((nm32s*)src0_32s,1,(nm8u*)dst_8s,16,0);              nmppsCrcAcc_32s(dst_32s,16,&crc);
//	nmppsCmpNeC_64s8um((nm64s*)src0_64s,1,(nm8u*)dst_8s,16,0);              //nmppsCrcAcc_64s(dst_64s,64,&crc);

	nmppsCmpNe_8s8um  ((nm8s*) src0_8s , (nm8s*) src1_8s ,(nm8u*)dst_8s, 16, 0);	nmppsCrcAcc_8s (dst_8s, 16,&crc);		
	nmppsCmpNe_16s8um ((nm16s*)src0_16s, (nm16s*)src1_16s,(nm8u*)dst_8s, 16, 0);	nmppsCrcAcc_16s(dst_16s,16,&crc);	
	nmppsCmpNe_32s8um ((nm32s*)src0_32s, (nm32s*)src1_32s,(nm8u*)dst_8s, 16, 0);	nmppsCrcAcc_32s(dst_32s,16,&crc);	
//	nmppsCmpNe_64s8um ((nm64s*)src0_64s, (nm64s*)src1_64s,(nm8u*)dst_8s, 16, 0);	//nmppsCrcAcc_64s(dst_64s,16,&crc);	
                                                                                    
																					//for(i=0; i<16; i++)	dst_8s[i]=-1;
	nmppsCmpLt_8s8um  ((nm8s*) src0_8s , (nm8s*) src1_8s ,(nm8u*)dst_8s, 16, 0);	nmppsCrcAcc_8s (dst_8s, 16,&crc);	
	nmppsCmpLt_16s8um ((nm16s*)src0_16s, (nm16s*)src1_16s,(nm8u*)dst_8s, 16, 0);	nmppsCrcAcc_16s(dst_16s,16,&crc);	
	nmppsCmpLt_32s8um ((nm32s*)src0_32s, (nm32s*)src1_32s,(nm8u*)dst_8s, 16, 0);	nmppsCrcAcc_32s(dst_32s,16,&crc);	
//	nmppsCmpLt_64s8um ((nm64s*)src0_32s, (nm64s*)src1_32s,(nm8u*)dst_8s, 16, 0);	//nmppsCrcAcc_64s(dst_64s,16,&crc);	

	
	aura_close(n);
	slog (0, SLOG_INFO, "Finished");
	printf("CRC=%x\n",crc);
	return crc-0xc354a8e4;;
}


