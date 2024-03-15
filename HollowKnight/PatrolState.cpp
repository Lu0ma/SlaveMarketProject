#include "PatrolState.h"
#include "Brain.h"

PatrolState::PatrolState(Brain* _brain) : State(_brain)
{
	patrolToDeath = new PatrolToDeath(_brain->GetBlackBoard());
	transitions.push_back(patrolToDeath);
}


void PatrolState::Start()
{
	cout << brain->GetOwner()->GetID() << "Start Patrol" << endl;

	if (!inspect)
	{
		Actor* _owner = brain->GetOwner();
		inspect = _owner->GetComponent<InspectComponent>();
	}
}

void PatrolState::Update(const float _deltaTime)
{
	State::Update(_deltaTime);

	brain->GetBlackBoard()->hasTarget = inspect->HasTarget();
}

void PatrolState::Stop()
{
	cout << brain->GetOwner()->GetID() << "Stop Patrol" << endl;
}