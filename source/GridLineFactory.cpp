#include "GridLineFactory.h"

GridLineFactory::GridLineFactory(void)
{
	mLineList = NULL;
	mLineID = 0;
	createMaterials();
}

GridLineFactory::GridLineFactory(Ogre::SceneManager* sceneManager)
{
	mLineList = NULL;
	mLineID = 0;
	createMaterials();
	
	setSceneManager(sceneManager);
}

GridLineFactory::~GridLineFactory(void)
{
	removeGrid();
}

void GridLineFactory::addGrid(Ogre::Vector3 center, Ogre::Real cellSize, int linesPerDirection)
{
	removeGrid();
	
	mLineList = new ColouredLine*[((linesPerDirection+1) * 2) * ((linesPerDirection+1) * 2) * 3];
	
	const Ogre::Real boundaryOffset = cellSize * linesPerDirection + cellSize / 2;
	const Ogre::Real startOffset = boundaryOffset;
	
	//make the x and y lines
	for (Ogre::Real z = center.z - startOffset; z <= center.z + boundaryOffset; z += cellSize)
	{
		//add the x lines here
		for (Ogre::Real y = center.y - startOffset; y <= center.y + boundaryOffset; y += cellSize)
		{
			addLine("RedGridLine", Ogre::Vector3(center.x, y, z), Ogre::Vector3(boundaryOffset, 0, 0));
		}
		//add the y lines here
		for (Ogre::Real x = center.x - startOffset; x <= center.x + boundaryOffset; x += cellSize)
		{
			addLine("GreenGridLine", Ogre::Vector3(x, center.y, z), Ogre::Vector3(0, boundaryOffset, 0));
		}
	}
	
	//make the z lines
	for (Ogre::Real x = center.x - startOffset; x <= center.x + boundaryOffset; x += cellSize)
	{
		for (Ogre::Real y = center.y - startOffset; y <= center.y + boundaryOffset; y += cellSize)
		{
			addLine("BlueGridLine", Ogre::Vector3(x, y, center.z), Ogre::Vector3(0, 0, boundaryOffset));
		}
	}
}

void GridLineFactory::removeGrid(void)
{
	if (mLineID == 0)
	{
		return;
	}
	
	for (int i = 0; i < mLineID; ++i)
	{
		delete mLineList[i];
	}
	delete mLineList;
	mLineID = 0;
	
	mLineList = NULL;
}

void GridLineFactory::addLine(Ogre::String material, Ogre::Vector3 lineCenter, Ogre::Vector3 lineHalfLength)
{
	char name[16];
	sprintf(name, "GridLine%d", mLineID);
	mLineList[mLineID] = new ColouredLine(mSceneMgr, name, material, lineCenter - lineHalfLength, lineCenter + lineHalfLength); 
	
	++mLineID;
}

void GridLineFactory::createMaterials(void)
{
	Ogre::MaterialPtr myManualObjectMaterial = Ogre::MaterialManager::getSingleton().create("RedGridLine","General"); 
	myManualObjectMaterial->setReceiveShadows(false); 
	myManualObjectMaterial->getTechnique(0)->setLightingEnabled(true); 
	myManualObjectMaterial->getTechnique(0)->getPass(0)->setDiffuse(1,0,0,0); 
	myManualObjectMaterial->getTechnique(0)->getPass(0)->setAmbient(1,0,0); 
	myManualObjectMaterial->getTechnique(0)->getPass(0)->setSelfIllumination(1,0,0); 
	//myManualObjectMaterial->dispose();  // dispose pointer, not the material
	
	myManualObjectMaterial = Ogre::MaterialManager::getSingleton().create("GreenGridLine","General"); 
	myManualObjectMaterial->setReceiveShadows(false); 
	myManualObjectMaterial->getTechnique(0)->setLightingEnabled(true); 
	myManualObjectMaterial->getTechnique(0)->getPass(0)->setDiffuse(0,1,0,0); 
	myManualObjectMaterial->getTechnique(0)->getPass(0)->setAmbient(0,1,0); 
	myManualObjectMaterial->getTechnique(0)->getPass(0)->setSelfIllumination(0,1,0); 
	
	myManualObjectMaterial = Ogre::MaterialManager::getSingleton().create("BlueGridLine","General"); 
	myManualObjectMaterial->setReceiveShadows(false); 
	myManualObjectMaterial->getTechnique(0)->setLightingEnabled(true); 
	myManualObjectMaterial->getTechnique(0)->getPass(0)->setDiffuse(0,0,1,0); 
	myManualObjectMaterial->getTechnique(0)->getPass(0)->setAmbient(0,0,1); 
	myManualObjectMaterial->getTechnique(0)->getPass(0)->setSelfIllumination(0,0,1); 
	
	//materialsCreated = true;
}
