#include "Wall.h"

//Реализовал конструктор с параметрами стены(ширина экрана, высота экрана, размер стены)
Wall::Wall(int size, int width, int height)
{
	wallSize = size;
	int maxParts = (rand() % 11) + 10;

	int direction;
	int x = width / size / 2;
	int y = height / size / 2;
	//Центральная часть 
	partsOfWall.push_back(sf::Vector2f(x * size, y * size));

	for (int i = 1; i < maxParts; i++)
	{
		//Определение направления новой части
		direction = (rand() % 4) + 1;

		switch (direction)
		{
			//Верх
		case 1:
			y--;

			if (y < 1)
				y = height / size - 2;
			break;
			//Низ
		case 2:
			y++;

			if (y >= height / size - 2)
				y = 1;
			break;

			//Левая часть
		case 3:
			x--;

			if (x < 1)
				x = width / size - 2;
			break;

			//Правая часть
		case 4:
			x++;

			if (x >= width / size - 2)
				x = 1;
			break;
		}
		partsOfWall.push_back(sf::Vector2f(x * size, y * size));
	}

	wall.setSize(sf::Vector2f(size, size));
	wall.setFillColor(sf::Color::Cyan);
}
//Функция, проверяющая столкновение точки со стеной
bool Wall::isWall(int x, int y)
{
	for (int i = 0; i < partsOfWall.size(); i++)
		if (partsOfWall[i].x / wallSize == x && partsOfWall[i].y / wallSize == y)
			return true;

	return false;
}
//Функция, отвечающая за отрисовку стены
void Wall::drawWall(sf::RenderWindow& window)
{
	for (int i = 0; i < partsOfWall.size(); i++)
	{
		wall.setPosition(partsOfWall[i]);
		window.draw(wall);
	}
}
