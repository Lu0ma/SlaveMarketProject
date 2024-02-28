#include "Spawner.h"
#include "HuskBully.h"
#include "Belfly.h"

#define PATH_BOOFLY "Animations/Boofly.png"
#define PATH_BELFLY "Animations/BelflyModif.png"

Spawner::Spawner()
{
	index = -1;
	boofly = nullptr;
	belfly = nullptr;
	/*animationNames = {
		"FlyLeft",
		"FlyRight",
		"TurnToLeft", 
		"TurnToRight",
		"BounceLeft", 
		"BounceRight",
		"DeathAirLeft",
		"DeathAirRight",
		"DeathLand",
	};*/
}


void Spawner::Spawn()
{
	Vector2f _position = Vector2f(500.0f, 600.0f);
	Vector2f _positionBelfly = Vector2f(500.0f, 50.0f);
	Vector2f _size = Vector2f(100.0f, 100.0f);
	Vector2f _sizeBelfly = Vector2f(120.0f, 160.0f);
	string _path = PATH_BOOFLY;
	string _pathBelfly = PATH_BELFLY;

	ShapeData _data = ShapeData(_position, _size, _path, IntRect(0, 17, 315, 345));
	ShapeData _dataBelfly = ShapeData(_positionBelfly, _sizeBelfly, _pathBelfly);
	boofly = new Boofly(_data);
	belfly = new Belfly(_dataBelfly);
	//const vector<string>& _animationNames = boofly->GetComponent<AnimationComponent>()->GetAnimationNames();

	/*new Timer([&]() {
		index++;
		index %= (int)_animationNames.size();

		boofly->GetComponent<AnimationComponent>()->RunAnimation(_animationNames[index]);
	}, seconds(2.0f), true, true);*/
}
