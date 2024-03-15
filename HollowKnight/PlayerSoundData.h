#pragma once
#include "PlayerSound.h"
#include <vector>
#include "SoundData.h"
class PlayerSoundData
{
	vector<SoundData*> playerSounds;

public:
	PlayerSoundData();

public:
	vector<SoundData*> GetPlayerSounds() const
	{
		return playerSounds;
	}
};

