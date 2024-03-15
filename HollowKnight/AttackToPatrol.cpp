#include "AttackToPatrol.h"

AttackToPatrol::AttackToPatrol(BlackBoard* _blackBoard) : Transition(_blackBoard)
{

}


void AttackToPatrol::Init(State* _nextState)
{
    nextState = _nextState;
}

bool AttackToPatrol::CanNext() const
{
    return !blackBoard->hasTarget;
}