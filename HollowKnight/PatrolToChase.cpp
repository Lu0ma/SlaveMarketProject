#include "PatrolToChase.h"
#include "ChaseState.h"
#include "BlackBoard.h"
#include "BossBrain.h"

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