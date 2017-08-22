#include "stdafx.h"
#include "SplashScreen.h"

void SplashScreen::Show(sf::RenderWindow& renderWindow)
{
	sf::Image image;
	
	// Load splash screen image from disk, return if not found
	if (image.loadFromFile("images/SplashScreen.png") != true)
		return;

	// Create a sprite from image
	// Images are essentially assets and are not displayed;
	// sprites are what is actually displayed onscreen
	sf::Sprite sprite(image);

	renderWindow.draw(sprite); // draw sprite to renderWindow
	renderWindow.display(); // display renderWindow on screen

	sf::Event event;

	while (true)
	{
		while (renderWindow.pollEvent(event))
		{
			// Close splash screen if any key or mouse button is pressed
			if (event.type == sf::Event::EventType::KeyPressed
				|| event.type == sf::Event::EventType::MouseButtonPressed
				|| event.type == sf::Event::EventType::Closed)
			{
				return;
			}
		}
	}
}