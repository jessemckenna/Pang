#include "stdafx.h"
#include "GameBall.h"
#include "Game.h"
#include "ServiceLocator.h"

// --- GameBall ---
// Default constructor
GameBall::GameBall() :
	_velocity(300.0f),
	_elapsedTimeSinceStart(0.0f)
{
	Load("images/ball.png");
	assert(IsLoaded());

	GetSprite().setOrigin(15, 15);

	std::srand((unsigned int)std::time(0)); // seed random number generator with current time
	_angle = (float)(std::rand() % 360 + 1); // set _angle to random number, 1 to 360
}

// --- ~GameBall ---
// Destructor
GameBall::~GameBall()
{
}

// --- Update ---
// Move ball; called every frame
void GameBall::Update(float elapsedTime)
{
	// Delay game from starting until 3 seconds have passed
	_elapsedTimeSinceStart += elapsedTime;
	if (_elapsedTimeSinceStart < 3.0f)
		return;

	// Determine base distance to be moved
	float moveAmount = _velocity * elapsedTime;
	
	// Convert base distance to be moved into distances on x and y axes
	float moveByX = LinearVelocityX(_angle) * moveAmount; // adj = cos(t) * hyp
	float moveByY = LinearVelocityY(_angle) * moveAmount; // opp = sin(t) * hyp
	
	// Create pointer player1, set to location of Paddle1 in GameObjectManager;
	// cast to PlayerPaddle* because expression returns a VisibleGameObject*
	PlayerPaddle* player1 = dynamic_cast<PlayerPaddle*>
		(Game::GetGameObjectManager().Get("Paddle1"));
	
	AIPaddle* player2 = dynamic_cast<AIPaddle*>
		(Game::GetGameObjectManager().Get("Paddle2"));

	// If dynamic_cast successful, calculate and execute ball movement
	if (player1 != NULL && player2 != NULL)
	{
		// Create rectangles p1BB and p2BB to represent paddle bounding boxes
		sf::Rect<float> p1BB = player1->GetBoundingRect();
		sf::Rect<float> p2BB = player2->GetBoundingRect();

		// Ball collides with player1 paddle
		if (p1BB.intersects(GetBoundingRect()))
		{
			_angle = 360.0f - (_angle - 180.0f); // ricochet

			if (_angle > 360.0f)
				_angle -= 360.0f; // keep angle between 0 and 360

			moveByY = -moveByY; // change direction
			
			// Make sure ball isn't inside paddle
			if ((GetBoundingRect().top + GetBoundingRect().height) >
				player1->GetBoundingRect().top)
			{
				SetPosition(GetPosition().x,
					player1->GetBoundingRect().top - GetHeight() / 2 - 1);
			}
			
			// Tweak ball angle based on velocity (to add variety to gameplay)
			float playerVelocity = player1->GetVelocity();

			if (playerVelocity < 0)
			{
				// Moving left
				_angle -= 20.0f; // intensify angle

				if (_angle < 0)
					_angle = 360.0f - _angle; // keep angle between 0 and 360
			}
			else if (playerVelocity > 0)
			{
				
				// Moving right
				_angle += 20.0f; // intensify angle

				if (_angle > 360.0f)
					_angle = _angle - 360.0f; // keep angle between 0 and 360
			}

			_velocity += 20.0f; // slightly increase speed on each reflect

			// Play sound for ball hitting paddle
			ServiceLocator::GetAudio()->PlaySound("audio/beeep.wav");
		}
		
		// Ball collides with player2 paddle
		if (p2BB.intersects(GetBoundingRect()))
		{
			_angle = 360.0f - (_angle - 180.0f); // ricochet

			if (_angle > 360.0f)
				_angle -= 360.0f; // keep angle between 0 and 360

			moveByY = -moveByY; // change direction

			// Make sure ball isn't inside paddle
			if ((GetBoundingRect().top) <
				player2->GetBoundingRect().top + player2->GetBoundingRect().height)
			{
				SetPosition(GetPosition().x,
					player2->GetBoundingRect().top + 
					player2->GetBoundingRect().height + GetHeight() / 2 + 1);
			}

			// Tweak ball angle based on velocity (to add variety to gameplay)
			float AIVelocity = player2->GetVelocity();

			if (AIVelocity < 0)
			{
				// Moving left
				_angle -= 20.0f; // intensify angle

				if (_angle < 0)
					_angle = 360.0f - _angle; // keep angle between 0 and 360
			}
			else if (AIVelocity > 0)
			{

				// Moving right
				_angle += 20.0f; // intensify angle

				if (_angle > 360.0f)
					_angle = _angle - 360.0f; // keep angle between 0 and 360
			}

			_velocity += 5.0f; // slightly increase speed on each reflect

			// Play sound for ball hitting paddle
			ServiceLocator::GetAudio()->PlaySound("audio/beeep.wav");
		}

		// Ball collides with sides of screen
		if (GetPosition().x + moveByX <= 0 + GetWidth() / 2
			|| GetPosition().x + GetWidth() / 2 + moveByX >= Game::SCREEN_WIDTH)
		{
			_angle = 360.0f - _angle; // ricochet

			// Tweak angle if ball hits wall straight on to keep the game moving
			if (_angle > 260.0f && _angle < 280.0f)
				_angle += 20.0f;
			if (_angle > 80.0f && _angle < 100.0f)
				_angle += 20.0f;

			moveByX = -moveByX; // change direction

			// Play sound for ball hitting wall
			ServiceLocator::GetAudio()->PlaySound("audio/plop.wav");
		}

		// Ball hits top or bottom of screen: reset position, randomize angle
		if (GetPosition().y - GetHeight() / 2 <= 0 || 
			GetPosition().y + GetHeight() / 2 + moveByY >= Game::SCREEN_HEIGHT)
		{
			GetSprite().setPosition
				(Game::SCREEN_WIDTH / 2, Game::SCREEN_HEIGHT / 2);
			_angle = (float)(std::rand() % 360 + 1); // randomize angle from 1 to 360
			_velocity = 230.0f;
			_elapsedTimeSinceStart = 0.0; // restart timer for 3-second pause

			// Play sound for ball reaching goal
			ServiceLocator::GetAudio()->PlaySound("audio/peeeeeep.wav");
		}
		
		GetSprite().move(moveByX, moveByY);
	}
}

// --- LinearVelocityX ---
// Return cosine of input angle (used to calculate distance on x coordinate)
float GameBall::LinearVelocityX(float angle)
{
	angle -= 90; // to make the angle 0 represent up instead of right
	if (angle < 0)
		angle = 360 + angle; // add 360 to ensure angle remains positive
	
	angle *= (3.1415926f / 180.0f); // convert angle to radians

	return (float)std::cos(angle);
}

// --- LinearVelocityY ---
// Return sine of input angle (used to calculate distance on x coordinate)
float GameBall::LinearVelocityY(float angle)
{
	angle -= 90; // to make the angle 0 represent up instead of right
	if (angle < 0)
		angle = 360 + angle; // add 360 to ensure angle remains positive
	
	angle *= (3.1415926f / 180.0f); // convert angle to radians

	return (float)std::sin(angle);
}