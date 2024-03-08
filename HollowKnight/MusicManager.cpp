#include "MusicManager.h"
#include <iostream>

void MusicManager::Play(const string& _path)
{
	if (_path == "") return;

	MusicData* _musicData = Get(_path);

	if (!_musicData)
	{
		_musicData = new MusicData(_path, 100.0f);
		if (!_musicData->openFromFile("Assets/Musics/" + _path))
		{
			cerr << "Le son n'a pas été correctement chargée !" << endl;
			return;
		}
	}

	if (_musicData)
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