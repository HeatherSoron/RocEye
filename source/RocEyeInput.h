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
	
	InputHandler* mHandler;
};

#endif
