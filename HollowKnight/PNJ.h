#pragma once
#include "InteractableActor.h"
#include"NPCAnimationComponent.h"

class PNJ : public InteractableActor
{
	NPCAnimationComponent* animation;

public:
	NPCAnimationComponent* GetAnimation() const
	{
		return animation;
	}

public:
	PNJ(const ShapeData& _data);
};

