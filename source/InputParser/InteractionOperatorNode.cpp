#include "InteractionOperatorNode.h"   

namespace __RocEye__
{
	bool InteractionOperatorAndNode::Evaluate(const InteractionState*,bool a,bool b)
	{
		return a&&b;
	}
	
	bool InteractionOperatorOrNode::Evaluate(const InteractionState*,bool a,bool b)
	{
		return a||b;
	}
} // namespace __RocEye__
