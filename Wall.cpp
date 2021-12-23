#include "Wall.h"

//���������� ����������� � ����������� �����(������ ������, ������ ������, ������ �����)
Wall::Wall(int size, int width, int height)
{
	wallSize = size;
	int maxParts = (rand() % 11) + 10;

	int direction;
	int x = width / size / 2;
	int y = height / size / 2;
	//����������� ����� 
	partsOfWall.push_back(sf::Vector2f(x * size, y * size));

	for (int i = 1; i < maxParts; i++)
	{
		//����������� ����������� ����� �����
		direction = (rand() % 4) + 1;

		switch (direction)
		{
			//����
		case 1:
			y--;

			if (y < 1)
				y = height / size - 2;
			break;
			//���
		case 2:
			y++;

			if (y >= height / size - 2)
				y = 1;
			break;

			//����� �����
		case 3:
			x--;

			if (x < 1)
				x = width / size - 2;
			break;

			//������ �����
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
//�������, ����������� ������������ ����� �� ������
bool Wall::isWall(int x, int y)
{
	for (int i = 0; i < partsOfWall.size(); i++)
		if (partsOfWall[i].x / wallSize == x && partsOfWall[i].y / wallSize == y)
			return true;

	return false;
}
//�������, ���������� �� ��������� �����
void Wall::drawWall(sf::RenderWindow& window)
{
	for (int i = 0; i < partsOfWall.size(); i++)
	{
		wall.setPosition(partsOfWall[i]);
		window.draw(wall);
	}
}
