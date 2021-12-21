#pragma once
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <SFML/Graphics.hpp>


#define SCREEN_HEIGHT 600
#define SCREEN_WIDTH 800



class Game
{
private:
	enum GameState { STARTED, MENU, OPTIONS, OVER, ENDED, SINGLEPLAYER, MULTIMENU };
	GameState gameState;
	sf::RenderWindow renderWindow;

	sf::Text gameName;
	sf::Text menuStrings[17];
	sf::Text playersPoints;
	sf::Text botsPoints;
	sf::Text gameTime;
	sf::Text gameFinish[4];
	sf::Color SnakeColor = sf::Color::Red;
	std::string enteredChars;


	bool isGamePaused;
	std::vector <Snake> botsArr;
	sf::RectangleShape wallsCheckbox;
	sf::RectangleShape borderCheckbox;
	sf::RectangleShape gameBorder;
	sf::Font font;
	int inGameBotsCounter;
	std::string Colors[3] = { "Green" , "Magenta", "White" };
	Snake snake;
	std::string pointsText;
	std::string timeText;
	std::string nickName;
	void updateGame();
	void drawMenu();
	void drawSingleMenu();
	void startGame();
};
