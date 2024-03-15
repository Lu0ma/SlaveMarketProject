#include "PlayerMovementComponent.h"
#include "Actor.h"
#include "PlayerAnimationComponent.h"
#include "Game.h"
#include "Timer.h"
#include "Macro.h"
#include "Kismet.h"
#include "FxManager.h"

PlayerMovementComponent::PlayerMovementComponent(Actor* _owner) : MovementComponent(_owner)
{
	// Movement
	canMove = false;
	speed = 0.45f;
	directionHasChanged = false;
	direction = Vector2f();

	// Ground
	isOnGround = false;
	checkGroundDistance = owner->GetShapeSize().y * 0.3f;

	// Jump
	isJumping = false;
	canDoubleJump = true;
	jumpForce = 1.2f;
	currentJumpForce = jumpForce;
	jumpFactor = 2.5f;

	// Gravity
	gravity = 0.41f;
	downSpeed = gravity;
	downFactor = 8.0f;

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
}


bool PlayerMovementComponent::CheckGround()
{
	HitInfo _info;
	return Raycast(owner->GetShapePosition(), Vector2f(0.0f, 1.0f), checkGroundDistance, _info, { owner });
}

void PlayerMovementComponent::StopJump()
{
	isJumping = false;
	currentJumpForce = jumpForce;
	downSpeed = gravity;
}


void PlayerMovementComponent::Update(const float _deltaTime)
{
	if (!canMove) return;

	if (isOnGround = CheckGround())
	{
		downSpeed = gravity;
		canDoubleJump = true;
		SetDirectionX(direction.x, "Right");
	}

	Game::GetCamera()->SetUpdate(!isOnGround);

	Vector2f _offset;

	// Si je suis en train de dash
	if (isDashing)
	{
		// Application de l'esquive
		_offset = Vector2f(dashDirection * dashSpeed * _deltaTime, 0.0f);
	}

	else
	{
		// S'il faut que je reset mon dash
		if (!canDash && !isResetingDash)
		{
			isResetingDash = true;
			new Timer([this]() {
				canDash = true;
				isResetingDash = false;
			}, seconds(dashCooldown));
		}

		// Déplacement par défaut
		_offset = direction * speed * _deltaTime;

		// Si je suis en l'air et que je ne saute pas
		if (!isOnGround && !isJumping)
		{
			downSpeed += downFactor / 1000.0f * _deltaTime;
			downSpeed = downSpeed > 2.0f ? 2.0f : downSpeed;

			// Application de la gravité
			_offset = direction + Vector2f(0.0f, 1.0f * downSpeed);
			Normalize(_offset);
			_offset *= _deltaTime;
		}

		// Si je suis en train de jump
		else if (isJumping)
		{
			currentJumpForce -= jumpFactor / 1000.0f * _deltaTime;
			if (currentJumpForce <= 0.5f)
			{
				StopJump();
			}

			_offset = direction + Vector2f(0.0f, -1.0f * currentJumpForce * 2.0f);
			Normalize(_offset);
			_offset *= _deltaTime;
		}
	}

	const Vector2f& _collisionOffset = Vector2f(0.0f, -5.0f);
	const Vector2f& _destination = _offset + _collisionOffset;
	collision->GetBoxCollision()->GetDrawable()->setPosition(owner->GetShapePosition() + Vector2f(_destination.x * checkWallDistance, _destination.y));

	if (!collision->CheckCollision())
	{
		owner->GetDrawable()->move(_offset);
	}
}

void PlayerMovementComponent::Jump()
{
	if (!canMove || !canDoubleJump) return;

	if (!isOnGround && canDoubleJump)
	{
		canDoubleJump = false;
		currentJumpForce = jumpForce;
		FxManager::GetInstance().Run("FxDoubleJump");
	}

	isJumping = true;
	animation->GetCurrentAnimation()->RunAnimation("Jump", dashDirection);
}

void PlayerMovementComponent::Dash()
{
	if (!canMove || !canDash || isDashing) return;

	isJumping = false;
	canDash = false;
	isDashing = true;
	new Timer([this]() { isDashing = false; }, seconds(dashDuration));
	animation->GetCurrentAnimation()->RunAnimation("Dash", dashDirection);
	FxManager::GetInstance().Run("FxDash");
}

void PlayerMovementComponent::SitDown()
{
	if (!canMove || !isStanding || !owner->GetBounds().contains(Game::GetMap()->GetBench()->GetShapePosition()))
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
	if (!canMove) return;

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


void PlayerMovementComponent::SetDirectionX(const float _directionX, const string& _animName)
{
	if (!canMove) return;

	if (_directionX == direction.x * -1.0f)
	{
		directionHasChanged = true;
	}

	if (_directionX == 0.0f)
	{
		animation->GetCurrentAnimation()->RunAnimation("StopRight", dashDirection);

		if (directionHasChanged)
		{
			directionHasChanged = false;
			return;
		}

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
		animation->GetCurrentAnimation()->RunAnimation(_animName, dashDirection);
	}

	direction.x = _directionX;
}