#include "RocEyeInput.h"
#include "InputParser/InteractionState.h"

RocEyeInput::RocEyeInput(int width, int height) : BaseAppInput(),
	mController(__RocEye__::InteractionBridgeDictionary::InitializeInput()),
	mWindowWidth(width),
	mWindowHeight(height),
	mHandler(NULL)
{
}

RocEyeInput::~RocEyeInput(void)
{
	delete(mController);
}

void RocEyeInput::setHandler(InputHandler* handler)
{
	mHandler = handler;
}

KeyArray* RocEyeInput::handleKeyboard(KeyArray* keys)
{
	if (!BaseAppInput::handleKeyboard(keys))
	{
		return NULL;
	}
	if (!keys)
	{
		keys = SDL_GetKeyState(NULL);
	}
	return keys;
}
bool RocEyeInput::runFrameInternal()
{
	__RocEye__::InteractionState state=__RocEye__::InteractionState(mKeyState.GetKeyArray(),mWindowWidth,mWindowHeight);
	
	if(mController->ExecuteIfNameMatches("TOGGLECONSOLE",mHandler,&state)) // ensure that this guy gets first dibs.
	   return true;
	if(mHandler->isConsoleActive())
		return true;
	mController->Execute(mHandler,&state);
	return true;
}
bool RocEyeInput::onKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode)
{	
	static const SDLKey consoleToggle = SDLK_F1;
	
	if (mHandler->isConsoleActive() && sym != consoleToggle) //MAKE SURE that you catch the consoleToggle here
	{
		return mHandler->sendConsoleMessage(SDL_GetKeyName(sym)); //return so that we don't send spurious signals to the input handler
	}
	
	switch (sym)
	{
		default:
		{
			//un-implemented key if we get here
			break;
		}
	}
	
	return true;
}

bool RocEyeInput::onKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode)
{	

	switch (sym)
	{
		default:
		{
			//un-implemented key
			break;
		}
	}
	
	return true;
}

bool RocEyeInput::handleMouse(void)
{
	if (! BaseAppInput::handleMouse() )
	{
		return false;
	}
	
	const int CENTER_X = mWindowWidth/2;
	const int CENTER_Y = mWindowHeight/2;
	
	int x, y;
	SDL_GetMouseState(&x,&y);
	
	//deltas
	int dx = x - CENTER_X;
	int dy = y - CENTER_Y;
	
	
	mHandler->rotate(InputHandler::ROT_RIGHT, true, dx);
    mHandler->rotate(InputHandler::ROT_UP, true, -dy);	
    
	
	//ideally, we would tell SDL to use relative mouse mode directly. Unfortunately, that seems not to be present in 1.2.15? At least, the Linux header I have doesn't seem to have SDL_SetRelativeMouseMode.
	if (dx || dy)
	{
		SDL_WarpMouse(CENTER_X, CENTER_Y);
	}
	return true;
}

bool RocEyeInput::fireLeftMouseDown(void)
{
	return mHandler->onPrimaryPointerDown();	
}

bool RocEyeInput::fireLeftMouseUp(void)
{
	return mHandler->onPrimaryPointerUp();
}

void RocEyeInput::frameDone(void)
{
	BaseAppInput::frameDone();
	
	mHandler->execute(); //need to tell our input handler to actually run what we told it to do
}
