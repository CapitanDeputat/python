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

//Функция начала игры
void Game::startGame()
{
	font.loadFromFile("MYmenu.ttf");
	updateGame();
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
	case Game::MULTIMENU:
		drawMultiMenu();
		break;
	}
}

//Отрисовка меню для многопользовательского режима
void Game::drawMultiMenu() {
	while (gameState == Game::MULTIMENU)
	{

		SnakeColor = sf::Color::Green;
		gameName.setFont(font);
		gameName.setString("Snake");
		gameName.setCharacterSize(80);
		gameName.setPosition(SCREEN_WIDTH / 2 - gameName.getGlobalBounds().width / 2, 0);

		menuStrings[0].setFont(font);
		menuStrings[0].setString("back");
		menuStrings[0].setCharacterSize(40);
		menuStrings[0].setPosition(SCREEN_WIDTH / 2 - 100, 500);


		menuStrings[1].setFont(font);
		char rounds = roundsCounter + '0';
		menuStrings[1].setString(rounds);
		menuStrings[1].setCharacterSize(40);
		menuStrings[1].setPosition(SCREEN_WIDTH / 12 + 300, 150);

		menuStrings[2].setFont(font);
		menuStrings[2].setString(">");
		menuStrings[2].setCharacterSize(40);
		menuStrings[2].setPosition(SCREEN_WIDTH / 12 + 330, 150);

		menuStrings[4].setFont(font);
		menuStrings[4].setString("Rounds count");
		menuStrings[4].setCharacterSize(40);
		menuStrings[4].setPosition(SCREEN_WIDTH / 12 + 220, 100);

		menuStrings[3].setFont(font);
		menuStrings[3].setString("<");
		menuStrings[3].setCharacterSize(40);
		menuStrings[3].setPosition(SCREEN_WIDTH / 12 + 230, 150);

		menuStrings[5].setFont(font);
		menuStrings[5].setString("Start");
		menuStrings[5].setCharacterSize(70);
		menuStrings[5].setPosition(SCREEN_WIDTH / 2 - 100, 300);
		sf::Event event;
		sf::Vector2f mouse(sf::Mouse::getPosition(renderWindow));
		sf::Text textKey(nickName, font, 20);
		textKey.setFillColor(sf::Color::White);
		textKey.setStyle(sf::Text::Italic);
		textKey.setPosition(500, 150);

		while (renderWindow.pollEvent(event))
		{

			//Переход в игру, в параметры или на выход, когда пользователь выбирает нужное действие в меню
			if (event.type == sf::Event::MouseButtonReleased)
			{
				if (menuStrings[0].getGlobalBounds().contains(mouse) && event.mouseButton.button == sf::Mouse::Left) {
					gameState = MENU;
					for (int i = 0; i < 7; i++) {
						menuStrings[i].setString("");
					}
				}

				if (menuStrings[2].getGlobalBounds().contains(mouse) && event.mouseButton.button == sf::Mouse::Left) {
					if (roundsCounter < 9) {
						roundsCounter++;
					}
				}
				if (menuStrings[3].getGlobalBounds().contains(mouse) && event.mouseButton.button == sf::Mouse::Left) {
					if (roundsCounter > 1) {
						roundsCounter--;
					}
				}

				if (menuStrings[5].getGlobalBounds().contains(mouse) && event.mouseButton.button == sf::Mouse::Left) {
					nickName = "";
					botMode = PLAYER;
					botsCounter = 1;
					gameState = STARTED;
					inGameBotsCounter = 1;

				}
			}

			renderWindow.clear();
			renderWindow.draw(gameName);
		}

		for (int i = 0; i < 6; i++)
			renderWindow.draw(menuStrings[i]);

		for (int i = 0; i < 6; i++)
			if (menuStrings[i].getGlobalBounds().contains(mouse) && i != 4 && i != 1)
				menuStrings[i].setFillColor(sf::Color::Yellow);
			else
				menuStrings[i].setFillColor(sf::Color::Cyan);


		renderWindow.display();
	}

	updateGame();
}

