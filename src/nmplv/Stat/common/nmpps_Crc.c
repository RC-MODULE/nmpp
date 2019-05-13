unsigned nmppsCrcAcc_32u(const unsigned int* pSrcVec, int nSize, unsigned int* crcAccumulator);

unsigned int nmppsCrc_32u(
    const unsigned int* pSrcVec, 	// Input Vector			:long Any[Size/2]
    int nSize             	// Vector size        	:[0,1,2...]
    )
{
	unsigned crc=0xCCCCCCCC;
	nmppsCrcAcc_32u(pSrcVec,nSize,&crc);
	return crc;
}
