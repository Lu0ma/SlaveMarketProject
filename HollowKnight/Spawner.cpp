#include "Spawner.h"
#include "HuskBully.h"
#include "Boofly.h"
#include "Belfly.h"
#include "FalseKnight.h"

#define PATH_BOOFLY "Animations/Boofly.png"
#define PATH_BELFLY "Animations/BelflyModif.png"
#define PATH_HUSK_BULLY "Animations/HuskBully.png"
#define PATH_DEATHMOB "Animations/DeathMob.png"
#define PATH_FALSE_KNIGHT "Animations/FalseKnight.png"

Spawner::Spawner()
{
	index = -1;
}

void Spawner::Spawn()
{
	Vector2f _positionBoofly = Vector2f(0.0f, -250.0f);
	Vector2f _positionBelfly = Vector2f(200.0f, 225.0f);
	Vector2f _positionHuskBully = Vector2f(400.0f, 250.0f);
	Vector2f _sizeBoofly = Vector2f(220.0f, 200.0f);
	Vector2f _sizeBelfly = Vector2f(50.0f, 50.0f);
	Vector2f _sizeHuskBully = Vector2f(75.0f, 75.0f);

	ShapeData _dataBoofly = ShapeData(_positionBoofly, _sizeBoofly, PATH_BOOFLY, IntRect(0, 17, 315, 345));
	boofly = new Boofly(_dataBoofly);
	boofly->Init();

	Vector2f _positionFalseKnight = Vector2f(4000.0f, -250.0f);
	Vector2f _sizeFalseKnight = Vector2f(700.0f, 500.0f);

	ShapeData _data = ShapeData(_positionFalseKnight, _sizeFalseKnight, PATH_FALSE_KNIGHT);
	FalseKnight* _falseKnight = new FalseKnight(_data);
	_falseKnight->Init();
}