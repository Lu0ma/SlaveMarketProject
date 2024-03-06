#include "CollisionComponent.h"
#include "Actor.h"

CollisionComponent::CollisionComponent(Actor* _owner) : Component(_owner)
{
	boxCollision = new ShapeObject(ShapeData(_owner->GetBounds().getPosition(),
											 _owner->GetBounds().getSize(),
											 ""));
	boxCollision->GetDrawable()->setOutlineThickness(5.0f);
	boxCollision->GetDrawable()->setOutlineColor(Color::Red);
}

void CollisionComponent::CheckCollision(Actor* _owner)
{

}
