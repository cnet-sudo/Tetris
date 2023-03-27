#pragma once
#include"Button.h";
#include"Tetramino.h";

class GameEngine
{
public:
	// Конструктор игровой движок
	GameEngine();
	// Метод запуска игрового цикла
	void run();
private:
	// Менеджер ресурсов
	AssetManager manager; 
	// Умный указатель на графическое окно 
	std::unique_ptr<sf::RenderWindow> window = std::make_unique<sf::RenderWindow>
	(sf::VideoMode(640, 640),L"Тетрис", sf::Style::Close);
	// Иконка в графическом окне
	sf::Image icon;
	// Игровой фон 
	sf::RectangleShape background = sf::RectangleShape(sf::Vector2f(640, 640));
	// Кнопки
	Button pause = Button(sf::Vector2f(13,140),AssetManager::GetTexture("image/play1.png"), AssetManager::GetTexture("image/pause2.png"));
	Button restart = Button(sf::Vector2f(13, 220), AssetManager::GetTexture("image/restart1.png"), AssetManager::GetTexture("image/restart2.png"));
	Button sound = Button(sf::Vector2f(13, 300), AssetManager::GetTexture("image/nosound.png"), AssetManager::GetTexture("image/sound.png"));
	Button exit = Button(sf::Vector2f(13, 380), AssetManager::GetTexture("image/exit1.png"), AssetManager::GetTexture("image/exit2.png"));
	// Текст - игровые очки
	sf::Text text;
	// Игровая логика тетрис
	Tetramino tetramino = Tetramino(*window,sf::Vector2f(390,-40),Tetramino::Borders(198,609,590));
	// Метод обработки событий 
	void input();
	// Метод обновления значения свойств класса игровой движок
	void update(sf::Time const& deltaTime);
	// Метод отрисовки объектов в графическом окне
	void draw();
	// Выход с приложения
	bool myexit = false;
	// Пауза
	bool mypause = false;
	// Включение выключение музыки 
	bool mus = false;
	// Интервал задержки при выполнении выхода из приложения
	sf::Time tm;
};

