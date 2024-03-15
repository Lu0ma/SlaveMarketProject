#pragma once
#include <string>

using namespace std;

enum AudioType
{
	MP3,
	WAV
};

string GetExtensionNameByType(const AudioType& _type);