#include "AttackToBossPatrol.h"
#include "BossBrain.h"

AttackToBossPatrol::AttackToBossPatrol(BossBrain* _brain) : Transition(_brain)
{

}

void AttackToBossPatrol::Init()
{
	nextState = dynamic_cast<BossBrain*>(brain)->GetPatrolState();
}

bool AttackToBossPatrol::CanNext() const
{
	return !blackBoard->hasTarget;
}
