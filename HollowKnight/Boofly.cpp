#include "Boofly.h"
#include "MovementComponent.h"
#include "CollectableActor.h"
#include "TimerManager.h"
Boofly::Boofly(const ShapeData& _data) : Mob(_data)
{ 
	isPatrolling = true;
	life = new MobLifeComponent(this, 1);
}

void Boofly::Init()
{
	const Vector2f& _size = Vector2f(315.0f, 345.0f);
	const Vector2f& _sizeBounce = Vector2f(300.0f, 360.0f);
	const Vector2f& _sizeDeathAir = Vector2f(300.0f, 330.0f);
	const Vector2f& _sizeDeathLand = Vector2f(337.0f, 265.0f);
	const int _count = 4;
	const float _speed = 0.12f;
	const float _speedTurn = 0.09f;

	animation->InitAnimations({
		AnimationData("Go", Vector2f(0.0f, 17.0f), _size, READ_RIGHT, true, 5, _speed, "Turn"),
		AnimationData("Turn", Vector2f(0.0f, 380.0f), _size, READ_RIGHT, false, 4, _speedTurn, "Go"),
		AnimationData("Bounce", Vector2f(42.0f, 745.0f), _sizeBounce, READ_RIGHT, false, 2, _speed),
		AnimationData("DeathAir", Vector2f(0.0f, 1120.0f), _sizeDeathAir, READ_RIGHT, false, 4, _speed, "DeathLand"),
		AnimationData("DeathLand", Vector2f(0.0f, 1480.0f), _sizeDeathLand, READ_RIGHT, false, 3, _speed),

		/*AnimationData("GoLeft", Vector2f(0.0f, 17.0f), _size, READ_RIGHT, true, 5, _speed, true, "TurnToRight"),
		AnimationData("GoRight", Vector2f(0.0f, 17.0f), _size, READ_RIGHT, true, 5, _speed, false, "TurnToLeft"),
		AnimationData("TurnToLeft", Vector2f(0.0f, 380.0f), _size, READ_RIGHT, false, 4, _speedTurn, true, "GoLeft"),
		AnimationData("TurnToRight", Vector2f(0.0f, 380.0f), _size, READ_RIGHT, false, 4, _speedTurn, false, "GoRight"),
		AnimationData("BounceLeft", Vector2f(42.0f, 745.0f), _sizeBounce, READ_RIGHT, false, 2, _speed),
		AnimationData("BounceRight", Vector2f(42.0f, 745.0f), _sizeBounce, READ_RIGHT, false, 2, _speed, false),
		AnimationData("DeathAirLeft", Vector2f(0.0f, 1120.0f), _sizeDeathAir, READ_RIGHT, true, 4, _speed),
		AnimationData("DeathAirRight", Vector2f(0.0f, 1120.0f), _sizeDeathAir, READ_RIGHT, true, 4, _speed, false),
		AnimationData("DeathLand", Vector2f(0.0f, 1480.0f), _sizeDeathLand, READ_RIGHT, false, 3, _speed),*/
	});
}

void Boofly::Death()
{
 	if (life->GetLife() <= 0 && isPatrolling)
	{
		float _directionX = animation->GetCurrentAnimation()->GetDirectionX();
		animation->RunAnimation("DeathAir", _directionX);
		isPatrolling = false;
		movement->SetCanMove(false);
		cout << "Moooort" << endl;
		//new Timer([&]() { GetDrawable()->setScale(0.0f, 0.0f); }, seconds(2.0f));
		CollectableActor* _geo = new CollectableActor(STRING_ID("Geo"), ShapeData(Vector2f(GetPosition().x, GetPosition().y + 20.0f), Vector2f(50.0f, 50.0f), "Animations/Geos.png"), 30.0f, IT_GEOS);
		_geo->Destroy(2.0f);
		//TimerManager::GetInstance().SetTimeScale(0);
		//if (TimerManager::GetInstance().GetDeltaTime() == 0)
		//{
		//	new Timer([&]() {TimerManager::GetInstance().SetTimeScale(1); }, seconds(2));
		//}
	}
	
}

void Boofly::Attack(Player* _player)
{

}