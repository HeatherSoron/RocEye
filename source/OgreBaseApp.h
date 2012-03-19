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

// OGRE initialization:
#ifdef WIN32
//Necessary to tell the mouse events to go to this window
#if (_WIN32_WINNT < 0x0501)
#undef _WIN32_WINNT
#define _WIN32_WINNT 0x0501
#endif
// Necessary to get the Window Handle of the window
// OGRE created, so SDL can grab its input.
#include "windows.h"
#include "SDL_getenv.h"
#endif
 
// SDL initialization:
#include "SDL/SDL.h"
#include "SDL/SDL_syswm.h"
#include "SDL/SDL_keyboard.h"

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
	
    Ogre::Root* mRoot;
    Ogre::String mPluginsCfg;
    Ogre::String mResourcesCfg;
    Ogre::RenderWindow* mWindow;
    Ogre::SceneManager* mSceneMgr;
    Ogre::SceneNode* mCameraNode;
    Ogre::Camera* mCamera;
    Ogre::Viewport* mViewport;
    
    Ogre::Vector3 mMovementVector; //used to manually translate the camera
    Ogre::Real mRoll;
    static const Ogre::Real mCameraSpeed = 4; //the speed of our camera
    static const Ogre::Real mMouseRotateSpeed = 0.2;
    static const Ogre::Real mKeyRotateSpeed = 2;
    
private:
};

#endif
