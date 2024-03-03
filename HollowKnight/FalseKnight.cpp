#include "FalseKnight.h"

FalseKnight::FalseKnight(const ShapeData& _data) : Boss(_data)
{
	animation = new AnimationComponent(this);
	components.push_back(animation);

}

void FalseKnight::Init()
{
	const Vector2f& _size = Vector2f(655.0f, 586.0f);

	const float _speed = 0.15f;

	//=====================================================================
	// 
	//=====================================================================

	animation->InitAnimations(
	{
		AnimationData("Idle", Vector2f(0.0f, 0.0f), _size, READ_RIGHT, true, 5, _speed, true, ""),

		AnimationData("Turn", Vector2f(0.0f, 586.0f), _size, READ_RIGHT, false, 2, _speed, true, "Run"),
		AnimationData("Run", Vector2f(0.0f, 1172.0f), _size, READ_RIGHT, false, 3, _speed, true, "Running"),
		AnimationData("Running", Vector2f(0.0f, 1758.0f), _size, READ_RIGHT, true, 4, _speed, true, "Idle"),

		AnimationData("Jump", Vector2f(0.0f, 2344.0f), _size, READ_RIGHT, false, 3, 0.5f, true, "Jumping"),
		AnimationData("Jumping", Vector2f(0.0f, 2930.0f), _size, READ_RIGHT, true, 4, _speed, true, "Land"),
		AnimationData("Land", Vector2f(0.0f, 3516.0f), _size, READ_RIGHT, false, 3, 0.05f, true, "Idle"),

		AnimationData("Attack", Vector2f(0.0f, 4102.0f), _size, READ_RIGHT, false, 6, _speed, true, "AttackReach"),
		AnimationData("AttackReach", Vector2f(0.0f, 4688.0f), _size, READ_RIGHT, false, 3, 0.1f, true, "AttackCooldown"),
		AnimationData("AttackCooldown", Vector2f(0.0f, 5274.0f), _size, READ_RIGHT, false, 5, _speed, true, "Idle"),

		AnimationData("PreJumpAttack", Vector2f(0.0f, 2344.0f), _size, READ_RIGHT, false, 3, 0.5f, true, "JumpAttack"),
		AnimationData("JumpAttack", Vector2f(0.0f, 5860.0f), _size, READ_RIGHT, false, 5, _speed, true, "JumpAttackP1"),
		AnimationData("JumpAttackP1", Vector2f(0.0f, 6446.0f), _size, READ_RIGHT, false, 2, _speed, true, "JumpAttackP2"),
		AnimationData("JumpAttackP2", Vector2f(0.0f, 7032.0f), _size, READ_RIGHT, false, 2, _speed, true, "JumpAttackP3"),
		AnimationData("JumpAttackP3", Vector2f(0.0f, 7618.0f), _size, READ_RIGHT, false, 2, 0.2f, true, "PreJumpAttack"),

		AnimationData("StunRoll", Vector2f(0.0f, 8204.0f), _size, READ_RIGHT, false, 5, _speed, true, "StunEnd"),
		AnimationData("StunEnd", Vector2f(0.0f, 8790.0f), _size, READ_RIGHT, false, 4, _speed, true, "StunOpen"),
		AnimationData("StunOpen", Vector2f(0.0f, 9376.0f), _size, READ_RIGHT, false, 4, _speed, true, "StunOpened"),
		AnimationData("StunOpened", Vector2f(0.0f, 9962.0f), _size, READ_RIGHT, false, 1, _speed, true, "StunHit"),
		AnimationData("StunHit", Vector2f(0.0f, 10548.0f), _size, READ_RIGHT, false, 3, _speed, true, "StunRoll"),
		//TODO STUN HIT

		AnimationData("DeathFall", Vector2f(0.0f, 11134.0f), _size, READ_RIGHT, false, 3, _speed, true, "DeathLand"),
		AnimationData("DeathLand", Vector2f(0.0f, 11720.0f), _size, READ_RIGHT, false, 5, _speed, true, "Body"),
		AnimationData("Body", Vector2f(0.0f, 12306.0f), _size, READ_RIGHT, false, 1, _speed, true, "DeathFall"),

	});
}

void FalseKnight::Attack(Player* _player)
{
	Vector2f _playerPos = _player->GetDrawable()->getGlobalBounds().getPosition();
	if (GetDrawable()->getGlobalBounds().contains(_playerPos))
	{
		float _directionX = animation->GetCurrentAnimation()->GetDirectionX();
		animation->RunAnimation("Attack", _directionX);
		_player->GetStats()->UpdateLife(-1);
	}
}
