#include "RocEyeObject.h"
#include "GridHelper.h"

RocEyeObject::RocEyeObject(void)
	:
	mNode(NULL),
	mSnapToGrid(true)
{
}

RocEyeObject::RocEyeObject(Ogre::SceneNode* node)
	:
	mNode(node),
	mSnapToGrid(true)
{
}

RocEyeObject::~RocEyeObject(void)
{
}

void RocEyeObject::setSceneNode(Ogre::SceneNode* node)
{
	mNode = node;
	mPosition = mNode->getPosition();
}

void RocEyeObject::setPosition(Ogre::Vector3 pos)
{
	mPosition = pos;
	updateNodePosition();
}

void RocEyeObject::translate(Ogre::Vector3 offset)
{
	mPosition += offset;
	updateNodePosition();
}

void RocEyeObject::updateNodePosition(void)
{
	if (mSnapToGrid)
	{
		mNode->setPosition(GridHelper::roundToGrid(mPosition));
	}
	else
	{
		mNode->setPosition(mPosition);
	}
}
