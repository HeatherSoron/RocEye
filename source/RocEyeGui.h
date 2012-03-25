#ifndef ROC_EYE_GUI_H
#define ROC_EYE_GUI_H

#include "Gorilla.h"
#include "OgreConsoleForGorilla.h"

class RocEyeGui
{
public:
	RocEyeGui(void);
	virtual ~RocEyeGui(void);
	
	virtual void initialise(Ogre::SceneManager* sceneMgr, Ogre::Viewport* viewport);
	virtual void update(Ogre::SceneNode* cameraNode);
	
	virtual void activateConsole(void) { mConsole.setVisible(true); };
	virtual bool isConsoleActive(void) { return mConsole.isVisible(); };
	virtual bool sendConsoleMessage(Ogre::String keyName) { mConsole.onKeyPressed(keyName); return true; };
	
protected:
  Gorilla::Silverback*    mSilverback;
  Gorilla::Screen*        mHUD;
  Gorilla::Layer*         mHUDLayer;
  Gorilla::Layer*         mCrosshairLayer;
  Gorilla::Rectangle*     mCrosshair;
  
  Gorilla::Caption* mXReadout;
  Gorilla::Caption* mYReadout;
  Gorilla::Caption* mZReadout;
  
  OgreConsole mConsole;
  
  Ogre::Viewport* mViewport;
  Ogre::SceneManager* mSceneMgr;
};

#endif
