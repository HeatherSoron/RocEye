#include "RocEye.h"

RocEye::RocEye(void)
{
}

RocEye::~RocEye(void)
{
}

void RocEye::createScene(void)
{
	loadSceneFile();

	//set a decent ambient light level
	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
}

void RocEye::createEntity(Ogre::String mesh, Ogre::Vector3 pos)
{
using namespace std;
	static unsigned int id = 0; //keep a unique ID of every node we instantiate
	Ogre::Entity* entity = mSceneMgr->createEntity("Entity" + id, mesh);
	entity->setCastShadows(true);
	
	Ogre::SceneNode* node = mSceneMgr->getRootSceneNode()->createChildSceneNode("EntityNode" + id, pos);
	node->attachObject(entity);
	
	++id;
}

void RocEye::createPlane(Ogre::Vector3 normal, Ogre::Real distFromOrigin, Ogre::Real width, Ogre::Real height, Ogre::String materialName, Ogre::Vector3 upDir)
{
	static unsigned int id = 0; //keep a unique ID of our planes
	
	Ogre::Plane plane(normal, distFromOrigin);
	Ogre::MeshManager::getSingleton().createPlane("plane" + id, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
    plane, width, height, 20, 20, true, 1, 5, 5, upDir);
    
    Ogre::Entity* entGround = mSceneMgr->createEntity("PlaneEntity" + id, "plane" + id);
	mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(entGround);
	
	entGround->setMaterialName(materialName);
	entGround->setCastShadows(false);
	
	++id;
}

void RocEye::createPointLight(Ogre::Vector3 position, Ogre::ColourValue dColour, Ogre::ColourValue sColour)
{
	static unsigned int id = 0;
using namespace std;
cout << position << endl << dColour << endl << sColour << endl;
	//create a light
	Ogre::Light* l = mSceneMgr->createLight("PointLight" + id);
	l->setType(Ogre::Light::LT_POINT);
	l->setPosition(position);
	l->setDiffuseColour(dColour);
	l->setSpecularColour(sColour);
	
	++id;
}

void RocEye::createDirectionalLight(Ogre::Vector3 direction, Ogre::ColourValue dColour, Ogre::ColourValue sColour)
{
	static unsigned int id = 0;
	
	//create a light
	Ogre::Light* l = mSceneMgr->createLight("DirectionalLight" + id);
	l->setType(Ogre::Light::LT_DIRECTIONAL);
	l->setDirection(direction);
	l->setDiffuseColour(dColour);
	l->setSpecularColour(sColour);
	
	++id;
}

void RocEye::createSpotLight(Ogre::Vector3 position, Ogre::Vector3 direction, Ogre::ColourValue dColour, Ogre::ColourValue sColour, Ogre::Degree innerAngle, Ogre::Degree outerAngle)
{
	static unsigned int id = 0;
	
	//create a light
	Ogre::Light* l = mSceneMgr->createLight("SpotLight" + id);
	l->setType(Ogre::Light::LT_SPOTLIGHT);
	l->setPosition(position);
	l->setDirection(direction);
	l->setDiffuseColour(dColour);
	l->setSpecularColour(sColour);
	l->setSpotlightRange(innerAngle, outerAngle);
	
	++id;
}
