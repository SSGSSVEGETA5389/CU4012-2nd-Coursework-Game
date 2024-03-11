#pragma once
#include "Framework/GameObject.h"
#include <iostream>
class Enemy :
    public GameObject
{
    int health;
    float speed;
    sf::Texture texture;

public:
    Enemy();

    void update(float dt, sf::Vector2f& movement);
};

