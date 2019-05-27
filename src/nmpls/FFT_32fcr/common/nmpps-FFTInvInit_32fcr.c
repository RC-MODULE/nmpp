#include "fft_32fcr.h"

//int nmppsFFTInvInitAlloc_32fcr(NmppsFFTSpec_32fcr** spec, int order)
//{
//	int status;
//	if(order == 5) {
//		status = nmppsFFT32InvInitAlloc_32fcr(spec);
//		if (!status)	
//			(*spec)->order = order;	
//	} else if(order == 6) {
//		status = nmppsFFT64InvInitAlloc_32fcr(spec);
//		if (!status)	
//			(*spec)->order = order;	
//	} else if(order == 7) {
//		status = nmppsFFT128InvInitAlloc_32fcr(spec);
//		if (!status)	
//			(*spec)->order = order;	
//	} else if(order == 8) {
//		status = nmppsFFT256InvInitAlloc_32fcr(spec);
//		if (!status)
//			(*spec)->order = order;
//	} else if(order == 9) {
//		status = nmppsFFT512InvInitAlloc_32fcr(spec);
//		if (!status)	
//			(*spec)->order = order;
//	} else if(order == 10) {
//		status = nmppsFFT1024InvInitAlloc_32fcr(spec);
//		if (!order)	
//			(*spec)->order = order;
//	} else if(order == 11) {
//		status = nmppsFFT2048InvInitAlloc_32fcr(spec);
//		if (!status)	
//			(*spec)->order = order;
//	} else {
//		return -100;
//	}
//	return status;
//}