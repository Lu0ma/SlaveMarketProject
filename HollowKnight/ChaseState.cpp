#include "ChaseState.h"
#include "BossBrain.h"

ChaseState::ChaseState(Brain* _brain) : State(_brain)
{
	BlackBoard* _blackboard = _brain->GetBlackBoard();
	chaseToPatrol = new ChaseToPatrol(_blackboard);
	transitions.push_back(chaseToPatrol);
	
	chaseToAttack = new ChaseToAttack(_blackboard);
	transitions.push_back(chaseToAttack);
}


void ChaseState::Init()
{
	chaseToPatrol->Init(dynamic_cast<BossBrain*>(brain)->GetPatrolState());
	chaseToAttack->Init(dynamic_cast<BossBrain*>(brain)->GetAttackState());
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
