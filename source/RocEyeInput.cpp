#include "RocEyeInput.h"

RocEyeInput::RocEyeInput(void) : BaseAppInput(),
	mWasKeyDownC(false),
	mWasKeyDownG(false),
	mWasKeyDownH(false),
	mWasKeyDownO(false)
{
}

RocEyeInput::~RocEyeInput(void)
{
}

void RocEyeInput::setHandler(InputHandler* handler)
{
	mHandler = handler;
}

bool RocEyeInput::handleKeyboard(void)
{
	if (!BaseAppInput::handleKeyboard())
	{
		return false;
	}
	
	Uint8* keys = SDL_GetKeyState(NULL);
	
	if (keys[SDLK_o] && !mWasKeyDownO)
	{
		mWasKeyDownO = true;
		mHandler->toggleObjectMode();
	}
	else if (!keys[SDLK_o])
	{
		mWasKeyDownO = false;
	}
	
	
	if (keys[SDLK_LSHIFT] || keys[SDLK_RSHIFT])
	{
		mHandler->changeSpeed(1);
	}
	if (keys[SDLK_LCTRL] || keys[SDLK_RCTRL])
	{
		mHandler->changeSpeed(-1);
	}
	
	if (keys[SDLK_w])
	{
		mHandler->translate(InputHandler::DIR_FORWARD);
	}
	if (keys[SDLK_s])
	{
		mHandler->translate(InputHandler::DIR_BACKWARD);
	}
	if (keys[SDLK_a])
	{
		mHandler->translate(InputHandler::DIR_LEFT);
	}
	if (keys[SDLK_d])
	{
		mHandler->translate(InputHandler::DIR_RIGHT);
	}
	if (keys[SDLK_r])
	{
		mHandler->translate(InputHandler::DIR_UP);
	}
	if (keys[SDLK_f])
	{
		mHandler->translate(InputHandler::DIR_DOWN);
	}
	
	if (keys[SDLK_e])
	{
		mHandler->rotate(InputHandler::ROT_CW, false);
	}
	if (keys[SDLK_q])
	{
		mHandler->rotate(InputHandler::ROT_CCW, false);
	}
	
	if (keys[SDLK_DOWN])
	{
		mHandler->rotate(InputHandler::ROT_DOWN, false);
	}
	if (keys[SDLK_UP])
	{
		mHandler->rotate(InputHandler::ROT_UP, false);
	}
	if (keys[SDLK_RIGHT])
	{
		mHandler->rotate(InputHandler::ROT_RIGHT, false);
	}
	if (keys[SDLK_LEFT])
	{
		mHandler->rotate(InputHandler::ROT_LEFT, false);
	}
	if (keys[SDLK_SPACE])
	{
		mHandler->resetCamera();
	}
	
	if (keys[SDLK_c])
	{
		if (!mWasKeyDownC && (keys[SDLK_LSHIFT] || keys[SDLK_RSHIFT]))
		{
			mHandler->toggleObjectLock();
		}
		else
		{
			mHandler->centerObject();
		}
		mWasKeyDownC = true;
	}
	else
	{
		mWasKeyDownC = false;
	}
	
	if (keys[SDLK_h])
	{
		if (!mWasKeyDownH && (keys[SDLK_LSHIFT] || keys[SDLK_RSHIFT]))
		{
			mHandler->toggleHorizonLock();
		}
		else
		{
			mHandler->levelHorizon();
		}
		mWasKeyDownH = true;
	}
	else
	{
		mWasKeyDownH = false;
	}
	
	if (keys[SDLK_g] && !mWasKeyDownG)
	{
		mHandler->toggleGridLines(keys[SDLK_LSHIFT] || keys[SDLK_RSHIFT]);
		mWasKeyDownG = true;
	}
	else if (!keys[SDLK_g])
	{
		mWasKeyDownG = false;
	}
	
	return true;
}

bool RocEyeInput::handleMouse(void)
{
	if (! BaseAppInput::handleMouse() )
	{
		return false;
	}
	
	static const int CENTER_X = 320;
	static const int CENTER_Y = 240;
	
	int x, y;
	SDL_GetMouseState(&x,&y);
	
	int dx, dy; //deltas
	dx = x - CENTER_X;
	dy = y - CENTER_Y;
	
	
	mHandler->rotate(InputHandler::ROT_RIGHT, true, dx);
    mHandler->rotate(InputHandler::ROT_UP, true, -dy);	
    
	
	//ideally, we would tell SDL to use relative mouse mode directly. Unfortunately, that seems not to be present in 1.2.15? At least, the Linux header I have doesn't seem to have SDL_SetRelativeMouseMode.
	if (dx || dy)
	{
		SDL_WarpMouse(CENTER_X, CENTER_Y);
	}
	return true;
}

bool RocEyeInput::fireLeftMouseDown(void)
{
	return mHandler->onPrimaryPointerDown();	
}

bool RocEyeInput::fireLeftMouseUp(void)
{
	return mHandler->onPrimaryPointerUp();
}

void RocEyeInput::frameDone(void)
{
	BaseAppInput::frameDone();
	
	mHandler->execute(); //need to tell our input handler to actually run what we told it to do
}
