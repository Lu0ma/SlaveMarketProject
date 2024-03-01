#pragma once
#include "Actor.h"
#include "InteractableActor.h"

class NPC : public Actor
{
	vector<string> texts;

public:

public:
	NPC(const Vector2f& _position, const Vector2f& _size);
	NPC(const vector<string>& _texts);

public:
	// void Speak() override;
};

