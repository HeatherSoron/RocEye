#include "RocEyeGui.h"

RocEyeGui::RocEyeGui(void)
	:
	mSilverback(NULL),
	mCrosshairLayer(NULL),
	mCrosshair(NULL),
	mXReadout(NULL),
	mYReadout(NULL),
	mZReadout(NULL),
	
	mConsole(),
	
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
	
	mConsole.init(mHUD);
	mConsole.setVisible(false);
	
	mCrosshairLayer = mHUD->createLayer();
	mCrosshair = mCrosshairLayer->createRectangle((mViewport->getActualWidth() * 0.5f) - 11, (mViewport->getActualHeight() * 0.5f) - 11, 22, 22);
	mCrosshair->background_image("crosshair");
	
	mXReadout = mHUDLayer->createCaption(24, 0, 0, "");
	mXReadout->width(mViewport->getActualWidth()-16);
	mXReadout->height(mViewport->getActualHeight()-68);
	mXReadout->vertical_align(Gorilla::VerticalAlign_Bottom);
	
	mYReadout = mHUDLayer->createCaption(24, 0, 0, "");
	mYReadout->width(mViewport->getActualWidth()-16);
	mYReadout->height(mViewport->getActualHeight()-36);
	mYReadout->vertical_align(Gorilla::VerticalAlign_Bottom);
	
	mZReadout = mHUDLayer->createCaption(24, 0, 0, "");
	mZReadout->width(mViewport->getActualWidth()-16);
	mZReadout->height(mViewport->getActualHeight()-4);
	mZReadout->vertical_align(Gorilla::VerticalAlign_Bottom);
}

void RocEyeGui::update(Ogre::SceneNode* cameraNode)
{
	const Ogre::Vector3 position = cameraNode->getPosition();
	
	char x[32];
	sprintf(x, "X: %d", static_cast<int>(position.x));
	
	char y[32];
	sprintf(y, "Y: %d", static_cast<int>(position.y));
	
	char z[32];
	sprintf(z, "Z: %d", static_cast<int>(position.z));
	
	mXReadout->text(x);
	mYReadout->text(y);
	mZReadout->text(z);
}
