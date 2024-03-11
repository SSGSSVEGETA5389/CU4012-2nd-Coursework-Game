#pragma once

#include <SFML/Graphics.hpp>
#include "Framework/BaseLevel.h"
#include "Framework/Input.h"
#include "Framework/GameState.h"
#include "Framework/World.h"
#include <string>
#include <iostream>
#include "Player.h"
#include "Background.h"
#include "Level.h"
#include "Enemy.h"
#include "Ground.h"


class Level : public BaseLevel{
public:
	Level(sf::RenderWindow* hwnd, Input* in, GameState* gs, World* w);
	~Level();

	void handleInput(float dt) override;
	void update(float dt) override;
	void render();

private:
	// Default variables for level class.

	Ground ground

	//Player 
	Player Player; 

	

	Background bg; 
	sf::Texture backgroundTex; 

	//Enemy 
	Enemy Enemy1; 
	Enemy Enemy2;  
};