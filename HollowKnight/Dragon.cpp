#include "Dragon.h"
#include"Game.h"
#include"MusicManager.h"

#define MUSIC "Dance.wav"

Dragon::Dragon(const string& _name, const ShapeData& _data, const vector<string>& _texts)
	: InteractableActor(_name, _data)
{
	animations = new DragonAnimationComponent(this);
}

void Dragon::PlayMusic()
{
	Player* _player = Game::GetPlayer();
	if (GetDrawable()->getGlobalBounds().contains(_player->GetPosition()))
	{
	    MusicManager::GetInstance().Play(MUSIC);
	}
	
	//MusicManager::GetInstance().Stop(MUSIC);
	
	
}
