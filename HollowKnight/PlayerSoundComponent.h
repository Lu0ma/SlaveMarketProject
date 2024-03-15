#pragma once
#include "PlayerSound.h"
#include "Component.h"
#include "SoundData.h"
#include "SoundManager.h"
struct PlayerSoundComponent : public Component
{
	SoundData* footStep;
	SoundData* attack;
	SoundData* dash;
	SoundData* jump;
	PlayerSoundComponent(Actor* _owner) : Component(_owner)
	{

		footStep = new  SoundData(SOUND_FOOTSTEP_GRASS, 100, true);
		attack = new SoundData(SOUND_DAMAGE_V1, 100, false);
		dash = new SoundData(SOUND_DASH, 100, false);
		jump = new SoundData(SOUND_JUMP, 100, false);
	}

	void SetFootStepSound(SoundData* _newSound)
	{
		footStep = _newSound;
	}

	void Update()
	{

	}

	void PlaySound(const string& _path , const bool _canPlay)
	{
		if (!_canPlay)
		{
			SoundManager::GetInstance().Get(_path)->stop();
			return;
		}
		SoundManager::GetInstance().Get(_path)->Play();
	}
};

