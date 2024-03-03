#include "Boss.h"
#include "Macro.h"

Boss::Boss(const ShapeData& _data) : Enemy("Boss" + to_string(GetUniqueID()), _data)
{
	startPosition = _data.position;
	goalPosition = startPosition + Vector2f(2000.0f, 0.0f);

	MovementComponent* _movement = new MovementComponent(this);
	components.push_back(_movement);

	movement = new MovementComponent(this);
	movement->SetSpeed(0.5f);
	components.push_back(movement);

	attack = new MobAttackComponent(this, 1);
	components.push_back(attack);

	life = new MobLifeComponent(this, 3);
	components.push_back(life);

	InitTimerPatrol();
}

void Boss::FacePlayer(Player* _player)
{
		const float _x = GetPosition().x < _player->GetPosition().x ? 1.0f : -1.0f;
		animation->GetCurrentAnimation()->SetDirectionX(_x);
}

void Boss::Update(const float _deltaTime)
{
	Actor::Update(_deltaTime);
	Player* _player = Game::GetPlayer();

	if (animation->GetCurrentAnimation()->GetData().name == "Idle")
	{
		FacePlayer(_player);
		Attack(_player);
	}
	else if(movement->IsAtPosition() && animation->GetCurrentAnimation()->GetData().name == "Running")
	{
		RunLinkedAnimation("Idle", animation);
	}
}

void Boss::Patrol()
{
	if (animation->GetCurrentAnimation()->GetData().name == "Idle")
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
	}
}

void Boss::InitTimerPatrol()
{
	new Timer(this, &Boss::Patrol, seconds(10.0f), true, true);
}

void Boss::RunLinkedAnimation(const string& _linkedAnimation, AnimationComponent* _animationComponent)
{
	_animationComponent->GetCurrentAnimation()->Stop();

	Vector2f _direction = movement->GetDestination();
	_direction -= GetPosition();
	Normalize(_direction);
	_animationComponent->RunAnimation(_linkedAnimation, _direction.x);
}
