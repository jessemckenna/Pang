#include "stdafx.h"
#include "PlayerPaddle.h"
#include "Game.h"

// --- PlayerPaddle ---
// Default constructor; set _velocity to 0 and _maxVelocity to 600.0,
// load paddle texture, set sprite origin to center of texture
PlayerPaddle::PlayerPaddle() :
	_velocity(0),
	_maxVelocity(600.0f)
{
	Load("images/paddle.png");
	assert(IsLoaded()); // check IsLoaded() is true, else terminate program

	// Set origin (center) of sprite returned by GetSprite to its size / 2,
	// i.e. the sprite texture's center, instead of the default top-left corner
	GetSprite().setOrigin(GetSprite().getLocalBounds().width / 2,
		GetSprite().getLocalBounds().height / 2);
}

// --- ~PlayerPaddle ---
// Destructor
PlayerPaddle::~PlayerPaddle()
{
}

// --- Update ---
// Get user input and move paddle accordingly; called every frame
void PlayerPaddle::Update(float elapsedTime) // override base class Update
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		_velocity -= 3.0f; // move left
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		_velocity += 3.0f; // move right
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		_velocity = 0.0f; // stop movement
	}
	else if (_velocity < 0)
	{
		_velocity += 0.4f; // decay speed while no button is pressed, moving left
	}
	else if (_velocity > 0)
	{
		_velocity -= 0.4f; // decay speed while no button is pressed, moving right
	}

	// Limit velocity to maxVelocity
	if (_velocity > _maxVelocity)
		_velocity = _maxVelocity;

	if (_velocity < -_maxVelocity)
		_velocity = -_maxVelocity;

	// Create Vector2f "pos" and set to the position of the current object
	// (signified by "this") by calling VisibleGameObject function GetPosition
	sf::Vector2f pos = this->GetPosition();

	// If paddle reaches edge of screen
	if ((pos.x < GetSprite().getLocalBounds().width / 2
		&& _velocity < 0) ||
		(pos.x > (Game::SCREEN_WIDTH - GetSprite().getLocalBounds().width / 2)
		&& _velocity > 0))
	{
		// Bounce by current velocity in other direction
		_velocity = -_velocity;
	}

	// Move sprite based on velocity as determined above; elapsedTime
	// represents the time since the last frame was drawn
	GetSprite().move(_velocity * elapsedTime, 0);
}

// --- Draw ---
// Draw paddle to current render window
void PlayerPaddle::Draw(sf::RenderWindow &rw)
{
	VisibleGameObject::Draw(rw);
}

// --- GetVelocity ---
float PlayerPaddle::GetVelocity() const
{
	return _velocity;
}