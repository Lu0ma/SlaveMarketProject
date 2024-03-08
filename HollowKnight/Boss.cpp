#include "Boss.h"
#include "Macro.h"

Boss::Boss(const ShapeData& _data) : Enemy("Boss" + to_string(GetUniqueID()), _data)
{
	animation = new AnimationComponent(this);
	components.push_back(animation);

	movement = new MobMovementComponent(this);
	movement->SetSpeed(0.5f);
	components.push_back(movement);

	attack = new MobAttackComponent(this, 1);
	components.push_back(attack);

	life = new MobLifeComponent(this, 3);
	components.push_back(life);

	brain = new BossBrain(this);
	components.push_back(brain);
}

void Boss::Update(const float _deltaTime)
{
	Actor::Update(_deltaTime);
}
