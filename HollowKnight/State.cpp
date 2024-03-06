#include "State.h"
#include "Brain.h"

State::State(Brain* _brain)
{
	brain = _brain;
	nextTransition = nullptr;
}

State::~State()
{
	for (Transition* _transition : transitions)
	{
		delete _transition;
	}
}

void State::Update(const float _deltaTime)
{
	for (Transition* _transition : transitions)
	{
		if (_transition->CanNext())
		{
			nextTransition = _transition;
			return;
		}
	}
	nextTransition = nullptr;
}