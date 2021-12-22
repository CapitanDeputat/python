#include "Line.h"
//Конструктор с параметрами
Line::Line(int x, int y)
{
	nowX = x;
	nowY = y;
	beforeX = 0;
	beforeY = 0;
}


//Функция изменяющая координаты
void Line::changePos(int x, int y)
{
	beforeX = nowX;
	beforeY = nowY;
	nowX = x;
	nowY = y;
}


//Функции возвращающие значения координат
int Line::getNowX()
{
	return nowX;
}

int Line::getNowY()
{
	return nowY;
}

int Line::getBeforeX()
{
	return beforeX;
}


int Line::getBeforeY()
{
	return beforeY;
}
