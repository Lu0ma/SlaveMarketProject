#include "ChaseToPatrol.h"

ChaseToPatrol::ChaseToPatrol(BlackBoard* _blackBoard) : Transition(_blackBoard)
{

}


void ChaseToPatrol::Init(State* _nextState)
{
    nextState = _nextState;
}

bool ChaseToPatrol::CanNext() const
{
    return !blackBoard->hasTarget;
}