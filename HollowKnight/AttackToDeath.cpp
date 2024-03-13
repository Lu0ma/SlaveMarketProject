#include "AttackToDeath.h"

AttackToDeath::AttackToDeath(BlackBoard* _blackBoard) : Transition(_blackBoard)
{

}

void AttackToDeath::Init(State* _nextState)
{
	nextState = _nextState;
}

bool AttackToDeath::CanNext() const
{
	return blackBoard->isDead;
}
