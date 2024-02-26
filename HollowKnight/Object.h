#pragma once
#include <SFML/Graphics.hpp>
#include <string>

using namespace std;
using namespace sf;

struct Data
{
	Vector2f position = Vector2f();
	string path = string();

	Data() {}
	Data(const Vector2f& _position, const string& _path = "")
	{
		position = _position;
		path = _path;
	}
};

class Object
{
public:
	virtual Drawable* GetDrawable() const = 0;

public:
	virtual ~Object() {};
};