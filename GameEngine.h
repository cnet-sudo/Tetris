#pragma once
#include"Button.h";
#include"Tetramino.h";

class GameEngine
{
public:
	GameEngine();          // Конструктор игровой движок
	void run();            // Метод запуска игрового цикла
private:
	// Менеджер ресурсов
	AssetManager manager;
	// Умный указатель на графическое окно 
	std::unique_ptr<sf::RenderWindow> window = std::make_unique<sf::RenderWindow>
		(sf::VideoMode(640, 640), L"Тетрис", sf::Style::Close);
	// Иконка в графическом окне
	sf::Image icon;
	// Игровой фон 
	sf::RectangleShape background = sf::RectangleShape(sf::Vector2f(640, 640));
	// Кнопки
	Button pause = Button(sf::Vector2f(13, 140), 
	AssetManager::GetTexture("image/play1.png"), AssetManager::GetTexture("image/pause2.png"));
	Button restart = Button(sf::Vector2f(13, 220), 
	AssetManager::GetTexture("image/restart1.png"), AssetManager::GetTexture("image/restart2.png"));
	Button sound = Button(sf::Vector2f(13, 300), 
	AssetManager::GetTexture("image/nosound.png"), AssetManager::GetTexture("image/sound.png"));
	Button exit = Button(sf::Vector2f(13, 380), 
	AssetManager::GetTexture("image/exit1.png"), AssetManager::GetTexture("image/exit2.png"));
	sf::Text text;        // Свойство для вывода текста с очками выигрыша
	Tetramino tetramino = Tetramino(*window, sf::Vector2f(210, -42), sf::Vector2i(20,33), 20);
	void input();         // Метод обработки событий 
	// Метод обновления значения свойств класса игровой движок
	void update(sf::Time const& deltaTime);
	void draw();          // Метод отрисовки объектов в графическом окне
	bool myexit = false;  // Свойство разрешающее выход с приложения
	bool mypause = false; // Свойство включения выключения паузы
	bool mus = false;     // Свойство включения выключения музыки
	sf::Time tm;          // Свойство интервала задержки при выполнении выхода из приложения
};

