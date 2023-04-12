#pragma once
#include"Button.h";
#include"Tetramino.h";

class GameEngine
{
public:
	GameEngine();          
	void run();            
private:
	// объект игровых ассетов
	AssetManager manager;
	// графическое окно
	std::unique_ptr<sf::RenderWindow> window = std::make_unique<sf::RenderWindow>
		(sf::VideoMode(640, 640), L"Тетрис", sf::Style::Close);
	// иконка графического окна
	sf::Image icon;
	// игровой фон
	sf::RectangleShape background = sf::RectangleShape(sf::Vector2f(640, 640));
	// кнопки игрового интерфейса
	Button pause = Button(sf::Vector2f(13, 140), 
	AssetManager::GetTexture("image/play1.png"), AssetManager::GetTexture("image/pause2.png"));
	Button restart = Button(sf::Vector2f(13, 220), 
	AssetManager::GetTexture("image/restart1.png"), AssetManager::GetTexture("image/restart2.png"));
	Button sound = Button(sf::Vector2f(13, 300), 
	AssetManager::GetTexture("image/nosound.png"), AssetManager::GetTexture("image/sound.png"));
	Button exit = Button(sf::Vector2f(13, 380), 
	AssetManager::GetTexture("image/exit1.png"), AssetManager::GetTexture("image/exit2.png"));
	// объект текста
	sf::Text text;
	// игра тетрис
	Tetramino tetramino = Tetramino(*window, sf::Vector2f(210, -42), sf::Vector2i(20,33), 20);
	void input();         
	void update(sf::Time const& deltaTime);
	void draw();          
	bool myexit = false;  
	bool mypause = false; 
	bool mus = false;     
	sf::Time tm;          
};





