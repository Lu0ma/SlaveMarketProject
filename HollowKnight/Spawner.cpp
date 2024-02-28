#include "Spawner.h"
#include "HuskBully.h"
#include "Belfly.h"
#include "BooFly.h"

Spawner::Spawner()
{
}

void Spawner::Spawn()
{
	Vector2f _position = Vector2f(500.0f, 200.0f);
	Vector2f _size = Vector2f(100.0f, 100.0f);
	string _path = "";

	ShapeData _data = ShapeData(_position, _size, _path);
	new Boofly(_data);
}
