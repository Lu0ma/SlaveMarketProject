#include "MobAttackComponent.h"

MobAttackComponent::MobAttackComponent(Actor* _owner, const int _damages)
	: Component(_owner)
{
	damages = _damages;
}

void MobAttackComponent::Attack() // TODO
{

}
