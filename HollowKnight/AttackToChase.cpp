#include "AttackToChase.h"
#include "BlackBoard.h"
#include "BossBrain.h"

AttackToChase::AttackToChase(BossBrain* _brain) : Transition(_brain)
{
}

void AttackToChase::Init()
{
    nextState = dynamic_cast<BossBrain*>(brain)->GetChaseState();
}

bool AttackToChase::CanNext() const
{
    return !blackBoard->isInRange;
}
