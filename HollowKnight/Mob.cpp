#include "Mob.h"
#include "Macro.h"
#include "MovementComponent.h"
#include "PatrolComponent.h"
#include "MobBrain.h"

Mob::Mob(const ShapeData& _data) : Enemy(STRING_ID("Mob"), _data)
{
	isPatrolling = false;
	cooldownAttack = false;

	/*movement = new MobMovementComponent(this);
	components.push_back(movement);*/

	life = new EnemyLifeComponent(this, 1);
	components.push_back(life);

	patrol = new PatrolComponent(this, Vector2f(1000.0f, 0.0f));
	components.push_back(patrol);

	inspect = new InspectComponent(this, 100.0f);
	components.push_back(inspect);

	attack = new MobAttackComponent(this, 1);
	components.push_back(attack);

	brain = new MobBrain(this);
	components.push_back(brain);
}

void Mob::Update(const float _deltaTime)
{
	Enemy::Update(_deltaTime);
}

void Mob::Death()
{
	//ActorManager::GetInstance().Remove("Mob");
	cout << "il est mort " << endl;
}

void Mob::Attack(Player* _player)
{

}