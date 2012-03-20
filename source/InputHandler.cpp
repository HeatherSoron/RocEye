#include "InputHandler.h"

InputHandler::InputHandler(void)
{
	resetState();
}

InputHandler::~InputHandler(void)
{
}

void InputHandler::setCamera(Ogre::SceneNode* cameraNode)
{
	mCameraNode = cameraNode;
}

void InputHandler::translate(InputHandler::Direction dir)
{
	switch (dir)
	{
		case DIR_LEFT:
			mTransVector.x -= 1; break;
		case DIR_RIGHT:
			mTransVector.x += 1; break;
		case DIR_FORWARD:
			mTransVector.z -= 1; break;
		case DIR_BACKWARD:
			mTransVector.z += 1; break;
		case DIR_DOWN:
			mTransVector.y -= 1; break;
		case DIR_UP:
			mTransVector.y += 1; break;
	}
}

void InputHandler::rotate(InputHandler::Direction rot, bool isMouse, float mult)
{
	Ogre::Real speed = isMouse ? mMouseRotateSpeed : mKeyRotateSpeed;
	speed *= mult;
	
	switch (rot)
	{
		case ROT_UP:
			mRotVector.x += speed; break;
		case ROT_DOWN:
			mRotVector.x -= speed; break;
		case ROT_LEFT:
			mRotVector.y += speed; break;
		case ROT_RIGHT:
			mRotVector.y -= speed; break;
		case ROT_CCW:
			mRotVector.z += speed; break;
		case ROT_CW:
			mRotVector.z -= speed; break;
	}
}

void InputHandler::changeSpeed(float numSteps)
{
	if (numSteps > 0)
	{
		mSpeedMult *= SPEED_PER_STEP * numSteps;
	}
	else if (numSteps < 0)
	{
		mSpeedMult /= SPEED_PER_STEP * -numSteps; //remember to get it back to positive values
	}
}

void InputHandler::resetCamera(void)
{
	mCameraNeedsReset = true;
}

void InputHandler::execute(void)
{
	mCameraNode->translate(mTransVector * mCameraSpeed * mSpeedMult, Ogre::SceneNode::TS_LOCAL);
	
	mCameraNode->pitch(Ogre::Degree(mRotVector.x * mSpeedMult));
	mCameraNode->yaw(Ogre::Degree(mRotVector.y * mSpeedMult));
	mCameraNode->roll(Ogre::Degree(mRotVector.z * mSpeedMult));
	
	if (mCameraNeedsReset)
	{
		Ogre::Quaternion orient(1,-1,0,0); //point straight down
		mCameraNode->setOrientation(orient);
	}
	
	resetState();
}

void InputHandler::resetState(void)
{
	mCameraNeedsReset = false;
	mTransVector = Ogre::Vector3(0,0,0);
	mRotVector = Ogre::Vector3(0,0,0);
	mSpeedMult = 1;
}
