#include "Brain.h"

Brain::Brain(Actor* _owner) : Component(_owner)
{
	blackBoard = new BlackBoard();
}

Brain::~Brain()
{
	delete blackBoard;
	delete currentState;
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