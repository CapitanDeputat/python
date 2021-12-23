#include "Line.h"
//����������� � �����������
Line::Line(int x, int y)
{
	nowX = x;
	nowY = y;
	beforeX = 0;
	beforeY = 0;
}


//������� ���������� ����������
void Line::changePos(int x, int y)
{
	beforeX = nowX;
	beforeY = nowY;
	nowX = x;
	nowY = y;
}


//������� ������������ �������� ���������
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
