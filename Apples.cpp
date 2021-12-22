#include "Apples.h"

//конструктор с параметрами(ширина экрана, высота экрана, размер яблока)
Apple::Apple(int width, int height, int size)
{
	windowWidth = width;
	windowHeight = height;
	appleSize = size;
	appleСoordX = rand() % (windowWidth / size - 2) + 1;
	appleСoordY = rand() % (windowHeight / size - 2) + 1;

	appleShape.setRadius(appleSize / 2);
	appleShape.setFillColor(sf::Color::Red);
	appleShape.setPosition(appleСoordX * appleSize, appleСoordY * appleSize);
}


//Функция генерирует новое яблоко
void Apple::newApple()
{
	appleСoordX = rand() % (windowWidth / appleSize - 2) + 1;
	appleСoordY = rand() % (windowHeight / appleSize - 2) + 1;

	appleShape.setPosition(appleСoordX * appleSize, appleСoordY * appleSize);
}


