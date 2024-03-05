#include "BossBrain.h"

BossBrain::BossBrain(Actor* _owner) : EnemyBrain(_owner)
{


	chase->Init();
	patrol->Init();

	currentState = patrol;
	currentState->Start();
}

BossBrain::~BossBrain()
{
	delete chase;
}
