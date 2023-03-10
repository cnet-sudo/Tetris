#include "Tetramino.h"

void Tetramino::newFigrois()
{
	int n = 3; // задаем тип тетрамино
	cube->setFillColor(tetcolor[n]);
	for (int i = 0; i < 4; i++)
	{
		a[i].x = figures[n][i] % 2;
		a[i].y = figures[n][i] / 2;
		std::cout << a[i].x << " " << a[i].y<<"\n";
	}

}

void Tetramino::draw()
{
	float iy = 0;
	for (int i = 0; i < 4; i++)
	{   
	    float ix = 0;
		// Устанавливаем отступ в один пиксель для каждого кусочка
		
			if (a[i].x >0) ix=1;
			if (i!=0) if (a[i].y > a[i-1].y) iy++;
		
		// Устанавливаем позицию каждого кусочка тетрамино
		cube->setPosition(tetx+static_cast<float>(a[i].x * 20)+moveX+ix, tety+ static_cast<float>(a[i].y * 20)+moveY+iy);
		// Отрисовка кубика
		window.draw(*cube);
	}
}

void Tetramino::update(sf::Time const& deltaTime)
{
	frameRate += deltaTime;

	if (frameRate > sf::milliseconds(3))
	{
		frameRate = sf::milliseconds(0);
		moveX += click_dx;
		click_dx = 0;
	}
}

sf::Vector2f Tetramino::getPosition() const
{
	auto myxy = sf::Vector2f(tetx+moveX, tety+moveY);
	
	return myxy ;
}

float Tetramino::getStep() const
{
	return click_dx;
}

Tetramino::Tetramino(sf::RenderWindow& window, float x, float y):window(window),tetx(x),tety(y)
{
	newFigrois();
}

void Tetramino::Tetdirection(direction dir)
{
	click_dx = static_cast<float>(dir);
}
