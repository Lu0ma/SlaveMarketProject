#include "Dragon.h"
#include "Game.h"
#include "MusicManager.h"

#define MUSIC "Dance.wav"

Dragon::Dragon(const ShapeData& _data) : Actor(STRING_ID("Grub"), _data)
{
	animation = new DragonAnimationComponent(this);
}

void Dragon::PlayMusic()
{
	Player* _player = Game::GetPlayer();
	if (!GetDrawable()->getGlobalBounds().intersects(_player->GetBounds()))
	{
	    MusicManager::GetInstance().Play(MUSIC);
	}
}