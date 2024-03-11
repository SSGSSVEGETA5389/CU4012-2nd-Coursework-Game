#include "Enemy.h"

Enemy::Enemy()
{
	health = 100;
	speed = 150;
	velocity.x = -1;

	if (!texture.loadFromFile("gfx/Enemy.png"))
	{
		std::cout << "File not found\n";
	}
	setTexture(&texture);
	setSize(sf::Vector2f(100, 100));
	setCollisionBox(getPosition(), getSize());
	setTag("Enemy");
	setMass(50.f);
}

Enemy::~Enemy()
{


}

void Enemy::update(float dt, sf::Vector2f& movement)
{
	if (getPosition().x <= 0 || getPosition().x >= window->getSize().x - getSize().x)
	{
		movement.x = -movement.x;
	}

	if (getPosition().y <= 0 || getPosition().y >= window->getSize().y - getSize().y)
	{
		movement.y = -movement.y;

	}
	move(velocity * speed * dt);
}
