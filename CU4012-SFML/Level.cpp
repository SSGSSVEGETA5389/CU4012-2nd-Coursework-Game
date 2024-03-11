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

	

	// Background 

	backgroundTex.loadFromFile("gfx/Background.png"); 

	bg.setTexture(&backgroundTex); 
	bg.setSize(sf::Vector2f(11038, 675)); 
	bg.setInput(input); 
	bg.setWindow(window); 


	//Enemy 
	Enemy1.setPosition(500, 100);


	world->AddGameObject(Player);
	world->AddGameObject(Enemy1);
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
	if(p1.CollisionWithTag("Enemy"))
	{ 
		
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


	window->draw(Enemy1);
	window->draw(Enemy1.getDebugCollisionBox());


	window->draw(ground.getDebugCollisionBox());

	endDraw();
}
