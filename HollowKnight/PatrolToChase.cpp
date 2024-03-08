#include "PatrolToChase.h"
#include "BlackBoard.h"
#include "BossBrain.h"

PatrolToChase::PatrolToChase(BossBrain* _brain) : Transition(_brain)
{
}

void PatrolToChase::Init()
{
	nextState = dynamic_cast<BossBrain*>(brain)->GetChaseState();
}

bool PatrolToChase::CanNext() const
{
	return blackBoard->hasTarget;
}