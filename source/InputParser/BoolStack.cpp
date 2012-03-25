#ifdef NO_BLACK_MAGIC
#error Warning: This file cannot compile without black magic.
#endif


#include "BoolStack.h"   

namespace __RocEye__
{
    BoolStack::BoolStack(const unsigned int len):
		_index(0),
		_stack(new bool[len])
	{}
	
	BoolStack::~BoolStack(void)
	{
		delete[](_stack);
	}
	
	void BoolStack::push(bool b)
	{
		_stack[_index++]=b;
	}
	bool BoolStack::pop(void)
	{
		return _stack[--_index];
	}
} // namespace __RocEye__
