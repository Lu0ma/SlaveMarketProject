#include "SoundManager.h"
#include <iostream>

SoundManager::SoundManager()
{

}

void SoundManager::Play(const string& _path)
{
	if (_path == "") return;

	SoundData* _soundData = Get(_path);

	if (!_soundData)
	{
		Load(_path);
		_soundData = Get(_path);
	}

	if (_soundData)
	{
		_soundData->Play();
	}
}

void SoundManager::AdjustAllVolume(const float _volume)
{ 
	for (SoundData* _sound : SoundManager::GetInstance().GetAllValues())
	{
		_sound->AdjustVolume(_volume);
	}
}

void SoundManager::Load(const string& _path)
{
	if (_path == "") return;

	SoundData* _soundData = Get(_path);

	if (!_soundData)
	{
		_soundData = new SoundData(_path, 100.0f);
		if (!_soundData->loadFromFile("Assets/Sounds/" + _path))
		{
			cerr << "Le son n'a pas été correctement chargée !" << endl;
		}
	}
}