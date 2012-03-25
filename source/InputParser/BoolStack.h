#ifndef BOOL_STACK_H
#define BOOL_STACK_H

#ifdef NO_BLACK_MAGIC
#error Warning: This file cannot compile without black magic.
#endif


// Abandon all hope ye who enter here.
// This class performs NO error checking.
// It will happily overrun, underrun, or otherwise chew up the callstack.
// It is YOUR responsibility to use it correctly.
// Don't push to a full stack. Don't pop from an empty stack.
// And you should know if it is full or empty yourself.
// Because the class won't tell you.

namespace __RocEye__
{
class BoolStack
{
public:
	BoolStack(const unsigned int);
	~BoolStack(void);
	void push(bool);
	bool pop(void);
	
private:
	unsigned int _index;
	bool* _stack;
}; // class BoolStack
} // namespace __RocEye__

#endif // BOOL_STACK_H
