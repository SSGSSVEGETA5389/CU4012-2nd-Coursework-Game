#include "Ground.h"

Ground::Ground()
{
	setPosition(100, 500);
	setSize(sf::Vector2f(1000, 100));
	setOrigin(getSize() / 2.f);
	setCollisionBox(getPosition(), getSize());
	setTag("Ground");
	setStatic(true);
}
