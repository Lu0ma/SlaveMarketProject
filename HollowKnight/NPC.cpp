#include "NPC.h"
#include "Macro.h"

NPC::NPC(const ShapeData& _data, const vector<string>& _texts) : Actor(_data)
{
	texts = _texts;
}