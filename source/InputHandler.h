#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <Ogre.h>

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
	
	void setCamera(Ogre::SceneNode* mCameraNode);
	
	void translate(Direction dir);
	void rotate(Direction rot, bool isMouse = false, float mult = 1);
	void changeSpeed(float numSteps); //has to be called every frame, or it'll return to normal speed
	
	void resetCamera(void); //makes the camera point down. Note that this is still buffered, and overrides rotations
	
	void execute(void);
	
    static const Ogre::Real mCameraSpeed = 4; //the speed of our camera
    static const Ogre::Real mMouseRotateSpeed = 0.2;
    static const Ogre::Real mKeyRotateSpeed = 2;
    static const Ogre::Real SPEED_PER_STEP = 5; //gets multiplied with stuff
    
protected:
	void resetState(void);
	
	bool mCameraNeedsReset;
	Ogre::Vector3 mTransVector;
	Ogre::Vector3 mRotVector; // pitch/yaw/roll are stored on the corresponding axis (be sure to convert to degrees!)
	Ogre::Real mSpeedMult;
	
	Ogre::SceneNode* mCameraNode;
};
#endif
