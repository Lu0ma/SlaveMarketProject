#include "InspectComponent.h"
#include "Actor.h"
#include "Player.h"
#include "Macro.h"
#include "Enemy.h"

InspectComponent::InspectComponent(Actor* _owner, const float _viewRange) : Component(_owner)
{
	hitInfo = HitInfo();
	viewRange = _viewRange;
	factor = 5.0f;

	ShapeData _data2 = ShapeData(owner->GetShapePosition(), Vector2f(viewRange / 2.0f, 5.0f), "");
	raycast = new Actor(STRING_ID("Raycast"), _data2);
}

bool InspectComponent::HasTarget(const Vector2f& _position, Vector2f _destination)
{
	Enemy* _enemy;
	if (!(_enemy = dynamic_cast<Enemy*>(owner))) return false;

	if (_destination == Vector2f(0.0f, 0.0f))
	{
		_destination = Vector2f(1.0f, 0.0f);
	}

	Vector2f _direction = _destination - _position;
	Normalize(_direction);
	/*const float _maxDistance = Distance(_position, _destination);
	cout << "MaxDistance : " << _maxDistance << endl;*/
	HitInfo _hitInfo;

	Vector2f _size = owner->GetShapeSize();
	Vector2f _positionRayCast = Vector2f(_position.x, _position.y + (_size.y * 0.4f));

	const bool _hasHit = Raycast(_positionRayCast, Vector2f(_direction.x, 0.0f), viewRange, _hitInfo, { owner, raycast});

	raycast->SetShapePosition(_positionRayCast);
	raycast->GetDrawable()->setPosition(_positionRayCast+ (owner->GetDrawable()->getScale().x > 0.0f ?
	Vector2f(raycast->GetShapeSize().x / 2.0f, raycast->GetShapeSize().y) : Vector2f(-raycast->GetShapeSize().x / 2.0f, raycast->GetShapeSize().y)));

	if (_hasHit && dynamic_cast<Player*>(_hitInfo.actor)) //&& _hitInfo.distance < viewRange)
	{
		/*cout << owner->GetID() << " : " << _hitInfo.actor->GetID() << endl; */
		cout << _hitInfo.position.x << endl;
		hitInfo = _hitInfo;
		return true;
	}

	hitInfo = HitInfo();
	return false;
}

bool InspectComponent::IsInRange()
{	
	return hitInfo.actor && hitInfo.distance <= viewRange / 2.0f;
}