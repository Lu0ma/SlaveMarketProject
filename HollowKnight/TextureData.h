#pragma once
#include "IManagable.h"
#include <string>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class TextureManager;

class TextureData : public Texture, public IManagable<string>
{
public:
	TextureData(const string& _path);

private:
	virtual void Register() override;
};