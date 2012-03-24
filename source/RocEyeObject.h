#ifndef ROC_EYE_OBJECT_H
#define ROC_EYE_OBJECT_H

#include <Ogre.h>

//intended to be used as a base class for meshes and things in the app (in order to track them separately from their representation in Ogre itself)
class RocEyeObject
{
public:
	RocEyeObject(void);
	RocEyeObject(Ogre::SceneNode* sceneNode);
	virtual ~RocEyeObject(void);
	virtual Ogre::SceneNode* getSceneNode(void) { return mNode; };
	virtual void setSceneNode(Ogre::SceneNode* node);
	virtual bool getSnapToGrid(void) { return mSnapToGrid; };
	virtual void setSnapToGrid(bool snap) { mSnapToGrid = snap; };
	virtual Ogre::Vector3 getPosition(void) { return mPosition; };
	virtual void setPosition(Ogre::Vector3 pos);
	virtual void translate(Ogre::Vector3 offset);
protected:
	virtual void updateNodePosition(void);
	
	Ogre::SceneNode* mNode;
	Ogre::Vector3 mPosition;
	bool mSnapToGrid;
};

#endif
