#include "FxData.h"
#include "FxManager.h"
#include "Actor.h"
#include "AnimationComponent.h"
#include <iostream>

FxData::FxData(Actor* _actor, const string _path) : IManagable(_path)
{
	animation = _actor->GetComponent<AnimationComponent>();
	animFx = vector<string>();
	Init();
	Register();
}

void FxData::Register()
{
	FxManager::GetInstance().Add(id, this);
}

void FxData::Init()
{
	animFx.resize(5);
	animFx.push_back("None");
	animFx.push_back("FxChargingMana");
	animFx.push_back("FxMana");
	animFx.push_back("FxSpecial");
	animFx.push_back("FxDash");
	animFx.push_back("FxDoubleJump");

	const float _speed = 0.3f;

	animation->InitAnimations({
		AnimationData("None", Vector2f(0.0f, 0.0f), Vector2f(30.0f, 20.0f), READ_RIGHT, false, 1, _speed),
		AnimationData("FxMana", Vector2f(0.0f, 91.0f), Vector2f(510.0f, 301.0f), READ_RIGHT, false, 4, 0.03f),
		AnimationData("FxChargingMana", Vector2f(0.0f, 91.0f), Vector2f(510.0f, 301.0f), READ_RIGHT, false, 1, 0.03f),
		AnimationData("FxSpecial", Vector2f(0.0f, 440.0f), Vector2f(340.0f, 321.0f), READ_RIGHT, false, 4, 0.01f),
		AnimationData("FxDash", Vector2f(0.0f, 800.0f), Vector2f(383.0f, 342.0f), READ_RIGHT, false, 6, 0.05f),
		AnimationData("FxDoubleJump", Vector2f(0.0f, 1253.0f), Vector2f(487.0f, 422.0f), READ_RIGHT, false, 3, 0.1f),
	});
}
