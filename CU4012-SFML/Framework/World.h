#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <list>
#include "GameObject.h"

class World
{
	std::list<GameObject*> objects; // becomes ptrs internally but never exposed
	sf::Vector2f gravity;

public:
	World(sf::Vector2f gravity);

	void AddGameObject(GameObject& obj);
	void RemoveGameObject(GameObject& obj);
	void UpdatePhysics(float deltaTime);
};

