//#pragma once
//#include "IManagable.h"
//
//#include <SFML/Audio.hpp>
//
//using namespace sf;
//using namespace std;
//
//class SoundData : public SoundBuffer, public IManagable<string>
//{
//	Sound* sound;
//	float volumeMax;
//
//public:
//	SoundData(const string& _path, const float _volume, 
//			  const float _volumeMax = 100.0f);
//
//public:
//	virtual void Register() override;
//	void Play();
//	void AdjustVolume(const float _percent);
//};

#pragma once

#include "IManagable.h"

#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;

class SoundManager;

class SoundData : public Sound, public IManagable<string>
{
	SoundBuffer buffer;

public:
	SoundData(const string& _path);

public:
	virtual void Register() override;
};