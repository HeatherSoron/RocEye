#include "BaseAppInput.h"
#include <SDL/SDL_mouse.h>

BaseAppInput::BaseAppInput(void)
{
}

BaseAppInput::~BaseAppInput(void)
{
	SDL_ShowCursor(1);
	
	//do NOT need to destroy the camera pointer, since we assume it's handled elsewhere
}

void BaseAppInput::setup(Ogre::SceneNode* cameraNode)
{
	mCameraNode = cameraNode;
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
	Ogre::Vector3 moveVector(0,0,0);
	
	Uint8* keys = SDL_GetKeyState(NULL);
	if (keys[SDLK_ESCAPE])
	{
		return false;
	}
	
	//wait, shouldn't we be moving along z with w/s...? oh, right, we remapped where the camera was looking, right.
	if (keys[SDLK_w])
	{
		moveVector.z -= mCameraSpeed;
	}
	if (keys[SDLK_s])
	{
		moveVector.z += mCameraSpeed;
	}
	if (keys[SDLK_a])
	{
		moveVector.x -= mCameraSpeed;
	}
	if (keys[SDLK_d])
	{
		moveVector.x += mCameraSpeed;
	}
	if (keys[SDLK_r])
	{
		moveVector.y += mCameraSpeed;
	}
	if (keys[SDLK_f])
	{
		moveVector.y -= mCameraSpeed;
	}
	
	if (keys[SDLK_e])
	{
		mCameraNode->roll(Ogre::Degree(-mKeyRotateSpeed), Ogre::SceneNode::TS_LOCAL);
	}
	if (keys[SDLK_q])
	{
		mCameraNode->roll(Ogre::Degree(mKeyRotateSpeed), Ogre::SceneNode::TS_LOCAL);
	}
	
	if (keys[SDLK_DOWN])
	{
		mCameraNode->pitch(Ogre::Degree(-mKeyRotateSpeed), Ogre::SceneNode::TS_LOCAL);
	}
	if (keys[SDLK_UP])
	{
		mCameraNode->pitch(Ogre::Degree(mKeyRotateSpeed), Ogre::SceneNode::TS_LOCAL);
	}
	if (keys[SDLK_RIGHT])
	{
		mCameraNode->yaw(Ogre::Degree(-mKeyRotateSpeed), Ogre::SceneNode::TS_LOCAL);
	}
	if (keys[SDLK_LEFT])
	{
		mCameraNode->yaw(Ogre::Degree(mKeyRotateSpeed), Ogre::SceneNode::TS_LOCAL);
	}
	
	mCameraNode->translate(moveVector, Ogre::SceneNode::TS_LOCAL);
	
	return true;
}

bool BaseAppInput::handleMouse(void)
{
	static const int CENTER_X = 320;
	static const int CENTER_Y = 240;
	
	int x, y;
	SDL_GetMouseState(&x,&y);
	
	std::cout << x << ", " << y << std::endl;
	
	int dx, dy; //deltas
	dx = x - CENTER_X;
	dy = y - CENTER_Y;
	
	mCameraNode->yaw(Ogre::Degree(-dx * mMouseRotateSpeed));
    mCameraNode->pitch(Ogre::Degree(-dy * mMouseRotateSpeed));	
	
	//ideally, we would tell SDL to use relative mouse mode directly. Unfortunately, that seems not to be present in 1.2.15? At least, the Linux header I have doesn't seem to have SDL_SetRelativeMouseMode.
	if (dx || dy)
	{
		SDL_WarpMouse(CENTER_X, CENTER_Y);
	}
	
	return true;
}


/*
bool OgreBaseApp::mouseMoved(const OIS::MouseEvent& evt)
{
	return true;
}
*/
