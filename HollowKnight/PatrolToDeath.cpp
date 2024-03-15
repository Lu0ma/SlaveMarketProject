#include "PatrolToDeath.h"

PatrolToDeath::PatrolToDeath(BlackBoard* _blackBoard) : Transition(_blackBoard)
{
}

void PatrolToDeath::Init(State* _nextState)
{
	nextState = _nextState;
}

bool PatrolToDeath::CanNext() const
{
	return blackBoard->isDead;
}
