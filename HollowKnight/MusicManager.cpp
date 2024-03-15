#include "MusicManager.h"
#include <iostream>

void MusicManager::Play(const string& _path)
{
	if (current)
	{
		current->Stop();
	}

	if (MusicData* _musicData = Get(_path))
	{
		_musicData->Play();
	}
}

void MusicManager::AdjustAllVolume(const float _volume)
{
	for (MusicData* _musicData : MusicManager::GetInstance().GetAllValues())
	{
		_musicData->AdjustVolume(_volume);
	}
}

void MusicManager::Stop(const string& _path)
{
	if (current && _path == "")
	{
		current->Stop();
		return;
	}

	if (MusicData* _musicData = Get(_path))
	{
		_musicData->Stop();
	}
}