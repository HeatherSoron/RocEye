#include "InteractionBooleanExpression.h"   
#include "BoolStack.h"
#include "InteractionBooleanNode.h"
#include "InputMethodTokens.h"
#include <iostream>

namespace __RocEye__
{
	InteractionBooleanExpression::InteractionBooleanExpression(std::vector<std::string>* vec):
		_len(vec->size()),
		_nodes(new InteractionNode*[_len]),
		_usesKeyboard(false),
		_usesMouse(false)
	{
		int m;
		for(unsigned int i=0;i<vec->size();++i)
		{
			std::string s=vec->at(i);
			if(s==AND_TOKEN)
				_nodes[i]=new InteractionOperatorAndNode();
			else if(s==OR_TOKEN)
				_nodes[i]=new InteractionOperatorOrNode();
			else if((m=s.find(MODIFIER_KEY_TOKEN))==0){
				_usesKeyboard=true;
				_nodes[i]=new InteractionBooleanNodeKeyboard(s.substr(m+12,s.size()-m-13),true);// true == modifier
			}
			else if((m=s.find(KEY_TOKEN))==0){
				_usesKeyboard=true;
				_nodes[i]=new InteractionBooleanNodeKeyboard(s.substr(m+4,s.size()-m-5));
			}
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
