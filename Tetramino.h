#pragma once
#include"AssetManager.h"
#include "GameSound.h"
#include <array>
#include <iostream>
#include <chrono>
#include <random>



class Tetramino
{
public:

	// ��������� ������
	struct Borders
	{
		float x;
		float max;
		float maxy;

		Borders(float x,float x1,float y):x(x),max(x1),maxy(y){}
	};

    // ������ ����������� ��������
	enum class direction {left=-1,NuLL,Right};
	// ������ �������� ���������  
	enum class ch {x,y, rotation};

	explicit Tetramino(sf::RenderWindow& window,sf::Vector2f, Borders);
	// ������ �������� ���������
	void TetDirection(direction dir);
	// ��������� ���������
	void draw();
	// ���������� ������� ������ ���������
	void update(sf::Time const& deltaTime);
	// �������� ���������
	void Rotate();
	// ���������� ���������� ������ ���������
	sf::Vector2f getPositio();
	// ��������� ������� ���������
	void Speed();
	// ������� ����
	void Restart();
	// ���������� ��������� ����
	int getScore() const;
	// �������� ��������� ������
	void mustet(bool m);
private:
	static const int Y = 31;       // ������ �������� ����
	static const int X = 20;       // ������ �������� ����
    const float click_dy = 1.0f;;  // ��� ����������� ��������� �� y
	// ������� ����
	std::array<std::array<sf::Color, Y>, X> square;
	// ������ ������� ���������
	std::array<std::array<int, 4>, 7> figures{ {{1,3,5,7},{2,4,5,7},{3,4,5,6},{3,4,5,7},{2,3,5,7},{3,5,6,7},{2,3,4,5}} };
	// ��������� ���������
	std::array<sf::Vector2f, 4> a;
	// ���� ���������
	std::array<sf::Color, 7> tetcolor{ {sf::Color::Blue,sf::Color::Cyan,sf::Color::Yellow,sf::Color::Green,sf::Color::Magenta,sf::Color::Red,sf::Color::White} };

	// �������������� ���������
	std::unique_ptr<sf::RectangleShape> cube = std::make_unique<sf::RectangleShape>(sf::Vector2f(18,18));

	// ������ ���������� �������
	long long seed = std::chrono::system_clock::now().time_since_epoch().count();
	// ������ ���������� ��������� �����
	std::default_random_engine rnd=std::default_random_engine(static_cast<long>(seed));
	// ��������� ��������� ��������� �����
	std::uniform_int_distribution<int> d=std::uniform_int_distribution<int>(0,6);

	sf::RenderWindow& window;    // ����������� ����
	
	const sf::Vector2f tet;      // ��������� ���������� ���������
	
	
	sf::Time frameRate;          // �������� ���������� ������� ������
	Borders bordes;              // ������� ����������� ���������
	sf::Vector2i TN;	         // ��� ���������
	sf::Vector2i Col;            // ����
	void newFigrois();	         // ����� ���������
	void LineDead(int g);	     // ����������� �������
	bool check(ch ch);	         // �������� ��������� ���������
	sf::Int32 Delay;             // �������� ��������� ������� ������
	float click_dx;              // ��� ����������� ��������� �� x 
	
	int Score;                   // ���� ��������

	bool PlayMus = false;         // ��������� ������
	GameSound mus;				 // ������ ����������� ��������
};

