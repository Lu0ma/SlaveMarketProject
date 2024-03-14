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

SoundData::SoundData(const string& _path) : IManagable(_path)
{
	Register();
	buffer.loadFromFile(_path);
	setBuffer(buffer);
}

void SoundData::Register()
{
	SoundManager::GetInstance().Add(id, this);
}