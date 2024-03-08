#include "PatrolToChase.h"

PatrolToChase::PatrolToChase(BlackBoard* _blackBoard) : Transition(_blackBoard)
{

}


void PatrolToChase::Init(State* _state)
{
	nextState = _state;
}

bool PatrolToChase::CanNext() const
{
	return blackBoard->hasTarget;
}