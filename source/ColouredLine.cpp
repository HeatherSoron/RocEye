#include "ColouredLine.h"

ColouredLine::ColouredLine(Ogre::SceneManager* sceneMgr, Ogre::String name, Ogre::String material, Ogre::Vector3 start, Ogre::Vector3 end)
{
std::cout << "Line name: " << name << std::endl;
	mManualObject = sceneMgr->createManualObject(name);
	mSceneNode = sceneMgr->getRootSceneNode()->createChildSceneNode(name + "Node");
	init(material, start, end);
}

ColouredLine::~ColouredLine(void)
{
	Ogre::SceneManager* sceneMgr = mSceneNode->getCreator();
	sceneMgr->destroyManualObject(mManualObject);
	sceneMgr->destroySceneNode(mSceneNode);
}

void ColouredLine::init(Ogre::String material, Ogre::Vector3 start, Ogre::Vector3 end)
{
	mManualObject->begin(material, Ogre::RenderOperation::OT_LINE_LIST); 
	mManualObject->position(start); 
	mManualObject->position(end); 
	mManualObject->end(); 
	 
	mSceneNode->attachObject(mManualObject);
}
