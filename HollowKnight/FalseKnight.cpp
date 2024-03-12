#include "FalseKnight.h"

FalseKnight::FalseKnight(const ShapeData& _data) : Boss(_data)
{
	movement->SetIsFlying(true);
}

void FalseKnight::Init()
{
	const Vector2f& _size = Vector2f(655.0f, 586.0f);

	const float _speed = 0.15f;

	animation->InitAnimations(
	{
		AnimationData("Idle", Vector2f(0.0f, 0.0f), _size, READ_RIGHT, true, 5, _speed, ""),

		AnimationData("Turn", Vector2f(0.0f, 586.0f), _size, READ_RIGHT, false, 2, _speed, "Run"),
		AnimationData("Run", Vector2f(0.0f, 1172.0f), _size, READ_RIGHT, false, 3, _speed, "Running"),
		AnimationData("Running", Vector2f(0.0f, 1758.0f), _size, READ_RIGHT, true, 4, _speed, "Idle"),

		AnimationData("Jump", Vector2f(0.0f, 2344.0f), _size, READ_RIGHT, false, 3, 0.5f, "Jumping"),
		AnimationData("Jumping", Vector2f(0.0f, 2930.0f), _size, READ_RIGHT, true, 4, _speed, "Land"),
		AnimationData("Land", Vector2f(0.0f, 3516.0f), _size, READ_RIGHT, false, 3, 0.05f, "Idle"),

		AnimationData("Attack", Vector2f(0.0f, 4102.0f), _size, READ_RIGHT, false, 6, _speed, "AttackReach"),
		AnimationData("AttackReach", Vector2f(0.0f, 4688.0f), _size, READ_RIGHT, false, 3, 0.1f, "AttackCooldown"),
		AnimationData("AttackCooldown", Vector2f(0.0f, 5274.0f), _size, READ_RIGHT, false, 5, _speed, "Idle"),

		AnimationData("PreJumpAttack", Vector2f(0.0f, 2344.0f), _size, READ_RIGHT, false, 3, 0.5f, "JumpAttack"),
		AnimationData("JumpAttack", Vector2f(0.0f, 5860.0f), _size, READ_RIGHT, false, 5, _speed, "JumpAttackP1"),
		AnimationData("JumpAttackP1", Vector2f(0.0f, 6446.0f), _size, READ_RIGHT, false, 2, _speed, "JumpAttackP2"),
		AnimationData("JumpAttackP2", Vector2f(0.0f, 7032.0f), _size, READ_RIGHT, false, 2, _speed, "JumpAttackP3"),
		AnimationData("JumpAttackP3", Vector2f(0.0f, 7618.0f), _size, READ_RIGHT, false, 2, 0.2f, "PreJumpAttack"),

		AnimationData("StunRoll", Vector2f(0.0f, 8204.0f), _size, READ_RIGHT, false, 5, _speed, "StunEnd"),
		AnimationData("StunEnd", Vector2f(0.0f, 8790.0f), _size, READ_RIGHT, false, 4, _speed, "StunOpen"),
		AnimationData("StunOpen", Vector2f(0.0f, 9376.0f), _size, READ_RIGHT, false, 4, _speed, "StunOpened"),
		AnimationData("StunOpened", Vector2f(0.0f, 9962.0f), _size, READ_RIGHT, false, 1, _speed, "StunHit"),
		AnimationData("StunHit", Vector2f(0.0f, 10548.0f), _size, READ_RIGHT, false, 3, _speed, "StunRoll"),
		//TODO STUN HIT

		AnimationData("DeathFall", Vector2f(0.0f, 11134.0f), _size, READ_RIGHT, false, 3, _speed, "DeathLand"),
		AnimationData("DeathLand", Vector2f(0.0f, 11720.0f), _size, READ_RIGHT, false, 5, _speed, "Body"),
		AnimationData("Body", Vector2f(0.0f, 12306.0f), _size, READ_RIGHT, true, 1, _speed, ""),

	});
}