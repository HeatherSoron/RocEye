#include "RocEye.h"

RocEye::RocEye(void)
{
}

RocEye::~RocEye(void)
{
}

void RocEye::setupInput(void)
{
	RocEyeInput* input = new RocEyeInput();
	input->setHandler(&mHandler);
	
	mInput = input;
	
	mHandler.setCamera(mCameraNode);
	mHandler.resetCamera();
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

void RocEye::createPortraitCube(Ogre::Vector3 center, Ogre::Real diam, Ogre::String texture)
{
	static unsigned int id = 0;
	
	char name[16];
	sprintf(name, "Cube%d", id++);
	
	Ogre::SceneNode* boxNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(Ogre::String(name) + "node");
	
	Ogre::ManualObject* mo = mSceneMgr->createManualObject(Ogre::String(name) + "Object");
	
	mo->begin(texture, Ogre::RenderOperation::OT_TRIANGLE_LIST);
	
	int offset = 0; //we'll be using this to calculate vertices for the index buffer
	
	//first we create the top side
	mo->position(diam/2, diam/2, diam/2);
	mo->textureCoord(0,0);
	mo->position(-diam/2, diam/2, diam/2);
	mo->textureCoord(1,0);
	mo->position(diam/2, diam/2, -diam/2);
	mo->textureCoord(0,1);
	mo->position(-diam/2, diam/2, -diam/2);
	mo->textureCoord(1,1);
	
	mo->triangle(offset + 0, offset + 2, offset + 1);
	mo->triangle(offset + 1, offset + 2, offset + 3);
	offset += 4;
	
	//now the bottom
	mo->position(diam/2, -diam/2, diam/2);
	mo->textureCoord(0,0);
	mo->position(-diam/2, -diam/2, diam/2);
	mo->textureCoord(1,0);
	mo->position(diam/2, -diam/2, -diam/2);
	mo->textureCoord(0,1);
	mo->position(-diam/2, -diam/2, -diam/2);
	mo->textureCoord(1,1);
	
	mo->triangle(offset + 0, offset + 1, offset + 2);
	mo->triangle(offset + 1, offset + 3, offset + 2);
	offset += 4;
	
	//set up a rotation for the for loop below
	Ogre::Quaternion rot;
	rot.FromAngleAxis(Ogre::Degree(90), Ogre::Vector3::UNIT_Y);
	
	//and set up a vector to rotate (this'll be the center point of each face)
	//note that this vector doesn't NEED to be this length, but it'll save us a post-dot product multiplication
	Ogre::Vector3 faceCenter(diam/2, 0, 0);
	
	//now we create all 4 sides
	//that 6 represents the number of faces a cube has, btw
	for (offset; offset < 4 * 6; offset += 4)
	{
		mo->position(
			faceCenter.dotProduct(Ogre::Vector3::UNIT_X) + faceCenter.dotProduct(Ogre::Vector3::UNIT_Z),
			diam/2,
			-faceCenter.dotProduct(Ogre::Vector3::UNIT_Z) + faceCenter.dotProduct(Ogre::Vector3::UNIT_X));
		mo->textureCoord(0,0);
		mo->position(
			faceCenter.dotProduct(Ogre::Vector3::UNIT_X) + -faceCenter.dotProduct(Ogre::Vector3::UNIT_Z),
			diam/2,
			-faceCenter.dotProduct(Ogre::Vector3::UNIT_Z) + -faceCenter.dotProduct(Ogre::Vector3::UNIT_X));
		mo->textureCoord(1,0);
		mo->position(
			faceCenter.dotProduct(Ogre::Vector3::UNIT_X) + faceCenter.dotProduct(Ogre::Vector3::UNIT_Z),
			-diam/2,
			-faceCenter.dotProduct(Ogre::Vector3::UNIT_Z) + faceCenter.dotProduct(Ogre::Vector3::UNIT_X));
		mo->textureCoord(0,1);
		mo->position(
			faceCenter.dotProduct(Ogre::Vector3::UNIT_X) + -faceCenter.dotProduct(Ogre::Vector3::UNIT_Z),
			-diam/2,
			-faceCenter.dotProduct(Ogre::Vector3::UNIT_Z) + -faceCenter.dotProduct(Ogre::Vector3::UNIT_X));
		mo->textureCoord(1,1);
	
		mo->triangle(offset + 0, offset + 3, offset + 1);
		mo->triangle(offset + 0, offset + 2, offset + 3);
		
		faceCenter = rot * faceCenter;
	}
	
	mo->end();
	
	//we SHOULD convert this to a mesh, but that's not rendering (at all) on my machine. So, using mo directly for now
	
	//mo->convertToMesh(Ogre::String(name) + "Mesh");
	//Ogre::Entity* ent = mSceneMgr->createEntity(Ogre::String(name), Ogre::String(name) + "Mesh");
	
	boxNode->attachObject(mo);
    
    boxNode->setPosition(center);
}

void RocEye::createPortraitPillar(Ogre::Vector3 center, Ogre::Real diam, Ogre::String texture)
{
	static unsigned int id = 0;
	
	char name[16];
	sprintf(name, "Pillar%d", id++);
	
	Ogre::SceneNode* boxNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(Ogre::String(name) + "node");
	
	Ogre::ManualObject* mo = mSceneMgr->createManualObject(Ogre::String(name) + "Object");
	
	mo->begin(texture, Ogre::RenderOperation::OT_TRIANGLE_LIST);
	
	int offset = 0; //we'll be using this to calculate vertices for the index buffer
	
	//first we create the top side
	mo->position(diam/2, diam/2, diam/2);
	mo->textureCoord(0,0);
	mo->position(-diam/2, diam/2, diam/2);
	mo->textureCoord(1,0);
	mo->position(diam/2, diam/2, -diam/2);
	mo->textureCoord(0,1);
	mo->position(-diam/2, diam/2, -diam/2);
	mo->textureCoord(1,1);
	
	mo->triangle(offset + 0, offset + 2, offset + 1);
	mo->triangle(offset + 1, offset + 2, offset + 3);
	//double-sided
	mo->triangle(offset + 0, offset + 1, offset + 2);
	mo->triangle(offset + 1, offset + 3, offset + 2);
	offset += 4;
	
	//now the bottom
	mo->position(diam/2, -diam/2, diam/2);
	mo->textureCoord(0,0);
	mo->position(-diam/2, -diam/2, diam/2);
	mo->textureCoord(1,0);
	mo->position(diam/2, -diam/2, -diam/2);
	mo->textureCoord(0,1);
	mo->position(-diam/2, -diam/2, -diam/2);
	mo->textureCoord(1,1);
	
	mo->triangle(offset + 0, offset + 2, offset + 1);
	mo->triangle(offset + 1, offset + 2, offset + 3);
	//double-sided
	mo->triangle(offset + 0, offset + 1, offset + 2);
	mo->triangle(offset + 1, offset + 3, offset + 2);
	offset += 4;
	
	//set up a rotation for the for loop below
	Ogre::Quaternion rot;
	rot.FromAngleAxis(Ogre::Degree(90), Ogre::Vector3::UNIT_Y);
	
	//and set up a vector to rotate (this'll be the center point of each face)
	//note that this vector doesn't NEED to be this length, but it'll save us a post-dot product multiplication
	Ogre::Vector3 faceCenter(diam/2, 0, 0);
	
	//now we create all 4 sides
	//that 6 represents the number of faces a cube has, btw
	for (offset; offset < 4 * 6; offset += 4)
	{
		mo->position(faceCenter.dotProduct(Ogre::Vector3::UNIT_Z), diam/2, faceCenter.dotProduct(Ogre::Vector3::UNIT_X));
		mo->textureCoord(0,0);
		mo->position(-faceCenter.dotProduct(Ogre::Vector3::UNIT_Z), diam/2, -faceCenter.dotProduct(Ogre::Vector3::UNIT_X));
		mo->textureCoord(1,0);
		mo->position(faceCenter.dotProduct(Ogre::Vector3::UNIT_Z), -diam/2, faceCenter.dotProduct(Ogre::Vector3::UNIT_X));
		mo->textureCoord(0,1);
		mo->position(-faceCenter.dotProduct(Ogre::Vector3::UNIT_Z), -diam/2, -faceCenter.dotProduct(Ogre::Vector3::UNIT_X));
		mo->textureCoord(1,1);
	
		mo->triangle(offset + 0, offset + 3, offset + 1);
		mo->triangle(offset + 0, offset + 2, offset + 3);
		
		faceCenter = rot * faceCenter;
	}
	
	mo->end();
	
	//we SHOULD convert this to a mesh, but that's not rendering (at all) on my machine. So, using mo directly for now
	
	//mo->convertToMesh(Ogre::String(name) + "Mesh");
	//Ogre::Entity* ent = mSceneMgr->createEntity(Ogre::String(name), Ogre::String(name) + "Mesh");
	
	boxNode->attachObject(mo);
    
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
