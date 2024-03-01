#include "NPC.h"
#include "Macro.h"

NPC::NPC(const string& _name, const ShapeData& _data, const vector<string>& _texts)
		: InteractableActor(_name, _data)

NPC::NPC(const Vector2f& _position, const Vector2f& _size) : Actor(STRING_ID("NPC"),ShapeData(Vector2f(_position),Vector2f(_size), PATH_NPC))
{
	texts = _texts;
}