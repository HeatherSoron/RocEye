#ifndef INTERACTION_BOOLEAN_EXPRESSION_H
#define INTERACTION_BOOLEAN_EXPRESSION_H
#include "InteractionState.h"
#include "InteractionOperatorNode.h"
#include "InputMethodTokens.h"
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
									
private:
	unsigned int _len;
	InteractionNode** _nodes;
}; // class InteractionBooleanExpression
} // namespace __RocEye__

#endif // INTERACTION_BOOLEAN_EXPRESSION_H
