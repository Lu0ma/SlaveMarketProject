#include "PatrolState.h"
#include "Brain.h"
#include "Macro.h"
#include "MobLifeComponent.h"

PatrolState::PatrolState(Brain* _brain) : State(_brain)
{
	/*animation = nullptr;
	movement = nullptr;
	inspect = nullptr;*/
	patrolTimer = nullptr;

	startPosition = brain->GetOwner()->GetShapePosition();
	goalPosition = Vector2f();

	BlackBoard* _blackBoard = _brain->GetBlackBoard();
	patrolToDeath = new PatrolToDeath(_blackBoard);
	transitions.push_back(patrolToDeath);
}

void PatrolState::Start()
{
	//timerInspect->Start();

	std::cout << brain->GetOwner()->GetID() << "Start Patrol" << endl;

	goalPosition = startPosition + Vector2f(1500.0f, 0.0f);
	
	Actor* _owner = brain->GetOwner();

	if (!inspect || !animation || !movement )
	{
		inspect = _owner->GetComponent<InspectComponent>();
		animation = _owner->GetComponent<AnimationComponent>();
		movement = _owner->GetComponent<MobMovementComponent>();
	}

	movement->SetCallback([&]() 
		{
			movement->SetCanMove(false);
			patrolTimer = new Timer([&]()
				{
					cout << "Patrol TIMER" << endl;
					if (movement->GetDestination() == startPosition)
					{
						movement->SetDestination(goalPosition);
					}
					else
					{
						movement->SetDestination(startPosition);
					}
				}, seconds(2.0f), true, false);
		});

}

void PatrolState::Update(const float _deltaTime)
{
	State::Update(_deltaTime);

	/*if (inspect->GetHitInfo().operator!=(HitInfo()))
	{
		cout << "Karl Marx " << endl << endl << endl;
		brain->GetBlackBoard()->isInRange = inspect->IsInRange();
	}*/

	if (inspect)
	{
		brain->GetBlackBoard()->hasTarget = inspect->HasTarget(brain->GetOwner()->GetShapePosition(), movement->GetDestination());
		brain->GetBlackBoard()->isInRange = inspect->IsInRange();
	}
	if (brain->GetOwner()->GetComponent<MobLifeComponent>()->GetLife() <= 0)
	{
		brain->GetBlackBoard()->isDead = true;
	}
}

void PatrolState::Stop()
{
	//timerInspect->Pause();
	patrolTimer->Stop();
	movement->SetCallback(nullptr);
	//movement->SetDestination(brain->GetOwner()->GetShapePosition());
	//animation->RunAnimation("Idle", 1.0f);
	cout << brain->GetOwner()->GetID() << "Stop Patrol" << endl;
}

