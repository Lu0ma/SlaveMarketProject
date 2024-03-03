#include "NPC.h"
#include "Macro.h"

NPC::NPC(const string& _name, const ShapeData& _data, const vector<string>& _texts)
	: InteractableActor(_name, _data)
{
	animation = new NPCAnimationComponent(this);
	animation->GetCurrentAnimation()->RunAnimation("Stand", 1);
}