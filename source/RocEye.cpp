#include "RocEye.h"

#include "ObjectManager.h"

RocEye::RocEye(void)
{
}

RocEye::~RocEye(void)
{
	delete mObjectMgr;
}

void RocEye::setupInput(void)
{
	RocEyeInput* input = new RocEyeInput(mWindowWidth, mWindowHeight);
	input->setup();
	input->setHandler(&mHandler);
	
	mInput = input;
	
	mHandler.setCamera(mCamera);
	mHandler.resetCamera();
}

void RocEye::createScene(void)
{
	mObjectMgr = new ObjectManager(mSceneMgr);
	mHandler.setObjectManager(mObjectMgr);
	
	loadSceneFile();

	//set a decent ambient light level
	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
}

Ogre::String RocEye::getObjectBaseName(RocEyeObject* obj)
{
	Ogre::String name = obj->getSceneNode()->getName();
	return name.substr(0, name.length() - 4);
}

void RocEye::createEntity(Ogre::String mesh, Ogre::Vector3 pos)
{
	RocEyeObject* obj = mObjectMgr->createObject(ObjectManager::GAME);
	obj->setPosition(pos);
	
	Ogre::Entity* entity = mSceneMgr->createEntity(getObjectBaseName(obj), mesh);
	entity->setCastShadows(true);
	
	obj->getSceneNode()->attachObject(entity);
}

void RocEye::createPlane(Ogre::Vector3 normal, Ogre::Real distFromOrigin, Ogre::Real width, Ogre::Real height, Ogre::String materialName, Ogre::Vector3 upDir)
{
	RocEyeObject* obj = mObjectMgr->createObject(ObjectManager::GAME);
	Ogre::String name = getObjectBaseName(obj);
	
	Ogre::Plane plane(normal, distFromOrigin);
	Ogre::MeshManager::getSingleton().createPlane(name, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
    plane, width, height, 20, 20, true, 1, 5, 5, upDir);
    
    Ogre::Entity* entGround = mSceneMgr->createEntity(name, name);
	obj->getSceneNode()->attachObject(entGround);
	
	entGround->setMaterialName(materialName);
	entGround->setCastShadows(false);
}

void RocEye::createPortraitCube(Ogre::Vector3 center, Ogre::Real diam, Ogre::String texture)
{
	RocEyeObject* obj = mObjectMgr->createObject(ObjectManager::GAME);
	Ogre::String name = getObjectBaseName(obj);
	
	Ogre::ManualObject* mo = mSceneMgr->createManualObject(name);
	
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
	for (; offset < 4 * 6; offset += 4)
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
	
	obj->getSceneNode()->attachObject(mo);
    
    obj->setPosition(center);
}

void RocEye::createPortraitPillar(Ogre::Vector3 center, Ogre::Real diam, Ogre::String texture)
{
	RocEyeObject* obj = mObjectMgr->createObject(ObjectManager::GAME);
	Ogre::String name = getObjectBaseName(obj);
	
	Ogre::ManualObject* mo = mSceneMgr->createManualObject(name);
	
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
	for (; offset < 4 * 6; offset += 4)
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
	
	obj->getSceneNode()->attachObject(mo);
    
    obj->setPosition(center);
}

