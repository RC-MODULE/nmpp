#include "fft_32fcr.h"

int nmppsFFTFwdInitAlloc_32fcr(NmppsFFTSpec_32fcr **Spec, int Order)
{
	int Status;
	if(Order == 5) {
		Status = nmppsFFT32FwdInitAlloc_32fcr(Spec);
		if (!Status)	
			(*Spec)->order=Order;	
	} else if(Order == 6) {
		Status = nmppsFFT64FwdInitAlloc_32fcr(Spec);
		if (!Status)	
			(*Spec)->order=Order;	
	} else if(Order == 7) {
		Status = nmppsFFT128FwdInitAlloc_32fcr(Spec);
		if (!Status)	
			(*Spec)->order=Order;	
	} else if(Order == 8) {
		Status = nmppsFFT256FwdInitAlloc_32fcr(Spec);
		if (!Status)
			(*Spec)->order=Order;
	} else if(Order == 9) {
		Status = nmppsFFT512FwdInitAlloc_32fcr(Spec);
		if (!Status)	
			(*Spec)->order=Order;
	} else if(Order == 10) {
		Status = nmppsFFT1024FwdInitAlloc_32fcr(Spec);
		if (!Status)	
			(*Spec)->order=Order;
	} else if(Order == 11) {
		Status = nmppsFFT2048FwdInitAlloc_32fcr(Spec);
		if (!Status)	
			(*Spec)->order = Order;
	} else {
		return -100;
	}
	return Status;
}