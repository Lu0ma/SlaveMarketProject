#include "BossBrain.h"

BossBrain::BossBrain(Actor* _owner) : EnemyBrain(_owner)
{
	patrol = new BossPatrolState(this);
	states.push_back(patrol);

	chase = new ChaseState(this);
	states.push_back(chase);

	attack = new BossAttackState(this);
	states.push_back(attack);

	Init();
}

BossBrain::~BossBrain()
{
	delete patrol;
	delete chase;
	delete attack;
}

void BossBrain::Init()
{
	patrol->Init();
	chase->Init();
	attack->Init();
	
	currentState = patrol;
	currentState->Start();
}