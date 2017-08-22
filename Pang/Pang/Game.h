#pragma once // include guard
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

class Game
{
public:
	static void Start();

private:
	// Member functions
	static bool IsExiting();
	static void GameLoop();

	static void ShowSplashScreen();
	static void ShowMenu();

	// Enum data type for game state
	enum GameState { Uninitialized, ShowingSplash, Paused,
			ShowingMenu, Playing, Exiting };

	// Member variables
	static GameState _gameState;
	static sf::RenderWindow _mainWindow;
};