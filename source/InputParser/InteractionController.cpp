#include "InteractionController.h"   
#include <iostream>

#include "InteractionBridge.h"

namespace __RocEye__
{	
	InteractionController::InteractionController(std::string inname,InteractionBooleanExpression* ibe,InteractionBridgeDictionary* dict):
		name(inname),
		_exp(ibe),
		_bridge(dict->Find(&inname))
	{
		if(_bridge==NULL)
			std::cerr << "Error: Cannot find command " << name << std::endl;
	}
	InteractionController::~InteractionController(){delete(_exp);}
	float InteractionController::ProjectMouseDelta(const InteractionState* state) const
	{
		// ToDo: Need more code between these brackets.
		return 0.0f;
	}

	bool InteractionController::Execute(InputHandler* h,const InteractionState* s,bool matches)
	{
		if(!_bridge)
			return false;
		if(_exp->Evaluate(s))
		   return _bridge->Execute(h,s);
		return !matches;
	}
//	bool InteractionController::IsValid()
} // namespace __RocEye__
