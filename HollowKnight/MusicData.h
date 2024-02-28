#pragma once
#include "IManagable.h"
#include <SFML/Audio.hpp>

using namespace sf;
using namespace std;

class MusicData : public Music, public IManagable<string>
{
public:
	MusicData(const string& _path);

public:
	virtual void Register() override;
};
