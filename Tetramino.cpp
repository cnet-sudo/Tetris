#include "Tetramino.h"

Tetramino::Tetramino(sf::RenderWindow& window, sf::Vector2f pos, sf::Vector2i square_size, float scale)
: height(square_size.y), width(square_size.x), window(window), tet(pos), scale(scale)
{
	cube->setOutlineColor(sf::Color(78, 87, 84));
	cube->setOutlineThickness(-1);
	cube->setSize(sf::Vector2f(scale,scale));
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
	for (int i = 0; i < t.size(); i++)
	{
		t[i].x = figures[typeTet.x][i] % 2+ static_cast<float>(floor(width/2));
		t[i].y = static_cast<float>(figures[typeTet.x][i] / 2);
	}
	typeTet.y = d(rnd);
	colTet.y = d(rnd);
    delay = 250;
}

void Tetramino::update(sf::Time const& deltaTime)
{	
	if (playMus)  mus.play(0); else mus.stop(0);
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
			for (int i = 0; i < t.size(); i++)
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
	sf::Vector2f centerRotation = t[1];
	for (int i = 0; i < t.size(); i++) 
	{
		float x = t[i].y - centerRotation.y;
		float y = t[i].x - centerRotation.x;
		t[i].x = centerRotation.x - x;
		t[i].y = centerRotation.y + y;
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
			{	for (int i = 0; i < t.size(); i++)
				{if ((t[i].x + click_dx < 0) || 
				(t[i].x + click_dx >static_cast<float>(width-1))) return false;	
				if ((static_cast<int>(t[i].y) >= 0) && 
				(square[static_cast<size_t>(t[i].x + click_dx)][static_cast<size_t>(t[i].y)]
				!= sf::Color::Black))  return false;}
    	break;}
		case Tetramino::ch::y:
	        {	for (int i = 0; i < t.size(); i++)
				{if ((t[i].y+ click_dy) > static_cast<float>(height-1))  return false;
				if ((static_cast<int>(t[i].y + click_dy) >= 0) && 
				(square[static_cast<size_t>(t[i].x )][static_cast<size_t>(t[i].y + click_dy)] 
				!= sf::Color::Black))  return false;}
		break;}
		case Tetramino::ch::rotation:
			{ sf::Vector2f centerRotation = t[1];
				for (int i = 0; i < t.size(); i++)
				{
				float x = t[i].y - centerRotation.y;
				float y = t[i].x - centerRotation.x;
			    if (((centerRotation.x - x)<0) || ((centerRotation.x - x)  > static_cast<float>(width-1)) ||
				((centerRotation.y + y)> static_cast<float>(height-1))) return false;
				if ((static_cast<int>(centerRotation.y + y) >= 0) &&
				(square[static_cast<size_t>(centerRotation.x - x)][static_cast<size_t>(centerRotation.y + y)]
				!= sf::Color::Black))  return false;
				}
		break;}
	default:
		break;
	}	
	return true;
}

void Tetramino::draw()
{
	if (positionmaket.x >= 0) 
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
			cube->setPosition(static_cast<float>(i)*scale,static_cast<float>(j)*scale);
			cube->move(tet);
			window.draw(*cube);
		}
	}
	cube->setFillColor(tetcolor[colTet.x]);
	for (int i = 0; i < t.size(); i++)
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