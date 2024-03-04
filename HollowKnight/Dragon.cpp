#include "Dragon.h"

Dragon::Dragon(const string& _name, const ShapeData& _data, const vector<string>& _texts)
	: InteractableActor(_name, _data)
{
	animation = new DragonAnimationComponent(this);
}
