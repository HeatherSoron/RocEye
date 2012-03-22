#include "OgreBaseApp.h"

#include <OgreException.h>
#include <OgreEntity.h>
#include <OgreWindowEventUtilities.h>

#include "BaseAppInput.h"

#include <iostream>

//-------------------------------------------------------------------------------------
OgreBaseApp::OgreBaseApp(void)
	:
		mRoot(0),
		mWindow(0),
		mPluginsCfg(Ogre::StringUtil::BLANK),
		mResourcesCfg(Ogre::StringUtil::BLANK),
		mWindowWidth(640),
		mWindowHeight(480)
{
}
//-------------------------------------------------------------------------------------
OgreBaseApp::~OgreBaseApp(void)
{
/*
	Ogre::WindowEventUtilities::removeWindowEventListener(mWindow, this);
	windowClosed(mWindow);
*/
	delete mRoot;
	delete mInput;
	
	SDL_Quit();
}

bool OgreBaseApp::setup(void)
{
	std::ifstream videoFile;
	videoFile.open("screen_size.cfg");
	if (videoFile.good())
	{
		std::string width, height;
		getline(videoFile, width);
		getline(videoFile, height);
		
		mWindowWidth = atoi(width.c_str());
		mWindowHeight = atoi(height.c_str());
	}
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Surface *screen = SDL_SetVideoMode(mWindowWidth, mWindowHeight, 0, SDL_OPENGL);
	
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
	
	mRoot->initialise(false); //do NOT create a window
	
	//connect SDL and Ogre here
	Ogre::NameValuePairList misc;
#ifdef WINDOWS
	SDL_SysWMinfo wmInfo;
	SDL_VERSION(&wmInfo.version);
	SDL_GetWMInfo(&wmInfo);
	
	size_t winHandle = reinterpret_cast<size_t>(wmInfo.window);
	size_t winGlContext = reinterpret_cast<size_t>(wmInfo.hglrc);
	
	misc["externalWindowHandle"] = StringConverter::toString(winHandle);
	misc["externalGLContext"] = StringConverter::toString(winGlContext);
#else
	misc["currentGLContext"] = Ogre::String("True");
#endif
	
	//NOW we make a RenderWindow!
	mWindow = mRoot->createRenderWindow("MainRenderWindow", mWindowWidth, mWindowHeight, false, &misc);
	mWindow->setVisible(true);
	
	//just have Ogre create our window for us
	//mWindow = mRoot->initialise(true, "OgreBaseApp Render Window");
	

	//set the default mipmap level
	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
	//initialize the resource groups
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

	mSceneMgr = mRoot->createSceneManager("DefaultSceneManager");
	
	createCamera();
	createViewport();
	
	createScene();
	
	setupInput();

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
	mInput = new BaseAppInput();
}

bool OgreBaseApp::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
	if (mWindow->isClosed())
	{
		return false;
	}
	
	if (! mInput->runFrame() )
	{
		return false;
	}
	
	SDL_GL_SwapBuffers();
	
	return true;
}
