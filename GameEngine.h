#pragma once
#include"Button.h";
#include"string";
#include"Tetramino.h";

class GameEngine
{
public:
	// Конструктор
	GameEngine();
	// Метод запуска игрового цикла
	void run();
private:
	AssetManager manager; // Менеджер ресурсов
	// Умный указатель на графическое окно 
	std::unique_ptr<sf::RenderWindow> window = std::make_unique<sf::RenderWindow>
	(sf::VideoMode(640, 640),L"Тетрис", sf::Style::Close);
	// Игровой фон в виде прямоугольника
	sf::RectangleShape background = sf::RectangleShape(sf::Vector2f(640, 640));
	sf::Image icon;
	Button pause = Button(sf::Vector2f(13,140),AssetManager::GetTexture("image/play1.png"), AssetManager::GetTexture("image/pause2.png"));
	Button restart = Button(sf::Vector2f(13, 220), AssetManager::GetTexture("image/restart1.png"), AssetManager::GetTexture("image/restart2.png"));
	Button sound = Button(sf::Vector2f(13, 300), AssetManager::GetTexture("image/nosound.png"), AssetManager::GetTexture("image/sound.png"));
	Button exit = Button(sf::Vector2f(13, 380), AssetManager::GetTexture("image/exit1.png"), AssetManager::GetTexture("image/exit2.png"));
	sf::Text text;
	Tetramino tetramino = Tetramino(*window,sf::Vector2f(390,-40),Tetramino::Borders(198,609,610));
	// Метод обработки событий 
	void input();
	// Метод обновления переменных, свойств и методов 
	void update(sf::Time const& deltaTime);
	// Метод отрисовки объектов в графическом окне
	void draw();
	bool myexit = false;
	bool mypause = false;
	bool mus = false;
	sf::Time tm;
};

