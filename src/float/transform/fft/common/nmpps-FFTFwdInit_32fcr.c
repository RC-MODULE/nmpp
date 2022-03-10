#include "fft_32fcr.h"

//int nmppsFFTFwdInitAlloc_32fcr(NmppsFFTspec_32fcr** spec, int order)
//{
//	int status;
//	if(order == 5) {
//		status = nmppsFFT32FwdInitAlloc_32fcr(spec);
//		if (!status)	
//			(*spec)->order=order;	
//	} else if(order == 6) {
//		status = nmppsFFT64FwdInitAlloc_32fcr(spec);
//		if (!status)	
//			(*spec)->order=order;	
//	} else if(order == 7) {
//		status = nmppsFFT128FwdInitAlloc_32fcr(spec);
//		if (!status)	
//			(*spec)->order=order;	
//	} else if(order == 8) {
//		status = nmppsFFT256FwdInitAlloc_32fcr(spec);
//		if (!status)
//			(*spec)->order=order;
//	} else if(order == 9) {
//		status = nmppsFFT512FwdInitAlloc_32fcr(spec);
//		if (!status)	
//			(*spec)->order=order;
//	} else if(order == 10) {
//		status = nmppsFFT1024FwdInitAlloc_32fcr(spec);
//		if (!status)	
//			(*spec)->order=order;
//	} else if(order == 11) {
//		status = nmppsFFT2048FwdInitAlloc_32fcr(spec);
//		if (!status)	
//			(*spec)->order = order;
//	} else {
//		return -100;
//	}
//	return status;
//}