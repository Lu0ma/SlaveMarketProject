#include "PlayerMovementComponent.h"
#include "Actor.h"
#include "Timer.h"
#include "Macro.h"
#include "Kismet.h"

PlayerMovementComponent::PlayerMovementComponent(Actor* _owner) : MovementComponent(_owner)
{
	// Movement
	canMove = true;
	speed = 0.45f;
	direction = Vector2f();

	// Sprint
	isSprinting = false;
	sprintSpeed = 0.3f;

	// Ground
	isOnGround = false;
	checkGroundDistance = 1.7f;

	canJumpAndDash = false;

	// Jump
	isJumping = false;
	jumpForce = 0.1f;
	jumpDuration = 5.0f;
	gravity = 0.1f;

	// Dash
	canDash = true;
	isDashing = false;
	isResetingDash = false;
	dashSpeed = 0.75f;
	dashDuration = 0.2f;
	dashCooldown = 3.0f;

}


bool PlayerMovementComponent::CheckGround()
{
	HitInfo _hit;
	const bool _hasHit = Raycast(owner->GetShapePosition(), Vector2f(0.0f, 1.0f),
								 checkGroundDistance, _hit, { owner->GetDrawable() });

	return _hasHit;
}

void PlayerMovementComponent::Update(const float _deltaTime)
{
	if(!canMove) return;
	MovementComponent::Update(_deltaTime);
	Vector2f _offset;
		
	// Déplacement par défaut
	const float _finalSpeed = isSprinting ? sprintSpeed : speed;
	_offset = direction * _finalSpeed * _deltaTime;

	// Si je suis en donjon
	if (canJumpAndDash)
	{
		// Si je suis en l'air et que je ne saute pas
		if (!(isOnGround = CheckGround()) && !isJumping)
		{
			// Application de la gravité
			_offset = direction + Vector2f(0.0f, 1.0f);
			Normalize(_offset);
			_offset *= gravity * _deltaTime;
		}

		// Si je suis au sol
		else
		{
			// Si je suis en train de dash
			if (isDashing)
			{
				// Application de l'esquive
				_offset = dashDirection * dashSpeed * _deltaTime;
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
	}

	owner->GetDrawable()->move(_offset);
}

void PlayerMovementComponent::Jump()
{
	if (!isOnGround || isJumping) return;
	isJumping = true;
	new Timer([this]() { isJumping = false; }, seconds(jumpDuration));
}

void PlayerMovementComponent::Dash()
{
	if (!isOnGround || !canDash || isDashing) return;

	canDash = false;
	isDashing = true;
	dashDirection = direction;
	new Timer([this]() { isDashing = false; }, seconds(dashDuration));
}