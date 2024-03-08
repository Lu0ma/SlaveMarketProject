#include "PatrolToAttack.h"
#include "MobBrain.h"

PatrolToAttack::PatrolToAttack(MobBrain* _brain) : Transition(_brain)
{

}

void PatrolToAttack::Init()
{
	nextState = dynamic_cast<MobBrain*>(brain)->GetAttackState();
}

bool PatrolToAttack::CanNext() const
{
	return blackBoard->isInRange;
}