//Функция конца игры
void Game::gameOver()
{
	for (int i = 0; i < 4; i++)
	{
		gameFinish[i].setFont(font);
		gameFinish[i].setFillColor(sf::Color::White);
	}
	gameFinish[0].setString("");
	//Строка конца игры
	switch (botMode) {
	case REDDEAD:
		gameFinish[0].setString("Green wins!");
		break;
	case GREENDEAD:
		gameFinish[0].setString("Red wins!");
		break;
	case DEAD:
		gameFinish[0].setString("You win!");
		break;
	case DRAW:
		gameFinish[0].setString("DRAW");
		break;
	default:
		gameFinish[0].setString("You DIED HA HA");
		break;
	}
	gameFinish[0].setCharacterSize(80);
	gameFinish[0].setPosition(SCREEN_WIDTH / 2 - gameFinish[0].getGlobalBounds().width / 2, 150);
	(botMode == DEAD || botMode == REDDEAD) ? gameFinish[0].setFillColor(sf::Color::Green) : gameFinish[0].setFillColor(sf::Color::Red);

	std::ostringstream buffer;
	pointsText = "Player1 Points: ";
	pointsText += (roundsCounter == 1) ? convertNumToString(points) : convertNumToString(roundsOfPlayerWins);
	if (roundsCounter != 1) {
		pointsText += "   Player2 Points: ";
		pointsText += convertNumToString(roundsOfBotsWins);
	}
	else {
		if (roundsCounter == 1 && botsCounter == 1) {
			pointsText += "   Bot Points: ";
			pointsText += convertNumToString(pointsBot);
		}
	}
	points = 0;
	pointsBot = 0;
	roundsCounter = 1;
	roundsOfBotsWins = 0;
	roundsOfPlayerWins = 0;
	botsCounter = 0;

	gameFinish[1].setCharacterSize(40);
	gameFinish[1].setString(pointsText);
	gameFinish[1].setPosition(SCREEN_WIDTH / 2 - gameFinish[1].getGlobalBounds().width / 2, 240);

	//Очистить буффер
	buffer.str("");
	buffer.clear();

	pointsText = "Your time: ";
	buffer << playTime;
	pointsText += buffer.str();
	pointsText += "s";
	gameFinish[2].setCharacterSize(40);
	gameFinish[2].setString(pointsText);
	gameFinish[2].setPosition(SCREEN_WIDTH / 2 - gameFinish[1].getGlobalBounds().width / 2, 280);

	buffer.str("");
	buffer.clear();

	gameFinish[3].setString("Back to menu");
	gameFinish[3].setCharacterSize(40);
	gameFinish[3].setPosition(SCREEN_WIDTH / 2 - gameFinish[3].getGlobalBounds().width / 2, 340);


	sf::Event event;
	while (gameState == Game::OVER)
	{
		sf::Vector2f mouse(sf::Mouse::getPosition(renderWindow));
		renderWindow.clear();
		while (renderWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				gameState = ENDED;

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
				gameState = MENU;


			if (event.type == sf::Event::MouseButtonReleased)
				if (event.mouseButton.button == sf::Mouse::Left && gameFinish[3].getGlobalBounds().contains(mouse))
					gameState = MENU;
		}

		if (gameFinish[3].getGlobalBounds().contains(mouse))
			gameFinish[3].setFillColor(sf::Color::Green);
		else
			gameFinish[3].setFillColor(sf::Color::White);

		renderWindow.clear();

		for (int i = 0; i < 4; i++)
			renderWindow.draw(gameFinish[i]);

		renderWindow.display();
	}

	roundsCounter = 1;
	roundsOfPlayerWins = 0;
	roundsOfBotsWins = 0;
	inGameBotsCounter = 0;

	updateGame();
}

