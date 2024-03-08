#include "ChaseToAttack.h"
#include "BlackBoard.h"
#include "BossBrain.h"

ChaseToAttack::ChaseToAttack(BossBrain* _brain) : Transition(_brain)
{
}

void ChaseToAttack::Init()
{
    nextState = dynamic_cast<BossBrain*>(brain)->GetChaseState();
}

bool ChaseToAttack::CanNext() const
{
    return blackBoard->isInRange;
}