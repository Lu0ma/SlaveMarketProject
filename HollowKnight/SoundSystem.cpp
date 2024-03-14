#include "SoundSystem.h"

string GetExtensionNameByType(const AudioType& _type)
{
	const string _extentions[] = {
		"mp3",
		"wav"
	};

	return _extentions[_type];
}