#pragma once
#include "MovementComponent.h"

class MobMovementComponent : public MovementComponent
{
	float minRange;
	Vector2f destination;
	function<void()> callback;

	bool isJumping;
	float jumpForce;
	float jumpDuration;

	bool isFlying;

	bool isOnGround;
	float checkGroundDistance;

public:
	void SetDestination(const Vector2f& _destination, const bool _canMove = true);
	void SetCallback(const function<void()>& _callback)
	{
		callback = _callback;
	}
	void SetIsFlying(const bool _status)
	{
		isFlying = _status;
	}
	Vector2f GetDestination() const
	{
		return destination;
	}

public:
	MobMovementComponent(Actor* _owner);

private:
	void MoveToDestination(const float _deltaTime);
	bool CheckGround();

public:
	virtual void Update(const float _deltaTime) override;
	bool IsAtPosition() const;
};

