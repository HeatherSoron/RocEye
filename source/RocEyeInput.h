#ifndef ROC_EYE_INPUT_H
#define ROC_EYE_INPUT_H

#include "BaseAppInput.h"
#include "InputHandler.h"

class RocEyeInput : public BaseAppInput
{
public:
	RocEyeInput(void);
	virtual ~RocEyeInput(void);
	
	virtual void setHandler(InputHandler* handler);
	
protected:
	virtual bool handleKeyboard(void);
	virtual bool handleMouse(void);
	virtual void frameDone(void);
	
	//just going to overwrite the left button for now
	virtual bool fireLeftMouseDown(void);
	virtual bool fireLeftMouseUp(void);
	
	bool mWasKeyDownO;
	bool mWasKeyDownH;
	
	InputHandler* mHandler;
};

#endif
