#include "ChaseToDeath.h"

ChaseToDeath::ChaseToDeath(BlackBoard* _blackBoard) : Transition(_blackBoard)
{
}

void ChaseToDeath::Init(State* _nextState)
{
	nextState = _nextState;
}

bool ChaseToDeath::CanNext() const
{
	return blackBoard->isDead;
}