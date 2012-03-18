#ifndef OGRE_BASE_APP_H
#define OGRE_BASE_APP_H

#include <OgreRoot.h>
#include <OgreConfigFile.h>
#include <OgreRenderWindow.h>
#include <OgreCamera.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

#include <SdkCameraMan.h>

#include <OgreWindowEventUtilities.h>

class OgreBaseApp : public Ogre::WindowEventListener, public Ogre::FrameListener, public OIS::KeyListener, public OIS::MouseListener
{
public:
    OgreBaseApp(void);
    virtual ~OgreBaseApp(void);
    bool go(void);

protected:
    //from Ogre::WindowEventListener
    virtual void windowResized(Ogre::RenderWindow* rw);
    virtual void windowClosed(Ogre::RenderWindow* rw);
    //from Ogre::FrameListener
    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
    virtual bool mousePressed(const OIS::MouseEvent& evt, OIS::MouseButtonID id);
    virtual bool mouseReleased(const OIS::MouseEvent& evt, OIS::MouseButtonID id);
    virtual bool mouseMoved( const OIS::MouseEvent &arg );
    virtual bool keyPressed(const OIS::KeyEvent& evt);
    virtual bool keyReleased(const OIS::KeyEvent& evt);
    
    virtual bool setup(void);
    virtual void createCamera(void);
    virtual void createViewport(void);
    virtual void setupInput(void);
    
    virtual void createScene(void) = 0;
	
    Ogre::Root* mRoot;
    Ogre::String mPluginsCfg;
    Ogre::String mResourcesCfg;
    Ogre::RenderWindow* mWindow;
    Ogre::SceneManager* mSceneMgr;
    Ogre::Camera* mCamera;
    Ogre::Viewport* mViewport;
    
    // OgreBites
    OgreBites::SdkCameraMan* mCameraMan;       // basic camera controller

    OIS::InputManager* mInputManager;
    OIS::Mouse* mMouse;
    OIS::Keyboard* mKeyboard;
    
private:
};

#endif
