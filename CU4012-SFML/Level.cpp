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


	if (!font.loadFromFile("font/arial.ttf")) {
		std::cout << "error loading font" << std::endl;
	};

	TileEditorText.setFont(font);
	TileEditorText.setCharacterSize(24);
	TileEditorText.setFillColor(sf::Color::Red);

	TileEditorText.setString(" Press E to edit tiles");
	TileEditorText.setPosition(0, 0);

	tileManager.setInput(input);
	tileManager.setWindow(window);
	tileManager.setWorld(world);
	tileManager.setCustomTexture("gfx/Platform.png");
	// initialise game objects
	Player.setPosition(100, 100);
	Player.setInput(input);


	// Background 

	for (size_t i = 0; i < 3; i++)
	{
		bg[i].setScale(3, 3);
		bg[i].setPosition(bg[i].getSize().x*i, 0);
	}
	e1.setCustomTexture("gfx/Enemy.png"); 

	world->AddGameObject(Player);
	world->AddGameObject(e1);
	world->AddGameObject(ground);

	if (!tileManager.loadTiles())
	{
		std::cout << "Tiles not found\n";
	}
	else
	{
		std::cout << "Tiles loaded\n";
	}
	sf::Vector2f viewSize = sf::Vector2f(window->getSize().x, window->getSize().y);
	view.setSize(viewSize.x, viewSize.y);
	view.setCenter(viewSize.x / 2, viewSize.y / 2);
}

Level::~Level()
{

}

// handle user input
void Level::handleInput(float dt)
{

	if (input->isKeyDown(sf::Keyboard::Escape))
	{
		exit(0);
	}

	// Check if 'E' is pressed to toggle editing mode
	if (input->isKeyDown(sf::Keyboard::E))
	{
		// First, if we're in edit mode, we save the tiles
		if (editMode)
		{
			std::cout << "Exiting edit mode. Saving tiles...\n";
			tileManager.saveTiles(tileManager.getTiles(), tileManager.getFilePath());
		}
		// Then toggle the edit mode
		editMode = !editMode;
		input->setKeyUp(sf::Keyboard::E); // Acknowledge the key press
	}

	if (editMode)
	{
		// Handle moving the view or other edit-mode-specific logic
		moveView(dt);
		//tileManager.handleInput(dt); // tileManager might have its own logic for when editing is true
	}
	else
	{
		//To make the player move. 
		Player.handleInput(dt);
	}

}

// Update game objects
void Level::update(float dt)
{
	sf::Vector2f viewSize = sf::Vector2f(window->getSize().x, window->getSize().y);

	if (Player.CollisionWithTag("Enemy"))
	{
		if (Player.getCollisionDirection() == "Down")
		{
			std::cout << "Player hit enemy from above\n";
			e1.setAlive(false);
			world->RemoveGameObject(e1);
		}

	}
	if (Player.getPosition().y > 1500)
	{
		Reset();
		gameState->setCurrentState(State::GAMEOVER);
	}
	if (e1.CollisionWithTag("Wall"))
	{
		e1.setVelocity(-e1.getVelocity().x, e1.getVelocity().y);
	}
	if (Player.getPosition().x > 3200)
	{
		Reset();
		gameState->setCurrentState(State::WINNER);
	}
	if (e1.CollisionWithTag("Wall"))
	{
		e1.setVelocity(-e1.getVelocity().x, e1.getVelocity().y);
	}

	if (editMode)
	{
		TileEditorText.setPosition(view.getCenter().x - viewSize.x / 2, view.getCenter().y - viewSize.y / 2);
		TileEditorText.setString("Editing mode\nLeft Mouse Button to place tile\nPress B to set collider as a wall (allows bouncing) \nPress E to exit and Save");
		tileManager.handleInput(dt);
		tileManager.update(dt);
	}
	else
	{
		TileEditorText.setString("Press E to edit tiles");

		view.setCenter(view.getCenter().x, 360);

		sf::Vector2f playerPos = Player.getPosition();
		float newX = std::max(playerPos.x, view.getSize().x / 2.0f);
		view.setCenter(newX, playerPos.y);
		window->setView(view);
	}

}

// Render level
void Level::render()
{
	beginDraw();

	//Background rendered 

	for (size_t i = 0; i < 3; i++)
	{
		window->draw(bg[i]);
	}


	window->draw(Player);
	window->draw(Player.getDebugCollisionBox());


	if (e1.isAlive())
	{
		window->draw(e1);
		window->draw(e1.getDebugCollisionBox());
	}


	window->draw(ground.getDebugCollisionBox());

	window->draw(platform);
	tileManager.render();
	window->draw(TileEditorText);

	

	endDraw();
}
void Level::moveView(float dt)
{
	float speed = 500.f;
	if (input->isKeyDown(sf::Keyboard::W))
	{
		view.move(0, -speed * dt);
	}
	if (input->isKeyDown(sf::Keyboard::S))
	{
		view.move(0, speed * dt);
	}
	if (input->isKeyDown(sf::Keyboard::A))
	{
		view.move(-speed * dt, 0);
	}
	if (input->isKeyDown(sf::Keyboard::D))
	{
		view.move(speed * dt, 0);
	}

	window->setView(view);

}

void Level::Reset()
{
	Player.setPosition(100, 50);
	sf::Vector2f viewSize = sf::Vector2f(window->getSize().x, window->getSize().y);
	view.setCenter(viewSize);
	window->setView(view);


	e1.setPosition(500, 100);
	e1.setVelocity(sf::Vector2f(100, 100)); 
	e1.setAlive(true); // Set the enemy to alive state

	
	// Reset view to the center of the window
	adjustViewToWindowSize(window->getSize().x, window->getSize().y);

}

void Level::adjustViewToWindowSize(unsigned int width, unsigned int height)
{
	sf::FloatRect visibleArea(0, 0, static_cast<float>(width), static_cast<float>(height));
	view.setSize(static_cast<float>(width), static_cast<float>(height));
	view.setCenter(static_cast<float>(width) / 2, static_cast<float>(height) / 2);
}