#pragma once
#include "Actor.h"
#include "InteractableActor.h"


class NPC : public Actor
{
	vector<string> texts;

public:

public:
	NPC();
	NPC(const vector<string>& _texts);

public:
	// void Speak() override;
};

