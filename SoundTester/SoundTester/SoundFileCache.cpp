#include "stdafx.h"
#include "SoundFileCache.h"
#include <iostream>

// --- SoundFileCache ---
// Default constructor
SoundFileCache::SoundFileCache()
{
}

// --- ~SoundFileCache ---
// Destructor
SoundFileCache::~SoundFileCache()
{
	std::for_each(_sounds.begin(), _sounds.end(), 
		Deallocator<sf::SoundBuffer*>()); // deallocate _sounds cache
	
	std::for_each(_music.begin(), _music.end(),
		Deallocator<sf::Music*>()); // deallocate _music cache
}

// --- GetSound ---
// Load sound indicated by soundName into _sounds cache and return it
sf::Sound SoundFileCache::GetSound(std::string soundName) const
{
	std::cout << "Entering GetSound() function" << std::endl;
	
	// Check to see if soundName has already been loaded
	std::map<std::string, sf::SoundBuffer*>::iterator itr =
		_sounds.find(soundName);

	std::cout << "Done checking!" << std::endl;

	// If not already loaded
	if (itr == _sounds.end())
	{
		std::cout << "File " << soundName << " is not already loaded; loading from file..." << std::endl;

		// Create new SoundBuffer* and load soundName sound from file
		sf::SoundBuffer* soundBuffer = new sf::SoundBuffer();
		if (!soundBuffer->loadFromFile(soundName))
		{
			// Throw an exception if unable to load soundName from file
			delete soundBuffer;
			throw SoundNotFoundException(
				soundName + " not found in call to SoundFileCache::GetSound");

			std::cout << "Unable to load " << soundName << std::endl;
		}

		// Insert loaded SoundBuffer into _sounds cache
		std::cout << "Inserting into _sounds cache..." << std::endl;
		
		// map.insert returns a pair whose first element is an iterator
		// pointing to the new element we just inserted; here we assign .first
		// to itr, so itr points to the new element in the map
		itr = _sounds.insert(std::pair<std::string, sf::SoundBuffer*>
			(soundName, soundBuffer)).first;
	}

	// Return a Sound object whose buffer is set to cached SoundBuffer
	sf::Sound sound;
	sound.setBuffer(*itr->second);

	std::cout << "Returning from GetSound." << std::endl;

	return sound;

	// Return the sound that's already in the cache
}

// --- GetSong ---
// Return a pointer to the music file indicated by songName
sf::Music* SoundFileCache::GetSong(std::string songName) const
{
	// Check to see if songName has already been loaded
	std::map<std::string, sf::Music*>::iterator itr = _music.find(songName);

	// If not already loaded
	if (itr == _music.end())
	{
		// Create new Music* and load songName from file
		sf::Music* song = new sf::Music();
		if (!song->openFromFile(songName))
		{
			// Throw an exception if unable to load songName from file
			delete song;
			throw SoundNotFoundException(
				songName + " not found in call to SoundFileCache::GetSong");
		}
		else
		{
			// Insert loaded Music into _music cache
			std::map<std::string, sf::Music*>::iterator res =
				_music.insert(std::pair<std::string, sf::Music*>
				(songName, song)).first;
			
			// Return a pointer to loaded Music object
			return res->second;
		}
	}
	else
	{
		return itr->second;
	}

	throw SoundNotFoundException(
		songName + "was not found in call to SoundFileCache::GetSong");
}

std::map<std::string, sf::SoundBuffer*> SoundFileCache::_sounds;
std::map<std::string, sf::Music*> SoundFileCache::_music;