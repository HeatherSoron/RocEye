#ifndef COLOURED_LINE_H
#define COLOURED_LINE_H

#include <Ogre.h>

class ColouredLine
{
public:
	ColouredLine(Ogre::SceneManager* sceneMgr, Ogre::String name, Ogre::String material, Ogre::Vector3 start, Ogre::Vector3 end);
	virtual ~ColouredLine(void);
	Ogre::SceneNode* getNode(void) { return mSceneNode; };
protected:
	virtual void init(Ogre::String material, Ogre::Vector3 start, Ogre::Vector3 end);
	
	Ogre::SceneNode* mSceneNode;
	Ogre::ManualObject* mManualObject;
};

#endif
