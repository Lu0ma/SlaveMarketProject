#pragma once
#include "Component.h"
#include "Inventory.h"
#include "Merchand.h"
#include"PNJ.h"

class InteractionComponent : public Component
{
	float range;
	Inventory* inventory;
	Merchand* merchand;
	PNJ* pnj;

public:
	InteractionComponent(Actor* _owner);

public:
	void TryToInteract();
	void StopInteract();
};