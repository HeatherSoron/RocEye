#ifndef KEYBOARD_STATE_H
#define KEYBOARD_STATE_H

#define FOR_ALL_KEYS(x) for(int x = 0; x < _numKeys ; ++x)
class KeyboardState
{
public:
	KeyboardState()
	{
		Uint8* initialKeys=SDL_GetKeyState(&_numKeys); // sets numKeys
		_keys=new Uint8[_numKeys];
		FOR_ALL_KEYS(i)
			_keys[i]=(initialKeys[i]?3:0);
		// For initial state, I use 3=2|1, indicating that the keys are considered to have just been pressed
	}
	~KeyboardState()
	{
		delete[](_keys);
	}
	
	inline void UpdateForKeyDown(Uint16 key)
	{
		_keys[key]|=5; // 5=4|1 = touched this frame and down.
	}
	inline void UpdateForKeyUp(Uint16 key)
	{
		_keys[key]|=4; // touched this frame
		_keys[key]&=0xFE; // unset just the 1 bit
	}
	inline void UpdateBeforeFrame()
	{
		FOR_ALL_KEYS(i)
		{
			_keys[i]&=0xFB; // unset the 4 bit for this frame.
			if(_keys[i]&1)
				_keys[i]|=2; // If it is down before this frame, then it was down last frame, so set that.
			else if(_keys[i]==2)
				_keys[i]=0;
		}
	}
	
	inline Uint8* GetKeyArray()
	{
		return _keys;
	}
	
	static const Uint8 KEY_DOWN_MODE=   4  |1;
	static const Uint8 KEY_UP_MODE=     4|2;
	static const Uint8 KEY_DOWN_UP_MODE=4; // this is a down+up in one round.
	static const Uint8 KEY_REPEAT_MODE= 2|1;
	
	static const Uint8 MODIFIER_KEY_MODE=0;    // this has to be 0 to work
	static const Uint8 NO_MODIFIER_KEY_MODE=8; // Any orthogonal bit
private:
	int _numKeys;
	Uint8* _keys;
	// each key is a bitmask of the following bits:
	// 1: the key was down when this frame was calculating
	// 2: the key was down when the last frame was calculating
	// 4: the key was touched this frame (needed to detect down-and-up within one frame)

}; // KeyboardState

#undef FOR_ALL_KEYS
#endif
