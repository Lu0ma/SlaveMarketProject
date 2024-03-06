#pragma once
#include"InteractableActor.h"
#include"AnimationComponent.h"

class Grub : public InteractableActor
{
	AnimationComponent* animation;
	vector<string> animGrub;

public:
	AnimationComponent* GetCurrentAnimation()const
	{
		return animation;
	}

public:
	Grub(const string& _name,const ShapeData& _data, const vector<string>& _texts = {});
};

