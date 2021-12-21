#include "bot.h"
//функция выбирает сложное движение боту(уклонение от игрока и яблока)
/*
	bot - ссылка на бота
	enemy - вражеская змея(игрок)
	apple -  яблоко
*/
//возвращает ложь если бот столкнулся с собой
bool hardMode(Snake* bot, Snake enemy, Apple apple)
{
	int botX = bot->getSnakeX();
	int botY = bot->getSnakeY();
	int appX = apple.getAppleСoordX();
	int appY = apple.getAppleСoordY();
	std::vector <int> enemyCoordsX;
	std::vector <int> enemyCoordsY;
	int playerHeadX = enemy.getSnakeX();
	int playerHeadY = enemy.getSnakeY();
	int counter = 0;
	for (std::vector<Line>::iterator i = enemy.snakeBody.begin(); i != enemy.snakeBody.end(); i++) {
		int x = i->getNowX();
		int y = i->getNowY();
		enemyCoordsX.push_back(x);
		enemyCoordsY.push_back(y);
		counter++;
	}
	int playerBackX = enemyCoordsX[counter - 1];
	int playerBackY = enemyCoordsY[counter - 1];
	int playerBackMinX = enemyCoordsX[counter - 1];
	int playerBackMinY = enemyCoordsY[counter - 1];
	for (int i = 0; i < counter - 1; i++) {
		if (enemyCoordsX[i] > playerBackX) {
			playerBackX = enemyCoordsX[i];
		}
		if (enemyCoordsY[i] > playerBackY) {
			playerBackY = enemyCoordsY[i];
		}
		if (enemyCoordsX[i] < playerBackMinX) {
			playerBackMinX = enemyCoordsX[i];
		}
		if (enemyCoordsY[i] < playerBackMinY) {
			playerBackMinY = enemyCoordsY[i];
		}
	}
	if (playerHeadX < playerBackX) {
		int remp = playerBackX;
		playerBackX = playerHeadX;
		playerHeadX = remp;
	}
	if (playerHeadY < playerBackY) {
		int remp2 = playerBackY;
		playerBackY = playerHeadY;
		playerHeadY = remp2;
	}
	if (playerBackMinX < playerBackX) {
		playerBackX = playerBackMinX;
	}
	if (playerBackMinY < playerBackY) {
		playerBackY = playerBackMinY;
	}
	Snake::MoveDirection botDir = bot->getSnakeDirection();
	if ((botY <= playerHeadY) && (botY >= playerBackY)) {
		if (((botX == (playerHeadX - 1)) || (botX == (playerBackX - 1))) && (bot->getSnakeDirection() == Snake::RIGHT))
			bot->setSnakeDirection(Snake::DOWN);
		if (((botX == (playerHeadX + 1)) || (botX == (playerBackX + 1))) && (bot->getSnakeDirection() == Snake::LEFT))
			bot->setSnakeDirection(Snake::DOWN);
	}
	else {
		if (botX <= playerHeadX && botX >= playerBackX) {
			if (((botY == (playerHeadY - 1)) || (botY == (playerBackY - 1))) && (bot->getSnakeDirection() == Snake::DOWN))
				bot->setSnakeDirection(Snake::LEFT);
			if (((botY == (playerHeadY + 1)) || (botY == (playerBackY + 1))) && (bot->getSnakeDirection() == Snake::UP))
				bot->setSnakeDirection(Snake::LEFT);
		}
	}

	if ((botX == appX) && (botY == (appY + 1)) && (bot->getSnakeDirection() == Snake::UP)) {
		bot->setSnakeDirection(Snake::RIGHT);
	}
	if ((botX == appX) && (botY == (appY - 1)) && (bot->getSnakeDirection() == Snake::DOWN)) {
		bot->setSnakeDirection(Snake::RIGHT);
	}
	if ((botY == appY) && (botX == (appX - 1)) && (bot->getSnakeDirection() == Snake::RIGHT)) {
		bot->setSnakeDirection(Snake::UP);
	}
	if ((botY == appY) && (botX == (appX + 1)) && (bot->getSnakeDirection() == Snake::LEFT)) {
		bot->setSnakeDirection(Snake::UP);
	}

	bool res = bot->moveSnake();
	return res;
}
//функция выбирает простое движение боту(стремление к яблоку, попытка не задеть хвост)
/*
	bot - ссылка на бота
	enemy - вражеская змея(игрок)
	apple -  яблоко
*/
//возвращает ложь если бот столкнулся с собой
bool normalMode(Snake* bot, Snake enemy, Apple apple)
{
	int botX = bot->getSnakeX();
	int botY = bot->getSnakeY();
	int appX = apple.getAppleСoordX();
	int appY = apple.getAppleСoordY();
	std::vector <int> botCoordsX;
	std::vector <int> botCoordsY;
	int botHeadX = bot->getSnakeX();
	int botHeadY = bot->getSnakeY();
	int counter = 0;
	for (std::vector<Line>::iterator i = bot->snakeBody.begin(); i != bot->snakeBody.end(); i++) {
		int x = i->getNowX();
		int y = i->getNowY();
		botCoordsX.push_back(x);
		botCoordsY.push_back(y);
		counter++;
	}
	int botBackX = botCoordsX[counter - 1];
	int botBackY = botCoordsY[counter - 1];
	for (int i = 0; i < counter - 1; i++) {
		if (botCoordsX[i] > botBackX) {
			botBackX = botCoordsX[i];
		}
		if (botCoordsY[i] > botBackY) {
			botBackY = botCoordsY[i];
		}
	}
	if (botHeadX < botBackX) {
		int remp = botBackX;
		botBackX = botHeadX;
		botHeadX = remp;
	}
	if (botHeadY < botBackY) {
		int remp2 = botBackY;
		botBackY = botHeadY;
		botHeadY = remp2;
	}
	Snake::MoveDirection botDir = bot->getSnakeDirection();
	if ((botY <= botHeadY) && (botY >= botBackY)) {
		if (((botX == (botHeadX + 1)) || (botX == (botBackX + 1))) && (bot->getSnakeDirection() == Snake::LEFT))
			bot->setSnakeDirection(Snake::DOWN);
		if (((botX == (botHeadX - 1)) || (botX == (botBackX - 1))) && (bot->getSnakeDirection() == Snake::RIGHT))
			bot->setSnakeDirection(Snake::DOWN);
	}
	else {
		if (botX <= botHeadX && botX >= botBackX) {
			if (((botY == (botHeadY - 1)) || (botY == (botBackY - 1))) && (bot->getSnakeDirection() == Snake::DOWN))
				bot->setSnakeDirection(Snake::LEFT);
			if (((botX == (botHeadX + 1)) || (botX == (botBackX + 1))) && (bot->getSnakeDirection() == Snake::UP))
				bot->setSnakeDirection(Snake::LEFT);
		}
	}

	if (botDir == bot->getSnakeDirection()) {
		return goToApple(bot, enemy, apple);
	}
	return true;
}


