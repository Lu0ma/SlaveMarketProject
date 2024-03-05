#include "ChaseToPatrol.h"
#include "PatrolState.h"
#include "BlackBoard.h"

ChaseToPatrol::ChaseToPatrol(Brain* _brain) : Transition(_brain)
{
}

void ChaseToPatrol::Init()
{
    nextState = brain->GetPatrolState();
}

bool ChaseToPatrol::CanNext() const
{
    return !blackBoard->hasTarget;
}