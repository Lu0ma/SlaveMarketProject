#include "InspectComponent.h"
#include "Actor.h"
#include "Player.h"
#include "Macro.h"
#include "Enemy.h"

InspectComponent::InspectComponent(Actor* _owner, const float _viewRange) : Component(_owner)
{
	hitInfo = HitInfo();
	viewRange = _viewRange;
}

bool InspectComponent::HasTarget(const Vector2f& _position, const Vector2f& _destination)
{
	Enemy* _enemy;
	hitInfo = HitInfo();
	if (!(_enemy = dynamic_cast<Enemy*>(owner))) return false;

	Vector2f _direction = _destination - _position;
	Normalize(_direction);
	const float _maxDistance = Distance(_position, _destination);
	HitInfo _hitInfo;

	const bool _hasHit = Raycast(_position, _direction, _maxDistance, _hitInfo, { owner->GetDrawable() });
	if (_hasHit && dynamic_cast<Player*>(_hitInfo.actor) && _hitInfo.distance < 1.0f)
	{
		cout << owner->GetID() << " : " << _hitInfo.actor->GetID() << endl;
		cout << _hitInfo.distance << endl;
		hitInfo = _hitInfo;
		return true;
	}

	hitInfo = HitInfo();
	return false;
}

bool InspectComponent::IsInRange()
{	
	return hitInfo.actor && hitInfo.distance <= viewRange;
}