//Функция, отрисовывающая все пункты меню
void Game::drawMenu()
{
	gameName.setFont(font);
	gameName.setString("Snake");
	gameName.setCharacterSize(80);
	gameName.setPosition(SCREEN_WIDTH / 2 - gameName.getGlobalBounds().width / 2, 150);
	gameName.setFillColor(sf::Color::Magenta);

	menuStrings[0].setFont(font);
	menuStrings[0].setString("SOlO");
	menuStrings[0].setCharacterSize(40);
	menuStrings[0].setPosition(SCREEN_WIDTH / 2 - menuStrings[0].getGlobalBounds().width / 2, 250);

	menuStrings[1].setFont(font);
	menuStrings[1].setString("WithFriend");
	menuStrings[1].setCharacterSize(40);
	menuStrings[1].setPosition(SCREEN_WIDTH / 2 - menuStrings[1].getGlobalBounds().width / 2, 300);

	menuStrings[2].setFont(font);
	menuStrings[2].setString("Exit");
	menuStrings[2].setCharacterSize(40);
	menuStrings[2].setPosition(SCREEN_WIDTH / 2 - menuStrings[2].getGlobalBounds().width / 2, 350);

	menuStrings[3].setFont(font);
	menuStrings[3].setString("");
	menuStrings[3].setCharacterSize(40);
	menuStrings[3].setPosition(SCREEN_WIDTH / 2 - menuStrings[1].getGlobalBounds().width / 2, 300);
	for (int i = 4; i <= 17; i++)
		menuStrings[i].setString("");

	sf::Event event;
	while (gameState == Game::MENU)
	{
		sf::Vector2f mouse(sf::Mouse::getPosition(renderWindow));

		while (renderWindow.pollEvent(event))
		{
			//Закрытие окна при нажатии на крестик
			if (event.type == sf::Event::Closed)
				gameState = ENDED;
			//Создание новых окон при выборе игроком функций меню
			if (event.type == sf::Event::MouseButtonReleased)
			{
				if (menuStrings[0].getGlobalBounds().contains(mouse) && event.mouseButton.button == sf::Mouse::Left)
					gameState = SINGLEPLAYER;
				if (menuStrings[1].getGlobalBounds().contains(mouse) && event.mouseButton.button == sf::Mouse::Left) {
					gameState = MULTIMENU;
				}
				if (menuStrings[2].getGlobalBounds().contains(mouse) && event.mouseButton.button == sf::Mouse::Left)
					gameState = ENDED;

			}
		}
		renderWindow.clear();

		renderWindow.draw(gameName);

		for (int i = 0; i < 16; i++)
			renderWindow.draw(menuStrings[i]);

		for (int i = 0; i < 16; i++)
			if (menuStrings[i].getGlobalBounds().contains(mouse) && i != 6 && i != 4 && i != 8 && i != 11)
				menuStrings[i].setFillColor(sf::Color::Yellow);
			else
				menuStrings[i].setFillColor(sf::Color::Cyan);


		renderWindow.display();
	}
	updateGame();
}

