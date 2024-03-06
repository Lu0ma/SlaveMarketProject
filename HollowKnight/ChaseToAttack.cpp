#include "ChaseToAttack.h"
#include "BlackBoard.h"

bool ChaseToAttack::CanNext() const
{
    return blackBoard->isInRange;
}
