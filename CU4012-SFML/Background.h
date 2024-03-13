#pragma once
#include "Framework/GameObject.h"
class Background : public GameObject
{
	sf::Texture backgroundTex;
	sf::View view;
public:

	Background();
	~Background();
	void handleInput(float dt); 

};

