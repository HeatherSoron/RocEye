#ifndef ROC_EYE_INPUT_H
#define ROC_EYE_INPUT_H

#include "BaseAppInput.h"
#include "InputHandler.h"
#include "InputParser/InteractionBridge.h"
#include "InputParser/InteractionController.h"

class RocEyeInput : public BaseAppInput
{
public:
	RocEyeInput(int width, int height);
	virtual ~RocEyeInput(void);
	
	virtual void setHandler(InputHandler* handler);
	
protected:
	virtual KeyArray* handleKeyboard(KeyArray*); // Do not free the return value.
	virtual bool handleMouse(void);
	virtual void frameDone(void);
	
	//just going to overwrite the left button for now
	virtual bool fireLeftMouseDown(void);
	virtual bool fireLeftMouseUp(void);
	
	virtual bool onKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
	virtual bool onKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);
	
	virtual bool runFrameInternal();
	
	__RocEye__::MasterInteractionController* mController;
	
	int mWindowWidth;
	int mWindowHeight;
	
	InputHandler* mHandler;
};

#endif
