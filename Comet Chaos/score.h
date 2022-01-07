#include <SFML/Graphics.hpp>
#include <iostream>

#ifndef SCORE_H
#define SCORE_H

class Score {
public:
	int x, y;
	sf::CircleShape rect;
	Score(int, int);
	bool collide(int, int);
};

Score::Score(int spx, int spy)
{
	x = spx;
	y = spy;
	rect = sf::CircleShape(25);
	rect.setPosition(x, y);
	rect.setFillColor(sf::Color(160, 150, 140));
	rect.setOutlineColor(sf::Color::Black);
	rect.setOutlineThickness(6);
}

bool Score::collide(int plx, int ply)
{
	if (plx > x && plx < x + 50 && ply > y && ply < y + 50)
	{
		return true;
	}
	else
	{
		return false;
	}
}

#endif
