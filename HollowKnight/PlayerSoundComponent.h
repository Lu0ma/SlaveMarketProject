#pragma once
#include "PlayerSound.h"
#include "Component.h"
#include "SoundData.h"
#include "SoundManager.h"
struct PlayerSoundComponent : public Component
{
	bool canPlay;
	PlayerSoundComponent(Actor* _owner) : Component(_owner)
	{
		 canPlay = true;
		 new SoundData(SOUND_FOOTSTEP_GRASS, 100, true);
		 new SoundData(SOUND_FOOTSTEP_STONE, 100, true);
		 new SoundData(SOUND_DAMAGE_V1, 100, false);
		 new SoundData(SOUND_DASH, 100, false);
		 new SoundData(SOUND_JUMP, 100, false);
		 new SoundData(SOUND_WINGS, 100, false);
		 new SoundData(SOUND_CHARGE_LOOP, 100, false);
		 new SoundData(SOUND_CHARGE_COMPLETE, 100, false);
	}

	//~PlayerSoundComponent()
	//{
	//	for(SoundData* )
	//}


	void PlaySound(const string& _path , const bool _canPlay)
	{
		canPlay = _canPlay;
		if (!canPlay)
		{
			SoundManager::GetInstance().Get(_path)->stop();
			return;
		}
		SoundManager::GetInstance().Get(_path)->Play();
	}

	void GetSound(const string& _path)
	{
		SoundManager::GetInstance().Get(_path);
	}
};

