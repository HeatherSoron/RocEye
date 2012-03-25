#ifdef NO_BLACK_MAGIC
#error Warning: This file cannot compile without black magic.
#endif

#include "InteractionBridge.h"
namespace __RocEye__
{
	
	InteractionBridgeNameMap* InteractionBridgeDictionary::Find(const std::string* s)
	{
		std::string* str=InputMethodParser::NormalizedCopy(*s);
	
		for(unsigned int i=0;i<InteractionBridgeMap->size();++i)
		{
			if((*str)==InteractionBridgeMap->at(i)->Name()){
				delete(str);
				return InteractionBridgeMap->at(i);
			}
		}
		delete(str);
		return NULL;
	}
	
} // namespace __RocEye__