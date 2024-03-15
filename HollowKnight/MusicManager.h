#pragma once
#include "Singleton.h"
#include "IManager.h"
#include "MusicData.h"

class MusicManager : public Singleton<MusicManager>, public IManager<string, MusicData>
{
	MusicData* current;

public:
	void Play(const string& _path);
	void AdjustAllVolume(const float _volume);
	void Stop(const string& _path = "");
};