#include "AttackToPatrol.h"
#include "BlackBoard.h"

bool AttackToPatrol::CanNext() const
{
    return !blackBoard->hasTarget;
}
