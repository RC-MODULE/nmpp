#include "fft_32fc.h"

int nmppsFFTFwdInitAlloc_32fc(NmppsFFTSpec_32fc **Spec, int Order)
{
	int Status;
	if(Order == 5) {
		Status = nmppsFFT32FwdInitAlloc_32fc(Spec);
		if (!Status)	
			(*Spec)->order=Order;	
	} else if(Order == 6) {
		Status = nmppsFFT64FwdInitAlloc_32fc(Spec);
		if (!Status)	
			(*Spec)->order=Order;	
	} else if(Order == 7) {
		Status = nmppsFFT128FwdInitAlloc_32fc(Spec);
		if (!Status)	
			(*Spec)->order=Order;	
	} else if(Order == 8) {
		Status = nmppsFFT256FwdInitAlloc_32fc(Spec);
		if (!Status)
			(*Spec)->order=Order;
	} else if(Order == 9) {
		Status = nmppsFFT512FwdInitAlloc_32fc(Spec);
		if (!Status)	
			(*Spec)->order=Order;
	} else if(Order == 10) {
		Status = nmppsFFT1024FwdInitAlloc_32fc(Spec);
		if (!Status)	
			(*Spec)->order=Order;
	} else if(Order == 11) {
		Status = nmppsFFT2048FwdInitAlloc_32fc(Spec);
		if (!Status)	
			(*Spec)->order=Order;
	} else {
		return -100;
	}
	return Status;
}