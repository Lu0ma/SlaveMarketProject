#pragma once
#include "Component.h"

class InteractionComponent : public Component
{
	float range;

public:
	InteractionComponent(Actor* _owner);

public:
	void TryToInteract();
};