#include "Tetramino.h"

bool Tetramino::check(ch ch)
{
	
	switch (ch)
	{
	case Tetramino::ch::x:
	{
		for (int i = 0; i < 4; i++)
		{
			if (((tet.x + (a[i].x + click_dx)* 20) < bordes.x) || ((tet.x + (a[i].x + click_dx)* 20) >= bordes.max)) return false;	
		}
    break;
	}
		
	case Tetramino::ch::y:
	{
	for (int i = 0; i < 4; i++)
	{
		if ((tet.y + (a[i].y+ click_dy) * 20 ) > bordes.maxy)  return false;
	}
	break;
	}
	case Tetramino::ch::r:
	{
		sf::Vector2f p = a[1]; 
		for (int i = 0; i < 4; i++)
		{
			float x = a[i].y - p.y; 
			float y = a[i].x - p.x; 
			if (((p.x - x)*20+tet.x< bordes.x) || ((p.x - x) * 20 + tet.x >= bordes.max) || ((p.y + y)*20+tet.y>bordes.maxy) ) return false;	 
		}
	break;
	}
		
	default:
		break;
	}	
	return true;
}



void Tetramino::newFigrois()
{
	int n = d(rnd); // задаем тип тетрамино
	cube->setFillColor(tetcolor[n]);
	for (int i = 0; i < 4; i++)
	{
		a[i].x = figures[n][i] % 2;
		a[i].y = static_cast<float>(figures[n][i] / 2);
		std::cout << a[i].x << " " << a[i].y<<"\n";
	}

}

void Tetramino::draw()
{
	
	for (int i = 0; i < 4; i++)
	{   
	    // ”станавливаем позицию каждого кусочка тетрамино
		cube->setPosition(tet.x+a[i].x * 20, tet.y+a[i].y * 20);
		// ќтрисовка кубика
		window.draw(*cube);
	}
}

void Tetramino::update(sf::Time const& deltaTime)
{
	frameRate += deltaTime;
	
	if (frameRate > sf::milliseconds(100))
	{
		frameRate = sf::milliseconds(0);
		
		if (check(ch::x)) for (int i = 0; i < 4; i++) a[i].x += click_dx;
			
		click_dx = 0;
	
		if (check(ch::y)) for (int i = 0; i < 4; i++) a[i].y += click_dy;
		else 
		{
			for (int i = 0; i < 4; i++) field[a[i].y][a[i].x] = colorNum;
			newFigrois();
		}
	}

	
}

void Tetramino::Rotate()
{
	if (check(ch::r)) 
	{
	sf::Vector2f p = a[1];
	for (int i = 0; i < 4; i++) 
	{
		float x = a[i].y - p.y;
		float y = a[i].x - p.x;
		a[i].x = p.x - x;
		a[i].y = p.y + y;
	}
	}
}

Tetramino::Tetramino(sf::RenderWindow& window, sf::Vector2f pos, Borders b)
:window(window), tet(pos), bordes(b)
{
	cube->setOutlineColor(sf::Color::Black);
	cube->setOutlineThickness(1);
	newFigrois();
}

void Tetramino::TetDirection(direction dir)
{
	switch (dir)
	{
	case Tetramino::direction::left: {click_dx = -1; }
		break;
	case Tetramino::direction::N: {click_dx = 0; }
		break;
	case Tetramino::direction::Right: {click_dx = 1; }
		break;
	default:
		break;
	}

}
