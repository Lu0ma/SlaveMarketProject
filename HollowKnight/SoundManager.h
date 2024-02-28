#pragma once
#include "Singleton.h"
#include "IManager.h"
#include "SoundData.h"

class SoundManager : public Singleton<SoundManager>, public IManager<string, SoundData>
{
	Sound sound;

public:
	SoundManager();

private:
	void Load(const string& _path);

public:
	void Play(const string& _path);
};