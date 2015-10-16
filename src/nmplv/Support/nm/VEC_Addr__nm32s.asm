//------------------------------------------------------------------------
//
//  $Workfile:: Access.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:11 $
//
//! \if file_doc
//!
//! \file   Access.asm
//! \author Сергей Мушкаев
//! \brief  Функции доступа для векторов.
//!
//! \endif
//!
//------------------------------------------------------------------------

//#include "vClip.h"



begin ".text_nmplv"

  
    //--------------------------------------------------------------------
    //! \fn nm32s * VEC_Addr (nm32s *pVec, int nIndex) 
	//!
	//! \perfinclude _VEC_Addr__FPii.html
    //--------------------------------------------------------------------

    
global _VEC_Addr__FPii:label;
global _int._.0.8.8VEC_Addr.1int._.0.9._int.2 :label;
<_VEC_Addr__FPii>
<_int._.0.8.8VEC_Addr.1int._.0.9._int.2>
.branch;
	ar5 = sp-2 with gr7=gr5;	
delayed return;
	ar5,gr5 = [--ar5];
	nul;
	ar5+=gr5 with gr5=gr7;
return;
.wait;


end ".text_nmplv";

