#include "Level.h"
#include <iostream>
using namespace std;

Level::Level(sf::RenderWindow* hwnd, Input* in)
{
	window = hwnd;
	input = in;

	// initialise game objects
	circle.setRadius(5);
	circle.setFillColor(sf::Color::Black);
	circle.setPosition(300, 300);
	circle.setOutlineColor(sf::Color::Black);
	circle.setOutlineThickness(3);

	circle2.setRadius(5);
	circle2.setFillColor(sf::Color::Red);
	circle2.setPosition(300, 300);
	circle2.setOutlineColor(sf::Color::Black);
	circle2.setOutlineThickness(3);

	player.setSize(sf::Vector2f(50, 50));
	player.setFillColor(sf::Color::Black);
	player.setPosition(300, 500);

	movingRight = true;
	c2movingRight = true;
	c2movingUp = true;
	speed = 1;
}

Level::~Level()
{
	
}

// handle user input
void Level::handleInput(float dt)
{
	if (input->isKeyDown(sf::Keyboard::Up))
		player.setPosition(player.getPosition().x, player.getPosition().y - 1);
	else if (input->isKeyDown(sf::Keyboard::Down))
		player.setPosition(player.getPosition().x, player.getPosition().y + 1);
	else if (input->isKeyDown(sf::Keyboard::Left))
		player.setPosition(player.getPosition().x - 1, player.getPosition().y);
	else if (input->isKeyDown(sf::Keyboard::Right))
		player.setPosition(player.getPosition().x + 1, player.getPosition().y);

	if (input->isKeyDown(sf::Keyboard::W) && speed < 5)
		speed++;
	else if (input->isKeyDown(sf::Keyboard::S) && speed > 1)
		speed--;

}

// Update game objects
void Level::update(float dt)
{
	if (circle.getPosition().x == window->getSize().x)
	{
		movingRight = false;
	}
	else if (circle.getPosition().x == 0)
	{
		movingRight = true;
	}

	if (movingRight == true)
		circle.setPosition(circle.getPosition().x + 1, circle.getPosition().y);
	else
		circle.setPosition(circle.getPosition().x - 1, circle.getPosition().y);

	if (c2movingRight == true && circle2.getPosition().x + speed < window->getSize().x)
		circle2.setPosition(circle2.getPosition().x + speed, circle2.getPosition().y);
	else if (c2movingRight == false && circle2.getPosition().x > speed)
		circle2.setPosition(circle2.getPosition().x - speed, circle2.getPosition().y);
	else if (circle2.getPosition().x >= window->getSize().x - 15)
	{
		c2movingRight = false;
		circle2.setPosition(circle2.getPosition().x - 15, circle2.getPosition().y);
	}
	else if (circle2.getPosition().x <= 15)
	{
		c2movingRight = true;
		circle2.setPosition(circle2.getPosition().x + 15, circle2.getPosition().y);
	}

	if (c2movingUp == true && circle2.getPosition().y > speed)
		circle2.setPosition(circle2.getPosition().x, circle2.getPosition().y - speed);
	else if (c2movingUp == false && circle2.getPosition().y + speed < window->getSize().y)
		circle2.setPosition(circle2.getPosition().x, circle2.getPosition().y + speed);
	else if (circle2.getPosition().y >= window->getSize().y - 15)
	{
		c2movingUp = true;
		circle2.setPosition(circle2.getPosition().x, circle2.getPosition().y - 15);
	}
	else if (circle2.getPosition().y <= 15)
	{
		c2movingUp = false;
		circle2.setPosition(circle2.getPosition().x, circle2.getPosition().y + 15);
	}

}

// Render level
void Level::render()
{
	beginDraw();

	window->draw(circle);
	window->draw(player);
	window->draw(circle2);
	
	endDraw();
}

// clear back buffer
void Level::beginDraw()
{
	window->clear(sf::Color(100, 149, 237));
}

// Ends rendering to the back buffer, and swaps buffer to the screen.
void Level::endDraw()
{
	window->display();
}