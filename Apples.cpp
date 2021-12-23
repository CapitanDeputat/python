#include "Apples.h"

//����������� � �����������(������ ������, ������ ������, ������ ������)
Apple::Apple(int width, int height, int size)
{
	windowWidth = width;
	windowHeight = height;
	appleSize = size;
	apple�oordX = rand() % (windowWidth / size - 2) + 1;
	apple�oordY = rand() % (windowHeight / size - 2) + 1;

	appleShape.setPointCount(8);

	// ������������� ���������� ������
	appleShape.setPoint(0, sf::Vector2f(0 , appleSize));
	appleShape.setPoint(1, sf::Vector2f(appleSize ,0 ));
	appleShape.setPoint(2, sf::Vector2f(appleSize, appleSize));

	appleShape.setFillColor(sf::Color::Magenta);
	appleShape.setPosition(apple�oordX * appleSize, apple�oordY * appleSize);
}


//������� ���������� ����� ������
void Apple::newApple()
{
	apple�oordX = rand() % (windowWidth / appleSize - 2) + 1;
	apple�oordY = rand() % (windowHeight / appleSize - 2) + 1;

	appleShape.setPosition(apple�oordX * appleSize, apple�oordY * appleSize);
}


//������� ������������ ���������� ������ 
int Apple::getApple�oordX()
{
	return apple�oordX;
}

int Apple::getApple�oordY()
{
	return apple�oordY;
}

//������� ������������ ������ � ����, ������� �������� � �������� ���������
void Apple::drawApple(sf::RenderWindow& window)
{
	window.draw(appleShape);
}
