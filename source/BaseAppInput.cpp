#include "BaseAppInput.h"

BaseAppInput::BaseAppInput(void) : mWasLeftDown(false), mWasRightDown(false), mWasMiddleDown(false)
{
}

BaseAppInput::~BaseAppInput(void)
{
	SDL_ShowCursor(1);
}

void BaseAppInput::setup(void)
{
	SDL_ShowCursor(0);
}

bool BaseAppInput::runFrame(void)
{
	//ideally, we would be using events. However, that tended to result in either segfaults or a hang when I tried it. *sigh*
	//so, we'll fake events on our own
	if (! handleKeyboard() || ! handleMouse())
	{
		return false;
	}
	
	frameDone();
	
	return true;
}

void BaseAppInput::frameDone(void)
{
	//SDL wants us to pump the events periodically to keep them flowing
	SDL_PumpEvents();
}

bool BaseAppInput::handleKeyboard(void)
{
	Uint8* keys = SDL_GetKeyState(NULL);
	if (keys[SDLK_ESCAPE])
	{
		return false;
	}
	
	return true;
}

bool BaseAppInput::handleMouse(void)
{
	Uint8 buttons = SDL_GetMouseState(NULL, NULL);
	
	bool left = buttons & SDL_BUTTON(1);
	bool right = buttons & SDL_BUTTON(2);
	bool middle = buttons & SDL_BUTTON(3);
	
	//fire our own mouse up/down events
	if (left)
	{
		if (!mWasLeftDown)
		{
			if (! fireLeftMouseDown() )
			{
				return false;
			}
		}
	}
	else
	{
		if (mWasLeftDown)
		{
			if (! fireLeftMouseUp() )
			{
				return false;
			}
		}
	}
	
	if (right)
	{
		if (!mWasRightDown)
		{
			if (! fireRightMouseDown() )
			{
				return false;
			}
		}
	}
	else
	{
		if (mWasRightDown)
		{
			if (! fireRightMouseUp() )
			{
				return false;
			}
		}
	}
	
	if (middle)
	{
		if (!mWasMiddleDown)
		{
			if (! fireMiddleMouseDown() )
			{
				return false;
			}
		}
	}
	else
	{
		if (mWasMiddleDown)
		{
			if (! fireMiddleMouseUp() )
			{
				return false;
			}
		}
	}
	
	mWasLeftDown = left;
	mWasRightDown = right;
	mWasMiddleDown = middle;
	return true;
}

bool BaseAppInput::fireLeftMouseDown(void)
{
	return true;
}

bool BaseAppInput::fireLeftMouseUp(void)
{
	return true;
}

bool BaseAppInput::fireRightMouseDown(void)
{
	return true;
}

bool BaseAppInput::fireRightMouseUp(void)
{
	return true;
}

bool BaseAppInput::fireMiddleMouseDown(void)
{
	return true;
}

bool BaseAppInput::fireMiddleMouseUp(void)
{
	return true;
}
