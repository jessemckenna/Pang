#pragma once

#include "stdafx.h"
#include "IAudioProvider.h"

class ServiceLocator
{
public:
	static IAudioProvider* GetAudio()
	{
		return _audioProvider; // get audio provider
	} const

	static void RegisterServiceLocator(IAudioProvider *provider)
	{
		_audioProvider = provider; // set audio provider
	}

private:
	static IAudioProvider* _audioProvider;
};