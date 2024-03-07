#include "AttackToPatrol.h"
#include "BlackBoard.h"
#include "Brain.h"

AttackToPatrol::AttackToPatrol(Brain* _brain) : Transition(_brain)
{
}

void AttackToPatrol::Init()
{
    nextState = brain->GetPatrolState();
}

bool AttackToPatrol::CanNext() const
{
    return !blackBoard->hasTarget;
}
