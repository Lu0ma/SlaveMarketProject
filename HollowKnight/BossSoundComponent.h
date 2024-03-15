#pragma once
#include "BossSound.h"
#include "Component.h"
#include "SoundData.h"
#include "SoundManager.h"


struct BossSoundComponent : public Component
{
	bool canPlay;

	BossSoundComponent(Actor* _owner) : Component(_owner)
	{
		canPlay = true;
		new SoundData(SOUND_JUMP_BOSS, 100, false);
		new SoundData(SOUND_LAND_BOSS, 100, false);
		new SoundData(SOUND_FIRST_LAND_BOSS, 100, false);
		new SoundData(SOUND_STRIKE_GROUND_BOSS, 100, false);
		new SoundData(SOUND_SWING_BOSS, 100, false);
		new SoundData(SOUND_DAMAGE_ARMOUR, 100, false);
		new SoundData(SOUND_CEILING_BREAK_BOSS, 100, false);
		new SoundData(SOUND_ATTACK_01, 100, false);
		new SoundData(SOUND_ATTACK_02, 100, false);
		new SoundData(SOUND_ATTACK_03, 100, false);
		new SoundData(SOUND_ATTACK_04, 100, false);
		new SoundData(SOUND_ATTACK_05, 100, false);
	}

	void PlaySound(const string& _path, const bool _canPlay)
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