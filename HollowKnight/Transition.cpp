#include "Transition.h"
#include "State.h"
#include "Brain.h"

Transition::Transition(Brain* _brain)
{
	brain = _brain;
	blackBoard = &_brain->GetBlackBoard();
}
