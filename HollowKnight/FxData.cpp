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
	animFx.resize(11);
	animFx.push_back("None");
	animFx.push_back("FxChargingMana");
	animFx.push_back("FxMana");
	animFx.push_back("FxSpecial");
	animFx.push_back("FxDash");
	animFx.push_back("FxDoubleJump");
	animFx.push_back("FxIsHitten");
	animFx.push_back("FxDarkHole");
	animFx.push_back("FxHighAttack");
	animFx.push_back("FxBroken");
	animFx.push_back("FxDamagesHuskBully");

	const float _speed = 0.3f;

	animation->InitAnimations({
		AnimationData("None", Vector2f(0.0f, 0.0f), Vector2f(30.0f, 20.0f), READ_RIGHT, false, 1, _speed),
		AnimationData("FxMana", Vector2f(0.0f, 91.0f), Vector2f(510.0f, 301.0f), READ_RIGHT, false, 4, 0.03f),
		AnimationData("FxChargingMana", Vector2f(0.0f, 91.0f), Vector2f(510.0f, 301.0f), READ_RIGHT, false, 1, 0.03f),
		//AnimationData("FxSpecial", Vector2f(0.0f, 440.0f), Vector2f(340.0f, 321.0f), READ_RIGHT, false, 3, 0.01f),
		AnimationData("FxSpecial", Vector2f(2.0f, 452.0f), Vector2f(796.0f, 316.0f), READ_RIGHT, false, 3, 0.01f),
		AnimationData("FxDash", Vector2f(0.0f, 800.0f), Vector2f(383.0f, 342.0f), READ_RIGHT, false, 6, 0.05f),
		AnimationData("FxDoubleJump", Vector2f(0.0f, 1253.0f), Vector2f(487.0f, 422.0f), READ_RIGHT, false, 3, 0.1f),
		AnimationData("FxIsHitten", Vector2f(0.0f, 477.0f), Vector2f(216.0f, 142.0f), READ_RIGHT, false, 2, 0.01f),
		AnimationData("FxDarkHole", Vector2f(0.0f, 642.0f), Vector2f(94.0f, 91.0f), READ_RIGHT, false, 3, 0.03f),
		AnimationData("FxHighAttack", Vector2f(0.0f, 742.0f), Vector2f(160.0f, 152.0f), READ_RIGHT, false, 5, 0.09f, "None"),
		AnimationData("FxBroken", Vector2f(52.0f, 0.0f), Vector2f(1337.0f, 360.0f), READ_DOWN, false, 3, 0.13f),
		AnimationData("FxDamagesHuskBully", Vector2f(37.0f, 1737.0f), Vector2f(127.0f, 153.0f), READ_RIGHT, false, 14, 0.13f),
	});
}
