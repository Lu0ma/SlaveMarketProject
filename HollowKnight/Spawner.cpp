#include "Spawner.h"
#include "HuskBully.h"
#include "Belfly.h"

#define PATH_BOOFLY "Animations/Boofly.png"
#define PATH_DEATHMOB "Animations/DeathMob.png"

Spawner::Spawner()
{
	index = -1;

	animationNames = {
		"Idle",
		"Right",
		"Bounce",
		"DeathAir",
		"DeathLand",
		"StandBy",
		"Explosion",
	};
}


void Spawner::Spawn()
{
	Vector2f _position = Vector2f(500.0f, 200.0f);
	Vector2f _size = Vector2f(100.0f, 100.0f);
	string _path = PATH_BOOFLY;

	ShapeData _data = ShapeData(_position, _size, _path, IntRect(0, 18, 316, 346));
	boofly = new Boofly(_data);
	//deathMob = new DeathMob(_data);

	new Timer([&]() {
		index++;
		index %= (int)animationNames.size();
		boofly->GetComponent<AnimationComponent>()->RunAnimation(animationNames[index]);
		//deathMob->GetComponent<AnimationComponent>()->RunAnimation(animationNames[6]);
	}, seconds(2.0f), true, true);
}
