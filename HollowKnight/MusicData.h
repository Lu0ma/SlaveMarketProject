#pragma once
#include <SFML/Audio.hpp>
#include "IManagable.h"
#include "SoundSystem.h"

using namespace sf;
using namespace std;

class MusicData : public Music, public IManagable<string>
{
	float volumeMax;

public:
	MusicData(const string& _path, const float _volume, const float _volumeMax = 100.0f,
			  const AudioType& _type = MP3);

public:
	virtual void Register() override;

	void Play();
	void AdjustVolume(const float _value);
	void Stop();
};