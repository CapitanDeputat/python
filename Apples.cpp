#include "Apples.h"

//����������� � �����������(������ ������, ������ ������, ������ ������)
Apple::Apple(int width, int height, int size)
{
	windowWidth = width;
	windowHeight = height;
	appleSize = size;
	apple�oordX = rand() % (windowWidth / size - 2) + 1;
	apple�oordY = rand() % (windowHeight / size - 2) + 1;

	appleShape.setRadius(appleSize / 2);
	appleShape.setFillColor(sf::Color::Red);
	appleShape.setPosition(apple�oordX * appleSize, apple�oordY * appleSize);
}


//������� ���������� ����� ������
void Apple::newApple()
{
	apple�oordX = rand() % (windowWidth / appleSize - 2) + 1;
	apple�oordY = rand() % (windowHeight / appleSize - 2) + 1;

	appleShape.setPosition(apple�oordX * appleSize, apple�oordY * appleSize);
}


