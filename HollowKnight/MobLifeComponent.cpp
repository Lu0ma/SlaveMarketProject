#include "MobLifeComponent.h"

MobLifeComponent::MobLifeComponent(Actor* _owner, const int _life) : Component(_owner)
{
	life = _life;
}


void MobLifeComponent::TakeDamages(const int _damages)
{
	SetLife(-_damages);
}