#include "Dragon.h"
#include "Game.h"
#include "MusicManager.h"
#include "Macro.h"

#define MUSIC "Dance.wav"

Dragon::Dragon(const ShapeData& _data) : Actor(STRING_ID("Dragon"), _data)
{
	/*animation->AddNames({
		"DanceRight",
		"DanceLeft"
	});*/

	const float _speed = 0.085f;

	/*animation->InitAnimations({
		AnimationData("DanceLeft", Vector2f(0.0f, 476.0f), Vector2f(275.0f, 286.0f), READ_RIGHT, true, 8, _speed, "DanceRight"),
		AnimationData("DanceRight", Vector2f(0.0f, 53.0f), Vector2f(267.0f, 286.0f), READ_RIGHT, true, 8, _speed, "DanceLeft"),
	});*/

	InitAnimations({
		AnimationData("DanceLeft", Vector2f(0.0f, 476.0f), Vector2f(275.0f, 286.0f), READ_RIGHT, false, 8, _speed, "DanceRight"),
		AnimationData("DanceRight", Vector2f(0.0f, 53.0f), Vector2f(267.0f, 286.0f), READ_RIGHT, false, 8, _speed, "DanceLeft"),
		});
}


void Dragon::PlayMusic()
{
	Player* _player = Game::GetPlayer();
	if (!GetDrawable()->getGlobalBounds().intersects(_player->GetBounds()))
	{
	    MusicManager::GetInstance().Play(MUSIC);
	}
}