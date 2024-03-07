#include "PatrolToChase.h"
#include "BlackBoard.h"
#include "Brain.h"

PatrolToChase::PatrolToChase(Brain* _brain) : Transition(_brain)
{
}

void PatrolToChase::Init()
{
	nextState = brain->GetChaseState();
}

bool PatrolToChase::CanNext() const
{
	return blackBoard->hasTarget;
}