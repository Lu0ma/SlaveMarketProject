#include "DeathMob.h"
#include"Game.h"
#include"Player.h"

DeathMob::DeathMob(const ShapeData& _data) : Mob(_data)
{
	animation = new AnimationComponent(this);
	components.push_back(animation);

	SetLife(1);
	Action();
}


void DeathMob::Init()
{
	const Vector2f& _size = Vector2f(110.0f, 150.1f);
	const ReadDirection& _readDirection = READ_DOWN;
	const bool _toRepeat = true;
	const int _count = 5;
	const float _speed = 0.1f;

	animation->InitAnimations({
		AnimationData("StandBy", Vector2f(0.0f, 0.0f), _size, _readDirection, _toRepeat, _count, _speed),
		AnimationData("Explosion", Vector2f(490.0f, 1103.0f), Vector2f(99.0f, 228.0f), _readDirection, _toRepeat, 3, _speed),
	});
}

void DeathMob::Death()
{
	if (GetLife() == 0)
	{
		GetDrawable()->setScale(Vector2f(0.0f, 0.0f));
	}
}


void DeathMob::StandBy()
{
	animation->RunAnimation("StandBy");
}

void DeathMob::Action()
{
	StandBy();
	Attack();
	Death();
}

void DeathMob::Attack()
{
	Player* _player = Game::GetPlayer();
	if (GetDrawable()->getGlobalBounds().contains(_player->GetPosition()))
	{
		animation->RunAnimation("Explosion");
		_player->GetStats()->UpdateLife(-1);
	}
}