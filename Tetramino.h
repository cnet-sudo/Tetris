#pragma once
#include"AssetManager.h"
#include "GameSound.h"
#include <array>
#include <iostream>
#include <chrono>
#include <random>
#include<cmath>


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
	enum class direction {left=-1,N,Right};
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
	sf::Vector2f getPositio();
	void Speed();
	void Restart();
	int getScore() const;
	void mustet(bool m);
private:
	static const int Y = 31; // высота игрового поля
	static const int X = 20; // ширина игрового поля
	// игровое поле
	std::array<std::array<sf::Color, Y>, X> square;
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
	
	const sf::Vector2f tet;      // начальные координаты тетрамино
	
	
	sf::Time frameRate;          // интервал обновления игровой логики
	Borders bordes;              // границы перемещения тетрамино
	sf::Vector2i TN;	         // тип тетрамино
	sf::Vector2i Col;            // цвет
	void newFigrois();	         // новый тетрамино
	void LineDead(int g);	     // уничтожение полоски
	bool check(ch ch);	         // проверка положения тетрамино
	sf::Int32 Delay = 300;       // интервал обработки игровой логики
	float click_dx;              // шаг перемещения тетрамино по x 
	const float click_dy=1.0f;   // шаг перемещения тетрамино по y
	int Score;

	bool PlayMus = false;
	GameSound mus;
};