void RocEye::createSphere(Ogre::Vector3 center, Ogre::String material, Ogre::Real radius, Ogre::Real stepSize)
{
	RocEyeObject* obj = mObjectMgr->createObject(ObjectManager::GAME);
	Ogre::String name = getObjectBaseName(obj);
	
	Ogre::ManualObject* mo = mSceneMgr->createManualObject(name);
	
	mo->begin(material, Ogre::RenderOperation::OT_TRIANGLE_LIST);
	
	int offset = 0; //we'll be using this to calculate vertices for the index buffer
	
	for (Ogre::Real x = -radius; x < radius; x += stepSize)
	{
		for (Ogre::Real y = -radius; y < radius; y += stepSize)
		{
			for (Ogre::Real z = -radius; z < radius; z += stepSize)
			{
				//skip any cells outside of the sphere
				if (Ogre::Vector3(x, y, z).length() > radius)
				{
					continue;
				}
				
				//check the top
				if (Ogre::Vector3(x, y + stepSize, z).length() >= radius)
				{
					mo->position(x + stepSize/2, y + stepSize/2, z + stepSize/2);
					mo->textureCoord(0,0);
					mo->position(x - stepSize/2, y + stepSize/2, z + stepSize/2);
					mo->textureCoord(1,0);
					mo->position(x + stepSize/2, y + stepSize/2, z - stepSize/2);
					mo->textureCoord(0,1);
					mo->position(x - stepSize/2, y + stepSize/2, z - stepSize/2);
					mo->textureCoord(1,1);
	
					mo->triangle(offset + 0, offset + 2, offset + 1);
					mo->triangle(offset + 1, offset + 2, offset + 3);
					//double-sided
					mo->triangle(offset + 0, offset + 1, offset + 2);
					mo->triangle(offset + 1, offset + 3, offset + 2);
					offset += 4;
				}
				
				//check the bottom
				if (Ogre::Vector3(x, y - stepSize, z).length() > radius)
				{
					mo->position(x + stepSize/2, y - stepSize/2, z + stepSize/2);
					mo->textureCoord(0,0);
					mo->position(x - stepSize/2, y - stepSize/2, z + stepSize/2);
					mo->textureCoord(1,0);
					mo->position(x + stepSize/2, y - stepSize/2, z - stepSize/2);
					mo->textureCoord(0,1);
					mo->position(x - stepSize/2, y - stepSize/2, z - stepSize/2);
					mo->textureCoord(1,1);
	
					mo->triangle(offset + 0, offset + 2, offset + 1);
					mo->triangle(offset + 1, offset + 2, offset + 3);
					//double-sided
					mo->triangle(offset + 0, offset + 1, offset + 2);
					mo->triangle(offset + 1, offset + 3, offset + 2);
					offset += 4;
				}
				
				//one of the sides
				if (Ogre::Vector3(x + stepSize, y, z).length() >= radius)
				{
					mo->position(x + stepSize/2, y + stepSize/2, z + stepSize/2);
					mo->textureCoord(0,0);
					mo->position(x + stepSize/2, y - stepSize/2, z + stepSize/2);
					mo->textureCoord(1,0);
					mo->position(x + stepSize/2, y + stepSize/2, z - stepSize/2);
					mo->textureCoord(0,1);
					mo->position(x + stepSize/2, y - stepSize/2, z - stepSize/2);
					mo->textureCoord(1,1);
	
					mo->triangle(offset + 0, offset + 2, offset + 1);
					mo->triangle(offset + 1, offset + 2, offset + 3);
					//double-sided
					mo->triangle(offset + 0, offset + 1, offset + 2);
					mo->triangle(offset + 1, offset + 3, offset + 2);
					offset += 4;
				}
				
				//one of the sides
				if (Ogre::Vector3(x - stepSize, y, z).length() > radius)
				{
					mo->position(x - stepSize/2, y + stepSize/2, z + stepSize/2);
					mo->textureCoord(0,0);
					mo->position(x - stepSize/2, y - stepSize/2, z + stepSize/2);
					mo->textureCoord(1,0);
					mo->position(x - stepSize/2, y + stepSize/2, z - stepSize/2);
					mo->textureCoord(0,1);
					mo->position(x - stepSize/2, y - stepSize/2, z - stepSize/2);
					mo->textureCoord(1,1);
	
					mo->triangle(offset + 0, offset + 2, offset + 1);
					mo->triangle(offset + 1, offset + 2, offset + 3);
					//double-sided
					mo->triangle(offset + 0, offset + 1, offset + 2);
					mo->triangle(offset + 1, offset + 3, offset + 2);
					offset += 4;
				}
				
				//one of the sides
				if (Ogre::Vector3(x, y, z + stepSize).length() >= radius)
				{
					mo->position(x + stepSize/2, y + stepSize/2, z + stepSize/2);
					mo->textureCoord(0,0);
					mo->position(x + stepSize/2, y - stepSize/2, z + stepSize/2);
					mo->textureCoord(1,0);
					mo->position(x - stepSize/2, y + stepSize/2, z + stepSize/2);
					mo->textureCoord(0,1);
					mo->position(x - stepSize/2, y - stepSize/2, z + stepSize/2);
					mo->textureCoord(1,1);
	
					mo->triangle(offset + 0, offset + 2, offset + 1);
					mo->triangle(offset + 1, offset + 2, offset + 3);
					//double-sided
					mo->triangle(offset + 0, offset + 1, offset + 2);
					mo->triangle(offset + 1, offset + 3, offset + 2);
					offset += 4;
				}
				
				//one of the sides
				if (Ogre::Vector3(x, y, z - stepSize).length() > radius)
				{
					mo->position(x + stepSize/2, y + stepSize/2, z - stepSize/2);
					mo->textureCoord(0,0);
					mo->position(x + stepSize/2, y - stepSize/2, z - stepSize/2);
					mo->textureCoord(1,0);
					mo->position(x - stepSize/2, y + stepSize/2, z - stepSize/2);
					mo->textureCoord(0,1);
					mo->position(x - stepSize/2, y - stepSize/2, z - stepSize/2);
					mo->textureCoord(1,1);
	
					mo->triangle(offset + 0, offset + 2, offset + 1);
					mo->triangle(offset + 1, offset + 2, offset + 3);
					//double-sided
					mo->triangle(offset + 0, offset + 1, offset + 2);
					mo->triangle(offset + 1, offset + 3, offset + 2);
					offset += 4;
				}
			}
		}
	}
	
	mo->end();
	
	obj->getSceneNode()->attachObject(mo);
    
    obj->setPosition(center);
}

void RocEye::createParticleSystem(Ogre::Vector3 position, Ogre::String source)
{
	RocEyeObject* obj = mObjectMgr->createObject(ObjectManager::GAME);
	Ogre::String name = getObjectBaseName(obj);
	
	Ogre::ParticleSystem* system = mSceneMgr->createParticleSystem(name, source);
	//we're going to be moving particle systems around in order to place them, and we don't want bounding boxes expanding (at least, not if they stay expanded)
	system->setKeepParticlesInLocalSpace(true);
	
	obj->getSceneNode()->attachObject(system);
	obj->setPosition(position);
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
