#pragma once
#include "InteractableActor.h"
#include"DragonAnimationComponent.h"

class Dragon : public InteractableActor
{
	DragonAnimationComponent* animations;

public:
	DragonAnimationComponent* GetAnimations()const
	{
		return animations;
	}

public:
	Dragon(const string& _name, const ShapeData& _data, const vector<string>& _texts = {});

public:
	void PlayMusic();
};

