#pragma once
#include "MovementComponent.h"
#include "PlayerAnimationComponent.h"

class PlayerMovementComponent : public MovementComponent
{
	// Movement
	Vector2f direction;

	// Sprintç
	bool isSprinting;
	float sprintSpeed;

	// Ground
	bool isOnGround;
	float checkGroundDistance;

	// Jump
	bool isJumping;
	bool canIncreaseJump;
	float jumpForce;
	float jumpDuration;
	float jumpDurationFactor;
	float gravity;
	Timer* jumpTimer;

	// Dash
	bool canDash;
	bool isDashing;
	bool isResetingDash;
	float dashSpeed;
	float dashDuration;
	float dashCooldown;
	float dashDirection;

	// Sit
	bool isStanding;
	float sitOffset;

	//Distance
	float checkWallDistance;

	// Components
	PlayerAnimationComponent* animation;

	//Actor* rayCastLineX;
	Actor* rayCastLineY;
	//Actor* triggerBox;

public:
	void SetDirectionX(const float _directionX, const string& _animName);
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
	Vector2f GetDirection() const
	{
		return direction;
	}
	float GetDashDirection()const
	{
		return dashDirection;
	}

public:
	PlayerMovementComponent(Actor* _owner);

private:
	bool CheckGround();
	void Jump();
	
public:
	virtual void Update(const float _deltaTime) override;
	void StartJump();
	void StopJump();
	void Dash();
	void SitDown();
	void StandUp();
};