#include "RocEyeGui.h"

RocEyeGui::RocEyeGui(void)
	:
	mSilverback(NULL),
	mCrosshairLayer(NULL),
	mCrosshair(NULL),
	mViewport(NULL),
	mSceneMgr(NULL)
{
}

RocEyeGui::~RocEyeGui(void)
{
	delete mSilverback;
}

void RocEyeGui::initialise(Ogre::SceneManager* sceneMgr, Ogre::Viewport* viewport)
{
	mSilverback = new Gorilla::Silverback();
	mSilverback->loadAtlas("dejavu");
	mViewport = viewport;
	mSceneMgr = sceneMgr;
	
	mHUD = mSilverback->createScreen(mViewport, "dejavu");
	mHUDLayer = mHUD->createLayer();
	
	mCrosshairLayer = mHUD->createLayer();
	mCrosshair = mCrosshairLayer->createRectangle((mViewport->getActualWidth() * 0.5f) - 11, (mViewport->getActualHeight() * 0.5f) - 11, 22, 22);
	mCrosshair->background_image("crosshair");
}
