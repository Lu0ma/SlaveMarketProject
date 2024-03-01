#pragma once
#include "MovementComponent.h"
#include "PlayerAnimationComponent.h"

class PlayerMovementComponent : public MovementComponent
{
	// Movement
	bool canMove;
	float speed;
	Vector2f direction;

	// Sprintç
	bool isSprinting;
	float sprintSpeed;

	// Ground
	bool isOnGround;
	float checkGroundDistance;

	// Jump
	bool isJumping;
	float jumpForce;
	float jumpDuration;
	float gravity;

	// Dash
	bool canDash;
	bool isDashing;
	bool isResetingDash;
	float dashSpeed;
	float dashDuration;
	float dashCooldown;
	Vector2f dashDirection;

	// Sit
	bool isStanding;
	float sitOffset;

	// Components
	PlayerAnimationComponent* animation;

public:
	void SetDirectionX(const float _directionX, const string& _animName)
	{
		if (!canMove) return;

		direction.x = _directionX;
		animation->GetCurrentAnimation()->RunAnimation(_animName);
	}
	void SetDirectionY(const float _directionY)
	{
		if (!canMove) return;
		direction.y = _directionY;
	}
	void SetSprint(const bool _status)
	{
		isSprinting = _status;
	}
	bool IsStanding() const
	{
		return isStanding;
	}

public:
	PlayerMovementComponent(Actor* _owner);

private:
	bool CheckGround();

public:
	virtual void Update(const float _deltaTime) override;
	void Jump();
	void Dash();
	void SitDown();
	void StandUp();
};