#pragma once
#include "Framework/GameObject.h"
class Platform : public GameObject
{
	sf::Texture platformerTex; 
	sf::View view; 

public:

	Platform(); 
	~Platform();

	void handleInput(float dt); 


};

