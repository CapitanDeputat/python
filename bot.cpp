//функци€ выбирает сложное движение боту(уклонение от игрока и €блока)
/*
	bot - ссылка на бота
	enemy - вражеска€ зме€(игрок)
	apple -  €блоко
*/
//возвращает ложь если бот столкнулс€ с собой
bool hardMode(Snake* bot, Snake enemy, Apple apple)
{
	
	return res;
}
//функци€ выбирает простое движение боту(стремление к €блоку, попытка не задеть хвост)
/*
	bot - ссылка на бота
	enemy - вражеска€ зме€(игрок)
	apple -  €блоко
*/
//возвращает ложь если бот столкнулс€ с собой
bool normalMode(Snake* bot, Snake enemy, Apple apple)
{
	int botX = bot->getSnakeX();
	int botY = bot->getSnakeY();
	int appX = apple.getApple—oordX();
	int appY = apple.getApple—oordY();
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


//функци€ выбирает самое простое движение боту(стремление к €блоку)
/*
	bot - ссылка на бота
	enemy - вражеска€ зме€(игрок)
	apple -  €блоко
*/
//возвращает ложь если бот столкнулс€ с собой
bool goToApple(Snake* bot, Snake enemy, Apple apple)
{

	return res;
}

//‘ункци€ выбирает движение боту
/*
	bot - ссылка на бота
	level - уровень сложности
	enemy - вражеска€ зме€(игрок)
	apple -  €блоко
*/
//возвращает ложь если бот столкнулс€ с собой
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
