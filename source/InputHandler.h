#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <Ogre.h>
#include "GridLineFactory.h"

class InputHandler
{
public:
	InputHandler(void);
	virtual ~InputHandler(void);
	
	enum Direction
    {
    	DIR_FORWARD,
    	DIR_BACKWARD,
    	DIR_LEFT,
    	DIR_RIGHT,
    	DIR_UP,
    	DIR_DOWN,
    	ROT_LEFT,
    	ROT_RIGHT,
    	ROT_UP,
    	ROT_DOWN,
    	ROT_CCW,
    	ROT_CW
    };
	
	virtual void setCamera(Ogre::Camera* mCamera);
	
	virtual void translate(Direction dir);
	virtual void rotate(Direction rot, bool isMouse = false, float mult = 1);
	virtual void changeSpeed(float numSteps); //has to be called every frame, or it'll return to normal speed
	
	virtual void resetCamera(void); //makes the camera point down. Note that this is still buffered, and overrides rotations
	
	virtual void centerObject(void);
	virtual void toggleObjectLock(void);
	
	virtual void levelHorizon(void);
	virtual void toggleHorizonLock(void);
	
	//we're not calling this "left mouse down", because we might port to iOS or something eventually
	//and yes, an iOS port HAS been requested
	virtual bool onPrimaryPointerDown(void);
	virtual bool onPrimaryPointerUp(void);
	
	virtual void toggleObjectMode(void);
	
	virtual void toggleGridLines(bool centerOnTarget);
	
	virtual void execute(void);
	
    static const Ogre::Real mCameraSpeed = 4; //the speed of our camera
    static const Ogre::Real mMouseRotateSpeed = 0.2;
    static const Ogre::Real mKeyRotateSpeed = 2;
    static const Ogre::Real SPEED_PER_STEP = 5; //gets multiplied with stuff
    
protected:
	virtual void resetState(void);
	virtual void clickOnObjects(void);
	virtual void tryPickObjects(void);
	virtual void selectObject(Ogre::SceneNode* object);
	virtual void deselectObject(void);
	
	bool mPointerDown;
	bool mPickingMeshes;
	
	bool mCameraNeedsReset;
	Ogre::Vector3 mTransVector;
	Ogre::Vector3 mRotVector; // pitch/yaw/roll are stored on the corresponding axis (be sure to convert to degrees!)
	Ogre::Real mSpeedMult;
	bool mCenterObject;
	bool mTracking;
	bool mHorizonLocked;
	
	Ogre::RaySceneQuery* mRaySceneQuery;
	Ogre::SceneManager* mSceneMgr;
	
	Ogre::Camera* mCamera;
	
	Ogre::SceneNode* mSelectedObject;
	
	GridLineFactory* mGridLineFactory;
};
#endif
