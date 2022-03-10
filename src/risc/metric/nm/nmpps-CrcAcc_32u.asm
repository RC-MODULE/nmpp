//------------------------------------------------------------------------
//
//  $Workfile:: Crc32.as $
//
//  ��������-��������� ����������
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:11 $
//
//! \if file_doc
//!
//! \file Crc32.asm
//! \author ������ �������
//! \brief ������� ����������� ����
//! 
//! \endif
//!
//------------------------------------------------------------------------

// #include "vDiv.h"


//data ".data_nmplv_L"
//end ".data_nmplv_L";

extern  _CRC32_Table: word;

//data ".data_nmplv_G"
//global CRC32_Table: word[256] = (
//    000000000h, 077073096h, 0EE0E612Ch, 0990951BAh,
//    0076DC419h, 0706AF48Fh, 0E963A535h, 09E6495A3h,
//    00EDB8832h, 079DCB8A4h, 0E0D5E91Eh, 097D2D988h,
//    009B64C2Bh, 07EB17CBDh, 0E7B82D07h, 090BF1D91h,
//    01DB71064h, 06AB020F2h, 0F3B97148h, 084BE41DEh,
//    01ADAD47Dh, 06DDDE4EBh, 0F4D4B551h, 083D385C7h,
//    0136C9856h, 0646BA8C0h, 0FD62F97Ah, 08A65C9ECh,
//    014015C4Fh, 063066CD9h, 0FA0F3D63h, 08D080DF5h,
//    03B6E20C8h, 04C69105Eh, 0D56041E4h, 0A2677172h,
//    03C03E4D1h, 04B04D447h, 0D20D85FDh, 0A50AB56Bh,
//    035B5A8FAh, 042B2986Ch, 0DBBBC9D6h, 0ACBCF940h,
//    032D86CE3h, 045DF5C75h, 0DCD60DCFh, 0ABD13D59h,
//    026D930ACh, 051DE003Ah, 0C8D75180h, 0BFD06116h,
//    021B4F4B5h, 056B3C423h, 0CFBA9599h, 0B8BDA50Fh,
//    02802B89Eh, 05F058808h, 0C60CD9B2h, 0B10BE924h,
//    02F6F7C87h, 058684C11h, 0C1611DABh, 0B6662D3Dh,
//
//    076DC4190h, 001DB7106h, 098D220BCh, 0EFD5102Ah,
//    071B18589h, 006B6B51Fh, 09FBFE4A5h, 0E8B8D433h,
//    07807C9A2h, 00F00F934h, 09609A88Eh, 0E10E9818h,
//    07F6A0DBBh, 0086D3D2Dh, 091646C97h, 0E6635C01h,
//    06B6B51F4h, 01C6C6162h, 0856530D8h, 0F262004Eh,
//    06C0695EDh, 01B01A57Bh, 08208F4C1h, 0F50FC457h,
//    065B0D9C6h, 012B7E950h, 08BBEB8EAh, 0FCB9887Ch,
//    062DD1DDFh, 015DA2D49h, 08CD37CF3h, 0FBD44C65h,
//    04DB26158h, 03AB551CEh, 0A3BC0074h, 0D4BB30E2h,
//    04ADFA541h, 03DD895D7h, 0A4D1C46Dh, 0D3D6F4FBh,
//    04369E96Ah, 0346ED9FCh, 0AD678846h, 0DA60B8D0h,
//    044042D73h, 033031DE5h, 0AA0A4C5Fh, 0DD0D7CC9h,
//    05005713Ch, 0270241AAh, 0BE0B1010h, 0C90C2086h,
//    05768B525h, 0206F85B3h, 0B966D409h, 0CE61E49Fh,
//    05EDEF90Eh, 029D9C998h, 0B0D09822h, 0C7D7A8B4h,
//    059B33D17h, 02EB40D81h, 0B7BD5C3Bh, 0C0BA6CADh,
//
//    0EDB88320h, 09ABFB3B6h, 003B6E20Ch, 074B1D29Ah,
//    0EAD54739h, 09DD277AFh, 004DB2615h, 073DC1683h,
//    0E3630B12h, 094643B84h, 00D6D6A3Eh, 07A6A5AA8h,
//    0E40ECF0Bh, 09309FF9Dh, 00A00AE27h, 07D079EB1h,
//    0F00F9344h, 08708A3D2h, 01E01F268h, 06906C2FEh,
//    0F762575Dh, 0806567CBh, 0196C3671h, 06E6B06E7h,
//    0FED41B76h, 089D32BE0h, 010DA7A5Ah, 067DD4ACCh,
//    0F9B9DF6Fh, 08EBEEFF9h, 017B7BE43h, 060B08ED5h,
//    0D6D6A3E8h, 0A1D1937Eh, 038D8C2C4h, 04FDFF252h,
//    0D1BB67F1h, 0A6BC5767h, 03FB506DDh, 048B2364Bh,
//    0D80D2BDAh, 0AF0A1B4Ch, 036034AF6h, 041047A60h,
//    0DF60EFC3h, 0A867DF55h, 0316E8EEFh, 04669BE79h,
//    0CB61B38Ch, 0BC66831Ah, 0256FD2A0h, 05268E236h,
//    0CC0C7795h, 0BB0B4703h, 0220216B9h, 05505262Fh,
//    0C5BA3BBEh, 0B2BD0B28h, 02BB45A92h, 05CB36A04h,
//    0C2D7FFA7h, 0B5D0CF31h, 02CD99E8Bh, 05BDEAE1Dh,
//
//    09B64C2B0h, 0EC63F226h, 0756AA39Ch, 0026D930Ah,
//    09C0906A9h, 0EB0E363Fh, 072076785h, 005005713h,
//    095BF4A82h, 0E2B87A14h, 07BB12BAEh, 00CB61B38h,
//    092D28E9Bh, 0E5D5BE0Dh, 07CDCEFB7h, 00BDBDF21h,
//    086D3D2D4h, 0F1D4E242h, 068DDB3F8h, 01FDA836Eh,
//    081BE16CDh, 0F6B9265Bh, 06FB077E1h, 018B74777h,
//    088085AE6h, 0FF0F6A70h, 066063BCAh, 011010B5Ch,
//    08F659EFFh, 0F862AE69h, 0616BFFD3h, 0166CCF45h,
//    0A00AE278h, 0D70DD2EEh, 04E048354h, 03903B3C2h,
//    0A7672661h, 0D06016F7h, 04969474Dh, 03E6E77DBh,
//    0AED16A4Ah, 0D9D65ADCh, 040DF0B66h, 037D83BF0h,
//    0A9BCAE53h, 0DEBB9EC5h, 047B2CF7Fh, 030B5FFE9h,
//    0BDBDF21Ch, 0CABAC28Ah, 053B39330h, 024B4A3A6h,
//    0BAD03605h, 0CDD70693h, 054DE5729h, 023D967BFh,
//    0B3667A2Eh, 0C4614AB8h, 05D681B02h, 02A6F2B94h,
//    0B40BBE37h, 0C30C8EA1h, 05A05DF1Bh, 02D02EF8Dh
//);
//end  ".data_nmplv_G";

