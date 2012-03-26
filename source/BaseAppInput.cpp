#include "BaseAppInput.h"

#include <iostream>

BaseAppInput::BaseAppInput(void) : mKeyState(KeyboardState()), mWasLeftDown(false), mWasRightDown(false), mWasMiddleDown(false)
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
	if (! handleKeyboard(NULL) || ! handleMouse())
	{
		return false;
	}
	mKeyState.UpdateBeforeFrame();
	SDL_Event evt;
	while (SDL_PollEvent(&evt)) //need to make sure it's not null
	{
		if (!processEvent(&evt))
		{
			return false;
		}
	}
	bool ret=runFrameInternal();
	frameDone();
	return ret;
}

bool BaseAppInput::processEvent(SDL_Event* evt)
{
	switch (evt->type)
	{
		case SDL_ACTIVEEVENT:
		{
			switch (evt->active.state)
			{
				case SDL_APPMOUSEFOCUS:
				{
					if (evt->active.gain)
					{
						//TODO handle mouse focus
					}
					else
					{
						//TODO handle mouse blur
					}
					break;
				}
				case SDL_APPINPUTFOCUS:
				{
					if (evt->active.gain)
					{
						//TODO handle input focus
					}
					else
					{
						//TODO handle input blur
					}
					break;
				}
				case SDL_APPACTIVE:
				{
					if (evt->active.gain)
					{
						//TODO handle restore event
					}
					else
					{
						//TODO handle minimize event
					}
					break;
				}
			}
			break;
		}
		
		case SDL_KEYDOWN:
		{
			mKeyState.UpdateForKeyDown(evt->key.keysym.sym);
			return onKeyDown(evt->key.keysym.sym, evt->key.keysym.mod, evt->key.keysym.unicode);
			break;
		}
		
		case SDL_KEYUP:
		{
			mKeyState.UpdateForKeyUp(evt->key.keysym.sym);
			return onKeyUp(evt->key.keysym.sym, evt->key.keysym.mod, evt->key.keysym.unicode);
			break;
		}
	}
	
	return true;
}

void BaseAppInput::frameDone(void)
{
	//SDL wants us to pump the events periodically to keep them flowing
	for(int i = 0; i < 1000; ++i) SDL_PumpEvents();
	// We seem to need to pump "a few" times, at least on mac, to keep keys from sticking.
}

KeyArray* BaseAppInput::handleKeyboard(KeyArray* keys)
{
	if(!keys)
	{
		keys = SDL_GetKeyState(NULL);	
	}
	
	if (keys[SDLK_ESCAPE])
	{
		return NULL;
	}
	
	return keys;
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
