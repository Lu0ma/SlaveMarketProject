#include "MobBrain.h"

MobBrain::MobBrain(Actor* _owner) : EnemyBrain(_owner)
{
	patrol->Init();

	currentState = patrol;
	currentState->Start();
}
