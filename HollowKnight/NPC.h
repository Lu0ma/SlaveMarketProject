#pragma once
#include "InteractableActor.h"
#include"NPCAnimationComponent.h"

class NPC : public InteractableActor
{
	vector<string> texts;
	NPCAnimationComponent* animation;

public:
	NPCAnimationComponent* GetAnimation()const
	{
		return animation;
	}

public:
	NPC(const string& _name, const ShapeData& _data, const vector<string>& _texts = {});

public:
	// void Speak() override;
};