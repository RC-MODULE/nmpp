#define __STDC_FORMAT_MACROS
#include <aura/aura.h>
#include <ion/ion.h>
#include "nmpp.h"

struct aura_node *n;
int main() {

	printf("START-%s\n", aura_get_version());
	slog_init(NULL, 3);
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
	static signed char  src0_8s[256] , src1_8s[256];
	static signed short src0_16s[256], src1_16s[256];
	static signed int   src0_32s[2*2048] , src1_32s[256];
	long long    src0_64s[256], src1_64s[256];
	static signed char  dst_8s[256];
	signed short dst_16s[256];
	signed int 	 dst_32s[2*2048];
	signed long long dst_64s[256];
	
	int j,i=0;

	for(i=0; i<256; i++){
		src0_8s[i] =1;//i;  
		src0_16s[i]=i%2;  
		src0_32s[i]=i+10;  
		src0_64s[i]=i+10;  
		            
		src1_8s[i] =1;
		src1_16s[i]=1;
		src1_32s[i]=8-i;
		src1_64s[i]=8-i;
	}
	//for(i=0; i<256; i++){
	//	src0_8s[i] =1;  
	//	src0_16s[i]=1;  
	//	src0_32s[i]=1;  
	//	src0_64s[i]=1;  
	//	            
	//	src1_8s[i] =1;
	//	src1_16s[i]=1;
	//	src1_32s[i]=1;
	//	src1_64s[i]=1;
	//}

	unsigned crc=-1;
	
	nmppsAbs_8s ((nm8s* )src0_8s ,(nm8s* )dst_8s ,8);					nmppsCrcAcc_8s (dst_8s, 8, &crc);
	nmppsAbs_16s((nm16s*)src0_16s,(nm16s*)dst_16s,16);					nmppsCrcAcc_16s(dst_16s,16,&crc);
	nmppsAbs_32s((nm32s*)src0_32s,(nm32s*)dst_32s,16); 					nmppsCrcAcc_32s(dst_32s,32,&crc);
	nmppsAbs_64s((nm64s*)src0_16s,(nm64s*)dst_64s,16);					nmppsCrcAcc_64s(dst_64s,64,&crc);

	nmppsAbs1_8s ((nm8s* )src0_8s ,(nm8s* )dst_8s ,8);  				nmppsCrcAcc_8s (dst_8s, 8, &crc);
	nmppsAbs1_16s((nm16s*)src0_16s,(nm16s*)dst_16s,16); 				nmppsCrcAcc_16s(dst_16s,16,&crc);
	nmppsAbs1_32s((nm32s*)src0_32s,(nm32s*)dst_32s,16); 				nmppsCrcAcc_32s(dst_32s,32,&crc);
	nmppsAbs1_64s((nm64s*)src0_16s,(nm64s*)dst_64s,16); 				nmppsCrcAcc_64s(dst_64s,64,&crc);
	
	nmppsAdd_8s ((nm8s* )src0_8s ,(nm8s* )src1_8s ,(nm8s* )dst_8s ,8);  nmppsCrcAcc_8s (dst_8s, 8, &crc);
	nmppsAdd_16s((nm16s*)src0_16s,(nm16s*)src1_16s,(nm16s*)dst_16s,16); nmppsCrcAcc_16s(dst_16s,16,&crc);
	nmppsAdd_32s((nm32s*)src0_32s,(nm32s*)src1_32s,(nm32s*)dst_32s,16); nmppsCrcAcc_32s(dst_32s,32,&crc);
	nmppsAdd_64s((nm64s*)src0_16s,(nm64s*)src1_16s,(nm64s*)dst_64s,16); nmppsCrcAcc_64s(dst_64s,64,&crc);
	
	nmppsSub_8s ((nm8s* )src0_8s ,(nm8s* )src1_8s ,(nm8s* )dst_8s ,8);  nmppsCrcAcc_8s (dst_8s, 8, &crc);
	nmppsSub_16s((nm16s*)src0_16s,(nm16s*)src1_16s,(nm16s*)dst_16s,16); nmppsCrcAcc_16s(dst_16s,16,&crc);
	nmppsSub_32s((nm32s*)src0_32s,(nm32s*)src1_32s,(nm32s*)dst_32s,16); nmppsCrcAcc_32s(dst_32s,32,&crc);
	nmppsSub_64s((nm64s*)src0_16s,(nm64s*)src1_16s,(nm64s*)dst_64s,16); nmppsCrcAcc_64s(dst_64s,64,&crc);

	nmppsAddC_8s ((nm8s* )src0_8s ,(nm8s* )1,(nm8s* )dst_8s ,8);  		nmppsCrcAcc_8s (dst_8s, 8, &crc);
	nmppsAddC_16s((nm16s*)src0_16s,(nm16s*)1,(nm16s*)dst_16s,16);       nmppsCrcAcc_16s(dst_16s,16,&crc);
	nmppsAddC_32s((nm32s*)src0_32s,(nm32s*)1,(nm32s*)dst_32s,16);       nmppsCrcAcc_32s(dst_32s,32,&crc);
	nmppsAddC_64s((nm64s*)src0_16s,(nm64s*)1,(nm64s*)dst_64s,16);       nmppsCrcAcc_64s(dst_64s,64,&crc);
	                                       
	nmppsSubC_8s ((nm8s* )src0_8s ,(nm8s* )1,(nm8s* )dst_8s ,8);		nmppsCrcAcc_8s (dst_8s, 8, &crc);
	nmppsSubC_16s((nm16s*)src0_16s,(nm16s*)1,(nm16s*)dst_16s,16);       nmppsCrcAcc_16s(dst_16s,16,&crc);
	nmppsSubC_32s((nm32s*)src0_32s,(nm32s*)1,(nm32s*)dst_32s,16);       nmppsCrcAcc_32s(dst_32s,32,&crc);
	nmppsSubC_64s((nm64s*)src0_16s,(nm64s*)1,(nm64s*)dst_64s,16);       nmppsCrcAcc_64s(dst_64s,64,&crc);
	
	nmppsSubCRev_8s ((nm8s* )src0_8s ,(nm8s* )1,(nm8s* )dst_8s ,8);		nmppsCrcAcc_8s (dst_8s, 8, &crc);
	nmppsSubCRev_16s((nm16s*)src0_16s,(nm16s*)1,(nm16s*)dst_16s,16);    nmppsCrcAcc_16s(dst_16s,16,&crc);
	nmppsSubCRev_32s((nm32s*)src0_32s,(nm32s*)1,(nm32s*)dst_32s,16);    nmppsCrcAcc_32s(dst_32s,32,&crc);
	nmppsSubCRev_64s((nm64s*)src0_16s,(nm64s*)1,(nm64s*)dst_64s,16);    nmppsCrcAcc_64s(dst_64s,64,&crc);

	int sum;
	long long sum64;
	nmppsSum_8s ((nm8s*) src0_8s, 32,&sum  );  							nmppsCrcAcc_32s(&sum,  1,&crc);
	nmppsSum_16s((nm16s*)src0_16s,32,&sum64);							nmppsCrcAcc_64s(&sum64,1,&crc);
	nmppsSum_32s((nm32s*)src0_32s,32,&sum64);							nmppsCrcAcc_64s(&sum64,1,&crc);
	nmppsSum_64s((nm64s*)src0_64s,32,&sum64);							nmppsCrcAcc_64s(&sum64,1,&crc);	

	nmppsMulC_8s 	((nm8s*) src0_8s ,2,(nm8s*) dst_8s, 16); 			nmppsCrcAcc_8s (dst_8s, 16, &crc);
	nmppsMulC_8s16s	((nm8s*) src0_8s ,2,(nm8s*) dst_16s,16);			nmppsCrcAcc_8s (dst_8s, 16, &crc);
	nmppsMulC_16s	((nm16s*)src0_16s,3,(nm16s*)dst_16s,16); 			nmppsCrcAcc_16s(dst_16s,16,&crc);
	nmppsMulC_16s32s((nm16s*)src0_16s,3,(nm32s*)dst_32s,16); 			nmppsCrcAcc_32s(dst_32s,16,&crc);
	nmppsMulC_32s	((nm32s*)src0_32s,4,(nm32s*)dst_32s,16); 			nmppsCrcAcc_32s(dst_32s,16,&crc);
	nmppsMulC_32s64s((nm32s*)src0_32s,4,(nm64s*)dst_64s,16); 			nmppsCrcAcc_64s(dst_64s,16,&crc);
	nmppsMulC_64s	((nm64s*)src0_64s,2,(nm64s*)dst_64s,16); 			nmppsCrcAcc_64s(dst_64s,16,&crc);
	
	
	nmppmMul_mv_8s64s (src0_8s, src1_64s,dst_64s,8,8);					nmppsCrcAcc_64s(dst_64s,8,&crc);
	nmppmMul_mv_16s64s(src0_16s,src1_64s,dst_64s,8,8);                  nmppsCrcAcc_64s(dst_64s,8,&crc);
	nmppmMul_mv_32s64s(src0_32s,src1_64s,dst_64s,8,8);                  nmppsCrcAcc_64s(dst_64s,8,&crc);
                
	nmppmMul_mm_8s8s  (src0_8s,8,16,src1_8s, dst_8s, 16);				nmppsCrcAcc_8s (dst_8s, 256,&crc);
	nmppmMul_mm_8s16s (src0_8s,8,16,src1_16s,dst_16s,16);               nmppsCrcAcc_16s(dst_16s,256,&crc);
	nmppmMul_mm_8s32s (src0_8s,8,16,src1_32s,dst_32s,16);               nmppsCrcAcc_32s(dst_32s,256,&crc);
	nmppmMul_mm_8s64s (src0_8s,8,16,src1_64s,dst_64s,16);               nmppsCrcAcc_64s(dst_64s,256,&crc);
				                                                                                
	nmppmMul_mm_16s16s(src0_16s,8,16,src1_16s,dst_16s,16);              nmppsCrcAcc_16s(dst_16s,256,&crc);
	//for(i=0; i<8; i++){
	//	printf("\n");
	//	for(j=0; j<16; j++)	
	//		printf("%d\t", dst_16s[i*16+j]);
	//}
	//printf("\n\n");

	
	nmppmMul_mm_16s32s(src0_16s,8,16,src1_32s,dst_32s,16);              nmppsCrcAcc_32s(dst_32s,256,&crc);
	nmppmMul_mm_16s64s(src0_16s,8,16,src1_64s,dst_64s,16);              nmppsCrcAcc_64s(dst_64s,256,&crc);
	                                                                                            
	nmppmMul_mm_32s32s(src0_32s,8,16,src1_32s,dst_32s,16);				nmppsCrcAcc_32s(dst_32s,256,&crc);
	nmppmMul_mm_32s64s(src0_32s,8,16,src1_64s,dst_64s,16);              nmppsCrcAcc_64s(dst_64s,256,&crc);
	
//	nmppmMul_mv_colmajor_8s64s (src0_8s, src1_64s,dst_64s,8,8);			nmppsCrcAcc_64s(dst_64s,8,&crc);
//	nmppmMul_mv_colmajor_16s64s(src0_16s,src1_64s,dst_64s,8,8);         nmppsCrcAcc_64s(dst_64s,8,&crc);
//	nmppmMul_mv_colmajor_32s64s(src0_32s,src1_64s,dst_64s,8,8);         nmppsCrcAcc_64s(dst_64s,8,&crc);
//                                                                        
//	nmppmMul_mm_colmajor_8s8s  (src0_8s,8,16,src1_8s, dst_8s, 16);		nmppsCrcAcc_8s (dst_8s, 256,&crc);
//	nmppmMul_mm_colmajor_8s16s (src0_8s,8,16,src1_16s,dst_16s,16);      nmppsCrcAcc_16s(dst_16s,256,&crc);
//	nmppmMul_mm_colmajor_8s32s (src0_8s,8,16,src1_32s,dst_32s,16);      nmppsCrcAcc_32s(dst_32s,256,&crc);
//	nmppmMul_mm_colmajor_8s64s (src0_8s,8,16,src1_64s,dst_64s,16);      nmppsCrcAcc_64s(dst_64s,256,&crc);
//                                                                                                
//	nmppmMul_mm_colmajor_16s16s(src0_16s,8,16,src1_16s,dst_16s,16);     nmppsCrcAcc_16s(dst_16s,256,&crc);
//	nmppmMul_mm_colmajor_16s32s(src0_16s,8,16,src1_32s,dst_32s,16);     nmppsCrcAcc_32s(dst_32s,256,&crc);
//	nmppmMul_mm_colmajor_16s64s(src0_16s,8,16,src1_64s,dst_64s,16);     nmppsCrcAcc_64s(dst_64s,256,&crc);
//                                                                                              
//	nmppmMul_mm_colmajor_32s32s(src0_32s,8,16,src1_32s,dst_32s,16);		nmppsCrcAcc_32s(dst_32s,256,&crc);
//	nmppmMul_mm_colmajor_32s64s(src0_32s,8,16,src1_64s,dst_64s,16);     nmppsCrcAcc_64s(dst_64s,256,&crc);
	
	signed long long ret64;
	nmppsDotProd_8s8sm  ((nm8s*) src0_8s ,(nm8s *)src1_8s , 16, &ret64,0);  nmppsCrcAcc_64s(&ret64,1,&crc);    
	nmppsDotProd_8s16sm ((nm8s*) src0_8s ,(nm16s*)src1_16s, 16, &ret64,0);  nmppsCrcAcc_64s(&ret64,1,&crc);    
	nmppsDotProd_8s32sm ((nm8s*) src0_8s ,(nm32s*)src1_32s, 16, &ret64,0);  nmppsCrcAcc_64s(&ret64,1,&crc);    
	nmppsDotProd_8s64s  ((nm8s*) src0_8s ,(nm64s*)src1_64s, 16, &ret64);    nmppsCrcAcc_64s(&ret64,1,&crc);    
                                                                                
	nmppsDotProd_16s16sm((nm16s*)src0_16s,(nm16s*)src1_16s, 16, &ret64,0); 	nmppsCrcAcc_64s(&ret64,1,&crc);   
	nmppsDotProd_16s32sm((nm16s*)src0_16s,(nm32s*)src1_32s, 16, &ret64,0);  nmppsCrcAcc_64s(&ret64,1,&crc);  
	nmppsDotProd_16s64s ((nm16s*)src0_16s,(nm64s*)src1_64s, 16, &ret64);    nmppsCrcAcc_64s(&ret64,1,&crc);  
                                                                               
	nmppsDotProd_32s32sm((nm32s*)src0_32s,(nm32s*)src1_32s, 16, &ret64,0);  nmppsCrcAcc_64s(&ret64,1,&crc);  
	nmppsDotProd_32s64s ((nm32s*)src0_32s,(nm64s*)src1_64s, 16, &ret64);    nmppsCrcAcc_64s(&ret64,1,&crc);   
	                                                                        
	nmppsDotProd_64s64s ((nm64s*)src0_64s,(nm64s*)src1_64s, 16, &ret64);    nmppsCrcAcc_64s(&ret64,1,&crc);   
//
//	long min,max;
//	long long min64,max64;
//	
//	nmppsMin_8s7b  (src0_8s ,32,&min);								nmppsCrcAcc_32s(&min,  1,&crc);
//	nmppsMin_16s15b(src0_16s,32,&min);	                            nmppsCrcAcc_32s(&min,  1,&crc);
//	nmppsMin_32s31b(src0_32s,32,&min);	                            nmppsCrcAcc_32s(&min,  1,&crc);
//	nmppsMin_64s63b(src0_64s,16,&min64);                            nmppsCrcAcc_64s(&min64,1,&crc);
//
//	nmppsMax_8s7b  (src0_8s,32, &max); 								nmppsCrcAcc_64s(&max,  1,&crc);
//	nmppsMax_16s15b(src0_16s,32,&max); 						     	nmppsCrcAcc_64s(&max,  1,&crc);
//	nmppsMax_32s31b(src0_32s,32,&max); 						     	nmppsCrcAcc_64s(&max,  1,&crc);
//	nmppsMax_64s63b(src0_64s,32,&max64);                            nmppsCrcAcc_64s(&max64,1,&crc);
//	
//	nmppsMin_8sm  (src0_8s ,32,&min, 0);							nmppsCrcAcc_32s(&min,  1,&crc);
//	nmppsMin_16sm (src0_16s,32,&min, 0);	                        nmppsCrcAcc_32s(&min,  1,&crc);
//	nmppsMin_32sm (src0_32s,32,&min, 0);	                        nmppsCrcAcc_32s(&min,  1,&crc);
//                                                                    //
//	nmppsMax_8sm  (src0_8s,32, &max, 0); 							nmppsCrcAcc_32s(&max,  1,&crc);
//	nmppsMax_16sm (src0_16s,32,&max, 0); 					     	nmppsCrcAcc_32s(&max,  1,&crc);
//	nmppsMax_32sm (src0_32s,32,&max, 0); 					     	nmppsCrcAcc_32s(&max,  1,&crc);

	//	aura_handle_events_timeout(aura_eventloop_get_data(n), 500);
	aura_close(n);
	
	slog (0, SLOG_INFO, "Finished");
	printf("CRC=%x\n",crc);
	return crc-0xc354a8e4;
}
//	for(i=0; i<32; i++)	printf("%llu %llu \r\n", src0_64s [i],max64);
//	for(i=0; i<32; i++)	printf("%d %d \r\n", (int)src0_32s [i],(int)max);
	
//	for(i=0; i<8; i++){
//		printf("\n");
//		for(j=0; j<16; j++)	
//			printf("%d\t", dst_16s[i*16+j]);
//	}
//	printf("\n\n");


