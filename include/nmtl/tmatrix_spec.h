   /////////////////////////////////////////////////////////////////////////////
//                                                                         // 
//  Header file of template of class mtr                                //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////
#ifndef _TMATRIX_SPEC_H_INCLUDED_
#define _TMATRIX_SPEC_H_INCLUDED_

//#include "tnmtl.h"
		
//THIS FUNCTIONS WAS INSERTED FROM OLD VERSION OF THIS FILE!!!!!!!!!!!!!!!!!!!!!!!!!!
template<>
mtr<double>&  mtr<double>::operator<<=	(const int Shl)
{
	int m_size=m_height*m_width;
	//double n=pow(2,Shl);
	double n=1<<Shl;
	for(int i=0;i<m_size;i++)
		m_data[i]*=n;
	return (*this);
}	
//THIS FUNCTIONS WAS INSERTED FROM OLD VERSION OF THIS FILE!!!!!!!!!!!!!!!!!!!!!!!!!!


#endif
