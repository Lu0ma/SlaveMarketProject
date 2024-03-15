//#include "SoundData.h"
//#include "SoundManager.h"
//#include <iostream>
//
//SoundData::SoundData(const string& _path, const float _volume, const float _volumeMax) : IManagable(_path)
//{
//	Register();
//
//	sound->setVolume(_volume);
//	volumeMax = _volumeMax;
//}
//
//void SoundData::Register()
//{
//	SoundManager::GetInstance().Add(id, this);
//}
//
//void SoundData::Play()
//{
//	sound->setBuffer(*this);
//	sound->play();
//}
//
//void SoundData::AdjustVolume(const float _percent)
//{
//	float _newVolume = _percent * volumeMax / 100.0f;
//	_newVolume = _newVolume < 0.0f ? 0.0f : _newVolume;
//	_newVolume = _newVolume > volumeMax ? volumeMax : _newVolume;
//	sound->setVolume(_newVolume);
//}

#include "SoundData.h"
#include "SoundManager.h"
#include <iostream>

SoundData::SoundData(const string& _path, const float _volume, const bool _isLoop, const float _volumeMax,  const AudioType& _type) : IManagable(_path)
{
	Register();

	setVolume(_volume);
	volumeMax = _volumeMax;

	if (!buffer.loadFromFile("Assets/Audio/Sounds/" + _path + "." + GetExtensionNameByType(_type)))
	{
		cerr << "Le son " << _path << " n'a pas été correctement chargé !" << endl;
		return;
	}
	//setBuffer(buffer); // Warning 
	// SoundManager::GetInstance().Play(_path , _isLoop);	// Warning
}

void SoundData::Register()
{
	SoundManager::GetInstance().Add(id, this);
}

void SoundData::AdjustVolume(const float _percent)
{
	float _newVolume = _percent * volumeMax / 100.0f;
	_newVolume = _newVolume < 0.0f ? 0.0f : _newVolume;
	_newVolume = _newVolume > volumeMax ? volumeMax : _newVolume;
	setVolume(_newVolume);
}

void SoundData::GetSound(const string& _sound)
{
	SoundManager::GetInstance().Get(_sound);
}