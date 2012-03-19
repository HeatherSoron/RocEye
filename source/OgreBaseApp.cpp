#include "OgreBaseApp.h"

#include <OgreException.h>
#include <OgreEntity.h>
#include <OgreWindowEventUtilities.h>

//-------------------------------------------------------------------------------------
OgreBaseApp::OgreBaseApp(void)
	:
		mRoot(0),
		mWindow(0),
		mPluginsCfg(Ogre::StringUtil::BLANK),
		mResourcesCfg(Ogre::StringUtil::BLANK),
		mMovementVector(0,0,0),
		mRoll(0)
{
}
//-------------------------------------------------------------------------------------
OgreBaseApp::~OgreBaseApp(void)
{
	Ogre::WindowEventUtilities::removeWindowEventListener(mWindow, this);
	windowClosed(mWindow);
	delete mRoot;
}

bool OgreBaseApp::setup(void)
{
	//construct the Ogre::Root object
	mRoot = new Ogre::Root(mPluginsCfg);

	//set up resources
	Ogre::ConfigFile cf;
	cf.load(mResourcesCfg);

	//go through all the sections and settings in the file
	Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();

	Ogre::String secName, typeName, archName;
	while (seci.hasMoreElements())
	{
		secName = seci.peekNextKey();
		Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator i;
		for (i = settings->begin(); i != settings->end(); ++i)
		{
			typeName = i->first;
			archName = i->second;
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(archName, typeName, secName);
		}
	}

	//configure
	//first try to restore the config, if that fails, ask the user, and if they cancel out of that, quit the program
	if ( !(mRoot->restoreConfig() || mRoot->showConfigDialog()) )
	{
		return false;
	}
	
	return true;
}

bool OgreBaseApp::go(void)
{
#ifdef _DEBUG
	mPluginsCfg = "plugins_d.cfg";
	mResourcesCfg = "resources_d.cfg";
#else
	mPluginsCfg = "plugins.cfg";
	mResourcesCfg = "resources.cfg";
#endif

	if (!setup()) return false;

	//just have Ogre create our window for us
	mWindow = mRoot->initialise(true, "OgreBaseApp Render Window");
	

	//set the default mipmap level
	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
	//initialize the resource groups
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

	mSceneMgr = mRoot->createSceneManager("DefaultSceneManager");
	
	createCamera();
	createViewport();
	
	createScene();
	
	setupInput();

	//set initial mouse clipping area
	windowResized(mWindow);

	//register this app as a window listener
	Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);

	mRoot->addFrameListener(this);

	mRoot->startRendering();

	return true;
}

void OgreBaseApp::createCamera(void)
{
	mCamera = mSceneMgr->createCamera("PlayerCam");

	//look back along -z
	mCamera->lookAt(Ogre::Vector3(0,0,-300));
	mCamera->setNearClipDistance(5);
	
	mCameraNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	mCameraNode->attachObject(mCamera);
	
	//position the camera at 80 along the z axis
	mCameraNode->setPosition(Ogre::Vector3(0,0,80));
}

void OgreBaseApp::createViewport(void)
{	
	//create a whole-window viewport
	mViewport = mWindow->addViewport(mCamera);
	mViewport->setBackgroundColour(Ogre::ColourValue(0,0,0));

	//make sure the camera aspect ratio matches the viewport's
	mCamera->setAspectRatio(Ogre::Real(mViewport->getActualWidth()) / Ogre::Real(mViewport->getActualHeight()));
}

void OgreBaseApp::setupInput(void)
{
	//set up OIS for input handling
	Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");
	OIS::ParamList pl;
	size_t windowHnd = 0;
	std::ostringstream windowHndStr;

	mWindow->getCustomAttribute("WINDOW", &windowHnd);
	windowHndStr << windowHnd;
	pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

	mInputManager = OIS::InputManager::createInputSystem(pl);
	//get unbuffered input here (set that last param to true for buffered input)
	mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject(OIS::OISKeyboard, true));
	mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject(OIS::OISMouse, true));
	
	mMouse->setEventCallback(this);
	mKeyboard->setEventCallback(this);
}

