#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <Ogre.h>
#include "GridLineFactory.h"
#include "ObjectManager.h"
#include "RocEyeGui.h"

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
	virtual void setObjectManager(ObjectManager* manager) { mObjectMgr = manager; };
	virtual void setGui(RocEyeGui* gui) { mGui = gui; addConsoleCommands(); };
	
	virtual void activateConsole(void) { mGui->activateConsole(); };
	virtual bool isConsoleActive(void) { return mGui->isConsoleActive(); };
	virtual bool sendConsoleMessage(Ogre::String keyName) { return mGui->sendConsoleMessage(keyName); };
	virtual void toggleConsole(void) { mGui->toggleConsole(); };
	
	virtual void setCameraPosition(Ogre::Vector3 point) { mCamera->getParentSceneNode()->setPosition(point); };
	
	virtual void translate(Direction dir);
	virtual void rotate(Direction rot, bool isMouse = false, float mult = 1);
	virtual void changeSpeed(float numSteps); //has to be called every frame, or it'll return to normal speed
	
	virtual void resetCamera(void); //makes the camera point down. Note that this is still buffered, and overrides rotations
	
	virtual void centerObject(void);
	virtual void toggleObjectLock(void);
	virtual void toggleMovementTarget(void) { mReverseMovementTarget = !mReverseMovementTarget; }; //switches between controlling the camera and the selected object
	
	virtual void levelHorizon(void);
	virtual void toggleHorizonLock(void);
	
	virtual void toggleSnapToGrid(void);
	
	//we're not calling this "left mouse down", because we might port to iOS or something eventually
	//and yes, an iOS port HAS been requested
	virtual bool onPrimaryPointerDown(void);
	virtual bool onPrimaryPointerUp(void);
	
	virtual void toggleObjectMode(void);
	
	virtual void toggleGridLines(bool centerOnTarget);
	virtual void setCellNumber(unsigned int count) { mGridLineFactory->setCellNumber(count); };
	
	
	virtual void execute(void);
	
    static const int mCameraSpeed = 4; //the speed of our camera
    static const int mMouseRotateSpeedDivisor = 5;
    static const int mKeyRotateSpeed = 2;
    static const int SPEED_PER_STEP = 5; //gets multiplied with stuff
    
protected:
	virtual void resetState(void);
	virtual void clickOnObjects(void);
	virtual void tryPickObjects(void);
	virtual void selectObject(Ogre::SceneNode* object);
	virtual void deselectObject(void);
	
	virtual void addConsoleCommands(void);
	
	bool mPointerDown;
	bool mPickingMeshes;
	
	bool mCameraNeedsReset;
	Ogre::Vector3 mTransVector;
	Ogre::Vector3 mRotVector; // pitch/yaw/roll are stored on the corresponding axis (be sure to convert to degrees!)
	Ogre::Real mSpeedMult;
	bool mCenterObject;
	bool mTracking;
	bool mHorizonLocked;
	bool mReverseMovementTarget;
	
	Ogre::RaySceneQuery* mRaySceneQuery;
	Ogre::SceneManager* mSceneMgr;
	ObjectManager* mObjectMgr;
	
	Ogre::Camera* mCamera;
	
	RocEyeObject* mSelectedObject;
	
	GridLineFactory* mGridLineFactory;
	
	RocEyeGui* mGui;
};
#endif
