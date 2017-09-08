#include "stdafx.h"
#include "MainMenu.h"
#include "ServiceLocator.h"

// --- Show ---
// Create menu buttons, display main menu, and call GetMenuResponse for choice
MainMenu::MenuResult MainMenu::Show(sf::RenderWindow& window)
{
	// Load menu image from file and assign to sprite
	sf::Texture texture;
	texture.loadFromFile("Images/mainmenu.png");
	sf::Sprite sprite(texture);

	// TODO: Set up clickable regions

	// Play menu item coordinates
	MenuItem playButton;
	playButton.rect.top = 145;
	playButton.rect.left = 0;
	playButton.rect.height = 235;
	playButton.rect.width = 1023;
	playButton.action = Play;

	// Exit menu item coordinates
	MenuItem exitButton;
	exitButton.rect.top = 383;
	exitButton.rect.left = 0;
	exitButton.rect.height = 177;
	exitButton.rect.width = 1023;
	exitButton.action = Exit;

	// Add play and exit buttons to list of main menu items
	_menuItems.push_back(playButton);
	_menuItems.push_back(exitButton);

	// Display main menu sprite to screen
	window.draw(sprite);
	window.display();

	return GetMenuResponse(window);
}

// --- GetMenuResponse ---
// Call HandleClick if mouse is clicked, or return Exit if window is closed
MainMenu::MenuResult MainMenu::GetMenuResponse(sf::RenderWindow& window)
{
	sf::Event menuEvent;

	while (true)
	{
		while (window.pollEvent(menuEvent))
		{
			if (menuEvent.type == sf::Event::MouseButtonPressed)
			{
				return HandleClick(menuEvent.mouseButton.x,
					menuEvent.mouseButton.y);

				// Stop playing menu music
				if (ServiceLocator::GetAudio()->IsSongPlaying())
					ServiceLocator::GetAudio()->StopAllSounds();
			}
			if (menuEvent.type == sf::Event::Closed)
			{
				return Exit;
			}
		}
	}
}

// --- HandleClick ---
// Accept coordinates of click and determine whether any button was clicked;
// return the appropriate menu action based on what was clicked
MainMenu::MenuResult MainMenu::HandleClick(int x, int y)
{
	std::list<MenuItem>::iterator it;

	// Iterate through _menuItems list
	for (it = _menuItems.begin(); it != _menuItems.end(); it++)
	{
		// Set int-type Rect menuItemRect to... ???
		sf::Rect<int> menuItemRect = (*it).rect;

		// If click coordinates are within bounds of menu item
		if (menuItemRect.left < x
			&& menuItemRect.top < y
			&& menuItemRect.left + menuItemRect.width > x
			&& menuItemRect.top + menuItemRect.height > y)
		{
			// Return action of current item in _menuItems
			return (*it).action;
		}
	}
	
	// Return Nothing if click coordinates do not match any button
	return Nothing;
}