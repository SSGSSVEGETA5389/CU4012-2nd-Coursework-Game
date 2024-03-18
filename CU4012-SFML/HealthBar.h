#pragma once
#include "Player.h"
#include "Framework/GameObject.h"
class HealthBar : public GameObject 
{
	HealthBar(float maxHealth, float width, float height, sf::Color full, sf::Color empty); 
};

