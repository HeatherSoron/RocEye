#include "InteractionBooleanNode.h"
#include "InputMethodParser.h"

namespace __RocEye__
{	
	inline bool InteractionBooleanNodeKeyboard::Evaluate(const InteractionState* state,bool,bool)
	{
		Uint8 r=state->keys[_key];
		if(!_mode)return r; // for modifiers
		if(_mode==KeyboardState::NO_MODIFIER_KEY_MODE)return !r; // for no modifiers
		return r==_mode;
	}
	InteractionBooleanNodeKeyboard::InteractionBooleanNodeKeyboard(std::string s,Uint8 mode):InteractionBooleanNode()
	{
		if(!mode || mode==KeyboardState::NO_MODIFIER_KEY_MODE)
			_key=InputMethodParser::GetKeycodeForStringModifier(s);
		else
			_key=InputMethodParser::GetKeycodeForStringKey(s);
		_mode=mode;
	}
} // namespace __RocEye__
