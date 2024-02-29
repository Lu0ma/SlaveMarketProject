#include "Spawner.h"
#include "HuskBully.h"
#include "Boofly.h"
#include "Belfly.h"

#define PATH_BOOFLY "Animations/Boofly.png"
#define PATH_BELFLY "Animations/BelflyModif.png"
#define PATH_HUSK_BULLY "Animations/HuskBully.png"

Spawner::Spawner()
{
	index = -1;
}


void Spawner::Spawn()
{
	Vector2f _positionBoofly = Vector2f(00.0f, 50.0f);
	Vector2f _positionBelfly = Vector2f(00.0f, 25.0f);
	Vector2f _positionHuskBully = Vector2f(00.0f, 0.0f);
	Vector2f _sizeBoofly = Vector2f(120.0f, 100.0f);
	Vector2f _sizeBelfly = Vector2f(50.0f, 50.0f);
	Vector2f _sizeHuskBully = Vector2f(75.0f, 75.0f);
	string _pathBoofly = PATH_BOOFLY;
	string _pathBelfly = PATH_BELFLY;
	string _pathHuskBully = PATH_HUSK_BULLY;

	ShapeData _dataBoofly = ShapeData(_positionBoofly, _sizeBoofly, _pathBoofly, IntRect(0, 17, 315, 345));
	ShapeData _dataBelfly = ShapeData(_positionBelfly, _sizeBelfly, _pathBelfly);
	ShapeData _dataHuskBully = ShapeData(_positionHuskBully, _sizeHuskBully, _pathHuskBully);
	//new Boofly(_dataBoofly);
	//new Belfly(_dataBelfly);
	new HuskBully(_dataHuskBully);
}
