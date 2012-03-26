#include "InteractionBooleanExpression.h"   
#include "BoolStack.h"
#include "InteractionBooleanNode.h"
#include "InputMethodTokens.h"
#include <iostream>

#include "../KeyboardState.h"

#define GENERATE_KEYBOARD_NODE(name) else if((m=s.find(name##_TOKEN))==0)_nodes[i]=new InteractionBooleanNodeKeyboard(s.substr(m+name##_TOKEN_LENGTH,s.size()-m-name##_TOKEN_LENGTH-1),KeyboardState::name##_MODE)
namespace __RocEye__
{
	InteractionBooleanExpression::InteractionBooleanExpression(std::vector<std::string>* vec):
		_len(vec->size())
	{
		_nodes=new InteractionNode*[_len];
		int m;
		for(unsigned int i=0;i<_len;++i)
		{
			std::string s=vec->at(i);
			if(s==AND_TOKEN)
				_nodes[i]=new InteractionOperatorAndNode();
			else if(s==OR_TOKEN)
				_nodes[i]=new InteractionOperatorOrNode();
			GENERATE_KEYBOARD_NODE(MODIFIER_KEY);
			GENERATE_KEYBOARD_NODE(NO_MODIFIER_KEY);
			GENERATE_KEYBOARD_NODE(KEY_UP);
			GENERATE_KEYBOARD_NODE(KEY_DOWN);
			GENERATE_KEYBOARD_NODE(KEY_REPEAT);
			else{
				// THIS SHOULDN'T HAPPEN AND IS BAD
				std::cerr << "Empty node in InteractionBooleanExpression. Later code is likely to crash." << std::endl;
				_nodes[i]=NULL;
			}
		}
	}
	bool InteractionBooleanExpression::Evaluate(const InteractionState* state){
		BoolStack work=BoolStack(_len);
		for(unsigned int i = 0; i < _len; ++i)
		{
			if(_nodes[i]->IsOperator())
				work.push(_nodes[i]->Evaluate(NULL,work.pop(),work.pop()));
			else
				work.push(_nodes[i]->Evaluate(state,false,false));
		}
		return work.pop();
	}
	
	InteractionBooleanExpression::~InteractionBooleanExpression()
	{
		for(unsigned int i = 0; i < _len; ++i)
			if(_nodes[i])
				delete(_nodes[i]);
		delete[](_nodes);
		_len=0;
	}
} // namespace __RocEye__
