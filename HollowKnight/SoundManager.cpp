//#include "SoundManager.h"
//#include <iostream>
//
//SoundManager::SoundManager()
//{
//
//}
//
//
//void SoundManager::Play(const string& _path)
//{
//	if (_path == "") return;
//
//	SoundData* _soundData = Get(_path);
//
//	if (!_soundData)
//	{
//		Load(_path);
//		_soundData = Get(_path);
//	}
//
//	if (_soundData)
//	{
//		_soundData->Play();
//	}
//}
//
//void SoundManager::AdjustAllVolume(const float _volume)
//{ 
//	for (SoundData* _sound : SoundManager::GetInstance().GetAllValues())
//	{
//		_sound->AdjustVolume(_volume);
//	}
//}
//
//void SoundManager::Load(const string& _path)
//{
//	if (_path == "") return;
//
//	SoundData* _soundData = Get(_path);
//
//	if (!_soundData)
//	{
//		_soundData = new SoundData(_path, 100.0f);
//		if (!_soundData->loadFromFile("Assets/Sounds/" + _path))
//		{
//			cerr << "Le son n'a pas été correctement chargée !" << endl;
//		}
//	}
//}

#include "SoundManager.h"

SoundManager::SoundManager()
{
	volume = new float(40.0f);
	isMuted = false;
	tempVolume = 1;
}

SoundManager::~SoundManager()
{
	delete volume;
}

void SoundManager::Play(const string& _path, const DirectionalSettings& _settings)
{
	if (_path == "") return;

	SoundData* _soundData = Get(_path);

	if (!_soundData)
	{
		_soundData = new SoundData(_path);
	}

	_soundData->setPosition(Vector3f(_settings.position.x, _settings.position.y, 0.0f));
	_soundData->setRelativeToListener(_settings.attenuationSpeed == 0.0f);
	_soundData->setAttenuation(_settings.attenuationSpeed);
	_soundData->setMinDistance(_settings.minDistance);
	_soundData->setVolume(*volume);
	_soundData->play();
}

void SoundManager::Stop(const string& _path)
{
	if (_path == "") return;

	SoundData* _soundData = Get(_path);

	if (!_soundData)
	{
		_soundData = new SoundData(_path);
	}

	_soundData->stop();
}

void SoundManager::IncreaseVolume(const float _value)
{
	if (*volume <= 99.0f)
	{
		*volume += _value;
		for (SoundData* _sound : GetAllValues())
		{
			_sound->setVolume(*volume);
		}
	}
}

void SoundManager::DecreaseVolume(const float _value)
{
	if (*volume >= 1.0f)
	{
		*volume -= _value;
		for (SoundData* _sound : GetAllValues())
		{
			_sound->setVolume(*volume);
		}
	}
}