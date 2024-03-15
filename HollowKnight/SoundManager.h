//#pragma once
//#include "Singleton.h"
//#include "IManager.h"
//#include "SoundData.h"
//
//class SoundManager : public Singleton<SoundManager>, public IManager<string, SoundData>
//{
//	
//
//public:
//	SoundManager();
//
//private:
//	void Load(const string& _path);
//
//public:
//	void Play(const string& _path);
//	void AdjustAllVolume(const float _volume);
//};

#pragma once

#include "IManager.h"
#include "SoundData.h"
#include "Singleton.h"

struct DirectionalSettings
{
	float minDistance;
	float attenuationSpeed;
	Vector2f position;

public:
	DirectionalSettings()
	{
		minDistance = 0.1f;
		attenuationSpeed = 75.0f;
		position = Vector2f();
	}
	DirectionalSettings(const Vector2f& _position, const float _minDistance, const float _attenuationSpeed)
	{
		position = _position;
		minDistance = _minDistance;
		attenuationSpeed = _attenuationSpeed;
	}
};

class SoundManager : public Singleton<SoundManager>, public IManager<string, SoundData>
{
	bool isMuted;
	float volume;
	float tempVolume;

public:
	SoundManager();

public:
	float GetVolume() const
	{
		return volume;
	}

public:
	void Play(const string& _path, const bool _isLoop ,const DirectionalSettings& _settings = DirectionalSettings());
	void AdjustAllVolume(const float _value);
	void Stop(const string& _path);
};