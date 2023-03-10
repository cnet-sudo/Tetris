#pragma once
#include"AssetManager.h"
#include"array"
#include<iostream>

class Tetramino
{
	
	// игровое поле
	std::array<std::array<int, 20>, 10> field{ 0};
	// массив фигурок-тетрамино
	std::array<std::array<int, 4>, 7> figures{ {{1,3,5,7},{2,4,5,7},{3,4,5,6},{3,4,5,7},{2,3,5,7},{3,5,6,7},{2,3,4,5}} };

	std::array<sf::Vector2i, 4> a;
	std::array<sf::Vector2i, 4> b;
	std::array<sf::Color, 7> tetcolor{ {sf::Color::Blue,sf::Color::Cyan,sf::Color::Yellow,sf::Color::Green,sf::Color::Magenta,sf::Color::Red,sf::Color::White} };

	std::unique_ptr<sf::RectangleShape> cube = std::make_unique<sf::RectangleShape>(sf::Vector2f(20,20));

	sf::RenderWindow& window;
	// Стартовые координаты тетрамино
	const float tetx;
	const float tety;
	// Координаты смещения тетрамино
	float moveX=0;
	float moveY=0;
	float click_dx=0; // шаг перемещения тетрамино
	sf::Time frameRate;
	void newFigrois();
	
public:
    enum class direction {N=0,left=-20,Right=20};
	explicit Tetramino(sf::RenderWindow& window,float,float);
	void Tetdirection(direction dir);
	void draw();
	void update(sf::Time const& deltaTime);
	sf::Vector2f getPosition() const;
	float getStep() const;
};

