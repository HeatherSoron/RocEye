//note: only create ONE of these per scene manager

#ifndef OBJECT_MANAGER_H
#define OBJECT_MANAGER_H

#include "RocEyeObject.h"
#include <vector>

class ObjectManager
{
public:	
	enum ObjectType
	{
		GAME,
		DISPLAY
	};
	
	ObjectManager(Ogre::SceneManager* sceneMgr);
	virtual ~ObjectManager(void);
	
	virtual Ogre::SceneManager* getSceneManager(void) { return mSceneMgr; }; //intended primarily to check that we're using the right scene manager!
	
	virtual RocEyeObject* getObjectByID(unsigned int index, ObjectType type); //returns NULL if the object doesn't exist, or the index is invalid
	virtual RocEyeObject* getObjectByName(Ogre::String nodeName);
	virtual RocEyeObject* createObject(ObjectType type); //creates a RocEyeObject, and accompanying scene node, and adds it to the list
	virtual bool removeObjectByID(unsigned int index, ObjectType type);
	virtual bool removeObjectByName(Ogre::String name);
protected:
	Ogre::SceneManager* mSceneMgr;
	std::vector<RocEyeObject*> mGameObjectList; //note that elements are not guaranteed to exist, unless the corresponding scene node also exists
	std::vector<RocEyeObject*> mDispObjectList;
	unsigned int mGameID;
	unsigned int mDispID;
	static const int mNamePrefixLength = 10; //expects names to be prefixed with "GameObject", "DispObject"
};

#endif
