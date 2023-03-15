#pragma once
#include"AssetManager.h"
#include"array"
#include<iostream>
#include <chrono>
#include <random>

class Tetramino
{
public:

	// структура границ
	struct Borders
	{
		float x;
		float max;
		float maxy;

		Borders(float x,float x1,float y):x(x),max(x1),maxy(y){}
	};
    // список направления движения
	enum class direction {left,N,Right};
	// списко проверки координат  
	enum class ch {x,y,r};
	explicit Tetramino(sf::RenderWindow& window,sf::Vector2f, Borders);
	// вектор движения тетрамино
	void TetDirection(direction dir);
	// отрисовка тетрамино
	void draw();
	// обновление игровой логики тетрамино
	void update(sf::Time const& deltaTime);
	// вращение тетрамино
	void Rotate();
private:
	// игровое поле
	std::array<std::array<int, 30>, 18> field{0};
	// массив фигурок тетрамино
	std::array<std::array<int, 4>, 7> figures{ {{1,3,5,7},{2,4,5,7},{3,4,5,6},{3,4,5,7},{2,3,5,7},{3,5,6,7},{2,3,4,5}} };
	// положение тетрамино
	std::array<sf::Vector2f, 4> a;
	// цвет тетрамино
	std::array<sf::Color, 7> tetcolor{ {sf::Color::Blue,sf::Color::Cyan,sf::Color::Yellow,sf::Color::Green,sf::Color::Magenta,sf::Color::Red,sf::Color::White} };

	// прямоугольники тетрамино
	std::unique_ptr<sf::RectangleShape> cube = std::make_unique<sf::RectangleShape>(sf::Vector2f(18,18));

	// момент системного времени
	long long seed = std::chrono::system_clock::now().time_since_epoch().count();
	// запуск генератора случайных чисел
	std::default_random_engine rnd=std::default_random_engine(static_cast<long>(seed));
	// установка диапазона случайных чисел
	std::uniform_int_distribution<int> d=std::uniform_int_distribution<int>(0,6);

	sf::RenderWindow& window;    // графическое окно
	
	const sf::Vector2f tet;     // начальные координаты тетрамино
	
	float click_dx;            // шаг перемещения тетрамино по x 
	const float click_dy=0.1f; // шаг перемещения тетрамино по y
	sf::Time frameRate;  // интервал обновления игровой логики
	Borders bordes;      // границы перемещения тетрамино
	int N;			     // тип тетрамино
	void newFigrois();	 // новый тетрамино
	bool check(ch ch);	 // проверка положения тетрамино
	
};

