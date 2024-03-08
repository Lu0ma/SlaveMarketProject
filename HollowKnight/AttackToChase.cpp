#include "AttackToChase.h"
#include "BlackBoard.h"

bool AttackToChase::CanNext() const
{
    return !blackBoard->isInRange;
}
