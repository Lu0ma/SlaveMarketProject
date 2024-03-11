#pragma once
#include "IManagable.h"
#include <SFML/Audio.hpp>

using namespace sf;
using namespace std;

class MusicData : public Music, public IManagable<string>
{
	float volumeMax;

public:
	MusicData(const string& _path, const float _volume,
			  const float _volumeMax = 100.0f);

public:
	virtual void Register() override;

	void Play();
	void AdjustVolume(const float _value);
};
