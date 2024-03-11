#include "AttackToChase.h"

AttackToChase::AttackToChase(BlackBoard* _blackBoard) : Transition(_blackBoard)
{

}


void AttackToChase::Init(State* _nextState)
{
    nextState = _nextState;
}

bool AttackToChase::CanNext() const
{
    return !blackBoard->isInRange;
}