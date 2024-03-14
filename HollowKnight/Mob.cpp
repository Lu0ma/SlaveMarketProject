#include "Mob.h"
#include "Macro.h"
#include "MovementComponent.h"
#include "MobBrain.h"

Mob::Mob(const ShapeData& _data) : Enemy(STRING_ID("Mob"), _data)
{
	isPatrolling = false;
	cooldownAttack = false;

	movement = new MobMovementComponent(this);
	movement->SetSpeed(0.1f);
	components.push_back(movement);
	
	attack = new MobAttackComponent(this, 1);
	components.push_back(attack);

	life = new MobLifeComponent(this, 1);
	components.push_back(life);

	inspect = new InspectComponent(this, 100.0f);
	components.push_back(inspect);

	brain = new MobBrain(this);
	components.push_back(brain);
}

void Mob::Update(const float _deltaTime)
{
	Enemy::Update(_deltaTime);
}

void Mob::Death()
{
}

void Mob::Attack(Player* _player)
{
}
