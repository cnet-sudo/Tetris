#include "GameEngine.h"

void GameEngine::input()
{
	sf::Event event;

	while (window->pollEvent(event))  
	{
		// Обработка события нажатия на клавишу Esc
		if  (event.type == sf::Event::Closed) 	window->close(); 
		
		if (event.type == sf::Event::MouseWheelMoved) 
		{
			if ((event.mouseWheel.delta == -1) || (event.mouseWheel.delta == 1))
			{
				tetramino.Speed();
			}
		}
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
			if (pause.checkClick(sf::Mouse::getPosition(*window),true))
				{
				mypause = !mypause;
				}
			if (sound.checkClick(sf::Mouse::getPosition(*window),true))
			{

			}
			if (restart.checkClick(sf::Mouse::getPosition(*window),true))
			{
				tetramino.Restart();
			}
			
			if (exit.checkClick(sf::Mouse::getPosition(*window), true))
			{
				myexit = true;
			}
			
			if ((sf::Mouse::getPosition(*window).x < tetramino.getPositio().x) &&(sf::Mouse::getPosition(*window).x>208) && (sf::Mouse::getPosition(*window).x < 609))
			{
				tetramino.TetDirection(Tetramino::direction::left);		
			}
			
			if (sf::Mouse::getPosition(*window).x >= tetramino.getPositio().x && sf::Mouse::getPosition(*window).x > 208 && sf::Mouse::getPosition(*window).x < 609)
			{
			tetramino.TetDirection(Tetramino::direction::Right);
			
			}
			
			}
		

			if (event.mouseButton.button == sf::Mouse::Right)
			{
				if (sf::Mouse::getPosition(*window).x > 208 && sf::Mouse::getPosition(*window).x < 609)
				{
					tetramino.Rotate();
				}
			}
		}



		if (event.type == sf::Event::MouseButtonReleased)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{				
				restart.checkClick(sf::Mouse::getPosition(*window), false);
				exit.checkClick(sf::Mouse::getPosition(*window), false);
			}
			
		}
	}

}

void GameEngine::update(sf::Time const& deltaTime)
{
	
	if (!mypause) tetramino.update(deltaTime);
	
	if (myexit) {
	tm += deltaTime;
	if (tm > sf::seconds(1))
	{
		if (myexit) window->close();
	}
	}
}

void GameEngine::draw()
{
	// Очистка графического окна
	window->clear(sf::Color::Black);
	// Отрисовка фона в графическом окне
	tetramino.draw();
	window->draw(background);
	window->draw(*pause.getSprite());
	window->draw(*restart.getSprite());
	window->draw(*sound.getSprite());
	window->draw(*exit.getSprite());
	text.setPosition(15, 515);
	text.setString(" < Score > ");
	window->draw(text);
    text.setString(std::to_string(tetramino.getScore()));
	text.setPosition(100-text.getGlobalBounds().width/2, 555);
	window->draw(text);
	// Вывод объектов в графическом окне
	window->display();
}

GameEngine::GameEngine()
{
	// Получение ссылки на текстуру для прямоугольника 
	background.setTexture(&AssetManager::GetTexture("image/Tetris.png"));
	if (!icon.loadFromFile("image/game.png")) window->close();
	window->setIcon(256, 256, icon.getPixelsPtr());
	text.setFont(AssetManager::GetFont("Godzilla.ttf"));
	text.setFillColor(sf::Color::Black);
	
}

void GameEngine::run()
{
	
	// Объявление переменной часы
	sf::Clock clock;
	// Цикл работает пока окно открыто
	while (window->isOpen())
	{
		// Текущее время присваиваем переменной времени dt
		sf::Time dt = clock.restart();

		input();
		
		update(dt);

		draw();
	}
}
