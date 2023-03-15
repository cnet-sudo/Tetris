#include "GameEngine.h"

void GameEngine::input()
{
	sf::Event event;

	while (window->pollEvent(event))  
	{
		// Обработка события нажатия на клавишу Esc
		if  (event.type == sf::Event::Closed) 	window->close(); 
		
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
			if (pause.checkClick(sf::Mouse::getPosition(*window),true))
				{
					
				}
			if (sound.checkClick(sf::Mouse::getPosition(*window),true))
			{

			}
			if (play.checkClick(sf::Mouse::getPosition(*window),true))
			{

			}
			if (restart.checkClick(sf::Mouse::getPosition(*window),true))
			{

			}
			
			if (sf::Mouse::getPosition(*window).x > 208 && sf::Mouse::getPosition(*window).x < 403 )
			{
				tetramino.TetDirection(Tetramino::direction::left);
				std::cout << sf::Mouse::getPosition(*window).x << "\n";
			}
			
			if (sf::Mouse::getPosition(*window).x >= 403 && sf::Mouse::getPosition(*window).x < 609)
			{
			tetramino.TetDirection(Tetramino::direction::Right);
			std::cout << sf::Mouse::getPosition(*window).x << "\n";
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
				if (play.checkClick(sf::Mouse::getPosition(*window),false))
				{

				}

				if (restart.checkClick(sf::Mouse::getPosition(*window),false))
				{

				}

			}
			
		}
	}

}

void GameEngine::update(sf::Time const& deltaTime)
{
	
	tetramino.update(deltaTime);
}

void GameEngine::draw()
{
	// Очистка графического окна
	window->clear(sf::Color::Black);
	// Отрисовка фона в графическом окне
	tetramino.draw();
	window->draw(background);
	window->draw(*play.getSprite());
	window->draw(*pause.getSprite());
	window->draw(*restart.getSprite());
	window->draw(*sound.getSprite());
	text.setPosition(15, 515);
	text.setString(" < Score > ");
	window->draw(text);
    text.setString(std::to_string(score));
	text.setPosition(100-text.getGlobalBounds().width/2, 555);
	window->draw(text);
	// Вывод объектов в графическом окне
	window->display();
}

GameEngine::GameEngine()
{
	// Получение ссылки на текстуру для прямоугольника 
	background.setTexture(&AssetManager::GetTexture("image/Tetris.png"));
	
	
	if (!icon.loadFromFile("image/game.png")) exit(3); 
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