//Функция для отрисовки всех полей выбора бота в одиночной игре
void Game::drawSingleMenu()
{
	while (gameState == Game::SINGLEPLAYER)
	{

		gameName.setFont(font);
		gameName.setString("Snake");
		gameName.setCharacterSize(80);
		gameName.setPosition(SCREEN_WIDTH / 2 - gameName.getGlobalBounds().width / 2, 0);

		menuStrings[0].setFont(font);
		menuStrings[0].setString("I'm to young to die bot");
		menuStrings[0].setCharacterSize(40);
		menuStrings[0].setPosition(SCREEN_WIDTH / 2 - menuStrings[0].getGlobalBounds().width / 2, 70);

		menuStrings[1].setFont(font);
		menuStrings[1].setString("Hurt me plenty bot");
		menuStrings[1].setCharacterSize(40);
		menuStrings[1].setPosition(SCREEN_WIDTH / 2 - menuStrings[1].getGlobalBounds().width / 2, 120);

		menuStrings[2].setFont(font);
		menuStrings[2].setString("Nightmare bot");
		menuStrings[2].setCharacterSize(40);
		menuStrings[2].setPosition(SCREEN_WIDTH / 2 - menuStrings[1].getGlobalBounds().width / 2, 170);

		menuStrings[3].setFont(font);
		menuStrings[3].setString("back");
		menuStrings[3].setCharacterSize(40);
		menuStrings[3].setPosition(SCREEN_WIDTH / 2 - menuStrings[2].getGlobalBounds().width / 4, 550);

		menuStrings[4].setFont(font);
		menuStrings[4].setString("Bots count");
		menuStrings[4].setCharacterSize(40);
		menuStrings[4].setPosition(SCREEN_WIDTH / 10, 260);

		menuStrings[5].setFont(font);
		menuStrings[5].setString(">");
		menuStrings[5].setCharacterSize(40);
		menuStrings[5].setPosition(SCREEN_WIDTH / 10 + 138, 300);

		menuStrings[6].setFont(font);
		char bots = botsCounter + '0';
		menuStrings[6].setString(bots);
		menuStrings[6].setCharacterSize(40);
		menuStrings[6].setPosition(SCREEN_WIDTH / 10 + 100, 300);

		menuStrings[7].setFont(font);
		menuStrings[7].setString("<");
		menuStrings[7].setCharacterSize(40);
		menuStrings[7].setPosition(SCREEN_WIDTH / 10 + 38, 300);

		menuStrings[8].setFont(font);
		char rounds = roundsCounter + '0';
		menuStrings[8].setString(rounds);
		menuStrings[8].setCharacterSize(40);
		menuStrings[8].setPosition(SCREEN_WIDTH / 2 + 100, 300);

		menuStrings[9].setFont(font);
		menuStrings[9].setString(">");
		menuStrings[9].setCharacterSize(40);
		menuStrings[9].setPosition(SCREEN_WIDTH / 2 + 135, 300);

		menuStrings[10].setFont(font);
		menuStrings[10].setString("<");
		menuStrings[10].setCharacterSize(40);
		menuStrings[10].setPosition(SCREEN_WIDTH / 2 + 35, 300);

		menuStrings[11].setFont(font);
		menuStrings[11].setString("Rounds count");
		menuStrings[11].setCharacterSize(40);
		menuStrings[11].setPosition(SCREEN_WIDTH / 10 + 300, 260);

		menuStrings[12].setFont(font);
		menuStrings[12].setString("Snake Color");
		menuStrings[12].setCharacterSize(40);
		menuStrings[12].setPosition(SCREEN_WIDTH / 12, 400);

		menuStrings[13].setFont(font);
		menuStrings[13].setString("<");
		menuStrings[13].setCharacterSize(40);
		menuStrings[13].setPosition(SCREEN_WIDTH / 12 - 14, 440);

		menuStrings[14].setFont(font);
		std::string color = Colors[iter];
		menuStrings[14].setString(color);
		menuStrings[14].setCharacterSize(40);
		menuStrings[14].setPosition(SCREEN_WIDTH / 12 + 50, 440);

		menuStrings[15].setFont(font);
		menuStrings[15].setString(">");
		menuStrings[15].setCharacterSize(40);
		menuStrings[15].setPosition(SCREEN_WIDTH / 12 + 210, 440);

		menuStrings[16].setFont(font);
		menuStrings[16].setString("Name");
		menuStrings[16].setCharacterSize(40);
		menuStrings[16].setPosition(SCREEN_WIDTH / 12 + 380, 400);

		sf::Event event;
		sf::Vector2f mouse(sf::Mouse::getPosition(renderWindow));
		sf::Text textKey(nickName, font, 40);
		textKey.setFillColor(sf::Color::Cyan);
		textKey.setStyle(sf::Text::Italic);
		textKey.setPosition(SCREEN_WIDTH / 12 + 380, 440);

		while (renderWindow.pollEvent(event))
		{
			if (event.type == sf::Event::TextEntered)
			{
				if (event.text.unicode != 8) {
					nickName += event.text.unicode;

					sf::Text newText(nickName, font, 40);
					newText.setFillColor(sf::Color::Cyan);
					newText.setStyle(sf::Text::Regular);
					newText.setPosition(SCREEN_WIDTH / 12 + 380, 440);
					textKey = newText;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace)) {
					int index = 0;
					nickName.pop_back();
					sf::Text newText(nickName, font, 40);
					newText.setFillColor(sf::Color::Cyan);
					newText.setStyle(sf::Text::Regular);
					newText.setPosition(SCREEN_WIDTH / 12 + 380, 440);
					textKey = newText;
				}
			}

			//Выход при нажатии на крестик
			if (event.type == sf::Event::Closed)
				gameState = ENDED;

			//Создание новых окон при выборе функций игроком
			if (event.type == sf::Event::MouseButtonReleased)
			{
				if (menuStrings[0].getGlobalBounds().contains(mouse) && event.mouseButton.button == sf::Mouse::Left) {
					gameState = STARTED;
					botMode = EASY;
					inGameBotsCounter = botsCounter;
				}

				if (menuStrings[1].getGlobalBounds().contains(mouse) && event.mouseButton.button == sf::Mouse::Left) {
					gameState = STARTED;
					botMode = NORMAL;
					inGameBotsCounter = botsCounter;
				}
				if (menuStrings[2].getGlobalBounds().contains(mouse) && event.mouseButton.button == sf::Mouse::Left) {
					gameState = STARTED;
					botMode = INSANE;
					inGameBotsCounter = botsCounter;
				}
				if (menuStrings[3].getGlobalBounds().contains(mouse) && event.mouseButton.button == sf::Mouse::Left) {
					gameState = MENU;
					for (int i = 0; i <= 16; i++) {
						menuStrings[i].setString("");
					}

				}
				if (menuStrings[5].getGlobalBounds().contains(mouse) && event.mouseButton.button == sf::Mouse::Left) {
					if (botsCounter < 9) {
						botsCounter++;
					}
				}
				if (menuStrings[7].getGlobalBounds().contains(mouse) && event.mouseButton.button == sf::Mouse::Left) {
					if (botsCounter > 0) {
						botsCounter--;
					}
				}
				if (menuStrings[9].getGlobalBounds().contains(mouse) && event.mouseButton.button == sf::Mouse::Left) {
					if (roundsCounter < 9) {
						roundsCounter++;
					}
				}
				if (menuStrings[10].getGlobalBounds().contains(mouse) && event.mouseButton.button == sf::Mouse::Left) {
					if (roundsCounter > 1) {
						roundsCounter--;
					}
				}
				if (menuStrings[15].getGlobalBounds().contains(mouse) && event.mouseButton.button == sf::Mouse::Left) {
					if (iter < 2) {
						iter++;
					}
				}
				if (menuStrings[13].getGlobalBounds().contains(mouse) && event.mouseButton.button == sf::Mouse::Left) {
					if (iter > 0) {
						iter--;
					}
				}
			}
		}

		renderWindow.clear();

		renderWindow.draw(gameName);
		renderWindow.draw(textKey);

		for (int i = 0; i < 17; i++)
			renderWindow.draw(menuStrings[i]);
		for (int i = 0; i < 17; i++)
			if (menuStrings[i].getGlobalBounds().contains(mouse) && i != 6 && i != 4 && i != 8 && i != 12 && i != 11 && i != 16)
				menuStrings[i].setFillColor(sf::Color::Yellow);
			else
				menuStrings[i].setFillColor(sf::Color::Cyan);
		if (iter == 0) {
			menuStrings[14].setFillColor(sf::Color::Green);
			SnakeColor = sf::Color::Green;
		}
		if (iter == 1) {
			menuStrings[14].setFillColor(sf::Color::Magenta);
			SnakeColor = sf::Color::Magenta;
		}
		if (iter == 2) {
			menuStrings[14].setFillColor(sf::Color::White);
			SnakeColor = sf::Color::White;
		}


		renderWindow.display();
	}

	updateGame();
}

