// SoundTester.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include "SFMLSoundProvider.h"

int main()
{
	SFMLSoundProvider soundProvider;

	while (true)
	{
		soundProvider.PlaySound("Audio/beeep.wav");
		soundProvider.PlaySound("Audio/peeeeeep.wav");
		soundProvider.PlaySound("Audio/plop.wav");
	}
}

