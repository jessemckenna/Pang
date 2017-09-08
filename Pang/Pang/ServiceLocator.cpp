#include "stdafx.h"
#include "ServiceLocator.h"

// Initialize member variables manually; needed because they are static
IAudioProvider* ServiceLocator::_audioProvider = NULL;