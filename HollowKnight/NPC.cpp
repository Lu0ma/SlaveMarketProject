#include "NPC.h"
#include "Macro.h"

NPC::NPC(const vector<string>& _texts) : InteractableActor(STRING_ID("NPC"), ShapeData(Vector2f(0.0f, 0.0f), Vector2f(50.0f, 50.0f)))
{ 
	texts = _texts;

	GetDrawable()->setFillColor(Color::Blue);
}