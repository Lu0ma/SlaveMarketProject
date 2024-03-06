#include "MusicData.h"
#include "MusicManager.h"
#include <iostream>

MusicData::MusicData(const string& _path, const float _volume) : IManagable(_path)
{
	volumeMax = _volume;
	setVolume(volumeMax);
	Register();
}

void MusicData::Register()
{
	MusicManager::GetInstance().Add(id, this);
}

void MusicData::Play()
{
	setVolume(0.0f);
	play();
}

void MusicData::AdjustVolume(const float _percent)
{
	const float _value = _percent * volumeMax / 100.0f;
	float _volume = getVolume() + _value;
	_volume < 0 ? _volume = 0 : _volume;
	_volume > 100 ? _volume = 100 : _volume;
	setVolume(_volume);
}
