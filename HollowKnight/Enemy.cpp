#include "Enemy.h"

Enemy::Enemy(const string& _name, const ShapeData& _data) : Actor(_name, _data, CT_NONE)
{
	isDead = false;
	ShapeData _data2 = ShapeData(GetShapePosition(), Vector2f(200.0f, 5.0f), "");
}

void Enemy::Update(const float _deltaTime)
{
	Actor::Update(_deltaTime);
}