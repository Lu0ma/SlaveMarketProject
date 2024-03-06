#include "PatrolState.h"
#include "Macro.h"
#include "Brain.h"

PatrolState::PatrolState(Brain* _brain) : State(_brain)
{
	animation = nullptr;
	movement = nullptr;

	patrolToChase = new PatrolToChase(brain);
	transitions.push_back(patrolToChase);
}

void PatrolState::Init()
{
	patrolToChase->Init();
}

void PatrolState::Start()
{
	startPosition = brain->GetOwner()->GetShapePosition();
	goalPosition = startPosition + Vector2f(1000.0f, 0.0f);

	animation = brain->GetOwner()->GetComponent<AnimationComponent>();
	movement = brain->GetOwner()->GetComponent<MobMovementComponent>();
	movement->SetCallback([&]() 
		{
			movement->SetCanMove(false);
			new Timer([&]() 
				{				
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

	//cout << "Update Patrol" << endl;
}

void PatrolState::Stop()
{
	cout << "Stop Patrol" << endl;
}
