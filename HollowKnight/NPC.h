#pragma once
#include "InteractableActor.h"

class NPC : public InteractableActor
{
	vector<string> texts;

public:
	NPC(const string& _name, const ShapeData& _data, const vector<string>& _texts = {});

public:
	// void Speak() override;
};