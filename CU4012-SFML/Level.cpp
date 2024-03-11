#include "Level.h"
#include "Player.h"
#include "Squares.h"
#include "Background.h" 
#include "Enemy.h"


Level::Level(sf::RenderWindow* hwnd, Input* in, GameState* gs, World* w)
{


	window = hwnd;
	input = in;
	gameState = gs;
	world = w;
	// initialise game objects
	Player.setPosition(100, 100);
	Player.setInput(input);

	bg.setScale(3, 3);

	// Background 
	bg.setInput(input); 
	bg.setWindow(window); 



	world->AddGameObject(Player);
	world->AddGameObject(e1);
	world->AddGameObject(ground);
}

Level::~Level()
{

}

// handle user input
void Level::handleInput(float dt)
{

	//To make the player move. 
	Player.handleInput(dt);
	//To make background move.
	bg.handleInput(dt); 

	if (input->isKeyDown(sf::Keyboard::Escape))
	{
		exit(0);
	}
}

// Update game objects
void Level::update(float dt)
{
	if (Player.CollisionWithTag("Enemy"))
	{
		//std::cout << "Player is colliding with the Enemy\n";
	}

}

// Render level
void Level::render()
{
	beginDraw();

	//Background rendered 
	window->draw(bg);



	window->draw(Player);
	window->draw(Player.getDebugCollisionBox());


	window->draw(e1);
	window->draw(e1.getDebugCollisionBox());


	window->draw(ground.getDebugCollisionBox());



	endDraw();
}
