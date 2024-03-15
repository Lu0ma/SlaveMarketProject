#include "InspectComponent.h"
#include "Actor.h"
#include "Player.h"
#include "Macro.h"
#include "Enemy.h"

InspectComponent::InspectComponent(Actor* _owner, const float _viewRange) : Component(_owner)
{
	hasTarget = false;
	viewRange = _viewRange;
	hitInfo = HitInfo();
}


void InspectComponent::Update(const float _deltaTime)
{
	const bool _hasHit = Raycast(owner->GetShapePosition(), owner->GetDrawable()->getScale(), viewRange, hitInfo, { owner });
	hasTarget = _hasHit && dynamic_cast<Player*>(hitInfo.actor);
}