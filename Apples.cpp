#include "Apples.h"

//конструктор с параметрами(ширина экрана, высота экрана, размер яблока)
Apple::Apple(int width, int height, int size)
{
	windowWidth = width;
	windowHeight = height;
	appleSize = size;
	appleСoordX = rand() % (windowWidth / size - 2) + 1;
	appleСoordY = rand() % (windowHeight / size - 2) + 1;

	appleShape.setPointCount(8);

	// Устанавливаем координаты вершин
	appleShape.setPoint(0, sf::Vector2f(0 , appleSize));
	appleShape.setPoint(1, sf::Vector2f(appleSize ,0 ));
	appleShape.setPoint(2, sf::Vector2f(appleSize, appleSize));

	appleShape.setFillColor(sf::Color::Magenta);
	appleShape.setPosition(appleСoordX * appleSize, appleСoordY * appleSize);
}


//Функция генерирует новое яблоко
void Apple::newApple()
{
	appleСoordX = rand() % (windowWidth / appleSize - 2) + 1;
	appleСoordY = rand() % (windowHeight / appleSize - 2) + 1;

	appleShape.setPosition(appleСoordX * appleSize, appleСoordY * appleSize);
}


//Функции возвращающие координаты яблока 
int Apple::getAppleСoordX()
{
	return appleСoordX;
}

int Apple::getAppleСoordY()
{
	return appleСoordY;
}

//Функция отрисовывает яблоко в окне, которое передано в качестве параметра
void Apple::drawApple(sf::RenderWindow& window)
{
	window.draw(appleShape);
}
