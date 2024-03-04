#pragma once
#include "Singleton.h"
#include "IManager.h"
#include "MusicData.h"

class MusicManager : public Singleton<MusicManager>, public IManager<string, MusicData>
{
public:
	void Play(const string& _path);
};
