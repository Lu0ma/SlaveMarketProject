#include "MobBrain.h"

MobBrain::MobBrain(Actor* _owner) : EnemyBrain(_owner)
{
	attack = new MobAttackState(this);
	states.push_back(attack);

	patrol = new MobPatrolState(this);
	states.push_back(patrol);

	Init();
}


void MobBrain::Init()
{
	attack->Init();
	patrol->Init();
	death->Init();

	currentState = patrol;
	currentState->Start();
}