#pragma once
#include "Framework/GameObject.h"
#include <iostream>
class Player : public GameObject
{
	int health;
	float speed;
	sf::Texture texture;
public:
	Player();

	void handleInput(float dt);
	void update(float dt);
};

