#include <SFML/Graphics.hpp>
#include <iostream>

#ifndef ENEMY_H
#define ENEMY_H

class Enemy {
public:
	int x, y, s;
	std::vector<double> vel;
	sf::CircleShape rect;
	Enemy(int, int, int, float, float);
	void move();
	bool collide(int, int);
};

Enemy::Enemy(int sx, int sy, int si, float xs, float ys)
{
	x = sx;
	y = sy;
	s = si;
	vel.push_back(xs);
	vel.push_back(ys);
	rect = sf::CircleShape(s / 2);
	rect.setPosition(x, y);
	rect.setFillColor(sf::Color(30, 30, 30));
	rect.setOutlineColor(sf::Color::Black);
	rect.setOutlineThickness(s / 8);
}

void Enemy::move()
{
	x += vel[0] * 2;
	y += vel[1] * 2;
}

bool Enemy::collide(int plx, int ply)
{
	if (plx > x && plx < x + s && ply > y && ply < y + s)
	{
		return true;
	}
	else
	{
		return false;
	}
}

#endif
