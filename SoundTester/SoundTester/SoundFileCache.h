#pragma once

#include "stdafx.h"
#include "SFML/Audio.hpp"

class SoundFileCache
{
public:
	// Constructor and destructor
	SoundFileCache();
	~SoundFileCache();

	// Get methods for sound and music; GetSound returns a sf::Sound object
	// because Sound objects are fairly resource-light
	sf::Sound GetSound(std::string soundName) const;
	sf::Music* GetSong(std::string songName) const;

private:
	// SoundBuffer and Music are cached because they are resource-intensive
	static std::map<std::string, sf::SoundBuffer*> _sounds; // soundbuff. cache
	static std::map<std::string, sf::Music*> _music; // music cache

	// Functor to be used by destructor
	// A template is used to eliminate the need for multiple redundant methods
	template <typename T>
	struct Deallocator // will work for both SoundBuffer* and Music* as type T
	{
		void operator()(const std::pair<std::string, T>& p)
		{
			delete p.second;
		}
	};
};

// Exception object derived from runtime_error
class SoundNotFoundException : public std::runtime_error
{
public:
	// Constructor
	SoundNotFoundException(std::string const& msg):
		std::runtime_error(msg) // pass string "msg" to base class constructor
	{}
};