//Основной функционал игры
void Game::drawGame()
{

	int snakeX, snakeY;

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

	pause.setFont(font);
	pause.setCharacterSize(30);
	pause.setFillColor(sf::Color::White);
	pause.setPosition(SNAKE_SIZE + 5, SCREEN_HEIGHT / 2);
	pause.setString("Game paused (press Space to continue)");


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
				points = 0;
				pointsBot = 0;
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

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
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
		//Не обновлять игру, когда она на паузе
		while (elapsedGameTime > timeStep && !isGamePaused)
		{
			if (botMode != PLAYER && canMove) {
				if (!snake.moveSnake()) {
					roundsOfBotsWins++;
					nowRounds++;
					inGameBotsCounter = botsCounter;
					while (!botsArr.empty()) {
						botsArr.pop_back();
					}
					if (nowRounds >= roundsCounter) {
						gameState = OVER;

					}

					updateGame();

				}
				canMove = false;
			}
			for (int i = 0; i < inGameBotsCounter; i++) {

				switch (botMode) {
				case EASY:
					result = chooseMove(&botsArr[i], "easy", snake, app);
					break;
				case NORMAL:
					result = chooseMove(&botsArr[i], "medium", snake, app);
					break;
				case INSANE:
					result = chooseMove(&botsArr[i], "insane", snake, app);
					break;
				default: result = true;
					break;
				}
				if (!result) {
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
						nowRounds++;
						roundsOfPlayerWins++;
						inGameBotsCounter = botsCounter;
						while (!botsArr.empty()) {
							botsArr.pop_back();
						}
						if (nowRounds >= roundsCounter) {
							if (roundsOfBotsWins < roundsOfPlayerWins) {
								botMode = DEAD;
							}
							if (roundsOfBotsWins == roundsOfPlayerWins) {
								botMode = DRAW;
							}
							gameState = OVER;
						}
					}
					updateGame();
				}

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
		pointsText = "Player2 Points: ";
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

		timeText = "Time: ";

		//Не обновлять время, когда игра на паузе
		if (!isGamePaused)
			playTime = playClock.getElapsedTime().asSeconds() - elapsedPauseTime;

		sstreamBuffer << playTime;
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


		if (isGamePaused)
			renderWindow.draw(pause);

		renderWindow.display();
	}

	updateGame();
}
