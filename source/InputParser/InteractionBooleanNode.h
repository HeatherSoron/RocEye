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
	virtual bool Evaluate(const InteractionState*,bool,bool)=0;
	virtual ~InteractionBooleanNode(){}
	inline bool IsOperator() const{return false;}
}; // class InteractionBooleanNode

class  InteractionBooleanNodeKeyboard: public InteractionBooleanNode
{
public:
	InteractionBooleanNodeKeyboard(std::string,Uint8);
	bool Evaluate(const InteractionState*,bool,bool);
private:
	Uint16 _key;
	Uint8 _mode;
	

}; // class  InteractionBooleanNodeKeyboard
} // namespace __RocEye__

#endif // INTERACTION_BOOLEAN_NODE_H