begin ".text_nmplv"


/////////////////////////////////////////////////////////////////////////////////////////////////////////

//! \fn unsigned nmppsCrcAcc_(unsigned int* pSrcVec, int nSize, unsigned int& nCrc);
//!
//! \perfinclude _nmppsCrcAcc_32u.html

global _nmppsCrcAcc_32u :label;
<_nmppsCrcAcc_32u>
 

.branch;

	ar5 = ar7-2;
	push ar0,gr0;
	push ar1,gr1;
	push ar2,gr2;
	push ar3,gr3;
	push ar4,gr4;
	push ar5,gr5;
	push ar6,gr6;

	ar0 = [--ar5];//	nm32u*	Vec,	// Input Vector			:long Any[Size/2]
	gr5 = [--ar5];//	int				nSize,// Vector size        	:[0,1,2...]	
	ar6 = [--ar5];//	unsigned int&	Crc32	// Init/Output crc	
	gr7 = [ar6]	with gr5;
	if =0 delayed goto End_CRC32;
		gr2 = 000000FFh;
	ar5 = _CRC32_Table;
	gr0=[ar0++];									//		a=pSrcVec[i++];
	ar4 = ar5;
	<Next_CRC32>									
		gr1 = gr0 and gr2;							//		b = a & 0x000000FF;		
		gr3 = gr7 and gr2;							//		c = CRC32 & 0x000000FF ;		
		gr4 = gr1 xor gr3;							//		addr=b^c;			
		gr6 = [ar4+=gr4]	with gr7>>=8; 			//		t=pTable[addr];	CRC32 >>=8; 		
		ar4 = ar5			with gr7 = gr7 xor gr6;	//		CRC32 = CRC32 ^t;		
		gr1 = gr0 >> 8;								//		b = a >> 8;		
		gr1 = gr1 and gr2;							//		b = b & 0x000000FF;		
		gr3 = gr7 and gr2;							//		c = CRC32 & 0x000000FF ;		
		gr4	= gr1 xor gr3;							//		addr=b^c;					
		gr6 = [ar4+=gr4]	with gr7>>=8;			//		t=pTable[addr];	CRC32 >>=8;	
		ar4 = ar5			with gr7 = gr7 xor gr6;	//		CRC32 = CRC32 ^t;		
		gr1 = gr0 >> 16;							//		b = a >> 16;		
		gr1 = gr1 and gr2;							//		b = b & 0x000000FF;		
		gr3 = gr7 and gr2;							//		c = CRC32 & 0x000000FF ;		
		gr4	= gr1 xor gr3;							//		addr=b^c;		
		gr6	= [ar4+=gr4]	with gr7>>= 8;			//		t=pTable[addr];	CRC32 >>= 8 ;		
		ar4 = ar5			with gr7 = gr7 xor gr6;	//		CRC32 = CRC32 ^ t;		
		gr1 = gr0 >> 24;							//		b = a >> 24;		
		gr1 = gr1 and gr2;							//		b = b & 0x000000FF;		
		gr3 = gr7 and gr2;							//		c = CRC32 & 0x000000FF ;		
		gr4	= gr1 xor gr3;							//		addr=b^c;		
		gr6	= [ar4+=gr4]	with gr5--;				//		t=pTable[addr];		
	if <>0 delayed goto Next_CRC32;					//		i++		
		ar4 = ar5			with gr7>>= 8;			//		CRC32 >>= 8 		
		gr0	=[ar0++]		with gr7 = gr7 xor gr6;	//		a=pSrcVec[i++];CRC32 = CRC32 ^ t;
	
	<End_CRC32>	
	gr7 = not gr7;									//	CRC32 = ~ CRC32;
	[ar6] = gr7;
	pop ar6,gr6;
	pop ar5,gr5;
	pop ar4,gr4;
	pop ar3,gr3;
	pop ar2,gr2;
	pop ar1,gr1;
	pop ar0,gr0;
	
