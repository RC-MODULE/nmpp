#include <nmtype.h>
#include <malloc32.h>
#include <nmpp.h>
#include <stdio.h>

#define 				SIZE					256

//template<typename T, typename B>
//class FloatCopyTester {
//public:
//  FloatCopyTester() {
//    src = (T*)malloc(size);
//	dst = (T*)malloc(size + additional_memory);
//  }
//  ~FloatCopyTester() {
//	free(src);
//	free(dst);
//  }
//  
//  int TestCopyEvenEvenAddress();
//  
//private:
//  T* src = nullptr;
//  T* dst = nullptr;
//  size_t size = 256;
//  size_t additional_memory = 32;
//}
//
//template<typename T, typename B>
//int FloatCopyTester<T, B>:: TestCopyEvenEvenAddress()
//{
//  
//}

unsigned TestCopyEvenEvenAddress()
{
  size_t additional_memory = 32;
  nm32f* src = (T*)malloc(SIZE);
  nm32f* dst = (T*)malloc(SIZE + additional_memory);
  
  for(int i = 0; i < SIZE; i++) {
	src[i] = i;
  }
  
  for(int i = SIZE; i < SIZE + additional_memory; i++) {
	src[i] = 777;
  }
  
  for(int i = 0; i < SIZE + 11; i++) {
	dst_32f[i] = 555;
  }
  
  unsigned crc = 0;
  
  for(int iSize = 2; iSize < SIZE; iSize++) {
	nmppsCopy_32f(src, dst, iSize);
	nmppsCrcAcc_32f(dst, 0, SIZE + additional_memory, &crc);
  }
  
  free(src);
  free(dst);
  return crc >> 2;
}


int main()
{
  int crc = TestCopyEvenEvenAddress();
  return crc;
}

