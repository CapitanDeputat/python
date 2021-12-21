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