//adjust mouse clipping area
void OgreBaseApp::windowResized(Ogre::RenderWindow* rw)
{
	unsigned int width, height, depth;
	int left, top;
	rw->getMetrics(width, height, depth, left, top);

	const OIS::MouseState &ms = mMouse->getMouseState();
	ms.width = width;
	ms.height = height;
}

//unattach OIS before window shutdown (very important under Linux)
void OgreBaseApp::windowClosed(Ogre::RenderWindow* rw)
{
	//only close for window that created OIS (the main window in these demos)
	if (rw == mWindow)
	{
		if (mInputManager)
		{
			mInputManager->destroyInputObject(mMouse);
			mInputManager->destroyInputObject(mKeyboard);

			OIS::InputManager::destroyInputSystem(mInputManager);
			mInputManager = 0;
		}
	}
}

bool OgreBaseApp::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
	if (mWindow->isClosed())
	{
		return false;
	}

	//need to capture/update each device
	mKeyboard->capture();
	mMouse->capture();

	if (mKeyboard->isKeyDown(OIS::KC_ESCAPE))
	{
		return false;
	}
	
	//update camera position
	moveCamera();

	return true;
}

void OgreBaseApp::moveCamera()
{
	mCameraNode->translate(mMovementVector, Ogre::SceneNode::TS_LOCAL);
	mCameraNode->roll(Ogre::Degree(mRoll), Ogre::SceneNode::TS_LOCAL);
}

bool OgreBaseApp::mousePressed(const OIS::MouseEvent& evt, OIS::MouseButtonID id)
{
	return true;
}
 
bool OgreBaseApp::mouseReleased(const OIS::MouseEvent& evt, OIS::MouseButtonID id)
{
	return true;
}
 
bool OgreBaseApp::mouseMoved(const OIS::MouseEvent& evt)
{
	mCameraNode->yaw(Ogre::Degree(-evt.state.X.rel * mRotateSpeed));
    mCameraNode->pitch(Ogre::Degree(-evt.state.Y.rel * mRotateSpeed));
	return true;
}
 
bool OgreBaseApp::keyPressed(const OIS::KeyEvent& evt)
{
	switch(evt.key)
	{
		case OIS::KC_W:
			mMovementVector.z = -mCameraSpeed;
			break;
		case OIS::KC_S:
			mMovementVector.z = mCameraSpeed;
			break;
		case OIS::KC_A:
			mMovementVector.x = -mCameraSpeed;
			break;
		case OIS::KC_D:
			mMovementVector.x = mCameraSpeed;
			break;
		case OIS::KC_R:
			mMovementVector.y = mCameraSpeed;
			break;
		case OIS::KC_F:
			mMovementVector.y = -mCameraSpeed;
			break;
		
		case OIS::KC_E:
			mRoll = -mRollSpeed;
			break;
		case OIS::KC_Q:
			mRoll = mRollSpeed;
			break;
	}
	
	return true;
}
 
bool OgreBaseApp::keyReleased(const OIS::KeyEvent& evt)
{
	switch(evt.key)
	{
		case OIS::KC_W:
			mMovementVector.z = 0;
			break;
		case OIS::KC_S:
			mMovementVector.z = 0;
			break;
		case OIS::KC_A:
			mMovementVector.x = 0;
			break;
		case OIS::KC_D:
			mMovementVector.x = 0;
			break;
		case OIS::KC_R:
			mMovementVector.y = 0;
			break;
		case OIS::KC_F:
			mMovementVector.y = 0;
			break;
			
		
		case OIS::KC_E:
			mRoll = 0;
			break;
		case OIS::KC_Q:
			mRoll = 0;
			break;
	}
	
	return true;
}
