#include "ChaseToAttack.h"

ChaseToAttack::ChaseToAttack(BlackBoard* _blackBoard) : Transition(_blackBoard)
{

}

void ChaseToAttack::Init(State* _nextState)
{
    nextState = _nextState;
}

bool ChaseToAttack::CanNext() const
{
    return blackBoard->isInRange;
}