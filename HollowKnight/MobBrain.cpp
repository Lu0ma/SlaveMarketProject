#include "MobBrain.h"

MobBrain::MobBrain(Actor* _owner) : EnemyBrain(_owner)
{
	attack = new AttackState(this);
	states.push_back(attack);

	patrol = new PatrolState(this);
	states.push_back(patrol);

	attack->Init();
	patrol->Init();

	currentState = patrol;
	currentState->Start();
}