//функция выбирает самое простое движение боту(стремление к яблоку)
/*
	bot - ссылка на бота
	enemy - вражеская змея(игрок)
	apple -  яблоко
*/
//возвращает ложь если бот столкнулся с собой
bool goToApple(Snake* bot, Snake enemy, Apple apple)
{
	int botX = bot->getSnakeX();
	int botY = bot->getSnakeY();
	int appX = apple.getAppleСoordX();
	int appY = apple.getAppleСoordY();
	Snake::MoveDirection botDir = bot->getSnakeDirection();
	if (botY != appY) {
		if ((botY < appY) && (bot->getSnakeDirection() != Snake::DOWN)) {
			switch (botDir)
			{

			case Snake::UP:
				bot->setSnakeDirection(Snake::LEFT);
				break;
			case Snake::LEFT:
				bot->setSnakeDirection(Snake::DOWN);
				break;
			case Snake::RIGHT:
				bot->setSnakeDirection(Snake::DOWN);
				break;
			}
		}
		if ((botY > appY) && (bot->getSnakeDirection() != Snake::UP)) {
			switch (botDir)
			{

			case Snake::DOWN:
				bot->setSnakeDirection(Snake::LEFT);
				break;
			case Snake::LEFT:
				bot->setSnakeDirection(Snake::UP);
				break;
			case Snake::RIGHT:
				bot->setSnakeDirection(Snake::UP);
				break;
			}
		}
	}
	else {
		if ((botX < appX) && (bot->getSnakeDirection() != Snake::RIGHT)) {
			switch (botDir)
			{

			case Snake::DOWN:
				bot->setSnakeDirection(Snake::RIGHT);
				break;
			case Snake::LEFT:
				bot->setSnakeDirection(Snake::UP);
				break;
			case Snake::UP:
				bot->setSnakeDirection(Snake::RIGHT);
				break;
			}
		}
		if ((botX > appX) && (bot->getSnakeDirection() != Snake::LEFT)) {
			switch (botDir)
			{

			case Snake::DOWN:
				bot->setSnakeDirection(Snake::LEFT);
				break;
			case Snake::RIGHT:
				bot->setSnakeDirection(Snake::UP);
				break;
			case Snake::UP:
				bot->setSnakeDirection(Snake::LEFT);
				break;
			}
		}
	}
	bool res = bot->moveSnake();
	return res;
}

//Функция выбирает движение боту
/*
	bot - ссылка на бота
	level - уровень сложности
	enemy - вражеская змея(игрок)
	apple -  яблоко
*/
//возвращает ложь если бот столкнулся с собой
bool chooseMove(Snake* bot, std::string level, Snake enemy, Apple apple)
{
	bool result = false;
	if (level == "insane")
		result = hardMode(bot, enemy, apple);
	if (level == "medium")
		result = normalMode(bot, enemy, apple);
	if (level == "easy")
		result = goToApple(bot, enemy, apple);

	if (enemy.collideWithSnake(bot->getSnakeX(), bot->getSnakeY()))
		result = false;
	return result;
}
