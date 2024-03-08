#pragma once
#include "IManagable.h"

#include <SFML/Audio.hpp>

using namespace sf;
using namespace std;

class SoundData : public SoundBuffer, public IManagable<string>
{
	Sound* sound;
public:
	SoundData(const string& _path, const float _volume);

public:
	virtual void Register() override;
	void Play();
	void AdjustVolume(const float _percent);
};