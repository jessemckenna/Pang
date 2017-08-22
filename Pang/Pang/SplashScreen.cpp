#include "stdafx.h"
#include "SplashScreen.h"

void SplashScreen::Show(sf::RenderWindow& renderWindow)
{
	sf::Texture texture;
	
	// Load splash screen texture from disk, return if not found
	if (texture.loadFromFile("Images/splashscreen.png") != true)
		return;

	// Create a sprite from texture
	// Textures are essentially assets and are not displayed;
	// sprites are what is actually displayed onscreen
	sf::Sprite sprite(texture);

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