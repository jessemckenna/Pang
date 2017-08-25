#include "stdafx.h"
#include "VisibleGameObject.h"

// --- VisibleGameObject ---
// Default constructor
VisibleGameObject::VisibleGameObject()
{
	_isLoaded = false;
}

// --- ~VisibleGameObject ---
// Destructor
VisibleGameObject::~VisibleGameObject()
{
}

// --- Load ---
// Load texture based on filename; if loaded correctly, set sprite to texture
void VisibleGameObject::Load(std::string filename)
{
	// Check whether filename loads correctly, set _isLoaded to false if not
	if (_texture.loadFromFile(filename) == false)
	{
		_filename = "";
		_isLoaded = false;
	}
	
	// If loads correctly, assign filename and sprite, set _isLoaded to true
	else
	{
		_filename = filename;
		_sprite.setTexture(_texture);
		_isLoaded = true;
	}
}

// --- Draw ---
// If image has been loaded, draw sprite to render window
void VisibleGameObject::Draw(sf::RenderWindow& window)
{
	if (_isLoaded)
	{
		window.draw(_sprite);
	}
}

// --- SetPosition ---
// If image has been loaded, set sprite position based on x and y parameters
void VisibleGameObject::SetPosition(float x, float y)
{
	if (_isLoaded)
	{
		_sprite.setPosition(x, y);
	}
}