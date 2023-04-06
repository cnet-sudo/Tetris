#include "Tetramino.h"

Tetramino::Tetramino(sf::RenderWindow& window, sf::Vector2f pos, sf::Vector2i size, float scale)
:window(window), tet(pos), height(size.y), width(size.x),scale(scale)
{
	cube->setOutlineColor(sf::Color(78, 87, 84));
	cube->setOutlineThickness(-1);
	cube->setSize(sf::Vector2f(scale,scale));
	positionmaket = sf::Vector2f(-1,-1);
	for (int i = 0; i < width; i++)
	{
		std::vector<sf::Color> v;
		for (int j = 0; j < height; j++) {
			v.push_back(sf::Color::Black);
		}
		square.push_back(v);
	}
	restart();
}

void Tetramino::restart()
{
	for (int i = 0; i < width; i++)
	{
		
		for (int j = 0; j < height; j++)
		{
			square[i][j] = sf::Color::Black;
		}
	}
	typeTet.y = d(rnd);
	colTet.y = d(rnd);
	score = 0;
	newFigrois();
}

void Tetramino::newFigrois()
{
	typeTet.x = typeTet.y;
	colTet.x = colTet.y;
	for (int i = 0; i < 4; i++)
	{
		t[i].x = figures[typeTet.x][i] % 2+static_cast<int>(width/2);
		t[i].y = static_cast<float>(figures[typeTet.x][i] / 2);
	}
	typeTet.y = d(rnd);
	colTet.y = d(rnd);
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
			for (int i = 0; i < 4; i++) t[i].x += click_dx; mus.play(3); click_dx = 0;
		}
		
		if (check(ch::y)) { for (int i = 0; i < 4; i++)  t[i].y += click_dy; }
		else 
		{   
			for (int i = 0; i < 4; i++)
			{
				if (static_cast<int>(t[i].y) == 2) { restart(); mus.play(2); return; }
				square[static_cast<size_t>(t[i].x)][static_cast<size_t>(t[i].y)] = sf::Color(tetcolor[colTet.x]);
			}
			int numLine = 0;
				for (int j = 0; j < height; j++)
				{
				int line = 0;
				for (int i = 0; i < width; i++)
			    {	
					if (square[i][j] != sf::Color::Black) line++;
					if (line == width)
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

void Tetramino::tetDirection(direction dir)
{
	click_dx =static_cast<float> (dir); 
}

void Tetramino::rotate()
{
	if (check(ch::rotation))
	{
	sf::Vector2f p = t[1];
	for (int i = 0; i < 4; i++) 
	{
		float x = t[i].y - p.y;
		float y = t[i].x - p.x;
		t[i].x = p.x - x;
		t[i].y = p.y + y;
	}
	mus.play(3);
	}
}

void Tetramino::speed()
{
	mus.play(4);
	delay = 10;
}

void Tetramino::lineDead(int g) 
{
	for (int i = g; i > 0; i--)
	{
		for (int j = 0; j < width; j++)
		{
			square[j][i] = square[j][static_cast<size_t>(i-1)];
		}
	}
}

bool Tetramino::check(ch ch)
{
	switch (ch)
	{	case Tetramino::ch::x:
			{	for (int i = 0; i < 4; i++)
				{if ((t[i].x + click_dx < 0) || 
				(t[i].x + click_dx >width-1)) return false;	
						
			if ((static_cast<int>(t[i].y) >= 0) && 
				(square[static_cast<size_t>(t[i].x + click_dx)][static_cast<size_t>(t[i].y)]
				!= sf::Color::Black))  return false;}
    	break;}
		case Tetramino::ch::y:
	        {	for (int i = 0; i < 4; i++)
				{if ((t[i].y+ click_dy) > height-1)  return false;
				if ((static_cast<int>(t[i].y + click_dy) >= 0) && 
				(square[static_cast<size_t>(t[i].x )][static_cast<size_t>(t[i].y + click_dy)] 
				!= sf::Color::Black))  return false;}
		break;}
		case Tetramino::ch::rotation:
			{ sf::Vector2f p = t[1]; 
				for (int i = 0; i < 4; i++)
				{
				float x = t[i].y - p.y; 
				float y = t[i].x - p.x; 
			    if (((p.x - x)<0) || ((p.x - x)  >width-1) || 
				((p.y + y)>height-1) ) return false;
				
				if ((static_cast<int>(p.y + y) >= 0) && 
				(square[static_cast<size_t>(p.x - x)][static_cast<size_t>(p.y + y)] 
				!= sf::Color::Black))  return false;}
		break;}
	default:
		break;
	}	
	return true;
}

void Tetramino::draw()
{
	if (playMus)  mus.play(0); else mus.stop(0);
	if (positionmaket.x > 0) 
	{
	cube->setFillColor(tetcolor[colTet.y]);
	for (int i = 0; i < 4; i++)
	{	
		cube->setPosition((figures[typeTet.y][i] % 2)*scale, (static_cast<float>(figures[typeTet.y][i] / 2))* scale);
		cube->move(positionmaket);
		window.draw(*cube);	
	}
    }
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			cube->setFillColor(square[i][j]);
			cube->setPosition(static_cast<float>(i* scale),static_cast<float>(j* scale));
			cube->move(tet);
			window.draw(*cube);
		}
	}

	cube->setFillColor(tetcolor[colTet.x]);
	for (int i = 0; i < 4; i++)
	{   
	    cube->setPosition(t[i].x * scale, t[i].y * scale);
		cube->move(tet);
		window.draw(*cube);
	}
}

void Tetramino::mustet(bool m)
{
	playMus = m;
}

int Tetramino::getscore() const
{
	return score;
}

sf::Vector2f Tetramino::getPositio()
{
	sf::Vector2f pos;
	pos.x = t[1].x * scale + tet.x;
	pos.y =  t[1].y * scale + tet.y;
	return pos;
}

void Tetramino::maket(sf::Vector2f posmak)
{
	positionmaket = posmak;
}