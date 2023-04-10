#pragma once
#include"AssetManager.h"
#include "GameSound.h"
#include <array>
#include <vector>
#include <chrono>
#include <random>
#include <math.h>

class Tetramino
{
public:
	// перечисление направлений движения тетрамино по горизонтали
	// enumeration of directions of movement of Tetrimino horizontally
	enum class direction { left = -1, nuLL, right };
	// перечисление проверки координат на столкновение с установлеными границами 
	// при перемещении и вращении
	// enumeration of checking coordinates for collision with set boundaries
    // when moving and rotating
	enum class ch { x, y, rotation };
	// конструктор тетрамино
	// Tetrimino constructor
	explicit Tetramino(sf::RenderWindow&, sf::Vector2f, sf::Vector2i, float);
	// метод устанавливающий вектор движения тетрамино
	// method that sets the tetramino's motion vector
	void tetDirection(direction);
	// метод рисующий тетрамино в графическом окне
	// method that draws tetraminos in the graphics window
	void draw();
	// метод обновления игровой логики тетрамино
	// method for updating game logic Tetrimino
	void update(sf::Time const&);
	// метод вращения тетрамино
	// tetramino rotation method
	void rotate();
	// метод возвращающий координаты центра тетрамино
	// method returning tetramino center coordinates
	sf::Vector2f getPositio();
	// метод ускоряющий падение тетрамино
	// method to accelerate the fall of tetraminos
	void speed();
	// метод сбрасывающий все свойства в начальные значения - рестарт игры
	// method resetting all properties to initial values ​​- game restart
	void restart();
	// метод возвращающий количество выигранных очков
	// method returning the number of points won
	int getscore() const;
	// метод включающий и выключающий фоновую музыку
	// method to enable and disable background music
	void mustet(bool);
	// метод отображения макета следующего тетрамино
	// method for displaying the layout of the next Tetrimino
	void maket(sf::Vector2f);

private:
	const int height;               // высота игрового поля / height of the playing field
	const int width;                // ширина игрового поля / playing field width
	const  float click_dy = 1.0f;   // шаг перемещения тетрамино по y  /  step of moving tetraminos in y
	// массив игрового поля
	// playing field array
	std::vector<std::vector<sf::Color>> square;
	// массив локальных координат фигурок тетрамино 
	// array of local coordinates of tetramino figures
	std::array<std::array<int, 4>, 7> figures
	{ {{1,3,5,7},{2,4,5,7},{3,4,5,6},{3,4,5,7},{2,3,5,7},{3,5,6,7},{2,3,4,5}} };
	// положение прямоугольника в построении тетрамино 
	// the position of the rectangle in the construction of tetraminos
	std::array<sf::Vector2f, 4> t;
	// массив цвета для тетрамино
	// color array for tetramino
	std::array<sf::Color, 7> tetcolor{ {sf::Color::Blue,sf::Color::Cyan,sf::Color::Yellow,
		sf::Color::Green,sf::Color::Magenta,sf::Color::Red,sf::Color::White} };
	// прямоугольник тетрамино
	// tetramino rectangle
	std::unique_ptr<sf::RectangleShape> cube = std::make_unique<sf::RectangleShape>();
	// момент системного времени
	// point of system time
	long long seed = std::chrono::system_clock::now().time_since_epoch().count();
	// запуск генератора случайных чисел
	// start the random number generator
	std::default_random_engine rnd = std::default_random_engine(static_cast<long>(seed));
	// установка диапазона случайных чисел
	// set the range of random numbers
	std::uniform_int_distribution<int> d = std::uniform_int_distribution<int>(0, 6);
	// ссылка на графическое окно
	// link to the graphics window
	sf::RenderWindow& window;
	// начальные координаты тетрамино
	// initial coordinates of tetramino
	const sf::Vector2f tet;
	sf::Time frameRate;          // интервал обновления игровой логики / game logic update interval
	sf::Vector2i typeTet;	     // тип тетрамино / tetramino type
	sf::Vector2i colTet;         // цвет тетрамино / tetramino color
	void newFigrois();	         // новый тетрамино  / new tetramino
	void lineDead(int);	         // уничтожение полоски тетрамино при заполнении поля по горизонтали / destruction of a strip of tetramino when filling the field horizontally
	bool check(ch);	             // проверка положения тетрамино / Tetrimino Position Check
	sf::Int32 delay;             // интервал обработки игровой логики / game logic processing interval
	float click_dx;              // шаг перемещения тетрамино по x  / move step of tetramino in x
	int score;                   // очки выигрыша / scoring points
	bool playMus = false;        // включение музыки / turning on the music
	GameSound mus;				 // объект музыкальных эффектов / music effects object
	float scale;                 // масштаб тетрамино / tetramino scale
	// свойство координат макета тетрамино
	// tetramino layout coordinates property
	sf::Vector2f positionmaket= sf::Vector2f(-1, -1);
};

