#include "SoundData.h"
#include "SoundManager.h"
#include <iostream>

SoundData::SoundData(const string& _path, const float _volume) : IManagable(_path)
{
	sound->setVolume(_volume);
	Register();
}

void SoundData::Register()
{
	SoundManager::GetInstance().Add(id, this);
}

void SoundData::Play()
{
	sound->setBuffer(*this);
	sound->play();
}

void SoundData::AdjustVolume(const float _percent)
{
	const float _value = _percent * sound->getVolume() / 100.0f;

	float _volume = sound->getVolume() + _value;
	_volume < 0 ? _volume = 0 : _volume;
	_volume > 100 ? _volume = 100 : _volume;
	sound->setVolume(_volume);
}
