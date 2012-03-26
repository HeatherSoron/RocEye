#ifndef INTERACTION_STATE_H
#define INTERACTION_STATE_H

#include "../BaseAppInput.h"

namespace __RocEye__
{
class InteractionState{
public:
	Uint8* keys;
	Uint8 mouseButtons;
	int mouse_dx;
	int mouse_dy; // Note: This is internally normalized to up as positive!
	
	InteractionState(int screenWidth,int screenHeight) // ToDo use a Dimension. Or a global!
	{
		keys=SDL_GetKeyState(NULL);
		mouseButtons=SDL_GetMouseState(&mouse_dx,&mouse_dy);
		mouse_dx=screenWidth-mouse_dx;
		mouse_dy-=screenHeight;
	}
	
	InteractionState(Uint8* keyAr, int screenWidth,int screenHeight) // ToDo use a Dimension. Or a global!
	{
		keys=keyAr;
		mouseButtons=SDL_GetMouseState(&mouse_dx,&mouse_dy);
		mouse_dx=screenWidth-mouse_dx;
		mouse_dy-=screenHeight;
	}
	~InteractionState(){}
	

}; // class InteractionState
} // namespace __RocEye__

#endif // INTERACTION_STATE_H
