#pragma once
#include "Actor.h"
class InteractableActor : public Actor
{

	virtual void Update(const float _deltaTime);


public:
	virtual void Speak();
};

