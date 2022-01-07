#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
#include <fstream>
#include "player.h"
#include "enemy.h"
#include "score.h"
#include "button.h"

int getHighscore()
{
	std::string line;
	std::ifstream myfile("highscore.txt");
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			return std::stoi(line);
		}
		myfile.close();
	}
	return 0;
}

int main()
{
	//Setup window
	sf::RenderWindow window(sf::VideoMode(500, 500), "Comet Chaos");
	window.setFramerateLimit(60);
	//Setup player
	Player p(200, 200);
	//Random seed
	srand(time(0));
	//Setup enemies
	std::vector<Enemy> enemies;
	enemies.push_back(Enemy(rand() % 500, -150, rand() % 70 + 25, rand() % 10 - 5, rand() % 10));
	enemies.push_back(Enemy(rand() % 500, -150, rand() % 70 + 25, rand() % 10 - 5, rand() % 10));
	enemies.push_back(Enemy(rand() % 500, -150, rand() % 70 + 25, rand() % 10 - 5, rand() % 10));
	//Setup score
	int score = 0;
	Score s(rand() % 500, rand() % 500);
	int highscore = getHighscore();
	//Setup font
	sf::Font font;
	font.loadFromFile("Arial.ttf");
	//Setup score text
	sf::Text text;
	text.setFont(font);
	text.setPosition(20, 15);
	text.setCharacterSize(30);
	text.setFillColor(sf::Color(200, 200, 200));
	text.setString(std::to_string(score) + "/" + std::to_string(highscore));
	//Setup title
	sf::Text title;
	title.setFont(font);
	title.setPosition(100, 100);
	title.setCharacterSize(50);
	title.setFillColor(sf::Color(200, 200, 200));
	title.setString("Comet Chaos");
	//Setup button
	Button button(200, 200, 110, 30, "Play Again!");
	//Setup start button
	Button sbutton(196, 225, 112, 30, "Play Game!");
	//Setup gravity
	float gravity = 0;
	//Loop
	bool running = false;
	int scene = 1;
	bool reset = false;
	while (window.isOpen())
	{
		if (reset == true)
		{
			enemies[0] = Enemy(rand() % 500, -150, rand() % 70 + 25, rand() % 10 - 5, rand() % 8);
			enemies[1] = Enemy(rand() % 500, -150, rand() % 70 + 25, rand() % 10 - 5, rand() % 8);
			enemies[2] = Enemy(rand() % 500, -150, rand() % 70 + 25, rand() % 10 - 5, rand() % 8);
			p.x = 200;
			p.y = 200;
			p.vel[0] = 0;
			p.vel[1] = 0;
			score = 0;
			srand(time(0));
			gravity = 0;
			reset = false;
		}
		if (scene == 1)
		{
			running = false;
		}
		if (running == false)
		{
			p.vel[0] = 0;
			p.vel[1] = 0;
		}
		if (s.collide(p.x, p.y))
		{
			score += 1;
			s.x = rand() % 500;
			s.y = rand() % 500;
			text.setString(std::to_string(score) + "/" + std::to_string(highscore));
		}
		gravity += 0.025;
		p.vel[1] += gravity;
		if (p.vel[0] > 25)
		{
			p.vel[0] = 25;
		}
		if (p.vel[1] > 25)
		{
			p.vel[1] = 25;
		}
		if (p.vel[0] < -25)
		{
			p.vel[0] = -25;
		}
		if (p.vel[1] < -25)
		{
			p.vel[1] = -25;
		}
		p.x += p.vel[0];
		p.y += p.vel[1];
		p.rect.setPosition(p.x - 25, p.y - 25);
		s.rect.setPosition(s.x, s.y);
		if (p.x < -20)
		{
			p.x = 520;
		}
		if (p.x > 520)
		{
			p.x = -20;
		}
		if (p.y < -20)
		{
			p.y = 520;
		}
		if (p.y > 520)
		{
			p.y = -20;
		}
		for (int i = 0; i < enemies.size(); i++)
		{
			enemies[i].rect.setPosition(enemies[i].x, enemies[i].y);
			enemies[i].move();
			if (enemies[i].collide(p.x, p.y))
			{
				running = false;
				text.setString(std::to_string(score) + "/" + std::to_string(highscore));
				if (score >= highscore)
				{
					std::ofstream myfile("highscore.txt");
					if (myfile.is_open())
					{
						myfile << score;
						myfile.close();
					}
				}
			}
			if (running == false)
			{
				enemies[i].vel[0] = 0;
				enemies[i].vel[1] = 0;
			}
			if (enemies[i].y > 500 + enemies[i].s)
			{
				enemies[i] = Enemy(rand() % 500, -80, rand() % 70 + 25, rand() % 10 - 5, rand() % 10);
			}
			if (enemies[i].vel[1] == 0 && running == true)
			{
				enemies[i].vel[1] = rand() % 20;
			}
		}
		//Events
		sf::Event event;
		while (window.pollEvent(event))
		{
			//Close window
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			//Click
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (running == true)
				{
					p.setVel(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
					gravity = 0;
				}
				if (button.hovering(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y) && running == false && scene == 2)
				{
					running = true;
					reset = true;
				}
				if (sbutton.hovering(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y) && running == false && scene == 1)
				{
					scene = 2;
					running = true;
				}
			}
		}
		//Rendering
		window.clear(sf::Color(10, 10, 10));
		if (scene == 1)
		{
			window.draw(title);
			window.draw(sbutton.rect);
			window.draw(sbutton.text);
		}
		if (scene == 2)
		{
			window.draw(p.rect);
			for (int i = 0; i < enemies.size(); i++)
			{
				window.draw(enemies[i].rect);
			}
			window.draw(text);
			window.draw(s.rect);
			if (running == false)
			{
				window.draw(button.rect);
				window.draw(button.text);
			}
		}
		window.display();
	}
	return 0;
}