#include "InteractionBooleanNode.h"
#include "InputMethodParser.h"

#include <iostream>
namespace __RocEye__
{	
	inline bool InteractionBooleanNodeKeyboard::Evaluate(const InteractionState* state,bool,bool)
	{
		return state->keys[_key];
	}
	InteractionBooleanNodeKeyboard::InteractionBooleanNodeKeyboard(std::string s):InteractionBooleanNode(),
		_key(InputMethodParser::GetKeycodeForStringKey(s))
	{}
	InteractionBooleanNodeKeyboard::InteractionBooleanNodeKeyboard(std::string s,bool):InteractionBooleanNode(),// bool just to differentiate modifiers
		_key(InputMethodParser::GetKeycodeForStringModifier(s))
	{}
	
	
	
	
	
} // namespace __RocEye__
