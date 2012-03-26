#ifndef INTERACTION_OPERATOR_NODE_H
#define INTERACTION_OPERATOR_NODE_H

#include "InteractionState.h"

namespace __RocEye__
{
class InteractionNode
{
public:
	InteractionNode(){}
	virtual ~InteractionNode(){}
	virtual bool Evaluate(const InteractionState*,bool,bool)=0;
	virtual bool IsOperator() const=0;
}; // class InteractionNode 
	
class InteractionOperatorNode: public InteractionNode
{
public:
	InteractionOperatorNode():InteractionNode(){}
	virtual bool Evaluate(const InteractionState*,bool,bool)=0;
	virtual ~InteractionOperatorNode(){}
	virtual bool IsOperator() const{return true;}
}; // class InteractionOperatorNode
	
	
class InteractionOperatorAndNode: public InteractionOperatorNode
{
public:
	InteractionOperatorAndNode():InteractionOperatorNode(){}
	bool Evaluate(const InteractionState*,bool,bool);
}; // class InteractionOperatorAndNode

class InteractionOperatorOrNode: public InteractionOperatorNode
{
public:
	InteractionOperatorOrNode():InteractionOperatorNode(){}
	bool Evaluate(const InteractionState*,bool,bool);
}; // class InteractionOperatorOrNode

} // namespace __RocEye__

#endif // INTERACTION_OPERATOR_NODE_H
