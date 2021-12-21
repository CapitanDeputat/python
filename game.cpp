#include "Game.h"






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

	case Game::ENDED:
		renderWindow.close();
		return;
		break;
	case Game::SINGLEPLAYER:
		drawSingleMenu();
		break;
}



//Функция, отрисовывающая все пункты меню
void Game::drawMenu()
{
	gameName.setFont(font);
	gameName.setString("Snake");
	gameName.setCharacterSize(80);
	gameName.setPosition(SCREEN_WIDTH / 2 - gameName.getGlobalBounds().width / 2, 150);

	menuStrings[0].setFont(font);
	menuStrings[0].setString("Singleplayer");
	menuStrings[0].setCharacterSize(40);
	menuStrings[0].setPosition(SCREEN_WIDTH / 2 - menuStrings[0].getGlobalBounds().width / 2, 250);

	menuStrings[1].setFont(font);
	menuStrings[1].setString("Multiplayer");
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
				menuStrings[i].setFillColor(sf::Color::Green);
			else
				menuStrings[i].setFillColor(sf::Color::White);


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
		menuStrings[0].setString("With easy bot");
		menuStrings[0].setCharacterSize(40);
		menuStrings[0].setPosition(SCREEN_WIDTH / 2 - menuStrings[0].getGlobalBounds().width / 2, 70);

		menuStrings[1].setFont(font);
		menuStrings[1].setString("With normal bot");
		menuStrings[1].setCharacterSize(40);
		menuStrings[1].setPosition(SCREEN_WIDTH / 2 - menuStrings[1].getGlobalBounds().width / 2, 120);

		menuStrings[2].setFont(font);
		menuStrings[2].setString("With insane bot");
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
		menuStrings[5].setString("+");
		menuStrings[5].setCharacterSize(40);
		menuStrings[5].setPosition(SCREEN_WIDTH / 10 + 150, 300);

		menuStrings[6].setFont(font);
		char bots = botsCounter + '0';
		menuStrings[6].setString(bots);
		menuStrings[6].setCharacterSize(40);
		menuStrings[6].setPosition(SCREEN_WIDTH / 10 + 100, 300);

		menuStrings[7].setFont(font);
		menuStrings[7].setString("-");
		menuStrings[7].setCharacterSize(40);
		menuStrings[7].setPosition(SCREEN_WIDTH / 10 + 50, 300);

		menuStrings[8].setFont(font);
		char rounds = roundsCounter + '0';
		menuStrings[8].setString(rounds);
		menuStrings[8].setCharacterSize(40);
		menuStrings[8].setPosition(SCREEN_WIDTH / 2 + 100, 300);

		menuStrings[9].setFont(font);
		menuStrings[9].setString("+");
		menuStrings[9].setCharacterSize(40);
		menuStrings[9].setPosition(SCREEN_WIDTH / 2 + 150, 300);

		menuStrings[10].setFont(font);
		menuStrings[10].setString("-");
		menuStrings[10].setCharacterSize(40);
		menuStrings[10].setPosition(SCREEN_WIDTH / 2 + 50, 300);

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
		menuStrings[13].setPosition(SCREEN_WIDTH / 12, 440);

		menuStrings[14].setFont(font);
		std::string color = Colors[iter];
		menuStrings[14].setString(color);
		menuStrings[14].setCharacterSize(40);
		menuStrings[14].setPosition(SCREEN_WIDTH / 12 + 50, 440);

		menuStrings[15].setFont(font);
		menuStrings[15].setString(">");
		menuStrings[15].setCharacterSize(40);
		menuStrings[15].setPosition(SCREEN_WIDTH / 12 + 180, 440);

		menuStrings[16].setFont(font);
		menuStrings[16].setString("Name");
		menuStrings[16].setCharacterSize(40);
		menuStrings[16].setPosition(SCREEN_WIDTH / 12 + 380, 400);





		sf::Event event;
		sf::Vector2f mouse(sf::Mouse::getPosition(renderWindow));
		sf::Text textKey(nickName, font, 40);
		textKey.setFillColor(sf::Color::White);
		textKey.setStyle(sf::Text::Italic);
		textKey.setPosition(SCREEN_WIDTH / 12 + 380, 440);

		while (renderWindow.pollEvent(event))
		{
			if (event.type == sf::Event::TextEntered)
			{   // event.key.code == sf::Keyboard::P
				if (event.text.unicode != 8) {
					nickName += event.text.unicode;

					sf::Text newText(nickName, font, 40);
					newText.setFillColor(sf::Color::White);
					newText.setStyle(sf::Text::Regular);
					newText.setPosition(SCREEN_WIDTH / 12 + 380, 440);
					textKey = newText;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace)) {
					int index = 0;
					nickName.pop_back();
					sf::Text newText(nickName, font, 40);
					newText.setFillColor(sf::Color::White);
					newText.setStyle(sf::Text::Regular);
					newText.setPosition(SCREEN_WIDTH / 12 + 380, 440);
					textKey = newText;
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
				menuStrings[i].setFillColor(sf::Color::Green);
			else
				menuStrings[i].setFillColor(sf::Color::White);
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

}
