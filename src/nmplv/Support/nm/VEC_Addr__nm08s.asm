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
    //! \fn nm8s * nmppsAddr_8s(nm8s *pVec, int nIndex) 
	//!
	//! \perfinclude _nmppsAddr__FPci_.html
    //--------------------------------------------------------------------
	   
global _char._.0.8.8nmppsAddr_.1char._const._.0.9._int.2 :label;
<_char._.0.8.8nmppsAddr_.1char._const._.0.9._int.2>
.branch;
	ar5 = sp-4 with gr7=gr5;	
	gr5 = [ar5++];
	ar5 = [ar5++] with gr5 A>>=2;
delayed return;
	nul;
	ar5+=gr5   with gr5 = gr7;
	nul;
.wait;

  

end ".text_nmplv";

