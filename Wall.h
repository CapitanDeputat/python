#pragma once
#include <vector>
#include <cstdlib>

#include <SFML/Graphics.hpp>

class Wall
{
private:
	std::vector <sf::Vector2f> partsOfWall;
	sf::RectangleShape wall;
	int wallSize;

public:
	Wall(int size, int width, int height);
	bool isWall(int x, int y); 
	void drawWall(sf::RenderWindow& window);
};