#ifndef ROC_EYE_H
#define ROC_EYE_H

#include "OgreBaseApp.h"
#include "InputHandler.h"
#include "RocEyeInput.h"

class RocEye : public OgreBaseApp
{
public:
	RocEye(void);
	~RocEye(void);

protected:
	virtual void setupInput(void);
	
	virtual void createScene(void);
	
    virtual void loadSceneFile(void);
    virtual void createEntity(Ogre::String mesh, Ogre::Vector3 pos);
    virtual void createPlane(Ogre::Vector3 normal, Ogre::Real distFromOrigin, Ogre::Real width, Ogre::Real height, Ogre::String materialName, Ogre::Vector3 upDir);
    virtual void createPortraitCube(Ogre::Vector3 center, Ogre::Real diam, Ogre::String texture);
    virtual void createPortraitPillar(Ogre::Vector3 center, Ogre::Real diam, Ogre::String texture);
    virtual void createParticleSystem(Ogre::Vector3 position, Ogre::String source);
	virtual void createPointLight(Ogre::Vector3 position, Ogre::ColourValue dColour, Ogre::ColourValue sColour);
	virtual void createDirectionalLight(Ogre::Vector3 direction, Ogre::ColourValue dColour, Ogre::ColourValue sColour);
	virtual void createSpotLight(Ogre::Vector3 position, Ogre::Vector3 direction, Ogre::ColourValue dColour, Ogre::ColourValue sColour, Ogre::Degree innerAngle, Ogre::Degree outerAngle);
	
	InputHandler mHandler;
};

#endif
