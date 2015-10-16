#ifndef __SUBPIXEL2D_H
#define __SUBPIXEL2D_H


//class I_2DSubPixelMinPosition предназначен для поиска субпиксельного минимума в массиве 3x3.
//Имеются две реализации - "параболическая" и "тригонометрическая"
class I_2DSubPixelMinPosition
{
public:

	//Ищет субпиксельный минимум
	//S9 - массив 3x3 с минимумом в центре квадрата.
	//dx, dy - координаты точки минимума относительно центра квадрата 3x3 (S9).
	virtual void Find(float *S9, float& dx, float& dy) = 0;

	//Освобождает указатель
	virtual void Release() = 0;

};

//Тип реализации ("параболическая" и "тригонометрическая" соответственно)
enum SPP_TYPE {SPP_par, SPP_trg};


//Создает объект и возвращает его интерфейс I_2DSubPixelMinPosition.
I_2DSubPixelMinPosition* Create2DSubPixelMinPosition(SPP_TYPE type);


#endif

