#pragma once
#include "VisibleGameObject.h"

// Use of keyword public means that only the public members of
// VisibleGameObject will be derived by PlayerPaddle; the derived class
// still contains the private data members, but has no direct access to them
class PlayerPaddle : public VisibleGameObject
{
public:
	PlayerPaddle(); // default constructor
	~PlayerPaddle(); // destructor

	void Update(float elapsedTime); // override base class Update method
	void Draw(sf::RenderWindow &rw);

	float GetVelocity() const;

private:
	float _velocity; // -- left ++ right
	float _maxVelocity;
};