#include "Game.h"
std::string convertNumToString(int num) {
	std::string result = "";
	if (num == 0) {
		result += '0';
	}
	while (num != 0) {
		result += num % 10 + '0';
		num /= 10;
	}
	for (int i = 0; i < result.length() / 2; i++) {
		std::swap(result[i], result[result.length() - 1 - i]);
	}
	return result;
}





//Конструктор класса
Game::Game()
{
	renderWindow.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Snake");
	renderWindow.setVerticalSyncEnabled(true);

	gameState = MENU;

	srand(time(0));

	isGamePaused = false;
}


//Функция, которая отвечает за действия пользователя(начало/конец игры, вызов меню, выбор одиночного/многопользовательского режимов игры)
void Game::updateGame()
{
	switch (gameState)
	{
	case Game::MENU:
		drawMenu();
		break;

	case Game::STARTED:
		drawGame();
		break;

	case Game::OVER:
		nowRounds = 0;


		gameOver();
		break;

	case Game::ENDED:
		renderWindow.close();
		return;
		break;
	case Game::SINGLEPLAYER:
		drawSingleMenu();
		break;
	}
}


//Основной функционал игры
void Game::drawGame()
{

	int snakeX, snakeY;
	bool isFirst = true;

	//Установка змеи в центре экрана
	snakeX = SCREEN_WIDTH / SNAKE_SIZE / 2;
	snakeY = SCREEN_HEIGHT / SNAKE_SIZE / 2;
	pointsText = "";
	Apple app(SCREEN_WIDTH, SCREEN_HEIGHT, SNAKE_SIZE);

	Wall wall(SNAKE_SIZE, SCREEN_WIDTH, SCREEN_HEIGHT);
	//Если змея генерируется внутри стены - сгенерировать новую
	while ((wall.isWall(snakeX, snakeY) || wall.isWall(snakeX, snakeY + 1)))
	{
		snakeX = rand() % (SCREEN_WIDTH / SNAKE_SIZE - 6 + 1) + 2;
		snakeY = rand() % (SCREEN_HEIGHT / SNAKE_SIZE - 6 + 1) + 2;
		isFirst = false;
	}

	//Столкновение с стеной 
	while ((wall.isWall(snakeX, snakeY) || wall.isWall(snakeX, snakeY + 1)) && (isFirst == false))
	{
		gameState = OVER;
		updateGame();
	}

	//Если яблоко генерируется внутри стены - сгенерировать новое
	while (wall.isWall(app.getAppleСoordX(), app.getAppleСoordY()))
	{
		app.newApple();
	}

	//Создаем змей
	if (inGameBotsCounter == botsCounter) {

		Snake newSnake(snakeX, snakeY, SCREEN_WIDTH, SCREEN_HEIGHT, SnakeColor);
		snake = newSnake;
	}

	if (botMode == PLAYER && botsArr.empty()) {
		int snakeBotX = SCREEN_WIDTH / SNAKE_SIZE / 2;
		int snakeBotY = SCREEN_HEIGHT / SNAKE_SIZE / 2;

		while ((wall.isWall(snakeBotX, snakeBotY) || wall.isWall(snakeBotX, snakeBotY + 1)) || ((snakeBotX == snakeX) && ((snakeBotY == snakeY) || (snakeBotY == snakeY + 1))))
		{
			snakeBotX = rand() % (SCREEN_WIDTH / SNAKE_SIZE - 6 + 1) + 2;
			snakeBotY = rand() % (SCREEN_HEIGHT / SNAKE_SIZE - 6 + 1) + 2;
		}
		Snake newSnake(snakeBotX, snakeBotY, SCREEN_WIDTH, SCREEN_HEIGHT, sf::Color::Red);
		botsArr.push_back(newSnake);
	}

	if (botsArr.empty() && botMode != PLAYER) {
		for (int i = 0; i < inGameBotsCounter; i++) {//
			int snakeBotX = SCREEN_WIDTH / SNAKE_SIZE / 2;
			int snakeBotY = SCREEN_HEIGHT / SNAKE_SIZE / 2;
			for (int j = i - 1; j >= 0; j--) {
				while ((wall.isWall(snakeBotX, snakeBotY) || wall.isWall(snakeBotX, snakeBotY + 1)) || ((snakeBotX == snakeX) && ((snakeBotY == snakeY) || (snakeBotY == snakeY + 1))) || ((snakeBotX == botsArr[j].getSnakeX()) && ((snakeBotY == botsArr[j].getSnakeY()) || (snakeBotY == botsArr[j].getSnakeY() + 1))))
				{
					snakeBotX = rand() % (SCREEN_WIDTH / SNAKE_SIZE - 6 + 1) + 2;
					snakeBotY = rand() % (SCREEN_HEIGHT / SNAKE_SIZE - 6 + 1) + 2;
				}
			}
			Snake newSnake(snakeBotX, snakeBotY, SCREEN_WIDTH, SCREEN_HEIGHT, sf::Color::Yellow);
			botsArr.push_back(newSnake);
		}
	}

	//Рисуем границу
	gameBorder.setPosition(SNAKE_SIZE, SNAKE_SIZE);
	gameBorder.setSize(sf::Vector2f(SCREEN_WIDTH - SNAKE_SIZE * 2, SCREEN_HEIGHT - SNAKE_SIZE * 2));
	gameBorder.setFillColor(sf::Color::Black);
	gameBorder.setOutlineThickness(3);
	gameBorder.setOutlineColor(SnakeColor);

	playersPoints.setFont(font);
	playersPoints.setCharacterSize(20);
	playersPoints.setPosition(SNAKE_SIZE, 0);
	playersPoints.setFillColor(sf::Color::Green);

	botsPoints.setFont(font);
	botsPoints.setCharacterSize(20);
	botsPoints.setPosition(SNAKE_SIZE * 300 / SNAKE_SIZE, 0);
	botsPoints.setFillColor(sf::Color::Red);


	gameTime.setFont(font);
	gameTime.setCharacterSize(20);
	gameTime.setPosition(SNAKE_SIZE + 450, 0);

	std::ostringstream sstreamBuffer;

	sf::Clock playClock;
	float elapsedPauseTime = 0;

	sf::Clock gameClock;
	float elapsedGameTime = 0.0f;
	float timeStep;

	sf::Clock pauseTime;

	timeStep = 0.3f;

	sf::Event event;

	bool directionChanged = true;

	bool directionChangedSecondPlayer = true;
	while (gameState == Game::STARTED)
	{
		while (renderWindow.pollEvent(event))
		{
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
				for (int i = 0; i < 17; i++) {
					menuStrings[i].setString("");
				}
				gameState = MENU;
				botsCounter = 0;
				roundsOfBotsWins = 0;
				roundsOfPlayerWins = 0;
				nowRounds = 0;
				roundsCounter = 1;
				inGameBotsCounter = 0;
				while (!botsArr.empty()) {
					botsArr.pop_back();
				}
			}
			if (event.type == sf::Event::Closed) {
				gameState = ENDED;
				botsCounter = 0;
				roundsOfBotsWins = 0;
				roundsOfPlayerWins = 0;
				nowRounds = 0;
				roundsCounter = 1;
				inGameBotsCounter = 0;
				while (!botsArr.empty()) {
					botsArr.pop_back();
				}

			}

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P)
			{
				if (!isGamePaused)
				{
					isGamePaused = true;
					pauseTime.restart();
				}
				else
				{
					isGamePaused = false;
					elapsedGameTime -= pauseTime.getElapsedTime().asSeconds();

					elapsedPauseTime += pauseTime.getElapsedTime().asSeconds();
				}
			}
		}

		bool result = true;

		for (int i = 0; i < inGameBotsCounter; i++) {

			if (botsArr[i].getSnakeX() == app.getAppleСoordX() && botsArr[i].getSnakeY() == app.getAppleСoordY())
			{
				pointsBot++;
				botsArr[i].addSegment(app.getAppleСoordX(), app.getAppleСoordY());

				app.newApple();



				//Если яблоки генерируются на змее - генерировать новые
				for (int j = 0; i < inGameBotsCounter; i++) {
					while (botsArr[j].collideWithSnake(app.getAppleСoordX(), app.getAppleСoordY()))
					{
						app.newApple();
					}
				}
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && directionChanged && !isGamePaused)
		{
			snake.setSnakeDirection(Snake::LEFT);
			directionChanged = false;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && directionChanged && !isGamePaused)
		{
			snake.setSnakeDirection(Snake::RIGHT);
			directionChanged = false;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && directionChanged && !isGamePaused)
		{
			snake.setSnakeDirection(Snake::UP);
			directionChanged = false;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && directionChanged && !isGamePaused)
		{
			snake.setSnakeDirection(Snake::DOWN);
			directionChanged = false;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && directionChanged && !isGamePaused && botMode == PLAYER)
		{
			botsArr[0].setSnakeDirection(Snake::UP);
			directionChanged = false;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && directionChanged && !isGamePaused && botMode == PLAYER)
		{
			botsArr[0].setSnakeDirection(Snake::LEFT);
			directionChanged = false;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && directionChanged && !isGamePaused && botMode == PLAYER)
		{
			botsArr[0].setSnakeDirection(Snake::DOWN);
			directionChanged = false;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && directionChanged && !isGamePaused && botMode == PLAYER)
		{
			botsArr[0].setSnakeDirection(Snake::RIGHT);
			directionChanged = false;
		}

		elapsedGameTime += gameClock.restart().asSeconds();
		bool canMove = true;

		//Если змея врезалась во что-либо

		if (botMode == PLAYER) {
			if (!botsArr[0].moveSnake()) {
				inGameBotsCounter = botsCounter;
				while (!botsArr.empty()) {
					botsArr.pop_back();
				}
				nowRounds++;
				roundsOfPlayerWins++;
				if (nowRounds >= roundsCounter) {
					gameState = OVER;
					if (roundsOfBotsWins > roundsOfPlayerWins) {
						botMode = GREENDEAD;
					}
					if (roundsOfBotsWins < roundsOfPlayerWins) {
						botMode = REDDEAD;
					}
					if (roundsOfBotsWins == roundsOfPlayerWins) {
						botMode = DRAW;
					}
				}
				updateGame();
			}
			if (!snake.moveSnake()) {
				nowRounds++;
				roundsOfBotsWins++;
				inGameBotsCounter = botsCounter;
				while (!botsArr.empty()) {
					botsArr.pop_back();
				}
				if (nowRounds >= roundsCounter) {
					gameState = OVER;
					botsCounter = 0;
					if (roundsOfBotsWins > roundsOfPlayerWins) {
						botMode = GREENDEAD;
					}
					if (roundsOfBotsWins < roundsOfPlayerWins) {
						botMode = REDDEAD;
					}
					if (roundsOfBotsWins == roundsOfPlayerWins) {
						botMode = DRAW;
					}
				}
				updateGame();
			}
			if ((botsArr[0].collideWithSnake(snake.getSnakeX(), snake.getSnakeY())) && (snake.collideWithSnake(botsArr[0].getSnakeX(), botsArr[0].getSnakeY()))) {
				updateGame();
			}
			else {
				if (botsArr[0].collideWithSnake(snake.getSnakeX(), snake.getSnakeY())) {
					roundsOfBotsWins++;
					nowRounds++;
					inGameBotsCounter = botsCounter;
					while (!botsArr.empty()) {
						botsArr.pop_back();
					}
					if (nowRounds >= roundsCounter) {
						botsCounter = 0;
						gameState = OVER;
						if (roundsOfBotsWins > roundsOfPlayerWins) {
							botMode = GREENDEAD;
						}
						if (roundsOfBotsWins < roundsOfPlayerWins) {
							botMode = REDDEAD;
						}
						if (roundsOfBotsWins == roundsOfPlayerWins) {
							botMode = DRAW;
						}
					}
					updateGame();
				}
				else
				{
					if (snake.collideWithSnake(botsArr[0].getSnakeX(), botsArr[0].getSnakeY())) {
						std::vector <Snake> newSnakesArr;
						for (int z = 0; z < i; z++) {
							newSnakesArr.push_back(botsArr[z]);
						}
						for (int z = i + 1; z < inGameBotsCounter; z++) {
							newSnakesArr.push_back(botsArr[z]);
						}
						botsArr = newSnakesArr;

						inGameBotsCounter--;
						if (inGameBotsCounter == 0) {
							inGameBotsCounter = botsCounter;
							while (!botsArr.empty()) {
								botsArr.pop_back();
							}
							roundsOfPlayerWins++;
							nowRounds++;
							if (nowRounds >= roundsCounter) {
								botsCounter = 0;
								if (roundsOfPlayerWins > roundsOfBotsWins) {
									botMode = REDDEAD;
								}
								if (roundsOfPlayerWins == roundsOfBotsWins) {
									botMode = DRAW;
								}
								if (roundsOfPlayerWins < roundsOfBotsWins) {
									botMode = GREENDEAD;
								}
								gameState = OVER;
							}


						}
						updateGame();
					}
				}
			}
		}

		if (botMode != PLAYER) {

			bool collideFlag = false;
			for (int j = 0; j < inGameBotsCounter; j++) {
				if (botsArr[j].collideWithSnake(botsArr[i].getSnakeX(), botsArr[i].getSnakeY()) && i != j) {
					collideFlag = true;
				}
			}
			if (snake.collideWithSnake(botsArr[i].getSnakeX(), botsArr[i].getSnakeY()) || (collideFlag)) {
				std::vector <Snake> newSnakesArr;
				for (int z = 0; z < i; z++) {
					newSnakesArr.push_back(botsArr[z]);
				}
				for (int z = i + 1; z < inGameBotsCounter; z++) {
					newSnakesArr.push_back(botsArr[z]);
				}
				botsArr = newSnakesArr;
				inGameBotsCounter--;
				if (inGameBotsCounter == 0) {
					inGameBotsCounter = botsCounter;
					while (!botsArr.empty()) {
						botsArr.pop_back();
					}
					roundsOfPlayerWins++;
					nowRounds++;
					if (nowRounds >= roundsCounter) {
						gameState = OVER;


						if (roundsOfBotsWins < roundsOfPlayerWins) {
							botMode = DEAD;
						}
						if (roundsOfBotsWins == roundsOfPlayerWins) {
							botMode = DRAW;
						}

					}
				}
				updateGame();
			}
			if (botsArr[i].collideWithSnake(snake.getSnakeX(), snake.getSnakeY())) {
				roundsOfBotsWins++;
				nowRounds++;
				inGameBotsCounter = botsCounter;
				while (!botsArr.empty()) {
					botsArr.pop_back();
				}
				if (nowRounds >= roundsCounter) {
					gameState = OVER;

					if (roundsOfBotsWins < roundsOfPlayerWins) {
						botMode = REDDEAD;
					}
					if (roundsOfBotsWins == roundsOfPlayerWins) {
						botMode = DRAW;
					}
				}
				updateGame();
			}
		}
	}
	directionChanged = true;

	elapsedGameTime -= timeStep;
}

