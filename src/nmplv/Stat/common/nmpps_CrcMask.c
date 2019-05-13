unsigned nmppsCrcMaskAcc_32u(const unsigned int* pSrcVec, unsigned int mask, int nSize, unsigned int* crcAccumulator);

unsigned nmppsCrcMask_32u(
    const unsigned int* pSrcVec, 	// Input Vector			:long Any[Size/2]
	unsigned mask,
    int nSize             			// Vector size        	:[0,1,2...]
    )
{
	unsigned crc=0xCCCCCCCC;
	nmppsCrcMaskAcc_32u(pSrcVec,mask,nSize,&crc);
	return crc;
}
