#include "Mob.h"
#include "Macro.h"
#include "MovementComponent.h"
#include "MobBrain.h"

Mob::Mob(const ShapeData& _data) : Enemy("Mob" + to_string(GetUniqueID()), _data)
{
	isPatrolling = false;
	cooldownAttack = false;

	animation = new AnimationComponent(this);
	components.push_back(animation);

	movement = new MobMovementComponent(this);
	movement->SetSpeed(0.1f);
	components.push_back(movement);
	
	attack = new MobAttackComponent(this, 1);
	components.push_back(attack);

	life = new MobLifeComponent(this, 3);
	components.push_back(life);

	brain = new MobBrain(this);
	components.push_back(brain);
}

void Mob::Update(const float _deltaTime)
{
	Actor::Update(_deltaTime);
}

