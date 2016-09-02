//////////////////////////////////////////////////////////////////////////
//                                                                      //
//               NeuroMatrix(r) C runtime library                       //
//                                                                      //
//		библиотека nm_io                                                //
//                                                                      //
//	Описывается пользовательский интерфейс хостовой части    			//
//                                                                      //
//  Copyright (c) 2004-2012 RC Module                                   //
//                                                                      //
//  Автор: Бирюков А.А.                                                 //
//////////////////////////////////////////////////////////////////////////

#include <iostream>

//	Рассчитываем на использование любой библиотеки загрузки и обмена
typedef unsigned long PL_Word;
typedef unsigned long PL_Addr;
struct PL_Access;

//	END #include "mc5101load.h"

class NM_IO_Service
{
    unsigned long datSecAddr;
    unsigned long bssSecAddr;
    unsigned long datSecSize;
    unsigned long bssSecSize;
    static bool work;
    PL_Access* a;
    int* bsStatus;
    int* bsBuf;
    int* readStatus();
    void writeBackStatus();
    volatile bool letsShutDown;
    unsigned int dispatch();
	bool valid;
	std::ostream* nm_cout;
//    NM_IO_Service( const char* fName, PL_Access* acc );
	PL_Word processPrintf( int* bufferFromBoard, int received  );
public:
	bool invalid() const {	return !valid; }
    NM_IO_Service( const char* fName, PL_Access* access, std::ostream* _cout= &std::cout, 
							std::ostream* _cerr= &std::cerr, std::istream* _cin= &std::cin );
    ~NM_IO_Service();
	friend unsigned int __stdcall nmServiceDispatcher( void* v_nms );
};