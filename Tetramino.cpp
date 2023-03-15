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
			if ((static_cast<int>(a[i].y - 2) >= 0) && (field[static_cast<int>(a[i].x + 9+ click_dx)][static_cast<int>(a[i].y - 2)] != sf::Color::Black))  return false;
		}
    break;
	}
		
	case Tetramino::ch::y:
	{
	for (int i = 0; i < 4; i++)
	{
		
		if ((tet.y + (a[i].y+ click_dy) * 20 ) > bordes.maxy)  return false;
		if ((static_cast<int>(a[i].y - 2 + click_dy) >= 0) && (field[static_cast<int>(a[i].x + 9)][static_cast<int>(a[i].y - 2 + click_dy)] != sf::Color::Black))  return false; 
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
			
			std::cout <<"a[i].y - 2 - " << a[i].y - 2 << "\n";
			std::cout << "(p.x - x) + 9 - " << (p.x - x) + 9 << "\n";
			std::cout << "(p.y + y) - 2 - " << (p.y + y) - 2 << "\n";
			if ((static_cast<int>((p.y + y) - 2) >= 0) && (field[static_cast<int>((p.x - x) + 9)][static_cast<int>((p.y + y) - 2)] != sf::Color::Black))  return false;
		}
	break;
	}
		
	default:
		break;
	}	
	return true;
}


void Tetramino::Speed()
{
	Delay = 50;
}

void Tetramino::Restart()
{
	for (int i = 0; i < X; i++)
	{
		for (int j = 0; j < Y; j++)
		{
			field[i][j] = sf::Color::Black;
		}
	}
	TN.y = d(rnd); // задаем будущий тип тетрамино
	Score = 0;
	newFigrois();
}

int Tetramino::getScore()
{
	return Score;
}

void Tetramino::newFigrois()
{
	TN.x = TN.y;
	cube->setFillColor(tetcolor[TN.x]);
	for (int i = 0; i < 4; i++)
	{
		a[i].x = figures[TN.x][i] % 2;
		a[i].y = static_cast<float>(figures[TN.x][i] / 2);
	}
   TN.y = d(rnd); // задаем тип тетрамино
}


void Tetramino::draw()
{
	cube->setFillColor(tetcolor[TN.y]);
	for (int i = 0; i < 4; i++)
	{	
		// Устанавливаем позицию каждого кусочка тетрамино
		cube->setPosition(70+(figures[TN.y][i] % 2)*20, (static_cast<float>(figures[TN.y][i] / 2))*20+30);
		// Отрисовка кубика
		window.draw(*cube);	
	}
	
	for (int i = 0; i < X; i++) 
	{
		for (int j = 0; j < Y; j++)
		{
			if (field[i][j] == sf::Color::Black) continue;
			cube->setFillColor(field[i][j]);
			cube->setPosition(static_cast<float>(210+i*20),static_cast<float>(25+j*20));
			window.draw(*cube);
		}
	}

	cube->setFillColor(tetcolor[TN.x]);
	for (int i = 0; i < 4; i++)
	{   
	    // Устанавливаем позицию каждого кусочка тетрамино
		cube->setPosition(tet.x+a[i].x * 20, tet.y+a[i].y * 20);
		// Отрисовка кубика
		window.draw(*cube);
	}
}

sf::Vector2f Tetramino::getPositio()
{
	sf::Vector2f pos;
	pos.x = a[1].x * 20 + tet.x;
	pos.y = tet.y + a[1].y * 20;
	return pos;
}

void Tetramino::update(sf::Time const& deltaTime)
{
	frameRate += deltaTime;
	
	if (frameRate > sf::milliseconds(Delay))
	{
		frameRate = sf::milliseconds(0);
		
		if (check(ch::x)) for (int i = 0; i < 4; i++) a[i].x += click_dx;
			
		click_dx = 0;
	
		if (check(ch::y)) for (int i = 0; i < 4; i++) a[i].y += click_dy;
		else 
		{   
			
			for (int i = 0; i < 4; i++)
			{
				if (static_cast<int>(a[i].y - 2) < 0) { Restart(); return; }
				field[static_cast<int>(a[i].x+9)][static_cast<int>(a[i].y-2)] = cube->getFillColor();
			}
			int numLine = 0;
				for (int j = 0; j < 31; j++)
				{
					int line = 0;
				for (int i = 0; i < 20; i++)
			    {	
					if (field[i][j] != sf::Color::Black) line++;
					if (line == 20) 
					{LineDead(j);
					numLine++;
					}
				}
				}
				if (numLine != 0) 
				{
					Score += 5*(numLine * numLine);
				}
			if (Delay != 300) Delay = 300;
			newFigrois();
		}
	}

	
}

void Tetramino::LineDead(int g) 
{
	for (int i = g; i > 0; i--)
	{
		for (int j = 0; j < X; j++)
		{
			field[j][i] = field[j][i-1];
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
	Restart();
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
