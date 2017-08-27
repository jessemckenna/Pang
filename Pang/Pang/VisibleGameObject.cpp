#include "stdafx.h"
#include "VisibleGameObject.h"

// --- VisibleGameObject ---
// Default constructor; sets _isLoaded to false
// This syntax is slightly more efficient than "_isLoaded = false;" in the body
VisibleGameObject::VisibleGameObject() : _isLoaded(false)
{
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

// --- Update ---
// Get user input; method to be implemented in derived classes
void VisibleGameObject::Update(float elapsedTime)
{
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

// --- GetPosition ---
// Get position of sprite as Vector2f (shorthand for templated form
// Vector2<float>, an SFML class representing a vector with coordinates x and y
sf::Vector2f VisibleGameObject::GetPosition() const
{
	if (_isLoaded)
	{
		// Call SFML sprite method getPosition, which returns a Vector2f
		return _sprite.getPosition();
	}

	// Return a temporary blank Vector2f by calling constructor in return
	return sf::Vector2f();
}

// --- IsLoaded ---
// Return true if sprite is loaded
bool VisibleGameObject::IsLoaded() const
{
	return _isLoaded;
}

// --- GetSprite ---
// Method for derived classes to get access to inherited private _sprite member
sf::Sprite& VisibleGameObject::GetSprite()
{
	return _sprite;
}