#include "InputHandler.h"

InputHandler::InputHandler(void) : mRaySceneQuery(0), mSceneMgr(0), mSelectedObject(0)
{
	resetState();
}

InputHandler::~InputHandler(void)
{
	mSceneMgr->destroyQuery(mRaySceneQuery);
}

void InputHandler::setCamera(Ogre::Camera* camera)
{
	mCamera = camera;
	
	//we assume that we ALWAYS have a scene manager, if we also have a ray scene query
	if (mRaySceneQuery != NULL && mSceneMgr != NULL)
	{
		mSceneMgr->destroyQuery(mRaySceneQuery);
	}
	
	mSceneMgr = mCamera->getParentSceneNode()->getCreator();
	mRaySceneQuery = mSceneMgr->createRayQuery(Ogre::Ray());
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

bool InputHandler::onPrimaryPointerDown(void)
{
	clickOnObjects();
	
	return true;
}

bool InputHandler::onPrimaryPointerUp(void)
{
	deselectObject();
	
	return true;
}

void InputHandler::resetCamera(void)
{
	mCameraNeedsReset = true;
}

void InputHandler::clickOnObjects(void)
{
	//we need to perform a scene query, first of all
	Ogre::Ray mouseRay(mCamera->getParentSceneNode()->getPosition(), mCamera->getDerivedDirection());
	mRaySceneQuery->setRay(mouseRay);
	mRaySceneQuery->setSortByDistance(true);
	
	//execute the query
	Ogre::RaySceneQueryResult &result = mRaySceneQuery->execute();
	Ogre::RaySceneQueryResult::iterator iter = result.begin();
	
	//iterate through the results, and select the closest object
	for (iter; iter != result.end(); iter++)
	{
		if (iter->movable && iter->movable->getName().substr(0,5) != "tile[");
		{
			selectObject(iter->movable->getParentSceneNode());
			break; //return early if we've found what we want
		}
	}
}

void InputHandler::selectObject(Ogre::SceneNode* object)
{
	mSelectedObject = object;
	mSelectedObject->showBoundingBox(true);
}

void InputHandler::deselectObject(void)
{
	if (mSelectedObject)
	{
		mSelectedObject->showBoundingBox(false);
	}
	
	mSelectedObject = NULL;
}

void InputHandler::execute(void)
{
	Ogre::SceneNode* transObject = mSelectedObject ? mSelectedObject : mCamera->getParentSceneNode();
	
	transObject->translate(mTransVector * mCameraSpeed * mSpeedMult, Ogre::SceneNode::TS_LOCAL);
	
	mCamera->getParentSceneNode()->pitch(Ogre::Degree(mRotVector.x * mSpeedMult));
	mCamera->getParentSceneNode()->yaw(Ogre::Degree(mRotVector.y * mSpeedMult));
	mCamera->getParentSceneNode()->roll(Ogre::Degree(mRotVector.z * mSpeedMult));
	
	if (mCameraNeedsReset)
	{
		Ogre::Quaternion orient(1,-1,0,0); //point straight down
		mCamera->getParentSceneNode()->setOrientation(orient);
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
