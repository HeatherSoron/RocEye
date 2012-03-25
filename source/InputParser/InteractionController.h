#ifndef INTERACTION_CONTROLLER_H
#define INTERACTION_CONTROLLER_H

#include <string>

#include "InteractionBooleanExpression.h"
#include "../InputHandler.h"

namespace __RocEye__
{
class InteractionBridgeDictionary;
class InteractionBridgeNameMap;
class InteractionController
{
public:
	InteractionController(std::string,InteractionBooleanExpression*,InteractionBridgeDictionary*);
	~InteractionController();
	
	inline bool IsActive(const InteractionState* state) const{return _exp->Evaluate(state);}
	bool Execute(InputHandler* h,const InteractionState* s);
	
	inline bool UsesMouse() const{return _exp->UsesMouse();}
	inline bool UsesKeyboard() const{return _exp->UsesKeyboard();}
	
	inline bool IsValid(){return !!_bridge && !!_exp;}
	
	float ProjectMouseDelta(const InteractionState*) const; // This flattens the 2D mouse move into a direction along the direction this event cares about
private:
	InteractionBooleanExpression* _exp;
	InteractionBridgeNameMap* _bridge;
	
}; // class InteractionController
	
class MasterInteractionController
{
public:
	MasterInteractionController(unsigned int len,InteractionController** controllers):_len(len),_controllers(controllers){}
	bool Execute(InputHandler* h,const InteractionState* s){
		bool ret=true;
		for(unsigned int i=0;i<_len;++i)
			ret&=_controllers[i]->Execute(h,s);
		return ret;
	}
	~MasterInteractionController()
	{
		for(unsigned int i=0;i<_len;++i)
			delete(_controllers[i]);
		delete[](_controllers);
	}
private:
	unsigned int _len;
	InteractionController** _controllers;
};
} // namespace __RocEye__

#endif // INTERACTION_CONTROLLER_H
