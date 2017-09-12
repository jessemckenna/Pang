#include "stdafx.h"
#include "AIPaddle.h"
#include "Game.h"
#include "GameBall.h"

// --- AIPaddle ---
// Default constructor
AIPaddle::AIPaddle() : 
	_velocity(0.0f), 
	_maxVelocity(400.0f)
{
	Load("images/paddle.png");
	assert(IsLoaded()); // check IsLoaded() is true, else terminate program

	// Set origin (center) of sprite returned by GetSprite to its size / 2,
	// i.e. the sprite texture's center, instead of the default top-left corner
	GetSprite().setOrigin(GetSprite().getLocalBounds().width / 2,
		GetSprite().getLocalBounds().height / 2);
}

// --- ~AIPaddle ---
// Destructor
AIPaddle::~AIPaddle()
{
}

// --- Update ---
// Move paddle according to ball position when ball is near; called every frame
void AIPaddle::Update(float elapsedTime)
{
	// Get ball position
	const GameBall* gameBall = static_cast<GameBall*>
		(Game::GetGameObjectManager().Get("Ball"));
	
	sf::Vector2f ballPosition = gameBall->GetPosition();

	// Paddle AI based on ball position
	// Note: paddle only moves when ball is on its side, to make game easier
	if (GetPosition().x + 20 < ballPosition.x 
		&& ballPosition.y < Game::SCREEN_HEIGHT / 2) // over 20 px left of ball
		_velocity += 15.0f;
	else if (GetPosition().x - 20 > ballPosition.x
		&& ballPosition.y < Game::SCREEN_HEIGHT / 2) // over 20 px right of ball
		_velocity -= 15.0f;
	else
		_velocity = 0.0f;

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
		(pos.x >(Game::SCREEN_WIDTH - GetSprite().getLocalBounds().width / 2)
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
void AIPaddle::Draw(sf::RenderWindow &rw)
{
	VisibleGameObject::Draw(rw);
}

// --- GetVelocity ---
float AIPaddle::GetVelocity() const
{
	return _velocity;
}