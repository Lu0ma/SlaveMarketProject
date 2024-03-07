#include "ChaseToAttack.h"
#include "BlackBoard.h"
#include "Brain.h"

ChaseToAttack::ChaseToAttack(Brain* _brain) : Transition(_brain)
{
}

void ChaseToAttack::Init()
{
    nextState = brain->GetAttackState();
}

bool ChaseToAttack::CanNext() const
{
    return blackBoard->isInRange;
}
