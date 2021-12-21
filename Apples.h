#pragma once

#include <cstdlib>
#include <SFML/Graphics.hpp>

class Apple
{
private:
	int apple—oordX, apple—oordY; 
	int appleSize; 
	int windowWidth;
	int windowHeight;
	sf::CircleShape appleShape;

public:
	Apple(int width, int height, int size);
	void newApple();
	int getApple—oordX();
	int getApple—oordY();
	void drawApple(sf::RenderWindow& window);
};
