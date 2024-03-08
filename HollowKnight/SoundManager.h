#pragma once
#include "Singleton.h"
#include "IManager.h"
#include "SoundData.h"

class SoundManager : public Singleton<SoundManager>, public IManager<string, SoundData>
{
	

public:
	SoundManager();

private:
	void Load(const string& _path);

public:
	void Play(const string& _path);
	void AdjustAllVolume(const float _volume);
};