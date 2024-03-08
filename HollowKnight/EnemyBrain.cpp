#include "EnemyBrain.h"

EnemyBrain::EnemyBrain(Actor* _owner) : Brain(_owner)
{
}

EnemyBrain::~EnemyBrain()
{
	delete attack;
	delete patrol;
}
