#ifndef OGRE_BASE_APP_H
#define OGRE_BASE_APP_H

#include <Ogre.h>
#include <OgreRoot.h>
#include <OgreException.h>
#include <OgreEntity.h>
#include <OgreWindowEventUtilities.h>
#include <OgreConfigFile.h>
#include <OgreRenderWindow.h>
#include <OgreCamera.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreMeshManager.h>

#include "BaseAppInput.h"

class OgreBaseApp : public Ogre::FrameListener
{
public:
    OgreBaseApp(void);
    virtual ~OgreBaseApp(void);
    bool go(void);

protected:
    //from Ogre::FrameListener
    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
    
    virtual bool setup(void);
    virtual void createCamera(void);
    virtual void createViewport(void);
    virtual void setupInput(void);
    
    virtual void createScene(void) {};
    
    BaseAppInput* mInput;
	
    Ogre::Root* mRoot;
    Ogre::String mPluginsCfg;
    Ogre::String mResourcesCfg;
    Ogre::RenderWindow* mWindow;
    Ogre::SceneManager* mSceneMgr;
    Ogre::SceneNode* mCameraNode;
    Ogre::Camera* mCamera;
    Ogre::Viewport* mViewport;
    
    int mWindowWidth;
    int mWindowHeight;
    
private:
};

#endif
