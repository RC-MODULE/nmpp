#include "fft_32fc.h"

int nmppsFFTInvInitAlloc_32fc(NmppsFFTSpec_32fc **iSpec, int iOrder)
{
	int Status;
	if(iOrder == 5) {
		Status = nmppsFFT32InvInitAlloc_32fc(iSpec);
		if (!Status)	
			(*iSpec)->order=iOrder;	
	} else if(iOrder == 6) {
		Status = nmppsFFT64InvInitAlloc_32fc(iSpec);
		if (!Status)	
			(*iSpec)->order=iOrder;	
	} else if(iOrder == 7) {
		Status = nmppsFFT128InvInitAlloc_32fc(iSpec);
		if (!Status)	
			(*iSpec)->order=iOrder;	
	} else if(iOrder == 8) {
		Status = nmppsFFT256InvInitAlloc_32fc(iSpec);
		if (!Status)
			(*iSpec)->order=iOrder;
	} else if(iOrder == 9) {
		Status = nmppsFFT512InvInitAlloc_32fc(iSpec);
		if (!Status)	
			(*iSpec)->order=iOrder;
	} else if(iOrder == 10) {
		Status = nmppsFFT1024InvInitAlloc_32fc(iSpec);
		if (!iOrder)	
			(*iSpec)->order=iOrder;
	} else if(iOrder == 11) {
		Status = nmppsFFT2048InvInitAlloc_32fc(iSpec);
		if (!Status)	
			(*iSpec)->order=iOrder;
	} else {
		return -100;
	}
	return Status;
}