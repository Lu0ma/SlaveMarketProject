#include "Boss.h"
#include "Macro.h"
#include "BossBrain.h"

Boss::Boss(const ShapeData& _data) : Enemy("Boss" + to_string(GetUniqueID()), _data)
{
	movement = new MobMovementComponent(this);
	movement->SetSpeed(0.5f);
	components.push_back(movement);

	attack = new MobAttackComponent(this, 1);
	components.push_back(attack);

	life = new MobLifeComponent(this, 3);
	components.push_back(life);

	inspect = new InspectComponent(this, 500.0f);
	components.push_back(inspect);

	brain = new BossBrain(this);
	components.push_back(brain);
}

void Boss::Update(const float _deltaTime)
{
	Enemy::Update(_deltaTime);
}
