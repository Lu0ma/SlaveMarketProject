#include "Enemy.h"

Enemy::Enemy(const string& _name, const ShapeData& _data) : Actor(_name, _data)
{
	isDead = false;
	ShapeData _data2 = ShapeData(GetShapePosition(), Vector2f(200.0f, 5.0f), "");
	raycast = new Actor(STRING_ID("Raycast"), _data2);
}

void Enemy::Update(const float _deltaTime)
{
	Actor::Update(_deltaTime);
	raycast->SetShapePosition(GetShapePosition());
	raycast->GetDrawable()->setPosition(GetShapePosition() + (GetDrawable()->getScale().x > 0.0f ?
	Vector2f(raycast->GetShapeSize().x / 2.0f, raycast->GetShapeSize().y) : Vector2f(-raycast->GetShapeSize().x / 2.0f, raycast->GetShapeSize().y)));
}
