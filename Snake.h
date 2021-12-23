#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Line.h"
#define SNAKE_SIZE 30 

class Snake
{
public:
	enum MoveDirection { UP, DOWN, LEFT, RIGHT };
	Snake();
	Snake(int x, int y, int width, int height, sf::Color SnakeColor); //    
	void drawSnake(sf::RenderWindow& window);
	int getSnakeX();
	int getSnakeY(); 
	bool moveSnake();
	MoveDirection getSnakeDirection()
	void setSnakeDirection(MoveDirection dir);
	void addSegment(int x, int y);
	bool collideWithSnake(int x, int y);
	std::vector <Line> snakeBody;

private:
	int snakeSize;
	int snakeX;
	int snakeY;
	int maxX;
	int maxY;


	sf::RectangleShape snakeHead;
	sf::RectangleShape snakeBodySegment;

	MoveDirection direction;

};
