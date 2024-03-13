#include "Background.h"

Background::Background()
{
	backgroundTex.loadFromFile("gfx/Background.png");

	setTexture(&backgroundTex);
	setSize(sf::Vector2f(698, 478));
}

Background::~Background()
{

}

void Background::handleInput(float dt)
{

}
