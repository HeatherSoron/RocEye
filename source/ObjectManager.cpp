#include "ObjectManager.h"

ObjectManager::ObjectManager(Ogre::SceneManager* sceneMgr)
	:
	mSceneMgr(sceneMgr),
	mGameID(0),
	mDispID(0)
{
}

ObjectManager::~ObjectManager(void)
{
	for (unsigned int i = 0; i < mGameID; ++i)
	{
		RocEyeObject* obj = mGameObjectList[i];
		if (obj)
		{
			delete obj;
		}
	}
	for (unsigned int i = 0; i < mDispID; ++i)
	{
		RocEyeObject* obj = mDispObjectList[i];
		if (obj)
		{
			delete obj;
		}
	}	
}

RocEyeObject* ObjectManager::getObjectByID(unsigned int index, ObjectType type)
{
	std::vector<RocEyeObject*>* list = type == GAME ? &mGameObjectList : &mDispObjectList;
	if (index < list->size())
	{
		return list->at(index);
	}
	
	return NULL;
}

RocEyeObject* ObjectManager::getObjectByName(Ogre::String nodeName)
{
	ObjectType type;
	if (nodeName[0] == 'G')
	{
		type = GAME;
	}
	else if (nodeName[0] == 'D')
	{
		type = DISPLAY;
	}
	else
	{
		return NULL;
	}
	
	if (nodeName.substr(nodeName.length() - 4, 4) != "Node")
	{
		return NULL;
	}
	
	std::string indexString = nodeName.substr(10, nodeName.length() - mNamePrefixLength - 4);
	
	int index = atoi(indexString.c_str());
	
	return getObjectByID(index, type);
}

RocEyeObject* ObjectManager::createObject(ObjectType type)
{
	char name[32]; //making it kinda long, because GameObject takes up a lot of space
	std::vector<RocEyeObject*>* list;
	switch (type)
	{
		case GAME:
			sprintf(name, "GameObject%dNode", mGameID++);
			list = &mGameObjectList;
			break;
		case DISPLAY:
			sprintf(name, "DispObject%dNode", mDispID++);
			list = &mDispObjectList;
			break;
	}
	
	Ogre::SceneNode* node = mSceneMgr->getRootSceneNode()->createChildSceneNode(name);
	
	RocEyeObject* obj = new RocEyeObject(node);
	list->push_back(obj);
	
	return obj;
}

bool ObjectManager::removeObjectByID(unsigned int index, ObjectType type)
{
	std::vector<RocEyeObject*>* list = type == GAME ? &mGameObjectList : &mDispObjectList;
	if (index < list->size())
	{
		delete list->at(index);
		return true;
	}
	
	return false;
}

bool ObjectManager::removeObjectByName(Ogre::String nodeName)
{
	ObjectType type;
	if (nodeName[0] == 'G')
	{
		type = GAME;
	}
	else if (nodeName[0] == 'D')
	{
		type = DISPLAY;
	}
	else
	{
		return false;
	}
	
	if (nodeName.substr(nodeName.length() - 4, 4) != "Node")
	{
		return false;
	}
	
	std::string indexString = nodeName.substr(10, nodeName.length() - mNamePrefixLength - 4);
	
	int index = atoi(indexString.c_str());
	
	return removeObjectByID(index, type);
}
