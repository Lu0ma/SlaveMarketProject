#include "BossBrain.h"

BossBrain::BossBrain(Actor* _owner) : EnemyBrain(_owner)
{
	chase = new ChaseState(this);
	states.push_back(chase);

	patrol = new BossPatrolState(this);
	states.push_back(patrol);

	chase->Init();
	patrol->Init();
	attack->Init();

	currentState = patrol;
	currentState->Start();
}

BossBrain::~BossBrain()
{
	delete chase;
	delete patrol;
}
