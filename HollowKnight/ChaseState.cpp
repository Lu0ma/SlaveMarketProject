#include "ChaseState.h"
#include "BossBrain.h"
#include "EnemyLifeComponent.h"

ChaseState::ChaseState(Brain* _brain) : State(_brain)
{
	/*animation = nullptr;
	movement = nullptr;
	inspect = nullptr;*/
	chaseTimer = nullptr;

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
	chaseToDeath->Init(dynamic_cast<BossBrain*>(brain)->GetDeathState());
}

void ChaseState::Start()
{
	//timerInspect->Start();
	cout << brain->GetOwner()->GetID() << "Start Chase" << endl;

	//Actor* _owner = brain->GetOwner();

	//if (!inspect || !animation || !patrol)
	//{
	//	inspect = _owner->GetComponent<InspectComponent>();
	//	animation = _owner->GetComponent<AnimationComponent>();
	//	patrol = _owner->GetComponent<MobMovementComponent>();
	//}

	//// set Le movement pour qu'il suive le player pendant un certain temps
	///*movement->SetCallback([&]() 
	//	{
	//		movement->SetCanMove(true);
	//	});*/

	//cout << "StartChase TIMER" << endl;
	//chaseTimer = new Timer([&]()
	//	{
	//		Actor* _actor = inspect->GetHitInfo().actor;
	//		if (_actor)
	//		{
	//			patrol->SetDestination(Vector2f(_actor->GetShapePosition().x, brain->GetOwner()->GetShapePosition().y));
	//		}
	//	}, seconds(0.050f), true, true);
	//stopChaseTimer	= new Timer([&]()
	//	{
	//		cout << "StopChase TIMER" << endl;
	//		chaseTimer->Stop();
	//		brain->GetBlackBoard()->hasTarget = false; //pour repasser en patrol
	//	}, seconds(5.0f), true, false);

}

void ChaseState::Update(const float _deltaTime)
{
	State::Update(_deltaTime);

	//if (inspect)
	//{
	//	/*inspect->HasTarget(brain->GetOwner()->GetShapePosition(), patrol->GetLastDirection());
	//	brain->GetBlackBoard()->isInRange = inspect->IsInRange();*/
	//}
	//if (brain->GetOwner()->GetComponent<EnemyLifeComponent>()->GetLife() <= 0)
	//{
	//	brain->GetBlackBoard()->isDead = true;
	//}

	//FacePLayer();
	//cout << "Update Chase" << endl;
}

void ChaseState::Stop()
{	
	//timerInspect->Pause();
	//chaseTimer->Stop();
	//stopChaseTimer->Stop();
	//patrol->SetDestination(brain->GetOwner()->GetShapePosition());

	cout << brain->GetOwner()->GetID() << "Stop Chase" << endl;
}