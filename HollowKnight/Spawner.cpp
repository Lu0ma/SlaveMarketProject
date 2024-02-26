#include "Spawner.h"

Spawner::Spawner()
{
}

void Spawner::Spawn()
{
	Vector2f _position = Vector2f(200.0f, 300.0f);
	Vector2f _size = Vector2f(100.0f, 100.0f);
	string _path = "Assets/Textures/test.png";

	ShapeData _data = ShapeData(_position, _size, _path);
	new Mob(_data);
}
