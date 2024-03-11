#include "MusicData.h"
#include "MusicManager.h"
#include <iostream>

MusicData::MusicData(const string& _path, const float _volume, const float _volumeMax) : IManagable(_path)
{
	Register();

	setVolume(_volume);
	volumeMax = _volumeMax;
}

void MusicData::Register()
{
	MusicManager::GetInstance().Add(id, this);
}

void MusicData::Play()
{
	//play();
}

void MusicData::AdjustVolume(const float _percent)
{
	float _newVolume = _percent * volumeMax / 100.0f;
	_newVolume = _newVolume < 0.0f ? 0.0f : _newVolume;
	_newVolume = _newVolume > volumeMax ? volumeMax : _newVolume;
	setVolume(_newVolume);
}