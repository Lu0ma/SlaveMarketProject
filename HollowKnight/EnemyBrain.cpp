#include "EnemyBrain.h"

EnemyBrain::EnemyBrain(Actor* _owner) : Brain(_owner)
{
	death = new DeathState(this);
	states.push_back(death);
}