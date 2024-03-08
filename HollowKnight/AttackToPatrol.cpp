#include "AttackToPatrol.h"
#include "BlackBoard.h"
#include "EnemyBrain.h"

AttackToPatrol::AttackToPatrol(EnemyBrain* _brain) : Transition(_brain)
{
}

void AttackToPatrol::Init()
{
    nextState = dynamic_cast<EnemyBrain*>(brain)->GetPatrolState();
}

bool AttackToPatrol::CanNext() const
{
    return !blackBoard->hasTarget;
}