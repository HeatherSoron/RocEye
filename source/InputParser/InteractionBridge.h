#ifndef INTERACTION_FUNCTIONS_H
#define INTERACTION_FUNCTIONS_H

#ifdef NO_BLACK_MAGIC
#error Warning: This file cannot compile without black magic.
#endif

// This file is relatvely fragile. Try not to mess with it too much. 

#include <vector>
#include <string>

#include "InteractionController.h"
#include "InteractionState.h"
#include "../InputHandler.h"
#include "InputMethodParser.h"

#define INTERACTION_BRIDGE_FUNCTION_POINTER(name) void (*name)(const InteractionController*,InputHandler*,const InteractionState*)

namespace __RocEye__
{
class InteractionBridge{
public:
// Do not move these!
#define INTERACTION_FUNCTION(name,func,arg)   static void name(const InteractionController* p,InputHandler* h,const InteractionState* s){h->func(arg);}
#define INTERACTION_FUNCTION_ROTATE(name,arg) static void name(const InteractionController* p,InputHandler* h,const InteractionState* s){h->rotate(arg,p->UsesMouse(),1/*p->ProjectMouseDelta(s)*/);}
	// todo: FIX the rotate above.
#include "InteractionBridgeFunctions.h"
	
};// class InteractionBridge
	
class InteractionBridgeDictionary;
class InteractionBridgeNameMap{
public:
	InteractionBridgeNameMap(const char* name,INTERACTION_BRIDGE_FUNCTION_POINTER(func)):
		_name(InputMethodParser::NormalizedCopy(std::string(name))),
		_func(func)
	{
	std::cerr << name << std::endl;
	}
	~InteractionBridgeNameMap(){}
	
	bool Execute(const InteractionController* i,InputHandler* h,const InteractionState* s)
	{
		(*_func)(i,h,s);
		return true;
	}
	std::string Name(){return *_name;}
private:
	std::string* _name;
	INTERACTION_BRIDGE_FUNCTION_POINTER(_func);
	
}; // class InteractionBridgeNameMap

class InteractionBridgeDictionary{
public:
	InteractionBridgeDictionary():
		InteractionBridgeMap(new std::vector<InteractionBridgeNameMap*>)
	{
		// Do not move these!
#undef INTERACTION_FUNCTION
#undef INTERACTION_FUNCTION_ROTATE
		// undefs required to silence redefinition warning
#define INTERACTION_FUNCTION(name,arg1,arg2) Push(new InteractionBridgeNameMap(#name,&InteractionBridge::name));
#define INTERACTION_FUNCTION_ROTATE(name,arg) INTERACTION_FUNCTION(name,skip,ignore)
#include "InteractionBridgeFunctions.h"
	} // InteractionBridgeDictionary()		
	
	InteractionBridgeNameMap* Find(const std::string*);
	void Push(InteractionBridgeNameMap* m){
		InteractionBridgeMap->push_back(m);
	}
	
	~InteractionBridgeDictionary()
	{
		while(InteractionBridgeMap->size())
			InteractionBridgeMap->pop_back();// this looks like it leaks them, but they are owned elsewhere.
		// Wait... this DOES leak any unused commands. Need to find a way to fix that later.
		delete(InteractionBridgeMap);
	}
	static MasterInteractionController* InitializeInput(const char* file="controls.cfg")
	{
		InputMethodParser* inp=new InputMethodParser(std::string(file));
		InteractionBridgeDictionary *dict= new InteractionBridgeDictionary();
		MasterInteractionController* ret=inp->ParseFile(dict);
		delete inp;
		delete dict;
		return ret;
	}
private:
		std::vector<InteractionBridgeNameMap*>* InteractionBridgeMap;
		
}; // class InteractionBridgeDictionary
} // namespace __RocEye__

#endif // INTERACTION_FUNCTIONS_H
