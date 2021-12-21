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
