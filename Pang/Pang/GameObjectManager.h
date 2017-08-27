#pragma once
#include "VisibleGameObject.h"

class GameObjectManager
{
public:
	// Member functions
	GameObjectManager(); // default constructor
	~GameObjectManager(); // destructor

	void Add(std::string name, VisibleGameObject* gameObject);
	void Remove(std::string name);
	
	// Member functions ending in const cannot change any member variables
	int GetObjectCount() const;
	static sf::Clock& GetClock();
	VisibleGameObject* Get(std::string name) const;
	
	void DrawAll(sf::RenderWindow& renderWindow);
	void UpdateAll();

private:
	// Member variables
	
	// Identifier is a string name, value is a pointer-to-VisibleGameObject
	std::map<std::string, VisibleGameObject*> _gameObjects;

	// GameObjectDeallocator is a functor, an object that can be called like
	// a function
	struct GameObjectDeallocator
	{
		// Overload the () operator to handle the type std::pair by reference,
		// where the pair consists of <std::string, VisibleGameObject*>
		void operator() (const std::pair<std::string, VisibleGameObject*>& p)
			const
		{
			// Delete the second item in the pair, i.e. the VisibleGameObject*
			delete p.second;
		}
	};

	static sf::Clock _clock;
};