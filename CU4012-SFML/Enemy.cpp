#include "Enemy.h"

Enemy::Enemy()
{
	health = 100;
	speed = 150;
	velocity.x = -150;


	setSize(sf::Vector2f(100, 100));
	setPosition(500, 100);
	setCollisionBox(getPosition(), getSize());
	setTag("Enemy");
	setMass(50.f);
}
void Enemy::update(float dt)
{
	//move(velocity * speed * dt);
}

void Enemy::setCustomTexture(std::string path)
{
	if (!texture.loadFromFile(path))
	{
		std::cout << "File not found\n";
	}
	setTexture(&texture);
}
