#ifndef INTERACTION_BOOLEAN_NODE_H
#define INTERACTION_BOOLEAN_NODE_H

#include "InteractionOperatorNode.h"
#include <string>

namespace __RocEye__
{
class InteractionBooleanNode: public InteractionNode
{
public:
	InteractionBooleanNode():InteractionNode(){}
	virtual bool Evaluate(const InteractionState*){return false;}
	virtual ~InteractionBooleanNode(){}
	inline bool IsOperator(){return false;}
}; // class InteractionBooleanNode

class  InteractionBooleanNodeKeyboard: public InteractionBooleanNode
{
public:
	InteractionBooleanNodeKeyboard(std::string);
	InteractionBooleanNodeKeyboard(std::string,bool);	
	bool Evaluate(const InteractionState*,bool,bool);
private:
	Uint16 _key;
	

}; // class  InteractionBooleanNodeKeyboard
} // namespace __RocEye__

#endif // INTERACTION_BOOLEAN_NODE_H
