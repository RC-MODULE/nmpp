#ifndef __PLESSY_H
#define __PLESSY_H

//class I_PlessyCornerDetector предназначен для поиска характерных точек на изображении по методу Plessy.
//На выходе выдаются коордитаты характерных точек с субпиксельной точностью.
class I_PlessyCornerDetector
{
public:
	//Распределяет память для полей класса. 
	//w, h, ww - ширина, высота и step картинки соответственно.
	virtual void Allocate(int w, int h, int ww) = 0;

	//Освобождает память, выделенную под поля класса.
	virtual void DeAllocate() = 0;

	//Собственно ищет углы. 
	//w, h, ww - as above. 
	//Picture - обрабатываемая картинка.
	//*px, *py - массивы x и y координат углов (размер массивов определяется снаружи, максимальное 
	//	значение - (w/2)*(h/2).
	//nc - количество найденных углов.
	virtual void FindCorners(unsigned char *Picture, int w, int h, int ww, float *px, float *py, int& nc) = 0;

	//Освобождает интерфейс объекта
	virtual void Release() = 0;

	//Устанавливает threshold, по которому порожится Plessy-массив. Для 16s обычно ставится 32.0f. 
	//Для 32f обычно ставится 1/1024.
	//Чем меньше порог, тем выше "качество" угла
	virtual void SetThreshold(float _threshold)=0;
};

//Тип реализации (float и short соответственно)
enum PCD_TYPE {PCD_32f, PCD_16s};

//Создает объект и возвращает интерфейс I_PlessyCornerDetector
I_PlessyCornerDetector* CreatePlessyCornerDetector(PCD_TYPE type);


#endif