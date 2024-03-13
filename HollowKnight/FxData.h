#pragma once
#include "IManagable.h"
#include"AnimationComponent.h"

using namespace std;

class FxData : public IManagable<string>
{
	AnimationComponent* animation;
	vector<string> animFx;

public:
	AnimationComponent* GetCurrentAnimation()const
	{
		return animation;
	}

public:
	FxData(Actor* _actor, const string _path);

public:
	void Register();
	void Init();
};