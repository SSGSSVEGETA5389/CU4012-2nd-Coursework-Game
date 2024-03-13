#include "Platform.h"

Platform::Platform()
{
	platformerTex.loadFromFile("gfx/Platform.png"); 

	setTexture(&platformerTex);
	setPosition(500, 500);
	setSize(sf::Vector2f(800, 50));
	setOrigin(getSize() / 2.f);
	setCollisionBox(getPosition(), getSize());
	setTag("Ground");
	setStatic(true);

}

Platform::~Platform()
{


}

void Platform::handleInput(float dt)
{


}
