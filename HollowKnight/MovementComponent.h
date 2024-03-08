#pragma once
#include "Component.h"
#include <SFML/Graphics.hpp>
#include "CollisionComponent.h"
#include <functional>
#include <iostream>

using namespace std;
using namespace sf;

class MovementComponent : public Component
{
protected:
	bool canMove;
	float speed;
	float minRange;
	Vector2f destination;
	function<void()> callback;
	CollisionComponent* collision;



public:

	void SetSpeed(const float _speed)
	{
		speed = _speed;
	}
	void SetCanMove(const bool _status)
	{
		canMove = _status;
	}
	void SetDestination(const Vector2f& _destination, const bool _canMove = true)
	{
		destination = _destination;
		//cout << destination.x << " " << destination.y << endl;
		canMove = _canMove;
	}
	void SetCallback(const function<void()>& _callback)
	{
		callback = _callback;
	}
	bool GetCanMove() const
	{
		return canMove;
	}
	Vector2f GetDestination() const
	{
		return destination;
	}

public:
	MovementComponent(Actor* _owner);

private:
	void MoveToDestination(const float _deltaTime);
public:
	virtual void Update(const float _deltaTime) override;
	bool IsAtPosition() const;

};