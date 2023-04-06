#pragma once
#include"AssetManager.h"
#include "GameSound.h"
#include <array>
#include <vector>
#include <chrono>
#include <random>
class Tetramino
{
public:
	// перечисление направлений движения тетрамино по горизонтали
	enum class direction { left = -1, nuLL, right };
	// перечисление проверки координат на столкновение с установлеными границами 
	// при перемещении и вращении
	enum class ch { x, y, rotation };
	// конструктор тетрамино
	explicit Tetramino(sf::RenderWindow&, sf::Vector2f, sf::Vector2i, float);
	// метод устанавливающий вектор движения тетрамино
	void tetDirection(direction dir);
	// метод рисующий тетрамино в графическом окне
	void draw();
	// метод обновления игровой логики тетрамино
	void update(sf::Time const& deltaTime);
	// метод вращения тетрамино
	void rotate();
	// метод возвращающий координаты центра тетрамино
	sf::Vector2f getPositio();
	// метод ускоряющий падение тетрамино
	void speed();
	// метод сбрасывающий все свойства в начальные значения - рестарт игры
	void restart();
	// метод возвращающий количество выигранных очков
	int getscore() const;
	// метод включающий и выключающий фоновую музыку
	void mustet(bool m);
	// метод отображения макета следующего тетрамино
	void maket(sf::Vector2f);
private:
	const int height;   // высота игрового поля
	const int width;    // ширина игрового поля
	const  float click_dy = 1.0f;   // шаг перемещения тетрамино по y
	// массив игрового поля
	std::vector<std::vector<sf::Color>> square;
	// массив локальных координат фигурок тетрамино 
	std::array<std::array<int, 4>, 7> figures
	{ {{1,3,5,7},{2,4,5,7},{3,4,5,6},{3,4,5,7},{2,3,5,7},{3,5,6,7},{2,3,4,5}} };
	// положение прямоугольника в построении тетрамино 
	std::array<sf::Vector2f, 4> t;
	// массив цвета для тетрамино
	std::array<sf::Color, 7> tetcolor{ {sf::Color::Blue,sf::Color::Cyan,sf::Color::Yellow,
		sf::Color::Green,sf::Color::Magenta,sf::Color::Red,sf::Color::White} };
	// прямоугольник тетрамино
	std::unique_ptr<sf::RectangleShape> cube = std::make_unique<sf::RectangleShape>();
	// момент системного времени
	long long seed = std::chrono::system_clock::now().time_since_epoch().count();
	// запуск генератора случайных чисел
	std::default_random_engine rnd = std::default_random_engine(static_cast<long>(seed));
	// установка диапазона случайных чисел
	std::uniform_int_distribution<int> d = std::uniform_int_distribution<int>(0, 6);
	// ссылка на графическое окно
	sf::RenderWindow& window;
	// начальные координаты тетрамино
	const sf::Vector2f tet;
	sf::Time frameRate;          // интервал обновления игровой логики
	sf::Vector2i typeTet;	     // тип тетрамино
	sf::Vector2i colTet;         // цвет тетрамино
	void newFigrois();	         // новый тетрамино
	void lineDead(int g);	     // уничтожение полоски тетрамино при заполнении поля по горизонтали
	bool check(ch ch);	         // проверка положения тетрамино
	sf::Int32 delay;             // интервал обработки игровой логики
	float click_dx;              // шаг перемещения тетрамино по x 
	int score;                   // очки выигрыша
	bool playMus = false;        // включение музыки
	GameSound mus;				 // объект музыкальных эффектов
	float scale;                 // масштаб тетрамино
	sf::Vector2f positionmaket;
};

