#pragma once

#include <SFML/Audio.hpp>
#include "IManagable.h"
#include "SoundSystem.h"

using namespace std;
using namespace sf;

class SoundManager;

class SoundData : public Sound, public IManagable<string>
{
	float volumeMax;
	SoundBuffer buffer;
public:
	SoundData(const string& _path, const float _volume,  const bool _isLoop , const float _volumeMax = 100.0f, const AudioType& _type = WAV);

public:
	virtual void Register() override;
	void AdjustVolume(const float _percent);
	void GetSound(const string& _sound);
};