#include "stdafx.h"
#include "Game.h"

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
	
	// Switch game to Playing state and loop until game is in Exiting state
	_gameState = Game::Playing;

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
	sf::Event currentEvent;

	// If an event exists, return true and assign to currentEvent;
	// multiple events can be in queue at a time, so will iterate over all
	// available events until there are none left to process
	while (_mainWindow.pollEvent(currentEvent))
	{
		// Execute based on game state; only one state can be active at a time
		switch (_gameState)
		{
			case Game::Playing:
			{
				// Clear mainWindow to red color
				_mainWindow.clear(sf::Color(255, 0, 0));
				
				// Display mainWindow on screen
				_mainWindow.display();

				// If user closes window, set game state to Exiting
				if (currentEvent.type == sf::Event::Closed)
					_gameState = Game::Exiting;
				
				break;
			}
		}
	}
}

// Initialize member variables manually; needed because they are static
Game::GameState Game::_gameState = Uninitialized; // default state Uninitialized
sf::RenderWindow Game::_mainWindow;