#ifndef BASE_APP_INPUT_H
#define BASE_APP_INPUT_H

#ifdef WIN32
//Necessary to tell the mouse events to go to this window
#if (_WIN32_WINNT < 0x0501)
#undef _WIN32_WINNT
#define _WIN32_WINNT 0x0501
#endif
// Necessary to get the Window Handle of the window
// OGRE created, so SDL can grab its input.
#include "windows.h"
#include "SDL_getenv.h"
#endif
 
// SDL initialization:
#include "SDL/SDL.h"
#include "SDL/SDL_syswm.h"
#include "SDL/SDL_keyboard.h"

class BaseAppInput
{
public:
	BaseAppInput(void);
	virtual ~BaseAppInput(void);
	virtual void setup(void);
	virtual bool runFrame(void);
protected:
	
	virtual void frameDone(void);
	virtual bool handleKeyboard(void);
	virtual bool handleMouse(void);
	
	virtual bool fireLeftMouseDown(void);
	virtual bool fireLeftMouseUp(void);
	virtual bool fireRightMouseDown(void);
	virtual bool fireRightMouseUp(void);
	virtual bool fireMiddleMouseDown(void);
	virtual bool fireMiddleMouseUp(void);
	
	
	bool mWasLeftDown;
	bool mWasRightDown;
	bool mWasMiddleDown;
};

#endif
