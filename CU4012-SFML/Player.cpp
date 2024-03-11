#include "Player.h"

Player::Player()
{
 
	health = 100;
	speed = 200;
	
	if (!texture.loadFromFile("gfx/Player.png"))
	{
		std::cout << "File not found\n";
	}
	setTexture(&texture);
	setSize(sf::Vector2f(100, 100));
	setCollisionBox(getPosition(), getSize());
	setMass(100.f);
	setTag("player");
}

void Player::handleInput(float dt)
{
	if (input->isKeyDown(sf::Keyboard::A))
	{
		velocity = sf::Vector2f(-1 * speed, 0);
	}
	else if (input->isKeyDown(sf::Keyboard::D))
	{
		velocity = sf::Vector2f(1 * speed, 0);
	}
	else if (input->isKeyDown(sf::Keyboard::S))
	{
		velocity = sf::Vector2f(0, 1 * speed);
	}

	else if (input->isKeyDown(sf::Keyboard::W))
	{
		velocity = sf::Vector2f(0, -1 * speed);
	}
	else
	{
		velocity = sf::Vector2f(0, 0);
	}

}

void Player::update(float dt)
{
}
