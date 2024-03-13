#include "PNJ.h"
#include "Macro.h"
#include "SoundManager.h"

PNJ::PNJ(const ShapeData& _data) : InteractableActor(STRING_ID("PNJ"), _data)
{
	/*animation = new AnimationComponent(this);
	components.push_back(animation);*/

	/*animation->AddNames({
		"Stand",
		"Talk"
	});*/

	const Vector2f& _sizeStand = Vector2f(53.0f, 76.0f);
	const Vector2f& _sizeTalk = Vector2f(57.0f, 76.0f);
	const float _speed = 0.2f;

	/*animation->InitAnimations({
		AnimationData("Stand", Vector2f(0.0f, 12.0f), _sizeStand, READ_RIGHT, true, 6, _speed),
		AnimationData("Talk", Vector2f(0.0f, 100.0f), _sizeTalk, READ_RIGHT, true, 6, _speed),
		});*/

	InitAnimations({
		AnimationData("Stand", Vector2f(0.0f, 12.0f), _sizeStand, READ_RIGHT, true, 6, _speed),
		AnimationData("Talk", Vector2f(0.0f, 100.0f), _sizeTalk, READ_RIGHT, true, 6, _speed),
		});

	soundIndex = 0;
}

void PNJ::Update(const float _deltaTime)
{

	soundIndex++;
	if (soundIndex > 3)
	{
		soundIndex = 0;
	}

	vector<string> _sounds = {
		"Assets/Musics/Hammer1.ogg",
		"Assets/Musics/Hammer2.ogg",
		"Assets/Musics/Hammer3.ogg",
		"Assets/Musics/Hammer4.ogg",
	};

	SoundManager::GetInstance().Play(_sounds[soundIndex], DirectionalSettings(GetPosition(), 175, 10.0f));
}

