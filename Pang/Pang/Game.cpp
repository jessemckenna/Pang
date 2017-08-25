#include "stdafx.h"
#include "Game.h"
#include "MainMenu.h"
#include "SplashScreen.h"

// --- Start ---
// Open game window, run game loop, close game window
void Game::Start()
{
	// Check to make sure Game::Start() is not called more than once
	// gameState will only be Uninitialized when starting
	if (_gameState != Uninitialized)
		return;

	// Create main window at 1024x768 resolution, 32 bpp color, title "Pang!"
	_mainWindow.create(sf::VideoMode(1024, 768, 32), "Pang!");
	
	// Load player paddle and set its position, then add to _gameObjectManager
	PlayerPaddle* player1 = new PlayerPaddle();
	player1->Load("images/paddle.png");
	player1->SetPosition((1024 / 2) - 45, 700);

	_gameObjectManager.Add("Paddle1", player1);

	// Switch game to Playing state and loop until game is in Exiting state
	_gameState = Game::ShowingSplash;

	while (!IsExiting())
	{
		GameLoop();
	}

	_mainWindow.close();
}

// --- IsExiting ---
// Return true if game state is Exiting
bool Game::IsExiting()
{
	if (_gameState == Game::Exiting)
		return true;
	else
		return false;
}

// --- GameLoop ---
// Execute the game, set game state to Exiting when window closed
void Game::GameLoop()
{
	// Assign current event to currentEvent; multiple events can be in queue
	// at a time
	sf::Event currentEvent;
	_mainWindow.pollEvent(currentEvent);

	// Execute based on game state; only one state can be active at a time
	switch (_gameState)
	{
		case Game::ShowingSplash:
		{
			ShowSplashScreen();
			break;
		}

		case Game::ShowingMenu:
		{
			ShowMenu();
			break;
		}

		case Game::Playing:
		{
			// Clear mainWindow to solid color
			_mainWindow.clear(sf::Color(0, 0, 0));

			// Draw player 1 paddle to mainWindow
			_gameObjectManager.DrawAll(_mainWindow);

			// Display mainWindow on screen
			_mainWindow.display();

			// If user closes window, set game state to Exiting
			if (currentEvent.type == sf::Event::Closed)
				_gameState = Game::Exiting;

			// If user presses escape, return to main menu
			if (currentEvent.type == sf::Event::KeyPressed)
			{
				if (currentEvent.key.code == sf::Keyboard::Escape)
					ShowMenu();
			}

			break;
		}
	}
}

// --- ShowSplashScreen ---
// Call SplashScreen member function Show, set game state to ShowingMenu
void Game::ShowSplashScreen()
{
	SplashScreen splashScreen;
	splashScreen.Show(_mainWindow);
	_gameState = Game::ShowingMenu;
}

// --- ShowMenu ---
// Call MainMenu member function Show, set game state based on return value
void Game::ShowMenu()
{
	MainMenu mainMenu;
	MainMenu::MenuResult result = mainMenu.Show(_mainWindow);

	switch(result)
	{
		case MainMenu::Exit:
			_gameState = Game::Exiting;
			break;
		case MainMenu::Play:
			_gameState = Game::Playing;
			break;
	}
}

// Initialize member variables manually; needed because they are static
Game::GameState Game::_gameState = Uninitialized; // default to Uninitialized
sf::RenderWindow Game::_mainWindow;
GameObjectManager Game::_gameObjectManager;