#ifndef GRID_LINE_FACTORY_H
#define GRID_LINE_FACTORY_H

#include "ColouredLine.h"

class GridLineFactory
{
public:
	GridLineFactory();
	GridLineFactory(Ogre::SceneManager* sceneMgr);
	virtual ~GridLineFactory();
	
	void setSceneManager(Ogre::SceneManager* sceneMgr) { removeGrid(); mSceneMgr = sceneMgr; };
	void addGrid(Ogre::Vector3 center, Ogre::Real cellSize, int linesPerDirection);
	void removeGrid(void);
	bool isGridEmpty(void) { return mLineList == NULL; };
protected:
	static void createMaterials(void);
	virtual void addLine(Ogre::String material, Ogre::Vector3 lineCenter, Ogre::Vector3 lineHalfLength);
	
	Ogre::SceneManager* mSceneMgr;
	int mLineID;
	//static bool materialsCreated;
	ColouredLine** mLineList;
};

//bool GridLineFactory::materialsCreated = false;

#endif
