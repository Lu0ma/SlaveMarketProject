#include "Brain.h"

Brain::Brain(Actor* _owner) : Component(_owner)
{
	blackBoard = BlackBoard();

	patrol = new PatrolState(this);
	chase = new ChaseState(this);
	currentState = nullptr;
	attack = nullptr;
}

Brain::~Brain()
{
	delete attack;
	delete patrol;
	delete chase;
}

void Brain::Update(const float _deltaTime)
{
	currentState->Update(_deltaTime);

	if (Transition* _transition = currentState->GetNextTransition())
	{
		currentState->Stop();

		currentState = _transition->GetNextState();

		currentState->Start();
	}
}