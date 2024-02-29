#pragma once
#include "MovementComponent.h"

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

	#pragma region Jump & Dash

	bool canJumpAndDash;

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

	#pragma endregion

public:
	void SetDirectionX(const float _directionX)
	{
		direction.x = _directionX;
	}
	void SetDirectionY(const float _directionY)
	{
		direction.y = _directionY;
	}
	void SetSprint(const bool _status)
	{
		isSprinting = _status;
	}
	void SetCanJumpAndDash(const bool _status)
	{
		canJumpAndDash = _status;
	}

public:
	PlayerMovementComponent(Actor* _owner);

private:
	bool CheckGround();

public:
	virtual void Update(const float _deltaTime) override;
	void Jump();
	void Dash();
};