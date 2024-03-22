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
	tileManager.ShowDebugCollisionBox(true);
	tileManager.setPlatformTexture("gfx/Platform.png");
	tileManager.setCollectableTexture("gfx/Item.png");

	//Collectables Collected Text
	CollectablesCollectedText.setFont(font);
	CollectablesCollectedText.setCharacterSize(24);
	CollectablesCollectedText.setFillColor(sf::Color::Green);
	CollectablesCollectedText.setPosition(window->getSize().x, 0);
	CollectablesCollectedText.setString("Collected: ");


	// initialise game objects
	Player.setPosition(100, 100);
	Player.setInput(input);




	// Background 

	for (size_t i = 0; i < 3; i++)
	{
		bg[i].setScale(3, 3);
		bg[i].setPosition(bg[i].getSize().x * i, 0);
	}
	e1.setCustomTexture("gfx/Enemy.png");

	// Write a for loop for setting the enemyArray variables texture 
	for (size_t i = 0; i < 4; i++)
	{
		enemyArray[i].setCustomTexture("gfx/Enemy.png");
		enemyArray[i].setAlive(true);
		world->AddGameObject(enemyArray[i]);

	}

	//// Adds the other enemy 

	//Enemy one 
	enemyArray[0].setPosition(100, 70);
	enemyArray[0].setVelocity(100, 0);

	//Enemy two
	enemyArray[1].setPosition(400, 400);
	enemyArray[1].setVelocity(100, 0);

	//Enemy three 
	enemyArray[2].setPosition(800, 500);
	enemyArray[2].setVelocity(100, 0);

	//Enemy four
	enemyArray[3].setPosition(850, 600);
	enemyArray[3].setVelocity(100, 0);




	//Add all the gameobjects into the world.

	world->AddGameObject(Player);
	//world->AddGameObject(e1);
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
	//if (input->isKeyDown(sf::Keyboard::E))
	//{
	//	// First, if we're in edit mode, we save the tiles
	//	if (editMode)
	//	{
	//		std::cout << "Exiting edit mode. Saving tiles...\n";
	//		tileManager.saveTiles(tileManager.getTiles(), tileManager.getFilePath());
	//	}
	//	// Then toggle the edit mode
	//	editMode = !editMode;
	//	input->setKeyUp(sf::Keyboard::E); // Acknowledge the key press
	//}

	//if (editMode)
	//{
	//	// Handle moving the view or other edit-mode-specific logic
	//	moveView(dt);
	//	//tileManager.handleInput(dt); // tileManager might have its own logic for when editing is true
	//}
	//else
	{
		//To make the player move. 
		Player.handleInput(dt);
	}

}

// Update game objects
void Level::update(float dt)
{
	sf::Vector2f viewSize = sf::Vector2f(window->getSize().x, window->getSize().y);

	CollectablesCollectedText.setPosition(view.getCenter().x - viewSize.x / 14, view.getCenter().y - viewSize.y / 2);


	for (int i = 0; i < 4; i++)
	{
		if (enemyArray[i].CollisionWithTag("Player"))
		{
			std::cout << enemyArray[i].getCollisionDirection() << std::endl;
			if (enemyArray[i].getCollisionDirection() == "Up")
			{
				enemyArray[i].setAlive(false);
				world->RemoveGameObject(enemyArray[i]);
			}
			else
			{
				std::cout << "Player hit enemy from the side\n";
				Player.setPosition(100, 100);
			}
		}
		else if (enemyArray[i].CollisionWithTag("Wall"))
		{
			enemyArray[i].setVelocity(-enemyArray[i].getVelocity().x, enemyArray[i].getVelocity().y);
		}
	}
	if (Player.CollisionWithTag("Collectable"))
	{
		// Player is Colliding with Collectable
		Player.AddCollectable(1); // Increment Collectable count
		tileManager.RemoveCollectable(); // Remove the collectable

		// Update the CollectablesCollectedText to display the new number of rings collected
		int collectableCount = Player.getCollectables(); // Assume p1 is the player object and has the getCollectablesCount method
		CollectablesCollectedText.setString("Collected: " + std::to_string(collectableCount));
	}

	//When the player goes over a certain position on the Y axis (Downwards), this should trigger a game over screen.
	if (Player.getPosition().y > 1500)
	{
		Reset();
		gameState->setCurrentState(State::GAMEOVER);
	}

	//When the player goes over a certain position on the X axis (Right), this should trigger the winning screen.

	if (Player.getPosition().x > 3200)
	{
		Reset();
		gameState->setCurrentState(State::WINNER);
	}
	


	if (editMode)
	{
		TileEditorText.setPosition(view.getCenter().x - viewSize.x / 2, view.getCenter().y - viewSize.y / 2);
		TileEditorText.setString("Editing mode\nLeft Mouse Button to place tile\nPress B to set collider as a wall (allows bouncing)\n Press C to make it a collectable\n Press P to make it a Platform\nPress E to exit and Save");
		tileManager.handleInput(dt);
		tileManager.update(dt);
	}
	else
	{
		TileEditorText.setString("Press E to edit tiles");

		view.setCenter(view.getCenter().x, view.getCenter().y);

		sf::Vector2f playerPos = Player.getPosition();
		float newX = std::max(playerPos.x, view.getSize().x / 2.0f);
		float newY = std::max(playerPos.y, view.getSize().y / 2.0f);

		newY = std::min(newY, 1000.0f); // This clamps the newY to not exceed 1000

		view.setCenter(newX, newY);
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
	//window->draw(Player.getDebugCollisionBox());

	for (size_t i = 0; i < 4; i++)
	{
		if (enemyArray[i].isAlive())
		{
			window->draw(enemyArray[i]);
		}
	}
	window->draw(ground.getDebugCollisionBox());

	window->draw(platform);
	tileManager.render(editMode);

	if (editMode) window->draw(TileEditorText);
	window->draw(CollectablesCollectedText);




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

//This resets the whole level once the restart button has been pressed on either Game over state, or winning screen state.

void Level::Reset()
{
	Player.setPosition(100, 50);
	sf::Vector2f viewSize = sf::Vector2f(window->getSize().x, window->getSize().y);
	view.setCenter(viewSize);
	window->setView(view);


	e1.setPosition(200, 70);
	e1.setVelocity(sf::Vector2f(100, 100));
	e1.setAlive(true); // Set the enemy to alive state
	world->AddGameObject(e1); // Add the enemy back to the world

	// Reset view to the center of the window
	adjustViewToWindowSize(window->getSize().x, window->getSize().y);
}

void Level::adjustViewToWindowSize(unsigned int width, unsigned int height)
{
	sf::FloatRect visibleArea(0, 0, static_cast<float>(width), static_cast<float>(height));
	view.setSize(static_cast<float>(width), static_cast<float>(height));
	view.setCenter(static_cast<float>(width) / 2, static_cast<float>(height) / 2);
}