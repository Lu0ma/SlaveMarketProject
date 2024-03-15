#include "MusicData.h"
#include "MusicManager.h"
#include <iostream>

MusicData::MusicData(const string& _path, const float _volume, const float _volumeMax,
					 const AudioType& _type) : IManagable(_path)
{
	Register();

	setVolume(_volume);
	volumeMax = _volumeMax;

	if (!openFromFile("Assets/Audio/Musics/" + _path + "." + GetExtensionNameByType(_type)))
	{
		cerr << "Le son " << _path << " n'a pas été correctement chargée !" << endl;
		return;
	}

	MusicManager::GetInstance().Play(_path);
}


void MusicData::Register()
{
	MusicManager::GetInstance().Add(id, this);
}

void MusicData::Play()
{
	play();
}

void MusicData::AdjustVolume(const float _percent)
{
	float _newVolume = _percent * volumeMax / 100.0f;
	_newVolume = _newVolume < 0.0f ? 0.0f : _newVolume;
	_newVolume = _newVolume > volumeMax ? volumeMax : _newVolume;
	setVolume(_newVolume);
}

void MusicData::Stop()
{
	stop();
}