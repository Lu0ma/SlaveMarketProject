#include "HuskBully.h"
#include "Animation.h"

#define PATH_HUSK_BULLY "Animations/HuskBully.png"

HuskBully::HuskBully(const ShapeData& _data) : Mob(_data)
{

}


void HuskBully::Init()
{
	const Vector2f& _sizeIdle = Vector2f(105.0f, 135.0f); // ratio fait de la taille d'une image dans le sheet
	const Vector2f& _sizeWalk = Vector2f(113.0f, 135.0f);
	const Vector2f& _sizeAttack = Vector2f(123.0f, 139.0f);
	const Vector2f& _sizeAttackLunge = Vector2f(111.0f, 127.0f);
	const Vector2f& _sizeDeath = Vector2f(140.0f, 113.0f);
	const Vector2f& _sizeDeathLand = Vector2f(154.0f, 124.0f);
	const ReadDirection& _readDirection = READ_RIGHT;
	const bool _toRepeat = true;
	const float _speedIdle = 0.15f;
	const float _speedWalk = 0.1f;

	animation->InitAnimations({
		AnimationData("AttackLeft", Vector2f(0.0f, 474.0f), _sizeAttack, _readDirection, false, 4, _speedIdle, true, "AttackLunge_L"),
		AnimationData("AttackRight", Vector2f(0.0f, 474.0f), _sizeAttack, _readDirection, false, 4, _speedIdle, false, "AttackLunge_R"),
		AnimationData("WalkLeft", Vector2f(0.0f, 171.0f), _sizeWalk, _readDirection, true, 7, _speedWalk, true, "TurnToRight"),
		AnimationData("WalkRight", Vector2f(0.0f, 171.0f), _sizeWalk, _readDirection, true, 7, _speedWalk, false, "TurnToLeft"),
		AnimationData("IdleLeft", Vector2f(5.0f, 21.0f), _sizeIdle, _readDirection, false, 6, _speedIdle, true, "AttackRight"),
		AnimationData("IdleRight", Vector2f(5.0f, 21.0f), _sizeIdle, _readDirection, false, 6, _speedIdle, false, "AttackLeft"),
		AnimationData("TurnToLeft", Vector2f(0.0f, 320.0f), _sizeIdle, _readDirection, false, 2, _speedIdle, false, "WalkLeft"),
		AnimationData("TurnToRight", Vector2f(0.0f, 320.0f), _sizeIdle, _readDirection, false, 2, _speedIdle, true, "WalkRight"),
		AnimationData("AttackLunge_L", Vector2f(0.0f, 632.f), _sizeAttackLunge, _readDirection, true, 2, 0.15f, true, "AttackCooldown_L"),
		AnimationData("AttackLunge_R", Vector2f(0.0f, 632.f), _sizeAttackLunge, _readDirection, true, 2, 0.15f, false, "AttackCooldown_R"),
		AnimationData("AttackCooldown_L", Vector2f(0.0f, 776.f), _sizeAttackLunge, _readDirection, false, 1, 0.2f, true, "IdleLeft"),
		AnimationData("AttackCooldown_R", Vector2f(0.0f, 776.f), _sizeAttackLunge, _readDirection, false, 1, 0.2f, false, "IdleRight"),
		AnimationData("DeathAirLeft", Vector2f(0.0f, 920.f), _sizeDeath, _readDirection, false, 1, 0.2f, true, "DeathLandLeft"),
		AnimationData("DeathAirRight", Vector2f(0.0f, 920.f), _sizeDeath, _readDirection, false, 1, 0.2f, false, "DeathLandRight"),
		AnimationData("DeathLandLeft", Vector2f(16.0f, 1050.0f), _sizeDeathLand, _readDirection, true, 8, 0.2f),
		AnimationData("DeathLandRight", Vector2f(16.0f, 1050.0f), _sizeDeathLand, _readDirection, true, 8, 0.15f, false),
	});
}

void HuskBully::Death()
{

}