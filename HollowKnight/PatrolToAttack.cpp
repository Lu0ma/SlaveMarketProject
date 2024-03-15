#include "PatrolToAttack.h"

PatrolToAttack::PatrolToAttack(BlackBoard* _blackBoard) : Transition(_blackBoard)
{

}


void PatrolToAttack::Init(State* _nextState)
{
	nextState = _nextState;
}

bool PatrolToAttack::CanNext() const
{
	return blackBoard->hasTarget;
}