if (snake.getSnakeX() == app.getAppleСoordX() && snake.getSnakeY() == app.getAppleСoordY())
{
	points++;
	snake.addSegment(app.getAppleСoordX(), app.getAppleСoordY());

	app.newApple();



	//Если яблоки генерируются на змее - сгенерировать новые
	for (int j = 0; j < inGameBotsCounter; j++) {
		while (snake.collideWithSnake(app.getAppleСoordX(), app.getAppleСoordY()) || botsArr[j].collideWithSnake(app.getAppleСoordX(), app.getAppleСoordY()))
		{
			app.newApple();
		}
	}

}

//Перевод чисел в строки, подготовка текста и установка sf::Text
pointsText = nickName + " Points:";
pointsText += (roundsCounter == 1) ? convertNumToString(points) : convertNumToString(roundsOfPlayerWins);
sstreamBuffer.str("");
sstreamBuffer.clear();
playersPoints.setString(pointsText);
playersPoints.setFillColor(SnakeColor);
pointsText = "";
pointsText = "Red points: ";
pointsText += (roundsCounter == 1 && botsCounter == 1) ? convertNumToString(pointsBot) : convertNumToString(roundsOfBotsWins);
sstreamBuffer.str("");
sstreamBuffer.clear();
if (botMode == PLAYER || roundsCounter != 1) {
	botsPoints.setString(pointsText);
}
else {
	botsPoints.setString("");
}

//Очистка буффера
sstreamBuffer.str("");
sstreamBuffer.clear();

timeText += sstreamBuffer.str();
gameTime.setString(timeText);

sstreamBuffer.str("");
sstreamBuffer.clear();

renderWindow.clear();

renderWindow.draw(gameBorder);
renderWindow.draw(playersPoints);
renderWindow.draw(botsPoints);
renderWindow.draw(gameTime);
snake.drawSnake(renderWindow);
for (int j = 0; j < inGameBotsCounter; j++) {
	botsArr[j].drawSnake(renderWindow);
}
app.drawApple(renderWindow);


renderWindow.display();
	}

	updateGame();
}
