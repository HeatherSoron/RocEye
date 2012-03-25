#include "InteractionController.h"   
#include <iostream>

#include "InteractionBridge.h"

namespace __RocEye__
{	
	InteractionController::InteractionController(std::string name,InteractionBooleanExpression* ibe,InteractionBridgeDictionary* dict):
		_exp(ibe),
		_bridge(dict->Find(&name))
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

	bool InteractionController::Execute(InputHandler* h,const InteractionState* s)
	{
		if(!_bridge)
			return false;
		if(_exp->Evaluate(s))
		   return _bridge->Execute(this,h,s);
		return true;
	}
//	bool InteractionController::IsValid()
} // namespace __RocEye__
