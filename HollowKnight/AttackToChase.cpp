#include "AttackToChase.h"
#include "BlackBoard.h"
#include "Brain.h"

AttackToChase::AttackToChase(Brain* _brain) : Transition(_brain)
{
}

void AttackToChase::Init()
{
    nextState = brain->GetChaseState();
}

bool AttackToChase::CanNext() const
{
    return !blackBoard->isInRange;
}
