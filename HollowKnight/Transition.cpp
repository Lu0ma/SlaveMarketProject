#include "Transition.h"
#include "Brain.h"

Transition::Transition(Brain* _brain)
{
	brain = _brain;
	blackBoard = &_brain->GetBlackBoard();
}
