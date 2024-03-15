#include "EnemyLifeComponent.h"

EnemyLifeComponent::EnemyLifeComponent(Actor* _owner, const int _life) : Component(_owner)
{
	life = _life;
}


void EnemyLifeComponent::TakeDamages(const int _damages)
{
	life -= _damages;
}