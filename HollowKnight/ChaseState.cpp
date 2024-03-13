#include "ChaseState.h"
#include "BossBrain.h"
#include "MobLifeComponent.h"

ChaseState::ChaseState(Brain* _brain) : State(_brain)
{
	animation = nullptr;
	movement = nullptr;
	inspect = nullptr;

	BlackBoard* _blackboard = _brain->GetBlackBoard();
	chaseToPatrol = new ChaseToPatrol(_blackboard);
	transitions.push_back(chaseToPatrol);
	
	chaseToAttack = new ChaseToAttack(_blackboard);
	transitions.push_back(chaseToAttack);

	chaseToDeath = new ChaseToDeath(_blackboard);
	transitions.push_back(chaseToDeath);
}

void ChaseState::Init()
{
	chaseToPatrol->Init(dynamic_cast<BossBrain*>(brain)->GetPatrolState());
	chaseToAttack->Init(dynamic_cast<BossBrain*>(brain)->GetAttackState());
}

void ChaseState::Start()
{
	Actor* _owner = brain->GetOwner();

	if (!inspect || !animation || !movement)
	{
		inspect = _owner->GetComponent<InspectComponent>();
		animation = _owner->GetComponent<AnimationComponent>();
		movement = _owner->GetComponent<MobMovementComponent>();
	}

	// set Le movement pour qu'il suive le player pendant un certain temps
	/*movement->SetCallback([&]() 
		{
			movement->SetCanMove(true);
		});*/

	cout << "StartChase TIMER" << endl;
	chaseTimer = new Timer([&]()
		{
			Actor* _actor = inspect->GetHitInfo().actor;
			if (_actor)
			{
				movement->SetDestination(Vector2f(_actor->GetShapePosition().x, brain->GetOwner()->GetShapePosition().y));
			}
		}, seconds(0.050f), true, true);
	new Timer([&]()
		{
			cout << "StopChase TIMER" << endl;
			chaseTimer->Stop();
			brain->GetBlackBoard()->hasTarget = false; //pour repasser en patrol
		}, seconds(5.0f), true, false);

	cout << "Start Chase" << endl;
}

void ChaseState::Update(const float _deltaTime)
{
	if (inspect)
	{
		inspect->HasTarget(brain->GetOwner()->GetShapePosition(), movement->GetLastDirection());
		brain->GetBlackBoard()->isInRange = inspect->IsInRange();
	}

	State::Update(_deltaTime);
	//FacePLayer();
	//cout << "Update Chase" << endl;
	if (brain->GetOwner()->GetComponent<MobLifeComponent>()->GetLife() <= 0)
	{
		brain->GetBlackBoard()->isDead = true;
	}
}

void ChaseState::Stop()
{	
	chaseTimer->Stop();
	movement->SetDestination(brain->GetOwner()->GetShapePosition());

	cout << "Stop Chase" << endl;
}
