#include "PatrolState.h"
#include "Macro.h"

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
	goalPosition = startPosition + Vector2f(500.0f, 0.0f);

	animation = brain->GetOwner()->GetComponent<AnimationComponent>();
	movement = brain->GetOwner()->GetComponent<MobMovementComponent>();
	movement->SetCallback([&]() 
		{
			movement->SetCanMove(false);
			new Timer([&]() {
				movement->SetCanMove(true);
				if (movement->GetDestination() == startPosition)
				{
					movement->SetDestination(goalPosition);
					animation->GetCurrentAnimation()->SetDirectionX(1.0f);
				}
				else
				{
					movement->SetDestination(startPosition);
					animation->GetCurrentAnimation()->SetDirectionX(-1.0f);
				}
				}, seconds(2.0f), true, false);
		});

	std::cout << "Start Patrol" << endl;
}

void PatrolState::Update(const float _deltaTime)
{
	State::Update(_deltaTime);

	/*if (animation->GetCurrentAnimation()->GetData().name == "Idle")
	{
		if (Animation* _animation = animation->GetCurrentAnimation())
		{
			const float _directionX = animation->GetCurrentAnimation()->GetDirectionX();
			animation->RunAnimation("Run", _directionX);

			if (movement->GetDestination() == startPosition)
			{
				movement->SetDestination(goalPosition);
				animation->GetCurrentAnimation()->SetDirectionX(1.0f);
			}
			else
			{
				movement->SetDestination(startPosition);
				animation->GetCurrentAnimation()->SetDirectionX(-1.0f);
			}
		}
	}*/

	//cout << "Update Patrol" << endl;
}

void PatrolState::Stop()
{
	cout << "Stop Patrol" << endl;
}
