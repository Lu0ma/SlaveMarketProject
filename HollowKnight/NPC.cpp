#include "NPC.h"
#include "Macro.h"

NPC::NPC(const Vector2f& _position, const Vector2f& _size) : Actor(STRING_ID("NPC"),ShapeData(Vector2f(_position),Vector2f(_size)))
{
	texts = vector<string>();
}

NPC::NPC(const vector<string>& _texts) : Actor(STRING_ID("NPC"), ShapeData(Vector2f(1280, 720.0f), Vector2f(50.0f, 50.0f)))
{ 
	texts = _texts;
}

//void NPC::Speak()
//{
//
//}