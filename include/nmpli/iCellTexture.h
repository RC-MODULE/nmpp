//------------------------------------------------------------------------
//
//  $Workfile:: CellTexture.h             $
//
//  <Название библиотеки>
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2005/02/10 12:36:38 $
//
//! \if file_doc
//!
//! \file   CellTexture.h
//! \author Sergey V. Vaganov esq.
//! \brief  <Краткое описание>
//!
//! \endif
//!
//------------------------------------------------------------------------
#ifndef __CELLTEXTURE_H
#define __CELLTEXTURE_H


//Класс определяет точку на плоскости
class RPoint {
 public:
	double x;
	double y;


	//virtual ~RPoint() {};


	RPoint() : x(0), y(0)
	{
	}

	RPoint(const RPoint &p) : x(p.x), y(p.y)
	{
	}

	RPoint (double _x, double _y) :x(_x), y(_y)
	{
	}

	RPoint &operator= (const RPoint &p)
	{
		x = p.x; y = p.y;
		return (*this);
	}


};




	/**
	\internal
	\defgroup CellTexture CellTexture
	\ingroup iInit
	\brief
		\ru Создание "клеточной" текстуры на изображении
		\en Creates  "cell" texture on image

		\~
	\~
	\param width
      \ru Ширина изображения; 
      \en Image width; 
		\~
	\param height
      \ru Высота изображения. 
      \en Image height. 

		\~
  \retval texture_img		
      \ru Результирующее изображение; 
      \en Output image. 
	  \~


	*/
//! \{
void IMG_CreateCellTexture(unsigned char *texture_img, int width, int height);
void IMG_CreateRandomCellTexture(unsigned char *texture_img, int width, int height);
void IMG_CreateComplexTexture(unsigned char *texture_img, int width, int height);
//! \}


	/**
	\internal
	\defgroup PointInRectangle PointInRectangle
	\ingroup iCell
	\brief
		\ru определяет, находится ли точка внутри четырехугольника
		\en

	\~
	\param p
		\ru координаты точки
		\en
	\param borders
		\ru координаты вершин четырехугольника
		\en

	\return 1 - внутри, 0 - снаружи
	*/
//! \{
int PointInRectangle(RPoint& p, RPoint *borders);
//! \}

#endif
