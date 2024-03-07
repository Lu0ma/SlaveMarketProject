#include "MobAttackComponent.h"
#include "Actor.h"
#include "Mob.h"
#include "Boss.h"

MobAttackComponent::MobAttackComponent(Actor* _owner, const int _damages)
	: Component(_owner)
{
	damages = _damages;
}

void MobAttackComponent::Attack() // TODO
{	
	//if (Mob* _mob = dynamic_cast<Mob*>(owner))
	//{
	//	_mob->GetBrain()->GetBlackBoard().hasTarget; // faire les condition avec RayCast ou Distance
	//}

	//else if (Boss* _boss = dynamic_cast<Boss*>(owner))
	//{
	//	_boss->GetBrain()->GetBlackBoard().hasTarget;
	//}
}