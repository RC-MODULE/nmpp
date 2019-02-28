////////////////////////////////////////////////////////////////////
//
//
//  NMPP library 
//
//  Copyright (c) RC Module Inc.
//
//  12:24 05.02.2015
//
//! \if file_doc
//!
//! \file   iPRINT.h
//! \author S. Mushkaev
//! \brief  Graphic text print functions
//!
//! \endif
//!
////////////////////////////////////////////////////////////////////

#ifndef _IPRINT_H_INCLUDED_
#define _IPRINT_H_INCLUDED_

	
 /**
 *  \ingroup nmppiPrint
 *  \brief  Prints text over 8-bit grayscale image buffer with 8x15 font size. 
 *  
 *  \param [in] str String to be printed
 *  \param [in] img Pointer to 8-bit grayscale image , where text should be printed 
 *  \param [in] imgWidth Image width
 *  \param [in] x Horizontal positon in image where text should be printed 
 *  \param [in] y Vertical   positon in image where text should be printed 
 *  \param [in] FGcolor Foreground text color
 *  \param [in] BGcolor Background text color
 *  \return x-coordinate behind printed text 
 *  
 *  \note Russian text is supported in win-1251 codepage
 */
 //! \{
 int nmppiPrint8x15( char *str, void* img, int imgWidth, int x, int y ,int FGcolor, int BGcolor);
//! \}

/**
 *  \ingroup nmppiPrint
 *  \brief  Converts integer to 8-byte string in hexadecimal base
 *  \param [in] value Value to be converted to a string 
 *  \param [in] str Array in memory where to store the resulting null-terminated string
 *  \return A pointer to the resulting null-terminated string, same as parameter str.
 *  
 *  \details Details
 */
 //! \{
 char* hex2ascii(int value, char* str);
//! \}

/**
 *  \ingroup nmppiPrint
 *  \brief Converts integer to 8-byte string in hexadecimal base
 *  \param [in] value Value to be converted to a string 
  * \return A pointer to the global resulting null-terminated string
 *  
 *  \note Function uses internal string buffer for result. Previous result of call this function will be overwritten.
 */
  //! \{
//char* hex2ascii(int value);
//! \}

#endif // _IPRINT_H_INCLUDED_


