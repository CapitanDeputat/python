#include "Snake.h"

//����������� ������ 
Snake::Snake() {
	snakeSize = SNAKE_SIZE;
	maxX = 0;
	maxY = 0;
	snakeHead.setSize(sf::Vector2f(snakeSize, snakeSize));
	snakeHead.setFillColor(sf::Color::Yellow);

	snakeBodySegment.setSize(sf::Vector2f(snakeSize, snakeSize));
	snakeBodySegment.setFillColor(sf::Color::Yellow);

	snakeX = 0;
	snakeY = 0;

	snakeHead.setPosition(snakeX * snakeSize, snakeY * snakeSize);

	snakeBody.push_back(Line(0, 1));

	direction = UP;
}

//���������� � �����������
Snake::Snake(int x, int y, int width, int height, sf::Color SnakeColor)
{
	maxX = width / SNAKE_SIZE - 1;
	maxY = height / SNAKE_SIZE - 1;
	snakeSize = SNAKE_SIZE;

	snakeHead.setSize(sf::Vector2f(snakeSize, snakeSize));
	snakeHead.setFillColor(SnakeColor);

	snakeBodySegment.setSize(sf::Vector2f(snakeSize, snakeSize));
	snakeBodySegment.setFillColor(SnakeColor);

	snakeX = x;
	snakeY = y;

	snakeHead.setPosition(snakeX * snakeSize, snakeY * snakeSize);

	snakeBody.push_back(Line(x, y + 1)); //Add one body segment behind head

	direction = UP;
}

//������� ��������� ��������� ������ �� x � y
int Snake::getSnakeX()
{
	return snakeX;
}

int Snake::getSnakeY()
{
	return snakeY;
}

//������� ����������� ������
void Snake::drawSnake(sf::RenderWindow& window)
{
	for (std::vector<Line>::iterator i = snakeBody.begin(); i != snakeBody.end(); i++)
	{
		snakeBodySegment.setPosition(i->getNowX() * snakeSize, i->getNowY() * snakeSize);
		window.draw(snakeBodySegment);
	}


	window.draw(snakeHead);
}

//������� ��� ��������� ����������� �������� ������
void Snake::setSnakeDirection(Snake::MoveDirection dir)
{
	//���� ������������ ������ ���������� ��������������� ��������
	if ((dir == LEFT && direction == RIGHT) || (dir == RIGHT && direction == LEFT))
		return;

	if ((dir == UP && direction == DOWN) || (dir == DOWN && direction == UP))
		return;

	direction = dir;
}

//������� ��� �������� ������ 
//���������� �������� false, ���� �������� �� ������� (��������, ������������)
bool Snake::moveSnake()
{
	int oldX, oldY;
	oldX = snakeX;
	oldY = snakeY;

	switch (direction)
	{
	case Snake::UP:
		snakeY--;
		break;

	case Snake::DOWN:
		snakeY++;
		break;

	case Snake::LEFT:
		snakeX--;
		break;

	case Snake::RIGHT:
		snakeX++;
		break;
	}

	if (snakeX >= maxX)
		snakeX = 1;

	if (snakeX < 1)
		snakeX = maxX - 1;

	if (snakeY >= maxY)
		snakeY = 1;

	if (snakeY < 1)
		snakeY = maxY - 1;

	//����, ����� ���� ������� ����������� ����
	for (unsigned int i = 0; i < snakeBody.size(); i++)
		if (snakeX == snakeBody[i].getNowX() && snakeY == snakeBody[i].getBeforeY())
			return false;

	snakeHead.setPosition(sf::Vector2f(snakeX * snakeSize, snakeY * snakeSize));

	snakeBody[0].changePos(oldX, oldY);

	//���� ��������� ������ 1, ����������� �� ����
	if (snakeBody.size() > 1)
		for (unsigned int i = 1; i < snakeBody.size(); i++)
			snakeBody[i].changePos(snakeBody[i - 1].getBeforeX(), snakeBody[i - 1].getBeforeY());

	return true;
}

//������� ��� ���������� � ������ +1 ������
void Snake::addSegment(int x, int y)
{
	Line vec(snakeX, snakeY);
	snakeBody.insert(snakeBody.begin(), vec);

	snakeX = x;
	snakeY = y;
}

//������� ��� �������� ������������ ������ � ���-��
bool Snake::collideWithSnake(int x, int y)
{
	if (x == snakeX && y == snakeY)
		return true;

	for (std::vector<Line>::iterator i = snakeBody.begin(); i != snakeBody.end(); i++)
		if (x == i->getNowX() && y == i->getNowY())
			return true;

	return false;
}


//������� ��� ��������� ����������� �������� ������
Snake::MoveDirection Snake::getSnakeDirection()
{
	return direction;
}
