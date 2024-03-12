#include "Transition.h"

Transition::Transition(BlackBoard* _blackBoard)
{
	blackBoard = _blackBoard;
	nextState = nullptr;
}