#include "PlayerMovementComponent.h"
#include "Actor.h"
#include "PlayerAnimationComponent.h"
#include "Game.h"
#include "Timer.h"
#include "Macro.h"
#include "Kismet.h"

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
	checkGroundDistance = 1.7f;

	// Jump
	isJumping = false;
	jumpForce = 0.65f;
	jumpDuration = 0.45f;
	gravity = 0.66f;

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

	// Components
	animation = owner->GetComponent<PlayerAnimationComponent>();
}


bool PlayerMovementComponent::CheckGround()
{
	HitInfo _hit;
	const bool _hasHit = Raycast(owner->GetShapePosition() + Vector2f(0.0f, 40.0f), Vector2f(0.0f, 1.0f),
								 checkGroundDistance, _hit, { owner->GetDrawable() });

	return _hasHit;
}

void PlayerMovementComponent::Update(const float _deltaTime)
{
	if (!canMove) return;

	// Déplacement par défaut
	const float _finalSpeed = isSprinting ? sprintSpeed : speed;
	Vector2f _offset;
	_offset = direction * _finalSpeed * _deltaTime;

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

	owner->GetDrawable()->move(_offset);
}

void PlayerMovementComponent::Jump()
{
	if (!canMove || !isOnGround || isJumping) return;

	isJumping = true;
	new Timer([this]() { isJumping = false; }, seconds(jumpDuration));
	animation->GetCurrentAnimation()->RunAnimation("Jump", dashDirection);
}

void PlayerMovementComponent::Dash()
{
	if (!isOnGround || !canDash || isDashing) return;

	canDash = false;
	isDashing = true;
	new Timer([this]() { isDashing = false; }, seconds(dashDuration));
	animation->GetCurrentAnimation()->RunAnimation("Dash", dashDirection);
}

void PlayerMovementComponent::SitDown()
{
	if (!isStanding || !owner->GetBounds().contains(Game::GetMap()->GetBench()->GetShapePosition()))
	{
		cout << "Impossible de se lever !" << endl;
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
		cout << "impossible de ce lever !" << endl;
		return;
	}

	const Vector2f& _position = owner->GetShapePosition();
	owner->GetDrawable()->setPosition(_position.x, _position.y + sitOffset);
	isStanding = true;
	canMove = true;

	animation->GetCurrentAnimation()->RunAnimation("StopRight", dashDirection);
}