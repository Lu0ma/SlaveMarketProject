#include "DeathMob.h"
#include "Game.h"
#include "Player.h"
#include "CollectableActor.h"
#include "Macro.h"

DeathMob::DeathMob(const string& _name, const ShapeData& _data) : Mob(_data)
{
	animDeath = vector<string>();
	name = _name;
	death = 0;
}

void DeathMob::Init()
{
	animDeath.push_back("StandBy");
	animDeath.push_back("Explosion");

	const Vector2f& _size = Vector2f(110.0f, 148.1f);
	const ReadDirection& _readDirection = READ_DOWN;
	const bool _toRepeat = true;
	const int _count = 5;
	const float _speed = 0.1f;

	animation->InitAnimations({
		AnimationData("StandBy", Vector2f(0.0f, 0.0f), _size, _readDirection, _toRepeat, _count, _speed),
		AnimationData("Explosion", Vector2f(490.0f, 1103.0f), Vector2f(99.0f, 228.0f), _readDirection, _toRepeat, 3, _speed),
		AnimationData("Death", Vector2f(0.0f, 0.0f), Vector2f(0.0f,0.0f), _readDirection, _toRepeat, 1, _speed),
	});
}

void DeathMob::Death()
{
	if (GetLife()->GetLife() > 0)
	{
		return;
	}
 	else if (GetLife()->GetLife() <= 0)
	{
		death++; 
		animation->RunAnimation("Death", GetDrawable()->getScale().x);
		GetDrawable()->setScale(Vector2f(0.0f, 0.0f));
		int _newDeath = Random<int>(10000, 0);
		new CollectableActor("Geo"+ to_string(_newDeath), ShapeData(Vector2f(GetShapePosition().x, GetShapePosition().y + 20.0f), Vector2f(50.0f, 50.0f), "Animations/Geos.png"), 30.0f, IT_GEOS);
	}
}
 
void DeathMob::Update(const float _deltaTime)
{
	Action();
}

bool DeathMob::IsDead()
{
	Death();
	return false;
}


void DeathMob::StandBy()
{
	animation->RunAnimation("StandBy", GetDrawable()->getScale().x);
}

void DeathMob::Action()
{
	StandBy();
	Attack(Game::GetPlayer());
	//Dead();//
}

void DeathMob::Attack(Player* _player)
{
	if (GetDrawable()->getGlobalBounds().contains(_player->GetShapePosition()))
	{
		animation->RunAnimation("Explosion", GetDrawable()->getScale().x);
		_player->GetStats()->UpdateLife(-1);
	}
}