#include "PlayerMovementComponent.h"
#include "Actor.h"
#include "PlayerAnimationComponent.h"
#include "Game.h"
#include "Timer.h"
#include "Macro.h"
#include "Kismet.h"
#include "FxManager.h"

void PlayerMovementComponent::SetDirectionX(const float _directionX, const string& _animName)
{
	if (!canMove) return;

	direction.x = _directionX;

	if (_directionX == 0.0f)
	{
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

PlayerMovementComponent::PlayerMovementComponent(Actor* _owner) : MovementComponent(_owner)
{
	// Movement
	canMove = false;
	speed = 0.45f;
	direction = Vector2f();

	// Sprint
	isSprinting = false;
	sprintSpeed = 0.3f;

	// Ground
	isOnGround = false;
	checkGroundDistance = owner->GetShapeSize().y * 0.3f;

	// Jump
	isJumping = false;
	canIncreaseJump = false;
	jumpForce = 0.6f;
	currentJumpForce = jumpForce;
	jumpForceFactor = 2.0f;
	jumpDuration = 0.15f;
	jumpDurationFactor = 1.0f;
	increaseJumpDuration = 2.0f;
	gravity = 0.8f;
	increaseJumpTimer = nullptr;
	jumpTimer = nullptr;

	// Dash
	canDash = true;
	isDashing = false;
	isResetingDash = false;
	dashSpeed = 1.50f;
	dashDuration = 0.25f;
	dashCooldown = 0.60f;
	dashDirection = 1.0f;

	// Sit
	isStanding = true;
	sitOffset = 30.0f;

	//Distance
	checkWallDistance = owner->GetShapeSize().x / 2.0f;

	// Components
	animation = owner->GetComponent<PlayerAnimationComponent>();

	rayCastLineY = new Actor("raycastlineY", ShapeData(owner->GetShapePosition(), Vector2f(5.0f, checkGroundDistance) , ""));
	rayCastLineY->GetDrawable()->setFillColor(Color::Blue);
	rayCastLineY->GetComponent<CollisionComponent>()->GetBoxCollision()->GetDrawable()->setFillColor(Color::Transparent);
}

bool PlayerMovementComponent::CheckGround()
{
	HitInfo _info;
	rayCastLineY->GetDrawable()->setPosition(owner->GetShapePosition() + Vector2f(0.0f, owner->GetShapeSize().y / 2.0f));
	return Raycast(owner->GetShapePosition(), Vector2f(0.0f, 1.0f), checkGroundDistance, _info, { owner, rayCastLineY });
}

void PlayerMovementComponent::Update(const float _deltaTime)
{
	if (!canMove) return;

	Jump();

	// Déplacement par défaut
	const float _finalSpeed = isSprinting ? sprintSpeed : speed;
	Vector2f _offset;
	_offset = direction * _finalSpeed * _deltaTime;

	// Si je suis en l'air et que je ne saute pas
	if (!(isOnGround = CheckGround()) && !isJumping)
	{
		// Application de la gravité
		_offset = direction + Vector2f(0.0f, 1.0f);
		_offset *= gravity * _deltaTime;
		//owner->GetDrawable()->move(_offset);
		//return;

		//TODO double jump
	}

	// Si je suis au sol
	else
	{
		// Si je suis en train de dash
		if (isDashing)
		{
			// Application de l'esquive
			_offset = Vector2f(dashDirection * dashSpeed * _deltaTime, 0.0f);
		}

		// Si je suis en train de jump et que je ne dash pas
		else if (isJumping)
		{
			// Application du saut
			_offset = direction + Vector2f(0.0f, -1.0f);
			Normalize(_offset);
			_offset *= jumpForce * _deltaTime;
		}

		// S'il faut que je reset mon dash
		if (!canDash && !isResetingDash)
		{
			isResetingDash = true;
			new Timer([this]() {
				canDash = true;
				isResetingDash = false;
			}, seconds(dashCooldown));
		}
	}

	const Vector2f& _collisionOffset = Vector2f(0.0f, -5.0f);
	const Vector2f& _destination = _offset + _collisionOffset;
	collision->GetBoxCollision()->GetDrawable()->setPosition(owner->GetShapePosition() + Vector2f(_destination.x * checkWallDistance, _destination.y));

	/*
	const float _collisionOffsetY = 5.0f;
	collision->GetBoxCollision()->GetDrawable()->setPosition(owner->GetShapePosition() + Vector2f(_offset.x * checkWallDistance, _offset.y * checkWallDistance - _collisionOffsetY));
	*/

	if (!collision->CheckCollision({ rayCastLineY }))
	{
		owner->GetDrawable()->move(_offset);
	}
}

void PlayerMovementComponent::StartJump()
{
	if (!canMove || isJumping || !isOnGround) return;

	//cout << "StartJump" << endl;
	isJumping = true;
	canIncreaseJump = true;

	animation->GetCurrentAnimation()->RunAnimation("Jump", dashDirection);
	//FxManager::GetInstance().Run("FxDoubleJump");

	jumpTimer = new Timer([&]() { 
		cout << "Stop Jump : " << jumpTimer->GetCurrentDuration() << endl;
		isJumping = false;
	}, seconds(jumpDuration));
	increaseJumpTimer = new Timer([&]() { 
		StopJump(); 
	}, seconds(increaseJumpDuration));
}

void PlayerMovementComponent::Jump()
{
	if (!canIncreaseJump) return;

	//cout << "Jump" << endl;
	jumpTimer->AddDuration(jumpDurationFactor);
	currentJumpForce += jumpForceFactor;
	//cout << "Jump : " << jumpTimer->GetCurrentDuration() << endl;
}

void PlayerMovementComponent::StopJump()
{
	//cout << "Stop increase" << endl;
	canIncreaseJump = false;
	currentJumpForce = jumpForce;
	//increaseJumpTimer->Stop();
}

void PlayerMovementComponent::Dash()
{
	if (!isOnGround || !canDash || isDashing) return;

	canDash = false;
	isDashing = true;
	new Timer([this]() { isDashing = false; }, seconds(dashDuration));
	animation->GetCurrentAnimation()->RunAnimation("Dash", dashDirection);
	FxManager::GetInstance().Run("FxDash");
}

void PlayerMovementComponent::SitDown()
{
	if (!isStanding || !owner->GetBounds().contains(Game::GetMap()->GetBench()->GetShapePosition()))
	{
		cout << "Impossible de s'assoir !" << endl;
		return;
	}

	const Vector2f& _position = owner->GetShapePosition();
	owner->GetDrawable()->setPosition(_position.x, _position.y - sitOffset);
	isStanding = false;
	canMove = false;

	animation->GetCurrentAnimation()->RunAnimation("Sit", dashDirection);
}

void PlayerMovementComponent::StandUp()
{
	if (isStanding)
	{
		cout << "Impossible de se lever !" << endl;
		return;
	}

	const Vector2f& _position = owner->GetShapePosition();
	owner->GetDrawable()->setPosition(_position.x, _position.y + sitOffset);
	isStanding = true;
	canMove = true;

	animation->GetCurrentAnimation()->RunAnimation("StopRight", dashDirection);
}