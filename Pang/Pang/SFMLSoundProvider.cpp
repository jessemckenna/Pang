#include "stdafx.h"
#include "SFMLSoundProvider.h"

// --- SFMLSoundProvider ---
// Standard constructor
SFMLSoundProvider::SFMLSoundProvider() : _currentSongName("")
{
}

// --- PlaySound ---
// Play sound in sound file cache on the last available channel
void SFMLSoundProvider::PlaySound(std::string filename)
{
	// Get the number of available channels, set to "availChannel"
	int availChannel = -1;

	for (int i = 0; i < MAX_SOUND_CHANNELS; i++)
	{
		if (_currentSounds[i].getStatus() != sf::Sound::Playing)
		{
			// Set availChannel to index of first available channel, exit loop
			availChannel = i;
			break;
		}
	}

	// If there is a channel available
	if (availChannel != -1)
	{
		try
		{
			// Try to set the first available channel to a sound from the cache
			_currentSounds[availChannel] = _soundFileCache.GetSound(filename);
			_currentSounds[availChannel].play();
		}
		catch (SoundNotFoundException&)
		{
			// Do nothing; exception isn't major
		}
	}
}

// --- PlaySong ---
// Load music from file and play on a loop or not depending on input parameters
void SFMLSoundProvider::PlaySong(std::string filename, bool looping)
{
	// Create pointer currentSong and point to the song in the _soundFileCache
	sf::Music* currentSong;

	try
	{
		currentSong = _soundFileCache.GetSong(filename);
	}
	catch (SoundNotFoundException&)
	{
		return; // exit program if song not found
	}

	// Stop prior song if still playing
	if (_currentSongName != "")
	{
		try
		{
			sf::Music* priorSong = _soundFileCache.GetSong(_currentSongName);
			if (priorSong->getStatus() != sf::Sound::Stopped)
			{
				priorSong->stop();
			}
		}
		catch (SoundNotFoundException&)
		{
			// Do nothing; exception isn't major
		}
	}

	_currentSongName = filename;
	currentSong->setLoop(looping);
	currentSong->play();
}

// --- StopAllSounds ---
// Stop playing all sounds and music
void SFMLSoundProvider::StopAllSounds()
{
	// Stop all songs in _currentSounds
	for (int i = 0; i < MAX_SOUND_CHANNELS; i++)
	{
		_currentSounds[i].stop();
	}

	// Stop currently playing music
	if (_currentSongName != "")
	{
		sf::Music* currentSong = _soundFileCache.GetSong(_currentSongName);
		if (currentSong->getStatus() == sf::Sound::Playing)
		{
			currentSong->stop();
		}
	}
}

// --- IsSoundPlaying ---
// Return true if any sound in _currentSounds is currently playing
bool SFMLSoundProvider::IsSoundPlaying()
{
	for (int i = 0; i < MAX_SOUND_CHANNELS; i++)
	{
		if (_currentSounds[i].getStatus() == sf::Sound::Playing)
			return true;
	}
	return false;
}

// --- IsSongPlaying ---
// Return true if music is currently playing
bool SFMLSoundProvider::IsSongPlaying()
{
	if (_currentSongName != "")
	{
		return _soundFileCache.GetSong(_currentSongName)->getStatus() == 
			sf::Music::Playing;
	}
	return false;
}