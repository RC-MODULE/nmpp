#include <stdlib.h>
#include "nmchar.h"

/*
uint8ptr nmchar::operator &(){
	uint8ptr p;
	p.addr=adr;
	p.indx=idx;
	return p;
}
*/

void free(uint8ptr& p){
	free(p.addr);
}

void nmchar_memcpy (uint8ptr dst, uint8ptr src, unsigned int  len){
	
	
	#ifdef __NM__
		memcpy((void*)dst.x86addr(), (void*)src.x86addr(),len);
	#else
		if (dst.indx==src.indx){
			// copy n bytes to align pointers
			if (dst.indx){
				int n=4-dst.indx;
				if (len<n)
					n=len;
				for(int i=0; i<n; i++){
					*dst=*src;
					dst++;
					src++;
				}
				len-=n;
			}
			int words=len>>2;
			memcpy(dst.addr, src.addr, words);
			dst.addr+=words;
			src.addr+=words;
			len%=4;
			// copy rest bytes
			for(int i=0;i<len;i++){
				*dst=*src;
				dst++;
				src++;
			}
		}
		else {
			for(int i=0; i<len; i++){
				*dst=*src;
				src++;
				dst++;
			}
		}
	
	#endif
}

__INLINE__ void nmchar_memset (uint8ptr dst, int setvalue, unsigned int  len){
	
	
	#ifdef __NM__
		memset((void*)dst.x86addr(), setvalue,len);
	#else

		// copy n bytes to align pointers
		if (dst.indx){
			int n=4-dst.indx;
			if (len<n)
				n=len;
			for(int i=0; i<n; i++){
				*dst=setvalue;
				dst++;
			}
			len-=n;
		}
		int words=len>>2;
		
		setvalue&=0xFF;
		setvalue|=(setvalue<<8);
		setvalue|=(setvalue<<16);
		memset(dst.addr, setvalue, words);
		dst.addr+=words;
		len%=4;
		// copy rest bytes
		setvalue&=0xFF;
		for(int i=0;i<len;i++){
			*dst=setvalue;
			dst++;
		}
		
	
	#endif
}


