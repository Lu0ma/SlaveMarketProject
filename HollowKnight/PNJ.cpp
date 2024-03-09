#include "PNJ.h"

PNJ::PNJ(const ShapeData& _data)
	: InteractableActor(STRING_ID("PNJ"), _data)
{
	animation = new NPCAnimationComponent(this);
	components.push_back(animation);
}
