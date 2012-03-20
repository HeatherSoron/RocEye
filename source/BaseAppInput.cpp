#include "BaseAppInput.h"

BaseAppInput::BaseAppInput(void)
{
}

BaseAppInput::~BaseAppInput(void)
{
	//do NOT need to destroy the camera pointer, since we assume it's handled elsewhere
}

void BaseAppInput::setup(Ogre::SceneNode* cameraNode)
{
	mCameraNode = cameraNode;
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
	return true;
}


/*
bool OgreBaseApp::mouseMoved(const OIS::MouseEvent& evt)
{
	mCameraNode->yaw(Ogre::Degree(-evt.state.X.rel * mMouseRotateSpeed));
    mCameraNode->pitch(Ogre::Degree(-evt.state.Y.rel * mMouseRotateSpeed));
	return true;
}
*/
