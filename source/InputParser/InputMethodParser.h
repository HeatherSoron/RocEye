#ifndef INPUT_METHOD_PARSER_H
#define INPUT_METHOD_PARSER_H
#include "InteractionBooleanExpression.h"

#include "../InputHandler.h"
#include <fstream>

namespace __RocEye__
{
class InteractionController;
class MasterInteractionController;
class InteractionBridgeDictionary;

class InputMethodParser
{
public:
	static Uint16 GetKeycodeForStringKey(const std::string);
	static Uint16 GetKeycodeForStringModifier(const std::string);
	static std::string* NormalizedCopy(const std::string);	
	
	InputMethodParser(std::string);
	~InputMethodParser(){ConfigFile.close();}

	MasterInteractionController* ParseFile(InteractionBridgeDictionary* map);
	
private:
	static void CloneInto(std::vector<std::string>*,unsigned int,const char*,const char*,const char*);
	InteractionController* ParseLine(std::string,InteractionBridgeDictionary*);
	
	std::ifstream ConfigFile;
	
}; // class InputMethodParser
} // namespace __RocEye__

#endif // INPUT_METHOD_PARSER_H
