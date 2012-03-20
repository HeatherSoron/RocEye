#ifndef BASE_APP_INPUT_H
#define BASE_APP_INPUT_H

#include <Ogre.h>

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
	void setup(Ogre::SceneNode* cameraNode);
	bool runFrame(void);
	
    static const Ogre::Real mCameraSpeed = 4; //the speed of our camera
    static const Ogre::Real mMouseRotateSpeed = 0.2;
    static const Ogre::Real mKeyRotateSpeed = 2;
protected:
	
	void frameDone(void);
	bool handleKeyboard(void);
	bool handleMouse(void);
	
	Ogre::SceneNode* mCameraNode;
};

#endif
