#include "PatrolState.h"
#include "Brain.h"
#include "Macro.h"

PatrolState::PatrolState(Brain* _brain) : State(_brain)
{
	animation = nullptr;
	movement = nullptr;
	inspect = nullptr;

	startPosition = brain->GetOwner()->GetShapePosition();
	goalPosition = Vector2f();
}

void PatrolState::Start()
{
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

	std::cout << "Start Patrol" << endl;
}

void PatrolState::Update(const float _deltaTime)
{
	State::Update(_deltaTime);

	if (inspect)
	{
		brain->GetBlackBoard()->hasTarget = inspect->HasTarget(brain->GetOwner()->GetShapePosition(), movement->GetDestination());
		//brain->GetBlackBoard()->isInRange = inspect->IsInRange();
	}
}

void PatrolState::Stop()
{
	patrolTimer->Stop();
	movement->SetCallback([&]() {});
	//movement->SetDestination(brain->GetOwner()->GetShapePosition());
	//animation->RunAnimation("Idle", 1.0f);
	cout << "Stop Patrol" << endl;
}