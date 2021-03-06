#pragma once
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <SFML/Graphics.hpp>

#include "Snake.h"
#include "Apples.h"
#include "Wall.h"
#include "Bot.h"

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
	sf::Text pause;
	sf::Color SnakeColor = sf::Color::Red;
	std::string enteredChars;


	bool isGamePaused;
	std::vector <Snake> botsArr; 
	sf::RectangleShape wallsCheckbox;
	sf::RectangleShape borderCheckbox;
	sf::RectangleShape gameBorder;
	sf::Font font;
	int points = 0;
	int playTime;
	int pointsBot = 0;
	int botsCounter = 0;
	int roundsCounter = 1;
	int roundsOfBotsWins = 0;
	int roundsOfPlayerWins = 0;
	int nowRounds = 0; 
	int inGameBotsCounter;
	int iter = 0;
	std::string Colors[3] = { "Green" , "Magenta", "White" };
	Snake snake;
	std::string pointsText;
	std::string timeText;
	std::string nickName;
	void updateGame();
	void drawMenu();
	void drawGame();
	void gameOver();
	void drawSingleMenu();
	void drawMultiMenu();
public:
	enum botsMode { EASY, NORMAL, INSANE, DEAD, PLAYER, REDDEAD, GREENDEAD, DRAW }; //BotsLevel
	botsMode botMode; 
	Game();
	void startGame();
};
