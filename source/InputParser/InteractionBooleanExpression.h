#ifndef INTERACTION_BOOLEAN_EXPRESSION_H
#define INTERACTION_BOOLEAN_EXPRESSION_H
#include "InteractionState.h"
#include "InteractionOperatorNode.h"
#include <vector>
#include <string>


namespace __RocEye__
{
class InteractionBooleanExpression
{
public:
	InteractionBooleanExpression(std::vector<std::string>*);
	bool Evaluate(const InteractionState*);
	~InteractionBooleanExpression();
	
	bool UsesKeyboard(){return _usesKeyboard;}
	bool UsesMouse(){return _usesMouse;}
								 
private:
	unsigned int _len;
	InteractionNode** _nodes;
	bool _usesKeyboard;
	bool _usesMouse;
}; // class InteractionBooleanExpression
} // namespace __RocEye__

#endif // INTERACTION_BOOLEAN_EXPRESSION_H
