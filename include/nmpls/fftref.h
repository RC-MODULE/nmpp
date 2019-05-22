#ifndef FFTREF_H_INCLUDED
#define FFTREF_H_INCLUDED
#include "nmtype.h"
	
void nmppsDFT16Fwd_RefFloat(const nm32sc* src, nm32sc* dst);
void nmppsFFT16Fwd2x8_RefFloat(const nm32sc* src, nm32sc* dst);
void nmppsFFT16Fwd2x8_RefInt(const nm32sc* src, nm32sc* dst);
void nmppsFFT16Fwd8x2_RefFloat(const nm32sc* src, nm32sc* dst);
void nmppsFFT16Fwd2x8Time_RefFloat(const nm32sc* src, nm32sc* dst);
void nmppsFFT16Fwd2x8Freq_RefFloat(const nm32sc* src, nm32sc* dst);
void nmppsFFT16Fwd242_RefFloat(const nm32sc* src, nm32sc* dst);
void nmppsFFT16Fwd242_RefFloat(const nm32sc* src, nm32fc* dst);
void nmppsFFT16Fwd242_RefInt(const nm32sc* src, nm32sc* dst);
void nmppsFFT16Fwd242_RefNmc(const nm32sc* src, nm32sc* dst);



void nmppsDFT32Fwd_RefFloat(const nm32sc* src, nm32sc* dst);
void nmppsFFT32Fwd282_RefFloat(const nm32sc* src, nm32sc* dst);

void nmppsDFT64Fwd_RefFloat(const nm32sc* src, nm32sc* dst);
void nmppsFFT64Fwd88_RefFloat(const nm32sc* src, nm32sc* dst);

void nmppsDFT128Fwd_RefFloat(const nm32sc* src, nm32sc* dst);
void nmppsFFT128Fwd882_RefFloat(const nm32sc* src, nm32sc* dst);
void nmppsFFT128Fwd828_RefFloat(const nm32sc* src, nm32sc* dst);

void nmppsDFT256Fwd_RefFloat(const nm32sc* src, nm32sc* dst);
void nmppsFFT256Fwd2882_RefFloat(const nm32sc* src, nm32sc* dst);

/*
template <int rep, int nb_bits, int sb_bits> load_wfifo(void *wfifo) {

}
template<int rep> void load_data_vsum_data_vr(void *data, int vr) {
	
}

template<int rep> void save_afifo(void *dst) {

}*/
#endif