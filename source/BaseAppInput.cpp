#include "BaseAppInput.h"
#include <SDL/SDL_mouse.h>

BaseAppInput::BaseAppInput(void)
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
	return true;
}