return;

global   vec_crc32:label;
		<vec_crc32>

.branch;

	ar5 = ar7-2;
	push ar0,gr0;
	push ar1,gr1;
	push ar2,gr2;
	push ar3,gr3;
	push ar4,gr4;
	push ar5,gr5;
	push ar6,gr6;

	//ar0 = [--ar5];//	nm32u*	Vec,	// Input Vector			:long Any[Size/2]
	//gr5 = [--ar5];//	int				nSize,// Vector size        	:[0,1,2...]	
	//ar6 = [--ar5];//	unsigned int&	Crc32	// Init/Output crc	
	//gr7 = [ar6]	
	gr7 = 0CCCCCCCCh;
	with gr5;
	if =0 delayed goto _End_CRC32;
		gr2 = 000000FFh;
	ar5 = _CRC32_Table;
	gr0=[ar0++];									//		a=pSrcVec[i++];
	ar4 = ar5;
	<_Next_CRC32>									
		gr1 = gr0 and gr2;							//		b = a & 0x000000FF;		
		gr3 = gr7 and gr2;							//		c = CRC32 & 0x000000FF ;		
		gr4 = gr1 xor gr3;							//		addr=b^c;			
		gr6 = [ar4+=gr4]	with gr7>>=8; 			//		t=pTable[addr];	CRC32 >>=8; 		
		ar4 = ar5			with gr7 = gr7 xor gr6;	//		CRC32 = CRC32 ^t;		
		gr1 = gr0 >> 8;								//		b = a >> 8;		
		gr1 = gr1 and gr2;							//		b = b & 0x000000FF;		
		gr3 = gr7 and gr2;							//		c = CRC32 & 0x000000FF ;		
		gr4	= gr1 xor gr3;							//		addr=b^c;					
		gr6 = [ar4+=gr4]	with gr7>>=8;			//		t=pTable[addr];	CRC32 >>=8;	
		ar4 = ar5			with gr7 = gr7 xor gr6;	//		CRC32 = CRC32 ^t;		
		gr1 = gr0 >> 16;							//		b = a >> 16;		
		gr1 = gr1 and gr2;							//		b = b & 0x000000FF;		
		gr3 = gr7 and gr2;							//		c = CRC32 & 0x000000FF ;		
		gr4	= gr1 xor gr3;							//		addr=b^c;		
		gr6	= [ar4+=gr4]	with gr7>>= 8;			//		t=pTable[addr];	CRC32 >>= 8 ;		
		ar4 = ar5			with gr7 = gr7 xor gr6;	//		CRC32 = CRC32 ^ t;		
		gr1 = gr0 >> 24;							//		b = a >> 24;		
		gr1 = gr1 and gr2;							//		b = b & 0x000000FF;		
		gr3 = gr7 and gr2;							//		c = CRC32 & 0x000000FF ;		
		gr4	= gr1 xor gr3;							//		addr=b^c;		
		gr6	= [ar4+=gr4]	with gr5--;				//		t=pTable[addr];		
	if <>0 delayed goto _Next_CRC32;					//		i++		
		ar4 = ar5			with gr7>>= 8;			//		CRC32 >>= 8 		
		gr0	=[ar0++]		with gr7 = gr7 xor gr6;	//		a=pSrcVec[i++];CRC32 = CRC32 ^ t;
	
	<_End_CRC32>	
	gr7 = not gr7;									//	CRC32 = ~ CRC32;
	//[ar6] = gr7;
	pop ar6,gr6;
	pop ar5,gr5;
	pop ar4,gr4;
	pop ar3,gr3;
	pop ar2,gr2;
	pop ar1,gr1;
	pop ar0,gr0;
	
return;	


end ".text_nmplv";
