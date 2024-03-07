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

	// Components
	PlayerAnimationComponent* animation;

public:
	void SetDirectionX(const float _directionX, const string& _animName)
	{
		if (!canMove) return;

		direction.x = _directionX;

		if (_directionX == 0.0f)
		{
			cout << owner->GetDrawable()->getScale().x << endl;

			if (owner->GetDrawable()->getScale().x >= 0.0f)
			{
				dashDirection = 1.0f;
			}

			else
			{
				dashDirection = -1.0f;
			}
		}

		else
		{
			dashDirection = _directionX;
		}

		animation->GetCurrentAnimation()->RunAnimation(_animName, dashDirection);
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
	Vector2f GetDirection() const
	{
		return direction;
	}

public:
	PlayerMovementComponent(Actor* _owner);

private:
	bool CheckGround();
	void Jump(const float _deltaTime);

public:
	virtual void Update(const float _deltaTime) override;
	void StartJump();
	void StopJump();
	void Dash();
	void SitDown();
	void StandUp();
};