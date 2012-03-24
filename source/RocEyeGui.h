#ifndef ROC_EYE_GUI_H
#define ROC_EYE_GUI_H

#include "Gorilla.h"

class RocEyeGui
{
public:
	RocEyeGui(void);
	virtual ~RocEyeGui(void);
	
	virtual void initialise(Ogre::SceneManager* sceneMgr, Ogre::Viewport* viewport);
protected:
  Gorilla::Silverback*    mSilverback;
  Gorilla::Screen*        mHUD;
  Gorilla::Layer*         mHUDLayer;
  Gorilla::Layer*         mCrosshairLayer;
  Gorilla::Rectangle*     mCrosshair;
  
  Ogre::Viewport* mViewport;
  Ogre::SceneManager* mSceneMgr;
};

#endif
