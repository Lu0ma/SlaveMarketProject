#include "Boss.h"
#include "Macro.h"

Boss::Boss(const ShapeData& _data) : Enemy("Boss" + to_string(GetUniqueID()), _data)
{
	animation = new AnimationComponent(this);
	components.push_back(animation);

	movement = new MobMovementComponent(this);
	movement->SetSpeed(0.5f);
	components.push_back(movement);

	attack = new MobAttackComponent(this, 1);
	components.push_back(attack);

	life = new MobLifeComponent(this, 3);
	components.push_back(life);

	brain = new BossBrain(this);
	components.push_back(brain);

	InitTimerPatrol();
}

void Boss::FacePlayer(Player* _player)
{
		//const float _x = GetPosition().x < _player->GetPosition().x ? 1.0f : -1.0f;
		//animation->GetCurrentAnimation()->SetDirectionX(_x);
}

void Boss::Update(const float _deltaTime)
{
	Actor::Update(_deltaTime);

	//Death();

	//if (!isDead)
	//{
	//	Player* _player = Game::GetPlayer();
	//	if (animation->GetCurrentAnimation()->GetData().name == "Idle")
	//	{
	//		FacePlayer(_player);
	//		Attack(_player);
	//	}
	//	else if (movement->IsAtPosition() && animation->GetCurrentAnimation()->GetData().name == "Running")
	//	{
	//		RunLinkedAnimation("Idle", animation);
	//	}
	//}
}

void Boss::Patrol()
{

}

void Boss::InitTimerPatrol()
{
	//timer = new Timer(this, &Boss::Patrol, seconds(10.0f), true, true);
	//new Timer([&]() {brain->GetBlackBoard().hasTarget = !brain->GetBlackBoard().hasTarget; }, seconds(3.0f), true, true);
}

void Boss::RunLinkedAnimation(const string& _linkedAnimation, AnimationComponent* _animationComponent)
{
	/*_animationComponent->GetCurrentAnimation()->Stop();

	Vector2f _direction = movement->GetDestination();
	_direction -= GetPosition();
	Normalize(_direction);
	_animationComponent->RunAnimation(_linkedAnimation, _direction.x);*/
}
