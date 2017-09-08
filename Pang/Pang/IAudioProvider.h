#pragma once

#include "stdafx.h"

class IAudioProvider
{
public:
	// IAudioProvider's member functions are "pure virtual", meaning they must
	// be implemented in a derived class; this is signified by a virtual
	// member function initialized to 0, as below
	
	virtual ~IAudioProvider() {}
	virtual void PlaySound(std::string filename) = 0;
	virtual void PlaySong(std::string filename, bool looping) = 0;
	virtual void StopAllSounds() = 0;

	virtual bool IsSoundPlaying() = 0;
	virtual bool IsSongPlaying() = 0;
};
