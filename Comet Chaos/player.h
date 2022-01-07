#include <SFML/Graphics.hpp>
#include <iostream>

#ifndef PLAYER_H
#define PLAYER_H

class Player {
public:
	int x, y;
	std::vector<float> vel;
	sf::CircleShape rect;
	Player(int, int);
	void setVel(int, int);
};

Player::Player(int pX, int pY)
{
	x = pX;
	y = pY;
	vel.push_back(0);
	vel.push_back(0);
	rect = sf::CircleShape(20);
	rect.setPosition(x, y);
	rect.setFillColor(sf::Color(70, 70, 70, 255));
	rect.setOutlineColor(sf::Color::Black);
	rect.setOutlineThickness(6);
}

void Player::setVel(int cx, int cy)
{
	vel[0] = (x - cx) / 25;
	vel[1] = (y - cy) / 25;
}

#endif
