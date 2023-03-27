#include "Tetramino.h"

bool Tetramino::check(ch ch)
{
	
	switch (ch)
	{
	case Tetramino::ch::x:
	{
		for (int i = 0; i < 4; i++)
		{
			if (((tet.x + (a[i].x + click_dx)* 20) <= bordes.x) || ((tet.x + (a[i].x + click_dx)* 20) >= bordes.max)) return false;	
			if ((static_cast<int>(a[i].y - 2) >= 0) && (square[static_cast<size_t>(a[i].x + 9+ click_dx)][static_cast<size_t>(a[i].y - 2)] != sf::Color::Black))  return false;
		}
    break;
	}
		
	case Tetramino::ch::y:
	{
	for (int i = 0; i < 4; i++)
	{
		
		if ((tet.y + (a[i].y+ click_dy) * 20 ) >= bordes.maxy)  return false;
		if ((static_cast<int>(a[i].y - 2 + click_dy) >= 0) && (square[static_cast<size_t>(a[i].x + 9)][static_cast<size_t>(a[i].y - 2 + click_dy)] != sf::Color::Black))  return false;
	}
	break;
	}
	case Tetramino::ch::rotation:
	{
		sf::Vector2f p = a[1]; 
		for (int i = 0; i < 4; i++)
		{
			float x = a[i].y - p.y; 
			float y = a[i].x - p.x; 
			if (((p.x - x)*20+tet.x<= bordes.x) || ((p.x - x) * 20 + tet.x >= bordes.max) || ((p.y + y)*20+tet.y>=bordes.maxy) ) return false;
			
			if ((static_cast<int>((p.y + y) - 2) >= 0) && (square[static_cast<size_t>((p.x - x) + 9)][static_cast<size_t>((p.y + y) - 2)] != sf::Color::Black))  return false;
		}
	break;
	}
		
	default:
		break;
	}	
	return true;
}


void Tetramino::speed()
{
	mus.play(4);
	delay = 10;
}

void Tetramino::restart()
{
	for (int i = 0; i < X; i++)
	{
		for (int j = 0; j < Y; j++)
		{
			square[i][j] = sf::Color::Black;
		}
	}
	tn.y = d(rnd); // ������ ������� ��� ���������
	col.y = d(rnd);
	score = 0;
	newFigrois();
}

void Tetramino::mustet(bool m)
{
	playMus = m;
}

int Tetramino::getscore() const
{
	return score;
}

void Tetramino::newFigrois()
{
	tn.x = tn.y;
	col.x = col.y;
	cube->setFillColor(tetcolor[col.x]);
	for (int i = 0; i < 4; i++)
	{
		a[i].x = figures[tn.x][i] % 2;
		a[i].y = static_cast<float>(figures[tn.x][i] / 2);
	}
   tn.y = d(rnd); // ������ ��� ���������
   col.y = d(rnd);
   delay = 250;
}

void Tetramino::update(sf::Time const& deltaTime)
{
	frameRate += deltaTime;
	
	if (frameRate > sf::milliseconds(delay))
	{
		frameRate = sf::milliseconds(0);
		
		if (check(ch::x) && click_dx !=0)
		{
			for (int i = 0; i < 4; i++) a[i].x += click_dx; mus.play(3);
		}
			
		click_dx = 0;
	
		if (check(ch::y)) { for (int i = 0; i < 4; i++)  a[i].y += click_dy; 	}
		else 
		{   
			for (int i = 0; i < 4; i++)
			{
				if (static_cast<int>(a[i].y - 2) < 0) { restart(); mus.play(2); return; }
				
				auto index1 = static_cast<size_t>(a[i].x + 9);
				auto index2 = static_cast<size_t>(a[i].y-2);
				
				square[index1][index2] = sf::Color(tetcolor[col.x]);
			}
			int numLine = 0;
				for (int j = 0; j < 31; j++)
				{
					int line = 0;
				for (int i = 0; i < 20; i++)
			    {	
					if (square[i][j] != sf::Color::Black) line++;
					if (line == 20) 
					{
					lineDead(j);
					mus.play(1);
					numLine++;
					}
				}
				}
				if (numLine != 0) 
				{
					score += 5*(numLine * numLine);
				}
			newFigrois();
		}
	}

	
}
void Tetramino::draw()
{
	if (playMus)  mus.play(0); else mus.stop(0);
	
	cube->setFillColor(tetcolor[col.y]);
	for (int i = 0; i < 4; i++)
	{	
		// ������������� ������� ������� ������� ���������
		cube->setPosition((figures[tn.y][i] % 2)*20, (static_cast<float>(figures[tn.y][i] / 2))*20);
		cube->move(70,30);
		// ��������� ������
		window.draw(*cube);	
	}
	
	for (int i = 0; i < X; i++) 
	{
		for (int j = 0; j < Y; j++)
		{
			//if (square[i][j] == sf::Color::Black) continue;
			
			cube->setFillColor(square[i][j]);
			cube->setPosition(static_cast<float>(i*20),static_cast<float>(j*20));
			cube->move(210,20);
			window.draw(*cube);
		}
	}

	cube->setFillColor(tetcolor[col.x]);
	for (int i = 0; i < 4; i++)
	{   
	    // ������������� ������� ������� ������� ���������
		cube->setPosition(a[i].x * 20, a[i].y * 20);
		cube->move(tet.x, tet.y);
		// ��������� ������
		window.draw(*cube);
	}
}

sf::Vector2f Tetramino::getPositio()
{
	sf::Vector2f pos;
	pos.x = a[1].x * 20 + tet.x;
	pos.y =  a[1].y * 20 + tet.y;
	return pos;
}



void Tetramino::lineDead(int g) 
{
	for (int i = g; i > 0; i--)
	{
		for (int j = 0; j < X; j++)
		{
			square[j][i] = square[j][static_cast<size_t>(i-1)];
		}
		
	}
}

void Tetramino::rotate()
{
	if (check(ch::rotation))
	{
	sf::Vector2f p = a[1];
	for (int i = 0; i < 4; i++) 
	{
		float x = a[i].y - p.y;
		float y = a[i].x - p.x;
		a[i].x = p.x - x;
		a[i].y = p.y + y;
	}
	mus.play(3);
	}
}

Tetramino::Tetramino(sf::RenderWindow& window, sf::Vector2f pos, Borders b)
:window(window), tet(pos), bordes(b)
{
	cube->setOutlineColor(sf::Color(78, 87, 84));
	//cube->setOutlineColor(sf::Color::Black);
	cube->setOutlineThickness(1);
	restart();
}

void Tetramino::tetDirection(direction dir)
{
	click_dx =static_cast<float> (dir); 
}
		

