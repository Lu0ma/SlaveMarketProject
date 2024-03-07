#include "ChaseState.h"
#include "Brain.h"
#include "InspectComponent.h"
#include "MovementComponent.h"

ChaseState::ChaseState(Brain* _brain) : State(_brain)
{
	chaseToPatrol = new ChaseToPatrol(_brain);
	transitions.push_back(chaseToPatrol);
}

void ChaseState::Init()
{
	chaseToPatrol->Init();
}

void ChaseState::Start()
{
	cout << "Start Chase" << endl;
}

void ChaseState::Update(const float _deltaTime)
{
	State::Update(_deltaTime);
	//FacePLayer();
	//cout << "Update Chase" << endl;
	Actor* _owner = brain->GetOwner();
	InspectComponent* _inspect = _owner->GetComponent<InspectComponent>();

	_inspect->HasTarget(_owner->GetShapePosition(), _owner->GetComponent<MobMovementComponent>()->GetDestination());
}

void ChaseState::Stop()
{	
	cout << "Stop Chase" << endl;
}
