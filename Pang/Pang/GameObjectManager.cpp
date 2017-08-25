#include "stdafx.h"
#include "GameObjectManager.h"

// --- GameObjectManager ---
// Default constructor
GameObjectManager::GameObjectManager()
{
}

// --- ~GameObjectManager ---
// Destructor; call struct GameObjectDeallocator() for all pairs in the map
GameObjectManager::~GameObjectManager()
{
	// The method for_each() takes two iterators representing start and end
	// location, followed by a single-parameter function to be called on
	// each iteration
	std::for_each(_gameObjects.begin(), _gameObjects.end(), 
		GameObjectDeallocator());
}

// --- Add ---
// Add "name" and "gameObject" to map _gameObjects as a pair
void GameObjectManager::Add(std::string name, VisibleGameObject* gameObject)
{
	// Syntax: .insert(std::pair<datatype1, datatype2>(variable1, variable2));
	_gameObjects.insert(std::pair<std::string, VisibleGameObject*>
		(name, gameObject));
}

// --- Remove ---
// Delete the VisibleGameObject* value (in a map) associated with the string
// key provided as argument, and remove the pair from the map
void GameObjectManager::Remove(std::string name)
{
	// Set constant iterator "results" to the location of the value associated
	// with key "name"
	std::map<std::string, VisibleGameObject*>::iterator results
		= _gameObjects.find(name);
	
	// If results successfully finds the pair associated with the given key,
	// delete the value associated with the key in memory and erase the pair
	// from the map
	if (results != _gameObjects.end())
	{
		delete results->second;
		_gameObjects.erase(results);
	}
}

// --- GetObjectCount ---
// Return size of (i.e. number of items contained in) map _gameObjects
int GameObjectManager::GetObjectCount() const
{
	return _gameObjects.size();
}

// --- Get ---
// Return the VisibleGameObject* value (in a map) associated with the string
// key provided as argument
VisibleGameObject* GameObjectManager::Get(std::string name) const
{
	// Set constant iterator "results" to the location of the value associated
	// with key "name"
	std::map<std::string, VisibleGameObject*>::const_iterator results
		= _gameObjects.find(name);

	// If iterator is at the end of the map, i.e. does not point to any valid
	// value, return NULL
	if (results == _gameObjects.end())
		return NULL;

	// Iterator "results" points to a std::pair, so we can access the first
	// item with results->first and the second item with results->second;
	// since we want to return the VisibleGameObject*, we return second here
	return results->second;
}

// --- DrawAll ---
// Loop through all items in map _gameObjects and call VisibleGameObject's
// Draw method for each
void GameObjectManager::DrawAll(sf::RenderWindow& renderWindow)
{
	// Create constant iterator "itr" and set to start of map
	std::map<std::string, VisibleGameObject*>::const_iterator itr
		= _gameObjects.begin();

	// Iterate through map until reaching _gameObjects.end()
	while (itr != _gameObjects.end())
	{
		// Draw the VisibleGameObject* value of each pair to renderWindow
		// using the Draw method from the VisibleGameObject class
		itr->second->Draw(renderWindow);
		itr++;
	}
}