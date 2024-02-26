#pragma once
#include "IManagable.h"

#include <SFML/Graphics.hpp>
#include <string>

using namespace std;
using namespace sf;

class FontData : public Font, public IManagable<string>
{
public:
	FontData(const string& _path);

private:
	virtual void Register() override;
};