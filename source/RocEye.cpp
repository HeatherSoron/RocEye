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

//this is kinda hack-y, yes. I wanted to just use a manual object, but it wasn't working for me, for some reason. I'm gonna clean this up in future versions.
void RocEye::createCube(Ogre::Vector3 center, Ogre::Real diam, Ogre::String texture)
{
	static unsigned int id = 0;
	
	char name[16];
	sprintf(name, "Cube%d", id++);
	
	Ogre::SceneNode* boxNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(Ogre::String(name) + "node");
	
	Ogre::Plane top(Ogre::Vector3::UNIT_Y, diam/2);
	Ogre::MeshManager::getSingleton().createPlane(Ogre::String(name) + "Top", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
    top, diam, diam, 20, 20, true, 1, 1, 1, Ogre::Vector3::UNIT_X);
    Ogre::Entity* ent = mSceneMgr->createEntity(Ogre::String(name) + "TopEntity", Ogre::String(name) + "Top");
    ent->setMaterialName(texture);
    ent->setCastShadows(true);
    boxNode->createChildSceneNode()->attachObject(ent);
    
	Ogre::Plane right(Ogre::Vector3::UNIT_X, diam/2);
	Ogre::MeshManager::getSingleton().createPlane(Ogre::String(name) + "Right", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
    right, diam, diam, 20, 20, true, 1, 1, 1, Ogre::Vector3::UNIT_Y);
    ent = mSceneMgr->createEntity(Ogre::String(name) + "RightEntity", Ogre::String(name) + "Right");
    ent->setMaterialName(texture);
    ent->setCastShadows(true);
    boxNode->createChildSceneNode()->attachObject(ent);
    
	Ogre::Plane left(Ogre::Vector3::NEGATIVE_UNIT_X, diam/2);
	Ogre::MeshManager::getSingleton().createPlane(Ogre::String(name) + "Left", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
    left, diam, diam, 20, 20, true, 1, 1, 1, Ogre::Vector3::UNIT_Y);
    ent = mSceneMgr->createEntity(Ogre::String(name) + "LeftEntity", Ogre::String(name) + "Left");
    ent->setMaterialName(texture);
    ent->setCastShadows(true);
    boxNode->createChildSceneNode()->attachObject(ent);
    
	Ogre::Plane far(Ogre::Vector3::UNIT_Z, diam/2);
	Ogre::MeshManager::getSingleton().createPlane(Ogre::String(name) + "Far", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
    far, diam, diam, 20, 20, true, 1, 1, 1, Ogre::Vector3::UNIT_Y);
    ent = mSceneMgr->createEntity(Ogre::String(name) + "FarEntity", Ogre::String(name) + "Far");
    ent->setMaterialName(texture);
    ent->setCastShadows(true);
    boxNode->createChildSceneNode()->attachObject(ent);
    
	Ogre::Plane near(Ogre::Vector3::NEGATIVE_UNIT_Z, diam/2);
	Ogre::MeshManager::getSingleton().createPlane(Ogre::String(name) + "Near", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
    near, diam, diam, 20, 20, true, 1, 1, 1, Ogre::Vector3::UNIT_Y);
    ent = mSceneMgr->createEntity(Ogre::String(name) + "NearEntity", Ogre::String(name) + "Near");
    ent->setMaterialName(texture);
    ent->setCastShadows(true);
    boxNode->createChildSceneNode()->attachObject(ent);
    
	Ogre::Plane bottom(Ogre::Vector3::NEGATIVE_UNIT_Y, diam/2);
	Ogre::MeshManager::getSingleton().createPlane(Ogre::String(name) + "Bottom", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
    bottom, diam, diam, 20, 20, true, 1, 1, 1, Ogre::Vector3::UNIT_X);
    ent = mSceneMgr->createEntity(Ogre::String(name) + "BottomEntity", Ogre::String(name) + "Bottom");
    ent->setMaterialName(texture);
    ent->setCastShadows(true);
    boxNode->createChildSceneNode()->attachObject(ent);
    
    boxNode->setPosition(center);
}

void RocEye::createParticleSystem(Ogre::Vector3 position, Ogre::String source)
{
	static unsigned int id = 0;
	
	char name[16];
	sprintf(name, "PartSys%d", id++);
	
	Ogre::ParticleSystem* system = mSceneMgr->createParticleSystem(name, source);
	Ogre::SceneNode* node = mSceneMgr->getRootSceneNode()->createChildSceneNode(Ogre::String(name) + "Node");
	node->attachObject(system);
	node->setPosition(position);
}

void RocEye::createPointLight(Ogre::Vector3 position, Ogre::ColourValue dColour, Ogre::ColourValue sColour)
{
	static unsigned int id = 0;
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
