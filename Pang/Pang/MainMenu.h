#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include <list>

class MainMenu
{
public:
	// Member variables
	enum MenuResult { Nothing, Exit, Play };

	struct MenuItem // struct to represent individual items in the menu
	{
		// rect holds the dimensions of a MenuItem
		// sf::Rect is a templated class, declared here using type int;
		// a templated class can accept a variety of data types
		sf::Rect<int> rect;
		
		// action holds the value to return after a MenuItem is clicked
		MenuResult action;
	};

	// Member functions
	MenuResult Show(sf::RenderWindow& window);

private:
	// Member variables
	std::list<MenuItem> _menuItems; // list of MenuItem items in main menu

	// Member functions
	MenuResult GetMenuResponse(sf::RenderWindow& window);
	MenuResult HandleClick(int x, int y);
};